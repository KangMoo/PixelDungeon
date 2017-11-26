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

	IMAGEMANAGER->addFrameImage("mimicDisable", "Img\Enemy\mimic\mimic_disable.bmp",32,	32, 1, 2, true, RGB(255, 0, 255));//���̵����� �˾Ҵµ� �����̿���
	IMAGEMANAGER->addFrameImage("mimicMove",	"Img\Enemy\mimic\mimic_move.bmp",	64,	64, 2, 2, true, RGB(255, 0, 255));//�������� �˾Ҵµ� ���̵��̿���
	IMAGEMANAGER->addFrameImage("mimicStay",	"Img\Enemy\mimic\mimic_stay.bmp",	160,64, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mimicDead",	"Img\Enemy\mimic\mimic_dead.bmp",	128,64, 4, 2, true, RGB(255, 0, 255));

	//=======================================================================================================================================================
	//												*MIMICINIT*	
	//=======================================================================================================================================================

	//==============================================*LV/STAT SETTING*=============================================================================================================

	_statistics.exp		= 2 + (_statistics.lv - 1) * 2 / 5;
	_statistics.lv		= 1;  //�÷��̾� ������ ����Ͽ� �����ϴ�.
	_statistics.maxLv	= 30;

	//�ִ뷹�� ����
	if (_statistics.lv >= _statistics.maxLv) _statistics.lv = _statistics.maxLv;

	_statistics.hp	= 12 + (_statistics.lv * 4);//������ ����Ͽ� ����մϴ�.
	_statistics.def = 3 + _statistics.lv;

	_image = IMAGEMANAGER->findImage("mimicDisable");

	_statistics.avd_lck = 4;
	_statistics.atk_lck = 11;

	//==============================================*CHARACTER INIT*=============================================================================================================

	_hitBox = RectMake(point.x, point.y, TILESIZE, TILESIZE);	//32�� ������ ���ݴϴ�. Ȥ�� �𸣴ϱ��.
	_attBox = RectMake(0, 0, 0, 0);								//�ϴ� �ʱ�ȭ�� ���ݽô�.

	_currntHp = _statistics.hp;

	_hpBar->init(point.x, point.y, TILESIZE, 4);
	_hpBar->setGauge(_currntHp, _statistics.hp);//hp�ٸ� �������ݴϴ�.

	//==============================================*BOOL SETTING*=============================================================================================================

	_myState = ENEMYSTATE_SLEEP;//SLEEP == DISABLE

	_isLive			= true;		//����ֽ��ϴ�.
	_action			= false;	//���� �� ���� �ƴմϴ�.
	_findPlayer		= false;	//���ε� �÷��̾ �÷��̾� �ǵ�ȴ����� �����Դϴ�.

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
		_statistics.lv		= _player->getStat().lv; //�÷��̾� ������ ����Ͽ� �����ϴ�
		_statistics.maxLv	= 5;
		_statistics.exp		= 2 + (_statistics.lv - 1) * 2 / 5;

		if (_statistics.lv >= _statistics.maxLv)_statistics.lv = _statistics.maxLv;
	}

	frameUpdate();

	//�÷��̾ �̹��� ��Ȱ��ȭ �� ���¿��� ������ �õ��Ҷ�
	if (_findPlayer == false && _myState == ENEMYSTATE_SLEEP && false)
	{
		_findPlayer = true;
		_myState	= ENEMYSTATE_IDLE;
		_image		= IMAGEMANAGER->findImage("mimicStay");
		_action		= false;
		//�������� �ϳ� ��´ٰ� �Ѵ�.
	}

	//�������� �ϳ� ���� ���¿��� Ȱ�� ���·� ����.
	//�÷��̾�� �־����� �ؼ� �ٽ� ��Ȱ�� ���·� ���ư����� �ʴ´�.
	if (_isLive == true && _findPlayer == true )
	{
		_myState = ENEMYSTATE_IDLE;

		if (_action == false)
		{
			_image = IMAGEMANAGER->findImage("mimicStay");
		}

		if (_action == true)//���� ���϶�
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
		_isLive		= false; //�������� �����.
		_deadAlpha--;

		//UI���� ����ҽ��� �˸���.
		//�÷��̾�� EXP�� �ѱ��.
		//�̹��� �����ϰ� �������� ��´�.
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

	//��ĭ �̻� ������ ������ �÷��̾� ��ġ�� �����Դϴ�.
	if (distanceToPlayer < 2) move();
	//�ƴҽ� �÷��̾� ��ġ�� ������ �õ��մϴ�.
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
	
	if (_myState == ENEMYSTATE_MOVE)	_image = IMAGEMANAGER->findImage("mimicMove");//�̹��� ����

	if (_myState == ENEMYSTATE_ATTACK)
	{
		_image = IMAGEMANAGER->findImage("mimicStay");
		if (_currentFrameX > _image->getMaxFrameX())
		{
			_image		= IMAGEMANAGER->findImage("mimicStay");//�� �̹��� ���� ���� ���� �𸣰ڴ�^^
			_myState	= ENEMYSTATE_IDLE;
			_action		= false; //���� �ѱ��
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
	//�÷��̾��� ��ġ�� ã�Ƽ� �� ���⿡ ���÷�Ʈ�� ������ �ݴϴ�. �״����� �ʱ�ȭ�� �����ݽô�.

	//���¸� �����մϴ�.
	_myState = ENEMYSTATE_ATTACK;

	//���ݷ�Ʈ�� �����մϴ�.
	_attBox = RectMake(_player->getPoint().x, _player->getPoint().y, TILESIZE, TILESIZE);

	//�� ��� ���� Ȯ���� ������ ����Ű�� ���ݷµ� �ٸ��ϴ�.
	_statistics.str = RND->getFromIntTo(3 + (_statistics.lv * 1), 5 + (_statistics.lv * 2));

	//_player->getDamaged(_statistics.str);
	_attBox = RectMake(0, 0, 0, 0);//�ʱ�ȭ

	_action = false; //���� �ѱ��

}

void Mimic::move()
{
	//���̽�Ÿ�� ���� ���� �̵��մϴ�.

	_myState = ENEMYSTATE_MOVE;

	//7 8 9
	//4 5 6
	//1 2 3
	//5�� idle



	//A*�� �����Ͽ� '�÷��̾�' �� '�ֺ� 1ĭ'�� �־����

	//_map->aStar(_point, _player->getPoint());
	//
	//if (_player->getPoint().y > _point.y)
	//{
	//	_point.y = _point.y + TILESIZE;
	//}

	//��ǥ�� ���ϱ�
	int x = _movePt.x;
	int y = _movePt.y;

	//�ش� ��ǥ���� �����ߴ��� üũ
	if (_point.x == x && _point.y == y)
	{
		_image = IMAGEMANAGER->findImage("mimicStay");
		_myState = ENEMYSTATE_IDLE;
		_action = false;
	}
	//��ǥ���� �������� ����
	else
	{
		//�¿�
		if (_point.x > x)	_point.x -= TILESIZE / 8;
		else				_point.x += TILESIZE / 8;

		//����
		if (_point.y > y)	_point.y -= TILESIZE / 8;
		else				_point.y += TILESIZE / 8;
	}

}

void Mimic::getDamaged(int damage)
{
	_currntHp -= (damage - _statistics.def);
}
