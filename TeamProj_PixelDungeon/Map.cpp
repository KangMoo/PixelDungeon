#include "stdafx.h"
#include "Map.h"
#include "EnemyManager.h"
#include "Player.h"
#include "UI.h"
#include "tinyxml2.h"

using namespace tinyxml2;

Map::Map()
{
}


Map::~Map()
{
}
HRESULT Map::init()
{
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			_map[i][j].terrain = TERRAIN_NULL;
		}
	
	}


	start = true;
	load();



	
		return S_OK;
}
void Map::release()
{

}
void Map::update()
{


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
	if (start) {
		for (int i = 0; i < 100; i++) {
			for (int j = 0; j < 100; j++) {
				if (_map[i][j].terrain != TERRAIN_NULL)
				{
					RectangleMake(getMemDC(), _map[i][j].destX * 10, _map[i][j].destY * 10, 10, 10);
					_map[i][j].img->frameRender(getMemDC(), i * 32, j * 32, _map[i][j].sourX, _map[i][j].sourY);
				}
					
			}
		}
	}


	
}


void Map::load() {

	//임시로 만듬. 나중에 바꿔야지...	


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


	//xml 로드
	XMLDocument xmlDoc;

	XMLError eResult = xmlDoc.LoadFile("SavedData.xml");

	XMLNode * pRoot = xmlDoc.FirstChild();

	XMLElement * pElement = pRoot->FirstChildElement("List");
	XMLElement * pListElement = pElement->FirstChildElement("tile");

	while (pListElement != nullptr) {
		TILE tile;

		tile.img = IMAGEMANAGER->findImage("mapTiles"); //임시, 나중에 주소값으로 바꿀거

		tile.destX = pListElement->FirstChildElement("destX")->IntText();
		tile.destY = pListElement->FirstChildElement("destY")->IntText();
		tile.sourX = pListElement->FirstChildElement("sourX")->IntText();
		tile.sourY = pListElement->FirstChildElement("sourY")->IntText();
		tile.index = pListElement->FirstChildElement("index")->IntText();
		tile.obj = (OBJ)pListElement->FirstChildElement("obj")->IntText();
		tile.terrain = (TERRAIN)pListElement->FirstChildElement("terrain")->IntText();

		_vMapTile.push_back(tile);

		pListElement = pListElement->NextSiblingElement("tile");
	}


	//지금은 타일 10000개로 고정. 나중에 맵 사이즈에 따라 변하게 바꿀 예정
	for (int i = 0; i < 10000; i++) {
		if (i >= _vMapTile.size()) break;

		_map[_vMapTile[i].destX][_vMapTile[i].destY].img = IMAGEMANAGER->findImage("mapTiles");
	
		_map[_vMapTile[i].destX][_vMapTile[i].destY].destX = _vMapTile[i].destX;
		_map[_vMapTile[i].destX][_vMapTile[i].destY].destY = _vMapTile[i].destY;
		_map[_vMapTile[i].destX][_vMapTile[i].destY].sourX = _vMapTile[i].sourX;
		_map[_vMapTile[i].destX][_vMapTile[i].destY].sourY = _vMapTile[i].sourY;
		_map[_vMapTile[i].destX][_vMapTile[i].destY].index = _vMapTile[i].index;
		_map[_vMapTile[i].destX][_vMapTile[i].destY].obj = _vMapTile[i].obj;
		_map[_vMapTile[i].destX][_vMapTile[i].destY].terrain = _vMapTile[i].terrain;
	}


	
}