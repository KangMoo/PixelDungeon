#include "stdafx.h"
#include "UI.h"
#include "Player.h"
#include "EnemyManager.h"
#include "Map.h"
#include "ItemManager.h"

UI::UI()
{

}

UI::~UI()
{

}

HRESULT UI::init()
{

	_camera = _player->getPoint();

	IMAGEMANAGER->addImage("status_pane", "Img/UI/status_pane.bmp", 384, 192, true, RGB(255, 0, 255));

	//avatars
	IMAGEMANAGER->addFrameImage("avatars", "Img/UI/avatars.bmp", 144, 48, 4, 1, true, RGB(255, 0, 255));

	//toolbar
	IMAGEMANAGER->addImage("toolbar", "Img/UI/toolbar.bmp", 456, 78, true, RGB(255, 0, 255));

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

	//틀만들기 테스트
	IMAGEMANAGER->addFrameImage("fream_window1", "Img/UI/fream_window1.bmp", 60, 60, 4, 4, true, RGB(255, 0, 255));

	//선택창
	IMAGEMANAGER->addFrameImage("select_menu_bar", "Img/UI/select_menu_bar.bmp", 130, 430, 1, 10, true, RGB(255, 0, 255));

	//타겟 버튼
	IMAGEMANAGER->addImage("Target_button", "Img/UI/Target_button.bmp", 70, 75, true, RGB(255, 0, 255));

	//스페셜 버튼
	IMAGEMANAGER->addImage("Special_Button", "Img/UI/Special_Button.bmp", 70, 75, true, RGB(255, 0, 255));

	//몬스터 표시
	IMAGEMANAGER->addImage("Monster_Display", "Img/UI/Monster_Display.bmp", 70, 48, true, RGB(255, 0, 255));

	//hp바
	IMAGEMANAGER->addImage("hp_bar", "Img/UI/hp_bar.bmp", 192, 12, true, RGB(255, 0, 255));

	//메인메뉴바
	IMAGEMANAGER->addImage("select_menu_bar2", "Img/UI/select_menu_bar2.bmp", 260, 129, true, RGB(255, 0, 255));

	//타일 선택
	IMAGEMANAGER->addImage("tile_select", "Img/UI/tile_select.bmp", 32, 32, true, RGB(255, 0, 255));

	//폰트
	IMAGEMANAGER->addFrameImage("font", "Img/UI/numberfont.bmp", 130, 19, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("font_green", "Img/UI/numberfontgreen.bmp", 130, 19, 10, 1, true, RGB(255, 0, 255)); //그린
	IMAGEMANAGER->addFrameImage("special_font", "Img/UI/specialfont.bmp", 36, 19, 3, 1, true, RGB(255, 0, 255)); //특수문자

	_backPackRect = RectMake(437, WINSIZEY - IMAGEMANAGER->findImage("toolbar")->getFrameHeight(), 72, (WINSIZEY - IMAGEMANAGER->findImage("toolbar")->getFrameHeight()));
	_SearchOptionRect = RectMake(567.5, WINSIZEY - IMAGEMANAGER->findImage("toolbar")->getFrameHeight(), 567.5, (WINSIZEY - IMAGEMANAGER->findImage("toolbar")->getFrameHeight()));
	_TurnSkipRect = RectMake(509, WINSIZEY - IMAGEMANAGER->findImage("toolbar")->getFrameHeight(), 58.5, (WINSIZEY - IMAGEMANAGER->findImage("toolbar")->getFrameHeight()));

	_Monster_DisplyRect = RectMake(WINSIZEX - IMAGEMANAGER->findImage("Monster_Display")->getFrameWidth(), 40, IMAGEMANAGER->findImage("Monster_Display")->getFrameWidth(), IMAGEMANAGER->findImage("Monster_Display")->getFrameHeight());
	_Special_ButtonRect = RectMake(WINSIZEX - IMAGEMANAGER->findImage("Special_Button")->getFrameWidth(), 380, IMAGEMANAGER->findImage("Special_Button")->getFrameWidth(), IMAGEMANAGER->findImage("Special_Button")->getFrameHeight());
	_Target_ButtonRect = RectMake(WINSIZEX - IMAGEMANAGER->findImage("Target_button")->getFrameWidth(), 460, IMAGEMANAGER->findImage("Target_button")->getFrameWidth(), IMAGEMANAGER->findImage("Target_button")->getFrameHeight());

	_Menu_selectRect = RectMake((WINSIZEX - IMAGEMANAGER->findImage("menu_button")->getFrameWidth()) + 60, 0, 30, IMAGEMANAGER->findImage("menu_button")->getFrameHeight());
	_StatusRect = RectMake(5, 5, 85, 88);

	_interface_button_timer1 = TIMEMANAGER->getWorldTime();
	_interface_button_timer2 = TIMEMANAGER->getWorldTime();
	_interface_button_timer3 = TIMEMANAGER->getWorldTime();

	_uitimer = TIMEMANAGER->getWorldTime();

	_Menu_WindowRect[GAMEMENU_SET] = RectMake(278, 242, 260, 45);
	_Menu_WindowRect[GAMEMENU_MAIN] = RectMake(278, 287, 130, 45);
	_Menu_WindowRect[GAMEMENU_EXIT] = RectMake(408, 287, 130, 45);
	_Menu_WindowRect[GAMEMENU_BACK] = RectMake(278, 332, 260, 45);

	return S_OK;
}

void UI::release()
{

}

void UI::update()
{
	cameraSet();
}


void UI::render(POINT camera)
{
	draw(_camera);

	TIMEMANAGER->render(getMemDC());
}

void UI::draw(POINT camera)
{
	if (!_player->getUsingUI())
	{
		_uitimer = TIMEMANAGER->getWorldTime();
	}

	IMAGEMANAGER->render("status_pane", getMemDC(), 0, 0);
	IMAGEMANAGER->render("hp_bar", getMemDC(), 90, 9);

	IMAGEMANAGER->render("toolbar", getMemDC(), WINSIZEX / 2 - (IMAGEMANAGER->findImage("toolbar")->getFrameWidth() / 2), WINSIZEY - (IMAGEMANAGER->findImage("toolbar")->getFrameHeight()));

	//Rectangle(getMemDC(), 437, WINSIZEY - IMAGEMANAGER->findImage("toolbar")->getFrameHeight(), 437 + 72, (WINSIZEY - IMAGEMANAGER->findImage("toolbar")->getFrameHeight()) + 78);
	//Rectangle(getMemDC(), 509, WINSIZEY - IMAGEMANAGER->findImage("toolbar")->getFrameHeight(), 509 + (float)58.5, (WINSIZEY - IMAGEMANAGER->findImage("toolbar")->getFrameHeight()) + 78);
	//Rectangle(getMemDC(), 567.5, WINSIZEY - IMAGEMANAGER->findImage("toolbar")->getFrameHeight(), 567.5 + (float)58.5, (WINSIZEY - IMAGEMANAGER->findImage("toolbar")->getFrameHeight()) + 78);

	IMAGEMANAGER->frameRender("avatars", getMemDC()
		, 45 - (IMAGEMANAGER->findImage("avatars")->getFrameWidth() / 2)
		, (float)46.5 - (IMAGEMANAGER->findImage("avatars")->getFrameHeight() / 2), 0, 0);

	IMAGEMANAGER->frameRender("menu_button", getMemDC()
		, WINSIZEX - (IMAGEMANAGER->findImage("menu_button")->getFrameWidth())
		, 0, 0, 0);

	//Rectangle(getMemDC(), WINSIZEX - IMAGEMANAGER->findImage("menu_button")->getFrameWidth(), 0, (WINSIZEX - IMAGEMANAGER->findImage("menu_button")->getFrameWidth()) + 30, IMAGEMANAGER->findImage("menu_button")->getFrameHeight());
	//Rectangle(getMemDC(), (WINSIZEX - IMAGEMANAGER->findImage("menu_button")->getFrameWidth()) + 30, 0, ((WINSIZEX - IMAGEMANAGER->findImage("menu_button")->getFrameWidth()) + 30) + 30, IMAGEMANAGER->findImage("menu_button")->getFrameHeight());
	//Rectangle(getMemDC(), (WINSIZEX - IMAGEMANAGER->findImage("menu_button")->getFrameWidth()) + 60, 0, ((WINSIZEX - IMAGEMANAGER->findImage("menu_button")->getFrameWidth()) + 60) + 30, IMAGEMANAGER->findImage("menu_button")->getFrameHeight());

	//if (/*몬스터가 근처에 있을시에 표시*/)
	IMAGEMANAGER->render("Monster_Display", getMemDC(), WINSIZEX - IMAGEMANAGER->findImage("Monster_Display")->getFrameWidth(), 40);
	//Rectangle(getMemDC(), WINSIZEX - IMAGEMANAGER->findImage("Monster_Display")->getFrameWidth(), 40, (WINSIZEX - IMAGEMANAGER->findImage("Monster_Display")->getFrameWidth()) + IMAGEMANAGER->findImage("Monster_Display")->getFrameWidth(), 40 + IMAGEMANAGER->findImage("Monster_Display")->getFrameHeight());

//if (/*플레이어가 특수 아이템을 소지하고 있을시*/)
	IMAGEMANAGER->render("Special_Button", getMemDC(), WINSIZEX - IMAGEMANAGER->findImage("Special_Button")->getFrameWidth(), 380);
	//Rectangle(getMemDC(), WINSIZEX - IMAGEMANAGER->findImage("Special_Button")->getFrameWidth(), 380, (WINSIZEX - IMAGEMANAGER->findImage("Special_Button")->getFrameWidth()) + IMAGEMANAGER->findImage("Special_Button")->getFrameWidth(), 380 + IMAGEMANAGER->findImage("Special_Button")->getFrameHeight());

//if (/*몬스터가 근처에 있을시*/)
	IMAGEMANAGER->render("Target_button", getMemDC(), WINSIZEX - IMAGEMANAGER->findImage("Target_button")->getFrameWidth(), 460);
	//Rectangle(getMemDC(), WINSIZEX - IMAGEMANAGER->findImage("Target_button")->getFrameWidth(), 460, (WINSIZEX - IMAGEMANAGER->findImage("Target_button")->getFrameWidth()) + IMAGEMANAGER->findImage("Target_button")->getFrameWidth(), 460 + IMAGEMANAGER->findImage("Target_button")->getFrameHeight());


//Rectangle(getMemDC(), 5, 5, 85,88);



	//
	//if (KEYMANAGER->isStayKeyDown(VK_LBUTTON) && (TIMEMANAGER->getWorldTime() - _interface_button_timer1) > 0.3 && _selectInterface == INTERFACEMENU_END && !_player->getIsPlayerMoving())
	//{
	//	//배낭
	//	if (PtInRect(&_backPackRect, _ptMouse) && _selectInterface == INTERFACEMENU_END)
	//	{
	//		_selectInterface = INTERFACEMENU_BACKPACK;
	//		_player->setUsingUI(true);
	//
	//		ResetInventory();
	//
	//		for (int i = 0; i < 10; i++)
	//			SortInventory();
	//	}
	//
	//	//탐색
	//	else if (PtInRect(&_SearchOptionRect, _ptMouse) && _selectInterface == INTERFACEMENU_END)
	//	{
	//		if (_player->getAction() == true)
	//		{
	//			_player->endTurn();
	//		}
	//
	//		//_selectInterface = INTERFACEMENU_TURNSKIP;
	//	}
	//
	//	//턴스킵
	//	else if (PtInRect(&_TurnSkipRect, _ptMouse) && _selectInterface == INTERFACEMENU_END)
	//	{
	//		_selectInterface = INTERFACEMENU_SEARCH;
	//	}
	//
	//	else if (PtInRect(&_Menu_selectRect, _ptMouse) && _selectInterface != INTERFACEMENU_MENU)
	//	{
	//		_selectInterface = INTERFACEMENU_MENU;
	//	}
	//
	//	else if (PtInRect(&_StatusRect, _ptMouse) && _selectInterface == INTERFACEMENU_END)
	//	{
	//		_selectInterface = INTERFACEMENU_STATUS;
	//	}
	//
	//	_interface_button_timer1 = TIMEMANAGER->getWorldTime();
	//}
	//
	//else if (KEYMANAGER->isStayKeyDown(VK_LBUTTON) && (TIMEMANAGER->getWorldTime() - _interface_button_timer1) > 0.3 && _selectInterface != INTERFACEMENU_END && !_player->getIsPlayerMoving())
	//{
	//	if (PtInRect(&_backPackRect, _ptMouse) || PtInRect(&_SearchOptionRect, _ptMouse) || PtInRect(&_TurnSkipRect, _ptMouse) || PtInRect(&_Menu_selectRect, _ptMouse) || PtInRect(&_StatusRect, _ptMouse))
	//	{
	//		_selectInterface = INTERFACEMENU_END;
	//		//_player->setUsingUI(false);
	//
	//		usingui();
	//	}
	//
	//	_interface_button_timer1 = TIMEMANAGER->getWorldTime();
	//}

	switch (_selectInterface)
	{
		//배낭
	case INTERFACEMENU_BACKPACK:
		BackPack();
		break;

		//턴스킵
	case INTERFACEMENU_TURNSKIP:
		break;

		//탐색
	case INTERFACEMENU_SEARCH:
		search();
		break;

		//메뉴창
	case INTERFACEMENU_MENU:
		main_menu();
		break;

		//스테이터스 창
	case INTERFACEMENU_STATUS:
		status_window();
		break;
	}

	if (throwcheck)
		throw_interface();

	if (isscroll == true)
		read_interface();

	//IMAGEMANAGER->findImage("status_pane")->render(getMemDC(), _status_pane_pos.x, _status_pane_pos.y); //고인
	//TIMEMANAGER->render(getMemDC());
}

void UI::main_menu()
{
	fream_window_draw(19, 10);
	IMAGEMANAGER->render("select_menu_bar2", getMemDC(), ((WINSIZEX / 2) - (IMAGEMANAGER->findImage("select_menu_bar2")->getWidth() / 2)) + 8, ((WINSIZEY / 2) - (IMAGEMANAGER->findImage("select_menu_bar2")->getHeight() / 2)) + 7);

	//Rectangle(getMemDC(), 278, 242, 538, 287);
	//Rectangle(getMemDC(), 278, 287, 408, 329);
	//Rectangle(getMemDC(), 408, 287, 538, 329);
	//Rectangle(getMemDC(), 278, 329, 538, 372);

//	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON) && (TIMEMANAGER->getWorldTime() - _interface_button_timer1) > 0.3 && _selectMenu == GAMEMENU_END && !_player->getIsPlayerMoving())
//	{
//		for (int MenuNumber = 0; MenuNumber < GAMEMENU_END; MenuNumber++)
//		{
//			if (PtInRect(&_Menu_WindowRect[MenuNumber], _ptMouse) && _selectMenu == GAMEMENU_END)
//			{
//				_selectMenu = MenuNumber;
//			}
//		}
//
//		_interface_button_timer1 = TIMEMANAGER->getWorldTime();
//	}

	switch (_selectMenu)
	{
	case GAMEMENU_SET:
		_selectInterface = INTERFACEMENU_END;
		_selectMenu = GAMEMENU_END;
		break;

	case GAMEMENU_MAIN:
		_selectInterface = INTERFACEMENU_END;
		_selectMenu = GAMEMENU_END;
		SCENEMANAGER->changeScene("메인메뉴씬");
		break;

	case GAMEMENU_EXIT:
		_selectInterface = INTERFACEMENU_END;
		_selectMenu = GAMEMENU_END;
		exit(0);
		break;

	case GAMEMENU_BACK:
		_selectInterface = INTERFACEMENU_END;
		_selectMenu = GAMEMENU_END;
		break;

	default:
		break;
	}

}

void UI::status_window()
{
	fream_window_draw(18, 20);

	IMAGEMANAGER->frameRender("avatars", getMemDC(), 300, 180, 0, 0);

	char name[] = "레벨 몇의 전사";
	PrintFont(name, namehFont, nameoldFont, 350, 190, 25, 0, 255, 0);

	char str[] = "힘";
	PrintFont(str, namehFont, nameoldFont, 300, 250, 18, 255, 255, 255);

	char health[] = "체력";
	PrintFont(health, namehFont, nameoldFont, 300, 280, 18, 255, 255, 255);

	char ex[] = "경험치";
	PrintFont(ex, namehFont, nameoldFont, 300, 310, 18, 255, 255, 255);

	char gold[] = "획득한 골드";
	PrintFont(gold, namehFont, nameoldFont, 300, 380, 18, 255, 255, 255);

	char level[] = "최고 레벨";
	PrintFont(level, namehFont, nameoldFont, 300, 410, 18, 255, 255, 255);
}

void UI::search()
{
	fream_window_draw(18, 4, 0, 170);

	char name[] = "탐색 지역을 선택하시오";
	PrintFont(name, namehFont, nameoldFont, 290, 468, 18, 0, 255, 0);
}

void UI::usingui()
{
	if ((TIMEMANAGER->getWorldTime() - _uitimer) > 1 && _player->getUsingUI())
	{
		_player->setUsingUI(false);

		_uitimer = TIMEMANAGER->getWorldTime();
	}
}

void UI::throw_interface()
{
	IMAGEMANAGER->alphaRender("tile_select", getMemDC(), (_ptMouse.x / TILESIZE) * TILESIZE, (_ptMouse.y/TILESIZE)*TILESIZE , 60);

	if (isthrow)
	{
		fream_window_draw(18, 4, 0, 170);
		char name[] = "던질 지역을 선택하시오";
		PrintFont(name, namehFont, nameoldFont, 290, 468, 18, 0, 255, 0);
	}

	if (islaunch)
	{
		fream_window_draw(19, 4, 0, 170);
		char name[] = "발사할 지역을 선택하시오";
		PrintFont(name, namehFont, nameoldFont, 280, 468, 18, 0, 255, 0);
	}

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON) && (TIMEMANAGER->getWorldTime() - _interface_button_timer2) > 0.3)
	{
		int equipnumber = 0;

		for (int check = 0; check < (_itemPosition - 4); check++)
		{
			if (_im->getvBag()[check].equip == true)
			{
				equipnumber++;
			}
		}

		_inventory[_itemPosition].itemNumber = NAME_END;

		if (isthrow)
			_im->throwItem(_itemPosition - 4, _ptMouse.x - _camera.x, _ptMouse.y - _camera.y);

		if (islaunch)
			_im->fire(_im->getvBag()[_itemPosition - 4].throwImg, _ptMouse.x - _camera.x, _ptMouse.y - _camera.y);

		throwcheck = false;
		isthrow = false;
		islaunch = false;
		_interface_button_timer2 = TIMEMANAGER->getWorldTime();
	}
}

