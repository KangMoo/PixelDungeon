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
	spareObjSetup();

	_stageDataList.push_back("map/SavedData.xml");
	_stageDataList.push_back("map/SavedData2.xml");
	_stageDataList.push_back("map/SavedData7.xml");
	_stageDataList.push_back("map/SavedData6.xml");
	_stageDataList.push_back("map/SavedData8.xml");

	_renderStartX = 0;
	_renderStartY = 0;
	_renderSizeX = (int) WINSIZEX / TILESIZE + 10;
	_renderSizeY = (int) WINSIZEY / TILESIZE + 10;

	_curStageNum = 0;
	start = true;

	for (int i = 0; i < _stageDataList.size(); i++) {
		load(i);
	}

	changeFloor(0, true);

	IMAGEMANAGER->addImage("blackLineVertical", "Img//Map//blackdot.bmp", 1, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("blackLineHorizontal", "Img//Map//blackdot.bmp", 32, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("blackTile", "Img//Map//blackdot.bmp", 32, 32, true, RGB(255, 0, 255));
	
	_aniCount = 0;

	return S_OK;

}


void Map::imageSetup() {

	_imgNameList.push_back("mapTiles");
	_imgNameList.push_back("chest");
	_imgNameList.push_back("water");
	_imgNameList.push_back("trap");

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

	int playerX = _player->getPoint().x / TILESIZE;
	int playerY = _player->getPoint().y / TILESIZE;

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

	if (KEYMANAGER->isOnceKeyDown('Q')) {

		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				if (_map[playerX + i][playerY + j].terrain == TERRAIN_DOOR_LOCKED)
				{
					setTile_UnlockDoor(playerX + i, playerY + j);
				}
				if (_map[playerX + i][playerY + j].terrain == TERRAIN_OBJECT)
				{
					for (int k = 0; k < _vObj.size(); k++) {
						if (_vObj[k].destX == playerX + i && _vObj[k].destY == playerY + j && _vObj[k].obj == OBJ_CHEST)
						{
							setObj_OpenChest(k);
						}
					}
				}
			}
		}
	}


	if (KEYMANAGER->isOnceKeyDown('W')) {

		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				if ((_map[playerX + i][playerY + j].terrain & ATTRIBUTE_HIDDEN) == ATTRIBUTE_HIDDEN)
				{
					setTile_SearchHidden(playerX + i, playerY + j);
				}
			}
		}
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
	

//	뒷배경 검은색
	RECT bg = RectMake(0, 0, WINSIZEX, WINSIZEY);
	HBRUSH b = CreateSolidBrush(RGB(0, 0, 0));
	FillRect(getMemDC(), &bg, b);
	DeleteObject(b);
		
	// 렌더링 범위 설정 (100,100 다 for문 안 돌리기 위해)
	_renderStartX = ((int)(-camera.x / TILESIZE) - 5 > 0) ? (int)(-_camera.x / TILESIZE) - 5 : 0;
	_renderStartY = ((int)(-camera.y / TILESIZE) - 5 > 0) ? (int)(-_camera.y / TILESIZE) - 5 : 0;


	_aniCount += 1;
	if (_aniCount > 1000) { _aniCount = 0; }

	// 타일 그리기
	for (int i = _renderStartX; i < _renderStartX + _renderSizeX; i++) {
		for (int j = _renderStartY; j < _renderStartY + _renderSizeY; j++) {
			if (_map[i][j].terrain != TERRAIN_NULL) {
				_map[i][j].img->frameRender(getMemDC(), i * TILESIZE + camera.x, j * TILESIZE + camera.y, _map[i][j].sourX, _map[i][j].sourY);
			}
			//RectangleMake(getMemDC(), i * 10, j * 10, 10, 10);				
		}
	}

	// 장식 그리기
	for (_viDecoTile = _vDecoTile.begin(); _viDecoTile != _vDecoTile.end(); ++_viDecoTile)
	{
		if (_viDecoTile->floor == _curStageNum) {
			_viDecoTile->img->frameRender(getMemDC(), _viDecoTile->destX * TILESIZE + camera.x, _viDecoTile->destY * TILESIZE + camera.y, _viDecoTile->sourX, _viDecoTile->sourY);		
		}
	}

	//그림자 그리기 (deco 때문에 여기로 옮김)
	for (int i = _renderStartX; i < _renderStartX + _renderSizeX; i++) {
		for (int j = _renderStartY; j < _renderStartY + _renderSizeY; j++) {
			if (_map[i][j].terrain != TERRAIN_NULL) {
				drawTileShadow(_map[i][j]);
			}
			//RectangleMake(getMemDC(), i * 10, j * 10, 10, 10);				
		}
	}

	// 오브젝트 그리기
	for (_viObj = _vObj.begin(); _viObj != _vObj.end(); ++_viObj)
	{
		if ((_map[_viObj->destX][_viObj->destY].terrain & ATTRIBUTE_HIDDEN) == ATTRIBUTE_HIDDEN && !(KEYMANAGER->isStayKeyDown(VK_LSHIFT))) continue;


		if (_viObj->obj != OBJ_NONE && _viObj->floor == _curStageNum) {
			if (_map[_viObj->destX][_viObj->destY].tileview == TILEVIEW_ALL)
				if (_viObj->obj == OBJ_WELL|| _viObj->obj == OBJ_POT)
				{
					_viObj->img->frameRender(getMemDC(), _viObj->destX * TILESIZE + camera.x, _viObj->destY * TILESIZE + camera.y, _viObj->img->getFrameX(), _viObj->img->getFrameY());
					if (_aniCount % 5 == 0) {
						_viObj->img->setFrameX(_viObj->img->getFrameX() + 1);
						if (_viObj->img->getFrameX() >= _viObj->img->getMaxFrameX()) _viObj->img->setFrameX(0);
					}
				}
				else {
					_viObj->img->frameRender(getMemDC(), _viObj->destX * TILESIZE + camera.x, _viObj->destY * TILESIZE + camera.y, _viObj->sourX, _viObj->sourY);
				}
		}
	}
}


