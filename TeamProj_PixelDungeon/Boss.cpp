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
HRESULT Boss::init(POINT point, int cog)//�νĹ��� �߱�
{
	return S_OK;
}
void Boss::release()
{

}
void Boss::update()
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

//������ �޾��� ��, ȸ���� ����Ͽ� �Լ� �����
void Boss::getDamaged(int damage)
{

}
