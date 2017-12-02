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
	int _actionCount;	//���° ���Ͱ� �ൿ�ϰ� �ִ��� Ȯ���ϱ� ���� int��

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
	void setTurn(bool turn) { _enemyTurn = turn; _actionCount = 0; }		//turn���� �� actioncount�� 0���� ����

	void setPlayerAddressLink(Player* player) { _player = player; }
	void setMapAddressLink(Map* map) { _map = map; }
	void setUiAddressLink(UI* ui) { _ui = ui; }
	void setItemManagerAddressLink(ItemManager* im) { _im = im; }

	void enemyClear();

	void setEnemy(POINT point, int type);		//enemy ����
	void setEnemy(POINT point, int type,int floor);		//enemy ����

	void setSwarm();			//�ĸ� ����
	void setSwarmSpawn(POINT pt, int hp)
	{
		_temp.pt = pt;
		_temp.hp = hp;
		_isSwarmSpawn = true;
	}

	EnemyManager();
	~EnemyManager();
};

