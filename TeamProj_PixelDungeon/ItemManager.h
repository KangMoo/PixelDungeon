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

	EnemyManager* _em;
	Map* _map;
	UI* _ui;
	Player* _player;

public:
	HRESULT init();
	void release();
	void update();
	void render();



	void setEnemyManagerAddressLink(EnemyManager* em) { _em = em; }
	void setMapAddressLink(Map* map) { _map = map; }
	void setUiAddressLink(UI* ui) { _ui = ui; }
	void setPlayerAddressLink(Player* player) { _player = player; }

	ItemManager();
	~ItemManager();


};

