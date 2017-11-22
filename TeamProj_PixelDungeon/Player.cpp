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

	//addImg();
	//test~
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{

			tile[i][j].point = PointMake(i * 20 + 180, j * 20 + 50);
			tile[i][j].rc = RectMakeCenter(tile[i][j].point.x, tile[i][j].point.y, 20, 20);
			if (RND->getInt(7) == 0)
			{
				//벽
				tile[i][j].type = 1;
			}
			else
			{
				//없음
				tile[i][j].type = 0;
			}
		}
	}
	_playerPoint = PointMake(tile[10][10].rc.left + 10, tile[10][10].rc.top + 10);
	//~test
	_playerState = PLAYERSTATE_IDLE;
	_frameUpdateTimer = TIMEMANAGER->getWorldTime();
	_currentFrameX = _currentFrameY = 0;
	_image = IMAGEMANAGER->findImage("warrior_idle");
	return S_OK;
}
void Player::release()
{

}
void Player::update()
{

	//frameUpdate();
	//fovCheck();
	if (_action) action();
}


void Player::action()
{

	//무슨행동인지 판별
	switch (_playerState)
	{
	case PLAYERSTATE_IDLE:
		//마우스 클릭에 따른 액션 변경
		break;
	case PLAYERSTATE_MOVE:
		//행동에 따른 이미지 변경
		//행동
		break;
	case PLAYERSTATE_ATTACK:
		//행동에 따른 이미지 변경
		//행동
		break;
	case PLAYERSTATE_EAT:
		//행동에 따른 이미지 변경
		//행동
		break;
	case PLAYERSTATE_SCROLL:
		//행동에 따른 이미지 변경
		//행동
		break;
	case PLAYERSTATE_DEAD:
		break;
	}
	//행동 종료 후 action값 false로 바꿔주기

	//행동이 종료됐다면 적에게 턴 넘기기
	if (!_action)
	{
		_em->setTurn(true);
	}
}



