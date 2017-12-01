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

	//���������� ���� �� ������ ����
	vector<TILE> way;

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

	//openlist�� �������� �ִ� ���?
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



	//���� ���� ���
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
	//���� ���� ���
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

		bool test = (ATTRIBUTE_UNGO & _map[v.x - 1][v.y].terrain) == ATTRIBUTE_UNGO;
		//�����¿�
		if ((ATTRIBUTE_UNGO & _map[v.x - 1][v.y].terrain) != ATTRIBUTE_UNGO && !search_closelist_exsist(v.x - 1, v.y))
		{
			bool addlist = true;
			//���Ͱ� �ִ�Ÿ�� ����
			for (auto i : _em->getEnemyVector())
			{
				if ((v.x - 1 == i->getPoint().x / TILESIZE && v.y == i->getPoint().y / TILESIZE))
				{
					addlist = false;
				}
			}
			//�÷��̾ �ִ� Ÿ�� ����
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
			//���Ͱ� �ִ�Ÿ�� ����
			for (auto i : _em->getEnemyVector())
			{
				if ((v.x + 1 == i->getPoint().x / TILESIZE && v.y == i->getPoint().y / TILESIZE))
				{
					addlist = false;
				}
			}
			//�÷��̾ �ִ� Ÿ�� ����
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
			//���Ͱ� �ִ�Ÿ�� ����
			for (auto i : _em->getEnemyVector())
			{
				if ((v.x == i->getPoint().x / TILESIZE && v.y - 1 == i->getPoint().y / TILESIZE))
				{
					addlist = false;
				}
			}
			//�÷��̾ �ִ� Ÿ�� ����
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
			//���Ͱ� �ִ�Ÿ�� ����
			for (auto i : _em->getEnemyVector())
			{
				if ((v.x == i->getPoint().x / TILESIZE && v.y + 1 == i->getPoint().y / TILESIZE))
				{
					addlist = false;
				}
			}
			//�÷��̾ �ִ� Ÿ�� ����
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

		//�밢��
		if ((_map[v.x - 1][v.y - 1].terrain & ATTRIBUTE_UNGO) != ATTRIBUTE_UNGO && !search_closelist_exsist(v.x - 1, v.y - 1) && aL && aU)
		{
			bool addlist = true;
			//���Ͱ� �ִ�Ÿ�� ����
			for (auto i : _em->getEnemyVector())
			{
				if ((v.x - 1 == i->getPoint().x / TILESIZE && v.y - 1 == i->getPoint().y / TILESIZE))
				{
					addlist = false;
				}
			}
			//�÷��̾ �ִ� Ÿ�� ����
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
			//���Ͱ� �ִ�Ÿ�� ����
			for (auto i : _em->getEnemyVector())
			{
				if ((v.x + 1 == i->getPoint().x / TILESIZE && v.y - 1 == i->getPoint().y / TILESIZE))
				{
					addlist = false;
				}
			}
			//�÷��̾ �ִ� Ÿ�� ����
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
			//���Ͱ� �ִ�Ÿ�� ����
			for (auto i : _em->getEnemyVector())
			{
				if ((v.x - 1 == i->getPoint().x / TILESIZE && v.y + 1 == i->getPoint().y / TILESIZE))
				{
					addlist = false;
				}
			}
			//�÷��̾ �ִ� Ÿ�� ����
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
			//���Ͱ� �ִ�Ÿ�� ����
			for (auto i : _em->getEnemyVector())
			{
				if ((v.x + 1 == i->getPoint().x / TILESIZE && v.y + 1 == i->getPoint().y / TILESIZE))
				{
					addlist = false;
				}
			}
			//�÷��̾ �ִ� Ÿ�� ����
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

		//�������� ���� openlist�� �߰�
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
		//���ǽĿ� ���� 8���� openlist�� �߰�
		bool aU, aD, aR, aL;
		aU = aD = aR = aL = false;
		//�����¿�
		if ((_map[v.x - 1][v.y].terrain & ATTRIBUTE_UNGO) != ATTRIBUTE_UNGO && !search_closelist_exsist(v.x - 1, v.y))
		{

			bool addlist = true;
			//���Ͱ� �ִ�Ÿ�� ����
			for (auto i : _em->getEnemyVector())
			{
				if ((v.x - 1 == i->getPoint().x / TILESIZE && v.y == i->getPoint().y / TILESIZE))
				{
					addlist = false;
				}
			}
			//�÷��̾ �ִ� Ÿ�� ����
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

		}
		if ((_map[v.x + 1][v.y].terrain & ATTRIBUTE_UNGO) != ATTRIBUTE_UNGO && !search_closelist_exsist(v.x + 1, v.y))
		{
			bool addlist = true;
			//���Ͱ� �ִ�Ÿ�� ����
			for (auto i : _em->getEnemyVector())
			{
				if ((v.x + 1 == i->getPoint().x / TILESIZE && v.y == i->getPoint().y / TILESIZE))
				{
					addlist = false;
				}
			}
			//�÷��̾ �ִ� Ÿ�� ����
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

		}
		if ((_map[v.x][v.y - 1].terrain & ATTRIBUTE_UNGO) != ATTRIBUTE_UNGO && !search_closelist_exsist(v.x, v.y - 1))
		{
			bool addlist = true;
			//���Ͱ� �ִ�Ÿ�� ����
			for (auto i : _em->getEnemyVector())
			{
				if ((v.x == i->getPoint().x / TILESIZE && v.y - 1 == i->getPoint().y / TILESIZE))
				{
					addlist = false;
				}
			}
			//�÷��̾ �ִ� Ÿ�� ����
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
		}
		if ((_map[v.x][v.y + 1].terrain & ATTRIBUTE_UNGO) != ATTRIBUTE_UNGO && !search_closelist_exsist(v.x, v.y + 1))
		{
			bool addlist = true;
			//���Ͱ� �ִ�Ÿ�� ����
			for (auto i : _em->getEnemyVector())
			{
				if ((v.x == i->getPoint().x / TILESIZE && v.y + 1 == i->getPoint().y / TILESIZE))
				{
					addlist = false;
				}
			}
			//�÷��̾ �ִ� Ÿ�� ����
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

		}

		//�밢��
		if ((_map[v.x - 1][v.y - 1].terrain & ATTRIBUTE_UNGO) != ATTRIBUTE_UNGO && !search_closelist_exsist(v.x - 1, v.y - 1) && aL && aU)
		{
			bool addlist = true;
			//���Ͱ� �ִ�Ÿ�� ����
			for (auto i : _em->getEnemyVector())
			{
				if ((v.x - 1 == i->getPoint().x / TILESIZE && v.y - 1 == i->getPoint().y / TILESIZE))
				{
					addlist = false;
				}
			}
			//�÷��̾ �ִ� Ÿ�� ����
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

		}
		if ((_map[v.x + 1][v.y - 1].terrain & ATTRIBUTE_UNGO) != ATTRIBUTE_UNGO && !search_closelist_exsist(v.x + 1, v.y - 1) && aR && aU)
		{
			bool addlist = true;
			//���Ͱ� �ִ�Ÿ�� ����
			for (auto i : _em->getEnemyVector())
			{
				if ((v.x + 1 == i->getPoint().x / TILESIZE && v.y - 1 == i->getPoint().y / TILESIZE))
				{
					addlist = false;
				}
			}
			//�÷��̾ �ִ� Ÿ�� ����
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

		}
		if ((_map[v.x - 1][v.y + 1].terrain & ATTRIBUTE_UNGO) != ATTRIBUTE_UNGO && !search_closelist_exsist(v.x - 1, v.y + 1) && aL && aD)
		{
			bool addlist = true;
			//���Ͱ� �ִ�Ÿ�� ����
			for (auto i : _em->getEnemyVector())
			{
				if ((v.x - 1 == i->getPoint().x / TILESIZE && v.y + 1 == i->getPoint().y / TILESIZE))
				{
					addlist = false;
				}
			}
			//�÷��̾ �ִ� Ÿ�� ����
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

		}
		if ((_map[v.x + 1][v.y + 1].terrain & ATTRIBUTE_UNGO) != ATTRIBUTE_UNGO && !search_closelist_exsist(v.x + 1, v.y + 1) && aR && aD)
		{
			bool addlist = true;
			//���Ͱ� �ִ�Ÿ�� ����
			for (auto i : _em->getEnemyVector())
			{
				if ((v.x + 1 == i->getPoint().x / TILESIZE && v.y + 1 == i->getPoint().y / TILESIZE))
				{
					addlist = false;
				}
			}
			//�÷��̾ �ִ� Ÿ�� ����
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
			//�������� ���� openlist�� �߰�
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
