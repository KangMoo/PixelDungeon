#include "stdafx.h"
#include "UI.h"
#include "Player.h"
#include "EnemyManager.h"
#include "Map.h"

UI::UI()
{
}


UI::~UI()
{
}

HRESULT UI::init()
{
	_camera = _player->getPoint();
	return S_OK;
}
void UI::release()
{

}
void UI::update()
{

}
void UI::render(POINT camera)
{
}
void UI::draw(POINT camera)
{
}