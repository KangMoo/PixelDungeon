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


	_paletteImg = IMAGEMANAGER->addFrameImage("mapTiles", "Img/Map/tiles_sewers.bmp", 0, 0, 512, 512, 16, 16, true, RGB(255, 0, 255));

	//카메라
	_cameraX = _cameraY = 0;

	//맵 rect
	for (int i = 0; i < GRIDNUM; i++) {
		int x = (i % GRIDX + 1) * TILESIZE;
		int y = (i / GRIDX + 1) * TILESIZE;
		_mapRect[i].x = x;
		_mapRect[i].y = y;
		_mapRect[i].index = i;
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


	paletteSetup();
	return S_OK;
}
void MapToolScene::release()
{

}

void MapToolScene::paletteSetup()
{
	for (int i = 0; i < _paletteImg->getMaxFrameY();  i++) {
		for (int j = 0; j < _paletteImg->getMaxFrameX(); j++) {
			TILE palTile;
			ZeroMemory(&palTile, sizeof(TILE));
			palTile.img = _paletteImg;
			palTile.sourX = j;
			palTile.sourY = i;

			palTile.index = (j + i * _paletteImg->getMaxFrameX());
			
			palTile.destX = palTile.index % PALETTEX;
			palTile.destY = palTile.index / PALETTEX;

			_vPaletTile.push_back(palTile);
		}		
	}
}


void MapToolScene::update()	
{
	
	buttonInput();
}