void UI::read_interface()
{
	if (isidentity)
	{
		fream_window_draw(19, 4, 0, 170);
		char name[] = "감정할 아이템을 선택하시오";
		PrintFont(name, namehFont, nameoldFont, 280, 468, 18, 0, 255, 0);
	}

	if (isUpgrad)
	{
		fream_window_draw(19, 4, 0, 170);
		char name[] = "강화할 아이템을 선택하시오";
		PrintFont(name, namehFont, nameoldFont, 280, 468, 18, 0, 255, 0);
	}

	if (ispurify)
	{
		fream_window_draw(19, 4, 0, 170);
		char name[] = "정화할 아이템을 선택하시오";
		PrintFont(name, namehFont, nameoldFont, 280, 468, 18, 0, 255, 0);
	}

	for (size_t Line = 0; Line < ARRSIZE; Line++)
	{
		if (PtInRect(&_inventory[Line].inventoryRect, _ptMouse))
		{
			IMAGEMANAGER->alphaRender("inventorytile", getMemDC(), _inventory[Line].inventoryRect.left, _inventory[Line].inventoryRect.top, 80);

			if (KEYMANAGER->isStayKeyDown(VK_LBUTTON) && (TIMEMANAGER->getWorldTime() - _interface_button_timer2) > 0.2)
			{
				int equipnumber = 0;

				for (int check = 0; check < (_itemPosition - 4); check++)
				{
					if (_im->getvBag()[check].equip == true)
					{
						equipnumber++;
					}
				}

				_inventory[_itemPosition].itemNumber = NAME_END;
				_selectInterface = INTERFACEMENU_END;
				_im->useItem(_itemPosition - 4, Line - 4);

				isscroll = false;

				isidentity = false;
				isUpgrad = false;
				ispurify = false;

				_interface_button_timer2 = TIMEMANAGER->getWorldTime();
			}
		}
	}
}

