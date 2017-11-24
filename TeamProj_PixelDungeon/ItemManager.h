#pragma once
#include "gameNode.h"
#include "Item.h"

class EnemyManager;
class Map;
class UI;
class Player;

struct tagBullet
{
	image* img;
	RECT rc;
	float x, y;
	float initX, initY;
	float destX, destY;
	float angle;
	float speed;
	bool fire;
	int count;
	int position;
};


class ItemManager :public gameNode
{
private:
	vector<tagItem> _vItem;
	vector<tagItem>::iterator _viItem;

	vector<tagItem> _vBag;
	vector<tagItem>::iterator _viBag;

	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	vector<tagBullet> _vThrow;
	vector<tagBullet>::iterator _viThrow;



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
	void useItem(int position);
	void useItem(int position, float x, float y);
	void useItem(int position, int target);

	//=========== T H R O W ===============
	void fire(image* img, float x, float y, float dextX, float destY);
	void throwItem(int position, float x, float y, float destX, float destY);
	void bulletMove();
	void throwMove();
	void removeBullet(int arrNum);
	void removeThrow(int arrNum);

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

	vector<tagBullet> getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator getVBulletIter() { return _viBullet; }

	vector<tagBullet> getVThrow() { return _vThrow; }
	vector<tagBullet>::iterator getVThrowIter() { return _viThrow; }


	ItemManager();
	~ItemManager();


};

