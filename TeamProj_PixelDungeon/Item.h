#pragma once
#include "gameNode.h"

class Item : public gameNode
{
private:
	tagItem _item;	

public:
	HRESULT init();
	void release();
	void update();
	void render(POINT camera);
	void draw(POINT camera);

	Item();
	~Item();
};