void UI::ResetInventory()
{
	for (size_t i = 0; i < 24; i++)
	{
		if (i < _im->getvBag().size())
		{
			if (_im->getvBag()[i].equip == false)
				_inventory[i + 4].itemNumber = _im->getvBag()[i].name;

			if (_im->getvBag()[i].equip == true)
				_inventory[i + 4].itemNumber = NAME_END;
		}

		else
		{
			_inventory[i + 4].itemNumber = NAME_END;
		}
	}
}

void UI::SortInventory()
{
	for (size_t i = 0; i < _im->getvBag().size(); i++)
	{
		if (_inventory[i + 4].itemNumber == NAME_END)
		{
			for (size_t x = i; x < _im->getvBag().size(); x++)
			{
				int t1tmep = _inventory[x + 4].itemNumber;
				_inventory[x + 4].itemNumber = _inventory[x + 4 + 1].itemNumber;
				_inventory[x + 4 + 1].itemNumber = t1tmep;
			}
		}
	}
}

bool UI::usingInterface()
{
	if (_selectInterface == INTERFACEMENU_END && _selectItem == NAME_END && _selectMenu == GAMEMENU_END)
	{
		return false;

	}
	return true;
}

void UI::BackPack()
{
	IMAGEMANAGER->render("backpack", getMemDC(), WINSIZEX / 2 - (IMAGEMANAGER->findImage("backpack")->getFrameWidth() / 2), WINSIZEY / 2 - (IMAGEMANAGER->findImage("backpack")->getFrameHeight() / 2));

	for (size_t Line = 0; Line < ARRSIZE; Line++)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD1))
		{
			ResetInventory();
		}

		if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD2))
		{
			SortInventory();
		}

		int _ix = ((WINSIZEX / 2 - (IMAGEMANAGER->findImage("backpack")->getFrameWidth() / 2)) + 35) + (Line % 6) * 92;
		int _iy = ((WINSIZEX / 2 - (IMAGEMANAGER->findImage("backpack")->getFrameWidth() / 2)) + 30) + (Line / 6) * 92;
		
		_inventory[Line].inventoryRect = RectMake(_ix, _iy, 90, 90);
		Rectangle(getMemDC(), _ix, _iy, _ix + 90, _iy + 90);

		HBRUSH brush;

		if (Line < 4)
		{
			brush = CreateSolidBrush(RGB(108, 112, 107));
		}

		else
		{
			brush = CreateSolidBrush(RGB(74, 76, 67));
		}

		FillRect(getMemDC(), &_inventory[Line].inventoryRect, brush);
		DeleteObject(brush);

	//	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON) && PtInRect(&_inventory[Line].inventoryRect, _ptMouse) && (TIMEMANAGER->getWorldTime() - _interface_button_timer2) > 0.3 && _selectItem == NAME_END)
	//	{
	//		for (int itemNumber = 0; itemNumber < _im->getvBag().size(); itemNumber++)
	//		{
	//			if (_inventory[Line].itemNumber == _im->getvBag()[itemNumber].name)
	//			{
	//				_selectItem = _im->getvBag()[itemNumber].name;
	//				_itemPosition = Line;
	//			}
	//		}
	//
	//		_interface_button_timer2 = TIMEMANAGER->getWorldTime();
	//	}
	//
		if (GetAsyncKeyState(VK_RBUTTON) && (TIMEMANAGER->getWorldTime() - _interface_button_timer2) > 0.3 && _selectItem != NAME_END)
		{
			_selectItem = NAME_END;
	
			_interface_button_timer2 = TIMEMANAGER->getWorldTime();
		}

		for (size_t i = 0; i < _im->getvBag().size(); i++)
		{
			if (_inventory[Line].itemNumber != NAME_END && _im->getvBag()[i].name == _inventory[Line].itemNumber)
			{
				_im->getvBag()[i].img->render(getMemDC(), _ix + (90 / 2) - (_im->getvBag()[i].img->getFrameWidth() / 2), _iy + (90 / 2) - (_im->getvBag()[i].img->getFrameHeight() / 2));

				//폰트
				if (_im->getvBag()[i].numOfItem > 1 && _im->getvBag()[i].type != TYPE_WEAPON && _im->getvBag()[i].type != TYPE_ARMOR && _im->getvBag()[i].type != TYPE_ACC && _im->getvBag()[i].type != TYPE_WAND)
				{
					IMAGEMANAGER->frameRender("font", getMemDC(), (_ix + (_im->getvBag()[i].img->getFrameWidth() / 2)) - 10, (_iy + (_im->getvBag()[i].img->getFrameHeight() / 2)) - 10, _im->getvBag()[i].numOfItem, 0);
				}

				if (_im->getvBag()[i].name == NAME_BOTTLE)
				{
					if (_im->getvBag()[i].currentCharge < 10)
					{
						IMAGEMANAGER->frameRender("special_font", getMemDC(), (_ix + (_im->getvBag()[i].img->getFrameWidth() / 2)) + 2, (_iy + (_im->getvBag()[i].img->getFrameHeight() / 2)) + 50, 2, 0);
						IMAGEMANAGER->frameRender("font", getMemDC(), (_ix + (_im->getvBag()[i].img->getFrameWidth() / 2)) - 10, (_iy + (_im->getvBag()[i].img->getFrameHeight() / 2)) + 50, _im->getvBag()[i].currentCharge, 0);
						IMAGEMANAGER->frameRender("font", getMemDC(), (_ix + (_im->getvBag()[i].img->getFrameWidth() / 2)) + 14, (_iy + (_im->getvBag()[i].img->getFrameHeight() / 2)) + 50, 2, 0);
						IMAGEMANAGER->frameRender("font", getMemDC(), (_ix + (_im->getvBag()[i].img->getFrameWidth() / 2)) + 26, (_iy + (_im->getvBag()[i].img->getFrameHeight() / 2)) + 50, 0, 0);
					}

					if (_im->getvBag()[i].currentCharge >= 10 && _im->getvBag()[i].currentCharge < 20)
					{
						IMAGEMANAGER->frameRender("special_font", getMemDC(), (_ix + (_im->getvBag()[i].img->getFrameWidth() / 2)) + 14, (_iy + (_im->getvBag()[i].img->getFrameHeight() / 2)) + 50, 2, 0);
						IMAGEMANAGER->frameRender("font", getMemDC(), (_ix + (_im->getvBag()[i].img->getFrameWidth() / 2)) - 10, (_iy + (_im->getvBag()[i].img->getFrameHeight() / 2)) + 50, 1, 0);
						IMAGEMANAGER->frameRender("font", getMemDC(), (_ix + (_im->getvBag()[i].img->getFrameWidth() / 2)) + 2, (_iy + (_im->getvBag()[i].img->getFrameHeight() / 2)) + 50, _im->getvBag()[i].currentCharge - 10, 0);
						IMAGEMANAGER->frameRender("font", getMemDC(), (_ix + (_im->getvBag()[i].img->getFrameWidth() / 2)) + 26, (_iy + (_im->getvBag()[i].img->getFrameHeight() / 2)) + 50, 2, 0);
						IMAGEMANAGER->frameRender("font", getMemDC(), (_ix + (_im->getvBag()[i].img->getFrameWidth() / 2)) + 38, (_iy + (_im->getvBag()[i].img->getFrameHeight() / 2)) + 50, 0, 0);
					}

					if (_im->getvBag()[i].currentCharge == 20)
					{
						IMAGEMANAGER->frameRender("special_font", getMemDC(), (_ix + (_im->getvBag()[i].img->getFrameWidth() / 2)) + 14, (_iy + (_im->getvBag()[i].img->getFrameHeight() / 2)) + 50, 2, 0);
						IMAGEMANAGER->frameRender("font", getMemDC(), (_ix + (_im->getvBag()[i].img->getFrameWidth() / 2)) - 10, (_iy + (_im->getvBag()[i].img->getFrameHeight() / 2)) + 50, 2, 0);
						IMAGEMANAGER->frameRender("font", getMemDC(), (_ix + (_im->getvBag()[i].img->getFrameWidth() / 2)) + 2, (_iy + (_im->getvBag()[i].img->getFrameHeight() / 2)) + 50, 0, 0);
						IMAGEMANAGER->frameRender("font", getMemDC(), (_ix + (_im->getvBag()[i].img->getFrameWidth() / 2)) + 26, (_iy + (_im->getvBag()[i].img->getFrameHeight() / 2)) + 50, 2, 0);
						IMAGEMANAGER->frameRender("font", getMemDC(), (_ix + (_im->getvBag()[i].img->getFrameWidth() / 2)) + 38, (_iy + (_im->getvBag()[i].img->getFrameHeight() / 2)) + 50, 0, 0);
					}
				}

				if (_im->getvBag()[i].type == TYPE_WEAPON || _im->getvBag()[i].type == TYPE_ARMOR || _im->getvBag()[i].type == TYPE_ACC || _im->getvBag()[i].type == TYPE_WAND)
				{
					if (_im->getvBag()[i].upgrade >= 1 && _im->getvBag()[i].upgrade < 10)
					{
						IMAGEMANAGER->frameRender("font_green", getMemDC(), (_ix + (_im->getvBag()[i].img->getFrameWidth() / 2)) + 55, (_iy + (_im->getvBag()[i].img->getFrameHeight() / 2)) + 50, _im->getvBag()[i].upgrade, 0);
					}

					if (_im->getvBag()[i].upgrade >= 10 && _im->getvBag()[i].upgrade < 20)
					{
						IMAGEMANAGER->frameRender("font_green", getMemDC(), (_ix + (_im->getvBag()[i].img->getFrameWidth() / 2)) + 45, (_iy + (_im->getvBag()[i].img->getFrameHeight() / 2)) + 50, 1, 0);
						IMAGEMANAGER->frameRender("font_green", getMemDC(), (_ix + (_im->getvBag()[i].img->getFrameWidth() / 2)) + 55, (_iy + (_im->getvBag()[i].img->getFrameHeight() / 2)) + 50, _im->getvBag()[i].upgrade - 10, 0);
					}
				}

				if (_im->getvBag()[i].type == TYPE_WEAPON || _im->getvBag()[i].type == TYPE_ARMOR || _im->getvBag()[i].type == TYPE_ACC || _im->getvBag()[i].type == TYPE_WAND || _im->getvBag()[i].type == TYPE_THROW)
				{
					if (_im->getvBag()[i].Power < 10)
					{
						IMAGEMANAGER->frameRender("special_font", getMemDC(), (_ix + (_im->getvBag()[i].img->getFrameWidth() / 2)) + 48, (_iy + (_im->getvBag()[i].img->getFrameHeight() / 2)) - 10, 0, 0);
						IMAGEMANAGER->frameRender("font", getMemDC(), (_ix + (_im->getvBag()[i].img->getFrameWidth() / 2)) + 58, (_iy + (_im->getvBag()[i].img->getFrameHeight() / 2)) - 10, _im->getvBag()[i].Power, 0);
					}

					if (_im->getvBag()[i].Power >= 10)
					{
						if (_im->getvBag()[i].Power >= 10 && _im->getvBag()[i].Power < 20)
						{
							IMAGEMANAGER->frameRender("special_font", getMemDC(), (_ix + (_im->getvBag()[i].img->getFrameWidth() / 2)) + 38, (_iy + (_im->getvBag()[i].img->getFrameHeight() / 2)) - 10, 0, 0);
							IMAGEMANAGER->frameRender("font", getMemDC(), (_ix + (_im->getvBag()[i].img->getFrameWidth() / 2)) + 48, (_iy + (_im->getvBag()[i].img->getFrameHeight() / 2)) - 10, 1, 0);
						}

						IMAGEMANAGER->frameRender("font", getMemDC(), (_ix + (_im->getvBag()[i].img->getFrameWidth() / 2)) + 58 , (_iy + (_im->getvBag()[i].img->getFrameHeight() / 2)) - 10, _im->getvBag()[i].Power - 10, 0);
					}
				}
			}
		}
	}

	/*
	NAME_OLD_SHORT_SWORD,	//낡은 소검	============ 무 기 ==========
	NAME_SHORT_SWORD,		//소검
	NAME_SWORD,				//검
	NAME_SPEAR,				//창
	NAME_BATTLE_AXE,		//전투 도끼
	NAME_CLOTH,				//일반 옷	============ 방 어 구 =======
	NAME_LEATHER,			//경갑
	NAME_MAIL,				//중갑
	NAME_RING_POWER,		//저항 반지	============ 악 세 ==========
	NAME_RING_RECHARGE,		//충전 반지
	NAME_LIOYDS_BEACON,		//완드
	NAME_DART,				//다트		============ 투 척 ==========
	NAME_PARALYSIS_DART,	//마비 다트
	NAME_POISON_DART,		//독 다트
	NAME_LIGHTNING,			//전기 완드	============ 완 드 ==========
	NAME_NORMAL,			//마법 완드
	NAME_POISON,			//독 완드
	NAME_EMERGENCY,			//비상식량	============ 음 식===========
	NAME_PASTY,				//파스티
	NAME_UNKNOWN_MEAT,		//알수없는 고기
	NAME_COOKED_MEAT,		//익힌고기
	NAME_FROZEN_MEAT,		//얼린 고기
	NAME_IDENTIFY,			//확인		============ 주 문 서 =======
	NAME_UPGRADE,			//강화
	NAME_PURIFY,			//정화
	NAME_MAP,				//지도
	NAME_RECHARGE,			//재충전
	NAME_DEW,				//이슬		============ 포 션 ==========
	NAME_HEAL,				//회복
	NAME_STR,				//힘
	NAME_EX,				//숙련도
	NAME_INVISIBLE,			//투명화
	NAME_LEVITATION,		//공중부양
	NAME_FORZEN,			//서리
	NAME_LIQUID_FIRE,		//액체 화염
	NAME_SEED_HEAL,			//치유		============ 씨 앗 ==========
	NAME_SEED_FIRE,			//화염초
	NAME_SEED_SNAKE,		//뱀뿌리
	NAME_SEED_FROST,		//얼음
	NAME_DEWW				//이슬		============ 특 수 ==========
	*/

	switch (_selectItem)
	{
		//낡은 소검
	case NAME_OLD_SHORT_SWORD:
		fream_window_draw(28, 12);
		button_interface(NAME_OLD_SHORT_SWORD, TYPE_WEAPON, 3, 28, 12);

		//char str[] = "폰트테스트";
		//HFONT hFont = CreateFont(50, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("굴림"));
		//HFONT oldFont = (HFONT)SelectObject(getMemDC(), hFont);
		////TextOut(getMemDC(), 300, 300, str, strlen(str));
		//SelectObject(getMemDC(), oldFont);
		//DeleteObject(hFont);

		break;

		//소검
	case NAME_SHORT_SWORD:
		fream_window_draw(28, 12);
		button_interface(NAME_SHORT_SWORD, TYPE_WEAPON, 3, 28, 12);
		break;

		//검
	case NAME_SWORD:
		fream_window_draw(28, 12);
		button_interface(NAME_SWORD, TYPE_WEAPON, 3, 28, 12);
		break;

		//창
	case NAME_SPEAR:
		fream_window_draw(28, 12);
		button_interface(NAME_SPEAR, TYPE_WEAPON, 3, 28, 12);
		break;

		//전투 도끼
	case NAME_BATTLE_AXE:
		fream_window_draw(28, 12);
		button_interface(NAME_BATTLE_AXE, TYPE_WEAPON, 3, 28, 12);
		break;

		//일반 옷
	case NAME_CLOTH:
		fream_window_draw(28, 12);
		button_interface(NAME_CLOTH, TYPE_ARMOR, 3, 28, 12);
		break;

		//경갑
	case NAME_LEATHER:
		fream_window_draw(28, 12);
		button_interface(NAME_LEATHER, TYPE_ARMOR, 3, 28, 12);
		break;

		//중갑
	case NAME_MAIL:
		fream_window_draw(28, 12);
		button_interface(NAME_MAIL, TYPE_ARMOR, 3, 28, 12);
		break;

		//저항 반지
	case NAME_RING_POWER:
		fream_window_draw(28, 12);
		button_interface(NAME_RING_POWER, TYPE_ACC, 3, 28, 12);
		break;

		//충전 반지
	case NAME_RING_RECHARGE:
		fream_window_draw(28, 12);
		button_interface(NAME_RING_RECHARGE, TYPE_ACC, 3, 28, 12);
		break;

		//완드
	case NAME_LIOYDS_BEACON:
		fream_window_draw(47, 12);
		button_interface(NAME_LIOYDS_BEACON, TYPE_ACC, 5, 47, 12);
		break;

		//다트
	case NAME_DART:
		fream_window_draw(28, 12);
		button_interface(NAME_DART, TYPE_THROW, 3, 28, 12);
		break;

		//마비 다트
	case NAME_PARALYSIS_DART:
		fream_window_draw(28, 12);
		button_interface(NAME_PARALYSIS_DART, TYPE_THROW, 3, 28, 12);
		break;

		//독 다트
	case NAME_POISON_DART:
		fream_window_draw(28, 12);
		button_interface(NAME_POISON_DART, TYPE_THROW, 3, 28, 12);
		break;

		//전기 완드
	case NAME_LIGHTNING:
		fream_window_draw(28, 12);
		button_interface(NAME_LIGHTNING, TYPE_WAND, 3, 28, 12);
		break;

		//마법 완드
	case NAME_NORMAL:
		fream_window_draw(28, 12);
		button_interface(NAME_NORMAL, TYPE_WAND, 3, 28, 12);
		break;

		//독 완드
	case NAME_POISON:
		fream_window_draw(28, 12);
		button_interface(NAME_POISON, TYPE_WAND, 3, 28, 12);
		break;

		//비상식량
	case NAME_EMERGENCY:
		fream_window_draw(28, 12);
		button_interface(NAME_EMERGENCY, TYPE_FOOD, 3, 28, 12);
		break;

		//파스티
	case NAME_PASTY:
		fream_window_draw(28, 12);
		button_interface(NAME_PASTY, TYPE_FOOD, 3, 28, 12);
		break;

		//알수없는 고기
	case NAME_UNKNOWN_MEAT:
		fream_window_draw(28, 12);
		button_interface(NAME_UNKNOWN_MEAT, TYPE_FOOD, 3, 28, 12);
		break;

		//익힌 고기
	case NAME_COOKED_MEAT:
		fream_window_draw(28, 12);
		button_interface(NAME_COOKED_MEAT, TYPE_FOOD, 3, 28, 12);
		break;

		//얼린 고기
	case NAME_FROZEN_MEAT:
		fream_window_draw(28, 12);
		button_interface(NAME_FROZEN_MEAT, TYPE_FOOD, 3, 28, 12);
		break;

		//확인
	case NAME_IDENTIFY:
		fream_window_draw(28, 12);
		button_interface(NAME_IDENTIFY, TYPE_SCROLL, 3, 28, 12);
		break;

		//강화
	case NAME_UPGRADE:
		fream_window_draw(28, 20);
		button_interface(NAME_UPGRADE, TYPE_SCROLL, 3, 28, 20);
		break;

		//정화
	case NAME_PURIFY:
		fream_window_draw(28, 12);
		button_interface(NAME_PURIFY, TYPE_SCROLL, 3, 28, 12);
		break;

		//지도
	case NAME_MAP:
		fream_window_draw(28, 12);
		button_interface(NAME_MAP, TYPE_SCROLL, 3, 28, 12);
		break;

		//재충전
	case NAME_RECHARGE:
		fream_window_draw(28, 12);
		button_interface(NAME_RECHARGE, TYPE_SCROLL, 3, 28, 12);
		break;

		//이슬
	case NAME_BOTTLE:
		fream_window_draw(28, 12);
		button_interface(NAME_BOTTLE, TYPE_POTION, 3, 28, 12);
		break;

		//회복
	case NAME_HEAL:
		fream_window_draw(28, 12);
		button_interface(NAME_HEAL, TYPE_POTION, 3, 28, 12);
		break;

		//힘
	case NAME_STR:
		fream_window_draw(28, 12);
		button_interface(NAME_STR, TYPE_POTION, 3, 28, 12);
		break;

		//숙련도
	case NAME_EX:
		fream_window_draw(28, 12);
		button_interface(NAME_EX, TYPE_POTION, 3, 28, 12);
		break;

		//투명화
	case NAME_INVISIBLE:
		fream_window_draw(28, 15);
		button_interface(NAME_INVISIBLE, TYPE_POTION, 3, 28, 15);
		break;

		//공중 부양
	case NAME_LEVITATION:
		fream_window_draw(28, 15);
		button_interface(NAME_LEVITATION, TYPE_POTION, 3, 28, 15);
		break;

		//서리
	case NAME_FROZEN:
		fream_window_draw(28, 12);
		button_interface(NAME_FROZEN, TYPE_POTION, 3, 28, 12);
		break;

		//액체 화염
	case NAME_LIQUID_FIRE:
		fream_window_draw(28, 12);
		button_interface(NAME_LIQUID_FIRE, TYPE_POTION, 3, 28, 12);
		break;

		//치유
	case NAME_SEED_HEAL:
		fream_window_draw(28, 12);
		button_interface(NAME_SEED_HEAL, TYPE_SEED, 3, 28, 12);
		break;

		//화염초
	case NAME_SEED_FIRE:
		fream_window_draw(28, 12);
		button_interface(NAME_SEED_FIRE, TYPE_SEED, 3, 28, 12);
		break;

		//뱀뿌리
	case NAME_SEED_SNAKE:
		fream_window_draw(28, 12);
		button_interface(NAME_SEED_SNAKE, TYPE_SEED, 3, 28, 12);
		break;

		//얼음
	case NAME_SEED_FROST:
		fream_window_draw(28, 12);
		button_interface(NAME_SEED_FROST, TYPE_SEED, 3, 28, 12);
		break;

		//이슬
	case NAME_DEW:
		fream_window_draw(28, 12);
		button_interface(NAME_DEW, TYPE_SPECIAL, 3, 28, 12);
		break;

		//없음
	case NAME_END:
		break;
	}
}

