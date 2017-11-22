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

	void swap();
	void imgInit();



	// ������ ��� �Լ� ( �ֹ���, ����, ����, ��Ʈ) 
	void useToScroll(ITEMNAME name, ITEMUSEMETHOD method);
	void useToSeed(ITEMNAME name, ITEMUSEMETHOD method);
	void useToPotion(ITEMNAME name, ITEMUSEMETHOD method);
	void useToDart(ITEMNAME name, ITEMUSEMETHOD method);


	void setItemToBag(ITEMNAME name);
	void setItemToField(ITEMNAME name);
	void setItemToBag(ITEMNAME name, bool isCursed, int upgrade);
	void setItemToField(ITEMNAME name, bool isCursed, int upgrade);

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

