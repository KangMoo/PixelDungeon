#include "stdafx.h"
#include "Mimic.h"
#include "Player.h"
#include "Map.h"
#include "UI.h"
//#include "Item.h"
#include "itemManager.h"
Mimic::Mimic()
{
}


Mimic::~Mimic()
{
}

HRESULT Mimic::init(POINT point, int cog)
{
	//=======================================================================================================================================================
	//												*MIMICIMAGE*	
	//=======================================================================================================================================================

	IMAGEMANAGER->addFrameImage("mimicDisable", "Img\Enemy\mimic\mimic_disable.bmp",32,	32, 1, 2, true, RGB(255, 0, 255));//아이들인줄 알았는데 슬립이였다
	IMAGEMANAGER->addFrameImage("mimicMove",	"Img\Enemy\mimic\mimic_move.bmp",	64,	64, 2, 2, true, RGB(255, 0, 255));//무브인줄 알았는데 아이들이였다
	IMAGEMANAGER->addFrameImage("mimicStay",	"Img\Enemy\mimic\mimic_stay.bmp",	160,64, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mimicDead",	"Img\Enemy\mimic\mimic_dead.bmp",	128,64, 4, 2, true, RGB(255, 0, 255));

	//=======================================================================================================================================================
	//												*MIMICINIT*	
	//=======================================================================================================================================================

	//==============================================*LV/STAT SETTING*=============================================================================================================

	_statistics.exp		= 2 + (_statistics.lv - 1) * 2 / 5; //경험치, 위키에서 이랬음
	_statistics.lv		= 1;  //플레이어 레벨에 비례하여 오릅니다.
	_statistics.maxLv	= 30; //최대레벨

	//최대레벨 고정
	if (_statistics.lv >= _statistics.maxLv) _statistics.lv = _statistics.maxLv;

	_statistics.hp	= 12 + (_statistics.lv * 4);//레벨에 비례하여 상승합니다.
	_statistics.def = 0; //방어력은 없다, 위키에서 그랫으ㅡㅁ


	//미믹이 들키지 않은 상태, 근데 이건 나도 어떻게 될지는 모르겠다.
	_image = IMAGEMANAGER->findImage("mimicDisable");

	//ㅎㅎ;
	_statistics.avd_lck = 0;
	_statistics.atk_lck = 9 + _statistics.lv;

	//==============================================*CHARACTER INIT*=============================================================================================================

	_hitBox = RectMake(point.x, point.y, TILESIZE, TILESIZE);	//32로 고정을 해줍니다. 혹시 모르니까요.
	_attBox = RectMake(0, 0, 0, 0);								//일단 초기화를 해줍시다.

	_currntHp = _statistics.hp;

	//_hpBar->init(point.x, point.y, TILESIZE, 4);
	//_hpBar->setGauge(_currntHp, _statistics.hp);//hp바를 세팅해줍니다.

	//==============================================*BOOL SETTING*=============================================================================================================

	_myState = ENEMYSTATE_SLEEP;//SLEEP == DISABLE

	_isLive			= true;		//살아있습니다.
	_action			= false;	//아직 내 턴이 아닙니다.
	_findPlayer		= false;	//파인드 플레이어가 플레이어 건드렸는지의 여부입니다.

	//==============================================*etc. SETTING*=============================================================================================================

	//=======================================================================================================================================================
	//*NOTICE
	//*FrameY가 0일시 right
	//*FrameY가 1일시 left
	//=======================================================================================================================================================

	_currentFrameX = 0;	//프레임을 초기화 해줍니다.
	_currentFrameY = 0;	//프레임을 초기화 해줍니다.
	_image->setFrameX(_currentFrameX);	//이미지 프레임을 초기화 해줍니다.
	_image->setFrameY(_currentFrameY);	//이미지 프레임을 초기화 해줍니다.

	_deadAlpha = 255;

	_cog = RectMake(point.x, point.y, cog, cog);

	_point.x = point.x;
	_point.y = point.y;


	return S_OK;
}

void Mimic::release()
{
	SAFE_RELEASE(_image);
	SAFE_DELETE(_image);
}

void Mimic::update()
{
	money = RND->getFromIntTo(1, 99999);

	if (_myState == ENEMYSTATE_SLEEP)
	{
		_statistics.lv		= _player->getStat().lv; //플레이어 레벨에 비례하여 오릅니다
		_statistics.maxLv	= 5;
		_statistics.exp		= 2 + (_statistics.lv - 1) * 2 / 5;

		if (_statistics.lv >= _statistics.maxLv)_statistics.lv = _statistics.maxLv;
	}

	frameUpdate();

	//플레이어가 미믹이 비활성화 된 상태에서 관찰을 시도할때
	if (_findPlayer == false && _myState == ENEMYSTATE_SLEEP && false)
	{
		_findPlayer = true;
		_myState	= ENEMYSTATE_IDLE;
		_image		= IMAGEMANAGER->findImage("mimicStay");
		_action		= false;
		//아이템을 하나 뱉는다고 한다.
	}

	//아이템을 하나 뱉은 상태에선 활동 상태로 들어간다.
	//플레이어와 멀어졌다 해서 다시 비활동 상태로 돌아가지는 않는다.
	if (_isLive == true && _findPlayer == true )
	{
		_myState = ENEMYSTATE_IDLE;

		if (_action == false)
		{
			_image = IMAGEMANAGER->findImage("mimicStay");
		}

		if (_action == true)//나의 턴일때
		{
			action();
		}

		//_hpBar->setX(_point.x);
		//_hpBar->setY(_point.y);
		//_hpBar->setGauge(_currntHp, _statistics.hp);
		//_hpBar->update();
	}

	if (_currntHp <= 0)
	{
		_myState	= ENEMYSTATE_DEAD;
		_isLive		= false; //움직임을 멈춘다.
		_deadAlpha--;

		//UI에게 사망소식을 알린다.
		//플레이어에게 EXP를 넘긴다.
		//미믹은 랜덤하게 아이템을 뱉는다.

		itemDrop();
	}
}

void Mimic::render(POINT camera)
{
	draw(camera);
}

void Mimic::draw(POINT camera)
{
	RectangleMake(getMemDC(), _point.x + camera.x, _point.y + camera.y, 32, 32);
	//_image->frameRender(getMemDC(), _point.x + camera.x, _point.y + camera.y);
	_image->alphaFrameRender(getMemDC(), _point.x + camera.x, _point.y + camera.y, _currentFrameX, _currentFrameY, _deadAlpha);
	//if (_findPlayer == true)
	//{
	//	_hpBar->render();
	//}
}

void Mimic::action()
{
	int distanceToPlayer = getDistance(_point.x, _point.y, _player->getPoint().x, _player->getPoint().y) / TILESIZE;

	//두칸 이상 떨어져 있으면 플레이어 위치로 움직입니다.
	if (distanceToPlayer < 2) move();
	//아닐시 플레이어 위치로 공격을 시도합니다.
	else attack();
}

void Mimic::frameUpdate()
{
	//============================================*DIRECTION SETTING*===========================================
	
	if (_findPlayer == true)
	{
		if (_player->getPoint().x > _point.x)	_right = true;
		else									_right = false;
	}

	//==========================================*DIRECTION IMAGE CHANGE*========================================
	
	if (_right)	_currentFrameY = 0;
	else		_currentFrameY = 1;

	//==============================================*STATE IMAGE CHANGE*========================================
	
	if (_myState == ENEMYSTATE_MOVE)	_image = IMAGEMANAGER->findImage("mimicMove");//이미지 변경

	if (_myState == ENEMYSTATE_ATTACK)
	{
		_image = IMAGEMANAGER->findImage("mimicStay");
		if (_currentFrameX > _image->getMaxFrameX())
		{
			_image		= IMAGEMANAGER->findImage("mimicStay");//아 이미지 이젠 뭐가 뭔지 모르겠다^^
			_myState	= ENEMYSTATE_IDLE;
			_action		= false; //턴을 넘김다
		}
	}

	if (_myState == ENEMYSTATE_DEAD)	_image = IMAGEMANAGER->findImage("mimicDead");

	//==============================================*FRAME UPDATE*========================================

	_frameFPS = 10;
	_frameTime++;

	if (_frameFPS <= _frameTime)
	{
		_currentFrameX++;
		_frameTime = 0;
	}

	if (_currentFrameX >= _image->getMaxFrameX() &&
		_myState	   != ENEMYSTATE_DEAD) _currentFrameX = 0;	

	//==============================================*FRAME UPDATE*========================================
}

void Mimic::attack()
{
	//플레이어의 위치를 찾아서 그 방향에 어택렉트를 생성해 줍니다. 그다음에 초기화를 시켜줍시다.

	//상태를 변경합니다.
	_myState = ENEMYSTATE_ATTACK;

	//공격렉트르 설정합니다.
	_attBox = RectMake(_player->getPoint().x, _player->getPoint().y, TILESIZE, TILESIZE);

	//흰 쥐는 일정 확률로 출혈을 일으키고 공격력도 다릅니다.
	_statistics.str = RND->getFromIntTo((9 + _statistics.lv) * 2, (9 + _statistics.lv) * 3);

	//_player->getDamaged(_statistics.str);
	_attBox = RectMake(0, 0, 0, 0);//초기화

	_action = false; //턴을 넘김다

}

void Mimic::move()
{
	//에이스타로 적을 따라 이동합니다.

	_myState = ENEMYSTATE_MOVE;

	//7 8 9
	//4 5 6
	//1 2 3
	//5는 idle



	//A*를 적용하여 '플레이어' 의 '주변 1칸'애 있어야함

	//_map->aStar(_point, _player->getPoint());
	//
	//if (_player->getPoint().y > _point.y)
	//{
	//	_point.y = _point.y + TILESIZE;
	//}

	//좌표값 구하기
	int x = _movePt.x;
	int y = _movePt.y;

	//해당 좌표값에 도착했는지 체크
	if (_point.x == x && _point.y == y)
	{
		_image = IMAGEMANAGER->findImage("mimicStay");
		_myState = ENEMYSTATE_IDLE;
		_action = false;
	}
	//좌표값에 도착하지 못함
	else
	{
		//좌우
		if (_point.x > x)	_point.x -= TILESIZE / 8;
		else				_point.x += TILESIZE / 8;

		//상하
		if (_point.y > y)	_point.y -= TILESIZE / 8;
		else				_point.y += TILESIZE / 8;
	}

}

void Mimic::itemDrop()
{
	//										0						40
	int item			= RND->getFromIntTo(NAME_OLD_SHORT_SWORD, NAME_MONEY);//랜덤하게 아이템을 뱉는다
	
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
		_im->setItemToField(NAME_OLD_SHORT_SWORD,	_point.x, _point.y, identify, isCursed, upgrade, 1);
		
		break;
	case NAME_SHORT_SWORD:
		_im->setItemToField(NAME_SHORT_SWORD,		_point.x, _point.y, identify, isCursed, upgrade, 1);

		break;
	case NAME_SWORD:
		_im->setItemToField(NAME_SWORD,				_point.x, _point.y, identify, isCursed, upgrade, 1);

		break;
	case NAME_SPEAR:
		_im->setItemToField(NAME_SPEAR,				_point.x, _point.y, identify, isCursed, upgrade, 1);

		break;
	case NAME_BATTLE_AXE:
		_im->setItemToField(NAME_BATTLE_AXE,		_point.x, _point.y, identify, isCursed, upgrade, 1);

		break;

		//방어구
	case NAME_CLOTH:
		_im->setItemToField(NAME_CLOTH,				_point.x, _point.y, identify, isCursed, upgrade, 1);

		break;
	case NAME_LEATHER:
		_im->setItemToField(NAME_LEATHER,			_point.x, _point.y, identify, isCursed, upgrade, 1);

		break;
	case NAME_MAIL:
		_im->setItemToField(NAME_MAIL,				_point.x, _point.y, identify, isCursed, upgrade, 1);

		break;

		//악세사리
	case NAME_RING_POWER:
		_im->setItemToField(NAME_RING_POWER,		_point.x, _point.y, identify, isCursed, upgrade, 1);

		break;
	case NAME_RING_RECHARGE:
		_im->setItemToField(NAME_RING_RECHARGE,		_point.x, _point.y, identify, isCursed, upgrade, 1);

		break;
	case NAME_LIOYDS_BEACON:
		_im->setItemToField(NAME_LIOYDS_BEACON,		_point.x, _point.y, identify, isCursed, upgrade, 1);

		break;

		//투척
	case NAME_DART:
		_im->setItemToField(NAME_DART,				_point.x, _point.y, identify, isCursed, upgrade, 1);

		break;
	case NAME_PARALYSIS_DART:
		_im->setItemToField(NAME_PARALYSIS_DART,	_point.x, _point.y, identify, isCursed, upgrade, 1);

		break;
	case NAME_POISON_DART:
		_im->setItemToField(NAME_POISON_DART,		_point.x, _point.y, identify, isCursed, upgrade, 1);

		break;
		//완드
	case NAME_LIGHTNING:
		_im->setItemToField(NAME_LIGHTNING,			_point.x, _point.y, identify, isCursed, upgrade, 1);

		break;
	case NAME_NORMAL:
		_im->setItemToField(NAME_NORMAL,			_point.x, _point.y, identify, isCursed, upgrade, 1);

		break;
	case NAME_POISON:
		_im->setItemToField(NAME_POISON,			_point.x, _point.y, identify, isCursed, upgrade, 1);

		break;

		//음식
		//음식등의 아이템류는 위치만 지정해 줍니다. 저주받은 파스타 따위가 나올리가 없죠 물론 주문서와 물약도 동일합니다.
	case NAME_EMERGENCY:
		_im->setItemToField(NAME_EMERGENCY,			_point.x, _point.y);

		break;
	case NAME_PASTY:
		_im->setItemToField(NAME_PASTY,				_point.x, _point.y);

		break;
	case NAME_UNKNOWN_MEAT:
		_im->setItemToField(NAME_UNKNOWN_MEAT,		_point.x, _point.y);

		break;
	case NAME_COOKED_MEAT:
		_im->setItemToField(NAME_COOKED_MEAT,		_point.x, _point.y);

		break;
	case NAME_FROZEN_MEAT:
		_im->setItemToField(NAME_FROZEN_MEAT,		_point.x, _point.y);

		break;

		//주문서
	case NAME_IDENTIFY:
		_im->setItemToField(NAME_IDENTIFY,			_point.x, _point.y);

		break;
	case NAME_UPGRADE:
		_im->setItemToField(NAME_UPGRADE,			_point.x, _point.y);

		break;
	case NAME_PURIFY:
		_im->setItemToField(NAME_PURIFY,			_point.x, _point.y);

		break;
	case NAME_MAP:
		_im->setItemToField(NAME_MAP,				_point.x, _point.y);

		break;

		//물약
	case NAME_RECHARGE:
		_im->setItemToField(NAME_RECHARGE,			_point.x, _point.y);

		break;
	case NAME_BOTTLE:
		_im->setItemToField(NAME_BOTTLE,			_point.x, _point.y);

		break;
	case NAME_HEAL:
		_im->setItemToField(NAME_HEAL,				_point.x, _point.y);

		break;
	case NAME_STR:
		_im->setItemToField(NAME_STR,				 _point.x, _point.y);

		break;
	case NAME_EX:
		_im->setItemToField(NAME_EX,				_point.x, _point.y);

		break;
	case NAME_INVISIBLE:
		_im->setItemToField(NAME_INVISIBLE,			_point.x, _point.y);

		break;
	case NAME_LEVITATION:
		_im->setItemToField(NAME_LEVITATION,		_point.x, _point.y);

		break;
	case NAME_FROZEN:
		_im->setItemToField(NAME_FROZEN,			_point.x, _point.y);

		break;
	case NAME_LIQUID_FIRE:
		_im->setItemToField(NAME_LIQUID_FIRE,		_point.x, _point.y);

		break;
	case NAME_SEED_HEAL:
		_im->setItemToField(NAME_SEED_HEAL,			_point.x, _point.y);

		break;
	case NAME_SEED_FIRE:
		_im->setItemToField(NAME_SEED_FIRE,			_point.x, _point.y);

		break;
	case NAME_SEED_SNAKE:
		_im->setItemToField(NAME_SEED_SNAKE,		_point.x, _point.y);

		break;
	case NAME_SEED_FROST:
		_im->setItemToField(NAME_SEED_FROST,		_point.x, _point.y);

		break;
	case NAME_DEW:
		_im->setItemToField(NAME_DEW,				_point.x, _point.y);

		break;

		//돈은 머니 랜덤변수를 이용합니다
	case NAME_MONEY:
		_im->setItemToField(NAME_POISON,			_point.x, _point.y, false, false, 0, money);

		break;
	}
}

void Mimic::getDamaged(int damage)
{
	//자는 상태에서 맞았으면 내 상태를 변경해준다.
	if (_myState == ENEMYSTATE_SLEEP)
	{
		_myState = ENEMYSTATE_IDLE;
		_findPlayer = true;
	}

	//플레이어의 명중률을 0부터 플레이어의 명중률로 계산해서
	//그 값이 나의 회피율보다 낮으면
	//회피 성공
	int rnd = RND->getInt(_player->getStat().atk_lck);

	//회피했음
	if (rnd < _statistics.avd_lck)
	{
		//ui에 회피 했다는것을 띄울것
		return;
	}
	else
	{
		int hitGift = RND->getInt(2);
		if (hitGift == 2) _im->setItemToField(NAME_POISON, _point.x, _point.y, false, false, 0, money);

		_currntHp -= (damage - _statistics.def);

	}
}
