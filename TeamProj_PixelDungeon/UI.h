#pragma once
#include "gameNode.h"

#define ARRSIZE 24

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
	void fream_window_draw(size_t sizeX, size_t sizeY);
	void button_interface(int itemName, int itemtype, int createNumber, int fream_window_sizeX, int fream_window_sizeY, int position = 0);
	void item_sort();

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

	int _selectInterface = INTERFACEMENU_END;
	int _selectItem = NAME_END;

	typedef struct TagInventory
	{
		RECT inventoryRect = { 0,0,0,0 };
		int itemNumber = NAME_END;
		bool itemUse = false;
		bool itemWear = false;
	}Inventory;

	enum INTERFACEMENU
	{
		INTERFACEMENU_BACKPACK,
		INTERFACEMENU_SEARCH,
		INTERFACEMENU_TURNSKIP,
		INTERFACEMENU_END,
	};

	typedef struct tagButtonOption
	{
		int number = 0;
		bool use_weapon = false;
		bool use_armor = false;
		bool use_acc = false;
	}ButtonOption;

	Inventory _inventory[24];
	int fream_valueX = 0;
	int fream_valueY = 0;
	ButtonOption button_option_value[10];
	RECT button_option_intersectRect[10];

	int savepositionX = 0;
	int savepositionY = 0;

	int _itemPosition = 0;
	int _positionCheck = 0;
	int _wearNumber = 0;

	vector<tagItem>tempBag;
	vector<tagItem>::iterator i_tempBag;
};