void Map::load(int stageNum) {


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
		tile.floor = stageNum;
		tile.tileview = TILEVIEW_NO;
		
		//if (tile.terrain == TERRAIN_DOOR_CLOSED) {
		//	TILE* newTile = _spareTile.find("HiddenDoor")->second;
		//
		//	tile.sourX = newTile->sourX;
		//	tile.sourY = newTile->sourY;
		//	tile.terrain = newTile->terrain;
		//
		//}


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
		tile.floor = stageNum;

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
		obj.floor = stageNum;

		if (obj.obj == OBJ_TRAP)
		{
			obj.obj = OBJ_TRAP_ACTIVE;
		}
		if (obj.obj == OBJ_WELL)
		{
			obj.img = IMAGEMANAGER->findImage("well_health");	
			obj.img->setFrameX(0);
			obj.img->setFrameY(0);
		}
		if (obj.obj == OBJ_POT)
		{
			obj.img = IMAGEMANAGER->findImage("pot");
			obj.img->setFrameX(0);
			obj.img->setFrameY(0);
		}

		_vObj.push_back(obj);

		pObjListElement = pObjListElement->NextSiblingElement("obj");


		for (int i = 0; i < _vMapTile.size(); i++){
			if (_vMapTile[i].destX == obj.destX && _vMapTile[i].destY == obj.destY) {
				_vMapTile[i].terrain = (TERRAIN)((long)_vMapTile[i].terrain | ATTRIBUTE_OBJECT);
				if (obj.obj == OBJ_STAIR_START) {
					POINT startPoint = PointMake(obj.destX * TILESIZE, obj.destY * TILESIZE);
					_player->setPoint(startPoint);
				}

				if (obj.obj == OBJ_POT) {
					_vMapTile[i].terrain = (TERRAIN)((long)_vMapTile[i].terrain | ATTRIBUTE_UNGO);
				}
				if ((obj.obj & ATTRIBUTE_TRAP) == ATTRIBUTE_TRAP) {
					_vMapTile[i].terrain = (TERRAIN)((long)_vMapTile[i].terrain | ATTRIBUTE_HIDDEN);
				}
			}
		}
	}


	XMLElement * pMonElement = pRoot->FirstChildElement("MonsterList");
	XMLElement * pMonListElement = pMonElement->FirstChildElement("monster");

	while (pMonListElement != nullptr) {
		string name = pMonListElement->FirstChildElement("name")->GetText();
		int destX = pMonListElement->FirstChildElement("destX")->IntText();
		int destY = pMonListElement->FirstChildElement("destY")->IntText();
		if (name == "gnoll") {
			_em->setEnemy(PointMake(destX, destY), 3, stageNum);
		}
		else if (name == "swarm") {
			_em->setEnemy(PointMake(destX, destY), 2, stageNum);
		}
		else if (name == "rat")
		{
			_em->setEnemy(PointMake(destX, destY), 0, stageNum);
		}
		else if (name == "crap")
		{
			_em->setEnemy(PointMake(destX, destY), 5, stageNum);
		}
		else if (name == "goo")
		{
			_em->setEnemy(PointMake(destX, destY), 4, stageNum);
		}

		pMonListElement = pMonListElement->NextSiblingElement("monster");
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


	//for (int i = 0; i < _vMapTile.size(); i++) {
	//	_vMapTile.clear();
	//	vector<TILE>().swap(_vMapTile);		//메모리 해제
	//}
}


