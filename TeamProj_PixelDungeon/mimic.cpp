#include "stdafx.h"
#include "mimic.h"
#include "Player.h"
#include "Map.h"
#include "UI.h"
#include "ItemManager.h"

Mimic::Mimic()
{
}


Mimic::~Mimic()
{
}

HRESULT Mimic::init(POINT point, int floor)
{
	//�Է¹��� ��ǥ�� �ʱ� ��ġ��
	_point = point;

	//�� �̹��� �����Ҵ�(MANAGER�� �� �Ȱ���������)
	move = new image;
	stay = new image;
	dead = new image;

	move->init("Img//Enemy//mimic//mimic_move.bmp", 64, 64, 2, 2, true, RGB(255, 0, 255));
	stay->init("Img//Enemy//mimic//mimic_stay.bmp", 160, 60, 5, 2, true, RGB(255, 0, 255));
	dead->init("Img//Enemy//mimic//mimic_dead.bmp", 128, 64, 4, 2, true, RGB(255, 0, 255));

	//�ʱ� ������ stay
	_image = stay;

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
	_statistics.maxLv = 8;
	_statistics.exp = 2;
	_statistics.hp = 12;
	_currntHp = 12;
	_statistics.avd_lck = 4;
	_statistics.def = 2;
	a = RND->getFromIntTo(2, 5);
	_statistics.str = a;
	_statistics.atk_lck = 11;

	//Ƣ��Դ�!
	 _myState = ENEMYSTATE_IDLE;

	//�ʱⰪ ����
	_movePoint = PointMake(0, 0);
	_frameFPS = 10;
	_frameTime = 0;
	_deadAlpha = 0;
	_active = false;
	_playerChack = true;

	_floor = floor;

	/*ENEMYSTATE_SLEEP,	//�÷��̾ ã�� ���ѻ���/�������
	ENEMYSTATE_IDLE,	//�÷��̾ ã�� ���¿����� �⺻
	ENEMYSTATE_MOVE,
	ENEMYSTATE_ATTACK,
	ENEMYSTATE_END*/

	//_hpBar = new progressBar;
	//_hpBar->init(_pointX - 25, _pointY + _image->getFrameHeight() / 2 + 10, 30, 10);

	return S_OK;
}

void Mimic::release()
{
	SAFE_RELEASE(_image);
	SAFE_DELETE(_image);

	SAFE_RELEASE(move);
	SAFE_DELETE(move);
	SAFE_RELEASE(stay);
	SAFE_DELETE(stay);
	SAFE_RELEASE(dead);
	SAFE_DELETE(dead);
}


void Mimic::getDamaged(int damage)
{
	//�̹��� ��� �ʿ��� ���� Ȯ���� ���Ͽ� ���ڿ��� ������ ������
	//�̹� ��Ų �����̱⿡ ENEMYSTATE_SLEEP ���°� �������� �ʴ´�.

	int a = RND->getInt(100);

	//ui�� ȸ�� �ߴٰ� ���������� ���ڴµ�
	if (a < _statistics.avd_lck) return;
	else
	{
		money = RND->getFromIntTo(1, 99999);

		if (_currntHp > 0)
			_currntHp -= damage - _statistics.def;
		int hitGift = RND->getInt(9);
		if (hitGift == 0)
		{
			_im->setItemToField(NAME_MONEY, _pointX, _pointY, false, false, 0, money,_map->getCurStageNum());
		}
	}
}

void Mimic::draw(POINT camera)
{
	//_hpBar->setGauge(_currntHp, _statistics.hp);
	//�þ߿� ���϶��� ����ϰ�
	if (_map->getCurStageNum() == _floor)
	{
		if (_map->getTile(_pointX / TILESIZE, _pointY / TILESIZE).tileview == TILEVIEW_ALL)
			_image->alphaFrameRender(getMemDC(), _hitBox.left + camera.x, _hitBox.top + camera.y, _deadAlpha);
	}
	//RectangleMakeCenter(getMemDC(), _pointX + camera.x, _pointY + camera.y, _currntHp, _currntHp);
	//if(_findPlayer)

	//_hpBar->setX(_point.x - 25 + camera.x);
	//_hpBar->setY(_pointY + _image->getFrameHeight() / 2 + 10 + camera.y);
	//if (_currntHp < _statistics.hp)
	//	_hpBar->render();
}


