#pragma once
#include "gameNode.h"

#define TILESIZE 32





class MapToolScene : public gameNode
{
private:
	vector<int> intd;

	
	vector<RECT> _tileButton;
	RECT _homeButton;




	


	int _cameraX, _cameraY;


public:
	HRESULT init();
	void release();
	void update();
	void render();
	

	void buttonInput();

	MapToolScene();
	~MapToolScene();
};

