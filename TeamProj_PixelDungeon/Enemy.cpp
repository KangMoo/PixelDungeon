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
HRESULT Enemy::init(POINT _point) //����Ʈ �߰�
{
	return S_OK;
}
void Enemy::release()
{

}
void Enemy::update()
{

	//���� �ൿ����(_action)�� true�� ��츸 action()����
	if (_action) action();
}
void Enemy::action()
{

	//�߿� : �ൿ�� �� ��ġ�� _action�� false�� �ٲ��ֱ�
}


//�׸� ��	x��ǥ�� camera.x ��ŭ
//			y��ǥ�� camera.y ��ŭ �����ֱ�!!!!
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
