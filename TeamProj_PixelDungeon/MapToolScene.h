#pragma once
#include "gameNode.h"
class MapToolScene : public gameNode
{
private:

public:
	HRESULT init();
	void release();
	void update();
	void render();

	MapToolScene();
	~MapToolScene();
};

