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
public:
	HRESULT init();
	void release();
	void update();
	void render();
	void render(POINT camera);
	void draw(POINT camera);


	void setPlayerAddressLink(Player* player) { _player = player; }
	void setEnemyManagerAddressLink(EnemyManager* em) { _em = em; }
	void setUiAddressLink(UI* ui) { _ui = ui; }
	void setItemManagerAddressLink(ItemManager* im) { _im = im; }
	Map();
	~Map();
};

