#pragma once
#include "gameNode.h"
#include "Enemy.h"
#include "Boss.h"
#include "Gnoll.h"
#include "Swarm.h"
#include "Rat.h"
#include "mimic.h"
#include "goo.h"
#include "Crap.h"

struct tagSwarmSpawn
{
	POINT pt;
	int hp;
};

class Player;
class Map;
class UI;
class ItemManager;
class EnemyManager : public gameNode
{
private:
	vector<Enemy*> _vEnemy;
	vector<Enemy*>::iterator _viEnemy;


	Player* _player;
	Boss* _boss;
	Map* _map;
	UI* _ui;
	ItemManager* _im;
	bool _enemyTurn;
	int _actionCount;	//몇번째 몬스터가 행동하고 있는지 확인하기 위한 int값

	bool _isSwarmSpawn;
	tagSwarmSpawn _temp;
public:
	HRESULT init();
	void release();
	void update();
	void render();
	void render(POINT camera);
	void draw(POINT camera);
	void action();

	vector<Enemy*> getEnemyVector() { return _vEnemy; }
	Boss* getBoss() { return _boss; }
	bool getTurn() { return _enemyTurn; }
	void setTurn(bool turn) { _enemyTurn = turn; _actionCount = 0; }		//turn받을 때 actioncount도 0으로 대입

	void setPlayerAddressLink(Player* player) { _player = player; }
	void setMapAddressLink(Map* map) { _map = map; }
	void setUiAddressLink(UI* ui) { _ui = ui; }
	void setItemManagerAddressLink(ItemManager* im) { _im = im; }

	void enemyClear();

	void setEnemy(POINT point, int type);		//enemy 제작
	void setEnemy(POINT point, int type,int floor);		//enemy 제작

	void setSwarm();			//파리 전용
	void setSwarmSpawn(POINT pt, int hp)
	{
		_temp.pt = pt;
		_temp.hp = hp;
		_isSwarmSpawn = true;
	}

	EnemyManager();
	~EnemyManager();
};

