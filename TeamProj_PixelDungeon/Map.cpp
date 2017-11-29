#include "stdafx.h"
#include "Map.h"
#include "EnemyManager.h"
#include "ItemManager.h"
#include "Player.h"
#include "UI.h"

Map::Map()
{
}


Map::~Map()
{
}
HRESULT Map::init()
{
	_mapSizeX = 0;
	_mapSizeY = 0;
	imageSetup();
	spareTileSetup();

	_stageDataList.push_back("SavedData.xml");
	_stageDataList.push_back("SavedData2.xml");


	_curStageNum = 0;
	start = true;
	load(_curStageNum);



	IMAGEMANAGER->addImage("blackLineVertical", "Img//Map//blackdot.bmp", 1, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("blackLineHorizontal", "Img//Map//blackdot.bmp", 32, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("blackTile", "Img//Map//blackdot.bmp", 32, 32, true, RGB(255, 0, 255));
	return S_OK;
}


void Map::imageSetup() {

	_imgNameList.push_back("mapTiles");
	_imgNameList.push_back("chest");

	for (int i = 0; i < _imgNameList.size(); i++) {
		image* image1 = IMAGEMANAGER->findImage(_imgNameList[i]);
		_imgList.push_back(image1);
	}
}


void Map::release()
{
}
void Map::update()
{

	//test
	for (int i = 0; i < _vObj.size(); i++) {
		if (_player->getPoint().x / TILESIZE == _vObj[i].destX && _player->getPoint().y / TILESIZE == _vObj[i].destY) {
			if (_vObj[i].obj == OBJ_STAIR_END) {
				if (_curStageNum == 0)
				{
					load(1);
				}
				else if (_curStageNum == 1)
					load(0);
			}
			if (_vObj[i].obj == OBJ_CHEST) {
				setObj_OpenChest(i);
			}
		}
	}

	// 타일 상태변화 test
	if (KEYMANAGER->isOnceKeyDown('A')) {
		for (int i = 0; i < TILEXMAX; i++) {
			for (int j = 0; j < TILEYMAX; j++)
			{
				if ((_map[i][j].terrain & ATTRIBUTE_FLAMMABLE) == ATTRIBUTE_FLAMMABLE)
				{
					setTile_Flame(i, j);
				}
			}
		}
	}

	if (KEYMANAGER->isOnceKeyDown('S')) {
		for (int i = 0; i < TILEXMAX; i++) {
			for (int j = 0; j < TILEYMAX; j++)
			{
				if ((_map[i][j].terrain & ATTRIBUTE_GRASS) == ATTRIBUTE_GRASS &&
					(_map[i][j].terrain & ATTRIBUTE_UNSIGHT) == ATTRIBUTE_UNSIGHT)
				{
					setTile_GrassCut(i, j);
				}
			}
		}
	}
	if (KEYMANAGER->isOnceKeyDown('D')) {
		for (int i = 0; i < _vObj.size(); i++) {
			if ((_vObj[i].obj & ATTRIBUTE_CHEST) == ATTRIBUTE_CHEST)
			{
				setObj_OpenChest(i);
			}
		}
	}

	if (KEYMANAGER->isOnceKeyDown('Q')) {
		if (_curStageNum == 0) { load(1); }
		else { load(0); }
	}
	// test
	_camera = _ui->getCamera();
}
void Map::render()
{
}

//그릴 때	x좌표에 camera.x 만큼
//			y좌표에 camera.y 만큼 더해주기!!!!
void Map::render(POINT camera)
{
	draw(camera);
}
void Map::draw(POINT camera)
{
	int temp = 7;
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) temp++;
	if (KEYMANAGER->isStayKeyDown(VK_LEFT)) temp--;
	for (int i = 0; i < TILEXMAX; i++) {

		for (int j = 0; j < TILEYMAX; j++) {
			if (_map[i][j].terrain != TERRAIN_NULL) {
				_map[i][j].img->frameRender(getMemDC(), i * TILESIZE + camera.x, j * TILESIZE + camera.y, _map[i][j].sourX, _map[i][j].sourY);
				drawTileShadow(_map[i][j]);
			}
			//RectangleMake(getMemDC(), i * 10, j * 10, 10, 10);				

		}
	}

	for (_viObj = _vObj.begin(); _viObj != _vObj.end(); ++_viObj)
	{
		if (_viObj->obj != OBJ_NONE) {
			if (_map[_viObj->destX][_viObj->destY].tileview == TILEVIEW_ALL)
				_viObj->img->frameRender(getMemDC(), _viObj->destX * TILESIZE + camera.x, _viObj->destY * TILESIZE + camera.y, _viObj->sourX, _viObj->sourY);
		}

	}
}


void Map::load(int stageNum) {

	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			_map[i][j].terrain = TERRAIN_NULL;
			_map[i][j].tileview = TILEVIEW_NO;
		}
	}

	//TILE loadMap[10000];
	////임시로 만듬. 나중에 바꿔야지...
	//
	//HANDLE file;
	//DWORD read;

	//file = CreateFile("mapSave.map", GENERIC_READ, 0, NULL,
	//	OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	//ReadFile(file, loadMap, sizeof(SAVETILE) * 10000, &read, NULL);

	////for (int i = 0; i < 10000; i++) {
	////	_mapTest[i].sourX = loadMap[i].sourX;
	////	_mapTest[i].sourY = loadMap[i].sourY;
	////	
	////}


	///////**/
	//
	//HANDLE file;
	//DWORD read;
	//file = CreateFile("mapSave.map", GENERIC_READ, 0, NULL,
	//	OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	//ReadFile(file, loadMap, sizeof(SAVETILE) * 10000, &read, NULL);

	//_vMapTile.clear();

	//for (int i = 0; i < 10000; i++) {
	//	TILE tile;

	//	tile.img = IMAGEMANAGER->findImage("mapTiles");

	//	tile.destX = loadMap[i].destX;
	//	tile.destY = loadMap[i].destY;
	//	tile.sourX = loadMap[i].sourX;
	//	tile.sourY = loadMap[i].sourY;
	//	tile.index = loadMap[i].index;
	//	tile.obj = loadMap[i].obj;
	//	tile.terrain = loadMap[i].terrain;

	//	_vMapTile.push_back(tile);

	//}


	_vMapTile.clear();
	_vDecoTile.clear();
	_vObj.clear();

	const char *name = _stageDataList[stageNum].c_str();

	XMLDocument xmlDoc;

	XMLError eResult = xmlDoc.LoadFile(name);

	XMLNode * pRoot = xmlDoc.FirstChild();

	XMLElement * pTileElement = pRoot->FirstChildElement("TileList");

	_mapSizeX = pTileElement->FirstChildElement("sizeX")->IntText();
	_mapSizeY = pTileElement->FirstChildElement("sizeY")->IntText();

	XMLElement * pTileListElement = pTileElement->FirstChildElement("tile");


	while (pTileListElement != nullptr) {
		TILE tile;

		int imgNum = pTileListElement->FirstChildElement("imgNum")->IntText();
		tile.img = IMAGEMANAGER->findImage(_imgNameList[imgNum]);


		tile.destX = pTileListElement->FirstChildElement("destX")->IntText();
		tile.destY = pTileListElement->FirstChildElement("destY")->IntText();
		tile.sourX = pTileListElement->FirstChildElement("sourX")->IntText();
		tile.sourY = pTileListElement->FirstChildElement("sourY")->IntText();
		tile.obj = (OBJ)pTileListElement->FirstChildElement("obj")->IntText();
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

		if (obj.obj == OBJ_STAIR_START) {
			POINT playerPoint = PointMake(obj.destX*TILESIZE + TILESIZE / 2, obj.destY*TILESIZE + TILESIZE / 2);
			_player->setPoint(playerPoint);
		}

	}

	//XMLElement * pDecoElement = pRoot->FirstChildElement("DecoList");
	//XMLElement * pDecoListElement = pDecoElement->FirstChildElement("tile");
	//
	//while (pDecoListElement != nullptr) {
	//	TILE tile;
	//
	//	tile.img = IMAGEMANAGER->findImage("mapTiles"); //임시, 나중에 주소값으로 바꿀거
	//
	//	tile.destX = pDecoListElement->FirstChildElement("destX")->IntText();
	//	tile.destY = pDecoListElement->FirstChildElement("destY")->IntText();
	//	tile.sourX = pDecoListElement->FirstChildElement("sourX")->IntText();
	//	tile.sourY = pDecoListElement->FirstChildElement("sourY")->IntText();
	//	tile.obj = (OBJ)pDecoListElement->FirstChildElement("obj")->IntText();
	//	tile.terrain = (TERRAIN)pDecoListElement->FirstChildElement("terrain")->IntText();
	//
	//	_vDecoTile.push_back(tile);
	//
	//	pDecoListElement = pDecoListElement->NextSiblingElement("tile");
	//}



	for (int i = 0; i < 10000; i++) {
		if (i >= _vMapTile.size()) break;

		_map[_vMapTile[i].destX][_vMapTile[i].destY].img = IMAGEMANAGER->findImage("mapTiles");

		_map[_vMapTile[i].destX][_vMapTile[i].destY].destX = _vMapTile[i].destX;
		_map[_vMapTile[i].destX][_vMapTile[i].destY].destY = _vMapTile[i].destY;
		_map[_vMapTile[i].destX][_vMapTile[i].destY].sourX = _vMapTile[i].sourX;
		_map[_vMapTile[i].destX][_vMapTile[i].destY].sourY = _vMapTile[i].sourY;
		_map[_vMapTile[i].destX][_vMapTile[i].destY].obj = _vMapTile[i].obj;
		_map[_vMapTile[i].destX][_vMapTile[i].destY].terrain = _vMapTile[i].terrain;
		_map[_vMapTile[i].destX][_vMapTile[i].destY].tileview = TILEVIEW_NO;
	}



	_curStageNum = stageNum;
	//for (int i = 0; i < _vMapTile.size(); i++) {
	//	_vMapTile.clear();
	//	vector<TILE>().swap(_vMapTile);		//메모리 해제
	//}
}


