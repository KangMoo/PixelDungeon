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
	_playerPoint = PointMake(_map->getTile(3, 3).destX*TILESIZE + TILESIZE / 2, _map->getTile(3, 3).destY*TILESIZE + TILESIZE / 2);




	//~test
	_maptile = _map->getMap();
	_playerState = PLAYERSTATE_IDLE;
	_frameUpdateTimer = TIMEMANAGER->getWorldTime();
	_currentFrameX = _currentFrameY = 0;
	_image = IMAGEMANAGER->findImage("warrior_Idle");
	return S_OK;
}
void Player::release()
{

}
void Player::update()
{

	frameUpdate();
	fovCheck();
	if (_action) action();
}


void Player::action()
{

	//�����ൿ���� �Ǻ�
	switch (_playerState)
	{
	case PLAYERSTATE_IDLE:
		//���콺 Ŭ���� ���� �׼� ����
		break;
	case PLAYERSTATE_MOVE:
		//�ൿ�� ���� �̹��� ����
		//�ൿ
		break;
	case PLAYERSTATE_ATTACK:
		//�ൿ�� ���� �̹��� ����
		//�ൿ
		break;
	case PLAYERSTATE_EAT:
		//�ൿ�� ���� �̹��� ����
		//�ൿ
		break;
	case PLAYERSTATE_SCROLL:
		//�ൿ�� ���� �̹��� ����
		//�ൿ
		break;
	case PLAYERSTATE_DEAD:
		break;
	}
	//�ൿ ���� �� action�� false�� �ٲ��ֱ�

	//�ൿ�� ����ƴٸ� ������ �� �ѱ��
	if (!_action)
	{
		_em->setTurn(true);
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
	//for (auto i : tileCanSee)
	//{
	//	switch (i.type)
	//	{
	//
	//	case 0:
	//		Rectangle(getMemDC(), i.rc.left, i.rc.top, i.rc.right, i.rc.bottom);
	//		break;
	//	case 1:
	//	{
	//		HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0));
	//		FillRect(getMemDC(), &i.rc, brush);
	//		DeleteObject(brush);
	//	}
	//	break;
	//	case 2:
	//		break;
	//	case 3:
	//
	//		break;
	//	}
	//}
	//
	//if (KEYMANAGER->isStayKeyDown(VK_SPACE))
	//{
	//	for (int i = 0; i < 20; i++)
	//	{
	//		for (int j = 0; j < 20; j++)
	//		{
	//			switch (tile[i][j].type)
	//			{
	//			case 0:
	//				Rectangle(getMemDC(), tile[i][j].rc.left, tile[i][j].rc.top, tile[i][j].rc.right, tile[i][j].rc.bottom);
	//				break;
	//			case 1:
	//			{
	//				HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0));
	//				FillRect(getMemDC(), &tile[i][j].rc, brush);
	//				DeleteObject(brush);
	//			}
	//			break;
	//			case 2:
	//				break;
	//			case 3:
	//
	//				break;
	//			}
	//		}
	//	}
	//}
	//for (auto i : angleCanTSee)
	//{
	//	MoveToEx(getMemDC(), _playerPoint.x, _playerPoint.y, NULL);
	//	LineTo(getMemDC(), _playerPoint.x + cosf(i.sangle) * 100, _playerPoint.y - sinf(i.sangle) * 100);
	//	LineTo(getMemDC(), _playerPoint.x + cosf(i.eangle) * 100, _playerPoint.y - sinf(i.eangle) * 100);
	//	LineTo(getMemDC(), _playerPoint.x, _playerPoint.y);
	//}
	//RectangleMakeCenter(getMemDC(), _playerPoint.x, _playerPoint.y, 7, 7);
	//~test

	_image->alphaFrameRender(getMemDC(), _playerPoint.x - _image->getFrameWidth() / 2, _playerPoint.y - _image->getFrameHeight() / 2, _currentFrameX, _currentFrameY, 0);
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
	POINT rcpoint = PointMake(rc.left + TILESIZE/2, rc.top + TILESIZE/2);
	//���� y�� ��
	if (_playerPoint.x == rcpoint.x)
	{
		//�÷��̾��� ��
		if (_playerPoint.y > rcpoint.y)
		{
			addCanTSeeAngle(getAngle(_playerPoint.x, _playerPoint.y, rc.right, rc.bottom), getAngle(_playerPoint.x, _playerPoint.y, rc.left, rc.bottom));
		}
		//�÷��̾��� �Ʒ�
		else if (_playerPoint.y < rcpoint.y)
		{
			addCanTSeeAngle(getAngle(_playerPoint.x, _playerPoint.y, rc.left, rc.top), getAngle(_playerPoint.x, _playerPoint.y, rc.right, rc.top));
		}

	}
	//1,4��и�
	else if (_playerPoint.x < rcpoint.x)
	{
		//���� x�� ��
		if (_playerPoint.y == rcpoint.y)
		{
			addCanTSeeAngle(0, getAngle(_playerPoint.x, _playerPoint.y, rc.left, rc.top));
			addCanTSeeAngle(getAngle(_playerPoint.x, _playerPoint.y, rc.left, rc.bottom), PI2);
		}
		//1��и�
		else if (_playerPoint.y > rcpoint.y)
		{
			addCanTSeeAngle(getAngle(_playerPoint.x, _playerPoint.y, rc.right, rc.bottom), getAngle(_playerPoint.x, _playerPoint.y, rc.left, rc.top));
		}
		//4��и�
		else if (_playerPoint.y < rcpoint.y)
		{
			addCanTSeeAngle(getAngle(_playerPoint.x, _playerPoint.y, rc.left, rc.bottom), getAngle(_playerPoint.x, _playerPoint.y, rc.right, rc.top));
		}
	}
	//2,3��и�
	else if (_playerPoint.x > rcpoint.x)
	{
		//���� x�� ��
		if (_playerPoint.y == rcpoint.y)
		{
			addCanTSeeAngle(getAngle(_playerPoint.x, _playerPoint.y, rc.right, rc.top), getAngle(_playerPoint.x, _playerPoint.y, rc.right, rc.bottom));
		}
		//2��и�
		else if (_playerPoint.y > rcpoint.y)
		{
			addCanTSeeAngle(getAngle(_playerPoint.x, _playerPoint.y, rc.right, rc.top), getAngle(_playerPoint.x, _playerPoint.y, rc.left, rc.bottom));
		}
		//3��и�
		else if (_playerPoint.y < rcpoint.y)
		{
			addCanTSeeAngle(getAngle(_playerPoint.x, _playerPoint.y, rc.left, rc.top), getAngle(_playerPoint.x, _playerPoint.y, rc.right, rc.bottom));
		}
	}
}

void Player::frameUpdate()
{
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
						if (k.sangle - PI/180 * limit <= getAngle(_playerPoint.x, _playerPoint.y, i*TILESIZE + TILESIZE / 2, j*TILESIZE + TILESIZE / 2) &&
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
					if (_map->getTile(i, j).terrain == TERRAIN_WALL)
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
	IMAGEMANAGER->addImage("blackTile", "Img//Player//blacktile.bmp", TILESIZE, TILESIZE, true, RGB(255, 0, 255));
}