void UI::fream_window_draw(size_t sizeX, size_t sizeY, int coordX, int coordY)
{
	for (size_t fream_windowY = 0; fream_windowY <= sizeY; fream_windowY++)
	{
		for (size_t fream_windowX = 0; fream_windowX <= sizeX; fream_windowX++)
		{
			if (fream_windowY == 0)
			{
				fream_valueY = 0;
			}

			if (fream_windowY == sizeY)
			{
				fream_valueY = 3;
			}

			if (fream_windowY != 0 && fream_windowY != sizeY)
			{
				fream_valueY = 1;
			}

			if (fream_windowY == 0 || fream_windowY == sizeY)
			{
				if (fream_windowX == 0 || fream_windowX == sizeX)
				{
					fream_valueX = 0;
				}

				if (fream_windowX != 0 && fream_windowX != sizeX)
				{
					fream_valueX = 1;
				}
			}

			if (fream_windowY != 0 || fream_windowY != sizeY)
			{
				if (fream_windowX == 0)
				{
					fream_valueX = 0;
				}

				if (fream_windowX != 0 && fream_windowX != sizeX)
				{
					fream_valueX = 1;
				}

				if (fream_windowX == sizeX)
				{
					fream_valueX = 3;
				}
			}

			IMAGEMANAGER->frameRender("fream_window1", getMemDC(),
				((WINSIZEX / 2) - ((sizeX * IMAGEMANAGER->findImage("fream_window1")->getFrameWidth()) / 2)) + (fream_windowX * IMAGEMANAGER->findImage("fream_window1")->getFrameWidth()) + coordX,
				((WINSIZEY / 2) - ((sizeY * IMAGEMANAGER->findImage("fream_window1")->getFrameHeight()) / 2)) + (fream_windowY * IMAGEMANAGER->findImage("fream_window1")->getFrameHeight()) + coordY,
				fream_valueX, fream_valueY);
		}
	}
}

