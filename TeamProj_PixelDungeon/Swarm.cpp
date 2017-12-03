#include "stdafx.h"
#include "Swarm.h"
#include "Player.h"
#include "EnemyManager.h"
#include "ItemManager.h"
#include "UI.h"
#include "Map.h"

Swarm::Swarm()
{
}


Swarm::~Swarm()
{
}

HRESULT Swarm::init(POINT point, int floor)
{
	_point = point;
	_floor = floor;

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
	_statistics.hp = 20;
	_currntHp = 20;
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
	_itemDrop = 20;

	/*ENEMYSTATE_SLEEP,	//플레이어를 찾지 못한상태/수면상태
	ENEMYSTATE_IDLE,	//플레이어를 찾은 상태에서의 기본
	ENEMYSTATE_MOVE,
	ENEMYSTATE_ATTACK,
	ENEMYSTATE_END*/
	//_hpBar = new progressBar;
	//_hpBar->init(_pointX - 25, _pointY + _image->getFrameHeight() / 2 + 10, 30, 10);

	return S_OK;
}
HRESULT Swarm::init(POINT point, int currntHp, int floor, int drop)
{
	//분열했다!
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
	//공격당해 분열당한거니 이미 발견한 상태
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
	_statistics.exp = 30;
	_statistics.hp = 20;
	_currntHp = currntHp;
	_statistics.avd_lck = 5;
	_statistics.def = 0;
	a = RND->getFromIntTo(1, 4);
	_statistics.str = a;
	_statistics.atk_lck = 12;
	
	//이미 공격당했으니 상태는 무조건 발각한 상태
	_myState = ENEMYSTATE_IDLE;

	_floor = floor;

	_movePoint = PointMake(0, 0);
	_frameCount = 0;
	_deadAlpha = 0;
	_itemDrop = drop;

	/*ENEMYSTATE_SLEEP,	//플레이어를 찾지 못한상태/수면상태
	ENEMYSTATE_IDLE,	//플레이어를 찾은 상태에서의 기본
	ENEMYSTATE_MOVE,
	ENEMYSTATE_ATTACK,
	ENEMYSTATE_END*/
	//_hpBar = new progressBar;
	//_hpBar->init(_pointX - 25, _pointY + _image->getFrameHeight() / 2 + 10, 30, 10);

	_frameFPS = 10;
	_frameTime = 0;


	return S_OK;
}

void Swarm::action()
{
	//if (KEYMANAGER->isOnceKeyDown('E')) getDamaged(3);
	if (!_active)
	{
		if (_map->getTile(_point.x, _point. y).tileview != TILEVIEW_NO)
		{
			_active = true;
		}
		_action = false;
		return;
	}


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
						if((ATTRIBUTE_UNGO & _map->getMap(_point.x, _point.y - 1).terrain) != ATTRIBUTE_UNGO)
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
			if ((x <= 1 && x>= -1) && (y <= 1 && y >= -1))
			{
				_myState = ENEMYSTATE_ATTACK;
				_currntFrameX = 0;
				_player->getDamaged(_statistics.str);
				//_action = false;
			}
			else
			{
				//아니라면 astar로 이동한다
				astarTest = aStar(PointMake(_pointX, _pointY), _player->getPoint());
				//움직일때 해당 좌표를 4,5 같은 식으로 주면 자동으로 4*TILESIZE + TILESIZE/2, 5*... 해줌
				//_movePoint = PointMake(astarTest[astarTest.size() - 1].destX, astarTest[astarTest.size() - 1].destY);
				if (astarTest.size() > 2)
					_movePoint = PointMake(astarTest[astarTest.size() - 2].destX, astarTest[astarTest.size() - 2].destY);
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

void Swarm::frameUpdate()
{
	//_frameCount++;

	if (_findPlayer)
	{
		if (_player->getPoint().x >= _pointX) _right = true;
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
			//공격시에는 끝나면 턴 넘겨주게
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

	//0~99 중에 나온 숫자가 회피율보다 낮다면 회피
	if (a < _statistics.avd_lck - _player->getStat().atk_lck)
	{
		return;
	}
	else
	{
		//높다면 뎀지받음
		int dam = damage - _statistics.def;
		if (dam < 1) dam = 1;
		_currntHp -= dam;

		if (_currntHp > 0)
		{
			//죽지 않았다면 분열을 해야한다
			//이걸 어떻게 하지?->ENEMYMANAGER에서 처리하자
			//ENEMY에 swarm을 구별할 수 있는 무언가를 추가해주고 나머진 false, 얘만 true로 해줘서
			//그게 true면 분열, 아님 냅두게

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
				//_em->setSwarm(PointMake(_point.x + x, _point.y + y), _currntHp);
			if ((ATTRIBUTE_UNGO & _map->getMap(_point.x + x, _point.y + y).terrain) != ATTRIBUTE_UNGO)
			{
				for (int i = 0; i < _em->getEnemyVector().size(); i++)
				{
					if (_em->getEnemyVector()[i]->getTilePt().x == _point.x + x &&
						_em->getEnemyVector()[i]->getTilePt().y == _point.y + y) return;
				}
				_em->setSwarmSpawn(PointMake(_point.x + x, _point.y + y), _currntHp, _floor, _itemDrop/2);
			}
		}
	}
}


void Swarm::draw(POINT camera)
{
	//_hpBar->setGauge(_currntHp, _statistics.hp);
	//시야에 보일때만 출력하게
	if (_floor == _map->getCurStageNum())
	{
		if (_map->getTile(_pointX / TILESIZE, _pointY / TILESIZE).tileview == TILEVIEW_ALL)
			_image->alphaFrameRender(getMemDC(), _hitBox.left + camera.x, _hitBox.top + camera.y, _deadAlpha);
		char string[128];
		sprintf_s(string, "%d", _statistics.hp);
		TextOut(getMemDC(), 300, 300, string, strlen(string));
	}
	//RectangleMakeCenter(getMemDC(), _pointX + camera.x, _pointY + camera.y, _currntHp, _currntHp);
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
	if (_floor == _map->getCurStageNum())
	{
		if (_currntHp <= 0)
		{
			_deadAlpha += 25;
			_action = false;
			if (_deadAlpha >= 255)
			{
				_deadAlpha = 255;
				_player->expUp(_statistics.exp);
				if (_isLive)
				{
					int a = RND->getInt(100);
					if (a < _itemDrop)
					{
						_im->setItemToField(NAME_HEAL, _pointX, _pointY, false, false, 0, 1,_map->getCurStageNum());
					}
				}
				_isLive = false;
				_action = false;
			}
		}

		if (_action && _currntHp > 0 && _isLive) action();
	}
	else _action = false;
}