#include "stdafx.h"
#include "Map.h"
#include "EnemyManager.h"
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
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			_map[i][j].terrain = TERRAIN_NULL;
		}

	}


	start = true;
	load();

	spareTileSetup();


	IMAGEMANAGER->addImage("blackLineVertical", "Img//Map//blackdot.bmp", 1, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("blackLineHorizontal", "Img//Map//blackdot.bmp", 32, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("blackTile", "Img//Map//blackdot.bmp", 32, 32, true, RGB(255, 0, 255));
	return S_OK;
}
void Map::release()
{
}
void Map::update()
{

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
	// test
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
			if (_map[i][j].terrain != TERRAIN_NULL)
			{
				RectangleMake(getMemDC(), i * 10, j * 10, 10, 10);
				_map[i][j].img->frameRender(getMemDC(), i * TILESIZE, j * TILESIZE, _map[i][j].sourX, _map[i][j].sourY);
			}
		}
	}

	
	//if (start) {
	//	for (int i = 0; i < _vMapTile.size(); i++) {
	//			if (_vMapTile[i].terrain != TERRAIN_NULL)
	//			{
	//
	//
	//				RectangleMake(getMemDC(), _vMapTile[i].destX * 10, _vMapTile[i].destY * 10, 10, 10);
	//				_vMapTile[i].img->frameRender(getMemDC(), _vMapTile[i].destX * TILESIZE, _vMapTile[i].destY * TILESIZE, _vMapTile[i].sourX, _vMapTile[i].sourY);

					//if (i == temp)
					//{
					//	for (int pix = 0; pix < 32; pix++)
					//	{
					//		IMAGEMANAGER->alphaRender("blackLineVertical", getMemDC(), i * 32 + pix, i * 32, pix * 150 / 32);
					//		//IMAGEMANAGER->alphaRender("blackLineHorizontal", getMemDC(), i * 32, j * 32 + pix, pix * 255 / 32);
					//	}
					//}
					//if (i == temp+1)
					//{
					//	IMAGEMANAGER->alphaRender("blackTile", getMemDC(), i * 32, i * 32, 150);
					//}
					//if (i == temp+2)
					//{
					//	IMAGEMANAGER->alphaRender("blackTile", getMemDC(), i * 32, i * 32, 150);
					//	for (int pix = 0; pix < 32; pix++)
					//	{
					//		IMAGEMANAGER->alphaRender("blackLineVertical", getMemDC(), i * 32 + pix, i * 32, pix * 255 / 32);
					//		//IMAGEMANAGER->alphaRender("blackLineHorizontal", getMemDC(), i * 32, j * 32 + pix, pix * 255 / 32);
					//	}

					//}
					//else if (i > temp+2)
					//{
					//	IMAGEMANAGER->render("blackTile", getMemDC(), i * 32, i * 32);
					//}
	//			}
	//
	//		}
	//}



}


void Map::load() {


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
		tile.obj = (OBJ)pTileListElement->FirstChildElement("obj")->IntText();
		tile.terrain = (TERRAIN)pTileListElement->FirstChildElement("terrain")->IntText();

		_vMapTile.push_back(tile);

		pTileListElement = pTileListElement->NextSiblingElement("tile");
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


	//for (int i = 0; i < _vMapTile.size(); i++) {
	//	_vMapTile.clear();
	//	vector<TILE>().swap(_vMapTile);		//메모리 해제
	//}
}

