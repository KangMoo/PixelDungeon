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
	_selectInterface = 0;

	_camera = _player->getPoint();

	_status_pane_pos = { 0,0 };
	IMAGEMANAGER->addImage("status_pane", "Img/UI/status_pane.bmp", 256, 128, true, RGB(255, 0, 255));

	//avatars
	IMAGEMANAGER->addFrameImage("avatars", "Img/UI/avatars.bmp", 96, 32, 4, 1, true, RGB(255, 0, 255));

	//toolbar
	IMAGEMANAGER->addImage("toolbar", "Img/UI/toolbar.bmp", 304, 52, true, RGB(255, 0, 255));

	//menu_button
	IMAGEMANAGER->addImage("menu_button", "Img/UI/menu_button.bmp", 90, 30, true, RGB(255, 0, 255));

	//BackPack
	IMAGEMANAGER->addImage("backpack", "Img/UI/backpack.bmp", 620, 500, true, RGB(255, 0, 255));

	//BackPack
	IMAGEMANAGER->addImage("backpack", "Img/UI/backpack.bmp", 620, 500, true, RGB(255, 0, 255));

	//inventorytile
	IMAGEMANAGER->addImage("inventorytile", "Img/UI/inventorytile.bmp", 90, 90, true, RGB(255, 0, 255));

	//itemList
	IMAGEMANAGER->addFrameImage("itemList", "Img/UI/itemList.bmp", 540, 540, 6, 6, true, RGB(255, 0, 255));

	_backPack = RectMake(423, WINSIZEY - IMAGEMANAGER->findImage("toolbar")->getFrameHeight(), 48, WINSIZEY - IMAGEMANAGER->findImage("toolbar")->getFrameHeight());

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
	draw(_camera);
}

void UI::draw(POINT camera)
{
	IMAGEMANAGER->render("status_pane", getMemDC(), _status_pane_pos.x, _status_pane_pos.y);
	IMAGEMANAGER->render("toolbar", getMemDC(), WINSIZEX / 2 - (IMAGEMANAGER->findImage("toolbar")->getFrameWidth() / 2), WINSIZEY - (IMAGEMANAGER->findImage("toolbar")->getFrameHeight()));

	IMAGEMANAGER->frameRender("avatars", getMemDC()
		, _status_pane_pos.x + 30 - (IMAGEMANAGER->findImage("avatars")->getFrameWidth() / 2)
		, _status_pane_pos.y + 31 - (IMAGEMANAGER->findImage("avatars")->getFrameHeight() / 2), 0, 0);

	IMAGEMANAGER->frameRender("menu_button", getMemDC()
		, WINSIZEX - (IMAGEMANAGER->findImage("menu_button")->getFrameWidth())
		, 0, 0, 0);

	//Rectangle(getMemDC(), 423, WINSIZEY - IMAGEMANAGER->findImage("toolbar")->getFrameHeight(), 423 + 48, (WINSIZEY - IMAGEMANAGER->findImage("toolbar")->getFrameHeight()) + 52);

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&_backPack, _ptMouse) && _selectInterface == INTERFACEMENU_NULL)
		{
			_selectInterface = INTERFACEMENU_BACKPACK;
		}

		else if (PtInRect(&_backPack, _ptMouse) && _selectInterface == INTERFACEMENU_BACKPACK)
		{
			_selectInterface = INTERFACEMENU_NULL;
		}
	}

	switch (_selectInterface)
	{
		case INTERFACEMENU_BACKPACK:
			BackPack();
			break;

		default:
			break;
	}

	//IMAGEMANAGER->findImage("status_pane")->render(getMemDC(), _status_pane_pos.x, _status_pane_pos.y); //고인
}

void UI::BackPack()
{
	IMAGEMANAGER->render("backpack", getMemDC(), WINSIZEX / 2 - (IMAGEMANAGER->findImage("backpack")->getFrameWidth() / 2), WINSIZEY / 2 - (IMAGEMANAGER->findImage("backpack")->getFrameHeight() / 2));

	for (size_t inventoryY = 0; inventoryY < 4; inventoryY++)
	{
		for (size_t inventoryX = 0; inventoryX < 6; inventoryX++)
		{
			/*테스트 공간*/
			_inventory[0][0].itemNumber = 1;
			_inventory[0][1].itemNumber = 2;
			_inventory[0][2].itemNumber = 3;
			_inventory[0][3].itemNumber = 4;
			/*테스트 공간*/

			int _ix = ((WINSIZEX / 2 - (IMAGEMANAGER->findImage("backpack")->getFrameWidth() / 2)) + 35 ) + inventoryX * 92;
			int _iy = ((WINSIZEX / 2 - (IMAGEMANAGER->findImage("backpack")->getFrameWidth() / 2)) + 30 ) + inventoryY * 92;

			_inventory[inventoryY][inventoryX].inventoryRect = RectMake(_ix, _iy, 90, 90);
			Rectangle(getMemDC(), _ix, _iy, _ix + 90, _iy + 90);

			HBRUSH brush;

			if (inventoryX < 4 && inventoryY == 0)
			{
				brush = CreateSolidBrush(RGB(108, 112, 107));
			}

			else
			{
				brush = CreateSolidBrush(RGB(74, 76, 67));
			}

			FillRect(getMemDC(), &_inventory[inventoryY][inventoryX].inventoryRect, brush);
			DeleteObject(brush);

			if (GetAsyncKeyState(VK_LBUTTON) && PtInRect(&_inventory[inventoryY][inventoryX].inventoryRect, _ptMouse) && _selectItem == ITEMLIST_NULL)
			{
				//_selectItem = ITEMLIST_TESTITEM;
				IMAGEMANAGER->render("inventorytile", getMemDC(), _inventory[inventoryY][inventoryX].inventoryRect.left, _inventory[inventoryY][inventoryX].inventoryRect.top);
			}

			switch (_inventory[inventoryY][inventoryX].itemNumber)
			{
				case ITEMLIST_TESTITEM1:
					IMAGEMANAGER->frameRender("itemList", getMemDC(), _ix, _iy ,0 ,0);
					break;

				case ITEMLIST_TESTITEM2:
					IMAGEMANAGER->frameRender("itemList", getMemDC(), _ix, _iy, 1, 0);
					break;

				case ITEMLIST_TESTITEM3:
					IMAGEMANAGER->frameRender("itemList", getMemDC(), _ix, _iy, 2, 0);
					break;

				case ITEMLIST_TESTITEM4:
					IMAGEMANAGER->frameRender("itemList", getMemDC(), _ix, _iy, 3, 0);
					break;

				default:
					break;
			}
		}
	}

	//switch (_selectItem)
	//{
	//	case ITEMLIST_TESTITEM:
	//		TestFunctin();
	//	default:
	//		break;
	//}
}

/*test
void UI::TestFunctin()
{
	
}
*/