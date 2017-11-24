#include "stdafx.h"
#include "Gnoll.h"
#include "Player.h"
#include "Map.h"
#include "UI.h"

Gnoll::Gnoll()
{
}


Gnoll::~Gnoll()
{
}

HRESULT Gnoll::init(POINT point)
{
	//�Է¹��� ��ǥ�� �ʱ� ��ġ��
	_point = point;

	//�� �̹��� �����Ҵ�(MANAGER�� �� �Ȱ���������)
	_stay = new image;
	_stay->init("Img\\Enemy\\gnoll_stay.bmp", 44, 60, 2, 2, true, RGB(255, 0, 255));
	_move = new image;
	_move->init("Img\\Enemy\\gnoll_move.bmp", 88, 60, 4, 2, true, RGB(255, 0, 255));
	_attack->init("Img\\Enemy\\gnoll_attack.bmp", 48, 60, 2, 2, true, RGB(255, 0, 255));
	_dead = new image;
	_dead->init("Img\\Enemy\\gnoll_dead.bmp", 84, 52, 3, 2, true, RGB(255, 0, 255));

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
	_statistics.maxLv = 8;
	_statistics.exp = 2;
	_statistics.hp = 12;
	_currntHp = 12;
	_statistics.avd_lck = 4;
	_statistics.def = 2;
	a = RND->getFromIntTo(2, 5);
	_statistics.str = a;
	_statistics.atk_lck = 11;

	//���������� �ڰ������� ���� ����
	a = RND->getInt(2);
	if (a == 0) _myState = ENEMYSTATE_SLEEP;
	else _myState = ENEMYSTATE_IDLE;

	//�ʱⰪ ����
	_movePoint = PointMake(0, 0);
	_frameCount = 0;

	/*ENEMYSTATE_SLEEP,	//�÷��̾ ã�� ���ѻ���/�������
	ENEMYSTATE_IDLE,	//�÷��̾ ã�� ���¿����� �⺻
	ENEMYSTATE_MOVE,
	ENEMYSTATE_ATTACK,
	ENEMYSTATE_END*/

	return S_OK;
}

void Gnoll::release()
{
	SAFE_RELEASE(_image);
	SAFE_DELETE(_image);

	SAFE_RELEASE(_stay);
	SAFE_DELETE(_stay);

	SAFE_RELEASE(_move);
	SAFE_DELETE(_move);

	SAFE_RELEASE(_attack);
	SAFE_DELETE(_attack);

	SAFE_RELEASE(_dead);
	SAFE_DELETE(_dead);
}


void Gnoll::getDamaged(int damage)
{
	_currntHp -= damage;
}

void Gnoll::draw(POINT camera)
{
	_image->frameRender(getMemDC(), _hitBox.left + camera.x, _hitBox.top + camera.y);
}


void Gnoll::frameUpdate()
{
	_frameCount++;

	if (_findPlayer)
	{
		if (_player->getPoint().x >= _point.x) _right = true;
		else _right = false;
	}
	if (_right) _currntFrameY = 0;
	else _currntFrameY = 1;

	if (_frameCount >= 10)
	{
		_frameCount = 0;
		switch (_myState)
		{
		case ENEMYSTATE_SLEEP:
			_image = _stay;
			_currntFrameX = 0;
			_image->setFrameX(_currntFrameX);
			_image->setFrameY(_currntFrameY);
			break;
		case ENEMYSTATE_IDLE:
			_image = _stay;
			_currntFrameX++;
			if (_currntFrameX > _image->getMaxFrameX()) _currntFrameX = 0;
			_image->setFrameX(_currntFrameX);
			_image->setFrameY(_currntFrameY);
			break;
		case ENEMYSTATE_MOVE:
			_image = _move;
			_currntFrameX++;
			if (_currntFrameX > _image->getMaxFrameX()) _currntFrameX = 0;
			_image->setFrameX(_currntFrameX);
			_image->setFrameY(_currntFrameY);
			break;
		case ENEMYSTATE_ATTACK:
			_image = _attack;
			_currntFrameX++;
			if (_currntFrameX > _image->getMaxFrameX())
			{
				_currntFrameX = 0;
				_myState = ENEMYSTATE_IDLE;
				_image = _stay;
			}
			_image->setFrameX(_currntFrameX);
			_image->setFrameY(_currntFrameY);
			break;
		}
	}

	_hitBox = RectMakeCenter(_pointX, _pointY, _image->getFrameWidth(), _image->getFrameHeight());
}