vector<TILE> Map::aStar(POINT currentPoint, POINT goalPoint)
{


	_openlist.clear();
	_closelist.clear();

	//시작지점 설정
	vertex startPoint;
	startPoint.g = 0;
	startPoint.h = getDistance(currentPoint.x, currentPoint.y, goalPoint.x, goalPoint.y);
	startPoint.f = startPoint.g + startPoint.h;
	startPoint.x = currentPoint.x / TILESIZE;
	startPoint.y = currentPoint.y / TILESIZE;
	startPoint.px = startPoint.x;
	startPoint.py = startPoint.y;
	//시작지점을 closelist에 push_back
	_closelist.push_back(startPoint);
	//8방향 탐색 후 열린 목록에 추가
	add_eightway(startPoint, goalPoint);


	vertex curV;
	bool findWay;
	while (true)
	{
		curV = pop_openlist();
		add_closelist(curV);

		add_eightway(curV, goalPoint);

		//openlist가 비었거나(길이없거나) 목적지를 찾은 경우
		if (_openlist.size() == 0)
		{
			findWay = false;
			break;
		}
		else if (search_openlist_exsist(goalPoint.x / TILESIZE, goalPoint.y / TILESIZE))
		{
			findWay = true;
			break;
		}
	}


	//목적지까지 가는 길 만들기
	vector<TILE> way;
	//길이 있을 경우
	if (findWay)
	{

		way.push_back(_map[curV.x][curV.y]);
		while (true)
		{
			if (curV.x == currentPoint.x/TILESIZE && curV.y == currentPoint.y / TILESIZE)
			{
				break;
			}
			else
			{
				curV = pop_closelist(curV.px, curV.py);
				way.push_back(_map[curV.x][curV.y]);
			}
		}
	}
	//길이 없을 경우
	else
	{
		return way;
	}
	return way;
}

