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

	void BackPack();
	void TestFunctin();

	POINT getCamera() { return _camera; }
	void setCamera(POINT camera) { _camera = camera; }

	void setPlayerAddressLink(Player* player) { _player = player; }
	void setEnemyManagerAddressLink(EnemyManager* em) { _em = em; }
	void setMapAddressLink(Map* map) { _map = map; }
	void setItemManagerAddressLink(ItemManager* im) { _im = im; }
	UI();
	~UI();

private:

	POINT _status_pane_pos;

	RECT _backPack;

	//RECT _inventory[4][6];

	int _selectInterface;
	int _selectItem = 0;

	typedef struct TagInventory
	{
		RECT inventoryRect = { 0,0,0,0 };
		int itemNumber = 0;
	}Inventory;

	enum ITEMLIST
	{
		ITEMLIST_NULL,
		ITEMLIST_TESTITEM1,
		ITEMLIST_TESTITEM2,
		ITEMLIST_TESTITEM3,
		ITEMLIST_TESTITEM4,
		ITEMLIST_END,
	};

	enum INTERFACEMENU
	{
		INTERFACEMENU_NULL,
		INTERFACEMENU_BACKPACK,
		INTERFACEMENU_END,
	};

	Inventory _inventory[4][6];
};

