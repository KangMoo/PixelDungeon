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

	return S_OK;
}
void MapToolScene::release()
{

}
void MapToolScene::update()	
{

}
void MapToolScene::render()	
{
	//test~
	TextOut(getMemDC(), 100, 100, "¸ÊÅø¾À", strlen("¸ÊÅø¾À"));
	//~test
}