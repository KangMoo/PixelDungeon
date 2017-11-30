#include "stdafx.h"
#include "mainGame.h"

mainGame::mainGame()
{
}


mainGame::~mainGame()
{

}


HRESULT mainGame::init(void)
{
	gameNode::init(true);
	
	IMAGEMANAGER->addFrameImage("mapTiles", "Img/Map/tiles_sewers.bmp", 0, 0, 512, 512, 16, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("chest", "Img/Map/chest.bmp", 0, 0, 32, 32, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("water", "Img/Map/water0.bmp", 0, 0, 32, 32, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("trap", "Img/Map/trap.bmp", 0, 0, 512, 256, 16, 8, true, RGB(255, 0, 255));

	SCENEMANAGER->addScene("게임씬", new GameScene);
	SCENEMANAGER->addScene("메인메뉴씬", new MainMenuScene);
	SCENEMANAGER->addScene("맵툴씬", new MapToolScene);
	SCENEMANAGER->changeScene("메인메뉴씬");
	return S_OK;
}

void mainGame::release(void)
{
	
}


void mainGame::update(void)	
{
	gameNode::update();

	SCENEMANAGER->update();

}


void mainGame::render(void)	
{
	//흰색 도화지 한 장 필요
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==============================================================

	SCENEMANAGER->render();
	
	
	//========================================================================
	//백버퍼에 있는걸 HDC로 그려주는 역할
	this->getBackBuffer()->render(getHDC(), 0, 0);

}