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

	if (_actionCount = 0)
	{
		//첫번째 몬스터에게 턴 넘김
		_vEnemy[_actionCount]->setAction(true);
		//다음차례 몬스터 번호 저장
		_actionCount++;
	}
	else if (_vEnemy[_actionCount - 1]->getAction() == false)	//전 차례의 몬스터 행동이 끝났으면
	{
		//다음차례 몬스터에게 턴 넘김
		_vEnemy[_actionCount]->setAction(true);
		//다음차례 몬스터 번호 저장
		_actionCount++;
	}

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
		//플레이어 차례 true 대입
		_player->setTurn(true);
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

void EnemyManager::setEnemy(POINT point, int type)
{
	switch (type)
	{
	case 0:
		//쥐, Rat

		break;
	case 1:
		//미믹, Mimic
		break;
	case 2:
		//파리, Swarm
		break;
	case 3:
		//놀, Gnoll
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