#pragma once
#include "gameNode.h"

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
};

class Item : public gameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

public:
	HRESULT init();
	void release();
	void update();
	void render(POINT camera);
	void draw(POINT camera);

	void fire(image* img, float x, float y, float dextX, float destY);
	void bulletMove();
	void removeBullet(int arrNum);
	void itemUse(int position);
	void itemUse(ITEMNAME name);
	void itemUse(ITEMNAME name, int position);

	vector<tagBullet> getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator getVBulletIter() { return _viBullet; }

	Item();
	~Item();
};

