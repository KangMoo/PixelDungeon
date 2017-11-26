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

	IMAGEMANAGER->addFrameImage("mimicDisable", "Img\Enemy\mimic\mimic_disable.bmp",32,	32, 1, 2, true, RGB(255, 0, 255));//아이들인줄 알았는데 슬립이였다
	IMAGEMANAGER->addFrameImage("mimicMove",	"Img\Enemy\mimic\mimic_move.bmp",	64,	64, 2, 2, true, RGB(255, 0, 255));//무브인줄 알았는데 아이들이였다
	IMAGEMANAGER->addFrameImage("mimicStay",	"Img\Enemy\mimic\mimic_stay.bmp",	160,64, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mimicDead",	"Img\Enemy\mimic\mimic_dead.bmp",	128,64, 4, 2, true, RGB(255, 0, 255));

	//=======================================================================================================================================================
	//												*MIMICINIT*	
	//=======================================================================================================================================================

	//==============================================*LV/STAT SETTING*=============================================================================================================

	_statistics.exp		= 2 + (_statistics.lv - 1) * 2 / 5;
	_statistics.lv		= 1;  //플레이어 레벨에 비례하여 오릅니다.
	_statistics.maxLv	= 30;

	//최대레벨 고정
	if (_statistics.lv >= _statistics.maxLv) _statistics.lv = _statistics.maxLv;

	_statistics.hp	= 12 + (_statistics.lv * 4);//레벨에 비례하여 상승합니다.
	_statistics.def = 3 + _statistics.lv;

	_image = IMAGEMANAGER->findImage("mimicDisable");

	_statistics.avd_lck = 4;
	_statistics.atk_lck = 11;

	//==============================================*CHARACTER INIT*=============================================================================================================

	_hitBox = RectMake(point.x, point.y, TILESIZE, TILESIZE);	//32로 고정을 해줍니다. 혹시 모르니까요.
	_attBox = RectMake(0, 0, 0, 0);								//일단 초기화를 해줍시다.

	_currntHp = _statistics.hp;

	_hpBar->init(point.x, point.y, TILESIZE, 4);
	_hpBar->setGauge(_currntHp, _statistics.hp);//hp바를 세팅해줍니다.

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

		_hpBar->setX(_point.x);
		_hpBar->setY(_point.y);
		_hpBar->setGauge(_currntHp, _statistics.hp);
		_hpBar->update();
	}

	if (_currntHp <= 0)
	{
		_myState	= ENEMYSTATE_DEAD;
		_isLive		= false; //움직임을 멈춘다.
		_deadAlpha--;

		//UI에게 사망소식을 알린다.
		//플레이어에게 EXP를 넘긴다.
		//미믹은 랜덤하게 아이템을 뱉는다.
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
	if (_findPlayer == true)
	{
		_hpBar->render();
	}
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
	_statistics.str = RND->getFromIntTo(3 + (_statistics.lv * 1), 5 + (_statistics.lv * 2));

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

void Mimic::getDamaged(int damage)
{
	_currntHp -= (damage - _statistics.def);
}
