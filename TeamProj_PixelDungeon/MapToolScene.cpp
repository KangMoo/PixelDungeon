#include "stdafx.h"
#include "MapToolScene.h"

MapToolScene::MapToolScene()
{
}


MapToolScene::~MapToolScene()
{
}
HRESULT MapToolScene::init()
{
	_check = 0;
	_showTile = false;
	_showTileIndex = 0;

	imageSetup();

	//카메라
	_cameraX = _cameraY = 0;

	//맵 rect
	for (int i = 0; i < GRIDNUM; i++) {
		int x = (i % GRIDX + 1) * TILESIZE;
		int y = (i / GRIDX + 1) * TILESIZE;
		_mapRect[i].x = x;
		_mapRect[i].y = y;
		_mapRect[i].index = i;
		_mapRect[i].empty = true;
		_mapRect[i].rc = RectMake(x, y, TILESIZE, TILESIZE);		
	}
	
	int palPosX = _mapRect[GRIDX - 1].rc.right;
	int palPosY = _mapRect[GRIDX - 1].rc.top;
	
	//팔레트 rect
	for (int i = 0; i < PALETTENUM; i++) {
		int x = (i % PALETTEX);
		int y = (i / PALETTEX);
		_paletRect[i].x = x;
		_paletRect[i].y = y;
		_paletRect[i].index = i;
		_paletRect[i].rc = RectMake((x + 1) * TILESIZE + palPosX + x, y * TILESIZE + palPosY + y, TILESIZE, TILESIZE);
	}
	_paletPage = 0;


	//인풋모드(임시)
	_inputMode = MODE_FLOOR;
	_inputLayer = LAYER_TILE;

	//버튼
	_buttonRect[0].rc = RectMake(WINSIZEX - 85, WINSIZEY - 40, WINSIZEX - 20, WINSIZEY - 20);//돌아가기
				  																			 
	_buttonRect[1].rc = RectMakeCenter(300, 15, 20, 20);									 //카메라
	_buttonRect[2].rc = RectMakeCenter(300, WINSIZEY - 40, 20, 20);							 //
	_buttonRect[3].rc = RectMakeCenter(15, WINSIZEY / 2 - 20, 20, 20);						 //
	_buttonRect[4].rc = RectMakeCenter(560, WINSIZEY / 2 - 20, 20, 20);						 //

	_buttonRect[5].rc = RectMakeCenter(_paletRect[PALETTEX / 2].rc.left - 52, _paletRect[PALETTENUM-1].rc.bottom + 20, 40, 20);
	_buttonRect[6].rc = RectMakeCenter(_paletRect[PALETTEX / 2].rc.right + 12, _paletRect[PALETTENUM - 1].rc.bottom + 20, 40, 20);


	for (int i = 0; i < BUTTONNUM; i++) {
		_buttonRect[i].isClicked = false;
	}

	_selectRangeRect = RectMake(0, 0, 0, 0);
	_selectRangePoint = { 0,0 };

	_inputCountdown = 0;

	paletteSetup();

	SOUNDMANAGER->play("48.map", 1.0);

	return S_OK;
}
void MapToolScene::release()
{
	SOUNDMANAGER->stop("48.map");
}

void MapToolScene::imageSetup() {

	//==== TILE ====
	_imgNameList.push_back("mapTiles");
	_imgNameList.push_back("chest");
	_imgNameList.push_back("water");
	_imgNameList.push_back("trap");

	//==== MONSTER ====

	_imgNameList_monster.push_back("rat");
	_imgNameList_monster.push_back("gnoll");
	_imgNameList_monster.push_back("crap");
	_imgNameList_monster.push_back("swarm");
	_imgNameList_monster.push_back("goo");

	image* rat = IMAGEMANAGER->addFrameImage("rat", "Img/Enemy/rat/blackAttack.bmp", 96, 64, 3, 2, true, RGB(255, 0, 255));
	image* gnoll = IMAGEMANAGER->addFrameImage("gnoll", "Img/Enemy/gnoll_attack.bmp", 48, 60, 2, 2, true, RGB(255, 0, 255));
	image* crap = IMAGEMANAGER->addFrameImage("crap", "Img/Enemy/crap_attack.bmp", 96, 64, 3, 2, true, RGB(255, 0, 255));
	image* swarm = IMAGEMANAGER->addFrameImage("swarm", "Img/Enemy/swarm_stay.bmp", 264, 56, 11, 2, true, RGB(255, 0, 255));
	image* goo = IMAGEMANAGER->addFrameImage("goo", "Img/Enemy/goo/goo_dead.bmp", 96, 64, 3, 2, true, RGB(255, 0, 255));



	for (int i = 0; i < _imgNameList.size(); i++) {
		image* image1 = IMAGEMANAGER->findImage(_imgNameList[i]);
		_imgList.push_back(image1);		
	}

	for (int i = 0; i < _imgNameList_monster.size(); i++) {
		image* image1 = IMAGEMANAGER->findImage(_imgNameList_monster[i]);
		_imgList_monster.push_back(image1);
	}
}

void MapToolScene::paletteSetup()
{
	int index = 0;

	for (auto img : _imgList) {
		for (int i = 0; i <= img->getMaxFrameY(); i++) {
			for (int j = 0; j <= img->getMaxFrameX(); j++) {
				TILE palTile;
				ZeroMemory(&palTile, sizeof(TILE));
				palTile.img = img;
				palTile.sourX = j;
				palTile.sourY = i;

				palTile.destX = index % PALETTEX;
				palTile.destY = index / PALETTEX;

				_vPaletTile.push_back(palTile);

				index++;
			}
		}
	}

	for (auto img : _imgList_monster) {
		TILE palTile;
		ZeroMemory(&palTile, sizeof(TILE));
		palTile.img = img;
		palTile.sourX = 0;
		palTile.sourY = 0;

		palTile.destX = index % PALETTEX;
		palTile.destY = index / PALETTEX;

		_vPaletTile.push_back(palTile);

		index++;
	}
}


