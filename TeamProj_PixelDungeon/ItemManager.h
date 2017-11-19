#pragma once
#include "gameNode.h"
#include "Item.h"

class EnemyManager;
class Map;
class UI;
class Player;

class ItemManager :public gameNode
{
private:
	vector<Item*> _vItem;
	vector<Item*>::iterator _viItem;

	vector<Item*> _vBag;
	vector<Item*>::iterator _viBag;

private:
	EnemyManager* _em;
	Map* _map;
	UI* _ui;
	Player* _player;

private:
	int _potion[7];
	int _wand[3];
	int _scroll[5];

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void swap();
	void imgInit();

	void setEnemyManagerAddressLink(EnemyManager* em) { _em = em; }
	void setMapAddressLink(Map* map) { _map = map; }
	void setUiAddressLink(UI* ui) { _ui = ui; }
	void setPlayerAddressLink(Player* player) { _player = player; }

	ItemManager();
	~ItemManager();


};

