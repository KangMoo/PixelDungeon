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


}
void Map::render()
{
}

//�׸� ��	x��ǥ�� camera.x ��ŭ
//			y��ǥ�� camera.y ��ŭ �����ֱ�!!!!
void Map::render(POINT camera)
{
	draw(camera);
}
void Map::draw(POINT camera)
{
	int temp = 7;
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) temp++;
	if (KEYMANAGER->isStayKeyDown(VK_LEFT)) temp--;
	if (start) {
		for (int i = 0; i < _vMapTile.size(); i++) {
				if (_vMapTile[i].terrain != TERRAIN_NULL)
				{


					RectangleMake(getMemDC(), _vMapTile[i].destX * 10, _vMapTile[i].destY * 10, 10, 10);
					_vMapTile[i].img->frameRender(getMemDC(), _vMapTile[i].destX * TILESIZE, _vMapTile[i].destY * TILESIZE, _vMapTile[i].sourX, _vMapTile[i].sourY);

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
				}

			}
	}



}


void Map::load() {


	//TILE loadMap[10000];
	////�ӽ÷� ����. ���߿� �ٲ����...
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


	//xml �ε�
	XMLDocument xmlDoc;

	XMLError eResult = xmlDoc.LoadFile("SavedData.xml");

	XMLNode * pRoot = xmlDoc.FirstChild();

	XMLElement * pElement = pRoot->FirstChildElement("List");
	_tileNum = pElement->FirstChildElement("size")->IntText();
	XMLElement * pListElement = pElement->FirstChildElement("tile");

	while (pListElement != nullptr) {
		TILE tile;

		tile.img = IMAGEMANAGER->findImage("mapTiles"); //�ӽ�, ���߿� �ּҰ����� �ٲܰ�

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
		_map[_vMapTile[i].destX][_vMapTile[i].destY].tileview = TILEVIEW_NO;
	}

}

