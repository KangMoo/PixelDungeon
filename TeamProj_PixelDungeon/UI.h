#pragma once
#include "gameNode.h"

class EnemyManager;
class Player;
class Map;
class ItemManager;

class UI : public gameNode
{
private:
	Player* _player;
	EnemyManager* _em;
	Map* _map;
	ItemManager* _im;

	POINT _camera;		//camera가 화면의 중심이 됨

public:
	HRESULT init();
	void release();
	void update();
	void render(POINT camera);
	void draw(POINT camera);
	
	POINT getCamera() { return _camera; }
	void setCamera(POINT camera) { _camera = camera; }

	void setPlayerAddressLink(Player* player) { _player = player; }
	void setEnemyManagerAddressLink(EnemyManager* em) { _em = em; }
	void setMapAddressLink(Map* map) { _map = map; }
	void setItemManagerAddressLink(ItemManager* im) { _im = im; }
	UI();
	~UI();
};