void Gnoll::action()
{
	if (_myState == ENEMYSTATE_SLEEP)
	{
		float dis = getDistance(_player->getPoint().x, _player->getPoint().y, _point.x, _point.y);

		if (dis < 2)
		{
			_myState = ENEMYSTATE_IDLE;
			_findPlayer = true;
			_action = false;
		}
		else
			_action = false;
	}
	else if (_myState == ENEMYSTATE_IDLE)
	{
		if (!_findPlayer)
		{
			//���� �߰����� �ʾ����� �����ൿ

			float dis = getDistance(_player->getPoint().x, _player->getPoint().y, _point.x, _point.y);

			if (dis < 2)
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
					_myState = ENEMYSTATE_MOVE;
					switch (a)
					{
					case 0:
						//��
						if (_map->getMap(_point.x, _point.y - 1).obj == OBJ_NONE &&
							(_map->getMap(_point.x, _point.y - 1).terrain == TERRAIN_FLOOR ||
								_map->getMap(_point.x, _point.y - 1).terrain == TERRAIN_GRASS))
						{
							_isMove = true;
							_movePoint = PointMake(_point.x, _point.y - 1);
							_right = false;
						}
						break;
					case 1:
						//������ ��
						if (_map->getMap(_point.x + 1, _point.y - 1).obj == OBJ_NONE &&
							(_map->getMap(_point.x + 1, _point.y - 1).terrain == TERRAIN_FLOOR ||
								_map->getMap(_point.x + 1, _point.y - 1).terrain == TERRAIN_GRASS))
						{
							_isMove = true;
							_movePoint = PointMake(_point.x + 1, _point.y - 1);
							_right = true;
						}
						break;
					case 2:
						//������
						if (_map->getMap(_point.x + 1, _point.y).obj == OBJ_NONE &&
							(_map->getMap(_point.x + 1, _point.y).terrain == TERRAIN_FLOOR ||
								_map->getMap(_point.x + 1, _point.y).terrain == TERRAIN_GRASS))
						{
							_isMove = true;
							_movePoint = PointMake(_point.x + 1, _point.y);
							_right = true;
						}
						break;
					case 3:
						//������ �Ʒ�
						if (_map->getMap(_point.x + 1, _point.y + 1).obj == OBJ_NONE &&
							(_map->getMap(_point.x + 1, _point.y + 1).terrain == TERRAIN_FLOOR ||
								_map->getMap(_point.x + 1, _point.y + 1).terrain == TERRAIN_GRASS))
						{
							_isMove = true;
							_movePoint = PointMake(_point.x + 1, _point.y + 1);
							_right = true;
						}
						break;
					case 4:
						//�Ʒ�
						if (_map->getMap(_point.x, _point.y + 1).obj == OBJ_NONE &&
							(_map->getMap(_point.x, _point.y + 1).terrain == TERRAIN_FLOOR ||
								_map->getMap(_point.x, _point.y + 1).terrain == TERRAIN_GRASS))
						{
							_isMove = true;
							_movePoint = PointMake(_point.x, _point.y + 1);
							_right = false;
						}
						break;
					case 5:
						//���� �Ʒ�
						if (_map->getMap(_point.x - 1, _point.y + 1).obj == OBJ_NONE &&
							(_map->getMap(_point.x - 1, _point.y + 1).terrain == TERRAIN_FLOOR ||
								_map->getMap(_point.x - 1, _point.y + 1).terrain == TERRAIN_GRASS))
						{
							_isMove = true;
							_movePoint = PointMake(_point.x - 1, _point.y + 1);
							_right = false;
						}
						break;
					case 6:
						//����
						if (_map->getMap(_point.x - 1, _point.y).obj == OBJ_NONE &&
							(_map->getMap(_point.x - 1, _point.y).terrain == TERRAIN_FLOOR ||
								_map->getMap(_point.x - 1, _point.y).terrain == TERRAIN_GRASS))
						{
							_isMove = true;
							_movePoint = PointMake(_point.x - 1, _point.y);
							_right = false;
						}
						break;
					case 7:
						//���� ��
						if (_map->getMap(_point.x - 1, _point.y - 1).obj == OBJ_NONE &&
							(_map->getMap(_point.x - 1, _point.y - 1).terrain == TERRAIN_FLOOR ||
								_map->getMap(_point.x - 1, _point.y - 1).terrain == TERRAIN_GRASS))
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
			//A* ���� �ȵ����� �̷�
		}
	}
	else if (_myState == ENEMYSTATE_MOVE)
	{
		//��ǥ�� �־������� �ش� ��ǥ�� �����Ѵ�
		//�߽���ǥ�� ���Ѵ�
		float x = _movePoint.x * TILESIZE + TILESIZE / 2;
		float y = _movePoint.y * TILESIZE + TILESIZE / 2;

		//�߽���ǥ�� �����ߴ��� Ȯ���Ѵ�
		if (static_cast<float>(_pointX) == x &&
			static_cast<float>(_pointY) == y)
		{
			//���� �����ϰ� �Ѱ��ش�
			_isMove = false;
			_myState = ENEMYSTATE_IDLE;
			_action = false;
		}
		else
		{
			//�������� �ʾ����� �̵��Ѵ�
			if (_pointX < x)
			{
				//���� ��ǥ�� ������ ��ǥ�� �߽ɺ��� ������ +
				_pointX += TILESIZE / 8;
			}
			else if (_pointX > x)
			{
				_pointX -= TILESIZE / 8;
			}

			if (_pointY < y)
			{
				_pointY += TILESIZE / 8;
			}
			else if (_pointY > y)
			{
				_pointY -= TILESIZE / 8;
			}

		}
	}


	frameUpdate();
}