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

	//�ൿ ���� �� action�� false�� �ٲ��ֱ�
	
	//�ൿ�� ����ƴٸ� ������ �� �ѱ��
	if (!_action)
	{
		_em->setTurn(true);
	}
}

void Player::render()
{

}


//�׸� ��	x��ǥ�� camera.x ��ŭ
//			y��ǥ�� camera.y ��ŭ �����ֱ�!!!!
void Player::render(POINT camera)
{
	draw(camera);
}

void Player::draw(POINT camera)
{
	
}