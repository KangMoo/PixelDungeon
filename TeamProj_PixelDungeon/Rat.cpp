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


//typedef struct tagEnemyStat {
//	int hp;			//체력
//	int str;		//힘
//	float atk_lck;	//명중률
//	float avd_lck;	//회피율
//}ENEMYSTAT;

HRESULT Rat::init(POINT point, int cog)
{
	//=======================================================================================================================================================
	//												*BROWNRATIMAGE*	
	//=======================================================================================================================================================

	IMAGEMANAGER->addFrameImage("brownIdle",	"Img\Enemy\rat\brownIdle.bmp",	64, 32, 2, 2,	true, RGB(255, 0, 255));//아이들인줄 알았는데 슬립이였다
	IMAGEMANAGER->addFrameImage("brownMove",	"Img\Enemy\rat\brownMove.bmp",	192, 64, 6, 2,	true, RGB(255, 0, 255));//무브인줄 알았는데 아이들이였다
	IMAGEMANAGER->addFrameImage("brownAttack",	"Img\Enemy\rat\brownAttack.bmp",96, 64, 3, 2,	true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("brownDead",	"Img\Enemy\rat\brownDead.bmp",	128, 64, 4, 2,	true, RGB(255, 0, 255));

	//=======================================================================================================================================================
	//												*WHITERATIMAGE*	
	//=======================================================================================================================================================

	IMAGEMANAGER->addFrameImage("whiteIdle",	"Img\Enemy\rat\whiteIdle.bmp",	64, 32, 2, 2,	true, RGB(255, 0, 255));//아이들인줄 알았는데 슬립이였다
	IMAGEMANAGER->addFrameImage("whiteMove",	"Img\Enemy\rat\whiteMove.bmp",	192, 64, 6, 2,	true, RGB(255, 0, 255));//무브인줄 알았는데 아이들이였다
	IMAGEMANAGER->addFrameImage("whiteAttack",	"Img\Enemy\rat\whiteAttack.bmp",96, 64, 3, 2,	true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("whiteDead",	"Img\Enemy\rat\whiteDead.bmp",	128, 64, 4, 2,	true, RGB(255, 0, 255));

	////=======================================================================================================================================================
	////												*BLACKIMAGE*	쥐 보스 입니다.
	////=======================================================================================================================================================
	//
	////IMAGEMANAGER->addFrameImage("blackIdle",	 "Img\Enemy\rat\blackIdle.bmp",		64, 32, 2, 1,	true, RGB(255, 0, 255));
	////IMAGEMANAGER->addFrameImage("blackMove",	 "Img\Enemy\rat\blackMove.bmp",		192, 64, 6, 2,	true, RGB(255, 0, 255));
	////IMAGEMANAGER->addFrameImage("blackAttack",	 "Img\Enemy\rat\blackAttack.bmp",	96, 64, 3, 2,	true, RGB(255, 0, 255));
	////IMAGEMANAGER->addFrameImage("blackDead",	 "Img\Enemy\rat\blackDead.bmp",		128, 64, 4, 2,	true, RGB(255, 0, 255));

	//==============================================*LV/STAT SETTING*=============================================================================================================

	//레벨 관련 설정
	_statistics.exp		= 1;						
	_statistics.lv		= _player->getStat().lv; //플레이어 레벨에 비례하여 오릅니다
	_statistics.maxLv	= 5;

	//최대레벨 고정
	if (_statistics.lv >= _statistics.maxLv) _statistics.lv = _statistics.maxLv;

	//알비노 쥐 확률
	_color		= RND->getFromIntTo(0, 30);		//랜덤으로 수를 불러옴
	_myColor	= _color == 0 ? WHITE : BROWN;	//삼항연산자로 판별, 30분의 1

	if (_myColor == WHITE)//흰 쥐의 경우 30분의 1 확률로 등장합니다.
	{
		//레벨에 비례하여 상승합니다.
		_statistics.hp	= 14 + _statistics.lv;
		_statistics.def = 3 + _statistics.lv;

		_image = IMAGEMANAGER->findImage("whiteIdle");//이미지 초기화
	}
	else //기본 쥐
	{
		//레벨이 비례하여 상승합니다.
		_statistics.hp	= 7 + _statistics.lv;
		_statistics.def = 3 + _statistics.lv;

		_image = IMAGEMANAGER->findImage("brownIdle");//이미지 초기화
	}

	_statistics.avd_lck = 4;
	_statistics.atk_lck = 11;

	//==============================================*CHARACTER INIT*=============================================================================================================
	
	//공격박스, 데미지 박스 설정
	_hitBox = RectMake(point.x, point.y, TILESIZE, TILESIZE);	//32로 고정을 해줍니다. 혹시 모르니까요.
	_attBox = RectMake(0, 0, 0, 0);								//일단 초기화를 해줍시다.
	
	_currntHp = _statistics.hp;									//초기 hp를 세팅해 줍니다.

	_hpBar->init(point.x, point.y, TILESIZE, 4);				//hp바의 위치 및 크기를 지정해 줍니다.
	_hpBar->setGauge(_currntHp, _statistics.hp);				//hp바를 세팅해줍니다.

	//==============================================*BOOL SETTING*=============================================================================================================
	
	_myState					= ENEMYSTATE_SLEEP;		//자고있습니다.

	_isLive						= true;					//살아있습니다.
	_action						= false;				//아직 내 턴이 아닙니다.
	_findPlayer					= false;				//플레이어를 찾지 못했습니다.
	int rightRendom				= RND->getInt(1);		//오른쪽 왼쪽을 랜덤으로 정합니다.
	if (rightRendom == 1)_right = true;					//오른쪽을 바라보는 중입니다.
	else _right					= false;				//왼쪽을 바라보는 중입니다.

	//==============================================*etc. SETTING*=============================================================================================================

	//=======================================================================================================================================================
	//*NOTICE
	//*FrameY가 0일시 right
	//*FrameY가 1일시 left
	//=======================================================================================================================================================

	_currentFrameX = 0;							//프레임을 초기화 해줍니다.
	if (_right == true)	_currentFrameY = 0;		
	else				_currentFrameY = 1;
	_image->setFrameX(_currentFrameX);			//이미지 프레임을 초기화 해줍니다.
	_image->setFrameY(_currentFrameY);			//이미지 프레임을 초기화 해줍니다.

	_deadAlpha = 255;							//죽으면 감소시킬 알파값

	_cog = RectMake(point.x, point.y, cog, cog);//플레이어를 찾아낼 거리

	_point.x = point.x;							//위치값
	_point.y = point.y;

	return S_OK;
}

void Rat::release()
{
	SAFE_RELEASE(_image);
	SAFE_DELETE(_image);
}

void Rat::update()
{
	//슬립 상태에서 플레이어의 레벨에 비례하여 레벨이 상승합니다.
	//레벨에 비례하여 능력치가 오릅니다.
	if (_myState == ENEMYSTATE_SLEEP)
	{
		_statistics.lv = _player->getStat().lv; //플레이어 레벨에 비례하여 오릅니다
		_statistics.maxLv = 5;

		if (_statistics.lv >= _statistics.maxLv)_statistics.lv = _statistics.maxLv;

		if (_myColor == WHITE)
		{
			//레벨에 비례하여 상승합니다.
			_statistics.hp = 14 + _statistics.lv;
			_statistics.def = 3 + _statistics.lv;
		}
		else //기본 쥐
		{
			//레벨이 비례하여 상승합니다.
			_statistics.hp = 7 + _statistics.lv;
			_statistics.def = 3 + _statistics.lv;
		}
	}

	//프레임을 업데이트 해줍니다.
	frameUpdate();

	//인식범위 내로 들어오면 인식을 함, 인식한 턴은 넘김
	if (PtInRect(&_cog, _player->getPoint()) && _myState == ENEMYSTATE_SLEEP)
	{
		_myState	= ENEMYSTATE_IDLE;
		_findPlayer = true;
		_action		= false;
	}

	//플레이어를 찾은 상태
	//플레이어를 인식한 상태니 다시는 Sleep로 들어가지 않는다.
	if (_findPlayer == true && _isLive == true)
	{
		_myState = ENEMYSTATE_IDLE;

		//나의 턴이 아닐때
		if (_action == false && _myColor == WHITE)
		{
			_image = IMAGEMANAGER->findImage("whiteMove");//알고보니 상대방 턴일때도 해당 이미지를 사용함
		}
		else if (_action == false && _myColor == BROWN)
		{
			_image = IMAGEMANAGER->findImage("brownMove");
		}

		//나의 턴일때 //색상여부 상관없음
		if (_action == true)
		{
			action();
		}
	}

	//hp바 업데이트
	_hpBar->setX(_point.x);
	_hpBar->setY(_point.y);
	_hpBar->setGauge(_currntHp, _statistics.hp);
	_hpBar->update();
	
	//죽었다.
	if (_currntHp <= 0)
	{
		_myState	= ENEMYSTATE_DEAD;
		_isLive		= false; //움직임을 멈춘다.
		_deadAlpha--;

		//UI에게 사망소식을 알린다.
		//플레이어에게 EXP를 넘긴다.
	}
}

void Rat::render(POINT camera)
{
	draw(camera);

}

void Rat::draw(POINT camera)
{
	RectangleMake(getMemDC(), _point.x + camera.x, _point.y + camera.y, TILESIZE, TILESIZE);
	//_image->frameRender(getMemDC(), _point.x + camera.x, _point.y + camera.y);
	_image->alphaFrameRender(getMemDC(), _point.x + camera.x, _point.y + camera.y, _currentFrameX, _currentFrameY, _deadAlpha);
	_hpBar->render();
}

void Rat::action()
{
	int distanceToPlayer = getDistance(_point.x, _point.y, _player->getPoint().x, _player->getPoint().y) / TILESIZE;

	//두칸 이상 떨어져 있으면 플레이어 위치로 움직입니다.
	if (distanceToPlayer < 2) move();
	//아닐시 플레이어 위치로 공격을 시도합니다.
	else attack();
}

void Rat::frameUpdate()
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
	//이동상태
	if (_myState == ENEMYSTATE_MOVE)
	{
		//흰 쥐
		if (_myColor == WHITE)		_image = IMAGEMANAGER->findImage("whiteMove");//이미지 변경
		else if (_myColor == BROWN)	_image = IMAGEMANAGER->findImage("brownMove");
	}
	//이동상태

	//공격상태
	if (_myState == ENEMYSTATE_ATTACK)
	{
		if (_myColor == WHITE)
		{
			_image = IMAGEMANAGER->findImage("whiteAttack");
			if (_currentFrameX > _image->getMaxFrameX())
			{
				_image		= IMAGEMANAGER->findImage("whiteIdle");
				_myState	= ENEMYSTATE_IDLE;
				_action		= false; //턴을 넘김다

			}
		}
		else if (_myColor == BROWN)
		{
			_image = IMAGEMANAGER->findImage("brownAttack");
			if (_currentFrameX > _image->getMaxFrameX())
			{
				_image		= IMAGEMANAGER->findImage("brownIdle");
				_myState	= ENEMYSTATE_IDLE;
				_action		= false;
			}
		}
	}
	//공격상태

	//죽은상태
	if (_myState == ENEMYSTATE_DEAD)
	{
		if (_myColor == WHITE)		_image = IMAGEMANAGER->findImage("whiteDead");
		else if (_myColor == BROWN)	_image = IMAGEMANAGER->findImage("brownDead");
	}
	//죽은상태

	//==============================================*FRAME UPDATE*========================================
	
	_frameFPS = 10;//프레임 속도 조절용
	_frameTime++;

	if (_frameFPS <= _frameTime)//프레임을 넘긴다
	{
		_currentFrameX++;
		_frameTime = 0;
	}

	//프레임 초기화
	if (_currentFrameX >= _image->getMaxFrameX() &&
		_myState	   != ENEMYSTATE_DEAD) _currentFrameX = 0;	//죽은상태가 아니면 프레임을 초기화 한다.

	//==============================================*FRAME UPDATE*========================================
}

void Rat::attack()
{
	//플레이어의 위치를 찾아서 그 방향에 어택렉트를 생성해 줍니다. 그다음에 초기화를 시켜줍시다.

	//상태를 변경합니다.
	_myState = ENEMYSTATE_ATTACK;

	//공격렉트르 설정합니다.
	_attBox = RectMake(_player->getPoint().x, _player->getPoint().y, TILESIZE, TILESIZE);

	//흰 쥐는 일정 확률로 출혈을 일으키고 공격력도 다릅니다.
	if (_myColor == WHITE)
	{
		//공격력 랜덤으로 나옵니다.
		_statistics.str = RND->getFromIntTo(3 + (_statistics.lv * 1), 5 + (_statistics.lv * 2));

		int bleed = RND->getInt(2);

		if (bleed == 2)//출혈 디버프
		{
			//_player.
		}
	}
	//갈색쥐는 출혈을 일으키지 않습니다.
	else if (_myColor == BROWN)
	{
		_statistics.str = RND->getFromIntTo(2 + (_statistics.lv * 1), 5 + (_statistics.lv * 2));
	}

	//_player->getDamaged(_statistics.str);
	_attBox = RectMake(0, 0, 0, 0);//초기화

	_action = false; //턴을 넘김다
}

void Rat::move()
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
		if (_myColor == WHITE)	_image = IMAGEMANAGER->findImage("whiteIdle"); //흰색
		else					_image = IMAGEMANAGER->findImage("brownIdle"); //갈색

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

void Rat::getDamaged(int damage)
{
	_currntHp -= (damage - _statistics.def);
}