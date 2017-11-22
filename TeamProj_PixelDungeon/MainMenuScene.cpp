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


	return S_OK;
}
void MainMenuScene::release()
{

}
void MainMenuScene::update() 
{
	//test~
	RECT temp1 = RectMake(50, 50, 100, 100);
	RECT temp2 = RectMake(160, 50, 100, 100);
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&temp1, _ptMouse))
		{
			SCENEMANAGER->changeScene("°ÔÀÓ¾À");
		}
		else if (PtInRect(&temp2, _ptMouse))
		{
			SCENEMANAGER->changeScene("¸ÊÅø¾À");
		}
	}
	//~test
}
void MainMenuScene::render() 
{
	//test~
	Rectangle(getMemDC(), 50, 50, 150, 150);
	Rectangle(getMemDC(), 160, 50, 260, 150);
	//~test
}