void MapToolScene::update()	
{	
	input();
}


void MapToolScene::input()
{
	input_ModeChange();
	input_SelectMapGrid();
	input_AddTile();
	input_ClickPalet();
	input_ClickButton();


	if (KEYMANAGER->isOnceKeyDown(VK_DELETE)) {

		if (!_vMapSelected.empty()) {
			switch (_inputLayer) {
			case LAYER_TILE:
				for (int i = 0; i < _vMapSelected.size(); i++) {
					int indexX = _vMapSelected[i].index % GRIDX + _cameraX;
					int indexY = _vMapSelected[i].index / GRIDX + _cameraY;
					for (_viMapTile = _vMapTile.begin(); _viMapTile != _vMapTile.end();) {
						if (_viMapTile->destX == indexX && _viMapTile->destY == indexY) {
							_viMapTile = _vMapTile.erase(_viMapTile);
						}
						else _viMapTile++;
					}
				}
			break;
			case LAYER_DECO:
				for (int i = 0; i < _vMapSelected.size(); i++) {
					int indexX = _vMapSelected[i].index % GRIDX + _cameraX;
					int indexY = _vMapSelected[i].index / GRIDX + _cameraY;
					for (_viDecoTile = _vDecoTile.begin(); _viDecoTile != _vDecoTile.end();) {
						if (_viDecoTile->destX == indexX && _viDecoTile->destY == indexY) {
							_viDecoTile = _vDecoTile.erase(_viDecoTile);
						}
						else
							_viDecoTile++;
					}
				}
				break;
			case LAYER_OBJ:
				for (int i = 0; i < _vMapSelected.size(); i++) {
					int indexX = _vMapSelected[i].index % GRIDX + _cameraX;
					int indexY = _vMapSelected[i].index / GRIDX + _cameraY;
					for (_viObj = _vObj.begin(); _viObj != _vObj.end();) {
						if (_viObj->destX == indexX && _viObj->destY == indexY) {
							_viObj = _vObj.erase(_viObj);
						}
						else
							_viObj++;
					}
				}
				break;
			case LAYER_ITEM:
				break;
			}
		}
	}
	

	if (KEYMANAGER->isStayKeyDown(VK_LCONTROL) && KEYMANAGER->isOnceKeyDown('S')) {
		save();
	}
	if (KEYMANAGER->isStayKeyDown(VK_LCONTROL) && KEYMANAGER->isOnceKeyDown('O')) {
		load();
	}


	if (KEYMANAGER->isOnceKeyDown(VK_UP)) {
		_buttonRect[1].isClicked = true;
		if (_cameraY > 0) cameraMove(0, -1);
		_inputCountdown = 0.5;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN)) {
		_buttonRect[2].isClicked = true;
		cameraMove(0, 1);
		_inputCountdown = 0.5;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT)) {
		_buttonRect[3].isClicked = true;
		if (_cameraX > 0) cameraMove(-1, 0);
		_inputCountdown = 0.5;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT)) {
		_buttonRect[4].isClicked = true;
		cameraMove(1, 0);
		_inputCountdown = 0.5;
	}
	
	if (KEYMANAGER->isStayKeyDown(VK_UP) || KEYMANAGER->isStayKeyDown(VK_DOWN) || KEYMANAGER->isStayKeyDown(VK_LEFT) || KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_inputCountdown -= TIMEMANAGER->getElapsedTime();
	}
	
	if (_inputCountdown < 0) {
		_inputCountdown = 0.1;
		if (KEYMANAGER->isStayKeyDown(VK_UP)) {
			_buttonRect[1].isClicked = true;
			if (_cameraY > 0) cameraMove(0, -1);
		}
		if (KEYMANAGER->isStayKeyDown(VK_DOWN)) {
			_buttonRect[2].isClicked = true;
			cameraMove(0, 1);
		}
		if (KEYMANAGER->isStayKeyDown(VK_LEFT)) {
			_buttonRect[3].isClicked = true;
			if (_cameraX > 0) cameraMove(-1, 0);
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) {
			_buttonRect[4].isClicked = true;
			cameraMove(1, 0);
		}
	}

	if ((KEYMANAGER->isOnceKeyUp(VK_UP)))
		_buttonRect[1].isClicked = false;
	if ((KEYMANAGER->isOnceKeyUp(VK_DOWN)))
		_buttonRect[2].isClicked = false;
	if ((KEYMANAGER->isOnceKeyUp(VK_LEFT)))
		_buttonRect[3].isClicked = false;
	if ((KEYMANAGER->isOnceKeyUp(VK_RIGHT)))
		_buttonRect[4].isClicked = false;

}


