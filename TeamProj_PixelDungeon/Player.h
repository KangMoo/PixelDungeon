#pragma once
#include "gameNode.h"
#include "UI.h"

class EnemyManager;
class Map;
class UI;
class Enemy;
class ItemManager;
class Player : public gameNode
{
private:
	EnemyManager* _em;
	Map* _map;
	UI* _ui;
	ItemManager* _im;
	PLAYERSTAT _playerStat;
	POINT _point;
	image* _image;
	bool _action;

public:
	HRESULT init();
	HRESULT init(POINT point);
	void release();
	void update();
	void render();
	void render(POINT camera);
	void draw(POINT camera);
	void action();


	void getDamaged(int damange);

	//게터세터
	bool getAction() { return _action; }
	void setAction(bool action) { _action = action; }
	PLAYERSTAT getStat() { return _playerStat; }
	void setStat(PLAYERSTAT stat) { _playerStat = stat; }
	POINT getPoint() { return _point; }
	void setPoint(POINT point) { _point = point; }
	int getHP() { return _playerStat.hp; }
	void setHP(int hp) { _playerStat.hp = hp; }
	bool getTurn() { return _action; }
	void setTurn(bool turn) { _action = turn; }


	void setEnemyManagerAddressLink(EnemyManager* em) { _em = em; }
	void setMapAddressLink(Map* map) { _map = map; }
	void setUiAddressLink(UI* ui) { _ui = ui; }
	void setItemManagerAddressLink(ItemManager* im) { _im = im; }

	Player();
	~Player();
};

