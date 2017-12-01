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
struct tagEffect
{
	image* img; //이펙트 이미지;
	RECT rc;	//이펙트 rc;
	int size;	//이펙트 사이즈
	int Trans;	//투명도 0~255;
	bool isSee; // 완전 투명해짐?
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
	tagEffect frozenE[20];
	tagEffect fireE[20];


private:
	int _potion[7];
	int _wand[3];
	int _scroll[5];
	int _acc[2];

	bool _potionIdentified[7];
	bool _scrollIdentified[5];
	bool _fire;
	bool _frozen;
public:
	HRESULT init();
	void release();
	void update();
	void render(POINT camera);
	void draw(POINT camera);

	void setItem(tagItem* item, ITEMNAME name);
	void swap();
	void imgInit();
	
	//============== T E S T =================
	void keyControl();

	//============= I T E M ==================
	void equipItem(int position);
	void unequipItem(int position);
	void useItem(int position);
	void useItem(int position, float x, float y);
	void useItem(int position, int target);

	//=========== T H R O W ===============
	void fire(image* img, float dextX, float destY);
	void throwItem(int position, float destX, float destY);
	void bulletMove();
	void throwMove();

	//=========== R E M O V E =============
	void removeBullet(int arrNum);
	void removeThrow(int arrNum);
	void removeFieldItem(int arrNum);
	void removeBagItem(int arrNum);
	
	//=========== A D D   I T E M  ============
	void setItemToBag(ITEMNAME name);
	void setItemToField(ITEMNAME name, float x, float y);
	void setItemToBag(ITEMNAME name, bool identify, bool isCursed, int upgrade, int numOfItem);
	void setItemToField(ITEMNAME name, float x, float y, bool identify, bool isCursed, int upgrade, int numOfItem);

	//=========== L I N K ===================
	void setEnemyManagerAddressLink(EnemyManager* em) { _em = em; }
	void setMapAddressLink(Map* map) { _map = map; }
	void setUiAddressLink(UI* ui) { _ui = ui; }
	void setPlayerAddressLink(Player* player) { _player = player; }


	void liquidFire(float x, float y);
	void liquidFireEffect(float x, float y);
	void frozen(float x, float y);
	void frozenEffect(float x, float y);

	//================= G E T T E R ================
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

