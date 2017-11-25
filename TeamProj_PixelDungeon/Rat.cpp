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
//	int hp;			//ü��
//	int str;		//��
//	float atk_lck;	//���߷�
//	float avd_lck;	//ȸ����
//}ENEMYSTAT;

HRESULT Rat::init(POINT point, int cog)
{
	//=======================================================================================================================================================
	//												*BROWNRATIMAGE*	
	//=======================================================================================================================================================

	IMAGEMANAGER->addFrameImage("brownIdle", "Img\Enemy\rat\brownIdle.bmp", 64, 32, 2, 2, true, RGB(255, 0, 255));//���̵����� �˾Ҵµ� �����̿���
	IMAGEMANAGER->addFrameImage("brownMove", "Img\Enemy\rat\brownMove.bmp", 192, 64, 6, 2, true, RGB(255, 0, 255));//�������� �˾Ҵµ� ���̵��̿���
	IMAGEMANAGER->addFrameImage("brownAttack", "Img\Enemy\rat\brownAttack.bmp", 96, 64, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("brownDead", "Img\Enemy\rat\brownDead.bmp", 128, 64, 4, 2, true, RGB(255, 0, 255));

	//=======================================================================================================================================================
	//												*WHITERATIMAGE*	
	//=======================================================================================================================================================

	IMAGEMANAGER->addFrameImage("whiteIdle", "Img\Enemy\rat\whiteIdle.bmp", 64, 32, 2, 2, true, RGB(255, 0, 255));//���̵����� �˾Ҵµ� �����̿���
	IMAGEMANAGER->addFrameImage("whiteMove", "Img\Enemy\rat\whiteMove.bmp", 192, 64, 6, 2, true, RGB(255, 0, 255));//�������� �˾Ҵµ� ���̵��̿���
	IMAGEMANAGER->addFrameImage("whiteAttack", "Img\Enemy\rat\whiteAttack.bmp", 96, 64, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("whiteDead", "Img\Enemy\rat\whiteDead.bmp", 128, 64, 4, 2, true, RGB(255, 0, 255));

	////=======================================================================================================================================================
	////												*BLACKIMAGE*	�� ���� �Դϴ�.
	////=======================================================================================================================================================
	//
	////IMAGEMANAGER->addFrameImage("blackIdle",	 "Img\Enemy\rat\blackIdle.bmp",		64, 32, 2, 1,	true, RGB(255, 0, 255));
	////IMAGEMANAGER->addFrameImage("blackMove",	 "Img\Enemy\rat\blackMove.bmp",		192, 64, 6, 2,	true, RGB(255, 0, 255));
	////IMAGEMANAGER->addFrameImage("blackAttack",	 "Img\Enemy\rat\blackAttack.bmp",	96, 64, 3, 2,	true, RGB(255, 0, 255));
	////IMAGEMANAGER->addFrameImage("blackDead",	 "Img\Enemy\rat\blackDead.bmp",		128, 64, 4, 2,	true, RGB(255, 0, 255));

	//==============================================*LV/STAT SETTING*=============================================================================================================

	//���� ���� ����
	_statistics.exp = 1;						
	_statistics.lv = _player->getStat().lv; //�÷��̾� ������ ����Ͽ� �����ϴ�
	_statistics.maxLv = 5;

	if (_statistics.lv <= _statistics.maxLv)//���� �ִ�ġ ����
	{
		_statistics.lv = _statistics.maxLv;
	}

	//�˺�� �� Ȯ��
	_color = RND->getFromIntTo(0, 30);		//�������� ���� �ҷ���
	_myColor = _color == 0 ? WHITE : BROWN;	//���׿����ڷ� �Ǻ�, 30���� 1

	if (_myColor == WHITE)//�� ���� ��� 30���� 1 Ȯ���� �����մϴ�.
	{
		//������ ����Ͽ� ����մϴ�.
		_statistics.hp = 14 + _statistics.lv;
		_statistics.def = 3 + _statistics.lv;

		_image = IMAGEMANAGER->findImage("whiteIdle");//�̹��� �ʱ�ȭ
	}
	else //�⺻ ��
	{
		//������ ����Ͽ� ����մϴ�.
		_statistics.hp = 7 + _statistics.lv;
		_statistics.def = 3 + _statistics.lv;

		_image = IMAGEMANAGER->findImage("brownIdle");//�̹��� �ʱ�ȭ
	}

	_statistics.avd_lck = 4;
	_statistics.atk_lck = 11;

	//==============================================*CHARACTER INIT*=============================================================================================================
	
	//���ݹڽ�, ������ �ڽ� ����
	_hitBox = RectMake(point.x, point.y, 32, 32);	//32�� ������ ���ݴϴ�. Ȥ�� �𸣴ϱ��.
	_attBox = RectMake(0, 0, 0, 0);					//�ϴ� �ʱ�ȭ�� ���ݽô�.
	
	_currntHp = _statistics.hp;						//�ʱ� hp�� ������ �ݴϴ�.

	_hpBar->init(point.x, point.y, 32, 4);			//hp���� ��ġ �� ũ�⸦ ������ �ݴϴ�.
	_hpBar->setGauge(_currntHp, _statistics.hp);	//hp�ٸ� �������ݴϴ�.

	//==============================================*BOOL SETTING*=============================================================================================================
	
	_myState					= ENEMYSTATE_SLEEP;		//�ڰ��ֽ��ϴ�.

	_isLive						= true;					//����ֽ��ϴ�.
	_action						= false;				//���� �� ���� �ƴմϴ�.
	_findPlayer					= false;				//�÷��̾ ã�� ���߽��ϴ�.
	int rightRendom				= RND->getInt(1);		//������ ������ �������� ���մϴ�.
	if (rightRendom == 1)_right = true;					//�������� �ٶ󺸴� ���Դϴ�.
	else _right					= false;				//������ �ٶ󺸴� ���Դϴ�.

	//==============================================*etc. SETTING*=============================================================================================================

	//=======================================================================================================================================================
	//*NOTICE
	//*FrameY�� 0�Ͻ� right
	//*FrameY�� 1�Ͻ� left
	//=======================================================================================================================================================

	_currentFrameX = 0;							//�������� �ʱ�ȭ ���ݴϴ�.
	if (_right == true)	_currentFrameY = 0;		
	else				_currentFrameY = 1;
	_image->setFrameX(_currentFrameX);			//�̹��� �������� �ʱ�ȭ ���ݴϴ�.
	_image->setFrameY(_currentFrameY);			//�̹��� �������� �ʱ�ȭ ���ݴϴ�.

	_deadAlpha = 255;							//������ ���ҽ�ų ���İ�

	_cog = RectMake(point.x, point.y, cog, cog);//�÷��̾ ã�Ƴ� �Ÿ�

	_point.x = point.x;							//��ġ��
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
	_statistics.lv = _player->getStat().lv; //�÷��̾� ������ ����Ͽ� �����ϴ�
	_statistics.maxLv = 5;

	if (_statistics.lv <= _statistics.maxLv)//���� �ִ�ġ ����
	{
		_statistics.lv = _statistics.maxLv;
	}

	//�������� ������Ʈ ���ݴϴ�.
	frameUpdate();

	//�νĹ��� ���� ������ �ν��� ��, �ν��� ���� �ѱ�
	if (PtInRect(&_cog, _player->getPoint()) && _myState == ENEMYSTATE_SLEEP)
	{
		_myState	= ENEMYSTATE_IDLE;
		_findPlayer = true;
		_action		= false;
	}

	//�÷��̾ ã�� ����
	//�÷��̾ �ν��� ���´� �ٽô� Sleep�� ���� �ʴ´�.
	if (_findPlayer == true && _isLive == true)
	{
		_myState = ENEMYSTATE_IDLE;

		//���� ���� �ƴҶ�
		if (_action == false && _myColor == WHITE)
		{
			_image = IMAGEMANAGER->findImage("whiteMove");//�˰��� ���� ���϶��� �ش� �̹����� �����
		}
		else if (_action == false && _myColor == BROWN)
		{
			_image = IMAGEMANAGER->findImage("brownMove");
		}

		//���� ���϶� //���󿩺� �������
		if (_action == true)
		{
			action();
		}
	}

	//hp�� ������Ʈ
	_hpBar->setX(_point.x);
	_hpBar->setY(_point.y);
	_hpBar->setGauge(_currntHp, _statistics.hp);
	_hpBar->update();
	
	//�׾���.
	if (_currntHp <= 0)
	{
		_myState	= ENEMYSTATE_DEAD;
		_isLive		= false; //�������� �����.
		_deadAlpha--;
	}
}

void Rat::render(POINT camera)
{
	draw(camera);
}

void Rat::draw(POINT camera)
{
	RectangleMake(getMemDC(), _point.x + camera.x, _point.y + camera.y, 32, 32);
	//_image->frameRender(getMemDC(), _point.x + camera.x, _point.y + camera.y);
	_image->alphaFrameRender(getMemDC(), _point.x + camera.x, _point.y + camera.y, _currentFrameX, _currentFrameY, _deadAlpha);
	_hpBar->render();
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
	//==*���� ����*==
	if (_findPlayer == true)
	{
		if (_player->getPoint().x > _point.x)	_right = true;
		else									_right = false;
	}

	//���⿡ ���� ������ ����
	if (_right)	_currentFrameY = 0;
	else		_currentFrameY = 1;

	//�̵�����
	if (_myState == ENEMYSTATE_MOVE)
	{
		//�� ��
		if (_myColor == WHITE)
		{

			_image = IMAGEMANAGER->findImage("whiteMove");//�̹��� ����
			if (_currentFrameX > _image->getMaxFrameX())
			{
				_image		= IMAGEMANAGER->findImage("whiteIdle");
				_myState	= ENEMYSTATE_IDLE;
				_action		= false;

			}

		}
		else if (_myColor == BROWN)
		{

			_image = IMAGEMANAGER->findImage("brownMove");
			if (_currentFrameX > _image->getMaxFrameX())
			{
				_image		= IMAGEMANAGER->findImage("brownIdle");
				_myState	= ENEMYSTATE_IDLE;
				_action		= false;
			}
		}
	}
	//�̵�����

	//���ݻ���
	if (_myState == ENEMYSTATE_ATTACK)
	{
		if (_myColor == WHITE)
		{
			_image = IMAGEMANAGER->findImage("whiteAttack");
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
			if (_currentFrameX > _image->getMaxFrameX())
			{
				_image = IMAGEMANAGER->findImage("brownIdle");
				_myState = ENEMYSTATE_IDLE;
				_action = false;

			}
		}
	}
	//���ݻ���

	//==*������ �ѱ��*==
	_frameFPS = 10;//������ �ӵ� ������
	_frameTime++;

	if (_frameFPS <= _frameTime)//�������� �ѱ��
	{
		_currentFrameX++;
		_frameTime = 0;
	}
	if (_currentFrameX >= _image->getMaxFrameX())//������ �ʱ�ȭ��
	{
		_currentFrameX = 0;
	}
	//==*������ �ѱ��*==
}

void Rat::attack()
{
	//�÷��̾��� ��ġ�� ã�Ƽ� �� ���⿡ ���÷�Ʈ�� ������ �ݴϴ�. �״����� �ʱ�ȭ�� �����ݽô�.

	//���¸� �����մϴ�.
	_myState = ENEMYSTATE_ATTACK;

	//���ݷ�Ʈ�� �����մϴ�.
	_attBox = RectMake(_player->getPoint().x, _player->getPoint().y, 32, 32);

	//�� ��� ���� Ȯ���� ������ ����Ű�� ���ݷµ� �ٸ��ϴ�.
	if (_myColor == WHITE)
	{
		//���ݷ� �������� ���ɴϴ�.
		_statistics.str = RND->getFromIntTo(3 + (_statistics.lv * 1), 5 + (_statistics.lv * 2));

		int bleed = RND->getInt(2);

		if (bleed == 2)//���� �����
		{
			//_player.
		}
	}
	//������� ������ ����Ű�� �ʽ��ϴ�.
	else if (_myColor == BROWN)
	{
		_statistics.str = RND->getFromIntTo(2 + (_statistics.lv * 1), 5 + (_statistics.lv * 2));

	}

	//_player->getDamaged(_statistics.str);
	_attBox = RectMake(0, 0, 0, 0);//�ʱ�ȭ

}

void Rat::move()
{
	//���̽�Ÿ�� ���� ���� �̵��մϴ�.

	_myState = ENEMYSTATE_MOVE;

	//A*�� �����Ͽ� '�÷��̾�' �� '�ֺ� 1ĭ'�� �־����
	//�÷��̾�� ���� ������
	if (true)
	{

	}
	//�÷��̾�� �����ʿ� ������
}

void Rat::getDamaged(int damage)
{
	_currntHp -= damage;
}