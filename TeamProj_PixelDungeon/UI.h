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
	void fream_window_draw(size_t sizeX, size_t sizeY);
	void button_interface(int itemName, int itemtype, int createNumber, int fream_window_sizeX, int fream_window_sizeY, int positionX = 0, int positionY = 0);

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
	}Inventory;

	//enum ITEMSELECT
	//{
	//	ITEMSELECT_SOWRD,
	//	ITEMSELECT_END,
	//};

	enum INTERFACEMENU
	{
		INTERFACEMENU_BACKPACK,
		INTERFACEMENU_SEARCH,
		INTERFACEMENU_TURNSKIP,
		INTERFACEMENU_END,
	};

	Inventory _inventory[4][6];
	int fream_valueX = 0;
	int fream_valueY = 0;
	int button_option_value[10];
	RECT button_option_intersectRect[10];

	int savepositionX = 0;
	int savepositionY = 0;
};

