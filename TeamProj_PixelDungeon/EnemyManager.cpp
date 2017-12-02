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


	//setEnemy(PointMake(6, 6), 2,0);
	//setEnemy(PointMake(5, 5), 2, 0);
	//setEnemy(PointMake(5, 5), 3, 0);
	//setEnemy(PointMake(6, 6), 5, 0);
	//setEnemy(PointMake(5, 5), 3, 0);
	//setEnemy(PointMake(4, 5), 5, 0);
	//setEnemy(PointMake(6, 6), 5, 0);
	//setEnemy(PointMake(12, 12), 1,1);
	//setEnemy(PointMake(12, 12), 4, 1);

	//setEnemy(PointMake(TILESIZE*14, TILESIZE*13), 0);
	//setEnemy(PointMake(TILESIZE*13, TILESIZE*11), 0);
	//setEnemy(PointMake(13, 13), 2);

	return S_OK;

	_finish = true;

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

	//차례가 몬스터에게 넘겨질 경우 && 몬스터의 수가 하나 이상 있을 경우
	if (_enemyTurn && _vEnemy.size() > 0)
	{
		//몬스터 행동
		action();		
	}
	//그냥 차례만 넘겨받은 경우
	else if (_enemyTurn)
	{
		//몬스터 차례 false 대입
		_enemyTurn = false;
		//플레이어 차례 true 대입
		_player->setTurn(true);
	}
}
void EnemyManager::action()
{
	bool allEnemyTurnOver = true;	//모든 적이 행동 마쳤는지 확인하기 위한 함수
	for (auto i : _vEnemy)
	{
		//차례를 마치지 않은 적이 있으면 allEnemyTurnOver = false
		if (i->getAction()) allEnemyTurnOver = false;
	}

	//모든 적이 행동을 마쳤으면
	if (allEnemyTurnOver)
	{
		//몬스터 차례 false 대입
		_enemyTurn = false;
		_actionCount = 0;
		//플레이어 차례 true 대입
		_player->activeTurn();
		_finish = true;
	}

	if (!_finish) return;

	_finish = false;

	//if (_actionCount == 0)
	//{
	//	//첫번째 몬스터에게 턴 넘김
	//		_vEnemy[_actionCount]->setAction(true);
	//		//다음차례 몬스터 번호 저장
	//		_actionCount++;
	//}
	//else if (_vEnemy[_actionCount - 1]->getAction() == false && _actionCount < _vEnemy.size())	//전 차례의 몬스터 행동이 끝났으면
	//{
	//	//다음차례 몬스터에게 턴 넘김
	//		_vEnemy[_actionCount]->setAction(true);
	//		//다음차례 몬스터 번호 저장
	//		_actionCount++;
	//}

	for (auto i : _vEnemy) {
		i->setAction(true);
	}

}
void EnemyManager::render()
{

}

//그릴 때	x좌표에 camera.x 만큼
//			y좌표에 camera.y 만큼 더해주기!!!!
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

void EnemyManager::setEnemy(POINT point, int type, int floor)
{
	switch (type)
	{
	case 0:
	{
		Rat* temp = new Rat;
		temp->init(point, floor);
		temp->setPlayerAddressLink(_player);
		temp->setItemManagerAddressLink(_im);
		temp->setUiAddressLink(_ui);
		temp->setMapAddressLink(_map);
		_vEnemy.push_back(temp);
		break;

		//쥐, Rat

		break;
	}
	case 1:
	{

		Mimic* temp = new Mimic;
		temp->init(point, floor);
		temp->setPlayerAddressLink(_player);
		temp->setItemManagerAddressLink(_im);
		temp->setUiAddressLink(_ui);
		temp->setMapAddressLink(_map);
		_vEnemy.push_back(temp);

		//미믹, Mimic
		break;
	}
	case 2:
	{
		//파리, Swarm
		Swarm* temp = new Swarm;
		temp->init(point, floor);
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
		//놀, Gnoll
		Gnoll* temp = new Gnoll;
		temp->init(point, floor);
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
		temp->init(point, floor);
		temp->setPlayerAddressLink(_player);
		temp->setItemManagerAddressLink(_im);
		temp->setUiAddressLink(_ui);
		temp->setMapAddressLink(_map);
		_vEnemy.push_back(temp);
		break;

	}
	case 5:
	{
		//게
		Crap* temp = new Crap;
		temp->init(point, floor);
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
	temp->init(_temp.pt, _temp.hp, _temp.floor, _temp.drop);
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