#pragma once
#include "gameNode.h"
class MainMenuScene : public gameNode
{
private:

public:
	HRESULT init();
	void release();
	void update();
	void render();

	MainMenuScene();
	~MainMenuScene();
};

