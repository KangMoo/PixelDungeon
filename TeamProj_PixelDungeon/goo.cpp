#include "stdafx.h"
#include "goo.h"
#include "Player.h"
#include "Map.h"
#include "UI.h"
#include "ItemManager.h"

goo::goo()
{
}


goo::~goo()
{
}

HRESULT goo::init(POINT point, int floor)//�νĹ��� �߱�
{
	//�Է¹��� ��ǥ�� �ʱ� ��ġ��
	_point = point;

	//�� �̹��� �����Ҵ�(MANAGER�� �� �Ȱ���������)
	_stay = new image;
	_move = new image;
	_dead = new image;

	_stay->init("Img//Enemy//goo//goo_stay.bmp", 192, 64, 6, 2, true, RGB(255, 0, 255));
	_move->init("Img//Enemy//goo//goo_move.bmp", 64, 64, 2, 2, true, RGB(255, 0, 255));
	_dead->init("Img//Enemy//goo//goo_dead.bmp", 96, 64, 3, 2, true, RGB(255, 0, 255));

	//�ʱ� ������ stay
	_image = _stay;

	//���� �׷��� ��ġ�� �ش� Ÿ�� �߽��� ����
	_pointX = _point.x * TILESIZE + TILESIZE / 2;
	_pointY = _point.y * TILESIZE + TILESIZE / 2;

	//Ÿ�� �߽����� �̹��� ũ�⸸ŭ ��Ʈ, �̰ɷ� �׸��׸�
	_hitBox = RectMakeCenter(_pointX, _pointY, _image->getFrameWidth(), _image->getFrameHeight());
	_attBox = RectMakeCenter(_pointX, _pointY, 0, 0);

	//�������
	_isLive = true;
	//�÷��̾� �߰� ����
	_findPlayer = false;

	//�ʱ� ������ ��������
	int a = RND->getInt(2);
	if (a == 0) _right = true;
	else _right = false;

	//���� �������� 0, ������ ���� y=0, �����̸� y=1
	_currntFrameX = 0;
	if (_right) _currntFrameY = 0;
	else _currntFrameY = 1;

	//������ ����
	_image->setFrameX(_currntFrameX);
	_image->setFrameY(_currntFrameY);

	//�� �� �ƴ�, �ȿ�����
	_action = false;
	_isMove = false;

	//���� ����
	_statistics.lv = 1;
	_statistics.exp = 2;
	_statistics.hp = 80;
	_currntHp = _statistics.hp;
	_statistics.avd_lck = 12;
	_statistics.def = 2;

	a = RND->getFromIntTo(2, 5);

	_statistics.str = 30;
	_statistics.atk_lck = 11;

	//���������� �ڰ������� ���� ����
	_myState = ENEMYSTATE_IDLE;

	//�ʱⰪ ����
	_movePoint = PointMake(0, 0);
	_frameFPS = 10;
	_frameTime = 0;
	_deadAlpha = 0;

	//_hpBar = new progressBar;
	//_hpBar->init(_pointX - 25, _pointY + _image->getFrameHeight() / 2 + 10, 30, 10);

	_PumpedUP = false;
	_trunCount = 0;

	_floor = floor;

	_hpBar = new progressBar;
	_hpBar->init(WINSIZEX/2 - (124 * 2 / 2), WINSIZEY / 2 - 275, 248,56);
	_hpBar->setGauge(_currntHp, _statistics.hp);

	return S_OK;
}

void goo::release()
{
	SAFE_RELEASE(_image);
	SAFE_DELETE(_image);

	SAFE_RELEASE(_hpBar);
	SAFE_DELETE(_hpBar);

	SAFE_RELEASE(_move);
	SAFE_DELETE(_move);

	SAFE_RELEASE(_dead);
	SAFE_DELETE(_dead);

	SAFE_RELEASE(_stay);
	SAFE_DELETE(_stay);


}


