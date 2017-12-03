#include "stdafx.h"
#include "MainMenuScene.h"


MainMenuScene::MainMenuScene()
{
}


MainMenuScene::~MainMenuScene()
{
}

HRESULT MainMenuScene::init()
{
	gameStart = RectMakeCenter(250,470, 96, 96);
	mapTool = RectMakeCenter(550,470,96,96);
	IMAGEMANAGER->addImage("maneMenuBg", "Img//Etc//mainbg.bmp", 800, 600,true,RGB(255,0,255));
	IMAGEMANAGER->addImage("gamestartButton", "Img//Etc//gamestart.bmp", gameStart.right - gameStart.left, gameStart.bottom - gameStart.top, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("mapToolButton", "Img//Etc//mt.bmp", mapTool.right - mapTool.left, mapTool.bottom - mapTool.top, true, RGB(255, 0, 255));
	
	SOUNDMANAGER->play("46.main",1.0);

	return S_OK;
}
void MainMenuScene::release()
{
	SOUNDMANAGER->stop("46.main");
}
void MainMenuScene::update() 
{
	//test~

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&gameStart, _ptMouse))
		{
			SCENEMANAGER->changeScene("°ÔÀÓ¾À");
		}
		else if (PtInRect(&mapTool, _ptMouse))
		{
			SCENEMANAGER->changeScene("¸ÊÅø¾À");
		}
	}
	//~test
}
void MainMenuScene::render() 
{
	IMAGEMANAGER->render("maneMenuBg",getMemDC(),0,0);
	IMAGEMANAGER->alphaRender("gamestartButton", getMemDC(), gameStart.left, gameStart.top,255);
	IMAGEMANAGER->alphaRender("mapToolButton", getMemDC(), mapTool.left, mapTool.top,255);
}