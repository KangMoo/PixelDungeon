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

	IMAGEMANAGER->addFrameImage("gooMove", "Img\Enemy\mimic\mimic_move.bmp", 64, 64, 2, 2, true, RGB(255, 0, 255));//�������� �˾Ҵµ� ���̵��̿���
	IMAGEMANAGER->addFrameImage("gooStay", "Img\Enemy\mimic\mimic_stay.bmp", 160, 64, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("gooDead", "Img\Enemy\mimic\mimic_dead.bmp", 128, 64, 4, 2, true, RGB(255, 0, 255));

	//=======================================================================================================================================================
	//												*GOOINIT*	
	//=======================================================================================================================================================

	//==============================================*LV/STAT SETTING*=============================================================================================================

	_statistics.exp = 10;
	_statistics.lv = 1;  //�÷��̾� ������ ����Ͽ� �����ϴ�.
	_statistics.maxLv = 30;

	//�ִ뷹�� ����
	if (_statistics.lv >= _statistics.maxLv) _statistics.lv = _statistics.maxLv;

	_statistics.hp = 80 + (_statistics.lv * 4);//������ ����Ͽ� ����մϴ�.
	_statistics.def = 12;

	_image = IMAGEMANAGER->findImage("gooStay");

	_statistics.avd_lck = 15;
	_statistics.atk_lck = 15;

	//==============================================*CHARACTER INIT*=============================================================================================================

	_hitBox = RectMake(point.x, point.y, TILESIZE, TILESIZE);	//32�� ������ ���ݴϴ�. Ȥ�� �𸣴ϱ��.
	_attBox = RectMake(0, 0, 0, 0);								//�ϴ� �ʱ�ȭ�� ���ݽô�.

	_currntHp = _statistics.hp;

	//_hpBar->init(point.x, point.y, TILESIZE, 4);
	//_hpBar->setGauge(_currntHp, _statistics.hp);//hp�ٸ� �������ݴϴ�.

	//==============================================*BOOL SETTING*=============================================================================================================

	_myState = ENEMYSTATE_SLEEP;//SLEEP == DISABLE

	_isLive = true;		//����ֽ��ϴ�.
	_action = false;	//���� �� ���� �ƴմϴ�.
	_findPlayer = false;	//���ε� �÷��̾ �÷��̾� �ǵ�ȴ����� �����Դϴ�.

							//==============================================*etc. SETTING*=============================================================================================================

							//=======================================================================================================================================================
							//*NOTICE
							//*FrameY�� 0�Ͻ� right
							//*FrameY�� 1�Ͻ� left
							//=======================================================================================================================================================

	_currentFrameX = 0;	//�������� �ʱ�ȭ ���ݴϴ�.
	_currentFrameY = 0;	//�������� �ʱ�ȭ ���ݴϴ�.
	_image->setFrameX(_currentFrameX);	//�̹��� �������� �ʱ�ȭ ���ݴϴ�.
	_image->setFrameY(_currentFrameY);	//�̹��� �������� �ʱ�ȭ ���ݴϴ�.

	_deadAlpha = 255;

	_cog = RectMake(point.x, point.y, cog, cog);

	_point.x = point.x;
	_point.y = point.y;

	pumpIt = false; //�ſ� ��-���� �����Դϴ�.
	trunCount = 0; //������ �������� �� ī��Ʈ, 2�� �Ǹ� �ſ� ������ ������ �õ� �մϴ�.

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
		_statistics.lv = _player->getStat().lv; //�÷��̾� ������ ����Ͽ� �����ϴ�
		_statistics.hp = 80 + (_statistics.lv * 4);//������ ����Ͽ� ����մϴ�.

		if (_statistics.lv >= _statistics.maxLv)_statistics.lv = _statistics.maxLv;
	}

	frameUpdate();

	//�÷��̾� ã�°�

	if (_findPlayer == false)
	{
		_findPlayer = true;
		_myState = ENEMYSTATE_IDLE;
		_image = IMAGEMANAGER->findImage("gooStay");
		_action = false;
	}

	//�÷��̾�� �־����� �ؼ� �ٽ� ��Ȱ�� ���·� ���ư����� �ʴ´�.
	if (_isLive == true && _findPlayer == true)
	{
		_myState = ENEMYSTATE_IDLE;

		if (_action == false)
		{
			_image = IMAGEMANAGER->findImage("gooStay");
		}

		if (_action == true)//���� ���϶�
		{
			action();
		}
	}

	if (_currntHp <= 0)
	{
		_myState = ENEMYSTATE_DEAD;
		_isLive = false; //�������� �����.
		_deadAlpha--;

		//UI���� ����ҽ��� �˸���.
		//�÷��̾�� EXP�� �ѱ��.
		//�̹��� �����ϰ� �������� ��´�.

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
	//��ĭ �̻� ������ ������ �÷��̾� ��ġ�� �����Դϴ�.
	if (distanceToPlayer < 2) move();
	//�ƴҽ� �÷��̾� ��ġ�� ������ �õ��մϴ�.
	else if (rnd == 2) pumpIt = true;
	else attack();

}

void goo::attack()
{
	//Ÿ�� ī��Ʈ�� �÷��ش�
	if (pumpIt == true)
	{
		trunCount++;
		_action = false;
	}
	//����Ѵ�!
	else if (pumpIt == true && trunCount == 2)
	{
		trunCount = 0;
		_action = false;
	}
	//��Ÿ
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
