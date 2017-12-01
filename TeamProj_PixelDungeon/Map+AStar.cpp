#include "stdafx.h"
#include "Map.h"
#include "EnemyManager.h"
#include "ItemManager.h"
#include "Player.h"
#include "UI.h"


vector<TILE> Map::aStar(POINT currentPoint, POINT goalPoint)
{


	_openlist.clear();
	_closelist.clear();

	//목적지까지 가는 길 저장할 벡터
	vector<TILE> way;

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

	//openlist에 목적지가 있는 경우?
	if (search_openlist_exsist(goalPoint.x / TILESIZE, goalPoint.y / TILESIZE))
	{
		way.push_back(_map[goalPoint.x / TILESIZE][goalPoint.y / TILESIZE]);
		way.push_back(_map[currentPoint.x / TILESIZE][currentPoint.y / TILESIZE]);

		return way;
	}

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



	//길이 있을 경우
	if (findWay)
	{

		way.push_back(_map[curV.x][curV.y]);
		while (true)
		{
			if (curV.x == currentPoint.x / TILESIZE && curV.y == currentPoint.y / TILESIZE)
			{
				break;
			}
			else
			{
				curV = pop_closelist(curV.px, curV.py);
				way.push_back(_map[curV.x][curV.y]);
			}
		}
		way.insert(way.begin(), _map[goalPoint.x / TILESIZE][goalPoint.y / TILESIZE]);
		return way;
	}
	//길이 없을 경우
	else
	{
		return way;
	}

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
			bool addlist = true;
			//몬스터가 있는타일 제외
			for (auto i : _em->getEnemyVector())
			{
				if ((v.x - 1 == i->getPoint().x / TILESIZE && v.y == i->getPoint().y / TILESIZE))
				{
					addlist = false;
				}
			}
			//플레이어가 있는 타일 제외
			if ((v.x - 1 == _player->getPoint().x / TILESIZE && v.y == _player->getPoint().y / TILESIZE) )
			{
				addlist = false;
			}
			if (addlist)
			{
				temp.x = v.x - 1;
				temp.y = v.y;
				temp = calc_vertex(temp, v, goalPoint);
				add_openlist(temp);
				aL = true;
			}
		}
		if ((_map[v.x + 1][v.y].terrain & ATTRIBUTE_UNGO) != ATTRIBUTE_UNGO && !search_closelist_exsist(v.x + 1, v.y))
		{
			bool addlist = true;
			//몬스터가 있는타일 제외
			for (auto i : _em->getEnemyVector())
			{
				if ((v.x + 1 == i->getPoint().x / TILESIZE && v.y == i->getPoint().y / TILESIZE))
				{
					addlist = false;
				}
			}
			//플레이어가 있는 타일 제외
			if ((v.x + 1 == _player->getPoint().x / TILESIZE && v.y == _player->getPoint().y / TILESIZE))
			{
				addlist = false;
			}
			if (addlist)
			{
				temp.x = v.x + 1;
				temp.y = v.y;
				temp = calc_vertex(temp, v, goalPoint);
				add_openlist(temp);
				aR = true;
			}

		}
		if ((_map[v.x][v.y - 1].terrain & ATTRIBUTE_UNGO) != ATTRIBUTE_UNGO && !search_closelist_exsist(v.x, v.y - 1))
		{
			bool addlist = true;
			//몬스터가 있는타일 제외
			for (auto i : _em->getEnemyVector())
			{
				if ((v.x == i->getPoint().x / TILESIZE && v.y - 1 == i->getPoint().y / TILESIZE))
				{
					addlist = false;
				}
			}
			//플레이어가 있는 타일 제외
			if ((v.x == _player->getPoint().x / TILESIZE && v.y - 1 == _player->getPoint().y / TILESIZE))
			{
				addlist = false;
			}
			if (addlist)
			{
				temp.x = v.x;
				temp.y = v.y - 1;
				temp = calc_vertex(temp, v, goalPoint);
				add_openlist(temp);
				aU = true;
			}

		}
		if ((_map[v.x][v.y + 1].terrain & ATTRIBUTE_UNGO) != ATTRIBUTE_UNGO && !search_closelist_exsist(v.x, v.y + 1))
		{
			bool addlist = true;
			//몬스터가 있는타일 제외
			for (auto i : _em->getEnemyVector())
			{
				if ((v.x == i->getPoint().x / TILESIZE && v.y + 1 == i->getPoint().y / TILESIZE))
				{
					addlist = false;
				}
			}
			//플레이어가 있는 타일 제외
			if ((v.x == _player->getPoint().x / TILESIZE && v.y + 1 == _player->getPoint().y / TILESIZE))
			{
				addlist = false;
			}
			if (addlist)
			{
				temp.x = v.x;
				temp.y = v.y + 1;
				temp = calc_vertex(temp, v, goalPoint);
				add_openlist(temp);
				aD = true;
			}

		}

		//대각선
		if ((_map[v.x - 1][v.y - 1].terrain & ATTRIBUTE_UNGO) != ATTRIBUTE_UNGO && !search_closelist_exsist(v.x - 1, v.y - 1) && aL && aU)
		{
			bool addlist = true;
			//몬스터가 있는타일 제외
			for (auto i : _em->getEnemyVector())
			{
				if ((v.x - 1 == i->getPoint().x / TILESIZE && v.y - 1 == i->getPoint().y / TILESIZE))
				{
					addlist = false;
				}
			}
			//플레이어가 있는 타일 제외
			if ((v.x - 1 == _player->getPoint().x / TILESIZE && v.y - 1 == _player->getPoint().y / TILESIZE))
			{
				addlist = false;
			}
			if (addlist)
			{
				temp.x = v.x - 1;
				temp.y = v.y - 1;
				temp = calc_vertex(temp, v, goalPoint);
				add_openlist(temp);
			}

		}
		if ((_map[v.x + 1][v.y - 1].terrain & ATTRIBUTE_UNGO) != ATTRIBUTE_UNGO && !search_closelist_exsist(v.x - 1, v.y - 1) && aR && aU)
		{
			bool addlist = true;
			//몬스터가 있는타일 제외
			for (auto i : _em->getEnemyVector())
			{
				if ((v.x + 1 == i->getPoint().x / TILESIZE && v.y - 1 == i->getPoint().y / TILESIZE))
				{
					addlist = false;
				}
			}
			//플레이어가 있는 타일 제외
			if ((v.x + 1 == _player->getPoint().x / TILESIZE && v.y - 1 == _player->getPoint().y / TILESIZE))
			{
				addlist = false;
			}
			if (addlist)
			{
				temp.x = v.x + 1;
				temp.y = v.y - 1;
				temp = calc_vertex(temp, v, goalPoint);
				add_openlist(temp);
			}

		}
		if ((_map[v.x - 1][v.y + 1].terrain & ATTRIBUTE_UNGO) != ATTRIBUTE_UNGO && !search_closelist_exsist(v.x - 1, v.y - 1) && aL && aD)
		{
			bool addlist = true;
			//몬스터가 있는타일 제외
			for (auto i : _em->getEnemyVector())
			{
				if ((v.x - 1 == i->getPoint().x / TILESIZE && v.y + 1 == i->getPoint().y / TILESIZE))
				{
					addlist = false;
				}
			}
			//플레이어가 있는 타일 제외
			if ((v.x - 1 == _player->getPoint().x / TILESIZE && v.y + 1 == _player->getPoint().y / TILESIZE))
			{
				addlist = false;
			}
			if (addlist)
			{
				temp.x = v.x - 1;
				temp.y = v.y + 1;
				temp = calc_vertex(temp, v, goalPoint);
				add_openlist(temp);
			}
		}
		if ((_map[v.x + 1][v.y + 1].terrain & ATTRIBUTE_UNGO) != ATTRIBUTE_UNGO && !search_closelist_exsist(v.x - 1, v.y - 1) && aR && aD)
		{
			bool addlist = true;
			//몬스터가 있는타일 제외
			for (auto i : _em->getEnemyVector())
			{
				if ((v.x + 1 == i->getPoint().x / TILESIZE && v.y + 1 == i->getPoint().y / TILESIZE))
				{
					addlist = false;
				}
			}
			//플레이어가 있는 타일 제외
			if ((v.x + 1 == _player->getPoint().x / TILESIZE && v.y + 1 == _player->getPoint().y / TILESIZE))
			{
				addlist = false;
			}
			if (addlist)
			{
				temp.x = v.x + 1;
				temp.y = v.y + 1;
				temp = calc_vertex(temp, v, goalPoint);
				add_openlist(temp);
			}
		}

		//목적지일 경우는 openlist에 추가
		for (int i = -1; i < 2; i++)
		{
			for (int j = -1; j < 2; j++)
			{
				if (v.x + i == goalPoint.x / TILESIZE && v.y + j == goalPoint.y / TILESIZE)
				{
					temp.x = v.x + i;
					temp.y = v.y + j;
					temp = calc_vertex(temp, v, goalPoint);
					add_openlist(temp);
				}
			}
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

			bool addlist = true;
			//몬스터가 있는타일 제외
			for (auto i : _em->getEnemyVector())
			{
				if ((v.x - 1 == i->getPoint().x / TILESIZE && v.y == i->getPoint().y / TILESIZE))
				{
					addlist = false;
				}
			}
			//플레이어가 있는 타일 제외
			if ((v.x - 1 == _player->getPoint().x / TILESIZE && v.y == _player->getPoint().y / TILESIZE))
			{
				addlist = false;
			}
			if (addlist)
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

		}
		if ((_map[v.x + 1][v.y].terrain & ATTRIBUTE_UNGO) != ATTRIBUTE_UNGO && !search_closelist_exsist(v.x + 1, v.y))
		{
			bool addlist = true;
			//몬스터가 있는타일 제외
			for (auto i : _em->getEnemyVector())
			{
				if ((v.x + 1 == i->getPoint().x / TILESIZE && v.y == i->getPoint().y / TILESIZE))
				{
					addlist = false;
				}
			}
			//플레이어가 있는 타일 제외
			if ((v.x + 1 == _player->getPoint().x / TILESIZE && v.y == _player->getPoint().y / TILESIZE))
			{
				addlist = false;
			}
			if (addlist)
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

		}
		if ((_map[v.x][v.y - 1].terrain & ATTRIBUTE_UNGO) != ATTRIBUTE_UNGO && !search_closelist_exsist(v.x, v.y - 1))
		{
			bool addlist = true;
			//몬스터가 있는타일 제외
			for (auto i : _em->getEnemyVector())
			{
				if ((v.x == i->getPoint().x / TILESIZE && v.y - 1 == i->getPoint().y / TILESIZE))
				{
					addlist = false;
				}
			}
			//플레이어가 있는 타일 제외
			if ((v.x == _player->getPoint().x / TILESIZE && v.y - 1 == _player->getPoint().y / TILESIZE))
			{
				addlist = false;
			}
			if (addlist)
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
		}
		if ((_map[v.x][v.y + 1].terrain & ATTRIBUTE_UNGO) != ATTRIBUTE_UNGO && !search_closelist_exsist(v.x, v.y + 1))
		{
			bool addlist = true;
			//몬스터가 있는타일 제외
			for (auto i : _em->getEnemyVector())
			{
				if ((v.x == i->getPoint().x / TILESIZE && v.y + 1 == i->getPoint().y / TILESIZE))
				{
					addlist = false;
				}
			}
			//플레이어가 있는 타일 제외
			if ((v.x == _player->getPoint().x / TILESIZE && v.y + 1 == _player->getPoint().y / TILESIZE))
			{
				addlist = false;
			}
			if (addlist)
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

		}

		//대각선
		if ((_map[v.x - 1][v.y - 1].terrain & ATTRIBUTE_UNGO) != ATTRIBUTE_UNGO && !search_closelist_exsist(v.x - 1, v.y - 1) && aL && aU)
		{
			bool addlist = true;
			//몬스터가 있는타일 제외
			for (auto i : _em->getEnemyVector())
			{
				if ((v.x - 1 == i->getPoint().x / TILESIZE && v.y - 1 == i->getPoint().y / TILESIZE))
				{
					addlist = false;
				}
			}
			//플레이어가 있는 타일 제외
			if ((v.x - 1 == _player->getPoint().x / TILESIZE && v.y - 1 == _player->getPoint().y / TILESIZE))
			{
				addlist = false;
			}
			if (addlist)
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

		}
		if ((_map[v.x + 1][v.y - 1].terrain & ATTRIBUTE_UNGO) != ATTRIBUTE_UNGO && !search_closelist_exsist(v.x + 1, v.y - 1) && aR && aU)
		{
			bool addlist = true;
			//몬스터가 있는타일 제외
			for (auto i : _em->getEnemyVector())
			{
				if ((v.x + 1 == i->getPoint().x / TILESIZE && v.y - 1 == i->getPoint().y / TILESIZE))
				{
					addlist = false;
				}
			}
			//플레이어가 있는 타일 제외
			if ((v.x + 1 == _player->getPoint().x / TILESIZE && v.y - 1 == _player->getPoint().y / TILESIZE))
			{
				addlist = false;
			}
			if (addlist)
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

		}
		if ((_map[v.x - 1][v.y + 1].terrain & ATTRIBUTE_UNGO) != ATTRIBUTE_UNGO && !search_closelist_exsist(v.x - 1, v.y + 1) && aL && aD)
		{
			bool addlist = true;
			//몬스터가 있는타일 제외
			for (auto i : _em->getEnemyVector())
			{
				if ((v.x - 1 == i->getPoint().x / TILESIZE && v.y + 1 == i->getPoint().y / TILESIZE))
				{
					addlist = false;
				}
			}
			//플레이어가 있는 타일 제외
			if ((v.x - 1 == _player->getPoint().x / TILESIZE && v.y + 1 == _player->getPoint().y / TILESIZE))
			{
				addlist = false;
			}
			if (addlist)
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

		}
		if ((_map[v.x + 1][v.y + 1].terrain & ATTRIBUTE_UNGO) != ATTRIBUTE_UNGO && !search_closelist_exsist(v.x + 1, v.y + 1) && aR && aD)
		{
			bool addlist = true;
			//몬스터가 있는타일 제외
			for (auto i : _em->getEnemyVector())
			{
				if ((v.x + 1 == i->getPoint().x / TILESIZE && v.y + 1 == i->getPoint().y / TILESIZE))
				{
					addlist = false;
				}
			}
			//플레이어가 있는 타일 제외
			if ((v.x + 1 == _player->getPoint().x / TILESIZE && v.y + 1 == _player->getPoint().y / TILESIZE))
			{
				addlist = false;
			}
			if (addlist)
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
			//목적지일 경우는 openlist에 추가
		}
		for (int i = -1; i < 2; i++)
		{
			for (int j = -1; j < 2; j++)
			{
				if (v.x + i == goalPoint.x / TILESIZE && v.y + j == goalPoint.y / TILESIZE)
				{
					vertex temp;
					temp.x = v.x + i;
					temp.y = v.y + j;
					temp = calc_vertex(temp, v, goalPoint);
					add_openlist(temp);
				}
			}
		}
	}


}
bool Map::check_goal()
{
	return false;
}
