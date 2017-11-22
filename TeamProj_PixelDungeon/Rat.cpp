#include "stdafx.h"
#include "Rat.h"


Rat::Rat()
{
}


Rat::~Rat()
{
}


//typedef struct tagEnemyStat {
//	int hp;			//ü��
//	int str;		//��
//	float atk_lck;	//���߷�
//	float avd_lck;	//ȸ����
//}ENEMYSTAT;

HRESULT Rat::init(POINT point)
{
	//=======================================================================================================================================================
	//												*BROWNRATIMAGE*	
	//=======================================================================================================================================================

	IMAGEMANAGER->addFrameImage("brownIdle", "Img\Enemy\rat\brownIdle.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));//���̵����� �˾Ҵµ� �����̿���
	IMAGEMANAGER->addFrameImage("brownMove", "Img\Enemy\rat\brownMove.bmp", 192, 64, 6, 2, true, RGB(255, 0, 255));//�������� �˾Ҵµ� ���̵��̿���
	IMAGEMANAGER->addFrameImage("brownAttack", "Img\Enemy\rat\brownAttack.bmp", 96, 64, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("brownDead", "Img\Enemy\rat\brownDead.bmp", 128, 64, 4, 2, true, RGB(255, 0, 255));

	//=======================================================================================================================================================
	//												*WHITERATIMAGE*	
	//=======================================================================================================================================================

	IMAGEMANAGER->addFrameImage("whiteIdle", "Img\Enemy\rat\whiteIdle.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));//���̵����� �˾Ҵµ� �����̿���
	IMAGEMANAGER->addFrameImage("whiteMove", "Img\Enemy\rat\whiteMove.bmp", 192, 64, 6, 2, true, RGB(255, 0, 255));//�������� �˾Ҵµ� ���̵��̿���
	IMAGEMANAGER->addFrameImage("whiteAttack", "Img\Enemy\rat\whiteAttack.bmp", 96, 64, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("whiteDead", "Img\Enemy\rat\whiteDead.bmp", 128, 64, 4, 2, true, RGB(255, 0, 255));

	//=======================================================================================================================================================
	//												*BLACKIMAGE*	�� ���� �Դϴ�.
	//=======================================================================================================================================================

	//IMAGEMANAGER->addFrameImage("blackIdle",	 "Img\Enemy\rat\blackIdle.bmp",		64, 32, 2, 1,	true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("blackMove",	 "Img\Enemy\rat\blackMove.bmp",		192, 64, 6, 2,	true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("blackAttack",	 "Img\Enemy\rat\blackAttack.bmp",	96, 64, 3, 2,	true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("blackDead",	 "Img\Enemy\rat\blackDead.bmp",		128, 64, 4, 2,	true, RGB(255, 0, 255));

	//=======================================================================================================================================================
	//												*CHARACTERINIT*	
	//=======================================================================================================================================================

	_color = RND->getFromIntTo(0, 30);

	_myColor = _color == 0 ? WHITE : BROWN;//���׿����ڷ� �Ǻ��մϴ�.

	if (_myColor == WHITE)//�� ���� ��� 30���� 1 Ȯ���� �����մϴ�. �� ģ���� �̸��� �˺�� �� �Դϴ�.
	{
		_statistics.exp = 1;
		_statistics.lv = 1;  //�÷��̾� ������ ����Ͽ� �����ϴ�.
		_statistics.maxLv = 5;

		_statistics.hp = 14 + _statistics.lv;//������ ����Ͽ� ����մϴ�.
		_currntHp = _statistics.hp;

		_hpBar->init(point.x, point.y, 32, 4);
		_hpBar->setGauge(_currntHp, _statistics.hp);

		_statistics.str = RND->getFromIntTo(2 + _statistics.lv, 6 + _statistics.lv);
		_statistics.def = 3 + _statistics.lv;

		_myState = ENEMYSTATE_SLEEP;

		_image = IMAGEMANAGER->findImage("whiteIdle");

	}
	else //�⺻ ��
	{
		_statistics.exp = 1;
		_statistics.lv = 1; //�÷��̾� ������ ����Ͽ� �����ϴ�
		_statistics.maxLv = 5;

		_statistics.hp = 7 + _statistics.lv;	
		_currntHp = _statistics.hp;//������ ����Ͽ� ����մϴ�

		_hpBar->init(point.x, point.y, 32, 4);
		_hpBar->setGauge(_currntHp, _statistics.hp);

		_statistics.str = RND->getFromIntTo(3 + _statistics.lv, 5 + _statistics.lv);
		_statistics.def = 3 + _statistics.lv;

		_myState = ENEMYSTATE_SLEEP;

		_image = IMAGEMANAGER->findImage("brownIdle");
	}
	_isLive = true;
	_action = false;

	_currentFrameX = 0;
	_currentFrameY = 0;

	_hitBox = RectMake(point.x, point.y,32,32);//32�� ������ ���ݴϴ�. Ȥ�� �𸣴ϱ��.
	_attBox = RectMake(0, 0, 0, 0);//�ϴ� �ʱ�ȭ�� ���ݽô�.

	_findPlayer = false;

	return S_OK;
}

void Rat::release()
{

}

void Rat::update()
{
	frameUpdate();

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

}

void Rat::action()
{
	move();

	attack();
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

	if (_currentFrameX > _image->getMaxFrameX())
	{
		_currentFrameX = 0;
		_action = false;	//�̹����� �� �Ǿ����� ���� �ѱ��.
	}

	if (_right)_currentFrameY = 0;
	else _currentFrameY = 1;
}

void Rat::attack()
{
	//�÷��̾��� ��ġ�� ã�Ƽ� �� ���⿡ ���÷�Ʈ�� ������ �ݴϴ�. �״����� �ʱ�ȭ�� �����ݽô�.
}

void Rat::move()
{
	//���̽�Ÿ
}