void Map::spareTileSetup() {
	TILE* flameTile1 = new TILE;
	flameTile1->img = IMAGEMANAGER->findImage("mapTiles");
	flameTile1->sourX = 3;
	flameTile1->sourY = 0;
	flameTile1->terrain = TERRAIN_FLOOR;

	_spareTile.insert(make_pair("AfterFlame1", flameTile1));

	TILE* flameTile2 = new TILE;
	flameTile2->img = IMAGEMANAGER->findImage("mapTiles");
	flameTile2->sourX = 9;
	flameTile2->sourY = 0;
	flameTile2->terrain = TERRAIN_FLOOR;

	_spareTile.insert(make_pair("AfterFlame2", flameTile2));

	TILE* grassCutTile1 = new TILE;
	grassCutTile1->img = IMAGEMANAGER->findImage("mapTiles");
	grassCutTile1->sourX = 2;
	grassCutTile1->sourY = 0;
	grassCutTile1->terrain = TERRAIN_GRASS;

	_spareTile.insert(make_pair("AfterGrass1", grassCutTile1));

	TILE* grassCutTile2 = new TILE;
	grassCutTile2->img = IMAGEMANAGER->findImage("mapTiles");
	grassCutTile2->sourX = 8;
	grassCutTile2->sourY = 0;
	grassCutTile2->terrain = TERRAIN_GRASS;

	_spareTile.insert(make_pair("AfterGrass2", grassCutTile2));

	TILE* unlockDoor = new TILE;
	unlockDoor->img = IMAGEMANAGER->findImage("mapTiles");
	unlockDoor->sourX = 0;
	unlockDoor->sourY = 5;
	unlockDoor->terrain = TERRAIN_DOOR_CLOSED;

	_spareTile.insert(make_pair("ClosedDoor", unlockDoor));

	TILE* openDoor = new TILE;
	openDoor->img = IMAGEMANAGER->findImage("mapTiles");
	openDoor->sourX = 1;
	openDoor->sourY = 5;
	openDoor->terrain = TERRAIN_DOOR_OPEN;

	_spareTile.insert(make_pair("OpenDoor", openDoor));

	TILE* hiddenDoor = new TILE;
	hiddenDoor->img = IMAGEMANAGER->findImage("mapTiles");
	hiddenDoor->sourX = 0;
	hiddenDoor->sourY = 4;
	hiddenDoor->terrain = TERRAIN_DOOR_HIDDEN;

	_spareTile.insert(make_pair("HiddenDoor", hiddenDoor));
}

void Map::spareObjSetup() {
	GAMEOBJECT* emptyWell = new GAMEOBJECT;
	emptyWell->img = IMAGEMANAGER->findImage("mapTiles");
	emptyWell->sourX = 2;
	emptyWell->sourY = 1;
	emptyWell->obj = OBJ_WELL;

	_spareObj.insert(make_pair("EmptyWell", emptyWell));
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


	int dropRate = RND->getFromIntTo(1, 15);
	if (dropRate == 15) {
		ITEMNAME drop = (ITEMNAME)((int)NAME_SEED_HEAL + RND->getFromIntTo(0, 3));
		_im->setItemToField(drop, i * TILESIZE + TILESIZE * 0.5, j * TILESIZE + TILESIZE * 0.5);
	}
	else if (dropRate <= 3)
		_im->setItemToField(NAME_DEW, i * TILESIZE + TILESIZE * 0.5, j * TILESIZE + TILESIZE * 0.5);
}

void Map::setTile_CloseDoor(int i, int j) {
	if (_map[i][j].terrain == TERRAIN_DOOR_OPEN) {
		TILE* newTile = _spareTile.find("ClosedDoor")->second;

		_map[i][j].sourX = newTile->sourX;
		_map[i][j].sourY = newTile->sourY;
		_map[i][j].terrain = newTile->terrain;
	}

}
void Map::setTile_OpenDoor(int i, int j) {
	if (_map[i][j].terrain == TERRAIN_DOOR_CLOSED) {
		TILE* newTile = _spareTile.find("OpenDoor")->second;

		_map[i][j].sourX = newTile->sourX;
		_map[i][j].sourY = newTile->sourY;
		_map[i][j].terrain = newTile->terrain;
	}
}

