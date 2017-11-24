#include "stdafx.h"
#include "Swarm.h"
#include "Player.h"
#include "UI.h"
#include "Map.h"

Swarm::Swarm()
{
}


Swarm::~Swarm()
{
}

HRESULT Swarm::init(POINT point)
{
	_point = point;

	_move = new image;
	_move->init("Img\\Enemy\\swarm_stay.bmp", 264, 56, 11, 2, true, RGB(255, 0, 255));
	_dead = new image;
	_dead->init("Img\\Enemy\\swarm_dead.bmp", 96, 60, 4, 2, true, RGB(255, 0, 255));

	_image = _move;

	_pointX = _point.x * TILESIZE + TILESIZE / 2;
	_pointY = _point.y * TILESIZE + TILESIZE / 2;

	_hitBox = RectMakeCenter(_pointX, _pointY, _image->getFrameWidth(), _image->getFrameHeight());
	_attBox = RectMakeCenter(_pointX, _pointY, 0, 0);
	_isLive = true;
	_findPlayer = false;
	int a = RND->getInt(2);
	if (a == 0) _right = true;
	else _right = false;

	_currntFrameX = 0;
	if (_right) _currntFrameY = 0;
	else _currntFrameY = 1;

	_image->setFrameX(_currntFrameX);
	_image->setFrameY(_currntFrameY);

	_action = false;
	_isMove = false;

	_statistics.lv = 1;
	_statistics.maxLv = 10;
	_statistics.exp = 1;
	_statistics.hp = 80;
	_currntHp = 80;
	_statistics.avd_lck = 5;
	_statistics.def = 0;
	a = RND->getFromIntTo(1, 4);
	_statistics.str = a;
	_statistics.atk_lck = 12;
	
	a = RND->getInt(2);
	if (a == 0) _myState = ENEMYSTATE_SLEEP;
	else _myState = ENEMYSTATE_IDLE;

	_movePoint = PointMake(0, 0);
	_frameCount = 0;

	/*ENEMYSTATE_SLEEP,	//�÷��̾ ã�� ���ѻ���/�������
	ENEMYSTATE_IDLE,	//�÷��̾ ã�� ���¿����� �⺻
	ENEMYSTATE_MOVE,
	ENEMYSTATE_ATTACK,
	ENEMYSTATE_END*/

	return S_OK;
}
HRESULT Swarm::init(POINT point, int currntHp)
{
	//�п��ߴ�!
	_point = point;

	_move = new image;
	_move->init("Img\\Enemy\\swarm_stay.bmp", 264, 56, 11, 2, true, RGB(255, 0, 255));
	_dead = new image;
	_dead->init("Img\\Enemy\\swarm_dead.bmp", 96, 60, 4, 2, true, RGB(255, 0, 255));

	_image = _move;

	_pointX = _point.x * TILESIZE + TILESIZE / 2;
	_pointY = _point.y * TILESIZE + TILESIZE / 2;

	_hitBox = RectMakeCenter(_pointX, _pointY, _image->getFrameWidth(), _image->getFrameHeight());
	_attBox = RectMakeCenter(_pointX, _pointY, 0, 0);
	_isLive = true;
	//���ݴ��� �п����ѰŴ� �̹� �߰��� ����
	_findPlayer = true;
	int a = RND->getInt(2);
	if (a == 0) _right = true;
	else _right = false;

	_currntFrameX = 0;
	if (_right) _currntFrameY = 0;
	else _currntFrameY = 1;

	_image->setFrameX(_currntFrameX);
	_image->setFrameY(_currntFrameY);

	_action = false;
	_isMove = false;

	_statistics.lv = 1;
	_statistics.maxLv = 10;
	_statistics.exp = 1;
	_statistics.hp = 80;
	_currntHp = currntHp;
	_statistics.avd_lck = 5;
	_statistics.def = 0;
	a = RND->getFromIntTo(1, 4);
	_statistics.str = a;
	_statistics.atk_lck = 12;
	
	//�̹� ���ݴ������� ���´� ������ �߰��� ����
	_myState = ENEMYSTATE_IDLE;


	_movePoint = PointMake(0, 0);
	_frameCount = 0;

	/*ENEMYSTATE_SLEEP,	//�÷��̾ ã�� ���ѻ���/�������
	ENEMYSTATE_IDLE,	//�÷��̾ ã�� ���¿����� �⺻
	ENEMYSTATE_MOVE,
	ENEMYSTATE_ATTACK,
	ENEMYSTATE_END*/

	return S_OK;
}

void Swarm::action()
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

void Swarm::frameUpdate()
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
		case ENEMYSTATE_SLEEP:	case ENEMYSTATE_IDLE:
			_image = _move;
			_currntFrameX = 0;
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
		}
	}

	_hitBox = RectMakeCenter(_pointX, _pointY, _image->getFrameWidth(), _image->getFrameHeight());
}

void Swarm::getDamaged(int damage)
{
	int a = RND->getInt(100);

	//0~99 �߿� ���� ���ڰ� ȸ�������� ���ٸ� ȸ��
	if (a < _statistics.avd_lck)
	{
		return;
	}
	else
	{
		//���ٸ� ��������
		_currntHp -= damage;
		if (_currntHp > 0)
		{
			//���� �ʾҴٸ� �п��� �ؾ��Ѵ�
			//�̰� ��� ����?->ENEMYMANAGER���� ó������
			//ENEMY�� swarm�� ������ �� �ִ� ���𰡸� �߰����ְ� ������ false, �길 true�� ���༭
			//�װ� true�� �п�, �ƴ� ���ΰ�
			
		}
		else
		{
			_isLive = false;
		}
	}
}


void Swarm::draw(POINT camera)
{
	_image->frameRender(getMemDC(), _hitBox.left + camera.x, _hitBox.top + camera.y);
}

void Swarm::release()
{
	SAFE_RELEASE(_image);
	SAFE_DELETE(_image);

	SAFE_RELEASE(_move);
	SAFE_DELETE(_move);
	
	SAFE_RELEASE(_dead);
	SAFE_DELETE(_dead);
}