void UI::button_interface(int itemName, int itemType, int createNumber, int fream_window_sizeX, int fream_window_sizeY)
{
	int itemCheck = 0;

	for (int Check = 0; Check < _im->getvBag().size(); Check++)
	{
		if (_im->getvBag()[Check].name == itemName)
		{
			itemCheck = Check;
		}
	}

	for (int buttonNumber = 0; buttonNumber < createNumber; buttonNumber++)
	{
		if (buttonNumber == 0)
			button_option_value[buttonNumber].number = BUTTONOPTION_DROP;

		if (buttonNumber == 1)
			button_option_value[buttonNumber].number = BUTTONOPTION_THROW;

		if (itemType == TYPE_WEAPON || itemType == TYPE_ARMOR || itemType == TYPE_ACC)
		{
			if (buttonNumber == 2)
			{
				if (_im->getvBag()[itemCheck].equip == false)
				{
					button_option_value[buttonNumber].number = BUTTONOPTION_WEAR;
				}

				if (_im->getvBag()[itemCheck].equip == true)
				{
					button_option_value[buttonNumber].number = BUTTONOPTION_UNLOCK;
				}
			}
		}

		if (itemName == NAME_LIOYDS_BEACON && itemType == TYPE_ACC)
		{
			if (buttonNumber == 3)
				button_option_value[buttonNumber].number = BUTTONOPTION_LAUNCH;

			if (buttonNumber == 4)
				button_option_value[buttonNumber].number = BUTTONOPTION_REMEMBER;
		}

		if (itemType == TYPE_POTION)
		{
			if (buttonNumber == 2)
				button_option_value[buttonNumber].number = BUTTONOPTION_DRINK;
		}

		if (itemType == TYPE_SCROLL)
		{
			if (buttonNumber == 2)
				button_option_value[buttonNumber].number = BUTTONOPTION_READ;
		}

		if (itemType == TYPE_SEED)
		{
			if (buttonNumber == 2)
				button_option_value[buttonNumber].number = BUTTONOPTION_PLANT;
		}

		if (itemType == TYPE_FOOD)
		{
			if (buttonNumber == 2)
				button_option_value[buttonNumber].number = BUTTONOPTION_EAT;
		}

		if (itemType == TYPE_WAND)
		{
			if (buttonNumber == 2)
				button_option_value[buttonNumber].number = BUTTONOPTION_LAUNCH;
		}

		if (itemType == TYPE_THROW)
		{
			if (buttonNumber == 2)
				button_option_value[buttonNumber].number = BUTTONOPTION_LAUNCH;
		}

		for (int optioCheck = 0; optioCheck < 10; optioCheck++)
		{
			_im->getvBag()[itemCheck].img->render(getMemDC(), ((WINSIZEX / 2) - (fream_window_sizeX * IMAGEMANAGER->findImage("fream_window1")->getFrameHeight()) / 2) + 30, ((WINSIZEY / 2) - (fream_window_sizeY * IMAGEMANAGER->findImage("fream_window1")->getFrameHeight()) / 2) + 30);

			if (button_option_value[buttonNumber].number == optioCheck)
			{
				IMAGEMANAGER->frameRender("select_menu_bar", getMemDC(),
					((WINSIZEX / 2) - ((IMAGEMANAGER->findImage("select_menu_bar")->getFrameWidth() * createNumber) / 2)) + (buttonNumber * IMAGEMANAGER->findImage("select_menu_bar")->getFrameWidth() + ((buttonNumber + 1) * 3)),
					((WINSIZEY / 2) + (fream_window_sizeY * IMAGEMANAGER->findImage("fream_window1")->getFrameHeight()) / 2) - IMAGEMANAGER->findImage("select_menu_bar")->getFrameHeight() - 3,
					0, button_option_value[buttonNumber].number);

				button_option_intersectRect[buttonNumber] = RectMake(
					((WINSIZEX / 2) - ((IMAGEMANAGER->findImage("select_menu_bar")->getFrameWidth() * createNumber) / 2)) + (buttonNumber * IMAGEMANAGER->findImage("select_menu_bar")->getFrameWidth() + ((buttonNumber + 1) * 3)),
					((WINSIZEY / 2) + (fream_window_sizeY * IMAGEMANAGER->findImage("fream_window1")->getFrameHeight()) / 2) - IMAGEMANAGER->findImage("select_menu_bar")->getFrameHeight() - 3,
					130, 43);
			}
		}

		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON) && PtInRect(&button_option_intersectRect[buttonNumber], _ptMouse) && (TIMEMANAGER->getWorldTime() - _interface_button_timer2) > 0.3 && _selectItem != NAME_END)
		{
			//떨어뜨린다
			if (button_option_value[buttonNumber].number == BUTTONOPTION_DROP)
			{
				if (_player->getAction() == true)
				{
					_player->endTurn();
				}

				_player->setUsingUI(false);
				_im->setItemToField((ITEMNAME)itemName, (LONG)_player->getPoint().x, (LONG)_player->getPoint().y, _im->getvBag()[_itemPosition - 4].contentsHide, _im->getvBag()[_itemPosition - 4].isCursed, _im->getvBag()[_itemPosition - 4].upgrade, _im->getvBag()[_itemPosition - 4].numOfItem,_map->getCurStageNum());
				_selectItem = NAME_END;
				_selectInterface = INTERFACEMENU_END;
				usingui();

				int equipnumber = 0;

				for (int check = 0; check < (_itemPosition - 4); check++)
				{
					if (_im->getvBag()[check].equip == true)
					{
						equipnumber++;
					}
				}

				_inventory[_itemPosition].itemNumber = NAME_END;
				_im->removeBagItem(((_itemPosition - 4) + equipnumber));
			}

			//마신다
			if (button_option_value[buttonNumber].number == BUTTONOPTION_DRINK)
			{
				if (_player->getAction() == true)
				{
					_player->endTurn();
				}

				_player->setUsingUI(false);
				_selectItem = NAME_END;
				_selectInterface = INTERFACEMENU_END;
				usingui();

				int equipnumber = 0;

				for (int check = 0; check < (_itemPosition - 4); check++)
				{
					if (_im->getvBag()[check].equip == true)
					{
						equipnumber++;
					}
				}

				_inventory[_itemPosition].itemNumber = NAME_END;
				_im->useItem((_itemPosition - 4) + equipnumber);
			}

			//던진다
			if (button_option_value[buttonNumber].number == BUTTONOPTION_THROW)
			{
				if (_player->getAction() == true)
				{
					_player->endTurn();
				}

				_player->setUsingUI(false);
				//_im->throwItem((ITEMNAME)itemName, _ptMouse.x, _ptMouse.y);
				_selectItem = NAME_END;
				_selectInterface = INTERFACEMENU_END;
				usingui();

				throwcheck = true;
				isthrow = true;
			}

			//읽는다
			if (button_option_value[buttonNumber].number == BUTTONOPTION_READ)
			{
				if (_player->getAction() == true)
				{
					_player->endTurn();
				}

				_player->setUsingUI(false);

				if (itemName == NAME_IDENTIFY)
				{
					isscroll = true;
					isidentity = true;
				}

				if (itemName == NAME_UPGRADE)
				{
					isscroll = true;
					isUpgrad = true;
				}

				if (itemName == NAME_PURIFY)
				{
					isscroll = true;
					ispurify = true;
				}

				if (itemName != NAME_IDENTIFY && itemName != NAME_UPGRADE && itemName != NAME_PURIFY)
				{
					_im->useItem(_itemPosition - 4);
					_selectInterface = INTERFACEMENU_END;
					usingui();
				}

				_selectItem = NAME_END;
				usingui();
			}

			//발사한다
			if (button_option_value[buttonNumber].number == BUTTONOPTION_LAUNCH)
			{
				if (_player->getAction() == true)
				{
					_player->endTurn();
				}

				_player->setUsingUI(false);
				//_im->fire();
				_selectItem = NAME_END;
				_selectInterface = INTERFACEMENU_END;
				usingui();

				throwcheck = true;
				islaunch = true;
			}

			//먹는다
			if (button_option_value[buttonNumber].number == BUTTONOPTION_EAT)
			{
				if (_player->getAction() == true)
				{
					_player->action_Eat();
					_player->endTurn();

					//PLAYERSTAT temp = _player->getStat();
					//temp.exp += 3;
					//_player->setStat(temp);
				}

				_player->setUsingUI(false);
				_selectItem = NAME_END;
				_selectInterface = INTERFACEMENU_END;
				usingui();

				int equipnumber = 0;

				for (int check = 0; check < (_itemPosition - 4); check++)
				{
					if (_im->getvBag()[check].equip == true)
					{
						equipnumber++;
					}
				}

				_inventory[_itemPosition].itemNumber = NAME_END;
				_im->useItem((_itemPosition - 4) + equipnumber);
			}

			//심는다
			if (button_option_value[buttonNumber].number == BUTTONOPTION_PLANT)
			{
				if (_player->getAction() == true)
				{
					_player->endTurn();
				}

				_player->setUsingUI(false);
				_selectItem = NAME_END;
				_selectInterface = INTERFACEMENU_END;
				usingui();

				int equipnumber = 0;

				for (int check = 0; check < (_itemPosition - 4); check++)
				{
					if (_im->getvBag()[check].equip == true)
					{
						equipnumber++;
					}
				}

				_inventory[_itemPosition].itemNumber = NAME_END;
				_im->useItem((_itemPosition - 4) + equipnumber, (LONG)_player->getPoint().x, (LONG)_player->getPoint().y);
			}

			//기억한다
			if (button_option_value[buttonNumber].number == BUTTONOPTION_REMEMBER)
			{
				if (_player->getAction() == true)
				{
					_player->endTurn();
				}

				_player->setUsingUI(false);
				_selectItem = NAME_END;
				_selectInterface = INTERFACEMENU_END;
				usingui();
			}

			//착용한다
			if (button_option_value[buttonNumber].number == BUTTONOPTION_WEAR)
			{
				//착용중

				if (_im->getvBag()[itemCheck].equip == true)
				{
					if (itemType == TYPE_WEAPON && _im->getvBag()[itemCheck].type == TYPE_WEAPON)
					{
						int tempweapon = _inventory[TYPE_WEAPON].itemNumber;
						_inventory[TYPE_WEAPON].itemNumber = _inventory[_itemPosition].itemNumber;
						_inventory[_itemPosition].itemNumber = tempweapon;
					}

					if (itemType == TYPE_ARMOR && _im->getvBag()[itemCheck].type == TYPE_ARMOR)
					{
						int temparmor = _inventory[TYPE_ARMOR].itemNumber;
						_inventory[TYPE_ARMOR].itemNumber = _inventory[_itemPosition].itemNumber;
						_inventory[_itemPosition].itemNumber = temparmor;
					}

					if (itemType == TYPE_ACC && _im->getvBag()[itemCheck].type == TYPE_ACC)
					{
						int tempacc = _inventory[TYPE_ACC].itemNumber;
						_inventory[TYPE_ACC].itemNumber = _inventory[_itemPosition].itemNumber;
						_inventory[_itemPosition].itemNumber = tempacc;
					}

				}

				//미착용중

				if (_im->getvBag()[itemCheck].equip == false)
				{
					if (itemType == TYPE_WEAPON && _im->getvBag()[itemCheck].type == TYPE_WEAPON)
					{
						if (_im->getvBag()[itemCheck].name == _inventory[_itemPosition].itemNumber)
						{
							_im->equipItem(itemCheck);
						}

						_inventory[TYPE_WEAPON].itemNumber = _inventory[_itemPosition].itemNumber;
						_inventory[_itemPosition].itemNumber = NAME_END;
					}

					if (itemType == TYPE_ARMOR && _im->getvBag()[itemCheck].type == TYPE_ARMOR)
					{
						if (_im->getvBag()[itemCheck].name == _inventory[_itemPosition].itemNumber)
						{
							_im->equipItem(itemCheck);
						}

						_inventory[TYPE_ARMOR].itemNumber = _inventory[_itemPosition].itemNumber;
						_inventory[_itemPosition].itemNumber = NAME_END;
					}

					if (itemType == TYPE_ACC && _im->getvBag()[itemCheck].type == TYPE_ACC)
					{
						if (_im->getvBag()[itemCheck].name == _inventory[_itemPosition].itemNumber)
						{
							_im->equipItem(itemCheck);
						}

						_inventory[TYPE_ACC].itemNumber = _inventory[_itemPosition].itemNumber;
						_inventory[_itemPosition].itemNumber = NAME_END;
					}
				}

				if (_player->getAction() == true)
				{
					_player->endTurn();
				}

				_player->setUsingUI(false);
				_selectItem = NAME_END;
				_selectInterface = INTERFACEMENU_END;
				usingui();
			}

			//해제한다
			if (button_option_value[buttonNumber].number == BUTTONOPTION_UNLOCK)
			{
				//for (int i = 4; i < ARRSIZE; i++)
				//{
				//	if (_inventory[i].itemNumber == NAME_END)
				//	{
				//		inventory_null = i;
				//		break;
				//	}
				//}

				if (itemType == TYPE_WEAPON)
				{
					//_inventory[inventory_null].itemNumber = _inventory[TYPE_WEAPON].itemNumber;
					_inventory[TYPE_WEAPON].itemNumber = NAME_END;
					_im->unequipItem(itemCheck);
				}

				if (itemType == TYPE_ARMOR)
				{
					//_inventory[inventory_null].itemNumber = _inventory[TYPE_ARMOR].itemNumber;
					_inventory[TYPE_ARMOR].itemNumber = NAME_END;
					_im->unequipItem(itemCheck);
				}

				if (itemType == TYPE_ACC)
				{
					//_inventory[inventory_null].itemNumber = _inventory[TYPE_ACC].itemNumber;
					_inventory[TYPE_ACC].itemNumber = NAME_END;
					_im->unequipItem(itemCheck);
				}

				if (_player->getAction() == true)
				{
					_player->endTurn();
				}

				_player->setUsingUI(false);
				_selectItem = NAME_END;
				_selectInterface = INTERFACEMENU_END;
				usingui();
			}

			if (button_option_value[buttonNumber].number == BUTTONOPTION_END)
				break;

			_interface_button_timer2 = TIMEMANAGER->getWorldTime();
		}
	}

	if (itemName == NAME_OLD_SHORT_SWORD)
	{
		char name[] = "낡은 소검";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "이 가벼운 갑옷은 기본적인 보호를 제공합니다.";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);

		char explanationLine2[] = "보통 소검보다 가볍고 피해를 덜 입힙니다.";
		PrintFont(explanationLine2, namehFont, nameoldFont, 220, 300, 15, 255, 255, 255);
	}

	if (itemName == NAME_SHORT_SWORD)
	{
		char name[] = "소검";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "이 무기는 단검보다 겨우 한두 뼘 정도 긴 무기에 불과합";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);

		char explanationLine2[] = "니다.";
		PrintFont(explanationLine2, namehFont, nameoldFont, 220, 300, 15, 255, 255, 255);
	}

	if (itemName == NAME_SWORD)
	{
		char name[] = "검";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "괜찮게 균형잡힌 검입니다.";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);

		char explanationLine2[] = "너무 크지는 않지만, 확실히 소검보다는 큽니다.";
		PrintFont(explanationLine2, namehFont, nameoldFont, 220, 300, 15, 255, 255, 255);
	}

	if (itemName == NAME_SPEAR)
	{
		char name[] = "창";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "길쭉한 나무봉 끝에 날카로운 쇠가 붙어있습니다.";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);
	}

	if (itemName == NAME_BATTLE_AXE)
	{
		char name[] = "전투 도끼";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);
	}

	if (itemName == NAME_CLOTH)
	{
		char name[] = "천 갑옷";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "이 가벼운 갑옷은 기본적인 보호를 제공합니다.";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);
	}

	if (itemName == NAME_LEATHER)
	{
		char name[] = "가죽 갑옷";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "그을려진 몬스터의 가죽으로 만든 갑옷입니다.";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);

		char explanationLine2[] = "천 갑옷 만큼 가볍지는 않지만 훨씬 더 나은 보호 효과를";
		PrintFont(explanationLine2, namehFont, nameoldFont, 220, 300, 15, 255, 255, 255);

		char explanationLine3[] = "제공해 줍니다.";
		PrintFont(explanationLine3, namehFont, nameoldFont, 220, 320, 15, 255, 255, 255);
	}

	if (itemName == NAME_MAIL)
	{
		char name[] = "사슬 갑옷";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "속 고리를 서로 엮어 만든 갑옷으로 단단하지만 유연한";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);

		char explanationLine2[] = "갑옷입니다.";
		PrintFont(explanationLine2, namehFont, nameoldFont, 220, 300, 15, 255, 255, 255);
	}

	if (itemName == NAME_RING_POWER)
	{
		char name[] = "저항 반지";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);
	}

	if (itemName == NAME_RING_RECHARGE)
	{
		char name[] = "충전 반지";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);
	}

	if (itemName == NAME_LIOYDS_BEACON)
	{
		char name[] = "로이드의 신호기";
		PrintFont(name, namehFont, nameoldFont, 120, 245, 25, 255, 255, 0);

		char explanation[] = "로이드의 신호기는 사용자에게 공간이동 마법을 제어할 수 있는 정교한 마법 장치입니다.";
		PrintFont(explanation, namehFont, nameoldFont, 70, 280, 15, 255, 255, 255);

		char explanationLine2[] = "신호기에 원하는 위치를 등록 시켜 돌아갈수도 있지만, 장비한 상태에서 충전량을 소모하여 무작위 공";
		PrintFont(explanationLine2, namehFont, nameoldFont, 70, 300, 15, 255, 255, 255);

		char explanationLine3[] = "간이동 마법을 발사할 수 있습니다. 이 마법은 대상에게 사용하거나 자신에게도 사용할 수 있습니다.";
		PrintFont(explanationLine3, namehFont, nameoldFont, 70, 320, 15, 255, 255, 255);
	}

	if (itemName == NAME_DART)
	{
		char name[] = "다트";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);
	}

	if (itemName == NAME_PARALYSIS_DART)
	{
		char name[] = "마비 다트";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);
	}

	if (itemName == NAME_POISON_DART)
	{
		char name[] = "독 다트";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);
	}

	if (itemName == NAME_LIGHTNING)
	{
		char name[] = "전기 완드";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);
	}

	if (itemName == NAME_NORMAL)
	{
		char name[] = "마법 막대";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "이 평범해 보이는 막대는 순수한 마법 에너지를 발사합니다.";
		PrintFont(explanation, namehFont, nameoldFont, 210, 280, 15, 255, 255, 255);

		char explanationLine2[] = "다른 막대에 비해서 강하지는 않지만, 그에 비해 더 많은 충";
		PrintFont(explanationLine2, namehFont, nameoldFont, 210, 300, 15, 255, 255, 255);

		char explanationLine3[] = "전량을 가집니다.";
		PrintFont(explanationLine3, namehFont, nameoldFont, 210, 320, 15, 255, 255, 255);
	}

	if (itemName == NAME_POISON)
	{
		char name[] = "독 완드";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);
	}

	if (itemName == NAME_EMERGENCY)
	{
		char name[] = "비상 식량";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);
	}

	if (itemName == NAME_PASTY)
	{
		char name[] = "파스티";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);
	}

	if (itemName == NAME_UNKNOWN_MEAT)
	{
		char name[] = "알수없는 고기";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);
	}

	if (itemName == NAME_COOKED_MEAT)
	{
		char name[] = "익힌고기";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);
	}

	if (itemName == NAME_FROZEN_MEAT)
	{
		char name[] = "얼린고기";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);
	}

	if (itemName == NAME_IDENTIFY)
	{
		char name[] = "감정의 주문서";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "이 주문서는 하나의 아이템을 비밀을 영구적으로 드러냅";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);

		char explanationLine2[] = "니다.";
		PrintFont(explanationLine2, namehFont, nameoldFont, 220, 300, 15, 255, 255, 255);
	}

	if (itemName == NAME_UPGRADE)
	{
		char name[] = "강화의 주문서";
		PrintFont(name, namehFont, nameoldFont, 260, 185, 25, 255, 255, 0);

		char explanation[] = "이 주문서는 하나의 아이템을 강화하여 품질을 높힙니다.";
		PrintFont(explanation, namehFont, nameoldFont, 210, 220, 15, 255, 255, 255);

		char explanationLine2[] = "마법 막대는 더 강력해지고 충전 횟수가 증가하며, 무기는";
		PrintFont(explanationLine2, namehFont, nameoldFont, 210, 240, 15, 255, 255, 255);

		char explanationLine3[] = "더 많은 피해를 줄 수 있고, 방어구는 피해를 더 잘 흡수 ";
		PrintFont(explanationLine3, namehFont, nameoldFont, 210, 260, 15, 255, 255, 255);

		char explanationLine4[] = "하게됩니다. 또한 반지는 착용자에게 주어지는 효과를 더";
		PrintFont(explanationLine4, namehFont, nameoldFont, 210, 280, 15, 255, 255, 255);

		char explanationLine5[] = "강화합니다. 무기와 갑옷은 또한 착용하는 데 필요한 힘을";
		PrintFont(explanationLine5, namehFont, nameoldFont, 210, 300, 15, 255, 255, 255);

		char explanationLine6[] = "소폭 감소시키며, 저주해제의 주문서보다는 못하지만 아이";
		PrintFont(explanationLine6, namehFont, nameoldFont, 210, 320, 15, 255, 255, 255);

		char explanationLine7[] = "템에 걸린 저주를 약화시킬 수도 있습니다.";
		PrintFont(explanationLine7, namehFont, nameoldFont, 210, 340, 15, 255, 255, 255);
	}

	if (itemName == NAME_PURIFY)
	{
		char name[] = "저주 해제의 주문서";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "이 주문서에 담긴 마법은 사용자의 무기, 반지, 마법봉, 유";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);

		char explanationLine2[] = "물에 깃든 저주를 즉시 제거합니다.";
		PrintFont(explanationLine2, namehFont, nameoldFont, 220, 300, 15, 255, 255, 255);
	}

	if (itemName == NAME_MAP)
	{
		char name[] = "마법 지도의 주문서";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "이 주문서를 읽으면, 수정같이 맑은 형상이 기억에 각인되";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);

		char explanationLine2[] = "어, 현재 층의 모든 비밀을 포함한 지형을 드러나게 합니";
		PrintFont(explanationLine2, namehFont, nameoldFont, 220, 300, 15, 255, 255, 255);

		char explanationLine3[] = "다. 아이템과 생물체들의 위치는 여전히 알 수 없습니다.";
		PrintFont(explanationLine3, namehFont, nameoldFont, 220, 320, 15, 255, 255, 255);
	}

	if (itemName == NAME_RECHARGE)
	{
		char name[] = "충전의 주문서";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "이 주문서에 담겨 있는 그대로의 마력은 풀려날 때 사용자";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);

		char explanationLine2[] = "의 마법 막대를 서서히 충전시킵니다.";
		PrintFont(explanationLine2, namehFont, nameoldFont, 220, 300, 15, 255, 255, 255);
	}

	if (itemName == NAME_BOTTLE)
	{
		char name[] = "이슬";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);
	}

	if (itemName == NAME_HEAL)
	{
		char name[] = "치유 물약";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "이 회복약은 체력을 급속도로 회복시키며 많은 상태 이상";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);

		char explanationLine2[] = "을 치료합니다.";
		PrintFont(explanationLine2, namehFont, nameoldFont, 220, 300, 15, 255, 255, 255);
	}

	if (itemName == NAME_STR)
	{
		char name[] = "힘의 물약";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "이 강력한 용액은 당신의 근육을 타고 흘러, 당신의 힘을";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);

		char explanationLine2[] = "1만큼 영구적으로 늘립니다.";
		PrintFont(explanationLine2, namehFont, nameoldFont, 220, 300, 15, 255, 255, 255);
	}

	if (itemName == NAME_EX)
	{
		char name[] = "경험의 물약";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "많은 사람들의 경험을 적은 이야기를 액체로 만든 것이며,";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);

		char explanationLine2[] = "이 물약을 마시는 즉시 당신의 경험 레벨을 올릴 것입니다.";
		PrintFont(explanationLine2, namehFont, nameoldFont, 220, 300, 15, 255, 255, 255);
	}

	if (itemName == NAME_INVISIBLE)
	{
		char name[] = "투명화의 물약";
		PrintFont(name, namehFont, nameoldFont, 260, 225, 25, 255, 255, 0);

		char explanation[] = "이 물약을 마시면 일시적으로 투명해집니다.";
		PrintFont(explanation, namehFont, nameoldFont, 220, 260, 15, 255, 255, 255);

		char explanationLine2[] = "투명해진 상태에서는 적들이 당신을 볼 수 없습니다.";
		PrintFont(explanationLine2, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);

		char explanationLine3[] = "적을 공격하거나, 마법 막대를 사용하거나, 적 앞에서 마";
		PrintFont(explanationLine3, namehFont, nameoldFont, 220, 300, 15, 255, 255, 255);

		char explanationLine4[] = "법 주문서를 사용하면 투명 효과가 사라집니다.";
		PrintFont(explanationLine4, namehFont, nameoldFont, 220, 320, 15, 255, 255, 255);
	}

	if (itemName == NAME_LEVITATION)
	{
		char name[] = "부유의 물약";
		PrintFont(name, namehFont, nameoldFont, 260, 225, 25, 255, 255, 0);

		char explanation[] = "이 호기심을 자아내는 물약을 마시면 공중으로 떠오르게";
		PrintFont(explanation, namehFont, nameoldFont, 220, 260, 15, 255, 255, 255);

		char explanationLine2[] = "됩니다. 당신은 공중을 별 어려움 없이 떠다닐 수 있으며";
		PrintFont(explanationLine2, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);

		char explanationLine3[] = "함정과 구덩이를 넘어다닐 수 있습니다.물약을 던지면 정";
		PrintFont(explanationLine3, namehFont, nameoldFont, 220, 300, 15, 255, 255, 255);

		char explanationLine4[] = "제 되지 않은 가스르 내뿜어 가스를 들이마신 대상의 방향";
		PrintFont(explanationLine4, namehFont, nameoldFont, 220, 320, 15, 255, 255, 255);

		char explanationLine5[] = "감각을 상실시킵니다.";
		PrintFont(explanationLine5, namehFont, nameoldFont, 220, 340, 15, 255, 255, 255);
	}

	if (itemName == NAME_FROZEN)
	{
		char name[] = "서리의 물약";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "이 화합물은 공기에 닿는 즉시 차가운 구름으로 기화합니";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);

		char explanationLine2[] = "다.";
		PrintFont(explanationLine2, namehFont, nameoldFont, 220, 300, 15, 255, 255, 255);
	}

	if (itemName == NAME_LIQUID_FIRE)
	{
		char name[] = "액체 화염 물약";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "이 물병은 불안정한 화합물로 가득 차 있어 공기와 닿으면";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);

		char explanationLine2[] = "급격한 폭발을 일으키며 주변을 불로 덮습니다.";
		PrintFont(explanationLine2, namehFont, nameoldFont, 220, 300, 15, 255, 255, 255);
	}

	if (itemName == NAME_SEED_HEAL)
	{
		char name[] = "치유";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);
	}

	if (itemName == NAME_SEED_FIRE)
	{
		char name[] = "화염초의 씨앗";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "이 씨앗을 원하는 곳에다 던져 식물을 자라게 할 수 있습니";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);

		char explanationLine2[] = "다. 무언가가 화염초를 건드리게 되면 폭발하여 주변을 불";
		PrintFont(explanationLine2, namehFont, nameoldFont, 220, 300, 15, 255, 255, 255);

		char explanationLine3[] = "꽃으로 뒤덮습니다.";
		PrintFont(explanationLine3, namehFont, nameoldFont, 220, 320, 15, 255, 255, 255);
	}

	if (itemName == NAME_SEED_SNAKE)
	{
		char name[] = "뱀뿌리의 씨앗";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "이 씨앗을 원하는 곳에다 던져 식물을 자라게 할 수 있습니다.";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);

		char explanationLine2[] = "생물체가 뱀뿌리를 건드리면, 그 뿌리는 생물체를 자연의 갑";
		PrintFont(explanationLine2, namehFont, nameoldFont, 220, 300, 15, 255, 255, 255);

		char explanationLine3[] = "옷으로 감싸 움직일 수 없게 만듭니다.";
		PrintFont(explanationLine3, namehFont, nameoldFont, 220, 320, 15, 255, 255, 255);
	}

	if (itemName == NAME_SEED_FROST)
	{
		char name[] = "눈꽃송이의 씨앗";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "이 씨앗을 원하는 곳에다 던져 식물을 자라게 할 수 있습니다.";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);

		char explanationLine2[] = "얼음 송이를 건드리면 주변에 차가운 포자를 흩뿌립니다.";
		PrintFont(explanationLine2, namehFont, nameoldFont, 220, 300, 15, 255, 255, 255);

		char explanationLine3[] = "포자의 냉동 효과는 주변 환경이 습할 때 더 강력해집니다.";
		PrintFont(explanationLine3, namehFont, nameoldFont, 220, 320, 15, 255, 255, 255);
	}

	if (itemName == NAME_DEW)
	{
		char name[] = "이슬";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);
	}

	if (itemName == NAME_MONEY)
	{
		char name[] = "돈";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);
	}

	if (itemName == NAME_KEY_IRON)
	{
		char name[] = "쇠 열쇠";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);
	}

	if (itemName == NAME_KEY_SILVER)
	{
		char name[] = "은 열쇠";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);
	}

	if (itemName == NAME_KEY_GOLD)
	{
		char name[] = "금 열쇠";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);
	}
}

