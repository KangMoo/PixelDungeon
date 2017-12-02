#include "stdafx.h"
#include "Rat.h"
#include "Player.h"
#include "Map.h"
#include "UI.h"

Rat::Rat()
{
}


Rat::~Rat()
{
}

HRESULT Rat::init(POINT point)
{
	//�Է¹��� ��ǥ�� �ʱ� ��ġ��
	_point = point;

	_color = RND->getInt(3);

	_myColor = _color == 0 ? WHITE : BROWN;

	if (_myColor == BROWN)
	{
		bIdle = new image;
		bMove = new image;
		bAttack = new image;
		bDead = new image;

		bIdle->init("img//Enemy//rat//brownIdle.bmp", 64, 64, 2, 2, true, RGB(255, 0, 255));
		bMove->init("img//Enemy//rat//brownMove.bmp", 192, 64, 6, 2, true, RGB(255, 0, 255));
		bAttack->init("img//Enemy//rat//brownAttack.bmp", 96, 64, 3, 2, true, RGB(255, 0, 255));
		bDead->init("img//Enemy//rat//brownDead.bmp", 128, 64, 4, 2, true, RGB(255, 0, 255));

		_image = bIdle;

		_statistics.lv = 1;
		_statistics.maxLv = 5;
		_statistics.exp = 1;
		_statistics.hp = 7;
		_currntHp = 7;
		_statistics.avd_lck = 7;
		_statistics.def = 2;
		int a = RND->getFromIntTo(1, 4);
		_statistics.str = a;
		_statistics.atk_lck = 12;

	}
	else if(_myColor == WHITE)
	{
		wIdle = new image;
		wMove = new image;
		wAttack = new image;
		wDead = new image;

		wIdle->init("img//Enemy//rat//whiteIdle.bmp", 64, 64, 2, 2, true, RGB(255, 0, 255));
		wMove->init("img//Enemy//rat//whiteMove.bmp", 192, 64, 6, 2, true, RGB(255, 0, 255));
		wAttack->init("img//Enemy//rat//whiteAttack.bmp", 96, 64, 3, 2, true, RGB(255, 0, 255));
		wDead->init("img//Enemy//rat//whiteDead.bmp", 128, 64, 4, 2, true, RGB(255, 0, 255));

		_image = wIdle;

		_statistics.lv = 1;
		_statistics.maxLv = 5;
		_statistics.exp = 1;
		_statistics.hp = 7;
		_currntHp = 7;
		_statistics.avd_lck = 7;
		_statistics.def = 2;
		int a = RND->getFromIntTo(1, 4);
		_statistics.str = a;
		_statistics.atk_lck = 12;

	}


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

	//���������� �ڰ������� ���� ����
	a = RND->getInt(2);
	if (a == 0) _myState = ENEMYSTATE_SLEEP;
	else _myState = ENEMYSTATE_IDLE;

	//�ʱⰪ ����
	_movePoint = PointMake(0, 0);
	_frameFPS = 10;
	_frameTime = 0;
	_deadAlpha = 0;
	_active = false;

	/*ENEMYSTATE_SLEEP,	//�÷��̾ ã�� ���ѻ���/�������
	ENEMYSTATE_IDLE,	//�÷��̾ ã�� ���¿����� �⺻
	ENEMYSTATE_MOVE,
	ENEMYSTATE_ATTACK,
	ENEMYSTATE_END*/

	//_hpBar = new progressBar;
	//_hpBar->init(_pointX - 25, _pointY + _image->getFrameHeight() / 2 + 10, 30, 10);

	return S_OK;
}

void Rat::release()
{
	SAFE_RELEASE(_image);
	SAFE_DELETE(_image);

	SAFE_RELEASE(bIdle);
	SAFE_DELETE(bIdle);
	SAFE_RELEASE(bAttack);
	SAFE_DELETE(bAttack);
	SAFE_RELEASE(bMove);
	SAFE_DELETE(bMove);
	SAFE_RELEASE(bDead);
	SAFE_DELETE(bDead);

	SAFE_RELEASE(wIdle);
	SAFE_DELETE(wIdle);
	SAFE_RELEASE(wAttack);
	SAFE_DELETE(wAttack);
	SAFE_RELEASE(wMove);
	SAFE_DELETE(wMove);
	SAFE_RELEASE(wDead);
	SAFE_DELETE(wDead);
}


