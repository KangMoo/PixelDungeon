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
	vector<tagItem> _vItem;
	vector<tagItem>::iterator _viItem;

	vector<tagItem> _vBag;
	vector<tagItem>::iterator _viBag;

private:
	EnemyManager* _em;
	Map* _map;
	UI* _ui;
	Player* _player;
	Item* _item;

private:
	int _potion[7];
	int _wand[3];
	int _scroll[5];
	int _acc[2];

public:
	HRESULT init();
	void release();
	void update();
	void render(POINT camera);
	void draw(POINT camera);

	void setItem(tagItem* item, ITEMNAME name);
	void swap();
	void imgInit();


	void equipItem(int position);
	void unequipItem(int position);
	void useItem(int position, float x, float y);

	// 아이템 사용 함수 ( 주문서, 씨앗, 포션, 다트) 
	void useToScroll(ITEMNAME name, ITEMUSEMETHOD method);
	void useToSeed(ITEMNAME name, ITEMUSEMETHOD method);
	void useToPotion(ITEMNAME name, ITEMUSEMETHOD method);
	void useToDart(ITEMNAME name, ITEMUSEMETHOD method);


	void setItemToBag(ITEMNAME name);
	void setItemToField(ITEMNAME name, float x, float y);
	void setItemToBag(ITEMNAME name, bool identify, bool isCursed, int upgrade, int numOfItem);
	void setItemToField(ITEMNAME name, float x, float y, bool identify, bool isCursed, int upgrade, int numOfItem);

	void setEnemyManagerAddressLink(EnemyManager* em) { _em = em; }
	void setMapAddressLink(Map* map) { _map = map; }
	void setUiAddressLink(UI* ui) { _ui = ui; }
	void setPlayerAddressLink(Player* player) { _player = player; }





	vector<tagItem> getvItem() { return _vItem; }
	vector<tagItem>::iterator getvItemIter() { return _viItem; }

	vector<tagItem> getvBag() { return _vBag; }
	vector<tagItem>::iterator getvBagIter() { return _viBag; }

	ItemManager();
	~ItemManager();


};

