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


HRESULT Boss::init()
{
	return S_OK;
}
HRESULT Boss::init(POINT point)
{
	return S_OK;
}
void Boss::release()
{

}
void Boss::update()
{


}
void Boss::render()
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