#pragma once
#include "gameNode.h"
class EnemyManager;
class Player;
class UI;
class ItemManager;

class Map : public gameNode
{
private:
	EnemyManager* _em;
	Player* _player;
	UI* _ui;
	ItemManager* _im;

	bool start;

	vector<TILE> _vMapTile;

	TILE _map[100][100];

	TILE _mapTest[10000];

	SAVETILE loadMap[10000];


public:
	HRESULT init();
	void release();
	void update();
	void render();
	void render(POINT camera);
	void draw(POINT camera);

	void load();

	TILE* getMap() { return *_map; }
	TILE getTile(int i, int j) { return _map[i][j]; }
	void setTile(TILE tile, int i, int j) { _map[i][j] = tile; }

	void setPlayerAddressLink(Player* player) { _player = player; }
	void setEnemyManagerAddressLink(EnemyManager* em) { _em = em; }
	void setUiAddressLink(UI* ui) { _ui = ui; }
	void setItemManagerAddressLink(ItemManager* im) { _im = im; }
	Map();
	~Map();
};

