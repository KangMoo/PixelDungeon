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
	bool _isPlayerMoving;

public:
	HRESULT init();
	void release();
	void update();
	void render(POINT camera);
	void draw(POINT camera);
	void fream_window_draw(size_t sizeX, size_t sizeY, int coordX = 0, int coordY = 0);
	void button_interface(int itemName, int itemtype, int createNumber, int fream_window_sizeX, int fream_window_sizeY);
	void item_sort();
	void main_menu();
	void status_window();
	void search();
	void usingui();

	void BackPack();
	void PrintFont(char name[], HFONT hFont, HFONT oldFont, int x, int y, int size, char r = 0, char g = 0, char b = 0);

	void ResetInventory();
	void SortInventory();

	POINT getCamera() { return _camera; }
	void setCamera(POINT camera) { _camera = camera; }
	bool usingInterface();

	void setPlayerAddressLink(Player* player) { _player = player; }
	void setEnemyManagerAddressLink(EnemyManager* em) { _em = em; }
	void setMapAddressLink(Map* map) { _map = map; }
	void setItemManagerAddressLink(ItemManager* im) { _im = im; }
	UI();
	~UI();


private:
	float _interface_button_timer1;
	float _interface_button_timer2;
	float _interface_button_timer3;
	float _uitimer;

	float timer = 0;

	bool testbool = false;

	//RECT _inventory[4][6];

	int _selectInterface = INTERFACEMENU_END;
	int _selectItem = NAME_END;
	int _selectMenu = GAMEMENU_END;

	typedef struct TagInventory
	{
		RECT inventoryRect = { 0,0,0,0 };
		int itemNumber = NAME_END;
		bool itemUse = false;
		//bool itemWear = false;
	}Inventory;


	RECT _backPackRect;
	RECT _SearchOptionRect;
	RECT _TurnSkipRect;

	RECT _Target_ButtonRect;
	RECT _Special_ButtonRect;
	RECT _Monster_DisplyRect;

	RECT _Menu_selectRect;
	RECT _StatusRect;
	RECT _Menu_WindowRect[5];
	enum INTERFACEMENU
	{
		INTERFACEMENU_BACKPACK,
		INTERFACEMENU_SEARCH,
		INTERFACEMENU_TURNSKIP,
		INTERFACEMENU_MENU,
		INTERFACEMENU_STATUS,
		INTERFACEMENU_END,
	};

	enum GAMEMENU
	{
		GAMEMENU_SET,
		GAMEMENU_MAIN,
		GAMEMENU_EXIT,
		GAMEMENU_BACK,
		GAMEMENU_END,
	};

	typedef struct tagButtonOption
	{
		int number = 0;
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
	int inventory_null = 0;

	vector<tagItem>tempBag;
	vector<tagItem>::iterator i_tempBag;

	int testnumber = 0;
	int total = 0;

	//폰트용

	HFONT namehFont;
	HFONT nameoldFont;
};

