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

	_isSwarmSpawn = false;
	_swarmSpawn.clear();

	setEnemy(PointMake(12, 12), 2);

	//setEnemy(PointMake(12, 12), 2);
	//setEnemy(PointMake(TILESIZE*14, TILESIZE*13), 0);
	//setEnemy(PointMake(13, 13), 2);

	return S_OK;
}

void EnemyManager::release()
{

}

void EnemyManager::update()
{
	for (int i = 0; i < _vEnemy.size(); i++)
	{
		_viEnemy = _vEnemy.begin() + i;
		if (!(*_viEnemy)->getLive())
		{
			_vEnemy.erase(_viEnemy);
			i--;
			break;
		}
	}
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

	if (_actionCount == 0)
	{
		//ù��° ���Ϳ��� �� �ѱ�
		_vEnemy[_actionCount]->setAction(true);
		//�������� ���� ��ȣ ����
		_actionCount++;
	}
	else if (_vEnemy[_actionCount - 1]->getAction() == false && _actionCount < _vEnemy.size())	//�� ������ ���� �ൿ�� ��������
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
	if (_isSwarmSpawn)
	{
		setSwarm();
		_isSwarmSpawn = false;
	}

	//��� ���� �ൿ�� ��������
	if (allEnemyTurnOver)
	{
		//���� ���� false ����
		_enemyTurn = false;
		_actionCount = 0;
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
		{

			Rat* temp = new Rat;
			temp->init(point);
			temp->setPlayerAddressLink(_player);
			temp->setItemManagerAddressLink(_im);
			temp->setUiAddressLink(_ui);
			temp->setMapAddressLink(_map);
			_vEnemy.push_back(temp);
			break;

		//��, Rat

		break;
		}
		case 1:
		{

			Mimic* temp = new Mimic;
			temp->init(point,4);
			temp->setPlayerAddressLink(_player);
			temp->setItemManagerAddressLink(_im);
			temp->setUiAddressLink(_ui);
			temp->setMapAddressLink(_map);
			_vEnemy.push_back(temp);

			//�̹�, Mimic
			break;
		}
		case 2:
		{
			//�ĸ�, Swarm
			Swarm* temp = new Swarm;
			temp->init(point);
			temp->setEm(this);
			temp->setPlayerAddressLink(_player);
			temp->setItemManagerAddressLink(_im);
			temp->setUiAddressLink(_ui);
			temp->setMapAddressLink(_map);
			_vEnemy.push_back(temp);
			break;
		}
		case 3:
		{
			//��, Gnoll
			Gnoll* temp = new Gnoll;
			temp->init(point);
			temp->setPlayerAddressLink(_player);
			temp->setItemManagerAddressLink(_im);
			temp->setUiAddressLink(_ui);
			temp->setMapAddressLink(_map);
			_vEnemy.push_back(temp);
			break;
		}
		case 4:
		{

			goo* temp = new goo;
			temp->init(point,8);
			temp->setPlayerAddressLink(_player);
			temp->setItemManagerAddressLink(_im);
			temp->setUiAddressLink(_ui);
			temp->setMapAddressLink(_map);

			break;

		}
		case 5:
		{
			//
			break;
		}
		default:
		{
			//
			break;
		}
	}
}

void EnemyManager::setSwarm()
{
	for (int i = 0; i < _swarmSpawn.size(); i++)
	{
		Swarm* temp = new Swarm;
		temp->init(_swarmSpawn[i].pt, _swarmSpawn[i].hp);
		temp->setEm(this);
		temp->setPlayerAddressLink(_player);
		temp->setItemManagerAddressLink(_im);
		temp->setUiAddressLink(_ui);
		temp->setMapAddressLink(_map);
		_vEnemy.push_back(temp);
	}

	for(;_swarmSpawn.empty() ;)
		_swarmSpawn.clear();
}