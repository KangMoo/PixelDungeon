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
	//												*COLORSETTING*	
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

		_statistics.def = 3 + _statistics.lv;

		_image = IMAGEMANAGER->findImage("whiteIdle");

	}
	else //�⺻ ��
	{
		_statistics.exp = 1;
		_statistics.lv = 1; //�÷��̾� ������ ����Ͽ� �����ϴ�
		_statistics.maxLv = 5;

		_statistics.hp = 7 + _statistics.lv;	
		_currntHp = _statistics.hp;//������ ����Ͽ� ����մϴ�


		_statistics.str = RND->getFromIntTo(3 + _statistics.lv, 5 + _statistics.lv);
		_statistics.def = 3 + _statistics.lv;


		_image = IMAGEMANAGER->findImage("brownIdle");
	}

	//=======================================================================================================================================================
	//												*CHARACTERINIT*	
	//=======================================================================================================================================================

	_hpBar->init(point.x, point.y, 32, 4);		
	_hpBar->setGauge(_currntHp, _statistics.hp);//hp�ٸ� �������ݴϴ�.

	_myState = ENEMYSTATE_SLEEP;				//�ڰ�ҽ��ϴ�.

	_isLive = true;								//����ֽ��ϴ�.
	_action = false;							//���� �� ���� �ƴմϴ�.

	_currentFrameX = 0;							//�������� �ʱ�ȭ ���ݴϴ�.
	_currentFrameY = 0;							//�������� �ʱ�ȭ ���ݴϴ�.

	_hitBox = RectMake(point.x, point.y,32,32);	//32�� ������ ���ݴϴ�. Ȥ�� �𸣴ϱ��.
	_attBox = RectMake(0, 0, 0, 0);				//�ϴ� �ʱ�ȭ�� ���ݽô�.

	_findPlayer = false;						//�÷��̾ ã�� ���߽��ϴ�.

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

	if (_action == false && _myColor == WHITE)//�˰��� ���� �ѱ� �Ŀ� ���� �ϴ�����;
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
		//�÷��̾ �ָ� ������
		move();
	}
	else if (false)
	{
		//�÷��̾ ������ ������
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
	//�÷��̾��� ��ġ�� ã�Ƽ� �� ���⿡ ���÷�Ʈ�� ������ �ݴϴ�. �״����� �ʱ�ȭ�� �����ݽô�.

	_myState = ENEMYSTATE_ATTACK;

	if (_myColor == WHITE)
	{
		_image = IMAGEMANAGER->findImage("whiteAttack");
		_statistics.str = RND->getFromIntTo(2 + _statistics.lv, 6 + _statistics.lv);

		if (_currentFrameX > _image->getMaxFrameX())
		{

			_image = IMAGEMANAGER->findImage("whiteIdle");
			_myState = ENEMYSTATE_IDLE;
			_action = false; //���� �ѱ��

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
	//���̽�Ÿ�� ���� ���� �̵��մϴ�.

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