void Mimic::frameUpdate()
{
	//_frameCount++;

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
		//case ENEMYSTATE_SLEEP:
		//	_image = stay;
		//	_currntFrameX = 0;
		//	_image->setFrameX(_currntFrameX);
		//	_image->setFrameY(_currntFrameY);
		//	break;
		case ENEMYSTATE_IDLE:
			_image = stay;
			_currntFrameX++;
			if (_currntFrameX > _image->getMaxFrameX()) _currntFrameX = 0;
			_image->setFrameX(_currntFrameX);
			_image->setFrameY(_currntFrameY);
			break;
		case ENEMYSTATE_MOVE:
			_image = move;
			_currntFrameX++;
			if (_currntFrameX > _image->getMaxFrameX()) _currntFrameX = 0;
			_image->setFrameX(_currntFrameX);
			_image->setFrameY(_currntFrameY);
			break;
		case ENEMYSTATE_ATTACK:
			_image = move;
			_currntFrameX++;
			if (_currntFrameX > _image->getMaxFrameX())
			{
				_currntFrameX = 0;
				_myState = ENEMYSTATE_IDLE;
				_image = move;
				_action = false;
			}
			_image->setFrameX(_currntFrameX);
			_image->setFrameY(_currntFrameY);
			break;
		case ENEMYSTATE_DEAD:

			_image = dead;
			_currntFrameX++;
			if (_currntFrameX >= _image->getMaxFrameX())
			{
				_currntFrameX = _image->getMaxFrameX();
			}

			_image->setFrameX(_currntFrameX);
			_image->setFrameY(_currntFrameY);


			break;

		}
	}

	_hitBox = RectMakeCenter(_pointX, _pointY, _image->getFrameWidth(), _image->getFrameHeight());
}

