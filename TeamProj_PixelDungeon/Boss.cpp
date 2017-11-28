#include "stdafx.h"
#include "Boss.h"
#include "Player.h"
#include "UI.h"

Boss::Boss()
{
}


Boss::~Boss()
{
}


HRESULT Boss::init(POINT point)
{
	return S_OK;
}
HRESULT Boss::init(POINT point, int cog)//인식범위 추기
{
	return S_OK;
}
void Boss::release()
{

}
void Boss::update()
{


}

//그릴 때	x좌표에 camera.x 만큼
//			y좌표에 camera.y 만큼 더해주기!!!!
void Boss::render(POINT camera)
{
	draw(camera);
}
void Boss::draw(POINT camera)
{


}

void Boss::action()
{

}
void Boss::attack()
{

}

void Boss::move()
{

}

void Boss::frameUpdate()
{

}

//데미지 받았을 때, 회피율 계산하여 함수 만들기
void Boss::getDamaged(int damage)
{

}