void Map::add_openlist(vertex v)
{
	for (auto i : _openlist)
	{
		if (i.x == v.x && i.y == v.y)
		{
			return;
		}
	}
	for (auto i : _closelist)
	{
		if (i.x == v.x && i.y == v.y)
		{
			return;
		}
	}
	_openlist.push_back(v);
	sort(_openlist.begin(), _openlist.end());
}
vertex Map::pop_openlist()
{
	vertex temp;
	temp = _openlist[_openlist.size() - 1];
	_openlist.pop_back();
	return temp;
}
vertex Map::pop_openlist(int x, int y)
{
	for (auto i : _openlist)
	{
		if (i.x == x && i.y == y)
		{
			return i;
		}
	}
	vertex temp;
	return temp;
}
vertex Map::search_openlist(int x, int y)
{
	for (auto i : _openlist)
	{
		if (i.x == x && i.y == y)
		{
			return i;
		}
	}
	vertex temp;
	return temp;
}
bool Map::search_openlist_exsist(int x, int y)
{
	for (auto i : _openlist)
	{
		if (i.x == x && i.y == y)
		{
			return true;
		}
	}
	return false;
}
void Map::add_closelist(vertex v)
{
	for (auto i : _closelist)
	{
		if (i.x == v.x && i.y == v.y)
		{
			return;
		}
	}
	_closelist.push_back(v);
}
vertex Map::pop_closelist(int x, int y)
{
	for (auto i : _closelist)
	{
		if (i.x == x && i.y == y)
		{
			return i;
		}
	}
	vertex temp;
	return temp;
}
bool Map::search_closelist_exsist(int x, int y)
{
	for (auto i : _closelist)
	{
		if (i.x == x && i.y == y)
		{
			return true;
		}
	}
	return false;
}
vertex Map::calc_vertex(vertex v, vertex p, POINT goalPoint)
{
	//이동비용 구하기
	if (v.x != p.x && v.y != p.y)
	{
		v.h = p.h + 45;
	}
	else
	{
		v.h = p.h + 32;
	}
	//예상이동비용 구하기
	v.g = getDistance(v.x, v.y, goalPoint.x, goalPoint.y);
	//합계
	v.f = v.g + v.h;
	return v;
}
void Map::add_eightway(vertex v, POINT goalPoint)
{
	if (v.x == v.px && v.y == v.py)
	{
		vertex temp;
		temp = v;
		temp.px = v.x;
		temp.py = v.y;
		//조건식에 따라 8방향 openlist에 추가
		bool aU, aD, aR, aL;
		aU = aD = aR = aL = false;

		bool test = (ATTRIBUTE_UNGO & _map[v.x - 1][v.y].terrain) == ATTRIBUTE_UNGO;
		//상하좌우
		if ((ATTRIBUTE_UNGO & _map[v.x - 1][v.y].terrain) != ATTRIBUTE_UNGO && !search_closelist_exsist(v.x - 1, v.y))
		{
			temp.x = v.x - 1;
			temp.y = v.y;
			temp = calc_vertex(temp, v, goalPoint);
			add_openlist(temp);
			aL = true;
		}
		if ((_map[v.x + 1][v.y].terrain & ATTRIBUTE_UNGO) != ATTRIBUTE_UNGO && !search_closelist_exsist(v.x + 1, v.y))
		{
			temp.x = v.x + 1;
			temp.y = v.y;
			temp = calc_vertex(temp, v, goalPoint);
			add_openlist(temp);
			aR = true;
		}
		if ((_map[v.x][v.y - 1].terrain & ATTRIBUTE_UNGO) != ATTRIBUTE_UNGO && !search_closelist_exsist(v.x, v.y - 1))
		{
			temp.x = v.x;
			temp.y = v.y - 1;
			temp = calc_vertex(temp, v, goalPoint);
			add_openlist(temp);
			aU = true;
		}
		if ((_map[v.x][v.y + 1].terrain & ATTRIBUTE_UNGO) != ATTRIBUTE_UNGO && !search_closelist_exsist(v.x, v.y + 1))
		{
			temp.x = v.x;
			temp.y = v.y + 1;
			temp = calc_vertex(temp, v, goalPoint);
			add_openlist(temp);
			aD = true;
		}

		//대각선
		if ((_map[v.x - 1][v.y - 1].terrain & ATTRIBUTE_UNGO) != ATTRIBUTE_UNGO && !search_closelist_exsist(v.x - 1, v.y - 1) && aL && aU)
		{
			temp.x = v.x - 1;
			temp.y = v.y - 1;
			temp = calc_vertex(temp, v, goalPoint);
			add_openlist(temp);
		}
		if ((_map[v.x + 1][v.y - 1].terrain & ATTRIBUTE_UNGO) != ATTRIBUTE_UNGO && !search_closelist_exsist(v.x - 1, v.y - 1) && aR && aU)
		{
			temp.x = v.x + 1;
			temp.y = v.y - 1;
			temp = calc_vertex(temp, v, goalPoint);
			add_openlist(temp);
		}
		if ((_map[v.x - 1][v.y + 1].terrain & ATTRIBUTE_UNGO) != ATTRIBUTE_UNGO && !search_closelist_exsist(v.x - 1, v.y - 1) && aL && aD)
		{
			temp.x = v.x - 1;
			temp.y = v.y + 1;
			temp = calc_vertex(temp, v, goalPoint);
			add_openlist(temp);
		}
		if ((_map[v.x + 1][v.y + 1].terrain & ATTRIBUTE_UNGO) != ATTRIBUTE_UNGO && !search_closelist_exsist(v.x - 1, v.y - 1) && aR && aD)
		{
			temp.x = v.x + 1;
			temp.y = v.y + 1;
			temp = calc_vertex(temp, v, goalPoint);
			add_openlist(temp);
		}
	}
	else
	{
		//조건식에 따라 8방향 openlist에 추가
		bool aU, aD, aR, aL;
		aU = aD = aR = aL = false;
		//상하좌우
		if ((_map[v.x - 1][v.y].terrain & ATTRIBUTE_UNGO) != ATTRIBUTE_UNGO && !search_closelist_exsist(v.x - 1, v.y))
		{
			vertex temp;
			temp = v;
			temp.px = v.x;
			temp.py = v.y;
			temp.x = v.x - 1;
			temp.y = v.y;
			temp = calc_vertex(temp, v, goalPoint);
			//이미 오픈리스트에 존재한다면?
			if (search_openlist_exsist(v.x - 1, v.y))
			{
				//값이 더 작은거로 바꿈
				if (temp.f < search_openlist(v.x - 1, v.y).f)
				{

				}
			}
			else
			{
				add_openlist(temp);
			}

			aL = true;
		}
		if ((_map[v.x + 1][v.y].terrain & ATTRIBUTE_UNGO) != ATTRIBUTE_UNGO && !search_closelist_exsist(v.x + 1, v.y))
		{
			vertex temp;
			temp = v;
			temp.px = v.x;
			temp.py = v.y;
			temp.x = v.x + 1;
			temp.y = v.y;
			temp = calc_vertex(temp, v, goalPoint);
			//이미 오픈리스트에 존재한다면?
			if (search_openlist_exsist(v.x + 1, v.y))
			{
				if (temp.f < search_openlist(v.x + 1, v.y).f)
				{

				}
			}
			else
			{
				add_openlist(temp);
			};
			aR = true;
		}
		if ((_map[v.x][v.y - 1].terrain & ATTRIBUTE_UNGO) != ATTRIBUTE_UNGO && !search_closelist_exsist(v.x, v.y - 1))
		{
			vertex temp;
			temp = v;
			temp.px = v.x;
			temp.py = v.y;
			temp.x = v.x;
			temp.y = v.y - 1;
			temp = calc_vertex(temp, v, goalPoint);
			//이미 오픈리스트에 존재한다면?
			if (search_openlist_exsist(v.x, v.y - 1))
			{
				if (temp.f < search_openlist(v.x, v.y - 1).f)
				{

				}
			}
			else
			{
				
			}
			add_openlist(temp);
			aU = true;
		}
		if ((_map[v.x][v.y + 1].terrain & ATTRIBUTE_UNGO) != ATTRIBUTE_UNGO && !search_closelist_exsist(v.x, v.y + 1))
		{
			vertex temp;
			temp = v;
			temp.px = v.x;
			temp.py = v.y;
			temp.x = v.x;
			temp.y = v.y + 1;
			temp = calc_vertex(temp, v, goalPoint);
			//이미 오픈리스트에 존재한다면?
			if (search_openlist_exsist(v.x, v.y + 1))
			{
				if (temp.f < search_openlist(v.x, v.y + 1).f)
				{

				}
			}
			else
			{
				
			}
			add_openlist(temp);
			aD = true;
		}

		//대각선
		if ((_map[v.x - 1][v.y - 1].terrain & ATTRIBUTE_UNGO) != ATTRIBUTE_UNGO && !search_closelist_exsist(v.x - 1, v.y - 1) && aL && aU)
		{
			vertex temp;
			temp = v;
			temp.px = v.x;
			temp.py = v.y;
			temp.x = v.x - 1;
			temp.y = v.y - 1;
			temp = calc_vertex(temp, v, goalPoint);
			//이미 오픈리스트에 존재한다면?
			if (search_openlist_exsist(v.x - 1, v.y - 1))
			{
				if (temp.f < search_openlist(v.x - 1, v.y - 1).f)
				{

				}
			}
			else
			{
				
			}
			add_openlist(temp);
		}
		if ((_map[v.x + 1][v.y - 1].terrain & ATTRIBUTE_UNGO) != ATTRIBUTE_UNGO && !search_closelist_exsist(v.x + 1, v.y - 1) && aR && aU)
		{
			vertex temp;
			temp = v;
			temp.px = v.x;
			temp.py = v.y;
			temp.x = v.x + 1;
			temp.y = v.y - 1;
			temp = calc_vertex(temp, v, goalPoint);
			//이미 오픈리스트에 존재한다면?
			if (search_openlist_exsist(v.x + 1, v.y - 1))
			{
				if (temp.f < search_openlist(v.x + 1, v.y - 1).f)
				{

				}
			}
			else
			{
				
			}
			add_openlist(temp);
		}
		if ((_map[v.x - 1][v.y + 1].terrain & ATTRIBUTE_UNGO) != ATTRIBUTE_UNGO && !search_closelist_exsist(v.x - 1, v.y + 1) && aL && aD)
		{
			vertex temp;
			temp = v;
			temp.px = v.x;
			temp.py = v.y;
			temp.x = v.x - 1;
			temp.y = v.y + 1;
			temp = calc_vertex(temp, v, goalPoint);
			//이미 오픈리스트에 존재한다면?
			if (search_openlist_exsist(v.x - 1, v.y + 1))
			{
				if (temp.f < search_openlist(v.x - 1, v.y + 1).f)
				{

				}
			}
			else
			{
				
			}
			add_openlist(temp);
		}
		if ((_map[v.x + 1][v.y + 1].terrain & ATTRIBUTE_UNGO) != ATTRIBUTE_UNGO && !search_closelist_exsist(v.x + 1, v.y + 1) && aR && aD)
		{
			vertex temp;
			temp = v;
			temp.px = v.x;
			temp.py = v.y;
			temp.x = v.x + 1;
			temp.y = v.y + 1;
			temp = calc_vertex(temp, v, goalPoint);
			//이미 오픈리스트에 존재한다면?
			if (search_openlist_exsist(v.x + 1, v.y + 1))
			{
				
				if (temp.f < search_openlist(v.x + 1, v.y + 1).f)
				{

				}
			}
			else
			{
				
			}
			add_openlist(temp);
		}
	}


}
bool Map::check_goal()
{
	return false;
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
}