//그릴 때	x좌표에 camera.x 만큼
//			y좌표에 camera.y 만큼 더해주기!!!!
void Player::render(POINT camera)
{
	//draw(camera);
}
//
//void Player::draw(POINT camera)
//{
////	//test~
////	for (auto i : tileCanSee)
////	{
////		switch (i.type)
////		{
////
////		case 0:
////			Rectangle(getMemDC(), i.rc.left, i.rc.top, i.rc.right, i.rc.bottom);
////			break;
////		case 1:
////		{
////			HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0));
////			FillRect(getMemDC(), &i.rc, brush);
////			DeleteObject(brush);
////		}
////		break;
////		case 2:
////			break;
////		case 3:
////
////			break;
////		}
////	}
////<<<<<<< HEAD
////
////	if (KEYMANAGER->isStayKeyDown(VK_SPACE))
////	{
////		for (int i = 0; i < 20; i++)
////		{
////			for (int j = 0; j < 20; j++)
////			{
////				switch (tile[i][j].type)
////				{
////				case 0:
////					Rectangle(getMemDC(), tile[i][j].rc.left, tile[i][j].rc.top, tile[i][j].rc.right, tile[i][j].rc.bottom);
////					break;
////				case 1:
////				{
////					HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0));
////					FillRect(getMemDC(), &tile[i][j].rc, brush);
////					DeleteObject(brush);
////				}
////				break;
////				case 2:
////					break;
////				case 3:
////
////					break;
////				}
////			}
////		}
////	}
////	for (auto i : angleCanTSee)
////	{
////		MoveToEx(getMemDC(), _playerPoint.x, _playerPoint.y, NULL);
////		LineTo(getMemDC(), _playerPoint.x + cosf(i.sangle) * 100, _playerPoint.y - sinf(i.sangle) * 100);
////		LineTo(getMemDC(), _playerPoint.x + cosf(i.eangle) * 100, _playerPoint.y - sinf(i.eangle) * 100);
////		LineTo(getMemDC(), _playerPoint.x, _playerPoint.y);
////	}
////	RectangleMakeCenter(getMemDC(), _playerPoint.x, _playerPoint.y, 7, 7);
////	//~test
//}
//
//void Player::addCanTSeeAngle(float sangle, float eangle)
//{
//	//추가
//	sightAngle temp;
//	temp.sangle = sangle;
//	temp.eangle = eangle;
//	angleCanTSee.push_back(temp);
//
//	vector<int> deleteNum;
//	
//	bool isTherNoIntersection = false;
//	while (!isTherNoIntersection)
//	{
//		isTherNoIntersection = true;
//		//중복되는 각도 합치기
//		for (int i = 0; i < angleCanTSee.size(); i++)
//		{
//			for (int j = i + 1; j < angleCanTSee.size(); j++)
//			{
//				//겹치는 각도가 있을 시
//				if ((angleCanTSee[i].sangle <= angleCanTSee[j].sangle && angleCanTSee[j].sangle <= angleCanTSee[i].eangle) ||
//					(angleCanTSee[i].sangle <= angleCanTSee[j].eangle && angleCanTSee[j].eangle <= angleCanTSee[i].eangle))
//				{
//					//
//					if (angleCanTSee[i].sangle >= angleCanTSee[j].sangle) angleCanTSee[i].sangle = angleCanTSee[j].sangle;
//					if (angleCanTSee[i].eangle <= angleCanTSee[j].eangle) angleCanTSee[i].eangle = angleCanTSee[j].eangle;
//					angleCanTSee.erase(angleCanTSee.begin() + j);
//					isTherNoIntersection = false;
//}
//
//void Player::addCanTSeeRect(RECT rc)
//{
//	POINT rcpoint = PointMake(rc.left + 10, rc.top + 10);
//	//동일 y축 위
//	if (_playerPoint.x == rcpoint.x)
//	{
//		//플레이어의 위
//		if (_playerPoint.y > rcpoint.y)
//		{
//			addCanTSeeAngle(getAngle(_playerPoint.x, _playerPoint.y, rc.right, rc.bottom), getAngle(_playerPoint.x, _playerPoint.y, rc.left, rc.bottom));
//		}
//		//플레이어의 아래
//		else if (_playerPoint.y < rcpoint.y)
//		{
//			addCanTSeeAngle(getAngle(_playerPoint.x, _playerPoint.y, rc.left, rc.top), getAngle(_playerPoint.x, _playerPoint.y, rc.right, rc.top));
//		}
//
//	}
//	//1,4사분면
//	else if (_playerPoint.x < rcpoint.x)
//	{
//		//동일 x축 위
//		if (_playerPoint.y == rcpoint.y)
//		{
//			addCanTSeeAngle(0, getAngle(_playerPoint.x, _playerPoint.y, rc.left, rc.top));
//			addCanTSeeAngle(getAngle(_playerPoint.x, _playerPoint.y, rc.left, rc.bottom), PI2);
//
//		}
//		//1사분면
//		else if (_playerPoint.y > rcpoint.y)
//		{
//			addCanTSeeAngle(getAngle(_playerPoint.x, _playerPoint.y, rc.right, rc.bottom), getAngle(_playerPoint.x, _playerPoint.y, rc.left, rc.top));
//		}
//		//4사분면
//		else if (_playerPoint.y < rcpoint.y)
//		{
//			addCanTSeeAngle(getAngle(_playerPoint.x, _playerPoint.y, rc.left, rc.bottom), getAngle(_playerPoint.x, _playerPoint.y, rc.right, rc.top));
//		}
//	}
//	//2,3사분면
//	else if (_playerPoint.x > rcpoint.x)
//	{
//		//동일 x축 위
//		if (_playerPoint.y == rcpoint.y)
//		{
//			addCanTSeeAngle(getAngle(_playerPoint.x, _playerPoint.y, rc.right, rc.top), getAngle(_playerPoint.x, _playerPoint.y, rc.right, rc.bottom));
//		}
//		//2사분면
//		else if (_playerPoint.y > rcpoint.y)
//		{
//			addCanTSeeAngle(getAngle(_playerPoint.x, _playerPoint.y, rc.right, rc.top), getAngle(_playerPoint.x, _playerPoint.y, rc.left, rc.bottom));
//		}
//		//3사분면
//		else if (_playerPoint.y < rcpoint.y)
//		{
//			addCanTSeeAngle(getAngle(_playerPoint.x, _playerPoint.y, rc.left, rc.top), getAngle(_playerPoint.x, _playerPoint.y, rc.right, rc.bottom));
//		}
//	}
//}
//
//void Player::frameUpdate()
//{
//	if (_currentFrameX < _image->getMaxFrameX())
//	{
//		_currentFrameX++;
//	}
//	else
//	{
//		_currentFrameX = 0;
//		if (_playerState != PLAYERSTATE_IDLE)
//		{
//			_playerState = PLAYERSTATE_IDLE;
//		}
//	}
//}
//
//void Player::imageChange(const char* str)
//{
//	_image = IMAGEMANAGER->findImage(str);
//	_currentFrameX = 0;
//}
//
//void Player::fovCheck()
//{
//	//FOV테스트~
//	_playerRC = RectMakeCenter(_playerPoint.x, _playerPoint.y, 20, 20);
//
//	RECT sightChkRC;
//	tileCanSee.clear();
//	angleCanTSee.clear();
//	for (int a = 0; a < 4; a++)
//	{
//		sightChkRC = RectMakeCenter(_playerPoint.x, _playerPoint.y, a * 40, a * 40);
//		for (int i = 0; i < 20; i++)
//		{
//			for (int j = 0; j < 20; j++)
//			{
//				RECT temp;
//				if (IntersectRect(&temp, &sightChkRC, &tile[i][j].rc))
//				{
//					bool addRECT = true;
//					for (auto k : angleCanTSee)
//					{
//
//						if (k.sangle <= getAngle(_playerPoint.x, _playerPoint.y, tile[i][j].point.x, tile[i][j].point.y) && getAngle(_playerPoint.x, _playerPoint.y, tile[i][j].point.x, tile[i][j].point.y) <= k.eangle)
//
//						{
//							addRECT = false;
//						}
//
//					}
//
//					if (addRECT)
//					{
//						tileCanSee.push_back(tile[i][j]);
//						switch (tile[i][j].type)
//						{
//						case 0:
//
//							break;
//							//벽
//						case 1:
//							addCanTSeeRect(tile[i][j].rc);
//							break;
//						case 2:
//							break;
//						case 3:
//							break;
//						}
//
//					}
//				}
//			}
//		}
//	}
//
//	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
//	{
//		_playerPoint.x -= 20;
//	}
//	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
//	{
//		_playerPoint.x += 20;
//	}
//	if (KEYMANAGER->isOnceKeyDown(VK_UP))
//	{
//		_playerPoint.y -= 20;
//	}
//	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
//	{
//		_playerPoint.y += 20;
//	}
//	//~FOV테스트
//}
//
//void Player::addImg()
//{
//	IMAGEMANAGER->addFrameImage("warrior_Idle", "Img//Player//warrior_idle.bmp", 48, 210, 2, 7, true, RGB(255, 0, 255));
//	IMAGEMANAGER->addFrameImage("warrior_Dead", "Img//Player//warrior_dead.bmp", 120, 210, 5, 7, true, RGB(255, 0, 255));
//	IMAGEMANAGER->addFrameImage("warrior_Eat", "Img//Player//warrior_eat.bmp", 48, 210, 2, 7, true, RGB(255, 0, 255));
//	IMAGEMANAGER->addFrameImage("warrior_Attack", "Img//Player//warrior_attack.bmp", 72, 210, 3, 7, true, RGB(255, 0, 255));
//	IMAGEMANAGER->addFrameImage("warrior_Scroll", "Img//Player//warrior_scroll.bmp", 72, 210, 3, 7, true, RGB(255, 0, 255));
//	IMAGEMANAGER->addFrameImage("warrior_Move", "Img//Player//warrior_move.bmp", 144, 210, 6, 7, true, RGB(255, 0, 255));
//
//}