void MapToolScene::render()	
{	
	for (int i = 0; i < GRIDNUM; i++) {
		Rectangle(getMemDC(), _mapRect[i].rc.left, _mapRect[i].rc.top, _mapRect[i].rc.right, _mapRect[i].rc.bottom);
		
		//char str[128];
		//sprintf(str, "%d", i);
		//TextOut(getMemDC(), _mapRect[i].rc.left, _mapRect[i].rc.top, str, strlen(str));
	}
	for (int i = 0; i < PALETTENUM; i++) {
		Rectangle(getMemDC(), _paletRect[i].rc.left, _paletRect[i].rc.top, _paletRect[i].rc.right, _paletRect[i].rc.bottom);
	}

	if (!_vMapTile.empty()) { _check = _vMapTile[0].sourX; }

	//test
	char str[128];
	sprintf(str, "CAMERA x : %d y : %d    %d %d", _cameraX, _cameraY, _vMapTile.size(), _vObj.size());
	//sprintf(str, "%d %d %d %d %d %d", _selectRangeRect.left, _selectRangeRect.top, _selectRangeRect.right, _selectRangeRect.bottom, _ptMouse.x, _ptMouse.y);

	TextOut(getMemDC(), 10, 10, str, strlen(str));
	//test

	for (int i = 0; i < PALETTENUM; i++) {

		int tileIndex = i + _paletPage * PALETTENUM;
		if (tileIndex >= _vPaletTile.size()) break;

		int rectIndex = _vPaletTile[tileIndex].destX + (_vPaletTile[tileIndex].destY - _paletPage * PALETTEY) * PALETTEX;

		int destX = _paletRect[rectIndex].rc.left;
		int destY = _paletRect[rectIndex].rc.top;

		_vPaletTile[tileIndex].img->frameRender(getMemDC(), destX, destY, _vPaletTile[tileIndex].sourX, _vPaletTile[tileIndex].sourY);
	}


	for (int i = 0; i < _vMapTile.size(); i++) {
		if (_vMapTile[i].destX - _cameraX < 0 || _vMapTile[i].destY - _cameraY < 0 ||
			_vMapTile[i].destX - _cameraX >= GRIDX || _vMapTile[i].destY - _cameraY >= GRIDY) continue;
		
		int index = _vMapTile[i].destX - _cameraX + (_vMapTile[i].destY - _cameraY) * GRIDX;

		int destX = _mapRect[index].rc.left;
		int destY = _mapRect[index].rc.top;

		int alpha;
		if (_inputLayer == LAYER_TILE) {
			if		(_vMapTile[i].terrain == TERRAIN_FLOOR				&& _inputMode == MODE_FLOOR)				alpha = 0;
			else if (_vMapTile[i].terrain == TERRAIN_WATER				&& _inputMode == MODE_WATER)				alpha = 0;
			else if (_vMapTile[i].terrain == TERRAIN_CHASM				&& _inputMode == MODE_CHASM)				alpha = 0;
			else if (_vMapTile[i].terrain == TERRAIN_GRASS				&& _inputMode == MODE_GRASS)				alpha = 0;
			else if (_vMapTile[i].terrain == TERRAIN_GRASS_UNTOUCHED	&& _inputMode == MODE_GRASS_UN)				alpha = 0;
			else if (_vMapTile[i].terrain == TERRAIN_WALL				&& _inputMode == MODE_WALL)					alpha = 0;
			else if (_vMapTile[i].terrain == TERRAIN_BARRICADE			&& _inputMode == MODE_BARRICADE)			alpha = 0;
			else if (_vMapTile[i].terrain == TERRAIN_STATUE				&& _inputMode == MODE_STATUE)				alpha = 0;
			else if (_vMapTile[i].terrain == TERRAIN_DOOR_CLOSED		&& _inputMode == MODE_DOOR)					alpha = 0;
			else if (_vMapTile[i].terrain == TERRAIN_DOOR_LOCKED		&& _inputMode == MODE_DOOR_LOCKED)			alpha = 0;
			else if (_inputMode == MODE_DELET)																		alpha = 0;
			else alpha = 100;
		}
		else if (_inputLayer < LAYER_TILE)																			alpha = 255;
		else if (_inputLayer > LAYER_TILE)																			alpha = 150;
		
		if (_inputMode == MODE_VIEWING)																				alpha = 0;
		if (_inputMode == MODE_VIEWING_TILE)																		alpha = 255;

		_vMapTile[i].img->alphaFrameRender(getMemDC(), destX, destY, _vMapTile[i].sourX, _vMapTile[i].sourY, alpha);


		if ((_inputMode == MODE_VIEWING_TILE)) {
			HBRUSH brush;
			if ((_vMapTile[i].terrain & ATTRIBUTE_UNGO) == ATTRIBUTE_UNGO)
				brush = CreateSolidBrush(RGB(255, 0, 0));
			else if ((_vMapTile[i].terrain & ATTRIBUTE_UNSIGHT) == ATTRIBUTE_UNSIGHT)
				brush = CreateSolidBrush(RGB(0, 255, 0));
			else 
				brush = CreateSolidBrush(RGB(100, 100, 100));

			FillRect(getMemDC(), &_mapRect[index].rc, brush);
			DeleteObject(brush);
		}
		//char str[128];
		//sprintf(str, "%d %d", _vMapTile[i].destX, _vMapTile[i].destY);
		//TextOut(getMemDC(), _mapRect[index].rc.left, _mapRect[index].rc.top, str, strlen(str));
	}



	for (int i = 0; i < _vDecoTile.size(); i++) {
		if (_vDecoTile[i].destX - _cameraX < 0 || _vDecoTile[i].destY - _cameraY < 0 ||
			_vDecoTile[i].destX - _cameraX >= GRIDX || _vDecoTile[i].destY - _cameraY >= GRIDY) continue;

		int index = _vDecoTile[i].destX - _cameraX + (_vDecoTile[i].destY - _cameraY) * GRIDX;

		int destX = _mapRect[index].rc.left;
		int destY = _mapRect[index].rc.top;
		
		int alpha;
		if (_inputLayer == LAYER_DECO)																				alpha = 0;
		else if (_inputLayer < LAYER_DECO)																			alpha = 255;
		else if (_inputLayer > LAYER_DECO)																			alpha = 150;

		if (_inputMode == MODE_VIEWING)																				alpha = 0;
		if (_inputMode == MODE_VIEWING_TILE)																		alpha = 255;

		_vDecoTile[i].img->alphaFrameRender(getMemDC(), destX, destY, _vDecoTile[i].sourX, _vDecoTile[i].sourY, alpha);
	}

	for (int i = 0; i < _vObj.size(); i++) {
		if (_vObj[i].destX - _cameraX < 0 || _vObj[i].destY - _cameraY < 0 ||
			_vObj[i].destX - _cameraX >= GRIDX || _vObj[i].destY - _cameraY >= GRIDY) continue;
		int index = _vObj[i].destX - _cameraX + (_vObj[i].destY - _cameraY) * GRIDX;

		int destX = _mapRect[index].rc.left;
		int destY = _mapRect[index].rc.top;

		int alpha;
		if (_inputLayer == LAYER_OBJ) {
			if		(_vObj[i].obj == OBJ_CHEST					&& _inputMode == MODE_CHEST)						alpha = 0;
			else if (_vObj[i].obj == OBJ_STAIR_START			&& _inputMode == MODE_STAIR_START)					alpha = 0;
			else if (_vObj[i].obj == OBJ_STAIR_END				&& _inputMode == MODE_STAIR_END)					alpha = 0;
			else if (_vObj[i].obj == OBJ_POT					&& _inputMode == MODE_POT)							alpha = 0;
			else if (_vObj[i].obj == OBJ_WELL					&& _inputMode == MODE_WELL)							alpha = 0;
			else if (_vObj[i].obj == OBJ_TRAP					&& _inputMode == MODE_TRAP)							alpha = 0;
			else if (_inputMode == MODE_DELET)																		alpha = 0;
			else alpha = 100;
		}
		else if (_inputLayer < LAYER_OBJ)																			alpha = 255;
		else if (_inputLayer > LAYER_OBJ)																			alpha = 150;


		if (_inputMode == MODE_VIEWING)																				alpha = 0;
		if (_inputMode == MODE_VIEWING_TILE)																		alpha = 255;


		_vObj[i].img->alphaFrameRender(getMemDC(), destX, destY, _vObj[i].sourX, _vObj[i].sourY, alpha);		
	}



	for (int i = 0; i < _vItem.size(); i++) {
		if (_vItem[i].destX - _cameraX < 0 || _vItem[i].destY - _cameraY < 0 ||
			_vItem[i].destX - _cameraX >= GRIDX || _vItem[i].destY - _cameraY >= GRIDY) continue;
		int index = _vItem[i].destX - _cameraX + (_vItem[i].destY - _cameraY) * GRIDX;

		int destX = _mapRect[index].rc.left;
		int destY = _mapRect[index].rc.top;

		int alpha;
		if (_inputLayer == LAYER_ITEM) {
			alpha = 0;
		}
		else if (_inputLayer < LAYER_ITEM)																			alpha = 255;
		else if (_inputLayer > LAYER_ITEM)																			alpha = 150;


		if (_inputMode == MODE_VIEWING)																				alpha = 0;
		if (_inputMode == MODE_VIEWING_TILE)																		alpha = 255;


		_vItem[i].img->alphaFrameRender(getMemDC(), destX, destY, _vItem[i].sourX, _vItem[i].sourY, alpha);
	}

	for (int i = 0; i < _vMon.size(); i++) {
		if (_vMon[i].destX - _cameraX < 0 || _vMon[i].destY - _cameraY < 0 ||
			_vMon[i].destX - _cameraX >= GRIDX || _vMon[i].destY - _cameraY >= GRIDY) continue;
		int index = _vMon[i].destX - _cameraX + (_vMon[i].destY - _cameraY) * GRIDX;

		int destX = _mapRect[index].rc.left;
		int destY = _mapRect[index].rc.top;

		int alpha;
		if (_inputLayer == LAYER_MONSTER) {
			alpha = 0;
		}
		else if (_inputLayer < LAYER_MONSTER)																			alpha = 255;
		else if (_inputLayer > LAYER_MONSTER)																			alpha = 150;


		if (_inputMode == MODE_VIEWING)																				alpha = 0;
		if (_inputMode == MODE_VIEWING_TILE)																		alpha = 255;


		_vMon[i].img->alphaFrameRender(getMemDC(), destX, destY, 0,0, alpha);
	}



	if (_showTile && !(KEYMANAGER->isStayKeyDown(VK_RBUTTON))) {
		_paletSelected[0].img->alphaFrameRender(getMemDC(), _mapRect[_showTileIndex].rc.left, _mapRect[_showTileIndex].rc.top, _vPaletTile[_paletSelected[0].index].sourX, _vPaletTile[_paletSelected[0].index].sourY, 150);
	}


	//선택 내용 색칠 등

	for (auto select : _vMapSelected) {
		HBRUSH myBrush, oldBrush;
		HPEN myPen, oldPen;
		myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		myPen = CreatePen(PS_SOLID, 4, RGB(255, 0, 255));

		oldPen = (HPEN)SelectObject(getMemDC(), myPen);
		oldBrush = (HBRUSH)SelectObject(getMemDC(), myBrush);
		Rectangle(getMemDC(), select.rc.left, select.rc.top, select.rc.right + 1, select.rc.bottom + 1);
		
		SelectObject(getMemDC(), oldPen);
		SelectObject(getMemDC(), oldBrush);
		DeleteObject(myBrush);
		DeleteObject(myPen);
		//DeleteObject(oldBrush);
		//DeleteObject(oldPen);
	}


	for (auto select : _paletSelected) {
		HBRUSH myBrush, oldBrush;
		HPEN myPen, oldPen;
		myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		myPen = CreatePen(PS_SOLID, 4, RGB(255, 0, 255));

		oldPen = (HPEN)SelectObject(getMemDC(), myPen);
		oldBrush = (HBRUSH)SelectObject(getMemDC(), myBrush);
		Rectangle(getMemDC(), select.rc.left, select.rc.top, select.rc.right + 1, select.rc.bottom + 1);
		SelectObject(getMemDC(), oldPen);
		SelectObject(getMemDC(), oldBrush);

		DeleteObject(myPen);
		DeleteObject(myBrush);
		//DeleteObject(oldPen);
		//DeleteObject(oldBrush);
	}


	// 클릭하면 회색빛으로
	for (int i = 0; i < BUTTONNUM; i++) {
		if (_buttonRect[i].isClicked) {
			HBRUSH btBrush, obtBrush;
			btBrush = (HBRUSH)CreateSolidBrush(RGB(100, 100, 100));
			obtBrush = (HBRUSH)SelectObject(getMemDC(), btBrush);
			Rectangle(getMemDC(), _buttonRect[i].rc.left, _buttonRect[i].rc.top, _buttonRect[i].rc.right, _buttonRect[i].rc.bottom);

			SelectObject(getMemDC(), obtBrush);
			//DeleteObject(obtBrush);
			DeleteObject(btBrush);
		}
		else {
			Rectangle(getMemDC(), _buttonRect[i].rc.left, _buttonRect[i].rc.top, _buttonRect[i].rc.right, _buttonRect[i].rc.bottom);
		}
	}

	//test~
	TextOut(getMemDC(), WINSIZEX - 50, 5, "맵툴씬", strlen("맵툴씬"));
	TextOut(getMemDC(), WINSIZEX - 70, WINSIZEY - 25, "돌아가기", strlen("돌아가기"));

	TextOut(getMemDC(), _buttonRect[5].rc.left + 2, _buttonRect[5].rc.top + 2,  "prev", strlen("prev"));
	TextOut(getMemDC(), _buttonRect[6].rc.left + 2, _buttonRect[6].rc.top + 2, "next", strlen("next"));

	char page[128];
	sprintf(page, "page : %d", _paletPage);
	TextOut(getMemDC(), _buttonRect[5].rc.right, _buttonRect[5].rc.top + 2, page, strlen(page));
	
	switch (_inputMode)
	{
	case MODE_FLOOR:		TextOut(getMemDC(), _buttonRect[5].rc.right, _buttonRect[5].rc.top + 20, "FLOOR",			strlen("FLOOR"));			break;
	case MODE_WATER:		TextOut(getMemDC(), _buttonRect[5].rc.right, _buttonRect[5].rc.top + 20, "WATER",			strlen("WATER"));			break;
	case MODE_CHASM:		TextOut(getMemDC(), _buttonRect[5].rc.right, _buttonRect[5].rc.top + 20, "CHASM",			strlen("CHASM"));			break;
	case MODE_GRASS:		TextOut(getMemDC(), _buttonRect[5].rc.right, _buttonRect[5].rc.top + 20, "GRASS",			strlen("GRASS"));			break;
	case MODE_GRASS_UN:		TextOut(getMemDC(), _buttonRect[5].rc.right, _buttonRect[5].rc.top + 20, "GRASS_UN",		strlen("GRASS_UN"));		break;
	case MODE_WALL:			TextOut(getMemDC(), _buttonRect[5].rc.right, _buttonRect[5].rc.top + 20, "WALL",			strlen("WALL"));			break;
	case MODE_BARRICADE:	TextOut(getMemDC(), _buttonRect[5].rc.right, _buttonRect[5].rc.top + 20, "BARICADE",		strlen("BARICADE"));		break;
	case MODE_STATUE:		TextOut(getMemDC(), _buttonRect[5].rc.right, _buttonRect[5].rc.top + 20, "STATUE",			strlen("STATUE"));			break;
	case MODE_DOOR:			TextOut(getMemDC(), _buttonRect[5].rc.right, _buttonRect[5].rc.top + 20, "DOOR",			strlen("DOOR"));			break;
	case MODE_DOOR_LOCKED:	TextOut(getMemDC(), _buttonRect[5].rc.right, _buttonRect[5].rc.top + 20, "DOOR_LOCKED",		strlen("DOOR_LOCKED"));		break;
	
	case MODE_CHEST:		TextOut(getMemDC(), _buttonRect[5].rc.right, _buttonRect[5].rc.top + 20, "CHEST",			strlen("CHEST"));			break;
	case MODE_STAIR_START:	TextOut(getMemDC(), _buttonRect[5].rc.right, _buttonRect[5].rc.top + 20, "STAIR_START",		strlen("STAIR_START"));		break;
	case MODE_STAIR_END:	TextOut(getMemDC(), _buttonRect[5].rc.right, _buttonRect[5].rc.top + 20, "STAIR_END",		strlen("STAIR_END"));		break;
	case MODE_POT:			TextOut(getMemDC(), _buttonRect[5].rc.right, _buttonRect[5].rc.top + 20, "POT",				strlen("POT"));				break;
	case MODE_WELL:			TextOut(getMemDC(), _buttonRect[5].rc.right, _buttonRect[5].rc.top + 20, "WELL",			strlen("WELL"));			break;
	case MODE_TRAP:			TextOut(getMemDC(), _buttonRect[5].rc.right, _buttonRect[5].rc.top + 20, "TRAP",			strlen("TRAP"));			break;

	case MODE_VIEWING:		TextOut(getMemDC(), _buttonRect[5].rc.right, _buttonRect[5].rc.top + 20, "VIEWING_IMAGE",	strlen("VIEWING_IMAGE"));	break;
	case MODE_VIEWING_TILE:	TextOut(getMemDC(), _buttonRect[5].rc.right, _buttonRect[5].rc.top + 20, "VIEWING_TILE",	strlen("VIEWING_TILE"));	break;
	case MODE_DELET:		TextOut(getMemDC(), _buttonRect[5].rc.right, _buttonRect[5].rc.top + 20, "ERASER",			strlen("ERASER"));			break;
	}

	switch (_inputLayer) {
	case LAYER_TILE:		TextOut(getMemDC(), _buttonRect[5].rc.right, _buttonRect[5].rc.top + 40, "TILE",			strlen("TILE"));			break;
	case LAYER_DECO:		TextOut(getMemDC(), _buttonRect[5].rc.right, _buttonRect[5].rc.top + 40, "DECO",			strlen("DECO"));			break;
	case LAYER_OBJ:			TextOut(getMemDC(), _buttonRect[5].rc.right, _buttonRect[5].rc.top + 40, "OBJ",				strlen("OBJ"));				break;
	case LAYER_ITEM:		TextOut(getMemDC(), _buttonRect[5].rc.right, _buttonRect[5].rc.top + 40, "ITEM",			strlen("ITEM"));			break;
	case LAYER_MONSTER:		TextOut(getMemDC(), _buttonRect[5].rc.right, _buttonRect[5].rc.top + 40, "MONSTER",			strlen("MONSTER"));			break;
	}


	HBRUSH myBrush2, oldBrush2;
	if (KEYMANAGER->isStayKeyDown(VK_RBUTTON)) {
		myBrush2 = (HBRUSH)GetStockObject(NULL_BRUSH);
		oldBrush2 = (HBRUSH)SelectObject(getMemDC(), myBrush2);
		Rectangle(getMemDC(), _selectRangeRect.left, _selectRangeRect.top, _selectRangeRect.right, _selectRangeRect.bottom);
		DeleteObject(myBrush2);
	}

	//~test
}

