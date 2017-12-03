#include "stdafx.h"
#include "Player.h"
#include "EnemyManager.h"
#include "Map.h"
#include "UI.h"

Player::Player()
{
}


Player::~Player()
{

}
HRESULT Player::init() { return S_OK; }
HRESULT Player::init(POINT point)
{

	addImg();
	//test~
	//_playerPoint = PointMake(_map->getTile(7, 7).destX*TILESIZE + TILESIZE / 2, _map->getTile(7, 7).destY*TILESIZE + TILESIZE / 2);

	_playerStat.atk_lck = 0;
	_playerStat.avd_lck = 0;
	_playerStat.def = 0;
	_playerStat.exp = 0;
	_playerStat.hp = 250;
	_playerStat.maxhp = 250;
	_playerStat.hunger = 100;
	_playerStat.lv = 1;
	_playerStat.str = 3;



	//~test
	_playerState = PLAYERSTATE_IDLE;
	_frameUpdateTimer = TIMEMANAGER->getWorldTime();
	_currentFrameX = _currentFrameY = 0;
	_image = IMAGEMANAGER->findImage("warrior_Idle");
	_frameTimer = TIMEMANAGER->getWorldTime();
	_keepMove = false;
	_isUsingUI = false;
	_isEnemyTargeted = false;


	return S_OK;
}
void Player::release()
{

}
void Player::update()
{

	frameUpdate();
	

	if (_playerState == PLAYERSTATE_DEAD) return;

	//�ڱ� ���ʰ� �ƴϸ� ���� ����X
	if (!_action) return;

	//keepMove��?? -> ���� �� ���� �ִ��� ���� (A*�� ���� �����ִ��� ����)
	if (astar.size() > 0)
	{
		_keepMove = true;
	}
	else
	{
		_keepMove = false;
	}

	//������ ���� �ִٸ�~?
	if (_keepMove == true && !_isUsingUI)
	{
		move();
	}
	else if (_isEnemyTargeted)
	{
		action_Attack();
		_isEnemyTargeted = false;
		endTurn();
	}
	else
	{
		//�þ�ó��
		fovCheck();
	}

	//���콺 Ŭ�� �̺�Ʈ ó��
	if (!_ui->usingInterface())
	{
		
		if (!_ui->usingInterface() && KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
		{
			//�����̴� �߿� ���콺 Ŭ�� �̺�Ʈ �߻� �ϸ� ���� Ÿ�ϸ� ���� ���� ��
			if (_keepMove && astar.size()>0)
			{
				TILE temp;
				temp = astar[astar.size() - 1];
				astar.clear();
				astar.push_back(temp);
				return;
			}
		}
	}
	

	//����ó��
	if (_playerStat.hp <= 0)
	{
		_playerState = PLAYERSTATE_DEAD;
		_image = IMAGEMANAGER->findImage("warrior_Dead");
	}
}
//�׸� ��	x��ǥ�� camera.x ��ŭ
//			y��ǥ�� camera.y ��ŭ �����ֱ�!!!!
void Player::render(POINT camera)
{
	draw(camera);
}

void Player::draw(POINT camera)
{
	//test~
	//for (auto i : angleCanTSee)
	//{
	//	MoveToEx(getMemDC(), _playerPoint.x, _playerPoint.y, NULL);
	//	LineTo(getMemDC(), _playerPoint.x + cosf(i.sangle) * 100, _playerPoint.y - sinf(i.sangle) * 100);
	//	LineTo(getMemDC(), _playerPoint.x + cosf(i.eangle) * 100, _playerPoint.y - sinf(i.eangle) * 100);
	//	LineTo(getMemDC(), _playerPoint.x, _playerPoint.y);
	//}
	for (auto i : astar)
	{
		RectangleMakeCenter(getMemDC(), i.destX * 32 + 16 + camera.x, i.destY * 32 + 16 + camera.y, 5, 5);
	}
	//~test
	_image->alphaFrameRender(getMemDC(), _playerPoint.x - _image->getFrameWidth() / 2 + camera.x, _playerPoint.y - _image->getFrameHeight() / 2 + camera.y, _currentFrameX, _currentFrameY, 0);
	//IMAGEMANAGER->render("blactkTile", getMemDC(), 50, 50, 0, 0, 100, 100);
	char str[128];
	SetTextColor(getMemDC(), RGB(255, 0, 0));
	sprintf_s(str, "%d", _playerStat.exp);
	TextOut(getMemDC(), 500, 250, str, strlen(str));

}

void Player::addCanTSeeAngle(float sangle, float eangle)
{
	//�߰�
	sightAngle temp;
	temp.sangle = sangle;
	temp.eangle = eangle;
	angleCanTSee.push_back(temp);

	vector<int> deleteNum;

	bool isTherNoIntersection = false;
	while (!isTherNoIntersection)
	{
		isTherNoIntersection = true;
		//�ߺ��Ǵ� ���� ��ġ��
		for (int i = 0; i < angleCanTSee.size(); i++)
		{
			for (int j = i + 1; j < angleCanTSee.size(); j++)
			{
				//��ġ�� ������ ���� ��
				if ((angleCanTSee[i].sangle <= angleCanTSee[j].sangle && angleCanTSee[j].sangle <= angleCanTSee[i].eangle) ||
					(angleCanTSee[i].sangle <= angleCanTSee[j].eangle && angleCanTSee[j].eangle <= angleCanTSee[i].eangle))
				{
					//
					if (angleCanTSee[i].sangle >= angleCanTSee[j].sangle) angleCanTSee[i].sangle = angleCanTSee[j].sangle;
					if (angleCanTSee[i].eangle <= angleCanTSee[j].eangle) angleCanTSee[i].eangle = angleCanTSee[j].eangle;
					angleCanTSee.erase(angleCanTSee.begin() + j);
					isTherNoIntersection = false;
					break;
				}
			}
		}
	}





}

void Player::addCanTSeeAngleByRect(RECT rc)
{
	POINT rcpoint = PointMake(rc.left + TILESIZE / 2, rc.top + TILESIZE / 2);
	//���� y�� ��
	if (_playerPoint.x / TILESIZE == rcpoint.x / TILESIZE)
	{
		//�÷��̾��� ��
		if (_playerPoint.y / TILESIZE > rcpoint.y / TILESIZE)
		{
			addCanTSeeAngle(getAngle(_playerPoint.x, _playerPoint.y, rc.right, rc.bottom), getAngle(_playerPoint.x, _playerPoint.y, rc.left, rc.bottom));
		}
		//�÷��̾��� �Ʒ�
		else if (_playerPoint.y / TILESIZE < rcpoint.y / TILESIZE)
		{
			addCanTSeeAngle(getAngle(_playerPoint.x, _playerPoint.y, rc.left, rc.top), getAngle(_playerPoint.x, _playerPoint.y, rc.right, rc.top));
		}

	}
	//1,4��и�
	else if (_playerPoint.x / TILESIZE< rcpoint.x / TILESIZE)
	{
		//���� x�� ��
		if (_playerPoint.y / TILESIZE == rcpoint.y / TILESIZE)
		{
			if (getAngle(_playerPoint.x, _playerPoint.y, rc.left, rc.bottom) > getAngle(_playerPoint.x, _playerPoint.y, rc.left, rc.top))
			{
				addCanTSeeAngle(0, getAngle(_playerPoint.x, _playerPoint.y, rc.left, rc.top));
				addCanTSeeAngle(getAngle(_playerPoint.x, _playerPoint.y, rc.left, rc.bottom), PI2);
			}
			else
			{
				addCanTSeeAngle(getAngle(_playerPoint.x, _playerPoint.y, rc.left, rc.bottom), getAngle(_playerPoint.x, _playerPoint.y, rc.left, rc.top));
			}
			
		}
		//1��и�
		else if (_playerPoint.y / TILESIZE> rcpoint.y / TILESIZE)
		{
			if (getAngle(_playerPoint.x, _playerPoint.y, rc.right, rc.bottom) >  getAngle(_playerPoint.x, _playerPoint.y, rc.left, rc.top))
			{
				addCanTSeeAngle(0, getAngle(_playerPoint.x, _playerPoint.y, rc.left, rc.top));
				addCanTSeeAngle(getAngle(_playerPoint.x, _playerPoint.y, rc.right, rc.bottom), PI2);
			}
			else
			{
				addCanTSeeAngle(getAngle(_playerPoint.x, _playerPoint.y, rc.right, rc.bottom), getAngle(_playerPoint.x, _playerPoint.y, rc.left, rc.top));
			}
			
		}
		//4��и�
		else if (_playerPoint.y / TILESIZE < rcpoint.y / TILESIZE)
		{
			if (getAngle(_playerPoint.x, _playerPoint.y, rc.left, rc.bottom) >  getAngle(_playerPoint.x, _playerPoint.y, rc.right, rc.top))
			{
				addCanTSeeAngle(0, getAngle(_playerPoint.x, _playerPoint.y, rc.right, rc.top));
				addCanTSeeAngle(getAngle(_playerPoint.x, _playerPoint.y, rc.left, rc.bottom), PI2);
			}
			else
			{
				addCanTSeeAngle(getAngle(_playerPoint.x, _playerPoint.y, rc.left, rc.bottom), getAngle(_playerPoint.x, _playerPoint.y, rc.right, rc.top));
			}
			
		}
	}
	//2,3��и�
	else if (_playerPoint.x / TILESIZE> rcpoint.x / TILESIZE)
	{
		//���� x�� ��
		if (_playerPoint.y / TILESIZE == rcpoint.y / TILESIZE)
		{
			addCanTSeeAngle(getAngle(_playerPoint.x, _playerPoint.y, rc.right, rc.top), getAngle(_playerPoint.x, _playerPoint.y, rc.right, rc.bottom));
		}
		//2��и�
		else if (_playerPoint.y / TILESIZE > rcpoint.y / TILESIZE)
		{
			addCanTSeeAngle(getAngle(_playerPoint.x, _playerPoint.y, rc.right, rc.top), getAngle(_playerPoint.x, _playerPoint.y, rc.left, rc.bottom));
		}
		//3��и�
		else if (_playerPoint.y / TILESIZE< rcpoint.y / TILESIZE)
		{
			addCanTSeeAngle(getAngle(_playerPoint.x, _playerPoint.y, rc.left, rc.top), getAngle(_playerPoint.x, _playerPoint.y, rc.right, rc.bottom));
		}
	}
}

void Player::frameUpdate()
{
	if (_playerState == PLAYERSTATE_IDLE && TIMEMANAGER->getWorldTime() - _frameTimer > 1.5)
	{
		_frameTimer = TIMEMANAGER->getWorldTime();
		if (_currentFrameX < _image->getMaxFrameX())
		{
			_currentFrameX++;
		}
		else
		{
			_currentFrameX = 0;
			if (_playerState != PLAYERSTATE_IDLE)
			{
				_playerState = PLAYERSTATE_IDLE;
				_image = IMAGEMANAGER->findImage("warrior_Idle");
			}
		}
	}

	else if (_playerState != PLAYERSTATE_IDLE && TIMEMANAGER->getWorldTime() - _frameTimer > 0.1)
	{
		_frameTimer = TIMEMANAGER->getWorldTime();


		if (_currentFrameX < _image->getMaxFrameX())
		{
			_currentFrameX++;
		}
		else
		{
			_currentFrameX = 0;

			if (_playerState == PLAYERSTATE_DEAD)
			{

			}
			else if (_playerState != PLAYERSTATE_IDLE)
			{
				_playerState = PLAYERSTATE_IDLE;
				_image = IMAGEMANAGER->findImage("warrior_Idle");
			}
		}
	}

}

void Player::imageChange(const char* str)
{
	_image = IMAGEMANAGER->findImage(str);
	_currentFrameX = 0;
}

void Player::fovCheck()
{
	//FOV�׽�Ʈ~
	tileCanSee.clear();
	angleCanTSee.clear();


	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			TILE temp = _map->getTile(i, j);
			if (temp.tileview == TILEVIEW_ALL)
			{
				temp.tileview = TILEVIEW_HALF;
				_map->setTile(temp, i, j);
			}
		}

	}

	//�÷��̾� �߽����� 9���� Ÿ���� �� �� �ִ� Ÿ�Ϸ� �߰�
	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			tileCanSee.push_back(_map->getTile(_playerPoint.x / TILESIZE + i, _playerPoint.y / TILESIZE + j));
		}
	}

	//�ִ� �þ߸�ŭ Ž��
	for (int sightMaxTile = 1; sightMaxTile < 4; sightMaxTile++)
	{
		for (int i = _playerPoint.x / TILESIZE - sightMaxTile; i <= _playerPoint.x / TILESIZE + sightMaxTile; i++)
		{
			for (int j = _playerPoint.y / TILESIZE - sightMaxTile; j <= _playerPoint.y / TILESIZE + sightMaxTile; j++)
			{
				//�� �� �ִ� Ÿ������ üũ�ϱ� ���� ����
				bool tileCanSeeChk = true;
				//�� �� ���� ��ġ�� ���� ��� Ž��
				for (auto k : angleCanTSee)
				{
					//���� ���ϴ� ������ Ÿ���� ��ġ�� �ִ°�?
					if (k.sangle <= getAngle(_playerPoint.x, _playerPoint.y, i*TILESIZE + TILESIZE / 2, j*TILESIZE + TILESIZE / 2) &&
						getAngle(_playerPoint.x, _playerPoint.y, i*TILESIZE + TILESIZE / 2, j*TILESIZE + TILESIZE / 2) <= k.eangle)
					{
						//��� ���� ��ġ
						int limit = 10;
						//��¦ ���̴������� ���δٰ� ������
						if (k.sangle - PI / 180 * limit <= getAngle(_playerPoint.x, _playerPoint.y, i*TILESIZE + TILESIZE / 2, j*TILESIZE + TILESIZE / 2) &&
							getAngle(_playerPoint.x, _playerPoint.y, i*TILESIZE + TILESIZE / 2, j*TILESIZE + TILESIZE / 2) <= k.sangle + PI / 180 * limit &&
							j != _playerPoint.y / TILESIZE)
						{

						}
						else if (k.eangle - PI / 180 * limit <= getAngle(_playerPoint.x, _playerPoint.y, i*TILESIZE + TILESIZE / 2, j*TILESIZE + TILESIZE / 2) &&
							getAngle(_playerPoint.x, _playerPoint.y, i*TILESIZE + TILESIZE / 2, j*TILESIZE + TILESIZE / 2) <= k.eangle + PI / 180 * limit &&
							j != _playerPoint.y / TILESIZE)
						{

						}
						else
						{
							tileCanSeeChk = false;
						}

					}
				}

				//�� �� �ִ� Ÿ���� ���
				if (tileCanSeeChk && i >= 0 && j >= 0)
				{
					//�� �� �ִ� Ÿ�Ϻ��Ϳ� push
					tileCanSee.push_back(_map->getTile(i, j));
					//��ֹ��� ���� ���
					if ((_map->getTile(i, j).terrain & ATTRIBUTE_UNSIGHT) == ATTRIBUTE_UNSIGHT)
					{
						//���� ���ϴ� ���� �߰�
						addCanTSeeAngleByRect(RectMake(i * TILESIZE, j * TILESIZE, TILESIZE, TILESIZE));
					}
				}
			}
		}
	}



	//�� �� �ִ� Ÿ���� TILEVIEW_ALL�� ����
	for (auto i : tileCanSee)
	{
		TILE temp = i;
		temp.tileview = TILEVIEW_ALL;
		_map->setTile(temp, i.destX, i.destY);
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		_playerPoint.x -= TILESIZE;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		_playerPoint.x += TILESIZE;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		_playerPoint.y -= TILESIZE;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		_playerPoint.y += TILESIZE;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_playerStat.hp -= 30;
	}
	//~FOV�׽�Ʈ
}

