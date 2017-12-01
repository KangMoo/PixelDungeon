#include "stdafx.h"
#include "Mimic.h"
#include "Player.h"
#include "Map.h"
#include "UI.h"
//#include "Item.h"
#include "itemManager.h"
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

	_statistics.exp		= 2 + (_statistics.lv - 1) * 2 / 5; //����ġ, ��Ű���� �̷���
	_statistics.lv		= 1;  //�÷��̾� ������ ����Ͽ� �����ϴ�.
	_statistics.maxLv	= 30; //�ִ뷹��

	//�ִ뷹�� ����
	if (_statistics.lv >= _statistics.maxLv) _statistics.lv = _statistics.maxLv;

	_statistics.hp	= 12 + (_statistics.lv * 4);//������ ����Ͽ� ����մϴ�.
	_statistics.def = 0; //������ ����, ��Ű���� �׷����Ѥ�


	//�̹��� ��Ű�� ���� ����, �ٵ� �̰� ���� ��� ������ �𸣰ڴ�.
	_image = IMAGEMANAGER->findImage("mimicDisable");

	//����;
	_statistics.avd_lck = 0;
	_statistics.atk_lck = 9 + _statistics.lv;

	//==============================================*CHARACTER INIT*=============================================================================================================

	_hitBox = RectMake(point.x, point.y, TILESIZE, TILESIZE);	//32�� ������ ���ݴϴ�. Ȥ�� �𸣴ϱ��.
	_attBox = RectMake(0, 0, 0, 0);								//�ϴ� �ʱ�ȭ�� ���ݽô�.

	_currntHp = _statistics.hp;

	//_hpBar->init(point.x, point.y, TILESIZE, 4);
	//_hpBar->setGauge(_currntHp, _statistics.hp);//hp�ٸ� �������ݴϴ�.

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
	money = RND->getFromIntTo(1, 99999);

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

		//_hpBar->setX(_point.x);
		//_hpBar->setY(_point.y);
		//_hpBar->setGauge(_currntHp, _statistics.hp);
		//_hpBar->update();
	}

	if (_currntHp <= 0)
	{
		_myState	= ENEMYSTATE_DEAD;
		_isLive		= false; //�������� �����.
		_deadAlpha--;

		//UI���� ����ҽ��� �˸���.
		//�÷��̾�� EXP�� �ѱ��.
		//�̹��� �����ϰ� �������� ��´�.

		itemDrop();
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
	//if (_findPlayer == true)
	//{
	//	_hpBar->render();
	//}
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
	_statistics.str = RND->getFromIntTo((9 + _statistics.lv) * 2, (9 + _statistics.lv) * 3);

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

void Mimic::itemDrop()
{
	//										0						40
	int item			= RND->getFromIntTo(NAME_OLD_SHORT_SWORD, NAME_MONEY);//�����ϰ� �������� ��´�
	
	int identifyPercent = RND->getInt(1);//50% Ȯ���� Ȯ�ε� ������
	bool identify;
	
	if (identifyPercent == 0)identify = false;
	else identify = true;

	int isCursedPercent = RND->getInt(1);//50% Ȯ���� ���ֹ���
	bool isCursed;
	if (isCursedPercent == 0)isCursed = false;
	else isCursed = true;

	int upgrade = RND->getInt(2);//���׷��̵� ��ġ

	switch (item)
	{
		//����
	case NAME_OLD_SHORT_SWORD:
							//������ �̸�			��ġX		��ġY	Ȯ�ο��� ���ֿ��� ���׷��̵� ����
		_im->setItemToField(NAME_OLD_SHORT_SWORD,	_point.x, _point.y, identify, isCursed, upgrade, 1);
		
		break;
	case NAME_SHORT_SWORD:
		_im->setItemToField(NAME_SHORT_SWORD,		_point.x, _point.y, identify, isCursed, upgrade, 1);

		break;
	case NAME_SWORD:
		_im->setItemToField(NAME_SWORD,				_point.x, _point.y, identify, isCursed, upgrade, 1);

		break;
	case NAME_SPEAR:
		_im->setItemToField(NAME_SPEAR,				_point.x, _point.y, identify, isCursed, upgrade, 1);

		break;
	case NAME_BATTLE_AXE:
		_im->setItemToField(NAME_BATTLE_AXE,		_point.x, _point.y, identify, isCursed, upgrade, 1);

		break;

		//��
	case NAME_CLOTH:
		_im->setItemToField(NAME_CLOTH,				_point.x, _point.y, identify, isCursed, upgrade, 1);

		break;
	case NAME_LEATHER:
		_im->setItemToField(NAME_LEATHER,			_point.x, _point.y, identify, isCursed, upgrade, 1);

		break;
	case NAME_MAIL:
		_im->setItemToField(NAME_MAIL,				_point.x, _point.y, identify, isCursed, upgrade, 1);

		break;

		//�Ǽ��縮
	case NAME_RING_POWER:
		_im->setItemToField(NAME_RING_POWER,		_point.x, _point.y, identify, isCursed, upgrade, 1);

		break;
	case NAME_RING_RECHARGE:
		_im->setItemToField(NAME_RING_RECHARGE,		_point.x, _point.y, identify, isCursed, upgrade, 1);

		break;
	case NAME_LIOYDS_BEACON:
		_im->setItemToField(NAME_LIOYDS_BEACON,		_point.x, _point.y, identify, isCursed, upgrade, 1);

		break;

		//��ô
	case NAME_DART:
		_im->setItemToField(NAME_DART,				_point.x, _point.y, identify, isCursed, upgrade, 1);

		break;
	case NAME_PARALYSIS_DART:
		_im->setItemToField(NAME_PARALYSIS_DART,	_point.x, _point.y, identify, isCursed, upgrade, 1);

		break;
	case NAME_POISON_DART:
		_im->setItemToField(NAME_POISON_DART,		_point.x, _point.y, identify, isCursed, upgrade, 1);

		break;
		//�ϵ�
	case NAME_LIGHTNING:
		_im->setItemToField(NAME_LIGHTNING,			_point.x, _point.y, identify, isCursed, upgrade, 1);

		break;
	case NAME_NORMAL:
		_im->setItemToField(NAME_NORMAL,			_point.x, _point.y, identify, isCursed, upgrade, 1);

		break;
	case NAME_POISON:
		_im->setItemToField(NAME_POISON,			_point.x, _point.y, identify, isCursed, upgrade, 1);

		break;

		//����
		//���ĵ��� �����۷��� ��ġ�� ������ �ݴϴ�. ���ֹ��� �Ľ�Ÿ ������ ���ø��� ���� ���� �ֹ����� ���൵ �����մϴ�.
	case NAME_EMERGENCY:
		_im->setItemToField(NAME_EMERGENCY,			_point.x, _point.y);

		break;
	case NAME_PASTY:
		_im->setItemToField(NAME_PASTY,				_point.x, _point.y);

		break;
	case NAME_UNKNOWN_MEAT:
		_im->setItemToField(NAME_UNKNOWN_MEAT,		_point.x, _point.y);

		break;
	case NAME_COOKED_MEAT:
		_im->setItemToField(NAME_COOKED_MEAT,		_point.x, _point.y);

		break;
	case NAME_FROZEN_MEAT:
		_im->setItemToField(NAME_FROZEN_MEAT,		_point.x, _point.y);

		break;

		//�ֹ���
	case NAME_IDENTIFY:
		_im->setItemToField(NAME_IDENTIFY,			_point.x, _point.y);

		break;
	case NAME_UPGRADE:
		_im->setItemToField(NAME_UPGRADE,			_point.x, _point.y);

		break;
	case NAME_PURIFY:
		_im->setItemToField(NAME_PURIFY,			_point.x, _point.y);

		break;
	case NAME_MAP:
		_im->setItemToField(NAME_MAP,				_point.x, _point.y);

		break;

		//����
	case NAME_RECHARGE:
		_im->setItemToField(NAME_RECHARGE,			_point.x, _point.y);

		break;
	case NAME_BOTTLE:
		_im->setItemToField(NAME_BOTTLE,			_point.x, _point.y);

		break;
	case NAME_HEAL:
		_im->setItemToField(NAME_HEAL,				_point.x, _point.y);

		break;
	case NAME_STR:
		_im->setItemToField(NAME_STR,				 _point.x, _point.y);

		break;
	case NAME_EX:
		_im->setItemToField(NAME_EX,				_point.x, _point.y);

		break;
	case NAME_INVISIBLE:
		_im->setItemToField(NAME_INVISIBLE,			_point.x, _point.y);

		break;
	case NAME_LEVITATION:
		_im->setItemToField(NAME_LEVITATION,		_point.x, _point.y);

		break;
	case NAME_FROZEN:
		_im->setItemToField(NAME_FROZEN,			_point.x, _point.y);

		break;
	case NAME_LIQUID_FIRE:
		_im->setItemToField(NAME_LIQUID_FIRE,		_point.x, _point.y);

		break;
	case NAME_SEED_HEAL:
		_im->setItemToField(NAME_SEED_HEAL,			_point.x, _point.y);

		break;
	case NAME_SEED_FIRE:
		_im->setItemToField(NAME_SEED_FIRE,			_point.x, _point.y);

		break;
	case NAME_SEED_SNAKE:
		_im->setItemToField(NAME_SEED_SNAKE,		_point.x, _point.y);

		break;
	case NAME_SEED_FROST:
		_im->setItemToField(NAME_SEED_FROST,		_point.x, _point.y);

		break;
	case NAME_DEW:
		_im->setItemToField(NAME_DEW,				_point.x, _point.y);

		break;

		//���� �Ӵ� ���������� �̿��մϴ�
	case NAME_MONEY:
		_im->setItemToField(NAME_POISON,			_point.x, _point.y, false, false, 0, money);

		break;
	}
}

void Mimic::getDamaged(int damage)
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
	else
	{
		int hitGift = RND->getInt(2);
		if (hitGift == 2) _im->setItemToField(NAME_POISON, _point.x, _point.y, false, false, 0, money);

		_currntHp -= (damage - _statistics.def);

	}
}
