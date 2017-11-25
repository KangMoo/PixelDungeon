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
	_viewMode = VIEW_ONE;


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

void MapToolScene::imageSetup() {
	
	_imgNameList.push_back("mapTiles");

	
	for (int i = 0; i < _imgNameList.size(); i++) {
		image* image1 = IMAGEMANAGER->findImage(_imgNameList[i]);
		_imgList.push_back(image1);		
	}
}

void MapToolScene::paletteSetup()
{
	int index = 0;

	for (auto img : _imgList) {
		for (int i = 0; i < img->getMaxFrameY(); i++) {
			for (int j = 0; j < img->getMaxFrameX(); j++) {
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
}


void MapToolScene::update()	
{
	
	buttonInput();
}



void MapToolScene::buttonInput()
{
	
	if (KEYMANAGER->isOnceKeyDown('1')) _inputMode = MODE_FLOOR;
	if (KEYMANAGER->isOnceKeyDown('2')) _inputMode = MODE_WALL;
	if (KEYMANAGER->isOnceKeyDown('3')) _inputMode = MODE_GRASS;
	if (KEYMANAGER->isOnceKeyDown('4')) _inputMode = MODE_DOOR;
	if (KEYMANAGER->isOnceKeyDown('5')) _inputMode = MODE_DECO;
	if (KEYMANAGER->isOnceKeyDown('6')) _inputMode = MODE_VIEWING;
	if (KEYMANAGER->isOnceKeyDown('7')) _inputMode = MODE_DELET;
	

	if (KEYMANAGER->isOnceKeyDown(VK_DELETE)) {
		if (!_mapSelected.empty()) {
			for (int i = 0; i < _mapSelected.size(); i++) {
				int indexX = i % GRIDX + _cameraX;
				int indexY = i / GRIDX + _cameraY;
				for (_viMapTile = _vMapTile.begin(); _viMapTile != _vMapTile.end();) {
					if (_viMapTile->destX == indexX && _viMapTile->destY == indexY) {
						_viMapTile = _vMapTile.erase(_viMapTile);
						break;
					}
					else _viMapTile++;
				}
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
			else if (KEYMANAGER->isStayKeyDown(VK_RBUTTON)) {
				_mapSelected.push_back(_mapRect[i]);
				break;
			}

			if (!_paletSelected.empty()) {

				if (_inputMode == MODE_VIEWING) return; //읽기 모드   : 아무것도 못한다
				
				if (_inputMode == MODE_DELET) {			//지우기 모드 : 이미 있는 경우를 확인, 지운다.
					if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
						int indexX = i % GRIDX + _cameraX;
						int indexY = i / GRIDX + _cameraY;
						for (_viMapTile = _vMapTile.begin(); _viMapTile != _vMapTile.end();) {
							if (_viMapTile->destX == indexX && _viMapTile->destY == indexY) {
								_viMapTile = _vMapTile.erase(_viMapTile);
								return;
							}
							else
								_viMapTile++;
						}
					}
					return;
				}


				_showTile = true;					// 현재 선택한 타일을 보여주기
				_showTileIndex = i;

					

				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) || KEYMANAGER->isStayKeyDown(VK_LBUTTON)) {
					int indexX = i % GRIDX + _cameraX;
					int indexY = i / GRIDX + _cameraY;
					int paletIndex = _paletSelected[0].index;

					//팔레트 사이즈보다 큰걸 선택했으면 입력 못한다
					if (paletIndex > _vPaletTile.size()) return;


					// 이미지 추가 모드
					if (_inputMode == MODE_DECO) {

						//이미 타일이 있는 경우 지운다
						for (_viDecoTile = _vDecoTile.begin(); _viDecoTile != _vDecoTile.end();) {
							if (_viDecoTile->destX == indexX && _viDecoTile->destY == indexY) {
								_viDecoTile = _vDecoTile.erase(_viDecoTile);
							}
							else
								_viDecoTile++;
						}

						TILE inputTile;
						ZeroMemory(&inputTile, sizeof(TILE));
						inputTile.img = _vPaletTile[paletIndex].img;
						inputTile.sourX = _vPaletTile[paletIndex].sourX;
						inputTile.sourY = _vPaletTile[paletIndex].sourY;
						inputTile.destX = indexX;
						inputTile.destY = indexY;

						inputTile.terrain = TERRAIN_NULL;

						_vDecoTile.push_back(inputTile);
					}


					// 타일 추가 모드
					else {
						//이미 타일이 있는 경우 지운다
						for (_viMapTile = _vMapTile.begin(); _viMapTile != _vMapTile.end();) {
							if (_viMapTile->destX == indexX && _viMapTile->destY == indexY) {
								_viMapTile = _vMapTile.erase(_viMapTile);
							}
							else
								_viMapTile++;
						}

						TILE inputTile;
						ZeroMemory(&inputTile, sizeof(TILE));
						inputTile.img = _vPaletTile[paletIndex].img;
						inputTile.sourX = _vPaletTile[paletIndex].sourX;
						inputTile.sourY = _vPaletTile[paletIndex].sourY;
						inputTile.destX = indexX;
						inputTile.destY = indexY;

						if (_inputMode == MODE_FLOOR) inputTile.terrain = TERRAIN_FLOOR;		//모드에 따라 속성을 다르게 부여
						if (_inputMode == MODE_WALL) inputTile.terrain = TERRAIN_WALL;
						if (_inputMode == MODE_GRASS) inputTile.terrain = TERRAIN_GRASS;
						if (_inputMode == MODE_DOOR) inputTile.terrain = TERRAIN_DOOR_CLOSED;

						_vMapTile.push_back(inputTile);
					}
				}
				//_mapSelected.clear();
				//_mapSelected.push_back(_mapRect[i]);
				break;
			}
		}
		else _showTile = false;		// 현재 선택한 타일을 보여주지 않음
	}



	for (int i = 0; i < PALETTENUM; i++) {
		if (PtInRect(&_paletRect[i].rc, _ptMouse)) {
			if (KEYMANAGER->isStayKeyDown(VK_LCONTROL) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
				S_TILE selectTile;

				int paletIndex = _paletRect[i].index + _paletPage * PALETTENUM;

				selectTile.img = _vPaletTile[paletIndex].img; // 팔레트는 이미지 하나만 갖고 있다
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

	for (int i = 0; i < _vMapTile.size(); i++) {
		if (_vMapTile[i].destX - _cameraX < 0 || _vMapTile[i].destY - _cameraY < 0 ||
			_vMapTile[i].destX - _cameraX >= GRIDX || _vMapTile[i].destY - _cameraY >= GRIDY) continue;
		
		int index = _vMapTile[i].destX - _cameraX + (_vMapTile[i].destY - _cameraY) * GRIDX;

		int destX = _mapRect[index].rc.left;
		int destY = _mapRect[index].rc.top;

		int alpha;
		if (_vMapTile[i].terrain == TERRAIN_FLOOR			 && _inputMode == MODE_FLOOR) alpha = 0;
		else if (_vMapTile[i].terrain == TERRAIN_WALL		 && _inputMode == MODE_WALL)  alpha = 0;
		else if (_vMapTile[i].terrain == TERRAIN_GRASS		 && _inputMode == MODE_GRASS)  alpha = 0;
		else if (_vMapTile[i].terrain == TERRAIN_DOOR_CLOSED && _inputMode == MODE_DOOR)  alpha = 0;
		else if (_inputMode == MODE_VIEWING)  alpha = 0;
		else alpha = 100;

		_vMapTile[i].img->alphaFrameRender(getMemDC(), destX, destY, _vMapTile[i].sourX, _vMapTile[i].sourY, alpha);
		
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
		if (_inputMode == MODE_DECO || _inputMode == MODE_VIEWING) alpha = 0; else alpha = 255;

		_vDecoTile[i].img->alphaFrameRender(getMemDC(), destX, destY, _vDecoTile[i].sourX, _vDecoTile[i].sourY, alpha);
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
	
	switch (_inputMode) {
	case MODE_FLOOR:
		TextOut(getMemDC(), _buttonRect[5].rc.right, _buttonRect[5].rc.top + 20, "FLOOR", strlen("FLOOR"));
		break;
	case MODE_WALL:
		TextOut(getMemDC(), _buttonRect[5].rc.right, _buttonRect[5].rc.top + 20, "WALL", strlen("WALL"));
		break;
	case MODE_GRASS:
		TextOut(getMemDC(), _buttonRect[5].rc.right, _buttonRect[5].rc.top + 20, "GRASS", strlen("GRASS"));
		break;
	case MODE_DOOR:
		TextOut(getMemDC(), _buttonRect[5].rc.right, _buttonRect[5].rc.top + 20, "DOOR", strlen("DOOR"));
		break;
	case MODE_VIEWING:
		TextOut(getMemDC(), _buttonRect[5].rc.right, _buttonRect[5].rc.top + 20, "VIEWING", strlen("VIEWING"));
		break;
	case MODE_DELET:
		TextOut(getMemDC(), _buttonRect[5].rc.right, _buttonRect[5].rc.top + 20, "DELET", strlen("DELET"));
		break;
	}
	
	//~test
}

void MapToolScene::save()
{
	//xml 저장
	XMLDocument xmlDoc;
	XMLNode *pRoot;

	pRoot = xmlDoc.NewElement("map");
	xmlDoc.InsertFirstChild(pRoot);

	XMLElement * pMapElement_Tile = xmlDoc.NewElement("TileList");

	XMLElement * pTileElementSize = xmlDoc.NewElement("size");
	pTileElementSize->SetText(_vMapTile.size());
	pMapElement_Tile->InsertEndChild(pTileElementSize);

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

		pListElementT->InsertEndChild(pListElement1);
		pListElementT->InsertEndChild(pListElement2);
		pListElementT->InsertEndChild(pListElement3);
		pListElementT->InsertEndChild(pListElement4);
		pListElementT->InsertEndChild(pListElement5);
		pListElementT->InsertEndChild(pListElement6);

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

		pListElementT->InsertEndChild(pListElement1);
		pListElementT->InsertEndChild(pListElement2);
		pListElementT->InsertEndChild(pListElement3);
		pListElementT->InsertEndChild(pListElement4);
		pListElementT->InsertEndChild(pListElement5);
		pListElementT->InsertEndChild(pListElement6);

		pMapElement_Deco->InsertEndChild(pListElementT);
	}
	pRoot->InsertEndChild(pMapElement_Deco);



	XMLError eResult = xmlDoc.SaveFile("SavedData.xml");



/*
	WriteFile(file, &saveMap, sizeof(SAVETILE) * size, &write, NULL);

	CloseHandle(file);

	delete[] saveMap;*/

}

void MapToolScene::load()
{

	//기존 타일 삭제
	_vMapTile.clear();


	//xml 로드
	XMLDocument xmlDoc;

	XMLError eResult = xmlDoc.LoadFile("SavedData.xml");
	
	XMLNode * pRoot = xmlDoc.FirstChild();
	
	XMLElement * pTileElement = pRoot->FirstChildElement("TileList");
	XMLElement * pTileListElement = pTileElement->FirstChildElement("tile");

	while (pTileListElement != nullptr) {
		TILE tile;

		tile.img = IMAGEMANAGER->findImage("mapTiles"); //임시, 나중에 주소값으로 바꿀거


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

		tile.img = IMAGEMANAGER->findImage("mapTiles"); //임시, 나중에 주소값으로 바꿀거
		
		tile.destX = pDecoListElement->FirstChildElement("destX")->IntText();
		tile.destY = pDecoListElement->FirstChildElement("destY")->IntText();
		tile.sourX = pDecoListElement->FirstChildElement("sourX")->IntText();
		tile.sourY = pDecoListElement->FirstChildElement("sourY")->IntText();
		tile.obj = (OBJ)pDecoListElement->FirstChildElement("obj")->IntText();
		tile.terrain = (TERRAIN)pDecoListElement->FirstChildElement("terrain")->IntText();

		_vDecoTile.push_back(tile);

		pDecoListElement = pDecoListElement->NextSiblingElement("tile");
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