void UI::item_sort()
{
}

/*test
void UI::TestFunctin()
{
	char str[] = "폰트테스트";
	HFONT hFont = CreateFont(50, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("궁서"));
	HFONT oldFont = (HFONT)SelectObject(getMemDC(), hFont);
	//TextOut(getMemDC(), 300, 300, str, strlen(str));
	SelectObject(getMemDC(), oldFont);
	DeleteObject(hFont);
}
*/

void UI::PrintFont(char name[], HFONT hFont, HFONT oldFont, int x, int y, int size, char r, char g, char b)
{
	namehFont = CreateFont(size, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("굴림"));
	nameoldFont = (HFONT)SelectObject(getMemDC(), namehFont);
	SetTextColor(getMemDC(), RGB(r, g, b));
	TextOut(getMemDC(), x, y, name, strlen(name));
	SelectObject(getMemDC(), nameoldFont);
	DeleteObject(namehFont);
	SetTextColor(getMemDC(), RGB(0, 0, 0));
}


void UI::cameraSet()
{
	_camera = _player->getPoint();

	//카메라 위치 재조정
	if (_camera.x < WINSIZEX / 2)
	{
		_camera.x = WINSIZEX / 2;
	}
	//else if (_camera.x > IMAGEMANAGER->findImage("bg")->getWidth() - WINSIZEX / 2)
	//{
	//	_camera.x = IMAGEMANAGER->findImage("bg")->getWidth() - WINSIZEX / 2;
	//}
	if (_camera.y < WINSIZEY / 2)
	{
		_camera.y = WINSIZEY / 2;
	}

	//else if (_camera.y > IMAGEMANAGER->findImage("bg")->getHeight() - WINSIZEY / 2)
	//{
	//	_camera.y = IMAGEMANAGER->findImage("bg")->getHeight() - WINSIZEY / 2;
	//}
	_camera.x = WINSIZEX / 2 - _camera.x;
	_camera.y = WINSIZEY / 2 - _camera.y;

}

