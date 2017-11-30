#include "stdafx.h"
#include "Swarm.h"
#include "Player.h"
#include "EnemyManager.h"
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
	_move->init("Img//Enemy//swarm_stay.bmp", 264, 56, 11, 2, true, RGB(255, 0, 255));
	_dead = new image;
	_dead->init("Img//Enemy//swarm_dead.bmp", 96, 60, 4, 2, true, RGB(255, 0, 255));

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
	_active = false;

	_statistics.lv = 1;
	_statistics.maxLv = 10;
	_statistics.exp = 1;
	_statistics.hp = 12;
	_currntHp = 12;
	_statistics.avd_lck = 5;
	_statistics.def = 0;
	a = RND->getFromIntTo(1, 4);
	_statistics.str = a;
	_statistics.atk_lck = 12;
	
	a = RND->getInt(2);
	if (a == 0) _myState = ENEMYSTATE_SLEEP;
	else _myState = ENEMYSTATE_IDLE;
	_myState = ENEMYSTATE_IDLE;

	_movePoint = PointMake(0, 0);
	_frameCount = 0;
	_deadAlpha = 0;

	/*ENEMYSTATE_SLEEP,	//�÷��̾ ã�� ���ѻ���/�������
	ENEMYSTATE_IDLE,	//�÷��̾ ã�� ���¿����� �⺻
	ENEMYSTATE_MOVE,
	ENEMYSTATE_ATTACK,
	ENEMYSTATE_END*/
	//_hpBar = new progressBar;
	//_hpBar->init(_pointX - 25, _pointY + _image->getFrameHeight() / 2 + 10, 30, 10);

	return S_OK;
}
HRESULT Swarm::init(POINT point, int currntHp)
{
	//�п��ߴ�!
	_point = point;

	_active = false;
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
	_deadAlpha = 0;

	/*ENEMYSTATE_SLEEP,	//�÷��̾ ã�� ���ѻ���/�������
	ENEMYSTATE_IDLE,	//�÷��̾ ã�� ���¿����� �⺻
	ENEMYSTATE_MOVE,
	ENEMYSTATE_ATTACK,
	ENEMYSTATE_END*/
	//_hpBar = new progressBar;
	//_hpBar->init(_pointX - 25, _pointY + _image->getFrameHeight() / 2 + 10, 30, 10);

	return S_OK;
}

void Swarm::action()
{
	if (!_active)
	{
		if (_map->getTile(_point.x, _point. y).tileview != TILEVIEW_NO)
		{
			_active = true;
		}
		_action = false;
		return;
	}

	//if (KEYMANAGER->isOnceKeyDown('E')) getDamaged(3);

	if (_myState == ENEMYSTATE_SLEEP)
	{
		float dis = getDistance(_player->getPoint().x / TILESIZE, _player->getPoint().y / TILESIZE, _point.x, _point.y);

		if (dis < 4)
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
						if((ATTRIBUTE_UNGO & _map->getMap(_point.x, _point.y - 1).terrain) != ATTRIBUTE_UNGO)
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
			if ((x <= 1 && x>= -1) && (y <= 1 && y >= -1))
			{
				_myState = ENEMYSTATE_ATTACK;
				_currntFrameX = 0;
				//_player->getDamaged(_statistics.str);
				//_action = false;
			}
			else
			{
				//�ƴ϶�� astar�� �̵��Ѵ�
				astarTest = _map->aStar(PointMake(_pointX, _pointY), _player->getPoint());
				//�����϶� �ش� ��ǥ�� 4,5 ���� ������ �ָ� �ڵ����� 4*TILESIZE + TILESIZE/2, 5*... ����
				//_movePoint = PointMake(astarTest[astarTest.size() - 1].destX, astarTest[astarTest.size() - 1].destY);
				_movePoint = PointMake(astarTest[astarTest.size() - 2].destX, astarTest[astarTest.size() - 2].destY);
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
				_pointX += TILESIZE / 8;
			}
			else if (_pointX > x)
			{
				_right = false;
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
			//_action = false;
			
		}
	}


	frameUpdate();
}

void Swarm::frameUpdate()
{
	//_frameCount++;

	if (_findPlayer)
	{
		if (_player->getPoint().x >= _point.x) _right = true;
		else _right = false;
	}
	if (_right) _currntFrameY = 0;
	else _currntFrameY = 1;
	
	if(true)
	//if (_frameCount >= 10)
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
		case ENEMYSTATE_ATTACK:
			//���ݽÿ��� ������ �� �Ѱ��ְ�
			_image = _move;
			_currntFrameX++;
			if (_currntFrameX > _image->getMaxFrameX())
			{
				_currntFrameX = 0;
				_myState = ENEMYSTATE_IDLE;
				_action = false;
			}
			_image->setFrameX(_currntFrameX);
			_image->setFrameY(_currntFrameY);
			break;
		}
	}

	_hitBox = RectMakeCenter(_pointX, _pointY, _image->getFrameWidth(), _image->getFrameHeight());
}

void Swarm::getDamaged(int damage)
{
	if (_myState == ENEMYSTATE_SLEEP)
		_myState = ENEMYSTATE_IDLE;
	_findPlayer = true;

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

			int x = 0;
			int y = 0;
			if (_player->getPoint().x / TILESIZE > _point.x)
				x = -1;
			else if (_player->getPoint().x / TILESIZE == _point.x)
				x = 0;
			else
				x = 1;

			if (_player->getPoint().y / TILESIZE > _point.y)
				y = -1;
			else if (_player->getPoint().y / TILESIZE == _point.y)
				y = 0;
			else
				y = 1;

			//if (_map->getMap(_point.x, _point.y - 1).obj == OBJ_NONE &&
			//	(_map->getMap(_point.x, _point.y - 1).terrain == TERRAIN_FLOOR ||
			//		_map->getMap(_point.x, _point.y - 1).terrain == TERRAIN_GRASS))
			//(ATTRIBUTE_UNGO & _map[v.x - 1][v.y].terrain) == ATTRIBUTE_UNGO
			if ((ATTRIBUTE_UNGO & _map->getMap(_point.x + x, _point.y + y).terrain) != ATTRIBUTE_UNGO)
				//_em->setSwarm(PointMake(_point.x + x, _point.y + y), _currntHp);
				_em->setSwarmSpawn(PointMake(_point.x + x, _point.y + y), _currntHp);
		}
	}
}


void Swarm::draw(POINT camera)
{
	//_hpBar->setGauge(_currntHp, _statistics.hp);
	//�þ߿� ���϶��� ����ϰ�
	if (_map->getTile(_pointX / TILESIZE, _pointY / TILESIZE).tileview == TILEVIEW_ALL)
		_image->alphaFrameRender(getMemDC(), _hitBox.left + camera.x, _hitBox.top + camera.y, _deadAlpha);
	RectangleMakeCenter(getMemDC(), _pointX + camera.x, _pointY + camera.y, _currntHp, _currntHp);
	//if(_findPlayer)

	//_hpBar->setX(_point.x - 25 + camera.x);
	//_hpBar->setY(_pointY + _image->getFrameHeight() / 2 + 10 + camera.y);
	//if (_currntHp < _statistics.hp)
	//	_hpBar->render();
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

void Swarm::update()
{
	if (_currntHp <= 0)
	{
		_deadAlpha += 5;
		if (_deadAlpha >= 255)
		{
			_deadAlpha = 255;
			_isLive = false;
			_action = false;
		}
	}

	if (_action && _currntHp > 0 && _isLive) action();
}