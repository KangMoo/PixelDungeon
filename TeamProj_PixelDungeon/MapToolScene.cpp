#include "stdafx.h"
#include "MapToolScene.h"


MapToolScene::MapToolScene()
{
}


MapToolScene::~MapToolScene()
{
}
HRESULT MapToolScene::init()
{
	IMAGEMANAGER->addFrameImage("mapTiles", "tile.bmp", 0, 0, 512, 288, 16, 9, true, RGB(255, 0, 255));




	_homeButton = RectMake(WINSIZEX - 120, WINSIZEY - 60, WINSIZEX - 20, WINSIZEY - 20);

	return S_OK;
}
void MapToolScene::release()
{

}
void MapToolScene::update()	
{




}



void MapToolScene::buttonInput()
{




	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&_homeButton, _ptMouse))
		{
			SCENEMANAGER->changeScene("∏ﬁ¿Œ∏ﬁ¥∫æ¿");
		}
	}
}


void MapToolScene::render()	
{
	int rangeX = WINSIZEX / TILESIZE - 3;
	int rangeY = WINSIZEY / TILESIZE;

	for (int i = 1; i <= rangeX; i++) {
		MoveToEx(getMemDC(), i * TILESIZE, TILESIZE ,NULL);
		LineTo(getMemDC(), i * TILESIZE, rangeY * TILESIZE);
	}
	for (int i = 1; i <= rangeY; i++) {
		MoveToEx(getMemDC(), TILESIZE, i * TILESIZE, NULL);
		LineTo(getMemDC(), rangeX * TILESIZE, i * TILESIZE);
	}




	Rectangle(getMemDC(), _homeButton.left, _homeButton.top, _homeButton.right, _homeButton.bottom);

	//test~
	TextOut(getMemDC(), WINSIZEX - 50, 5, "∏ ≈¯æ¿", strlen("∏ ≈¯æ¿"));
	TextOut(getMemDC(), WINSIZEX - 70, WINSIZEY - 25, "µπæ∆∞°±‚", strlen("µπæ∆∞°±‚"));
	//~test
}