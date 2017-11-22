#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"
#include "UI.h"

Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}


HRESULT Enemy::init()
{
	return S_OK;
}
HRESULT Enemy::init(POINT _point) //포인트 추가
{
	return S_OK;
}
void Enemy::release()
{

}
void Enemy::update()
{

	//몬스터 행동조건(_action)이 true일 경우만 action()실행
	if (_action) action();
}
void Enemy::action()
{

	//중요 : 행동을 다 마치면 _action값 false로 바꿔주기
}


//그릴 때	x좌표에 camera.x 만큼
//			y좌표에 camera.y 만큼 더해주기!!!!
void Enemy::render(POINT camera)
{
	draw(camera);
}
void Enemy::draw(POINT camera)
{

}

void Enemy::attack()
{


}
void Enemy::move()
{

}

void Enemy::frameUpdate()
{

}