void Mimic::action()
{
	if (!_active)
	{
		if (_map->getTile(_point.x, _point.y).tileview != TILEVIEW_NO)
		{
			_active = true;
		}
		_action = false;
		return;
	}

	if (KEYMANAGER->isOnceKeyDown('E')) getDamaged(500);

	//if (_myState == ENEMYSTATE_SLEEP)
	//{
	//	float dis = getDistance(_player->getPoint().x / TILESIZE, _player->getPoint().y / TILESIZE, _point.x, _point.y);
	//
	//	if (dis < 4)
	//	{
	//		_myState = ENEMYSTATE_IDLE;
	//		_findPlayer = true;
	//		_action = false;
	//	}
	//	else
	//		_action = false;
	//}
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
				_player->getDamaged(_statistics.str);
				//_action = false;
			}
			else
			{
				//�ƴ϶�� astar�� �̵��Ѵ�
				astar = aStar(PointMake(_pointX, _pointY), _player->getPoint());
				//�����϶� �ش� ��ǥ�� 4,5 ���� ������ �ָ� �ڵ����� 4*TILESIZE + TILESIZE/2, 5*... ����
				//_movePoint = PointMake(astarTest[astarTest.size() - 1].destX, astarTest[astarTest.size() - 1].destY);
				if (astar.size() > 2)
					_movePoint = PointMake(astar[astar.size() - 2].destX, astar[astar.size() - 2].destY);
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

void Mimic::update()
{
	if (_map->getCurStageNum() == _floor)
	{
		if (_currntHp <= 0)
		{
			_myState = ENEMYSTATE_DEAD;

			_deadAlpha += 15;
			_action = false;
			if (_deadAlpha >= 255)
			{
				_deadAlpha = 255;
				_isLive = false;
				_action = false;
				dropitem();
			}

		}

		if (_action && _currntHp > 0 && _isLive) action();
	}
	else _action = false;
}
void Mimic::dropitem()
{
	money = RND->getFromIntTo(1, 99999);

	int item = RND->getFromIntTo(NAME_OLD_SHORT_SWORD, NAME_MONEY);//�����ϰ� �������� ��´�
	//int item = RND->getFromIntTo(NAME_OLD_SHORT_SWORD, NAME_OLD_SHORT_SWORD);//�����ϰ� �������� ��´�

	int identifyPercent = RND->getInt(1);//50% Ȯ���� Ȯ�ε� ������
	bool identify;

	if (identifyPercent == 0)identify = false;
	else identify = true;

	int isCursedPercent = RND->getInt(1);//50% Ȯ���� ���ֹ���
	bool isCursed;
	if (isCursedPercent == 0)isCursed = false;
	else isCursed = true;

	int upgrade = RND->getInt(2);//���׷��̵� ��ġ

	switch (item)
	{
		//����
	case NAME_OLD_SHORT_SWORD:
		//������ �̸�			��ġX		��ġY	Ȯ�ο��� ���ֿ��� ���׷��̵� ����
		_im->setItemToField(NAME_OLD_SHORT_SWORD, _pointX, _pointY, identify, isCursed, upgrade,1, _map->getCurStageNum());
		break;

	case NAME_SHORT_SWORD:
		_im->setItemToField(NAME_SHORT_SWORD, _pointX, _pointY, identify, isCursed, upgrade, 1, _map->getCurStageNum());
		break;

	case NAME_SWORD:
		_im->setItemToField(NAME_SWORD, _pointX, _pointY, identify, isCursed, upgrade, 1, _map->getCurStageNum());

		break;
	case NAME_SPEAR:
		_im->setItemToField(NAME_SPEAR, _pointX, _pointY, identify, isCursed, upgrade, 1, _map->getCurStageNum());

		break;
	case NAME_BATTLE_AXE:
		_im->setItemToField(NAME_BATTLE_AXE, _pointX, _pointY, identify, isCursed, upgrade, 1, _map->getCurStageNum());

		break;

		//��
	case NAME_CLOTH:
		_im->setItemToField(NAME_CLOTH, _pointX, _pointY, identify, isCursed, upgrade, 1, _map->getCurStageNum());

		break;
	case NAME_LEATHER:
		_im->setItemToField(NAME_LEATHER, _pointX, _pointY, identify, isCursed, upgrade, 1, _map->getCurStageNum());

		break;
	case NAME_MAIL:
		_im->setItemToField(NAME_MAIL, _pointX, _pointY, identify, isCursed, upgrade, 1, _map->getCurStageNum());

		break;

		//�Ǽ��縮
	case NAME_RING_POWER:
		_im->setItemToField(NAME_RING_POWER, _pointX, _pointY, identify, isCursed, upgrade, 1, _map->getCurStageNum());

		break;
	case NAME_RING_RECHARGE:
		_im->setItemToField(NAME_RING_RECHARGE, _pointX, _pointY, identify, isCursed, upgrade, 1, _map->getCurStageNum());

		break;
	case NAME_LIOYDS_BEACON:
		_im->setItemToField(NAME_LIOYDS_BEACON, _pointX, _pointY, identify, isCursed, upgrade, 1, _map->getCurStageNum());

		break;

		//��ô
	case NAME_DART:
		_im->setItemToField(NAME_DART, _pointX, _pointY, identify, isCursed, upgrade, 1, _map->getCurStageNum());

		break;
	case NAME_PARALYSIS_DART:
		_im->setItemToField(NAME_PARALYSIS_DART, _pointX, _pointY, identify, isCursed, upgrade, 1, _map->getCurStageNum());

		break;
	case NAME_POISON_DART:
		_im->setItemToField(NAME_POISON_DART, _pointX, _pointY, identify, isCursed, upgrade, 1, _map->getCurStageNum());

		break;
		//�ϵ�
	case NAME_LIGHTNING:
		_im->setItemToField(NAME_LIGHTNING, _pointX, _pointY, identify, isCursed, upgrade, 1, _map->getCurStageNum());

		break;
	case NAME_NORMAL:
		_im->setItemToField(NAME_NORMAL, _pointX, _pointY, identify, isCursed, upgrade, 1, _map->getCurStageNum());

		break;
	case NAME_POISON:
		_im->setItemToField(NAME_POISON, _pointX, _pointY, identify, isCursed, upgrade, 1, _map->getCurStageNum());

		break;

		//����
		//���ĵ��� �����۷��� ��ġ�� ������ �ݴϴ�. ���ֹ��� �Ľ�Ÿ ������ ���ø��� ���� ���� �ֹ����� ���൵ �����մϴ�.
	case NAME_EMERGENCY:
		_im->setItemToField(NAME_EMERGENCY, _pointX, _pointY);

		break;
	case NAME_PASTY:
		_im->setItemToField(NAME_PASTY, _pointX, _pointY);

		break;
	case NAME_UNKNOWN_MEAT:
		_im->setItemToField(NAME_UNKNOWN_MEAT, _pointX, _pointY);

		break;
	case NAME_COOKED_MEAT:
		_im->setItemToField(NAME_COOKED_MEAT, _pointX, _pointY);

		break;
	case NAME_FROZEN_MEAT:
		_im->setItemToField(NAME_FROZEN_MEAT, _pointX, _pointY);

		break;

		//�ֹ���
	case NAME_IDENTIFY:
		_im->setItemToField(NAME_IDENTIFY, _pointX, _pointY);

		break;
	case NAME_UPGRADE:
		_im->setItemToField(NAME_UPGRADE, _pointX, _pointY);

		break;
	case NAME_PURIFY:
		_im->setItemToField(NAME_PURIFY, _pointX, _pointY);

		break;
	case NAME_MAP:
		_im->setItemToField(NAME_MAP, _pointX, _pointY);

		break;

		//����
	case NAME_RECHARGE:
		_im->setItemToField(NAME_RECHARGE, _pointX, _pointY);

		break;
	case NAME_BOTTLE:
		_im->setItemToField(NAME_BOTTLE, _pointX, _pointY);

		break;
	case NAME_HEAL:
		_im->setItemToField(NAME_HEAL, _pointX, _pointY);

		break;
	case NAME_STR:
		_im->setItemToField(NAME_STR, _pointX, _pointY);

		break;
	case NAME_EX:
		_im->setItemToField(NAME_EX, _pointX, _pointY);

		break;
	case NAME_INVISIBLE:
		_im->setItemToField(NAME_INVISIBLE, _pointX, _pointY);

		break;
	case NAME_LEVITATION:
		_im->setItemToField(NAME_LEVITATION, _pointX, _pointY);

		break;
	case NAME_FROZEN:
		_im->setItemToField(NAME_FROZEN, _pointX, _pointY);

		break;
	case NAME_LIQUID_FIRE:
		_im->setItemToField(NAME_LIQUID_FIRE, _pointX, _pointY);

		break;
	case NAME_SEED_HEAL:
		_im->setItemToField(NAME_SEED_HEAL, _pointX, _pointY);

		break;
	case NAME_SEED_FIRE:
		_im->setItemToField(NAME_SEED_FIRE, _pointX, _pointY);

		break;
	case NAME_SEED_SNAKE:
		_im->setItemToField(NAME_SEED_SNAKE, _pointX, _pointY);

		break;
	case NAME_SEED_FROST:
		_im->setItemToField(NAME_SEED_FROST, _pointX, _pointY);

		break;
	case NAME_DEW:
		_im->setItemToField(NAME_DEW, _pointX, _pointY);

		break;

		//���� �Ӵ� ���������� �̿��մϴ�
	case NAME_MONEY:
		_im->setItemToField(NAME_MONEY, _pointX, _pointY, false, false, 0, money, _map->getCurStageNum());

		break;
	}

}