void Map::spareTileSetup() {
	TILE* flameTile1 = new TILE;
	flameTile1->img = IMAGEMANAGER->findImage("mapTiles");
	flameTile1->destX = 0;
	flameTile1->destY = 0;
	flameTile1->sourX = 3;
	flameTile1->sourY = 0;
	flameTile1->terrain = TERRAIN_FLOOR;
	flameTile1->obj = OBJ_NONE;
	flameTile1->trap = TRAP_NONE;

	_spareTile.insert(make_pair("AfterFlame1", flameTile1));

	TILE* flameTile2 = new TILE;
	flameTile2->img = IMAGEMANAGER->findImage("mapTiles");
	flameTile2->destX = 0;
	flameTile2->destY = 0;
	flameTile2->sourX = 9;
	flameTile2->sourY = 0;
	flameTile2->terrain = TERRAIN_FLOOR;
	flameTile2->obj = OBJ_NONE;
	flameTile2->trap = TRAP_NONE;

	_spareTile.insert(make_pair("AfterFlame2", flameTile2));

	TILE* grassCutTile1 = new TILE;
	grassCutTile1->img = IMAGEMANAGER->findImage("mapTiles");
	grassCutTile1->destX = 0;
	grassCutTile1->destY = 0;
	grassCutTile1->sourX = 2;
	grassCutTile1->sourY = 0;
	grassCutTile1->terrain = TERRAIN_GRASS;
	grassCutTile1->obj = OBJ_NONE;
	grassCutTile1->trap = TRAP_NONE;

	_spareTile.insert(make_pair("AfterGrass1", grassCutTile1));

	TILE* grassCutTile2 = new TILE;
	grassCutTile2->img = IMAGEMANAGER->findImage("mapTiles");
	grassCutTile2->destX = 0;
	grassCutTile2->destY = 0;
	grassCutTile2->sourX = 8;
	grassCutTile2->sourY = 0;
	grassCutTile2->terrain = TERRAIN_GRASS;
	grassCutTile2->obj = OBJ_NONE;
	grassCutTile2->trap = TRAP_NONE;

	_spareTile.insert(make_pair("AfterGrass2", grassCutTile2));
}