void Map::setTile_UnlockDoor(int i, int j) {

	if (_map[i][j].terrain == TERRAIN_DOOR_LOCKED) {
		TILE* newTile = _spareTile.find("ClosedDoor")->second;

		_map[i][j].sourX = newTile->sourX;
		_map[i][j].sourY = newTile->sourY;
		_map[i][j].terrain = newTile->terrain;

		SOUNDMANAGER->play("43.unlock", 1.0);

	}
}

void Map::setTile_SearchHidden(int i, int j) {
	if ((_map[i][j].terrain & ATTRIBUTE_HIDDEN) == ATTRIBUTE_HIDDEN) {
		_map[i][j].terrain = (TERRAIN)((long)_map[i][j].terrain ^ ATTRIBUTE_HIDDEN);

		if ((_map[i][j].terrain & ATTRIBUTE_DOOR) == ATTRIBUTE_DOOR) {
			TILE* newTile = _spareTile.find("ClosedDoor")->second;

			_map[i][j].sourX = newTile->sourX;
			_map[i][j].sourY = newTile->sourY;
			_map[i][j].terrain = newTile->terrain;
		}
	}
}

void Map::setObj_OpenChest(int i) {
	if ((_vObj[i].obj & ATTRIBUTE_CHEST) == ATTRIBUTE_CHEST && (_vObj[i].obj & ATTRIBUTE_LOCKED) != ATTRIBUTE_LOCKED) {
		_vObj[i].obj = OBJ_NONE;

		int dropRate = RND->getFromIntTo(1,7);
		if (dropRate == 1) {
			ITEMNAME drop = (ITEMNAME)((int)NAME_BOTTLE + RND->getFromIntTo(0, 7));
			_im->setItemToField(drop, _vObj[i].destX * TILESIZE + TILESIZE * 0.5, _vObj[i].destY * TILESIZE + TILESIZE * 0.5);
		}
		else if (dropRate == 2) {
			_im->setItemToField(NAME_PASTY, _vObj[i].destX * TILESIZE + TILESIZE * 0.5, _vObj[i].destY * TILESIZE + TILESIZE * 0.5);
		}
		else if (dropRate == 3) {
			_im->setItemToField(NAME_BOTTLE, _vObj[i].destX * TILESIZE + TILESIZE * 0.5, _vObj[i].destY * TILESIZE + TILESIZE * 0.5);
		}
		else if (dropRate == 4) {
			ITEMNAME drop = (ITEMNAME)((int)NAME_IDENTIFY + RND->getFromIntTo(0, 4));
			_im->setItemToField(drop, _vObj[i].destX * TILESIZE + TILESIZE * 0.5, _vObj[i].destY * TILESIZE + TILESIZE * 0.5);
		}
		else { // 미믹용(임시)
			_em->setEnemy(PointMake(_vObj[i].destX, _vObj[i].destY), 1, _curStageNum);
		}
	}
}


void Map::setObj_UseWell(int i) {
	if ((_vObj[i].obj & ATTRIBUTE_WELL) == ATTRIBUTE_WELL)
	{
		GAMEOBJECT* newObj = _spareObj.find("EmptyWell")->second;

		_vObj[i].img = newObj->img;
		_vObj[i].sourX = newObj->sourX;
		_vObj[i].sourY = newObj->sourY;

		_vObj[i].obj = (OBJ)((long)_vObj[i].obj ^ ATTRIBUTE_ACTIVE);
	}
}

void Map::setObj_ActivTrap(int i) {
	_vObj[i].sourX = 8;
	_vObj[i].obj = (OBJ)((long)_vObj[i].obj ^ ATTRIBUTE_ACTIVE);

	_map[_vObj[i].destX][_vObj[i].destY].terrain = (TERRAIN)((long)_map[_vObj[i].destX][_vObj[i].destY].terrain ^ ATTRIBUTE_HIDDEN);
	
	_player->getDamaged(10);
	

}