void MapToolScene::save()
{
	OPENFILENAME ofn;
	char filePathSize[1028] = "";
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = filePathSize;
	ofn.nMaxFile = sizeof(filePathSize);
	ofn.nFilterIndex = true;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = NULL;
	ofn.lpstrInitialDir = NULL;
	ofn.lpstrFilter = ("XML Files(*.xml)\0*.xml\0");
	ofn.Flags = OFN_OVERWRITEPROMPT;
	if (GetSaveFileName(&ofn) == FALSE) return;

	char temp[1028];
	strncpy_s(temp, strlen(ofn.lpstrFile) + 1, ofn.lpstrFile, strlen(ofn.lpstrFile));

	char* context = NULL;
	char* token = strtok_s(temp, "\\", &context);
	while (strlen(context))
	{
		token = strtok_s(NULL, "\\", &context);
	}



	//xml 저장
	XMLDocument xmlDoc;
	XMLNode *pRoot;

	pRoot = xmlDoc.NewElement("map");
	xmlDoc.InsertFirstChild(pRoot);

	XMLElement * pMapElement_Tile = xmlDoc.NewElement("TileList");

	XMLElement * pTileElementSize = xmlDoc.NewElement("size");
	pTileElementSize->SetText(_vMapTile.size());
	pMapElement_Tile->InsertEndChild(pTileElementSize);


	int sizeX = 0, sizeY = 0;

	for (int i = 0; i < _vMapTile.size(); i++) {
		if (_vMapTile[i].destX > sizeX) sizeX = _vMapTile[i].destX;
		if (_vMapTile[i].destY > sizeY) sizeY = _vMapTile[i].destY;
	}

	XMLElement * pTileElementSizeX = xmlDoc.NewElement("sizeX");
	pTileElementSizeX->SetText(sizeX+1);
	pMapElement_Tile->InsertEndChild(pTileElementSizeX);
	XMLElement * pTileElementSizeY = xmlDoc.NewElement("sizeY");
	pTileElementSizeY->SetText(sizeY+1);
	pMapElement_Tile->InsertEndChild(pTileElementSizeY);

	for (int i = 0; i < _vMapTile.size(); i++) {
		XMLElement * pListElementT = xmlDoc.NewElement("tile");

		XMLElement * pListElement1 = xmlDoc.NewElement("destX");
		pListElement1->SetText(_vMapTile[i].destX);
		XMLElement * pListElement2 = xmlDoc.NewElement("destY");
		pListElement2->SetText(_vMapTile[i].destY);
		XMLElement * pListElement3 = xmlDoc.NewElement("sourX");
		pListElement3->SetText(_vMapTile[i].sourX);
		XMLElement * pListElement4 = xmlDoc.NewElement("sourY");
		pListElement4->SetText(_vMapTile[i].sourY);
		XMLElement * pListElement5 = xmlDoc.NewElement("obj");
		pListElement5->SetText(OBJ_NONE);
		XMLElement * pListElement6 = xmlDoc.NewElement("terrain");
		pListElement6->SetText(_vMapTile[i].terrain);
		XMLElement * pListElement7 = xmlDoc.NewElement("imgNum");
		for (int j = 0; j < _imgNameList.size(); j++) {
			if (_vMapTile[i].img == IMAGEMANAGER->findImage(_imgNameList[j]))
			{
				pListElement7->SetText(j);
				break;
			}
			if (j == _imgNameList.size() - 1)
				pListElement7->SetText(0);
		}

		pListElementT->InsertEndChild(pListElement1);
		pListElementT->InsertEndChild(pListElement2);
		pListElementT->InsertEndChild(pListElement3);
		pListElementT->InsertEndChild(pListElement4);
		pListElementT->InsertEndChild(pListElement5);
		pListElementT->InsertEndChild(pListElement6);
		pListElementT->InsertEndChild(pListElement7);

		pMapElement_Tile->InsertEndChild(pListElementT);
	}
	pRoot->InsertEndChild(pMapElement_Tile);


	XMLElement * pMapElement_Deco = xmlDoc.NewElement("DecoList");

	XMLElement * pDecoElementSize = xmlDoc.NewElement("size");
	pDecoElementSize->SetText(_vDecoTile.size());
	pMapElement_Deco->InsertEndChild(pDecoElementSize);


	for (int i = 0; i < _vDecoTile.size(); i++) {
		XMLElement * pListElementT = xmlDoc.NewElement("tile");

		XMLElement * pListElement1 = xmlDoc.NewElement("destX");
		pListElement1->SetText(_vDecoTile[i].destX);
		XMLElement * pListElement2 = xmlDoc.NewElement("destY");
		pListElement2->SetText(_vDecoTile[i].destY);
		XMLElement * pListElement3 = xmlDoc.NewElement("sourX");
		pListElement3->SetText(_vDecoTile[i].sourX);
		XMLElement * pListElement4 = xmlDoc.NewElement("sourY");
		pListElement4->SetText(_vDecoTile[i].sourY);
		XMLElement * pListElement5 = xmlDoc.NewElement("obj");
		pListElement5->SetText(OBJ_NONE);
		XMLElement * pListElement6 = xmlDoc.NewElement("terrain");
		pListElement6->SetText(_vDecoTile[i].terrain);
		XMLElement * pListElement7 = xmlDoc.NewElement("imgNum");
		for (int j = 0; j < _imgNameList.size(); j++) {
			if (_vDecoTile[i].img == IMAGEMANAGER->findImage(_imgNameList[j]))
			{
				pListElement7->SetText(j);
				break;
			}
			if (j == _imgNameList.size() - 1)
				pListElement7->SetText(0);
		}

		pListElementT->InsertEndChild(pListElement1);
		pListElementT->InsertEndChild(pListElement2);
		pListElementT->InsertEndChild(pListElement3);
		pListElementT->InsertEndChild(pListElement4);
		pListElementT->InsertEndChild(pListElement5);
		pListElementT->InsertEndChild(pListElement6);
		pListElementT->InsertEndChild(pListElement7);

		pMapElement_Deco->InsertEndChild(pListElementT);
	}
	pRoot->InsertEndChild(pMapElement_Deco);

	XMLElement * pMapElement_Obj = xmlDoc.NewElement("ObjList");

	XMLElement * pObjElementSize = xmlDoc.NewElement("size");
	pObjElementSize->SetText(_vObj.size());
	pMapElement_Obj->InsertEndChild(pObjElementSize);

	for (int i = 0; i < _vObj.size(); i++) {
		XMLElement * pListElementT = xmlDoc.NewElement("obj");

		XMLElement * pListElement1 = xmlDoc.NewElement("destX");
		pListElement1->SetText(_vObj[i].destX);
		XMLElement * pListElement2 = xmlDoc.NewElement("destY");
		pListElement2->SetText(_vObj[i].destY);
		XMLElement * pListElement3 = xmlDoc.NewElement("sourX");
		pListElement3->SetText(_vObj[i].sourX);
		XMLElement * pListElement4 = xmlDoc.NewElement("sourY");
		pListElement4->SetText(_vObj[i].sourY);
		XMLElement * pListElement5 = xmlDoc.NewElement("obj");
		pListElement5->SetText(_vObj[i].obj);
		XMLElement * pListElement6 = xmlDoc.NewElement("imgNum");
		for (int j = 0; j < _imgNameList.size(); j++) {
			if (_vObj[i].img == IMAGEMANAGER->findImage(_imgNameList[j]))
			{
				pListElement6->SetText(j);
				break;
			}
			if (j == _imgNameList.size() - 1)
				pListElement6->SetText(0);
		}

		pListElementT->InsertEndChild(pListElement1);
		pListElementT->InsertEndChild(pListElement2);
		pListElementT->InsertEndChild(pListElement3);
		pListElementT->InsertEndChild(pListElement4);
		pListElementT->InsertEndChild(pListElement5);
		pListElementT->InsertEndChild(pListElement6);
		

		pMapElement_Obj->InsertEndChild(pListElementT);
	}
	pRoot->InsertEndChild(pMapElement_Obj);



	XMLElement * pMapElement_Item = xmlDoc.NewElement("ItemList");

	XMLElement * pItemElementSize = xmlDoc.NewElement("size");
	pItemElementSize->SetText(_vItem.size());
	pMapElement_Item->InsertEndChild(pItemElementSize);

	for (int i = 0; i < _vItem.size(); i++) {
		XMLElement * pListElementT = xmlDoc.NewElement("item");

		XMLElement * pListElement1 = xmlDoc.NewElement("destX");
		pListElement1->SetText(_vItem[i].destX);
		XMLElement * pListElement2 = xmlDoc.NewElement("destY");
		pListElement2->SetText(_vItem[i].destY);
		XMLElement * pListElement6 = xmlDoc.NewElement("imgNum");
		for (int j = 0; j < _imgNameList.size(); j++) {
			if (_vItem[i].img == IMAGEMANAGER->findImage(_imgNameList[j]))
			{
				pListElement6->SetText(j);
				break;
			}
			if (j == _imgNameList.size() - 1)
				pListElement6->SetText(0);
		}

		pListElementT->InsertEndChild(pListElement1);
		pListElementT->InsertEndChild(pListElement2);
		pListElementT->InsertEndChild(pListElement6);


		pMapElement_Item->InsertEndChild(pListElementT);
	}
	pRoot->InsertEndChild(pMapElement_Item);


	XMLElement * pMapElement_Mon = xmlDoc.NewElement("MonsterList");

	XMLElement * pMonElementSize = xmlDoc.NewElement("size");
	pMonElementSize->SetText(_vMon.size());
	pMapElement_Mon->InsertEndChild(pMonElementSize);

	for (int i = 0; i < _vMon.size(); i++) {
		XMLElement * pListElementT = xmlDoc.NewElement("monster");

		XMLElement * pListElement1 = xmlDoc.NewElement("destX");
		pListElement1->SetText(_vMon[i].destX);
		XMLElement * pListElement2 = xmlDoc.NewElement("destY");
		pListElement2->SetText(_vMon[i].destY);
		XMLElement * pListElement6 = xmlDoc.NewElement("name");
		for (int j = 0; j < _imgNameList.size(); j++) {
			if (_vMon[i].img == IMAGEMANAGER->findImage(_imgNameList_monster[j]))
			{
				pListElement6->SetText(_imgNameList_monster[j].c_str());
				break;
			}
			if (j == _imgNameList.size() - 1)
				pListElement6->SetText(0);
		}

		pListElementT->InsertEndChild(pListElement1);
		pListElementT->InsertEndChild(pListElement2);
		pListElementT->InsertEndChild(pListElement6);


		pMapElement_Mon->InsertEndChild(pListElementT);
	}
	pRoot->InsertEndChild(pMapElement_Mon);


	//XMLError eResult = xmlDoc.SaveFile("SavedData.xml");
	XMLError eResult = xmlDoc.SaveFile(token);


/*
	WriteFile(file, &saveMap, sizeof(SAVETILE) * size, &write, NULL);

	CloseHandle(file);

	delete[] saveMap;*/

}

