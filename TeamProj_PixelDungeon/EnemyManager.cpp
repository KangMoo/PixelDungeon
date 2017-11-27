#include "stdafx.h"
#include "EnemyManager.h"
#include "Player.h"
#include "Map.h"
#include "UI.h"

EnemyManager::EnemyManager()
{
}


EnemyManager::~EnemyManager()
{
}

HRESULT EnemyManager::init()
{
	_enemyTurn = false;
	_actionCount = 0;
	return S_OK;
}

void EnemyManager::release()
{

}

void EnemyManager::update()
{
	for (auto i : _vEnemy)
	{
		i->update();
	}


	//���ʰ� ���Ϳ��� �Ѱ��� ��� && ������ ���� �ϳ� �̻� ���� ���
	if (_enemyTurn && _vEnemy.size() > 0)
	{
		//���� �ൿ
		action();
	}
	//�׳� ���ʸ� �Ѱܹ��� ���
	else if (_enemyTurn)
	{
		//���� ���� false ����
		_enemyTurn = false;
		//�÷��̾� ���� true ����
		_player->setTurn(true);
	}
}
void EnemyManager::action()
{

	if (_actionCount = 0)
	{
		//ù��° ���Ϳ��� �� �ѱ�
		_vEnemy[_actionCount]->setAction(true);
		//�������� ���� ��ȣ ����
		_actionCount++;
	}
	else if (_vEnemy[_actionCount - 1]->getAction() == false)	//�� ������ ���� �ൿ�� ��������
	{
		//�������� ���Ϳ��� �� �ѱ�
		_vEnemy[_actionCount]->setAction(true);
		//�������� ���� ��ȣ ����
		_actionCount++;
	}

	bool allEnemyTurnOver = true;	//��� ���� �ൿ ���ƴ��� Ȯ���ϱ� ���� �Լ�
	for (auto i : _vEnemy)
	{
		//���ʸ� ��ġ�� ���� ���� ������ allEnemyTurnOver = false
		if (i->getAction()) allEnemyTurnOver = false;
	}

	//��� ���� �ൿ�� ��������
	if (allEnemyTurnOver)
	{
		//���� ���� false ����
		_enemyTurn = false;
		//�÷��̾� ���� true ����
		_player->setTurn(true);
	}
}
void EnemyManager::render()
{

}

//�׸� ��	x��ǥ�� camera.x ��ŭ
//			y��ǥ�� camera.y ��ŭ �����ֱ�!!!!
void EnemyManager::render(POINT camera)
{	
	for (auto i : _vEnemy)
	{		
		i->render(camera);
	}
}
void EnemyManager::draw(POINT camera)
{

}

void EnemyManager::setEnemy(POINT point, int type)
{
	switch (type)
	{
	case 0:
		//��, Rat

		break;
	case 1:
		//�̹�, Mimic
		break;
	case 2:
		//�ĸ�, Swarm
		break;
	case 3:
		//��, Gnoll
		break;
	case 4:
		//
		break;
	case 5:
		//
		break;
	default:
		//
		break;
	}
}