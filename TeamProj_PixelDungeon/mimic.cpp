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
	//입력받은 좌표를 초기 위치로
	_point = point;

	//각 이미지 개별할당(MANAGER는 다 똑같아져버림)
	move = new image;
	stay = new image;
	dead = new image;

	move->init("Img//Enemy//mimic//mimic_move.bmp", 64, 64, 2, 2, true, RGB(255, 0, 255));
	stay->init("Img//Enemy//mimic//mimic_stay.bmp", 160, 60, 5, 2, true, RGB(255, 0, 255));
	dead->init("Img//Enemy//mimic//mimic_dead.bmp", 128, 64, 4, 2, true, RGB(255, 0, 255));

	//초기 설정은 stay
	_image = stay;

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
	_statistics.maxLv = 8;
	_statistics.exp = 2;
	_statistics.hp = 12;
	_currntHp = 12;
	_statistics.avd_lck = 4;
	_statistics.def = 2;
	a = RND->getFromIntTo(2, 5);
	_statistics.str = a;
	_statistics.atk_lck = 11;

	//튀어나왔다!
	 _myState = ENEMYSTATE_IDLE;

	//초기값 설정
	_movePoint = PointMake(0, 0);
	_frameFPS = 10;
	_frameTime = 0;
	_deadAlpha = 0;
	_active = false;
	_playerChack = true;

	_floor = floor;

	/*ENEMYSTATE_SLEEP,	//플레이어를 찾지 못한상태/수면상태
	ENEMYSTATE_IDLE,	//플레이어를 찾은 상태에서의 기본
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
	//미믹의 경우 맵에서 일정 확률에 의하여 상자에서 나오기 때문에
	//이미 들킨 상태이기에 ENEMYSTATE_SLEEP 상태가 존재하지 않는다.

	int a = RND->getInt(100);

	//ui에 회피 했다고 전달했으면 좋겠는데
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
	//시야에 보일때만 출력하게
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
				astar = aStar(PointMake(_pointX, _pointY), _player->getPoint());
				//움직일때 해당 좌표를 4,5 같은 식으로 주면 자동으로 4*TILESIZE + TILESIZE/2, 5*... 해줌
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

	int item = RND->getFromIntTo(NAME_OLD_SHORT_SWORD, NAME_MONEY);//랜덤하게 아이템을 뱉는다
	//int item = RND->getFromIntTo(NAME_OLD_SHORT_SWORD, NAME_OLD_SHORT_SWORD);//랜덤하게 아이템을 뱉는다

	int identifyPercent = RND->getInt(1);//50% 확률로 확인된 아이템
	bool identify;

	if (identifyPercent == 0)identify = false;
	else identify = true;

	int isCursedPercent = RND->getInt(1);//50% 확률로 저주받음
	bool isCursed;
	if (isCursedPercent == 0)isCursed = false;
	else isCursed = true;

	int upgrade = RND->getInt(2);//업그레이드 수치

	switch (item)
	{
		//무기
	case NAME_OLD_SHORT_SWORD:
		//아이템 이름			위치X		위치Y	확인여부 저주여부 업그레이드 개수
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

		//방어구
	case NAME_CLOTH:
		_im->setItemToField(NAME_CLOTH, _pointX, _pointY, identify, isCursed, upgrade, 1, _map->getCurStageNum());

		break;
	case NAME_LEATHER:
		_im->setItemToField(NAME_LEATHER, _pointX, _pointY, identify, isCursed, upgrade, 1, _map->getCurStageNum());

		break;
	case NAME_MAIL:
		_im->setItemToField(NAME_MAIL, _pointX, _pointY, identify, isCursed, upgrade, 1, _map->getCurStageNum());

		break;

		//악세사리
	case NAME_RING_POWER:
		_im->setItemToField(NAME_RING_POWER, _pointX, _pointY, identify, isCursed, upgrade, 1, _map->getCurStageNum());

		break;
	case NAME_RING_RECHARGE:
		_im->setItemToField(NAME_RING_RECHARGE, _pointX, _pointY, identify, isCursed, upgrade, 1, _map->getCurStageNum());

		break;
	case NAME_LIOYDS_BEACON:
		_im->setItemToField(NAME_LIOYDS_BEACON, _pointX, _pointY, identify, isCursed, upgrade, 1, _map->getCurStageNum());

		break;

		//투척
	case NAME_DART:
		_im->setItemToField(NAME_DART, _pointX, _pointY, identify, isCursed, upgrade, 1, _map->getCurStageNum());

		break;
	case NAME_PARALYSIS_DART:
		_im->setItemToField(NAME_PARALYSIS_DART, _pointX, _pointY, identify, isCursed, upgrade, 1, _map->getCurStageNum());

		break;
	case NAME_POISON_DART:
		_im->setItemToField(NAME_POISON_DART, _pointX, _pointY, identify, isCursed, upgrade, 1, _map->getCurStageNum());

		break;
		//완드
	case NAME_LIGHTNING:
		_im->setItemToField(NAME_LIGHTNING, _pointX, _pointY, identify, isCursed, upgrade, 1, _map->getCurStageNum());

		break;
	case NAME_NORMAL:
		_im->setItemToField(NAME_NORMAL, _pointX, _pointY, identify, isCursed, upgrade, 1, _map->getCurStageNum());

		break;
	case NAME_POISON:
		_im->setItemToField(NAME_POISON, _pointX, _pointY, identify, isCursed, upgrade, 1, _map->getCurStageNum());

		break;

		//음식
		//음식등의 아이템류는 위치만 지정해 줍니다. 저주받은 파스타 따위가 나올리가 없죠 물론 주문서와 물약도 동일합니다.
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

		//주문서
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

		//물약
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

		//돈은 머니 랜덤변수를 이용합니다
	case NAME_MONEY:
		_im->setItemToField(NAME_MONEY, _pointX, _pointY, false, false, 0, money, _map->getCurStageNum());

		break;
	}

}