vector<TILE> Map::aStar(POINT currentPoint, POINT goalPoint)
{


	_openlist.clear();
	_closelist.clear();

	//�������� ����
	vertex startPoint;
	startPoint.g = 0;
	startPoint.h = getDistance(currentPoint.x, currentPoint.y, goalPoint.x, goalPoint.y);
	startPoint.f = startPoint.g + startPoint.h;
	startPoint.x = currentPoint.x / TILESIZE;
	startPoint.y = currentPoint.y / TILESIZE;
	startPoint.px = startPoint.x;
	startPoint.py = startPoint.y;
	//���������� closelist�� push_back
	_closelist.push_back(startPoint);
	//8���� Ž�� �� ���� ��Ͽ� �߰�
	add_eightway(startPoint, goalPoint);


	vertex curV;
	bool findWay;
	while (true)
	{
		curV = pop_openlist();
		add_closelist(curV);

		add_eightway(curV, goalPoint);

		//openlist�� ����ų�(���̾��ų�) �������� ã�� ���
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


	//���������� ���� �� �����
	vector<TILE> way;
	//���� ���� ���
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
	//���� ���� ���
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
	//�̵���� ���ϱ�
	if (v.x != p.x && v.y != p.y)
	{
		v.h = p.h + 45;
	}
	else
	{
		v.h = p.h + 32;
	}
	//�����̵���� ���ϱ�
	v.g = getDistance(v.x, v.y, goalPoint.x, goalPoint.y);
	//�հ�
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
		//���ǽĿ� ���� 8���� openlist�� �߰�
		bool aU, aD, aR, aL;
		aU = aD = aR = aL = false;
		//�����¿�
		if (_map[v.x - 1][v.y].terrain != TERRAIN_WALL && !search_closelist_exsist(v.x - 1, v.y))
		{
			temp.x = v.x - 1;
			temp.y = v.y;
			temp = calc_vertex(temp, v, goalPoint);
			add_openlist(temp);
			aL = true;
		}
		if (_map[v.x + 1][v.y].terrain != TERRAIN_WALL && !search_closelist_exsist(v.x + 1, v.y))
		{
			temp.x = v.x + 1;
			temp.y = v.y;
			temp = calc_vertex(temp, v, goalPoint);
			add_openlist(temp);
			aR = true;
		}
		if (_map[v.x][v.y - 1].terrain != TERRAIN_WALL && !search_closelist_exsist(v.x, v.y - 1))
		{
			temp.x = v.x;
			temp.y = v.y - 1;
			temp = calc_vertex(temp, v, goalPoint);
			add_openlist(temp);
			aU = true;
		}
		if (_map[v.x][v.y + 1].terrain != TERRAIN_WALL && !search_closelist_exsist(v.x, v.y + 1))
		{
			temp.x = v.x;
			temp.y = v.y + 1;
			temp = calc_vertex(temp, v, goalPoint);
			add_openlist(temp);
			aD = true;
		}

		//�밢��
		if (_map[v.x - 1][v.y - 1].terrain != TERRAIN_WALL && !search_closelist_exsist(v.x - 1, v.y - 1) && aL && aU)
		{
			temp.x = v.x - 1;
			temp.y = v.y - 1;
			temp = calc_vertex(temp, v, goalPoint);
			add_openlist(temp);
		}
		if (_map[v.x + 1][v.y - 1].terrain != TERRAIN_WALL && !search_closelist_exsist(v.x - 1, v.y - 1) && aR && aU)
		{
			temp.x = v.x + 1;
			temp.y = v.y - 1;
			temp = calc_vertex(temp, v, goalPoint);
			add_openlist(temp);
		}
		if (_map[v.x - 1][v.y + 1].terrain != TERRAIN_WALL && !search_closelist_exsist(v.x - 1, v.y - 1) && aL && aD)
		{
			temp.x = v.x - 1;
			temp.y = v.y + 1;
			temp = calc_vertex(temp, v, goalPoint);
			add_openlist(temp);
		}
		if (_map[v.x + 1][v.y + 1].terrain != TERRAIN_WALL && !search_closelist_exsist(v.x - 1, v.y - 1) && aR && aD)
		{
			temp.x = v.x + 1;
			temp.y = v.y + 1;
			temp = calc_vertex(temp, v, goalPoint);
			add_openlist(temp);
		}
	}
	else
	{
		//���ǽĿ� ���� 8���� openlist�� �߰�
		bool aU, aD, aR, aL;
		aU = aD = aR = aL = false;
		//�����¿�
		if (_map[v.x - 1][v.y].terrain != TERRAIN_WALL && !search_closelist_exsist(v.x - 1, v.y))
		{
			vertex temp;
			temp = v;
			temp.px = v.x;
			temp.py = v.y;
			temp.x = v.x - 1;
			temp.y = v.y;
			temp = calc_vertex(temp, v, goalPoint);
			//�̹� ���¸���Ʈ�� �����Ѵٸ�?
			if (search_openlist_exsist(v.x - 1, v.y))
			{
				//���� �� �����ŷ� �ٲ�
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
		if (_map[v.x + 1][v.y].terrain != TERRAIN_WALL && !search_closelist_exsist(v.x + 1, v.y))
		{
			vertex temp;
			temp = v;
			temp.px = v.x;
			temp.py = v.y;
			temp.x = v.x + 1;
			temp.y = v.y;
			temp = calc_vertex(temp, v, goalPoint);
			//�̹� ���¸���Ʈ�� �����Ѵٸ�?
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
		if (_map[v.x][v.y - 1].terrain != TERRAIN_WALL && !search_closelist_exsist(v.x, v.y - 1))
		{
			vertex temp;
			temp = v;
			temp.px = v.x;
			temp.py = v.y;
			temp.x = v.x;
			temp.y = v.y - 1;
			temp = calc_vertex(temp, v, goalPoint);
			//�̹� ���¸���Ʈ�� �����Ѵٸ�?
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
		if (_map[v.x][v.y + 1].terrain != TERRAIN_WALL && !search_closelist_exsist(v.x, v.y + 1))
		{
			vertex temp;
			temp = v;
			temp.px = v.x;
			temp.py = v.y;
			temp.x = v.x;
			temp.y = v.y + 1;
			temp = calc_vertex(temp, v, goalPoint);
			//�̹� ���¸���Ʈ�� �����Ѵٸ�?
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

		//�밢��
		if (_map[v.x - 1][v.y - 1].terrain != TERRAIN_WALL && !search_closelist_exsist(v.x - 1, v.y - 1) && aL && aU)
		{
			vertex temp;
			temp = v;
			temp.px = v.x;
			temp.py = v.y;
			temp.x = v.x - 1;
			temp.y = v.y - 1;
			temp = calc_vertex(temp, v, goalPoint);
			//�̹� ���¸���Ʈ�� �����Ѵٸ�?
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
		if (_map[v.x + 1][v.y - 1].terrain != TERRAIN_WALL && !search_closelist_exsist(v.x + 1, v.y - 1) && aR && aU)
		{
			vertex temp;
			temp = v;
			temp.px = v.x;
			temp.py = v.y;
			temp.x = v.x + 1;
			temp.y = v.y - 1;
			temp = calc_vertex(temp, v, goalPoint);
			//�̹� ���¸���Ʈ�� �����Ѵٸ�?
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
		if (_map[v.x - 1][v.y + 1].terrain != TERRAIN_WALL && !search_closelist_exsist(v.x - 1, v.y + 1) && aL && aD)
		{
			vertex temp;
			temp = v;
			temp.px = v.x;
			temp.py = v.y;
			temp.x = v.x - 1;
			temp.y = v.y + 1;
			temp = calc_vertex(temp, v, goalPoint);
			//�̹� ���¸���Ʈ�� �����Ѵٸ�?
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
		if (_map[v.x + 1][v.y + 1].terrain != TERRAIN_WALL && !search_closelist_exsist(v.x + 1, v.y + 1) && aR && aD)
		{
			vertex temp;
			temp = v;
			temp.px = v.x;
			temp.py = v.y;
			temp.x = v.x + 1;
			temp.y = v.y + 1;
			temp = calc_vertex(temp, v, goalPoint);
			//�̹� ���¸���Ʈ�� �����Ѵٸ�?
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