void Map::setTile_Flame(int i, int j) {
	int random = RND->getFromIntTo(1, 2);
	TILE* newTile = (random == 1) ? _spareTile.find("AfterFlame1")->second : _spareTile.find("AfterFlame2")->second;

	_map[i][j].sourX = newTile->sourX;
	_map[i][j].sourY = newTile->sourY;
	_map[i][j].terrain = newTile->terrain;
}

void Map::setTile_GrassCut(int i, int j) {
	int random = RND->getFromIntTo(1, 2);
	TILE* newTile = (random == 1) ? _spareTile.find("AfterGrass1")->second : _spareTile.find("AfterGrass2")->second;

	_map[i][j].sourX = newTile->sourX;
	_map[i][j].sourY = newTile->sourY;
	_map[i][j].terrain = (TERRAIN)((long)_map[i][j].terrain ^ ATTRIBUTE_UNSIGHT);

	_im->setItemToField(NAME_DEW, i * TILESIZE + TILESIZE * 0.5, j * TILESIZE + TILESIZE * 0.5);
}


void Map::setObj_OpenChest(int i) {
	_vObj[i].obj = OBJ_NONE;
	_im->setItemToField(NAME_BOTTLE, _vObj[i].destX * TILESIZE + TILESIZE * 0.5, _vObj[i].destY * TILESIZE + TILESIZE * 0.5);
}

void Map::drawTileShadow(TILE tile)
{
	if (tile.tileview == TILEVIEW_HALF)
	{
		IMAGEMANAGER->alphaRender("blackTile", getMemDC(), tile.destX* TILESIZE + _camera.x, tile.destY* TILESIZE + _camera.y, 150);
	}
	else if (tile.tileview == TILEVIEW_NO)
	{
		IMAGEMANAGER->render("blackTile", getMemDC(), tile.destX * TILESIZE + _camera.x, tile.destY* TILESIZE + _camera.y);
	}
}