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

	IMAGEMANAGER->addFrameImage("mimicDisable", "Img\Enemy\mimic\mimic_disable.bmp", 32, 32, 1, 2, true, RGB(255, 0, 255));//���̵����� �˾Ҵµ� �����̿���
	IMAGEMANAGER->addFrameImage("mimicMove", "Img\Enemy\mimic\mimic_move.bmp", 64, 64, 2, 2, true, RGB(255, 0, 255));//�������� �˾Ҵµ� ���̵��̿���
	IMAGEMANAGER->addFrameImage("mimicStay", "Img\Enemy\mimic\mimic_stay.bmp", 160, 64, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mimicDead", "Img\Enemy\mimic\mimic_dead.bmp", 128, 64, 4, 2, true, RGB(255, 0, 255));

	//=======================================================================================================================================================
	//												*MIMICINIT*	
	//=======================================================================================================================================================

	_myState = ENEMYSTATE_SLEEP; //SLEEP == DISABLE

	_statistics.exp = 2 + (_statistics.lv - 1) * 2 / 5;
	_statistics.lv = 1;  //�÷��̾� ������ ����Ͽ� �����ϴ�.
	_statistics.maxLv = 30;

	_statistics.hp = 12 + (_statistics.lv * 4);//������ ����Ͽ� ����մϴ�.

	_statistics.def = 0;

	_image = IMAGEMANAGER->findImage("mimicDisable");

	_currntHp = _statistics.hp;

	_hpBar->init(point.x, point.y, 32, 4);
	_hpBar->setGauge(_currntHp, _statistics.hp);//hp�ٸ� �������ݴϴ�.

	_myState = ENEMYSTATE_SLEEP;				//�ڰ�ҽ��ϴ�.

	_isLive = true;								//����ֽ��ϴ�.
	_action = false;							//���� �� ���� �ƴմϴ�.

	_currentFrameX = 0;							//�������� �ʱ�ȭ ���ݴϴ�.
	_currentFrameY = 0;							//�������� �ʱ�ȭ ���ݴϴ�.

	_hitBox = RectMake(point.x, point.y, 32, 32);	//32�� ������ ���ݴϴ�. Ȥ�� �𸣴ϱ��.
	_attBox = RectMake(0, 0, 0, 0);				//�ϴ� �ʱ�ȭ�� ���ݽô�.

	_findPlayer = false;						//�÷��̾ ã�� ���߽��ϴ�.
	_playerChack = false;						//�÷��̾ �ǵ帮�� �ʾҽ��ϴ�.
	_mimicAct = false;							//���� Ȱ������ �ƴմϴ�.

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
		if (PtInRect(&_cog, _player->getPoint()))//�÷��̾ ã�Ƴ��� ���Ҵ�.
		{
			_findPlayer == true;
		}

		if (_action == false)//Sleep ���°� �ƴҽ�
		{
			_image = IMAGEMANAGER->findImage("mimicStay");
		}

		if (_action == true && _findPlayer == true)//���� ���϶�
		{
			action();
		}
	}

	if (_currntHp <= 0)//���� ü���� 0�� ����
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
