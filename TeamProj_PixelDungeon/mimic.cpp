#include "stdafx.h"
#include "Mimic.h"
#include "Player.h"
#include "Map.h"
#include "UI.h"

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

	IMAGEMANAGER->addFrameImage("mimicDisable", "Img\Enemy\mimic\mimic_disable.bmp", 32, 32, 1, 2, true, RGB(255, 0, 255));//아이들인줄 알았는데 슬립이였다
	IMAGEMANAGER->addFrameImage("mimicMove", "Img\Enemy\mimic\mimic_move.bmp", 64, 64, 2, 2, true, RGB(255, 0, 255));//무브인줄 알았는데 아이들이였다
	IMAGEMANAGER->addFrameImage("mimicStay", "Img\Enemy\mimic\mimic_stay.bmp", 160, 64, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mimicDead", "Img\Enemy\mimic\mimic_dead.bmp", 128, 64, 4, 2, true, RGB(255, 0, 255));

	//=======================================================================================================================================================
	//												*MIMICINIT*	
	//=======================================================================================================================================================

	_myState = ENEMYSTATE_SLEEP; //SLEEP == DISABLE

	_statistics.exp = 2 + (_statistics.lv - 1) * 2 / 5;
	_statistics.lv = 1;  //플레이어 레벨에 비례하여 오릅니다.
	_statistics.maxLv = 30;

	_statistics.hp = 12 + (_statistics.lv * 4);//레벨에 비례하여 상승합니다.

	_statistics.def = 0;

	_image = IMAGEMANAGER->findImage("mimicDisable");

	_currntHp = _statistics.hp;

	_hpBar->init(point.x, point.y, 32, 4);
	_hpBar->setGauge(_currntHp, _statistics.hp);//hp바를 세팅해줍니다.

	_myState = ENEMYSTATE_SLEEP;				//자고았습니다.

	_isLive = true;								//살아있습니다.
	_action = false;							//아직 내 턴이 아닙니다.

	_currentFrameX = 0;							//프레임을 초기화 해줍니다.
	_currentFrameY = 0;							//프레임을 초기화 해줍니다.

	_hitBox = RectMake(point.x, point.y, 32, 32);	//32로 고정을 해줍니다. 혹시 모르니까요.
	_attBox = RectMake(0, 0, 0, 0);				//일단 초기화를 해줍시다.

	_findPlayer = false;						//플레이어를 찾지 못했습니다.
	_playerChack = false;						//플레이어가 건드리지 않았습니다.
	_mimicAct = false;							//아직 활동중이 아닙니다.

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
	if (_player->getPoint().x > _point.x)_right = true;
	else _right = false;

	frameUpdate();

	if (_isLive == true)
	{
		if (PtInRect(&_cog, _player->getPoint()))//플레이어를 찾아내고 말았다.
		{
			_findPlayer == true;
		}

		if (_action == false)//Sleep 상태가 아닐시
		{
			_image = IMAGEMANAGER->findImage("mimicStay");
		}

		if (_action == true && _findPlayer == true)//나의 턴일때
		{
			action();
		}
	}

	if (_currntHp <= 0)//현재 체력이 0에 수렴
	{
		_myState = ENEMYSTATE_DEAD;
		_isLive = false;
	}
	if (_myState == ENEMYSTATE_DEAD)
	{
		_deadAlpha--;
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

}

void Mimic::action()
{

}

void Mimic::attack()
{

}

void Mimic::move()
{

}

void Mimic::frameUpdate()
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

void Mimic::getDamaged(int damage)
{

}
