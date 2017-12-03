#include "stdafx.h"
#include "Player.h"
#include "EnemyManager.h"
#include "Map.h"
#include "UI.h"

Player::Player()
{
}


Player::~Player()
{

}
HRESULT Player::init() { return S_OK; }
HRESULT Player::init(POINT point)
{

	addImg();
	//test~
	//_playerPoint = PointMake(_map->getTile(7, 7).destX*TILESIZE + TILESIZE / 2, _map->getTile(7, 7).destY*TILESIZE + TILESIZE / 2);

	_playerStat.atk_lck = 0;
	_playerStat.avd_lck = 0;
	_playerStat.def = 0;
	_playerStat.exp = 0;
	_playerStat.hp = 250;
	_playerStat.maxhp = 250;
	_playerStat.hunger = 100;
	_playerStat.lv = 1;
	_playerStat.str = 3;



	//~test
	_playerState = PLAYERSTATE_IDLE;
	_frameUpdateTimer = TIMEMANAGER->getWorldTime();
	_currentFrameX = _currentFrameY = 0;
	_image = IMAGEMANAGER->findImage("warrior_Idle");
	_frameTimer = TIMEMANAGER->getWorldTime();
	_keepMove = false;
	_isUsingUI = false;
	_isEnemyTargeted = false;


	return S_OK;
}
void Player::release()
{

}
void Player::update()
{

	frameUpdate();
	

	if (_playerState == PLAYERSTATE_DEAD) return;

	//자기 차례가 아니면 이하 실행X
	if (!_action) return;

	//keepMove는?? -> 아직 갈 길이 있는지 여부 (A*에 길이 남아있는지 여부)
	if (astar.size() > 0)
	{
		_keepMove = true;
	}
	else
	{
		_keepMove = false;
	}

	//가야할 길이 있다면~?
	if (_keepMove == true && !_isUsingUI)
	{
		move();
	}
	else if (_isEnemyTargeted)
	{
		action_Attack();
		_isEnemyTargeted = false;
		endTurn();
	}
	else
	{
		//시야처리
		fovCheck();
	}

	//마우스 클릭 이벤트 처리
	if (!_ui->usingInterface())
	{
		
		if (!_ui->usingInterface() && KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
		{
			//움직이는 중에 마우스 클릭 이벤트 발생 하면 가던 타일만 마저 가게 함
			if (_keepMove && astar.size()>0)
			{
				TILE temp;
				temp = astar[astar.size() - 1];
				astar.clear();
				astar.push_back(temp);
				return;
			}
		}
	}
	

	//상태처리
	if (_playerStat.hp <= 0)
	{
		_playerState = PLAYERSTATE_DEAD;
		_image = IMAGEMANAGER->findImage("warrior_Dead");
	}
}
//그릴 때	x좌표에 camera.x 만큼
//			y좌표에 camera.y 만큼 더해주기!!!!
void Player::render(POINT camera)
{
	draw(camera);
}

void Player::draw(POINT camera)
{
	//test~
	//for (auto i : angleCanTSee)
	//{
	//	MoveToEx(getMemDC(), _playerPoint.x, _playerPoint.y, NULL);
	//	LineTo(getMemDC(), _playerPoint.x + cosf(i.sangle) * 100, _playerPoint.y - sinf(i.sangle) * 100);
	//	LineTo(getMemDC(), _playerPoint.x + cosf(i.eangle) * 100, _playerPoint.y - sinf(i.eangle) * 100);
	//	LineTo(getMemDC(), _playerPoint.x, _playerPoint.y);
	//}
	for (auto i : astar)
	{
		RectangleMakeCenter(getMemDC(), i.destX * 32 + 16 + camera.x, i.destY * 32 + 16 + camera.y, 5, 5);
	}
	//~test
	_image->alphaFrameRender(getMemDC(), _playerPoint.x - _image->getFrameWidth() / 2 + camera.x, _playerPoint.y - _image->getFrameHeight() / 2 + camera.y, _currentFrameX, _currentFrameY, 0);
	//IMAGEMANAGER->render("blactkTile", getMemDC(), 50, 50, 0, 0, 100, 100);
	char str[128];
	SetTextColor(getMemDC(), RGB(255, 0, 0));
	sprintf_s(str, "%d", _playerStat.exp);
	TextOut(getMemDC(), 500, 250, str, strlen(str));

}

void Player::addCanTSeeAngle(float sangle, float eangle)
{
	//추가
	sightAngle temp;
	temp.sangle = sangle;
	temp.eangle = eangle;
	angleCanTSee.push_back(temp);

	vector<int> deleteNum;

	bool isTherNoIntersection = false;
	while (!isTherNoIntersection)
	{
		isTherNoIntersection = true;
		//중복되는 각도 합치기
		for (int i = 0; i < angleCanTSee.size(); i++)
		{
			for (int j = i + 1; j < angleCanTSee.size(); j++)
			{
				//겹치는 각도가 있을 시
				if ((angleCanTSee[i].sangle <= angleCanTSee[j].sangle && angleCanTSee[j].sangle <= angleCanTSee[i].eangle) ||
					(angleCanTSee[i].sangle <= angleCanTSee[j].eangle && angleCanTSee[j].eangle <= angleCanTSee[i].eangle))
				{
					//
					if (angleCanTSee[i].sangle >= angleCanTSee[j].sangle) angleCanTSee[i].sangle = angleCanTSee[j].sangle;
					if (angleCanTSee[i].eangle <= angleCanTSee[j].eangle) angleCanTSee[i].eangle = angleCanTSee[j].eangle;
					angleCanTSee.erase(angleCanTSee.begin() + j);
					isTherNoIntersection = false;
					break;
				}
			}
		}
	}





}

void Player::addCanTSeeAngleByRect(RECT rc)
{
	POINT rcpoint = PointMake(rc.left + TILESIZE / 2, rc.top + TILESIZE / 2);
	//동일 y축 위
	if (_playerPoint.x / TILESIZE == rcpoint.x / TILESIZE)
	{
		//플레이어의 위
		if (_playerPoint.y / TILESIZE > rcpoint.y / TILESIZE)
		{
			addCanTSeeAngle(getAngle(_playerPoint.x, _playerPoint.y, rc.right, rc.bottom), getAngle(_playerPoint.x, _playerPoint.y, rc.left, rc.bottom));
		}
		//플레이어의 아래
		else if (_playerPoint.y / TILESIZE < rcpoint.y / TILESIZE)
		{
			addCanTSeeAngle(getAngle(_playerPoint.x, _playerPoint.y, rc.left, rc.top), getAngle(_playerPoint.x, _playerPoint.y, rc.right, rc.top));
		}

	}
	//1,4사분면
	else if (_playerPoint.x / TILESIZE< rcpoint.x / TILESIZE)
	{
		//동일 x축 위
		if (_playerPoint.y / TILESIZE == rcpoint.y / TILESIZE)
		{
			if (getAngle(_playerPoint.x, _playerPoint.y, rc.left, rc.bottom) > getAngle(_playerPoint.x, _playerPoint.y, rc.left, rc.top))
			{
				addCanTSeeAngle(0, getAngle(_playerPoint.x, _playerPoint.y, rc.left, rc.top));
				addCanTSeeAngle(getAngle(_playerPoint.x, _playerPoint.y, rc.left, rc.bottom), PI2);
			}
			else
			{
				addCanTSeeAngle(getAngle(_playerPoint.x, _playerPoint.y, rc.left, rc.bottom), getAngle(_playerPoint.x, _playerPoint.y, rc.left, rc.top));
			}
			
		}
		//1사분면
		else if (_playerPoint.y / TILESIZE> rcpoint.y / TILESIZE)
		{
			if (getAngle(_playerPoint.x, _playerPoint.y, rc.right, rc.bottom) >  getAngle(_playerPoint.x, _playerPoint.y, rc.left, rc.top))
			{
				addCanTSeeAngle(0, getAngle(_playerPoint.x, _playerPoint.y, rc.left, rc.top));
				addCanTSeeAngle(getAngle(_playerPoint.x, _playerPoint.y, rc.right, rc.bottom), PI2);
			}
			else
			{
				addCanTSeeAngle(getAngle(_playerPoint.x, _playerPoint.y, rc.right, rc.bottom), getAngle(_playerPoint.x, _playerPoint.y, rc.left, rc.top));
			}
			
		}
		//4사분면
		else if (_playerPoint.y / TILESIZE < rcpoint.y / TILESIZE)
		{
			if (getAngle(_playerPoint.x, _playerPoint.y, rc.left, rc.bottom) >  getAngle(_playerPoint.x, _playerPoint.y, rc.right, rc.top))
			{
				addCanTSeeAngle(0, getAngle(_playerPoint.x, _playerPoint.y, rc.right, rc.top));
				addCanTSeeAngle(getAngle(_playerPoint.x, _playerPoint.y, rc.left, rc.bottom), PI2);
			}
			else
			{
				addCanTSeeAngle(getAngle(_playerPoint.x, _playerPoint.y, rc.left, rc.bottom), getAngle(_playerPoint.x, _playerPoint.y, rc.right, rc.top));
			}
			
		}
	}
	//2,3사분면
	else if (_playerPoint.x / TILESIZE> rcpoint.x / TILESIZE)
	{
		//동일 x축 위
		if (_playerPoint.y / TILESIZE == rcpoint.y / TILESIZE)
		{
			addCanTSeeAngle(getAngle(_playerPoint.x, _playerPoint.y, rc.right, rc.top), getAngle(_playerPoint.x, _playerPoint.y, rc.right, rc.bottom));
		}
		//2사분면
		else if (_playerPoint.y / TILESIZE > rcpoint.y / TILESIZE)
		{
			addCanTSeeAngle(getAngle(_playerPoint.x, _playerPoint.y, rc.right, rc.top), getAngle(_playerPoint.x, _playerPoint.y, rc.left, rc.bottom));
		}
		//3사분면
		else if (_playerPoint.y / TILESIZE< rcpoint.y / TILESIZE)
		{
			addCanTSeeAngle(getAngle(_playerPoint.x, _playerPoint.y, rc.left, rc.top), getAngle(_playerPoint.x, _playerPoint.y, rc.right, rc.bottom));
		}
	}
}

void Player::frameUpdate()
{
	if (_playerState == PLAYERSTATE_IDLE && TIMEMANAGER->getWorldTime() - _frameTimer > 1.5)
	{
		_frameTimer = TIMEMANAGER->getWorldTime();
		if (_currentFrameX < _image->getMaxFrameX())
		{
			_currentFrameX++;
		}
		else
		{
			_currentFrameX = 0;
			if (_playerState != PLAYERSTATE_IDLE)
			{
				_playerState = PLAYERSTATE_IDLE;
				_image = IMAGEMANAGER->findImage("warrior_Idle");
			}
		}
	}

	else if (_playerState != PLAYERSTATE_IDLE && TIMEMANAGER->getWorldTime() - _frameTimer > 0.1)
	{
		_frameTimer = TIMEMANAGER->getWorldTime();


		if (_currentFrameX < _image->getMaxFrameX())
		{
			_currentFrameX++;
		}
		else
		{
			_currentFrameX = 0;

			if (_playerState == PLAYERSTATE_DEAD)
			{

			}
			else if (_playerState != PLAYERSTATE_IDLE)
			{
				_playerState = PLAYERSTATE_IDLE;
				_image = IMAGEMANAGER->findImage("warrior_Idle");
			}
		}
	}

}

void Player::imageChange(const char* str)
{
	_image = IMAGEMANAGER->findImage(str);
	_currentFrameX = 0;
}

void Player::fovCheck()
{
	//FOV테스트~
	tileCanSee.clear();
	angleCanTSee.clear();


	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			TILE temp = _map->getTile(i, j);
			if (temp.tileview == TILEVIEW_ALL)
			{
				temp.tileview = TILEVIEW_HALF;
				_map->setTile(temp, i, j);
			}
		}

	}

	//플레이어 중심으로 9개의 타일은 볼 수 있는 타일로 추가
	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			tileCanSee.push_back(_map->getTile(_playerPoint.x / TILESIZE + i, _playerPoint.y / TILESIZE + j));
		}
	}

	//최대 시야만큼 탐색
	for (int sightMaxTile = 1; sightMaxTile < 4; sightMaxTile++)
	{
		for (int i = _playerPoint.x / TILESIZE - sightMaxTile; i <= _playerPoint.x / TILESIZE + sightMaxTile; i++)
		{
			for (int j = _playerPoint.y / TILESIZE - sightMaxTile; j <= _playerPoint.y / TILESIZE + sightMaxTile; j++)
			{
				//볼 수 있는 타일인지 체크하기 위한 변수
				bool tileCanSeeChk = true;
				//볼 수 없는 위치에 있을 경우 탐색
				for (auto k : angleCanTSee)
				{
					//보지 못하는 각도에 타일이 위치해 있는가?
					if (k.sangle <= getAngle(_playerPoint.x, _playerPoint.y, i*TILESIZE + TILESIZE / 2, j*TILESIZE + TILESIZE / 2) &&
						getAngle(_playerPoint.x, _playerPoint.y, i*TILESIZE + TILESIZE / 2, j*TILESIZE + TILESIZE / 2) <= k.eangle)
					{
						//허용 각도 수치
						int limit = 10;
						//살짝 보이는정도면 보인다고 쳐주자
						if (k.sangle - PI / 180 * limit <= getAngle(_playerPoint.x, _playerPoint.y, i*TILESIZE + TILESIZE / 2, j*TILESIZE + TILESIZE / 2) &&
							getAngle(_playerPoint.x, _playerPoint.y, i*TILESIZE + TILESIZE / 2, j*TILESIZE + TILESIZE / 2) <= k.sangle + PI / 180 * limit &&
							j != _playerPoint.y / TILESIZE)
						{

						}
						else if (k.eangle - PI / 180 * limit <= getAngle(_playerPoint.x, _playerPoint.y, i*TILESIZE + TILESIZE / 2, j*TILESIZE + TILESIZE / 2) &&
							getAngle(_playerPoint.x, _playerPoint.y, i*TILESIZE + TILESIZE / 2, j*TILESIZE + TILESIZE / 2) <= k.eangle + PI / 180 * limit &&
							j != _playerPoint.y / TILESIZE)
						{

						}
						else
						{
							tileCanSeeChk = false;
						}

					}
				}

				//볼 수 있는 타일일 경우
				if (tileCanSeeChk && i >= 0 && j >= 0)
				{
					//볼 수 있는 타일벡터에 push
					tileCanSee.push_back(_map->getTile(i, j));
					//장애물이 있을 경우
					if ((_map->getTile(i, j).terrain & ATTRIBUTE_UNSIGHT) == ATTRIBUTE_UNSIGHT)
					{
						//보지 못하는 각도 추가
						addCanTSeeAngleByRect(RectMake(i * TILESIZE, j * TILESIZE, TILESIZE, TILESIZE));
					}
				}
			}
		}
	}



	//볼 수 있는 타일은 TILEVIEW_ALL로 변경
	for (auto i : tileCanSee)
	{
		TILE temp = i;
		temp.tileview = TILEVIEW_ALL;
		_map->setTile(temp, i.destX, i.destY);
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		_playerPoint.x -= TILESIZE;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		_playerPoint.x += TILESIZE;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		_playerPoint.y -= TILESIZE;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		_playerPoint.y += TILESIZE;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_playerStat.hp -= 30;
	}
	//~FOV테스트
}