void goo::getDamaged(int damage)
{
	_currntHp -= damage - _statistics.def;

	//_player->getStat().atk_lck �� 0 �̻��̸� �������� �Դ´�

	//int a = RND->getInt(_player->getStat().atk_lck + 1);
	//
	////ui�� ȸ�� �ߴٰ� ���������� ���ڴµ�
	//if (a < _statistics.avd_lck - _player->getStat().atk_lck) return;
	//else
	//{
	//	if (_currntHp > 0)
	//		_currntHp -= damage - _statistics.def;
	//}
}

void goo::draw(POINT camera)
{
	if (_map->getCurStageNum() == _floor)
	{
		//�þ߿� ���϶��� ����ϰ�
		if (_map->getTile(_pointX / TILESIZE, _pointY / TILESIZE).tileview == TILEVIEW_ALL)
			_image->alphaFrameRender(getMemDC(), _hitBox.left + camera.x, _hitBox.top + camera.y, _deadAlpha);
		_hpBar->render();
	}
}

void goo::frameUpdate()
{
	if (_findPlayer)
	{
		if (_player->getPoint().x >= _pointX) _right = true;
		else _right = false;
	}

	if (_right) _currntFrameY = 0;
	else _currntFrameY = 1;

	if (true)
		//if (_frameCount >= 3)
	{
		switch (_myState)
		{
		case ENEMYSTATE_IDLE:
			_image = _stay;
			_frameTime++;
			if (_frameTime >= _frameFPS)
			{
				_currntFrameX++;
				_frameTime = 0;
			}

			if (_currntFrameX > _image->getMaxFrameX()) _currntFrameX = 0;
			_image->setFrameX(_currntFrameX);
			_image->setFrameY(_currntFrameY);

			if ((ATTRIBUTE_WATER & _map->getMap(_point.x, _point.y).terrain) == ATTRIBUTE_WATER)
			{
				_currntHp += 1;
				if (_currntHp >= _statistics.hp) _currntHp = _statistics.hp;
				break;
			}

			break;

		case ENEMYSTATE_MOVE:
			_image = _move;
			_frameTime++;
			if (_frameTime >= _frameFPS)
			{
				_currntFrameX++;
				_frameTime = 0;
			}

			if (_currntFrameX > _image->getMaxFrameX()) _currntFrameX = 0;
			_image->setFrameX(_currntFrameX);
			_image->setFrameY(_currntFrameY);
			//if (_PumpedUP == true) _trunCount++;

			if ((ATTRIBUTE_WATER & _map->getMap(_point.x, _point.y).terrain) == ATTRIBUTE_WATER)
			{
				_currntHp += 1;
				if (_currntHp >= _statistics.hp) _currntHp = _statistics.hp;
				break;
			}

			break;

		case ENEMYSTATE_ATTACK:
			_image = _stay;
			_frameTime++;
			if (_frameTime >= _frameFPS)
			{
				_currntFrameX++;
				_frameTime = 0;
			}

			if (_currntFrameX > _image->getMaxFrameX())
			{
				_currntFrameX = 0;
				_myState = ENEMYSTATE_IDLE;
				_image = _stay;
				_action = false;
			}
			_image->setFrameX(_currntFrameX);
			_image->setFrameY(_currntFrameY);
			//if (_PumpedUP == true) _trunCount++;

			if ((ATTRIBUTE_WATER & _map->getMap(_point.x, _point.y).terrain) == ATTRIBUTE_WATER)
			{
				_currntHp += 1;
				if (_currntHp >= _statistics.hp)_currntHp = _statistics.hp;
				break;
			}
			break;

		case ENEMYSTATE_DEAD:
			_image = _dead;

			_frameTime++;
			if (_frameTime >= _frameFPS)
			{
				_currntFrameX++;
				_frameTime = 0;
			}

			if (_currntFrameX > _image->getMaxFrameX())
			{
				_currntFrameX = _image->getMaxFrameX();
			}
			_image->setFrameX(_currntFrameX);
			_image->setFrameY(_currntFrameY);
			//if (_PumpedUP == true) _trunCount++;

		}
	}

	_hitBox = RectMakeCenter(_pointX, _pointY, _image->getFrameWidth(), _image->getFrameHeight());
}

