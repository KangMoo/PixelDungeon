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

//�׸� ��	x��ǥ�� camera.x ��ŭ
//			y��ǥ�� camera.y ��ŭ �����ֱ�!!!!
void Boss::render(POINT camera)
{
	draw(camera);
}
void Boss::draw(POINT camera)
{

	
}