#pragma once
#include "gameNode.h"
#include "GameScene.h"
#include "MainMenuScene.h"
#include "MapToolScene.h"

class mainGame : public gameNode
{
private:

public:
	virtual HRESULT init(void);	
	virtual void release(void);	
	virtual void update(void);	
	virtual void render(void);	

	
	mainGame();
	~mainGame();
};

