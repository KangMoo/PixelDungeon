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
	
	return S_OK;
}
void Player::release()
{

}
void Player::update()
{
	if (_action) action();
}

void Player::action()
{

	//행동 종료 후 action값 false로 바꿔주기
	
	//행동이 종료됐다면 적에게 턴 넘기기
	if (!_action)
	{
		_em->setTurn(true);
	}
}

void Player::render()
{

}


//그릴 때	x좌표에 camera.x 만큼
//			y좌표에 camera.y 만큼 더해주기!!!!
void Player::render(POINT camera)
{
	draw(camera);
}

void Player::draw(POINT camera)
{
	
}