void MapToolScene::buttonInput()
{
	


	if (KEYMANAGER->isOnceKeyDown(VK_DELETE)) {
		if (!_mapSelected.empty()) {
			for (_viMapTile = _vMapTile.begin(); _viMapTile != _vMapTile.end();) {
				if (_viMapTile->index == _mapSelected[0].index + _cameraX + (_cameraY * GRIDX)) {
					_viMapTile = _vMapTile.erase(_viMapTile);
					break;						
				}
				else _viMapTile++;

			}
		}
	}

	if (KEYMANAGER->isStayKeyDown(VK_LCONTROL) && KEYMANAGER->isOnceKeyDown('S')) {
		save();
	}
	if (KEYMANAGER->isStayKeyDown(VK_LCONTROL) && KEYMANAGER->isOnceKeyDown('O')) {
		load();
	}


	for (int i = 0; i < GRIDNUM; i++) {
		if (PtInRect(&_mapRect[i].rc, _ptMouse)) {

			//	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON) && _mapSelected.size != 0) {
			//		if (_sele 
			//	}

			if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON)) {
				_mapSelected.clear();
				_mapSelected.push_back(_mapRect[i]);
				break;
			}

			if (!_paletSelected.empty()) {

				_showTile = true;
				_showTileIndex = i;

					

				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) || KEYMANAGER->isStayKeyDown(VK_LBUTTON)) {
					int newMapIndex = i + _cameraX + (_cameraY * GRIDX);
					int paletIndex = _paletSelected[0].index;

					if (paletIndex > _vPaletTile.size()) return;

					//이미 있는 경우를 확인, 지운다.
					for (_viMapTile = _vMapTile.begin(); _viMapTile != _vMapTile.end();) {
						if (_viMapTile->index == newMapIndex) {
							_viMapTile = _vMapTile.erase(_viMapTile);
							break;
						}
						else
							_viMapTile++;
					}

					TILE inputTile;
					ZeroMemory(&inputTile, sizeof(TILE));
					inputTile.img = _vPaletTile[paletIndex].img;
					inputTile.sourX = _vPaletTile[paletIndex].sourX;
					inputTile.sourY = _vPaletTile[paletIndex].sourY;



					inputTile.destX = i % GRIDX + _cameraX;
					inputTile.destY = i / GRIDX + _cameraY;

					inputTile.index = newMapIndex;

					_vMapTile.push_back(inputTile);
				}
				//_mapSelected.clear();
				//_mapSelected.push_back(_mapRect[i]);
				break;
			}
		}
		else _showTile = false;		
	}



	for (int i = 0; i < PALETTENUM; i++) {
		if (PtInRect(&_paletRect[i].rc, _ptMouse)) {
			if (KEYMANAGER->isStayKeyDown(VK_LCONTROL) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
				S_TILE selectTile;

				int paletIndex = _paletRect[i].index + _paletPage * PALETTENUM;

				selectTile.img = _vPaletTile[paletIndex].img;
				selectTile.index = paletIndex;
				selectTile.rc = _paletRect[i].rc;

				_paletSelected.clear();
				_paletSelected.push_back(selectTile);
				break;
			}

			else if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
				S_TILE selectTile;

				int paletIndex = _paletRect[i].index + _paletPage * PALETTENUM;

				selectTile.img = _vPaletTile[paletIndex].img;
				selectTile.index = paletIndex;
				selectTile.rc = _paletRect[i].rc;

				_paletSelected.clear();
				_paletSelected.push_back(selectTile);
				break;
			}

		}
	}

	for (int i = 0; i < BUTTONNUM; i++) {
		if (PtInRect(&_buttonRect[i].rc, _ptMouse))
		{
			if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))  _buttonRect[i].isClicked = true;

			if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON) && _buttonRect[i].isClicked) {
				switch (i) {
				case 0:
					SCENEMANAGER->changeScene("메인메뉴씬");
				break;
				case 1:

					if (_cameraY > 0) _cameraY--;
				break;

				case 2:
					_cameraY++;
				break;
				case 3:
					if (_cameraX > 0) _cameraX--;
				break;
				case 4:
					_cameraX++;
				break;

				case 5:
					if (_paletPage > 0) {
						_paletPage--;
						_paletSelected.clear();
						_showTile = false;
					}
					break;
				case 6:
					_paletPage++;
					_paletSelected.clear();
					_showTile = false;
					break;
				}
				_buttonRect[i].isClicked = false;
			}
		}
		else if (_buttonRect[i].isClicked) _buttonRect[i].isClicked = false;	
	}
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
	sprintf(str, "CAMERA x : %d y : %d    %d", _cameraX, _cameraY, _vMapTile.size());
	TextOut(getMemDC(), 10, 10, str, strlen(str));
	//test

	for (int i = 0; i < PALETTENUM; i++) {

		int tileIndex = i + _paletPage * PALETTENUM;
		if (tileIndex >= _vPaletTile.size()) break;

		int rectIndex = _vPaletTile[tileIndex].destX + (_vPaletTile[tileIndex].destY - _paletPage * PALETTEY) * PALETTEX;

		int destX = _paletRect[rectIndex].rc.left;
		int destY = _paletRect[rectIndex].rc.top;

		_vPaletTile[i].img->frameRender(getMemDC(), destX, destY, _vPaletTile[tileIndex].sourX, _vPaletTile[tileIndex].sourY);
	}

	for (int i = 0; i < GRIDNUM; i++) {
		if (i >= _vMapTile.size()) break;
		if (_vMapTile[i].destX - _cameraX < 0 || _vMapTile[i].destY - _cameraY < 0) continue;
		
		int index = _vMapTile[i].destX - _cameraX + (_vMapTile[i].destY - _cameraY) * GRIDX;

		int destX = _mapRect[index].rc.left;
		int destY = _mapRect[index].rc.top;

		_vMapTile[i].img->frameRender(getMemDC(), destX, destY, _vMapTile[i].sourX, _vMapTile[i].sourY);
	}


	if (_showTile) {
		_paletSelected[0].img->alphaFrameRender(getMemDC(), _mapRect[_showTileIndex].rc.left, _mapRect[_showTileIndex].rc.top, _vPaletTile[_paletSelected[0].index].sourX, _vPaletTile[_paletSelected[0].index].sourY, 150);
	}


	//선택 내용 색칠 등
	HBRUSH myBrush, oldBrush;
	myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);

	HPEN hPen, oPen;
	hPen = CreatePen(PS_SOLID, 4, RGB(255, 0, 255));
	for (auto select : _mapSelected) {
		oPen = (HPEN)SelectObject(getMemDC(), hPen);
		oldBrush = (HBRUSH)SelectObject(getMemDC(), myBrush);
		Rectangle(getMemDC(), select.rc.left, select.rc.top, select.rc.right + 1, select.rc.bottom + 1);
		SelectObject(getMemDC(), oPen);
		HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), myBrush);
		SelectObject(getMemDC(), oldBrush);
	}
	DeleteObject(hPen);


	for (auto select : _paletSelected) {
		HPEN hPen2, oPen2;
		hPen2 = CreatePen(PS_SOLID, 4, RGB(255, 0, 255));
		oPen2 = (HPEN)SelectObject(getMemDC(), hPen2);
		oldBrush = (HBRUSH)SelectObject(getMemDC(), myBrush);
		Rectangle(getMemDC(), select.rc.left, select.rc.top, select.rc.right + 1, select.rc.bottom + 1);
		SelectObject(getMemDC(), oPen2);
		SelectObject(getMemDC(), oldBrush);
		DeleteObject(hPen2);
	}
	DeleteObject(myBrush);

	HBRUSH btBrush, obtBrush;
	for (int i = 0; i < BUTTONNUM; i++) {
		if (_buttonRect[i].isClicked) {
			btBrush = (HBRUSH)CreateSolidBrush(RGB(100, 100, 100));
			obtBrush = (HBRUSH)SelectObject(getMemDC(), btBrush);
			Rectangle(getMemDC(), _buttonRect[i].rc.left, _buttonRect[i].rc.top, _buttonRect[i].rc.right, _buttonRect[i].rc.bottom);
		}
		else {
			btBrush = (HBRUSH)CreateSolidBrush(RGB(255, 255, 255));
			obtBrush = (HBRUSH)SelectObject(getMemDC(), btBrush);
			Rectangle(getMemDC(), _buttonRect[i].rc.left, _buttonRect[i].rc.top, _buttonRect[i].rc.right, _buttonRect[i].rc.bottom);
		}
	}
	DeleteObject(btBrush);

	//test~
	TextOut(getMemDC(), WINSIZEX - 50, 5, "맵툴씬", strlen("맵툴씬"));
	TextOut(getMemDC(), WINSIZEX - 70, WINSIZEY - 25, "돌아가기", strlen("돌아가기"));

	TextOut(getMemDC(), _buttonRect[5].rc.left + 2, _buttonRect[5].rc.top + 2,  "prev", strlen("prev"));
	TextOut(getMemDC(), _buttonRect[6].rc.left + 2, _buttonRect[6].rc.top + 2, "next", strlen("next"));

	char page[128];
	sprintf(page, "page : %d", _paletPage);
	TextOut(getMemDC(), _buttonRect[5].rc.right, _buttonRect[5].rc.top + 2, page, strlen(page));
	//~test
}