void goo::action()
{
	//if (KEYMANAGER->isOnceKeyDown('E')) getDamaged(3);

	int skill = RND->getInt(2);

	if (skill == 0 && _PumpedUP == false) _PumpedUP = true;

	if (_myState == ENEMYSTATE_IDLE)
	{
		if (!_findPlayer)
		{
			//���� �߰����� �ʾ����� �����ൿ

			float dis = getDistance(_player->getPoint().x / TILESIZE, _player->getPoint().y / TILESIZE, _point.x, _point.y);

			if (dis < 4)
			{
				//�Ÿ��� ���� ���� �̳��� ���� �������� �ν�
				//�ν��� ���� �׳� �ڵ����� �Ѱ���
				_myState = ENEMYSTATE_IDLE;
				_findPlayer = true;
				_action = false;
			}
			else
			{
				//�Ÿ��� �ָ� �����̵�
				if (!_isMove)
				{
					//0���� �ð��������, 8�� ���
					//�ش� ������ Ÿ���� �˻��� �Ŀ�, �� �� �ִٸ� �������� �̵�
					int a = RND->getInt(50);
					_movePoint = _point;
					_myState = ENEMYSTATE_MOVE;
					switch (a)
					{
					case 0:
						//�� (ATTRIBUTE_UNGO & _map[v.x - 1][v.y].terrain) == ATTRIBUTE_UNGO
						//if (_map->getMap(_point.x, _point.y - 1).obj == OBJ_NONE &&
						//	(_map->getMap(_point.x, _point.y - 1).terrain == TERRAIN_FLOOR ||
						//		_map->getMap(_point.x, _point.y - 1).terrain == TERRAIN_GRASS))
						if ((ATTRIBUTE_UNGO & _map->getMap(_point.x, _point.y - 1).terrain) != ATTRIBUTE_UNGO)
						{
							_isMove = true;
							_movePoint = PointMake(_point.x, _point.y - 1);
							_right = false;
						}
						break;
					case 1:
						//������ ��
						//if (_map->getMap(_point.x + 1, _point.y - 1).obj == OBJ_NONE &&
						//	(_map->getMap(_point.x + 1, _point.y - 1).terrain == TERRAIN_FLOOR ||
						//		_map->getMap(_point.x + 1, _point.y - 1).terrain == TERRAIN_GRASS))
						if ((ATTRIBUTE_UNGO & _map->getMap(_point.x + 1, _point.y - 1).terrain) != ATTRIBUTE_UNGO)
						{
							_isMove = true;
							_movePoint = PointMake(_point.x + 1, _point.y - 1);
							_right = true;
						}
						break;
					case 2:
						//������
						//if (_map->getMap(_point.x + 1, _point.y).obj == OBJ_NONE &&
						//	(_map->getMap(_point.x + 1, _point.y).terrain == TERRAIN_FLOOR ||
						//		_map->getMap(_point.x + 1, _point.y).terrain == TERRAIN_GRASS))
						if ((ATTRIBUTE_UNGO & _map->getMap(_point.x + 1, _point.y).terrain) != ATTRIBUTE_UNGO)
						{
							_isMove = true;
							_movePoint = PointMake(_point.x + 1, _point.y);
							_right = true;
						}
						break;
					case 3:
						//������ �Ʒ�
						//if (_map->getMap(_point.x + 1, _point.y + 1).obj == OBJ_NONE &&
						//	(_map->getMap(_point.x + 1, _point.y + 1).terrain == TERRAIN_FLOOR ||
						//		_map->getMap(_point.x + 1, _point.y + 1).terrain == TERRAIN_GRASS))
						if ((ATTRIBUTE_UNGO & _map->getMap(_point.x + 1, _point.y + 1).terrain) != ATTRIBUTE_UNGO)
						{
							_isMove = true;
							_movePoint = PointMake(_point.x + 1, _point.y + 1);
							_right = true;
						}
						break;
					case 4:
						//�Ʒ�
						//if (_map->getMap(_point.x, _point.y + 1).obj == OBJ_NONE &&
						//	(_map->getMap(_point.x, _point.y + 1).terrain == TERRAIN_FLOOR ||
						//		_map->getMap(_point.x, _point.y + 1).terrain == TERRAIN_GRASS))
						if ((ATTRIBUTE_UNGO & _map->getMap(_point.x, _point.y + 1).terrain) != ATTRIBUTE_UNGO)
						{
							_isMove = true;
							_movePoint = PointMake(_point.x, _point.y + 1);
							_right = false;
						}
						break;
					case 5:
						//���� �Ʒ�
						//if (_map->getMap(_point.x - 1, _point.y + 1).obj == OBJ_NONE &&
						//	(_map->getMap(_point.x - 1, _point.y + 1).terrain == TERRAIN_FLOOR ||
						//		_map->getMap(_point.x - 1, _point.y + 1).terrain == TERRAIN_GRASS))
						if ((ATTRIBUTE_UNGO & _map->getMap(_point.x - 1, _point.y + 1).terrain) != ATTRIBUTE_UNGO)
						{
							_isMove = true;
							_movePoint = PointMake(_point.x - 1, _point.y + 1);
							_right = false;
						}
						break;
					case 6:
						//����
						//if (_map->getMap(_point.x - 1, _point.y).obj == OBJ_NONE &&
						//	(_map->getMap(_point.x - 1, _point.y).terrain == TERRAIN_FLOOR ||
						//		_map->getMap(_point.x - 1, _point.y).terrain == TERRAIN_GRASS))
						if ((ATTRIBUTE_UNGO & _map->getMap(_point.x - 1, _point.y).terrain) != ATTRIBUTE_UNGO)
						{
							_isMove = true;
							_movePoint = PointMake(_point.x - 1, _point.y);
							_right = false;
						}
						break;
					case 7:
						//���� ��
						//if (_map->getMap(_point.x - 1, _point.y - 1).obj == OBJ_NONE &&
						//	(_map->getMap(_point.x - 1, _point.y - 1).terrain == TERRAIN_FLOOR ||
						//		_map->getMap(_point.x - 1, _point.y - 1).terrain == TERRAIN_GRASS))
						if ((ATTRIBUTE_UNGO & _map->getMap(_point.x - 1, _point.y - 1).terrain) != ATTRIBUTE_UNGO)
						{
							_isMove = true;
							_movePoint = PointMake(_point.x - 1, _point.y - 1);
							_right = false;
						}
						break;
					default:
						_action = false;
						_myState = ENEMYSTATE_IDLE;
						break;
					}
				}
			}
		}
		else
		{
			//���� �߰������� A*�� �̿��� ������Ʈ�� �̵��Ѵ�
			//�ٷ� ��ĭ�̸� ���� �����ϴ�
			int x = _point.x - _player->getPoint().x / TILESIZE;
			int y = _point.y - _player->getPoint().y / TILESIZE;
			//���� x, y�� ������ ���밪�� ���� 1 ������ ��� ���� ����
			if ((x <= 1 && x >= -1) && (y <= 1 && y >= -1))
			{
				_myState = ENEMYSTATE_ATTACK;
				_currntFrameX = 0;
				_statistics.str = RND->getFromIntTo(2, 12);
				_player->getDamaged(_statistics.str);
				_player->addDebuff(DEBUFF_BLEEDING, 2000, 1);
				if (_PumpedUP == true) _trunCount++;
			}
			else if ((x <= 2 && x >= -2) && (y <= 2 && y >= -2) && _PumpedUP == true && _trunCount >= 2)
			{
				_myState = ENEMYSTATE_ATTACK;
				_currntFrameX = 0;
				_statistics.str = RND->getFromIntTo(11, 30);
				_player->getDamaged(_statistics.str*2);
				_player->addDebuff(DEBUFF_BLEEDING, 2000, 1);

				_PumpedUP = false;
				_trunCount = 0;
			}
			else
			{
				//�ƴ϶�� astar�� �̵��Ѵ�
				aStar = _map->aStar(PointMake(_pointX, _pointY), _player->getPoint());
				//�����϶� �ش� ��ǥ�� 4,5 ���� ������ �ָ� �ڵ����� 4*TILESIZE + TILESIZE/2, 5*... ����
				//_movePoint = PointMake(astarTest[astarTest.size() - 1].destX, astarTest[astarTest.size() - 1].destY);
				if (aStar.size() > 2)
					_movePoint = PointMake(aStar[aStar.size() - 2].destX, aStar[aStar.size() - 2].destY);
				else
					_movePoint = _point;
				_myState = ENEMYSTATE_MOVE;
			}
		}
	}
	else if (_myState == ENEMYSTATE_MOVE)
	{
		//��ǥ�� �־������� �ش� ��ǥ�� �����Ѵ�
		//�߽���ǥ�� ���Ѵ�
		float x = _movePoint.x * TILESIZE + TILESIZE / 2;
		float y = _movePoint.y * TILESIZE + TILESIZE / 2;

		//�߽���ǥ�� �����ߴ��� Ȯ���Ѵ�
		if ((static_cast<float>(_pointX) >= x - 4 && static_cast<float>(_pointX) <= x + 4) &&
			(static_cast<float>(_pointY) >= y - 4 && static_cast<float>(_pointY) <= y + 4))
		{
			//���� �����ϰ� �Ѱ��ش�
			_point = _movePoint;
			_pointX = x;
			_pointY = y;
			_isMove = false;
			_myState = ENEMYSTATE_IDLE;
			_action = false;
		}
		else
		{
			//_point.x += cosf(getAngle(_point.x, _point.y, _movePoint.x, _movePoint.y)) * 3;
			//_point.y -= sinf(getAngle(_point.x, _point.y, _movePoint.x, _movePoint.y)) * 3;
			//_action = false;

			//�������� �ʾ����� �̵��Ѵ�
			if (_pointX < x)
			{
				//���� ��ǥ�� ������ ��ǥ�� �߽ɺ��� ������ +
				_right = true;
				_pointX += TILESIZE / 4;
			}
			else if (_pointX > x)
			{
				_right = false;
				_pointX -= TILESIZE / 4;
			}

			if (_pointY < y)
			{
				_pointY += TILESIZE / 4;
			}
			else if (_pointY > y)
			{
				_pointY -= TILESIZE / 4;
			}
			//_action = false;

		}
	}


	frameUpdate();
}

void goo::update()
{
	if (_map->getCurStageNum() == _floor)
	{
		if (_currntHp <= 0)
		{
			_myState = ENEMYSTATE_DEAD;

			_deadAlpha += 25;
			_action = false;
			if (_deadAlpha >= 255)
			{
				_player->expUp(_statistics.exp);
				_deadAlpha = 255;
				_isLive = false;
				_action = false;

				int identifyPercent = RND->getInt(1);//50% Ȯ���� Ȯ�ε� ������
				bool identify;

				if (identifyPercent == 0)identify = false;
				else identify = true;

				int isCursedPercent = RND->getInt(1);//50% Ȯ���� ���ֹ���
				bool isCursed;
				if (isCursedPercent == 0)isCursed = false;
				else isCursed = true;

				int upgrade = RND->getInt(2);//���׷��̵� ��ġ

				int item = RND->getInt(2);
				if (item == 0)
					_im->setItemToField(NAME_OLD_SHORT_SWORD, _pointX, _pointY, identify, isCursed, upgrade, 1, _map->getCurStageNum());
			}
		}

		if (_action && _currntHp > 0 && _isLive) action();

		_hpBar->setGauge(_currntHp, _statistics.hp);
		_hpBar->update();

	}
	else _action = false;

}