void UI::LbuttonClickEvnet()
{
	if (_selectInterface == INTERFACEMENU_END)
	{
		//배낭
		if (PtInRect(&_backPackRect, _ptMouse))
		{
			_selectInterface = INTERFACEMENU_BACKPACK;
			_player->setUsingUI(true);

			ResetInventory(); 

			for (int i = 0; i < 24; i++)
			{
				SortInventory();
			}

		}

		//턴 스킵
		if (PtInRect(&_TurnSkipRect, _ptMouse))
		{
			if (_player->getAction() == true)
			{
				_player->endTurn();
			}
		}

		//탐색
		if (PtInRect(&_SearchOptionRect, _ptMouse))
		{
			_selectInterface = INTERFACEMENU_SEARCH;
		}

		//스테이터스
		if (PtInRect(&_StatusRect, _ptMouse))
		{
			_selectInterface = INTERFACEMENU_STATUS;
		}

	}
	else if (_selectInterface != INTERFACEMENU_END)
	{
		if (PtInRect(&_backPackRect, _ptMouse) || PtInRect(&_SearchOptionRect, _ptMouse) || PtInRect(&_TurnSkipRect, _ptMouse) || PtInRect(&_Menu_selectRect, _ptMouse) || PtInRect(&_StatusRect, _ptMouse))
		{
			_selectInterface = INTERFACEMENU_END;
			_player->setUsingUI(false);
			usingui();
		}
	}
	if (_selectInterface != INTERFACEMENU_MENU)
	{
		if (PtInRect(&_Menu_selectRect, _ptMouse))
		{
			_selectInterface = INTERFACEMENU_MENU;
		}
	}


	switch (_selectInterface)
	{
		//배낭
	case INTERFACEMENU_BACKPACK:
		//BackPack();
		for (size_t Line = 0; Line < ARRSIZE; Line++)
		{
			if (PtInRect(&_inventory[Line].inventoryRect, _ptMouse) && _selectItem == NAME_END && _selectInterface == INTERFACEMENU_BACKPACK)
			{
				for (int itemNumber = 0; itemNumber < _im->getvBag().size(); itemNumber++)
				{
					if (_inventory[Line].itemNumber == _im->getvBag()[itemNumber].name)
					{
						_selectItem = _im->getvBag()[itemNumber].name;
						_itemPosition = Line;
						break;
					}
				}
				_interface_button_timer2 = TIMEMANAGER->getWorldTime();
			}
		}
		break;

		//턴스킵
	case INTERFACEMENU_TURNSKIP:
		break;

		//탐색
	case INTERFACEMENU_SEARCH:
		break;

		//메뉴창
	case INTERFACEMENU_MENU:
		//main_menu()
		if (_selectMenu == GAMEMENU_END && !_player->getIsPlayerMoving())
		{
			for (int MenuNumber = 0; MenuNumber < GAMEMENU_END; MenuNumber++)
			{
				if (PtInRect(&_Menu_WindowRect[MenuNumber], _ptMouse) && _selectMenu == GAMEMENU_END)
				{
					_selectMenu = MenuNumber;
				}
			}
		}
		break;

		//스테이터스 창
	case INTERFACEMENU_STATUS:
		//status_window();
		break;
	}
}