void MapToolScene::save()
{
	//임시로 만듬. 나중에 바꿔야지...

	const int size = _vMapTile.size();

	for (int i = 0; i < 10000; i++) {
		//saveMap[i].imgName = "mapTiles";
		if (i < _vMapTile.size()) {
			saveMap[i].destX = _vMapTile[i].destX;
			saveMap[i].destY = _vMapTile[i].destY;
			saveMap[i].sourX = _vMapTile[i].sourX;
			saveMap[i].sourY = _vMapTile[i].sourY;
			saveMap[i].index = _vMapTile[i].index;
			saveMap[i].obj = OBJ_NONE;
			saveMap[i].terrain = TERRAIN_FLOOR;
		}
		else {
			saveMap[i].destX = 0;
			saveMap[i].destY = 0;
			saveMap[i].sourX = 0;
			saveMap[i].sourY = 0;
			saveMap[i].index = 0;
			saveMap[i].obj = OBJ_NONE;
			saveMap[i].terrain = TERRAIN_NULL;
		}
	}


	HANDLE file;
	DWORD write;

	file = CreateFile("mapSave.map", GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, saveMap, sizeof(SAVETILE) * 10000, &write, NULL);

	CloseHandle(file);


}

void MapToolScene::load()
{
	//임시로 만듬. 나중에 바꿔야지...

	
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
	}

	CloseHandle(file);
}
