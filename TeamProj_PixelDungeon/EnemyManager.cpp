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

	setEnemy(PointMake(12, 12), 5);

	//setEnemy(PointMake(12, 12), 2);

	//setEnemy(PointMake(TILESIZE*13, TILESIZE*11), 0);
	//setEnemy(PointMake(13, 13), 2);

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

	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end();)
	{
		if (!(*_viEnemy)->getLive())
		{
			(*_viEnemy)->release();
			_viEnemy = _vEnemy.erase(_viEnemy);
			_actionCount--;
			continue;
		}
		else ++_viEnemy;
	}

	if (_isSwarmSpawn)
	{
		setSwarm();
		_isSwarmSpawn = false;
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
			//��
			Crap* temp = new Crap;
			temp->init(point);
			temp->setPlayerAddressLink(_player);
			temp->setItemManagerAddressLink(_im);
			temp->setUiAddressLink(_ui);
			temp->setMapAddressLink(_map);
			_vEnemy.push_back(temp);
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
	Swarm* temp = new Swarm;
	temp->init(_temp.pt, _temp.hp);
	temp->setEm(this);
	temp->setPlayerAddressLink(_player);
	temp->setItemManagerAddressLink(_im);
	temp->setUiAddressLink(_ui);
	temp->setMapAddressLink(_map);
	_vEnemy.push_back(temp);
}

void EnemyManager::enemyClear()
{
	while (_vEnemy.empty()) 
	{
		_vEnemy.clear();
	}
}