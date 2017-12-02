#pragma once
#include "gameNode.h"
class MainMenuScene : public gameNode
{
private:
	RECT gameStart;
	RECT mapTool;
public:
	HRESULT init();
	void release();
	void update();
	void render();

	MainMenuScene();
	~MainMenuScene();
};