void Map::changeFloor(int floor, bool firstTime){

	// 변화한 타일 저장
	if (!firstTime) {
		for (int i = 0; i < _vMapTile.size(); i++) {
			if (_vMapTile[i].floor == _curStageNum) {
				_map[_vMapTile[i].destX][_vMapTile[i].destY].img = _vMapTile[i].img;

				_vMapTile[i].sourX = _map[_vMapTile[i].destX][_vMapTile[i].destY].sourX;
				_vMapTile[i].sourY = _map[_vMapTile[i].destX][_vMapTile[i].destY].sourY;

				_vMapTile[i].terrain = _map[_vMapTile[i].destX][_vMapTile[i].destY].terrain;
				_vMapTile[i].tileview = _map[_vMapTile[i].destX][_vMapTile[i].destY].tileview;
			}
		}
	}

	// 맵 비우기
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			_map[i][j].terrain = TERRAIN_NULL;
			_map[i][j].tileview = TILEVIEW_NO;
		}
	}

	// 옮길 층의 타일 불러오기
	for (int i = 0; i < _vMapTile.size(); i++) {
		if (_vMapTile[i].floor == floor) {
			_map[_vMapTile[i].destX][_vMapTile[i].destY].img = _vMapTile[i].img;

			_map[_vMapTile[i].destX][_vMapTile[i].destY].destX = _vMapTile[i].destX;
			_map[_vMapTile[i].destX][_vMapTile[i].destY].destY = _vMapTile[i].destY;
			_map[_vMapTile[i].destX][_vMapTile[i].destY].sourX = _vMapTile[i].sourX;
			_map[_vMapTile[i].destX][_vMapTile[i].destY].sourY = _vMapTile[i].sourY;
			_map[_vMapTile[i].destX][_vMapTile[i].destY].obj = _vMapTile[i].obj;
			_map[_vMapTile[i].destX][_vMapTile[i].destY].terrain = _vMapTile[i].terrain;
			_map[_vMapTile[i].destX][_vMapTile[i].destY].tileview = _vMapTile[i].tileview;
		}
	}
	for (int i = 0; i < _vObj.size(); i++) {
		if (_curStageNum <= floor) {
			if (_vObj[i].obj == OBJ_STAIR_START && _vObj[i].floor == floor) {
				POINT playerPoint = PointMake(_vObj[i].destX*TILESIZE + TILESIZE / 2, _vObj[i].destY*TILESIZE + TILESIZE / 2);
				_player->setPoint(playerPoint);
				break;
			}
		}
		else {
			if (_vObj[i].obj == OBJ_STAIR_END && _vObj[i].floor == floor) {
				POINT playerPoint = PointMake(_vObj[i].destX*TILESIZE + TILESIZE / 2, _vObj[i].destY*TILESIZE + TILESIZE / 2);
				_player->setPoint(playerPoint);
				break;
			}
		}
	}

	_curStageNum = floor;
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


void Map::playerTurnEnd() {

	int playerX = _player->getPoint().x / TILESIZE;
	int playerY = _player->getPoint().y / TILESIZE;
	bool isMoving =	_player->getIsPlayerMoving();

	//오브젝트 상호작용 test
	for (int i = 0; i < _vObj.size(); i++) {
		if (playerX == _vObj[i].destX && playerY == _vObj[i].destY && _vObj[i].floor == _curStageNum) {
			if (_vObj[i].obj == OBJ_STAIR_END && !isMoving) {
				if (_curStageNum < _stageDataList.size()) {
					changeFloor(_curStageNum + 1, false);
					break;
				}
			}
			if (_vObj[i].obj == OBJ_STAIR_START && !isMoving) {
				if (_curStageNum != 0)
				{
					changeFloor(_curStageNum - 1, false);
					break;
				}
			}
			

			//if (_vObj[i].obj == OBJ_CHEST && !isMoving) {
			//	setObj_OpenChest(i);
			//	break;
			//}

			if ((_vObj[i].obj & ATTRIBUTE_WELL) == ATTRIBUTE_WELL && (_vObj[i].obj & ATTRIBUTE_ACTIVE) == ATTRIBUTE_ACTIVE && !isMoving) {
				setObj_UseWell(i);
				break;
			}

			if ((_vObj[i].obj & ATTRIBUTE_TRAP) == ATTRIBUTE_TRAP && (_vObj[i].obj & ATTRIBUTE_ACTIVE) == ATTRIBUTE_ACTIVE) {
				setObj_ActivTrap(i);
				break;
			}
		}
	}

	if ((_map[playerX][playerY].terrain & ATTRIBUTE_GRASS) == ATTRIBUTE_GRASS &&
		(_map[playerX][playerY].terrain & ATTRIBUTE_UNSIGHT) == ATTRIBUTE_UNSIGHT) {
		setTile_GrassCut(playerX, playerY);
	}
	
	if ((_map[playerX][playerY].terrain == TERRAIN_DOOR_CLOSED)) {
		setTile_OpenDoor(playerX, playerY);
	}

}