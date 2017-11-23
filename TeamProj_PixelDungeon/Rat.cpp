#include "stdafx.h"
#include "Rat.h"


Rat::Rat()
{
}


Rat::~Rat()
{
}


//typedef struct tagEnemyStat {
//	int hp;			//체력
//	int str;		//힘
//	float atk_lck;	//명중률
//	float avd_lck;	//회피율
//}ENEMYSTAT;

HRESULT Rat::init(POINT point)
{
	//=======================================================================================================================================================
	//												*BROWNRATIMAGE*	
	//=======================================================================================================================================================

	IMAGEMANAGER->addFrameImage("brownIdle", "Img\Enemy\rat\brownIdle.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));//아이들인줄 알았는데 슬립이였다
	IMAGEMANAGER->addFrameImage("brownMove", "Img\Enemy\rat\brownMove.bmp", 192, 64, 6, 2, true, RGB(255, 0, 255));//무브인줄 알았는데 아이들이였다
	IMAGEMANAGER->addFrameImage("brownAttack", "Img\Enemy\rat\brownAttack.bmp", 96, 64, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("brownDead", "Img\Enemy\rat\brownDead.bmp", 128, 64, 4, 2, true, RGB(255, 0, 255));

	//=======================================================================================================================================================
	//												*WHITERATIMAGE*	
	//=======================================================================================================================================================

	IMAGEMANAGER->addFrameImage("whiteIdle", "Img\Enemy\rat\whiteIdle.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));//아이들인줄 알았는데 슬립이였다
	IMAGEMANAGER->addFrameImage("whiteMove", "Img\Enemy\rat\whiteMove.bmp", 192, 64, 6, 2, true, RGB(255, 0, 255));//무브인줄 알았는데 아이들이였다
	IMAGEMANAGER->addFrameImage("whiteAttack", "Img\Enemy\rat\whiteAttack.bmp", 96, 64, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("whiteDead", "Img\Enemy\rat\whiteDead.bmp", 128, 64, 4, 2, true, RGB(255, 0, 255));

	//=======================================================================================================================================================
	//												*BLACKIMAGE*	쥐 보스 입니다.
	//=======================================================================================================================================================

	//IMAGEMANAGER->addFrameImage("blackIdle",	 "Img\Enemy\rat\blackIdle.bmp",		64, 32, 2, 1,	true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("blackMove",	 "Img\Enemy\rat\blackMove.bmp",		192, 64, 6, 2,	true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("blackAttack",	 "Img\Enemy\rat\blackAttack.bmp",	96, 64, 3, 2,	true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("blackDead",	 "Img\Enemy\rat\blackDead.bmp",		128, 64, 4, 2,	true, RGB(255, 0, 255));

	//=======================================================================================================================================================
	//												*COLORSETTING*	
	//=======================================================================================================================================================

	_color = RND->getFromIntTo(0, 30);

	_myColor = _color == 0 ? WHITE : BROWN;//삼항연산자로 판별합니다.

	if (_myColor == WHITE)//흰 쥐의 경우 30분의 1 확률로 등장합니다. 이 친구의 이름은 알비노 쥐 입니다.
	{
		_statistics.exp = 1;
		_statistics.lv = 1;  //플레이어 레벨에 비례하여 오릅니다.
		_statistics.maxLv = 5;

		_statistics.hp = 14 + _statistics.lv;//레벨에 비례하여 상승합니다.
		_currntHp = _statistics.hp;

		_statistics.def = 3 + _statistics.lv;

		_image = IMAGEMANAGER->findImage("whiteIdle");

	}
	else //기본 쥐
	{
		_statistics.exp = 1;
		_statistics.lv = 1; //플레이어 레벨에 비례하여 오릅니다
		_statistics.maxLv = 5;

		_statistics.hp = 7 + _statistics.lv;	
		_currntHp = _statistics.hp;//레벨에 비례하여 상승합니다


		_statistics.str = RND->getFromIntTo(3 + _statistics.lv, 5 + _statistics.lv);
		_statistics.def = 3 + _statistics.lv;


		_image = IMAGEMANAGER->findImage("brownIdle");
	}

	//=======================================================================================================================================================
	//												*CHARACTERINIT*	
	//=======================================================================================================================================================

	_hpBar->init(point.x, point.y, 32, 4);		
	_hpBar->setGauge(_currntHp, _statistics.hp);//hp바를 세팅해줍니다.

	_myState = ENEMYSTATE_SLEEP;				//자고았습니다.

	_isLive = true;								//살아있습니다.
	_action = false;							//아직 내 턴이 아닙니다.

	_currentFrameX = 0;							//프레임을 초기화 해줍니다.
	_currentFrameY = 0;							//프레임을 초기화 해줍니다.

	_hitBox = RectMake(point.x, point.y,32,32);	//32로 고정을 해줍니다. 혹시 모르니까요.
	_attBox = RectMake(0, 0, 0, 0);				//일단 초기화를 해줍시다.

	_findPlayer = false;						//플레이어를 찾지 못했습니다.

	_point.x = point.x;
	_point.y = point.y;

	return S_OK;
}

void Rat::release()
{

}

void Rat::update()
{
	frameUpdate();

	if (_action == false && _myColor == WHITE)//알고보니 턴을 넘긴 후에 점프 하더라고요;
	{
		_image = IMAGEMANAGER->findImage("whiteMove");
	}
	else if (_action == false && _myColor == BROWN)
	{
		_image = IMAGEMANAGER->findImage("brownMove");
	}
	if (_action == true)
	{
		action();
	}
}

void Rat::render(POINT camera)
{
	draw(camera);
}

void Rat::draw(POINT camera)
{
	RectangleMake(getMemDC(), _point.x, _point.y, 32, 32);
	_image->frameRender(getMemDC(), _point.x, _point.y);
}

void Rat::action()
{
	if (false)
	{
		//플레이어가 멀리 있을때
		move();
	}
	else if (false)
	{
		//플레이어가 가까이 있을때
		attack();
	}
}

void Rat::frameUpdate()
{
	_frameFPS = 10;
	_frameTime++;

	if (_frameFPS <= _frameTime)
	{
		_currentFrameX++;
		_frameTime = 0;
	}

	if (_right)_currentFrameY = 0;
	else _currentFrameY = 1;
}

void Rat::attack()
{
	//플레이어의 위치를 찾아서 그 방향에 어택렉트를 생성해 줍니다. 그다음에 초기화를 시켜줍시다.

	_myState = ENEMYSTATE_ATTACK;

	if (_myColor == WHITE)
	{
		_image = IMAGEMANAGER->findImage("whiteAttack");
		_statistics.str = RND->getFromIntTo(2 + _statistics.lv, 6 + _statistics.lv);

		if (_currentFrameX > _image->getMaxFrameX())
		{

			_image = IMAGEMANAGER->findImage("whiteIdle");
			_myState = ENEMYSTATE_IDLE;
			_action = false; //턴을 넘김다

		}
	}
	else if (_myColor == BROWN)
	{
		_image = IMAGEMANAGER->findImage("brownAttack");
		_statistics.str = RND->getFromIntTo(3 + _statistics.lv, 5 + _statistics.lv);


		if (_currentFrameX > _image->getMaxFrameX())
		{
			
			_image = IMAGEMANAGER->findImage("brownIdle");
			_myState = ENEMYSTATE_IDLE;
			_action = false;

		}
	}


	//_attBox = RectMake
}

void Rat::move()
{
	//에이스타로 적을 따라 이동합니다.

	_myState = ENEMYSTATE_MOVE;

	if (_myColor == WHITE)
	{
		_image = IMAGEMANAGER->findImage("whiteMove");
		if (_currentFrameX > _image->getMaxFrameX())
		{

			_image = IMAGEMANAGER->findImage("whiteIdle");
			_myState = ENEMYSTATE_IDLE;
			_action = false;

		}

	}
	else if (_myColor == BROWN)
	{
		_image = IMAGEMANAGER->findImage("brownMove");

		if (_currentFrameX > _image->getMaxFrameX())
		{
			_image = IMAGEMANAGER->findImage("brownIdle");
			_myState = ENEMYSTATE_IDLE;
			_action = false;
		}
	}

}

void getDamaged(int damage)
{

}