void Player::addImg()
{
	IMAGEMANAGER->addFrameImage("warrior_Idle", "Img//Player//warrior_idle.bmp", 48, 210, 2, 7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("warrior_Dead", "Img//Player//warrior_dead.bmp", 120, 210, 5, 7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("warrior_Eat", "Img//Player//warrior_eat.bmp", 48, 210, 2, 7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("warrior_Attack", "Img//Player//warrior_attack.bmp", 72, 210, 3, 7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("warrior_Scroll", "Img//Player//warrior_scroll.bmp", 72, 210, 3, 7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("warrior_Move", "Img//Player//warrior_move.bmp", 144, 210, 6, 7, true, RGB(255, 0, 255));
}

void Player::addDebuff(DEBUFF debuffType, int lefttime, int damage)
{
	tagDebuff temp;
	temp.type = debuffType;
	temp.lefttime = lefttime;
	temp.damage = damage;
	_vdebuff.push_back(temp);
}

void Player::action_Move(POINT point)
{
	_playerState = PLAYERSTATE_MOVE;
	_image = IMAGEMANAGER->findImage("warrior_Move");

	astar = _map->aStar(_playerPoint, point);
	_goalTile = _map->getTile(_ptMouse.x / TILESIZE, _ptMouse.y / TILESIZE);
}
void Player::action_Attack()
{
	_playerState = PLAYERSTATE_ATTACK;
	_image = IMAGEMANAGER->findImage("warrior_Attack");
	_currentFrameX = 0;

	//목표 몬스터 공격
	if (_isEnemyTargeted)
	{
		attack = true;
		player_attack_dp = true;

		// 데미지 주기 (임시)
		_TargetEnemy->getDamaged(RND->getFromIntTo(3,3));
		
		//_TargetEnemy->setHP(_TargetEnemy->getHP() -RND->getFromIntTo(_playerStat.mindmg,_playerStat.maxdmg));
		_isEnemyTargeted = false;
	}
}
void Player::action_Scroll()
{
	_playerState = PLAYERSTATE_SCROLL;
	_image = IMAGEMANAGER->findImage("warrior_Scroll");
}
void Player::action_Eat()
{
	_playerState = PLAYERSTATE_EAT;
	_image = IMAGEMANAGER->findImage("warrior_Eat");
}

void Player::move()
{
	_playerState = PLAYERSTATE_MOVE;
	_image = IMAGEMANAGER->findImage("warrior_Move");

	_playerPoint.x += cosf(getAngle(_playerPoint.x, _playerPoint.y, astar[astar.size() - 1].destX * TILESIZE + TILESIZE / 2, astar[astar.size() - 1].destY*TILESIZE + TILESIZE / 2)) * 3;
	_playerPoint.y -= sinf(getAngle(_playerPoint.x, _playerPoint.y, astar[astar.size() - 1].destX * TILESIZE + TILESIZE / 2, astar[astar.size() - 1].destY*TILESIZE + TILESIZE / 2)) * 3;

	//목표에 도달하면 (타일 한칸 이동 완료하면)
	if (getDistance(_playerPoint.x, _playerPoint.y, astar[astar.size() - 1].destX * TILESIZE + TILESIZE / 2, astar[astar.size() - 1].destY*TILESIZE + TILESIZE / 2) <= 3)
	{
		//플레이어 위치 조정
		_playerPoint.x = astar[astar.size() - 1].destX*TILESIZE + TILESIZE / 2;
		_playerPoint.y = astar[astar.size() - 1].destY*TILESIZE + TILESIZE / 2;
		//시야처리
		fovCheck();

		//목표지점 수정
		astar.erase(astar.begin() + astar.size() - 1);

		//턴 넘기기
		endTurn();
	}
}
void Player::getDamaged(int damage)
{
	if (RND->getFloat(1.0)<_playerStat.atk_lck)
	{
		//빗나감
	}
	else
	{
		if (damage - _playerStat.def > 0)
		{
			//방어
			_playerStat.hp -= damage;
			monster_attack_dp = damage;
			damaged = true;
		}
		else
		{
			//완전방어

		}
	}
}
void Player::mouseClickEvent()
{
	//움직이는 중에 마우스 클릭 이벤트 발생 하면 가던 타일만 마저 가게 함
	if (_keepMove && astar.size()>0)
	{
		TILE temp;
		temp = astar[astar.size()-1];
		astar.clear();
		astar.push_back(temp);
		return;
	}
	
	POINT ptMouse = _ptMouse;
	ptMouse.x -= _ui->getCamera().x;
	ptMouse.y -= _ui->getCamera().y;
	_isEnemyTargeted = false;
	for (auto i : _em->getEnemyVector())
	{
		//몬스터를 클릭했다면?
		if ((ptMouse.x / TILESIZE == i->getPoint().x / TILESIZE && ptMouse.y / TILESIZE == i->getPoint().y / TILESIZE) &&
			_map->getTile(ptMouse.x / TILESIZE, ptMouse.y / TILESIZE).tileview != TILEVIEW_NO && i->getCHP() > 0 && _map->getCurStageNum() == i->getFloor())
		{
			//목표 저장
			_isEnemyTargeted = true;
			_TargetEnemy = i;
			astar = _map->aStar(_playerPoint, ptMouse);
			int a = 0;
			//길이 있는지 여부 판단
			if (astar.size() > 0)
			{
				//현재 위치는 뺌
				astar.erase(astar.begin() + 0);
			}

			if (astar.size() > 0)
			{
				//몬스터위치 뺌
				astar.erase(astar.begin() + astar.size() - 1);
			}

			break;
		}
	}

	//몬스터 말고 땅을 클릭했다면?
	if ((_map->getTile(ptMouse.x / TILESIZE, ptMouse.y / TILESIZE).terrain != TERRAIN_NULL && !_isEnemyTargeted)&&
		_map->getTile(ptMouse.x / TILESIZE, ptMouse.y / TILESIZE).tileview != TILEVIEW_NO)
	{
		//이동경로 저장
		astar = _map->aStar(_playerPoint, ptMouse);
		//길이 있는지 여부 판단
		if (astar.size() > 0)
		{
			//현재 위치는 뺌
			astar.erase(astar.begin() + astar.size() - 1);
		}
	}
	//keepMove는?? -> 아직 갈 길이 있는지 여부 (A*에 길이 남아있는지 여부)
	if (astar.size() > 0)
	{
		_keepMove = true;
	}
	else
	{
		_keepMove = false;
	}

	if (!_keepMove)
	{
		RECT temp = RectMakeCenter(_playerPoint.x, _playerPoint.y, TILESIZE * 3, TILESIZE * 3);
		if (PtInRect(&temp, ptMouse))
		{
			//열쇠를 가지고 있으면
			//if()~~~~~
			_map->setTile_UnlockDoor(ptMouse.x / TILESIZE, ptMouse.y / TILESIZE);
			
		}
	}
}

void Player::endTurn()
{
	//턴 종료시 발생하는 효과 추가
	effectDebuff();
	effectBuff();
	_playerStat.hunger--;

	//배고픔 처리
	if (_playerStat.hunger < 50)
	{
		_playerStat.hp--;
	}
	else if (_playerStat.hunger > 100)
	{
		if (_playerStat.maxhp < 250)
		{
			_playerStat.hp++;
		}

		if (_playerStat.hp >= 250)
		{
			_playerStat.hp = _playerStat.maxhp;
		}
	}

	//턴 종료
	_action = false;
	//적 차례
	_em->setTurn(true);
	//keepMove는?? -> 아직 갈 길이 있는지 여부 (A*에 길이 남아있는지 여부)
	if (astar.size() > 0)
	{
		_keepMove = true;
	}
	else
	{
		_keepMove = false;
	}
	//맵에 턴 끝났다는 정보 넘겨줌
	_map->playerTurnEnd();
}

void Player::expUp(int exp)
{
	_playerStat.exp += exp;
	if(_playerStat.exp >= 100)
	{
		_playerStat.lv++;
		_playerStat.exp = 0;

		_playerStat.maxhp += 15;
		//회피 & 명중률 up
		//_playerStat.atk_lck += 0.1;
		//_playerStat.avd_lck += 0.1;
	}	
}

void Player::effectDebuff()
{
	bool isThereFrozenDebuff = false;
	for (auto i : _vdebuff)
	{
		switch (i.type)
		{
		case DEBUFF_BLEEDING:
			_playerStat.hp -= i.damage;
			break;
		case DEBUFF_FIRE:
			_playerStat.hp -= i.damage;
			break;
		case DEBUFF_FROZEN:
			isThereFrozenDebuff = true;
			break;
		case DEBUFF_HUNGER:

			break;
		}
		i.lefttime--;
	}
	if (isThereFrozenDebuff)
	{
		for (int i = 0; i < _vdebuff.size(); i++)
		{
			if (_vdebuff[i].type == DEBUFF_FIRE)
			{
				_vdebuff.erase(_vdebuff.begin() + i);
			}
		}
	}
	for (int i = 0; i < _vdebuff.size(); i++)
	{
		if (_vdebuff[i].lefttime <= 0)
		{
			_vdebuff.erase(_vdebuff.begin() + i);
		}
	}
}
void Player::effectBuff()
{
	for (auto i : _vbuff)
	{
		switch (i.type)
		{
		case BUFF_INVISIBLE:

			break;
		case BUFF_LEVITATION:

			break;
		case BUFF_NATURAL_ARMOR:

			break;
		case BUFF_NATURAL_HEAL:

			break;
		}
	}
}

void Player::setChangeFoor()
{
	if (astar.size() > 0) astar.clear();
	fovCheck();
	endTurn();
}

void Player::stopMoving()
{
	if (_keepMove && astar.size()>0)
	{
		TILE temp;
		temp = astar[astar.size() - 1];
		astar.clear();
		astar.push_back(temp);
		return;
	}
}

void Player::activeTurn()
{
	_action = true;

}