void MapToolScene::load()
{
	OPENFILENAME ofn;
	char filePathSize[1028] = "";
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = filePathSize;
	ofn.nMaxFile = sizeof(filePathSize);
	ofn.nFilterIndex = true;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = NULL;
	ofn.lpstrInitialDir = NULL;
	ofn.lpstrFilter = ("XML Files(*.xml)\0*.xml\0");
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	if (GetOpenFileName(&ofn) == FALSE) return;
	
	char temp[1028];
	strncpy_s(temp, strlen(ofn.lpstrFile) + 1, ofn.lpstrFile, strlen(ofn.lpstrFile));
	
	char* context = NULL;
	char* token = strtok_s(temp, "\\", &context);
	while (strlen(context))
	{
		token = strtok_s(NULL, "\\", &context);
	}


	//기존 타일 삭제
	_vMapTile.clear();
	_vDecoTile.clear();

	//xml 로드
	XMLDocument xmlDoc;

	XMLError eResult = xmlDoc.LoadFile(token);
//	XMLError eResult = xmlDoc.LoadFile("SavedData.xml");

	XMLNode * pRoot = xmlDoc.FirstChild();
	
	XMLElement * pTileElement = pRoot->FirstChildElement("TileList");
	XMLElement * pTileListElement = pTileElement->FirstChildElement("tile");

	while (pTileListElement != nullptr) {
		TILE tile;

		//tile.img = IMAGEMANAGER->findImage("mapTiles"); //임시, 나중에 주소값으로 바꿀거
		int imgNum = pTileListElement->FirstChildElement("imgNum")->IntText();
		tile.img = IMAGEMANAGER->findImage(_imgNameList[imgNum]);

		tile.destX = pTileListElement->FirstChildElement("destX")->IntText();
		tile.destY = pTileListElement->FirstChildElement("destY")->IntText();
		tile.sourX = pTileListElement->FirstChildElement("sourX")->IntText();
		tile.sourY = pTileListElement->FirstChildElement("sourY")->IntText();
		tile.obj	= (OBJ)pTileListElement->FirstChildElement("obj")->IntText();
		tile.terrain = (TERRAIN)pTileListElement->FirstChildElement("terrain")->IntText();

		_vMapTile.push_back(tile);

		pTileListElement = pTileListElement->NextSiblingElement("tile");
	}
	


	XMLElement * pDecoElement = pRoot->FirstChildElement("DecoList");
	XMLElement * pDecoListElement = pDecoElement->FirstChildElement("tile");

	while (pDecoListElement != nullptr) {
		TILE tile;

		int imgNum = pDecoListElement->FirstChildElement("imgNum")->IntText();
		tile.img = IMAGEMANAGER->findImage(_imgNameList[imgNum]);

		tile.destX = pDecoListElement->FirstChildElement("destX")->IntText();
		tile.destY = pDecoListElement->FirstChildElement("destY")->IntText();
		tile.sourX = pDecoListElement->FirstChildElement("sourX")->IntText();
		tile.sourY = pDecoListElement->FirstChildElement("sourY")->IntText();
		tile.obj = (OBJ)pDecoListElement->FirstChildElement("obj")->IntText();
		tile.terrain = (TERRAIN)pDecoListElement->FirstChildElement("terrain")->IntText();

		_vDecoTile.push_back(tile);

		pDecoListElement = pDecoListElement->NextSiblingElement("tile");
	}

	XMLElement * pObjElement = pRoot->FirstChildElement("ObjList");
	XMLElement * pObjListElement = pObjElement->FirstChildElement("obj");

	while (pObjListElement != nullptr) {
		GAMEOBJECT obj;

		int imgNum = pObjListElement->FirstChildElement("imgNum")->IntText();
		obj.img = IMAGEMANAGER->findImage(_imgNameList[imgNum]);

		obj.destX = pObjListElement->FirstChildElement("destX")->IntText();
		obj.destY = pObjListElement->FirstChildElement("destY")->IntText();
		obj.sourX = pObjListElement->FirstChildElement("sourX")->IntText();
		obj.sourY = pObjListElement->FirstChildElement("sourY")->IntText();
		obj.obj = (OBJ)pObjListElement->FirstChildElement("obj")->IntText();
		
		_vObj.push_back(obj);

		pObjListElement = pObjListElement->NextSiblingElement("obj");
	}
	

	XMLElement * pMonElement = pRoot->FirstChildElement("MonsterList");
	XMLElement * pMonListElement = pMonElement->FirstChildElement("monster");

	while (pMonListElement != nullptr) {
		
		string name = pMonListElement->FirstChildElement("name")->GetText();
		int destX = pMonListElement->FirstChildElement("destX")->IntText();
		int destY = pMonListElement->FirstChildElement("destY")->IntText();

		TILE inputTile;
		ZeroMemory(&inputTile, sizeof(TILE));
		inputTile.img = IMAGEMANAGER->findImage(name);
		inputTile.destX = destX;
		inputTile.destY = destY;

		_vMon.push_back(inputTile);

		pMonListElement = pMonListElement->NextSiblingElement("monster");
	}

	//임시로 만들었던거

	/*
	HANDLE file;
	DWORD read;

	file = CreateFile("mapSave.map", GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, loadMap, sizeof(SAVETILE) * 10000, &read, NULL);

	_vMapTile.clear();

	for (int i = 0; i < 10000; i++) {
		if (loadMap[i].terrain == TERRAIN_NULL) break;
		TILE tile;

		tile.img = IMAGEMANAGER->findImage("mapTiles");

		tile.destX = loadMap[i].destX;
		tile.destY = loadMap[i].destY;
		tile.sourX = loadMap[i].sourX;
		tile.sourY = loadMap[i].sourY;
		tile.index = loadMap[i].index;
		tile.obj = loadMap[i].obj;
		tile.terrain = loadMap[i].terrain;

		_vMapTile.push_back(tile);
	}*/

	
	//CloseHandle(file);
}


void MapToolScene::cameraMove(int x, int y) {

	_cameraX += x;
	_cameraY += y;
	
}
