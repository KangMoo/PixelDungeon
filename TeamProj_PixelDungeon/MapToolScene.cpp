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
	_paletteImg = IMAGEMANAGER->addFrameImage("mapTiles", "Img/Map/tile.bmp", 0, 0, 512, 288, 16, 9, true, RGB(255, 0, 255));

	//Ä«¸Þ¶ó
	_cameraX = _cameraY = 0;

	//¸Ê rect
	for (int i = 0; i < GRIDNUM; i++) {
		int x = (i % GRIDX + 1) * TILESIZE;
		int y = (i / GRIDX + 1) * TILESIZE;
		_mapRect[i].rc = RectMake(x, y, TILESIZE, TILESIZE);
	}
	
	int palPosX = _mapRect[GRIDY].rc.right;
	int palPosY = _mapRect[GRIDY].rc.top;
	
	//ÆÈ·¹Æ® rect
	for (int i = 0; i < PALETTENUM; i++) {
		int x = (i % PALETTEX);
		int y = (i / PALETTEX);
		_paletRect[i].x = x;
		_paletRect[i].y = y;
		_paletRect[i].rc = RectMake((x + 2) * TILESIZE + palPosX, y * TILESIZE + palPosY, TILESIZE, TILESIZE);
	}



	//¹öÆ°
	_buttonRect[0] = RectMake(WINSIZEX - 85, WINSIZEY - 40, WINSIZEX - 20, WINSIZEY - 20);
	
	paletteSetup();
	return S_OK;
}
void MapToolScene::release()
{

}

void MapToolScene::paletteSetup()
{
	for (int i = 0; i < _paletteImg->getMaxFrameY();  i++) {
		for (int j = 0; j < _paletteImg->getMaxFrameX(); j++) {
			tagTile palTile;
			palTile.img = _paletteImg;
			palTile.sourX = j;
			palTile.sourY = i;

			palTile.destX = (j + i * _paletteImg->getMaxFrameX()) % PALETTEX;
			palTile.destY = (j + i * _paletteImg->getMaxFrameX()) / PALETTEX;
			_paletTile.push_back(palTile);
		}		
	}


}


void MapToolScene::update()	
{
	
	buttonInput();
}



void MapToolScene::buttonInput()
{
	


	for (int i = 0; i < GRIDNUM; i++) {
		if (PtInRect(&_mapRect[i].rc, _ptMouse)) {
		
		//	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON) && _mapSelected.size != 0) {
		//		if (_sele 
		//	}

			if (KEYMANAGER->isStayKeyDown(VK_LCONTROL) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
				_mapSelected.push_back(_mapRect[i]);
				break;
			}
			
			else if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
				_mapSelected.clear();
				_mapSelected.push_back(_mapRect[i]);
				break;
			}

					
		}		
	}

	for (int i = 0; i < PALETTENUM; i++) {
		if (PtInRect(&_paletRect[i].rc, _ptMouse)) {
			if (KEYMANAGER->isStayKeyDown(VK_LCONTROL) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
				_paletSelected.push_back(_paletRect[i]);
				break;
			}

			else if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
				_paletSelected.clear();
				_paletSelected.push_back(_paletRect[i]);
				break;
			}

		}
	}

	for (int i = 0; i < BUTTONNUM; i++) {
		if (PtInRect(&_buttonRect[i], _ptMouse))
		{
			if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
			{
				SCENEMANAGER->changeScene("¸ÞÀÎ¸Þ´º¾À");				
			}
		}
	}
}


void MapToolScene::render()	
{	
	for (int i = 0; i < GRIDNUM; i++) {
		Rectangle(getMemDC(), _mapRect[i].rc.left, _mapRect[i].rc.top, _mapRect[i].rc.right, _mapRect[i].rc.bottom);
	}
	for (int i = 0; i < PALETTENUM; i++) {
		Rectangle(getMemDC(), _paletRect[i].rc.left, _paletRect[i].rc.top, _paletRect[i].rc.right, _paletRect[i].rc.bottom);
	}

	

	for (int i = 0; i < PALETTENUM; i++) {
		if (i >= _paletTile.size()) break;
		
		int destX = _paletRect[_paletTile[i].destX + _paletTile[i].destY * PALETTEX].rc.left;
		int destY = _paletRect[_paletTile[i].destX + _paletTile[i].destY * PALETTEX].rc.top;

		_paletTile[i].img->frameRender(getMemDC(), destX, destY, _paletTile[i].sourX, _paletTile[i].sourY);
	}


	for (int i = 0; i < _mapSelected.size(); i++) {
		HBRUSH color = CreateSolidBrush(RGB(0, 0, 255));
		FillRect(getMemDC(), &_mapSelected[i].rc, color);	
	}
	
	for (int i = 0; i < _paletSelected.size(); i++) {
		HBRUSH color = CreateSolidBrush(RGB(255, 0, 255));
		FillRect(getMemDC(), &_paletSelected[i].rc, color);
	}

	for (int i = 0; i < BUTTONNUM; i++){
		Rectangle(getMemDC(), _buttonRect[i].left, _buttonRect[i].top, _buttonRect[i].right, _buttonRect[i].bottom);
	}
	//test~
	TextOut(getMemDC(), WINSIZEX - 50, 5, "¸ÊÅø¾À", strlen("¸ÊÅø¾À"));
	TextOut(getMemDC(), WINSIZEX - 70, WINSIZEY - 25, "µ¹¾Æ°¡±â", strlen("µ¹¾Æ°¡±â"));
	//~test
}