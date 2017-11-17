#include "stdafx.h"
#include "Item.h"


Item::Item()
{
}


Item::~Item()
{

}

HRESULT Item::init()			
{

	return S_OK;
}
void Item::release()			
{

}
void Item::update()				
{

}
void Item::render(POINT camera)	
{
	draw(camera);
}
void Item::draw(POINT camera)	
{

}