void Rat::getDamaged(int damage)
{
	if (_myState == ENEMYSTATE_SLEEP)
		_myState = ENEMYSTATE_IDLE;
	_findPlayer = true;

	int a = RND->getInt(100);

	if (a < _statistics.avd_lck - _player->getStat().atk_lck)
	{
		return;
	}
	else
	{
		if (_currntHp > 0)
			_currntHp -= damage - _statistics.def;
	}
}

void Rat::draw(POINT camera)
{
	//_hpBar->setGauge(_currntHp, _statistics.hp);
	//�þ߿� ���϶��� ����ϰ�
	if (_map->getTile(_pointX / TILESIZE, _pointY / TILESIZE).tileview == TILEVIEW_ALL)
		_image->alphaFrameRender(getMemDC(), _hitBox.left + camera.x, _hitBox.top + camera.y, _deadAlpha);
	//RectangleMakeCenter(getMemDC(), _pointX + camera.x, _pointY + camera.y, _currntHp, _currntHp);
	//if(_findPlayer)

	//_hpBar->setX(_point.x - 25 + camera.x);
	//_hpBar->setY(_pointY + _image->getFrameHeight() / 2 + 10 + camera.y);
	//if (_currntHp < _statistics.hp)
	//	_hpBar->render();
}


void Rat::frameUpdate()
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
		case ENEMYSTATE_SLEEP:
			if (_myColor == BROWN)
			{
				_image = bIdle;
				_currntFrameX = 0;
				_image->setFrameX(_currntFrameX);
				_image->setFrameY(_currntFrameY);
			}
			else if (_myColor == WHITE)
			{
				_image = wIdle;
				_currntFrameX = 0;
				_image->setFrameX(_currntFrameX);
				_image->setFrameY(_currntFrameY);
			}
			break;
		case ENEMYSTATE_IDLE:
			if (_myColor == BROWN)
			{
				_image = bIdle;
				_currntFrameX++;
				if (_currntFrameX > _image->getMaxFrameX()) _currntFrameX = 0;
				_image->setFrameX(_currntFrameX);
				_image->setFrameY(_currntFrameY);

			}
			else if (_myColor == WHITE)
			{
				_image = wIdle;
				_currntFrameX++;
				if (_currntFrameX > _image->getMaxFrameX()) _currntFrameX = 0;
				_image->setFrameX(_currntFrameX);
				_image->setFrameY(_currntFrameY);
			}

			break;
		case ENEMYSTATE_MOVE:
			if (_myColor == BROWN)
			{
				_image = bMove;
				_currntFrameX++;
				if (_currntFrameX > _image->getMaxFrameX()) _currntFrameX = 0;
				_image->setFrameX(_currntFrameX);
				_image->setFrameY(_currntFrameY);

			}
			else if (_myColor == WHITE)
			{
				_image = wMove;
				_currntFrameX++;
				if (_currntFrameX > _image->getMaxFrameX()) _currntFrameX = 0;
				_image->setFrameX(_currntFrameX);
				_image->setFrameY(_currntFrameY);
			}
			break;
		case ENEMYSTATE_ATTACK:
			if (_myColor == BROWN)	_image = bAttack;
			else if (_myColor == WHITE)_image = wAttack;

			_currntFrameX++;
			if (_currntFrameX > _image->getMaxFrameX())
			{
				_currntFrameX = 0;
				_myState = ENEMYSTATE_IDLE;
				if (_myColor == BROWN)	_image = bIdle;
				else if (_myColor == WHITE)_image = wIdle;
				_action = false;
			}
			_image->setFrameX(_currntFrameX);
			_image->setFrameY(_currntFrameY);
			break;
		case ENEMYSTATE_DEAD:

			if (_myColor == BROWN)	_image = bAttack;
			else if (_myColor == WHITE)_image = wAttack;

			break;
		}
	}

	_hitBox = RectMakeCenter(_pointX, _pointY, _image->getFrameWidth(), _image->getFrameHeight());
}

void Rat::action()
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

void Rat::update()
{

	if (_currntHp <= 0)
	{
		_myState = ENEMYSTATE_DEAD;

		_deadAlpha += 25;
		_action = false;
		if (_deadAlpha >= 255)
		{
			_deadAlpha = 255;
			_isLive = false;
			_action = false;
		}
	}

	if (_action && _currntHp > 0 && _isLive) action();
}