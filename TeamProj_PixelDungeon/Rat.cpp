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
	//입력받은 좌표를 초기 위치로
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


	//실제 그려줄 위치는 해당 타일 중심을 기준
	_pointX = _point.x * TILESIZE + TILESIZE / 2;
	_pointY = _point.y * TILESIZE + TILESIZE / 2;

	//타일 중심으로 이미지 크기만큼 렉트, 이걸로 그림그림
	_hitBox = RectMakeCenter(_pointX, _pointY, _image->getFrameWidth(), _image->getFrameHeight());
	_attBox = RectMakeCenter(_pointX, _pointY, 0, 0);

	//살아있음
	_isLive = true;
	//플레이어 발견 못함
	_findPlayer = false;

	//초기 방향은 랜덤으로
	int a = RND->getInt(2);
	if (a == 0) _right = true;
	else _right = false;

	//최초 프레임은 0, 오른쪽 보면 y=0, 왼쪽이면 y=1
	_currntFrameX = 0;
	if (_right) _currntFrameY = 0;
	else _currntFrameY = 1;

	//프레임 적용
	_image->setFrameX(_currntFrameX);
	_image->setFrameY(_currntFrameY);

	//내 턴 아님, 안움직임
	_action = false;
	_isMove = false;

	//깨어있을지 자고있을지 랜덤 설정
	a = RND->getInt(2);
	if (a == 0) _myState = ENEMYSTATE_SLEEP;
	else _myState = ENEMYSTATE_IDLE;

	//초기값 설정
	_movePoint = PointMake(0, 0);
	_frameFPS = 10;
	_frameTime = 0;
	_deadAlpha = 0;
	_active = false;

	/*ENEMYSTATE_SLEEP,	//플레이어를 찾지 못한상태/수면상태
	ENEMYSTATE_IDLE,	//플레이어를 찾은 상태에서의 기본
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
	//시야에 보일때만 출력하게
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
			//적을 발견하지 않았으면 랜덤행동

			float dis = getDistance(_player->getPoint().x / TILESIZE, _player->getPoint().y / TILESIZE, _point.x, _point.y);

			if (dis < 4)
			{
				//거리가 일정 범위 이내로 적이 들어왔으면 인식
				//인식한 턴은 그냥 자동으로 넘겨줌
				_myState = ENEMYSTATE_IDLE;
				_findPlayer = true;
				_action = false;
			}
			else
			{
				//거리가 멀면 랜덤이동
				if (!_isMove)
				{
					//0부터 시계방향으로, 8은 대기
					//해당 방향의 타일을 검사한 후에, 갈 수 있다면 그쪽으로 이동
					int a = RND->getInt(50);
					_movePoint = _point;
					_myState = ENEMYSTATE_MOVE;
					switch (a)
					{
					case 0:
						//위 (ATTRIBUTE_UNGO & _map[v.x - 1][v.y].terrain) == ATTRIBUTE_UNGO
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
						//오른쪽 위
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
						//오른쪽
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
						//오른쪽 아래
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
						//아래
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
						//왼쪽 아래
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
						//왼쪽
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
						//왼쪽 위
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
			//적을 발견했으면 A*를 이용해 최적루트로 이동한다
			//바로 옆칸이면 공격 가능하다
			int x = _point.x - _player->getPoint().x / TILESIZE;
			int y = _point.y - _player->getPoint().y / TILESIZE;
			//둘의 x, y값 차이의 절대값이 각각 1 이하인 경우 공격 가능
			if ((x <= 1 && x >= -1) && (y <= 1 && y >= -1))
			{
				_myState = ENEMYSTATE_ATTACK;
				_currntFrameX = 0;
				_player->getDamaged(_statistics.str);
				//_action = false;
			}
			else
			{
				//아니라면 astar로 이동한다
				aStar = _map->aStar(PointMake(_pointX, _pointY), _player->getPoint());
				//움직일때 해당 좌표를 4,5 같은 식으로 주면 자동으로 4*TILESIZE + TILESIZE/2, 5*... 해줌
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
		//좌표가 주어졌으면 해당 좌표로 가야한다
		//중심좌표를 구한다
		float x = _movePoint.x * TILESIZE + TILESIZE / 2;
		float y = _movePoint.y * TILESIZE + TILESIZE / 2;

		//중심좌표에 도달했는지 확인한다
		if ((static_cast<float>(_pointX) >= x - 4 && static_cast<float>(_pointX) <= x + 4) &&
			(static_cast<float>(_pointY) >= y - 4 && static_cast<float>(_pointY) <= y + 4))
		{
			//턴을 종료하고 넘겨준다
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

			//도달하지 않았으면 이동한다
			if (_pointX < x)
			{
				//현재 좌표가 가려는 좌표의 중심보다 작으면 +
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