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

	vector<tagBullet> _vThrow;
	vector<tagBullet>::iterator _viThrow;


public:
	HRESULT init();
	void release();
	void update();
	void render(POINT camera);
	void draw(POINT camera);

	void fire(image* img, float x, float y, float dextX, float destY);
	void throwItem(image* img, float x, float y, float destX, float destY);
	void bulletMove();
	void throwMove();
	void removeBullet(int arrNum);
	void removeThrow(int arrNum);

	vector<tagBullet> getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator getVBulletIter() { return _viBullet; }

	Item();
	~Item();
};