void Player::addImg()
{
	IMAGEMANAGER->addFrameImage("warrior_Idle", "Img//Player//warrior_idle.bmp", 48, 210, 2, 7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("warrior_Dead", "Img//Player//warrior_dead.bmp", 120, 210, 5, 7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("warrior_Eat", "Img//Player//warrior_eat.bmp", 48, 210, 2, 7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("warrior_Attack", "Img//Player//warrior_attack.bmp", 72, 210, 3, 7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("warrior_Scroll", "Img//Player//warrior_scroll.bmp", 72, 210, 3, 7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("warrior_Move", "Img//Player//warrior_move.bmp", 144, 210, 6, 7, true, RGB(255, 0, 255));
}

void Player::addDebuff(DEBUFF debuffType, int lefttime, int damage)
{
	tagDebuff temp;
	temp.type = debuffType;
	temp.lefttime = lefttime;
	temp.damage = damage;
	_vdebuff.push_back(temp);
}

void Player::action_Move(POINT point)
{
	_playerState = PLAYERSTATE_MOVE;
	_image = IMAGEMANAGER->findImage("warrior_Move");

	astar = _map->aStar(_playerPoint, point);
	_goalTile = _map->getTile(_ptMouse.x / TILESIZE, _ptMouse.y / TILESIZE);
}
void Player::action_Attack()
{
	_playerState = PLAYERSTATE_ATTACK;
	_image = IMAGEMANAGER->findImage("warrior_Attack");
	_currentFrameX = 0;

	//��ǥ ���� ����
	if (_isEnemyTargeted)
	{
		attack = true;
		player_attack_dp = true;

		// ������ �ֱ� (�ӽ�)
		_TargetEnemy->getDamaged(RND->getFromIntTo(3,3));
		
		//_TargetEnemy->setHP(_TargetEnemy->getHP() -RND->getFromIntTo(_playerStat.mindmg,_playerStat.maxdmg));
		_isEnemyTargeted = false;
	}
}
void Player::action_Scroll()
{
	_playerState = PLAYERSTATE_SCROLL;
	_image = IMAGEMANAGER->findImage("warrior_Scroll");
}
void Player::action_Eat()
{
	_playerState = PLAYERSTATE_EAT;
	_image = IMAGEMANAGER->findImage("warrior_Eat");
}

void Player::move()
{
	_playerState = PLAYERSTATE_MOVE;
	_image = IMAGEMANAGER->findImage("warrior_Move");

	_playerPoint.x += cosf(getAngle(_playerPoint.x, _playerPoint.y, astar[astar.size() - 1].destX * TILESIZE + TILESIZE / 2, astar[astar.size() - 1].destY*TILESIZE + TILESIZE / 2)) * 3;
	_playerPoint.y -= sinf(getAngle(_playerPoint.x, _playerPoint.y, astar[astar.size() - 1].destX * TILESIZE + TILESIZE / 2, astar[astar.size() - 1].destY*TILESIZE + TILESIZE / 2)) * 3;

	//��ǥ�� �����ϸ� (Ÿ�� ��ĭ �̵� �Ϸ��ϸ�)
	if (getDistance(_playerPoint.x, _playerPoint.y, astar[astar.size() - 1].destX * TILESIZE + TILESIZE / 2, astar[astar.size() - 1].destY*TILESIZE + TILESIZE / 2) <= 3)
	{
		//�÷��̾� ��ġ ����
		_playerPoint.x = astar[astar.size() - 1].destX*TILESIZE + TILESIZE / 2;
		_playerPoint.y = astar[astar.size() - 1].destY*TILESIZE + TILESIZE / 2;
		//�þ�ó��
		fovCheck();

		//��ǥ���� ����
		astar.erase(astar.begin() + astar.size() - 1);

		//�� �ѱ��
		endTurn();
	}
}
void Player::getDamaged(int damage)
{
	if (RND->getFloat(1.0)<_playerStat.atk_lck)
	{
		//������
	}
	else
	{
		if (damage - _playerStat.def > 0)
		{
			//���
			_playerStat.hp -= damage;
			monster_attack_dp = damage;
			damaged = true;
		}
		else
		{
			//�������

		}
	}
}
void Player::mouseClickEvent()
{
	//�����̴� �߿� ���콺 Ŭ�� �̺�Ʈ �߻� �ϸ� ���� Ÿ�ϸ� ���� ���� ��
	if (_keepMove && astar.size()>0)
	{
		TILE temp;
		temp = astar[astar.size()-1];
		astar.clear();
		astar.push_back(temp);
		return;
	}
	
	POINT ptMouse = _ptMouse;
	ptMouse.x -= _ui->getCamera().x;
	ptMouse.y -= _ui->getCamera().y;
	_isEnemyTargeted = false;
	for (auto i : _em->getEnemyVector())
	{
		//���͸� Ŭ���ߴٸ�?
		if ((ptMouse.x / TILESIZE == i->getPoint().x / TILESIZE && ptMouse.y / TILESIZE == i->getPoint().y / TILESIZE) &&
			_map->getTile(ptMouse.x / TILESIZE, ptMouse.y / TILESIZE).tileview != TILEVIEW_NO && i->getCHP() > 0 && _map->getCurStageNum() == i->getFloor())
		{
			//��ǥ ����
			_isEnemyTargeted = true;
			_TargetEnemy = i;
			astar = _map->aStar(_playerPoint, ptMouse);
			int a = 0;
			//���� �ִ��� ���� �Ǵ�
			if (astar.size() > 0)
			{
				//���� ��ġ�� ��
				astar.erase(astar.begin() + 0);
			}

			if (astar.size() > 0)
			{
				//������ġ ��
				astar.erase(astar.begin() + astar.size() - 1);
			}

			break;
		}
	}

	//���� ���� ���� Ŭ���ߴٸ�?
	if ((_map->getTile(ptMouse.x / TILESIZE, ptMouse.y / TILESIZE).terrain != TERRAIN_NULL && !_isEnemyTargeted)&&
		_map->getTile(ptMouse.x / TILESIZE, ptMouse.y / TILESIZE).tileview != TILEVIEW_NO)
	{
		//�̵���� ����
		astar = _map->aStar(_playerPoint, ptMouse);
		//���� �ִ��� ���� �Ǵ�
		if (astar.size() > 0)
		{
			//���� ��ġ�� ��
			astar.erase(astar.begin() + astar.size() - 1);
		}
	}
	//keepMove��?? -> ���� �� ���� �ִ��� ���� (A*�� ���� �����ִ��� ����)
	if (astar.size() > 0)
	{
		_keepMove = true;
	}
	else
	{
		_keepMove = false;
	}

	if (!_keepMove)
	{
		RECT temp = RectMakeCenter(_playerPoint.x, _playerPoint.y, TILESIZE * 3, TILESIZE * 3);
		if (PtInRect(&temp, ptMouse))
		{
			//���踦 ������ ������
			//if()~~~~~
			_map->setTile_UnlockDoor(ptMouse.x / TILESIZE, ptMouse.y / TILESIZE);
			
		}
	}
}

void Player::endTurn()
{
	//�� ����� �߻��ϴ� ȿ�� �߰�
	effectDebuff();
	effectBuff();
	_playerStat.hunger--;

	//����� ó��
	if (_playerStat.hunger < 50)
	{
		_playerStat.hp--;
	}
	else if (_playerStat.hunger > 100)
	{
		if (_playerStat.maxhp < 250)
		{
			_playerStat.hp++;
		}

		if (_playerStat.hp >= 250)
		{
			_playerStat.hp = _playerStat.maxhp;
		}
	}

	//�� ����
	_action = false;
	//�� ����
	_em->setTurn(true);
	//keepMove��?? -> ���� �� ���� �ִ��� ���� (A*�� ���� �����ִ��� ����)
	if (astar.size() > 0)
	{
		_keepMove = true;
	}
	else
	{
		_keepMove = false;
	}
	//�ʿ� �� �����ٴ� ���� �Ѱ���
	_map->playerTurnEnd();
}

void Player::expUp(int exp)
{
	_playerStat.exp += exp;
	if(_playerStat.exp >= 100)
	{
		_playerStat.lv++;
		_playerStat.exp = 0;

		_playerStat.maxhp += 15;
		//ȸ�� & ���߷� up
		//_playerStat.atk_lck += 0.1;
		//_playerStat.avd_lck += 0.1;
	}	
}

void Player::effectDebuff()
{
	bool isThereFrozenDebuff = false;
	for (auto i : _vdebuff)
	{
		switch (i.type)
		{
		case DEBUFF_BLEEDING:
			_playerStat.hp -= i.damage;
			break;
		case DEBUFF_FIRE:
			_playerStat.hp -= i.damage;
			break;
		case DEBUFF_FROZEN:
			isThereFrozenDebuff = true;
			break;
		case DEBUFF_HUNGER:

			break;
		}
		i.lefttime--;
	}
	if (isThereFrozenDebuff)
	{
		for (int i = 0; i < _vdebuff.size(); i++)
		{
			if (_vdebuff[i].type == DEBUFF_FIRE)
			{
				_vdebuff.erase(_vdebuff.begin() + i);
			}
		}
	}
	for (int i = 0; i < _vdebuff.size(); i++)
	{
		if (_vdebuff[i].lefttime <= 0)
		{
			_vdebuff.erase(_vdebuff.begin() + i);
		}
	}
}
void Player::effectBuff()
{
	for (auto i : _vbuff)
	{
		switch (i.type)
		{
		case BUFF_INVISIBLE:

			break;
		case BUFF_LEVITATION:

			break;
		case BUFF_NATURAL_ARMOR:

			break;
		case BUFF_NATURAL_HEAL:

			break;
		}
	}
}

void Player::setChangeFoor()
{
	if (astar.size() > 0) astar.clear();
	fovCheck();
	endTurn();
}

void Player::stopMoving()
{
	if (_keepMove && astar.size()>0)
	{
		TILE temp;
		temp = astar[astar.size() - 1];
		astar.clear();
		astar.push_back(temp);
		return;
	}
}

void Player::activeTurn()
{
	_action = true;

}