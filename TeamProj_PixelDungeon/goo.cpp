#include "stdafx.h"
#include "goo.h"
#include "Player.h"
#include "UI.h"
#include "Map.h"
#include "itemManager.h"

goo::goo()
{
}


goo::~goo()
{
}

HRESULT goo::init(POINT point, int cog)
{
	//=======================================================================================================================================================
	//												*GOOIMAGE*	
	//=======================================================================================================================================================

	IMAGEMANAGER->addFrameImage("gooMove", "Img\Enemy\mimic\mimic_move.bmp", 64, 64, 2, 2, true, RGB(255, 0, 255));//무브인줄 알았는데 아이들이였다
	IMAGEMANAGER->addFrameImage("gooStay", "Img\Enemy\mimic\mimic_stay.bmp", 160, 64, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("gooDead", "Img\Enemy\mimic\mimic_dead.bmp", 128, 64, 4, 2, true, RGB(255, 0, 255));

	//=======================================================================================================================================================
	//												*GOOINIT*	
	//=======================================================================================================================================================

	//==============================================*LV/STAT SETTING*=============================================================================================================

	_statistics.exp = 10;
	_statistics.lv = 1;  //플레이어 레벨에 비례하여 오릅니다.
	_statistics.maxLv = 30;

	//최대레벨 고정
	if (_statistics.lv >= _statistics.maxLv) _statistics.lv = _statistics.maxLv;

	_statistics.hp = 80 + (_statistics.lv * 4);//레벨에 비례하여 상승합니다.
	_statistics.def = 12;

	_image = IMAGEMANAGER->findImage("gooStay");

	_statistics.avd_lck = 15;
	_statistics.atk_lck = 15;

	//==============================================*CHARACTER INIT*=============================================================================================================

	_hitBox = RectMake(point.x, point.y, TILESIZE, TILESIZE);	//32로 고정을 해줍니다. 혹시 모르니까요.
	_attBox = RectMake(0, 0, 0, 0);								//일단 초기화를 해줍시다.

	_currntHp = _statistics.hp;

	//_hpBar->init(point.x, point.y, TILESIZE, 4);
	//_hpBar->setGauge(_currntHp, _statistics.hp);//hp바를 세팅해줍니다.

	//==============================================*BOOL SETTING*=============================================================================================================

	_myState = ENEMYSTATE_SLEEP;//SLEEP == DISABLE

	_isLive = true;		//살아있습니다.
	_action = false;	//아직 내 턴이 아닙니다.
	_findPlayer = false;	//파인드 플레이어가 플레이어 건드렸는지의 여부입니다.

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

	pumpIt = false; //매우 강-력한 공격입니다.
	trunCount = 0; //펌프잇 쓰기위한 턴 카운트, 2가 되면 매우 강력한 공격을 시도 합니다.

	return S_OK;
}

void goo::release()
{
	SAFE_RELEASE(_image);
	SAFE_DELETE(_image);
}

void goo::update()
{
	if (_myState == ENEMYSTATE_SLEEP)
	{
		_statistics.lv = _player->getStat().lv; //플레이어 레벨에 비례하여 오릅니다
		_statistics.hp = 80 + (_statistics.lv * 4);//레벨에 비례하여 상승합니다.

		if (_statistics.lv >= _statistics.maxLv)_statistics.lv = _statistics.maxLv;
	}

	frameUpdate();

	//플레이어 찾는거

	if (_findPlayer == false)
	{
		_findPlayer = true;
		_myState = ENEMYSTATE_IDLE;
		_image = IMAGEMANAGER->findImage("gooStay");
		_action = false;
	}

	//플레이어와 멀어졌다 해서 다시 비활동 상태로 돌아가지는 않는다.
	if (_isLive == true && _findPlayer == true)
	{
		_myState = ENEMYSTATE_IDLE;

		if (_action == false)
		{
			_image = IMAGEMANAGER->findImage("gooStay");
		}

		if (_action == true)//나의 턴일때
		{
			action();
		}
	}

	if (_currntHp <= 0)
	{
		_myState = ENEMYSTATE_DEAD;
		_isLive = false; //움직임을 멈춘다.
		_deadAlpha--;

		//UI에게 사망소식을 알린다.
		//플레이어에게 EXP를 넘긴다.
		//미믹은 랜덤하게 아이템을 뱉는다.

		//itemDrop();
	}

}

void goo::render(POINT camera)
{
	draw(camera);
}

void goo::draw(POINT camera)
{
	RectangleMake(getMemDC(), _point.x + camera.x, _point.y + camera.y, 32, 32);
	//_image->frameRender(getMemDC(), _point.x + camera.x, _point.y + camera.y);
	_image->alphaFrameRender(getMemDC(), _point.x + camera.x, _point.y + camera.y, _currentFrameX, _currentFrameY, _deadAlpha);

}

void goo::action()
{
	int distanceToPlayer = getDistance(_point.x, _point.y, _player->getPoint().x, _player->getPoint().y) / TILESIZE;
	int rnd = RND->getInt(2);
	//두칸 이상 떨어져 있으면 플레이어 위치로 움직입니다.
	if (distanceToPlayer < 2) move();
	//아닐시 플레이어 위치로 공격을 시도합니다.
	else if (rnd == 2) pumpIt = true;
	else attack();

}

void goo::attack()
{
	//타일 카운트를 늘려준다
	if (pumpIt == true)
	{
		trunCount++;
		_action = false;
	}
	//사용한다!
	else if (pumpIt == true && trunCount == 2)
	{
		trunCount = 0;
		_action = false;
	}
	//평타
	else
	{

	}
}

void goo::move()
{

}

void goo::frameUpdate()
{

}

void goo::getDamaged(int damage)
{

}
