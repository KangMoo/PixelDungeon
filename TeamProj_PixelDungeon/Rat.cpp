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

HRESULT Rat::init(POINT point)
{
	//=======================================================================================================================================================
	//												*BROWNRATIMAGE*	
	//=======================================================================================================================================================
	
	//�׽�Ʈ
	//IMAGEMANAGER->addFrameImage("brownIdle",	"Img\\Enemy\\rat\\brownIdle.bmp",	64, 64, 2, 2,	true, RGB(255, 0, 255));//���̵����� �˾Ҵµ� �����̿���
	//IMAGEMANAGER->addFrameImage("brownMove",	"Img\\Enemy\\rat\\brownMove.bmp",	192, 64, 6, 2,	true, RGB(255, 0, 255));//�������� �˾Ҵµ� ���̵��̿���
	//IMAGEMANAGER->addFrameImage("brownAttack",	"Img\\Enemy\\rat\\brownAttack.bmp",	96, 64, 3, 2,	true, RGB(255, 0, 255));
	//IMAGEMANAGER->addFrameImage("brownDead",	"Img\\Enemy\\rat\\brownDead.bmp",	128, 64, 4, 2,	true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("brownIdle", "brownIdle.bmp", 64, 64, 2, 2, true, RGB(255, 0, 255));//���̵����� �˾Ҵµ� �����̿���
	IMAGEMANAGER->addFrameImage("brownMove", "brownMove.bmp", 192, 64, 6, 2, true, RGB(255, 0, 255));//�������� �˾Ҵµ� ���̵��̿���
	IMAGEMANAGER->addFrameImage("brownAttack", "brownAttack.bmp", 96, 64, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("brownDead", "brownDead.bmp", 128, 64, 4, 2, true, RGB(255, 0, 255));

	//bIdle = new image;
	//bMove = new image;
	//bAttack = new image;
	//bDead = new image;
	//
	//bIdle->init"Img\Enemy\rat\brownIdle.bmp", 64, 32, 2, 2, true, RGB(255, 0, 255));//

	//=======================================================================================================================================================
	//												*WHITERATIMAGE*	
	//=======================================================================================================================================================

	IMAGEMANAGER->addFrameImage("whiteIdle",	"whiteIdle.bmp",	64, 64, 2, 2,	true, RGB(255, 0, 255));//���̵����� �˾Ҵµ� �����̿���
	IMAGEMANAGER->addFrameImage("whiteMove",	"whiteMove.bmp",	192, 64, 6, 2,	true, RGB(255, 0, 255));//�������� �˾Ҵµ� ���̵��̿���
	IMAGEMANAGER->addFrameImage("whiteAttack",	"whiteAttack.bmp",	96, 64, 3, 2,	true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("whiteDead",	"whiteDead.bmp",	128, 64, 4, 2,	true, RGB(255, 0, 255));

	//bIdle = new image;
	//bMove = new image;
	//bAttack = new image;
	//bDead = new image;


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
	_statistics.exp		= 1;						
	_statistics.lv		= 1;//_player->getStat().lv; //�÷��̾� ������ ����Ͽ� �����ϴ�
	_statistics.maxLv	= 5;

	//�ִ뷹�� ����
	if (_statistics.lv >= _statistics.maxLv) _statistics.lv = _statistics.maxLv;

	//�˺�� �� Ȯ��
	_color		= RND->getFromIntTo(0, 3);		//�������� ���� �ҷ���
	_myColor	= _color == 0 ? WHITE : BROWN;	//���׿����ڷ� �Ǻ�, 30���� 1

	if (_myColor == WHITE)//�� ���� ��� 30���� 1 Ȯ���� �����մϴ�.
	{
		//������ ����Ͽ� ����մϴ�.
		_statistics.hp	= 14 + _statistics.lv;
		_statistics.def = 3 + _statistics.lv;

		_image = IMAGEMANAGER->findImage("whiteIdle");//�̹��� �ʱ�ȭ
	}
	else //�⺻ ��
	{
		//������ ����Ͽ� ����մϴ�.
		_statistics.hp	= 7 + _statistics.lv;
		_statistics.def = 3 + _statistics.lv;

		_image = IMAGEMANAGER->findImage("brownIdle");//�̹��� �ʱ�ȭ
	}

	_statistics.str = 0;
	_statistics.avd_lck = 4;
	_statistics.atk_lck = 11;

	//==============================================*CHARACTER INIT*=============================================================================================================
	
	//���ݹڽ�, ������ �ڽ� ����
	_hitBox = RectMake(point.x, point.y, TILESIZE, TILESIZE);	//32�� ������ ���ݴϴ�. Ȥ�� �𸣴ϱ��.
	_attBox = RectMake(0, 0, 0, 0);								//�ϴ� �ʱ�ȭ�� ���ݽô�.
	
	_currntHp = _statistics.hp;									//�ʱ� hp�� ������ �ݴϴ�.

	//_hpBar->init(point.x, point.y, TILESIZE, 4);				//hp���� ��ġ �� ũ�⸦ ������ �ݴϴ�.
	//_hpBar->setGauge(_currntHp, _statistics.hp);				//hp�ٸ� �������ݴϴ�.

	//==============================================*BOOL SETTING*=============================================================================================================
	
	_myState					= ENEMYSTATE_SLEEP;		//�ڰ��ֽ��ϴ�.

	_isLive						= true;					//����ֽ��ϴ�.
	_action						= false;				//���� �� ���� �ƴմϴ�.
	_findPlayer					= false;				//�÷��̾ ã�� ���߽��ϴ�.
	int rightRendom				= RND->getInt(1);		//������ ������ �������� ���մϴ�.
	//if (rightRendom == 1)_right = true;					//�������� �ٶ󺸴� ���Դϴ�.
	//else _right					= false;				//������ �ٶ󺸴� ���Դϴ�.

	_active						= false;					
	_isMove = false;

	//==============================================*etc. SETTING*=============================================================================================================

	//=======================================================================================================================================================
	//*NOTICE
	//*FrameY�� 0�Ͻ� right
	//*FrameY�� 1�Ͻ� left
	//=======================================================================================================================================================
	_frameTime = 0;
	_currentFrameX = 0;							//�������� �ʱ�ȭ ���ݴϴ�.
	if (_right == true)	_currentFrameY = 0;		
	else				_currentFrameY = 1;
	_image->setFrameX(_currentFrameY);			//�̹��� �������� �ʱ�ȭ ���ݴϴ�.
	_image->setFrameY(_currentFrameY);			//�̹��� �������� �ʱ�ȭ ���ݴϴ�.

	_deadAlpha = 0;							//������ ���ҽ�ų ���İ�

	_cog = RectMake((point.x)- TILESIZE*2,( point.y) - TILESIZE * 2, 5*TILESIZE, 5 * TILESIZE);//�÷��̾ ã�Ƴ� �Ÿ�
	attackRange = RectMake((point.x)- TILESIZE, (point.y) - TILESIZE, TILESIZE * 3, TILESIZE * 3);//�÷��̾ ������ �Ÿ�

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
	frameUpdate();

	_attBox = RectMake(0, 0, 0, 0);

	//if (!_active)
	//{
	//	if (_map->getTile(_point.x, _point.y).tileview != TILEVIEW_NO) _active = true;
	//
	//	_action = false;
	//	return;
	//}

	//���� ���¿��� �÷��̾��� ������ ����Ͽ� ������ ����մϴ�.
	//������ ����Ͽ� �ɷ�ġ�� �����ϴ�.
	if (_myState == ENEMYSTATE_SLEEP)
	{
		_statistics.lv = _player->getStat().lv; //�÷��̾� ������ ����Ͽ� �����ϴ�
		_statistics.maxLv = 5;

		if (_statistics.lv >= _statistics.maxLv)_statistics.lv = _statistics.maxLv;

		if (_myColor == WHITE)
		{
			//������ ����Ͽ� ����մϴ�.
			_statistics.hp = 14 + _statistics.lv;
			_statistics.def = 3 + _statistics.lv;
		}
		else //�⺻ ��
		{
			//������ ����Ͽ� ����մϴ�.
			_statistics.hp = 7 + _statistics.lv;
			_statistics.def = 3 + _statistics.lv;
		}
	}

	//�������� ������Ʈ ���ݴϴ�.

	//�νĹ��� ���� ������ �ν��� ��, �ν��� ���� �ѱ�
	if (PtInRect(&_cog, _player->getPoint()) && _myState == ENEMYSTATE_SLEEP)
	{
		//�ʱ���¸� ���̵�� ���ְ�, �÷��̾ ã�� ���·� �Ұ��� �������ش�.
		//�׼� �� ���� ���� �ѱ��.
		_myState	= ENEMYSTATE_IDLE;
		_findPlayer = true;
		_action		= false;
	}

	//�÷��̾ ã�� ����
	//�÷��̾ �ν��� ���´� �ٽô� Sleep�� ���� �ʴ´�.
	if (_findPlayer == true && _isLive == true)
	{
		//�׼��� ������ ���� ����
		//���¸� ���̵�� ���ش�.
		_myState = ENEMYSTATE_IDLE;

		if (_action == true) action();

		////���� ���� �ƴҶ�
		else if (_action == false && _myColor == WHITE) _image = IMAGEMANAGER->findImage("whiteMove");//�˰��� ���� ���϶��� �ش� �̹����� �����
		else if (_action == false && _myColor == BROWN) _image = IMAGEMANAGER->findImage("brownMove");
	
		//���� ���϶� //���󿩺� �������
		//��Ƽ��� ���δٴ� �ǹ̷� ������
		//���� ���̸� �������� �׼��� ������.
	}

	//hp�� ������Ʈ
	//_hpBar->setX(_point.x);
	//_hpBar->setY(_point.y);
	//_hpBar->setGauge(_currntHp, _statistics.hp);
	//_hpBar->update();
	
	//�׾���.
	if (_currntHp <= 0)
	{
		_myState	= ENEMYSTATE_DEAD;
		_isLive		= false; //�������� �����.
		_deadAlpha--;
		

		//UI���� ����ҽ��� �˸���.
		//�÷��̾�� EXP�� �ѱ��.
	}


	//���� ������������ �ѱ��.
}

void Rat::render(POINT camera)
{
	draw(camera);

}


void Rat::action()
{
	//int distanceToPlayer = getDistance(_point.x, _point.y, _player->getPoint().x, _player->getPoint().y) / TILESIZE;

	//���� ����
	//������
	//������
	//������
	
	if		(PtInRect(&attackRange, _player->getPoint())) attack();
	else	move();

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
	//�̵�����
	if (_myState == ENEMYSTATE_MOVE)
	{
		
		//�� ��
	//_currentFrameX = 0;
	if (_myColor == WHITE)		_image = IMAGEMANAGER->findImage("whiteMove");//�̹��� ����
	else if (_myColor == BROWN)	_image = IMAGEMANAGER->findImage("brownMove");

		
	}
	//�̵�����

	//���ݻ���
	//if (_myState == ENEMYSTATE_ATTACK)
	//{
	//	
	//	//_currentFrameX = 0;
	//}
	//���ݻ���

	//��������
	if (_myState == ENEMYSTATE_DEAD)
	{
		
				//_currentFrameX = 0;
	if (_myColor == WHITE)	_image = IMAGEMANAGER->findImage("whiteDead");
	else if (_myColor == BROWN)	_image = IMAGEMANAGER->findImage("brownDead");

		
	}
	//��������

	//==============================================*FRAME UPDATE*========================================
	
	//_currentFrameX++;
	//if (_currentFrameX > _image->getMaxFrameX()) _currentFrameX = 0;	//�������°� �ƴϸ� �������� �ʱ�ȭ �Ѵ�.

	_frameFPS = 10;//������ �ӵ� ������
	_frameTime++;
	
	if (_frameTime > _frameFPS)
	{
		_currentFrameX++;
		_frameTime = 0;
	}
	//������ �ʱ�ȭ
	if (_currentFrameX > _image->getMaxFrameX())
	{
		_currentFrameX = 0;	//�������°� �ƴϸ� �������� �ʱ�ȭ �Ѵ�.
		_action = false;
	}
}

void Rat::attack()
{
	_myState = ENEMYSTATE_ATTACK;

	if (_myColor == WHITE)	_image = IMAGEMANAGER->findImage("whiteAttack");
	else if (_myColor == BROWN)	_image = IMAGEMANAGER->findImage("brownAttack");

	//_currentFrameX = 0;	//ȥ�� �ʱ�ȭ �Ѵ�.

	//�÷��̾��� ��ġ�� ã�Ƽ� �� ���⿡ ���÷�Ʈ�� ������ �ݴϴ�. �״����� �ʱ�ȭ�� �����ݽô�.

	//���¸� �����մϴ�.

	//�� ��� ���� Ȯ���� ������ ����Ű�� ���ݷµ� �ٸ��ϴ�.
	if (_myColor == WHITE)
	{
		//���ݷ� �������� ���ɴϴ�.
		_statistics.str = RND->getFromIntTo(3 + (_statistics.lv * 1), 5 + (_statistics.lv * 2));

		//���� ������� �ɱ����� ������
		int bleed = RND->getInt(2);

		//2000�� �ð����� 1 �������� ��� �ش�.
		if (bleed == 2) _player->addDebuff(DEBUFF_BLEEDING, 2000, 1);
	}

	//������� ������ ����Ű�� �ʽ��ϴ�.
	else if (_myColor == BROWN)
	{
		_statistics.str = RND->getFromIntTo(2 + (_statistics.lv * 1), 5 + (_statistics.lv * 2));
	}

	//�÷��̾�� ���� ����
	//_player->getDamaged(_statistics.str);

	//�÷��̾� ��ġ�� �������� �����Ȱ� ����, Ÿ�ϻ������� �������� ���� Ÿ�Ͽ� ���ߴ°��� ������ ����.
	//���ݷ�Ʈ ����		�÷��̾� ��ġ X			�÷��̾� ��ġ y		Ÿ�� �����ŭ
	_attBox = RectMake(_player->getPoint().x - (TILESIZE / 2), _player->getPoint().y - (TILESIZE / 2), 32, 32);

	_myState = ENEMYSTATE_IDLE;


	if (_currentFrameX >= _image->getMaxFrameX())
	{
		_action = false; //���� �ѱ��
	}

}

void Rat::move()
{
	//���̽�Ÿ�� ���� ���� �̵��մϴ�.

	_myState = ENEMYSTATE_MOVE;
	
	astar = _map->aStar(_player->getPoint(), PointMake(_point.x, _point.x));
	//�����϶� �ش� ��ǥ�� 4,5 ���� ������ �ָ� �ڵ����� 4*TILESIZE + TILESIZE/2, 5*... ����
	_movePt = PointMake(astar[astar.size() - 1].destX, astar[astar.size() - 1].destY);
	_myState = ENEMYSTATE_MOVE;
	
	if (_myState == ENEMYSTATE_MOVE)
	{
		//��ǥ�� �־������� �ش� ��ǥ�� �����Ѵ�
		//�߽���ǥ�� ���Ѵ�
		float x = _movePt.x * TILESIZE + TILESIZE / 2;
		float y = _movePt.y * TILESIZE + TILESIZE / 2;
	
		//�߽���ǥ�� �����ߴ��� Ȯ���Ѵ�
		if ((static_cast<float>(_point.x) >= x - 4 && static_cast<float>(_point.x) <= x + 4) &&
			(static_cast<float>(_point.y) >= y - 4 && static_cast<float>(_point.y) <= y + 4))
		{
			//���� �����ϰ� �Ѱ��ش�
			_point.x = x;
			_point.y = y;
			_isMove = false;
			_myState = ENEMYSTATE_IDLE;
			_action = false;
		}
		else
		{
			//_point.x += cosf(getAngle(_point.x, _point.y, _movePoint.x, _movePoint.y)) * 3;
			//_point.y -= sinf(getAngle(_point.x, _point.y, _movePoint.x, _movePoint.y)) * 3;
			//_action = false;
	
			//�������� �ʾ����� �̵��Ѵ�
			if (_point.x < x)_point.x += TILESIZE / 8;
			else if (_point.x > x)_point.x -= TILESIZE / 8;
			if (_point.y < y) _point.y += TILESIZE / 8;
			else if (_point.y > y) _point.y -= TILESIZE / 8;
			_action = false;
	
		}
	}
	_action = false;
}

void Rat::getDamaged(int damage)
{
	//�ڴ� ���¿��� �¾����� �� ���¸� �������ش�.
	if (_myState == ENEMYSTATE_SLEEP)
	{
		_myState = ENEMYSTATE_IDLE;
		_findPlayer = true;
	}

	//�÷��̾��� ���߷��� 0���� �÷��̾��� ���߷��� ����ؼ�
	//�� ���� ���� ȸ�������� ������
	//ȸ�� ����
	int rnd = RND->getInt(_player->getStat().atk_lck);

	//ȸ������
	if (rnd < _statistics.avd_lck)
	{
		//ui�� ȸ�� �ߴٴ°��� ����
		return;
	}
	else _currntHp -= (damage - _statistics.def);
}

void Rat::draw(POINT camera)
{

	for (auto i : astar)
	{
		RectangleMakeCenter(getMemDC(), i.destX*TILESIZE + TILESIZE / 2 + camera.x, i.destY * TILESIZE + TILESIZE / 2 + camera.y, 5, 5);
	}

	Rectangle(getMemDC(), _attBox.left + camera.x, _attBox.top + camera.y, _attBox.right + camera.x, _attBox.bottom + camera.y);
	//_image->frameRender(getMemDC(), _point.x + camera.x, _point.y + camera.y);
	_image->alphaFrameRender(getMemDC(), _hitBox.left + camera.x, _hitBox.top + camera.y, _currentFrameX, _currentFrameY, _deadAlpha);
	//_image->frameRender(getMemDC(), _hitBox.left + camera.x, _hitBox.top + camera.y, _currentFrameX, _currentFrameY);

	char str[128];

	wsprintf(str, "%d", _currentFrameX);
	TextOut(getMemDC(), _hitBox.left + camera.x, _hitBox.top + camera.y, str, strlen(str));

	//_hpBar->render();
	//}
}
