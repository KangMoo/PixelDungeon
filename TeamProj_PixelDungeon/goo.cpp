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

HRESULT goo::init(POINT point, int floor)//인식범위 추기
{
	//입력받은 좌표를 초기 위치로
	_point = point;

	//각 이미지 개별할당(MANAGER는 다 똑같아져버림)
	_stay = new image;
	_move = new image;
	_dead = new image;

	_stay->init("Img//Enemy//goo//goo_stay.bmp", 192, 64, 6, 2, true, RGB(255, 0, 255));
	_move->init("Img//Enemy//goo//goo_move.bmp", 64, 64, 2, 2, true, RGB(255, 0, 255));
	_dead->init("Img//Enemy//goo//goo_dead.bmp", 96, 64, 3, 2, true, RGB(255, 0, 255));

	//초기 설정은 stay
	_image = _stay;

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

	//스탯 설정
	_statistics.lv = 1;
	_statistics.exp = 2;
	_statistics.hp = 80;
	_currntHp = _statistics.hp;
	_statistics.avd_lck = 12;
	_statistics.def = 2;

	a = RND->getFromIntTo(2, 5);

	_statistics.str = 30;
	_statistics.atk_lck = 11;

	//깨어있을지 자고있을지 랜덤 설정
	_myState = ENEMYSTATE_IDLE;

	//초기값 설정
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

	//_player->getStat().atk_lck 가 0 이상이면 데미지를 입는다

	//int a = RND->getInt(_player->getStat().atk_lck + 1);
	//
	////ui에 회피 했다고 전달했으면 좋겠는데
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
		//시야에 보일때만 출력하게
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

				int identifyPercent = RND->getInt(1);//50% 확률로 확인된 아이템
				bool identify;

				if (identifyPercent == 0)identify = false;
				else identify = true;

				int isCursedPercent = RND->getInt(1);//50% 확률로 저주받음
				bool isCursed;
				if (isCursedPercent == 0)isCursed = false;
				else isCursed = true;

				int upgrade = RND->getInt(2);//업그레이드 수치

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