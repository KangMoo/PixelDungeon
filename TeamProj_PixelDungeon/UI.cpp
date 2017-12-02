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

	//Ʋ����� �׽�Ʈ
	IMAGEMANAGER->addFrameImage("fream_window1", "Img/UI/fream_window1.bmp", 60, 60, 4, 4, true, RGB(255, 0, 255));

	//����â
	IMAGEMANAGER->addFrameImage("select_menu_bar", "Img/UI/select_menu_bar.bmp", 130, 430, 1, 10, true, RGB(255, 0, 255));

	//Ÿ�� ��ư
	IMAGEMANAGER->addImage("Target_button", "Img/UI/Target_button.bmp", 70, 75, true, RGB(255, 0, 255));

	//����� ��ư
	IMAGEMANAGER->addImage("Special_Button", "Img/UI/Special_Button.bmp", 70, 75, true, RGB(255, 0, 255));

	//���� ǥ��
	IMAGEMANAGER->addImage("Monster_Display", "Img/UI/Monster_Display.bmp", 70, 48, true, RGB(255, 0, 255));

	//hp��
	IMAGEMANAGER->addImage("hp_bar", "Img/UI/hp_bar.bmp", 192, 12, true, RGB(255, 0, 255));

	//���θ޴���
	IMAGEMANAGER->addImage("select_menu_bar2", "Img/UI/select_menu_bar2.bmp", 260, 129, true, RGB(255, 0, 255));

	//Ÿ�� ����
	IMAGEMANAGER->addImage("tile_select", "Img/UI/tile_select.bmp", 32, 32, true, RGB(255, 0, 255));

	//��Ʈ
	IMAGEMANAGER->addFrameImage("font", "Img/UI/numberfont.bmp", 130, 19, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("font_green", "Img/UI/numberfontgreen.bmp", 130, 19, 10, 1, true, RGB(255, 0, 255)); //�׸�
	IMAGEMANAGER->addFrameImage("special_font", "Img/UI/specialfont.bmp", 36, 19, 3, 1, true, RGB(255, 0, 255)); //Ư������

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

	//if (/*���Ͱ� ��ó�� �����ÿ� ǥ��*/)
	IMAGEMANAGER->render("Monster_Display", getMemDC(), WINSIZEX - IMAGEMANAGER->findImage("Monster_Display")->getFrameWidth(), 40);
	//Rectangle(getMemDC(), WINSIZEX - IMAGEMANAGER->findImage("Monster_Display")->getFrameWidth(), 40, (WINSIZEX - IMAGEMANAGER->findImage("Monster_Display")->getFrameWidth()) + IMAGEMANAGER->findImage("Monster_Display")->getFrameWidth(), 40 + IMAGEMANAGER->findImage("Monster_Display")->getFrameHeight());

//if (/*�÷��̾ Ư�� �������� �����ϰ� ������*/)
	IMAGEMANAGER->render("Special_Button", getMemDC(), WINSIZEX - IMAGEMANAGER->findImage("Special_Button")->getFrameWidth(), 380);
	//Rectangle(getMemDC(), WINSIZEX - IMAGEMANAGER->findImage("Special_Button")->getFrameWidth(), 380, (WINSIZEX - IMAGEMANAGER->findImage("Special_Button")->getFrameWidth()) + IMAGEMANAGER->findImage("Special_Button")->getFrameWidth(), 380 + IMAGEMANAGER->findImage("Special_Button")->getFrameHeight());

//if (/*���Ͱ� ��ó�� ������*/)
	IMAGEMANAGER->render("Target_button", getMemDC(), WINSIZEX - IMAGEMANAGER->findImage("Target_button")->getFrameWidth(), 460);
	//Rectangle(getMemDC(), WINSIZEX - IMAGEMANAGER->findImage("Target_button")->getFrameWidth(), 460, (WINSIZEX - IMAGEMANAGER->findImage("Target_button")->getFrameWidth()) + IMAGEMANAGER->findImage("Target_button")->getFrameWidth(), 460 + IMAGEMANAGER->findImage("Target_button")->getFrameHeight());


//Rectangle(getMemDC(), 5, 5, 85,88);



	//
	//if (KEYMANAGER->isStayKeyDown(VK_LBUTTON) && (TIMEMANAGER->getWorldTime() - _interface_button_timer1) > 0.3 && _selectInterface == INTERFACEMENU_END && !_player->getIsPlayerMoving())
	//{
	//	//�賶
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
	//	//Ž��
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
	//	//�Ͻ�ŵ
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
		//�賶
	case INTERFACEMENU_BACKPACK:
		BackPack();
		break;

		//�Ͻ�ŵ
	case INTERFACEMENU_TURNSKIP:
		break;

		//Ž��
	case INTERFACEMENU_SEARCH:
		search();
		break;

		//�޴�â
	case INTERFACEMENU_MENU:
		main_menu();
		break;

		//�������ͽ� â
	case INTERFACEMENU_STATUS:
		status_window();
		break;
	}

	if (throwcheck)
		throw_interface();

	if (isscroll == true)
		read_interface();

	//IMAGEMANAGER->findImage("status_pane")->render(getMemDC(), _status_pane_pos.x, _status_pane_pos.y); //����
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
		SCENEMANAGER->changeScene("���θ޴���");
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

	char name[] = "���� ���� ����";
	PrintFont(name, namehFont, nameoldFont, 350, 190, 25, 0, 255, 0);

	char str[] = "��";
	PrintFont(str, namehFont, nameoldFont, 300, 250, 18, 255, 255, 255);

	char health[] = "ü��";
	PrintFont(health, namehFont, nameoldFont, 300, 280, 18, 255, 255, 255);

	char ex[] = "����ġ";
	PrintFont(ex, namehFont, nameoldFont, 300, 310, 18, 255, 255, 255);

	char gold[] = "ȹ���� ���";
	PrintFont(gold, namehFont, nameoldFont, 300, 380, 18, 255, 255, 255);

	char level[] = "�ְ� ����";
	PrintFont(level, namehFont, nameoldFont, 300, 410, 18, 255, 255, 255);
}

void UI::search()
{
	fream_window_draw(18, 4, 0, 170);

	char name[] = "Ž�� ������ �����Ͻÿ�";
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
		char name[] = "���� ������ �����Ͻÿ�";
		PrintFont(name, namehFont, nameoldFont, 290, 468, 18, 0, 255, 0);
	}

	if (islaunch)
	{
		fream_window_draw(19, 4, 0, 170);
		char name[] = "�߻��� ������ �����Ͻÿ�";
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
		char name[] = "������ �������� �����Ͻÿ�";
		PrintFont(name, namehFont, nameoldFont, 280, 468, 18, 0, 255, 0);
	}

	if (isUpgrad)
	{
		fream_window_draw(19, 4, 0, 170);
		char name[] = "��ȭ�� �������� �����Ͻÿ�";
		PrintFont(name, namehFont, nameoldFont, 280, 468, 18, 0, 255, 0);
	}

	if (ispurify)
	{
		fream_window_draw(19, 4, 0, 170);
		char name[] = "��ȭ�� �������� �����Ͻÿ�";
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

				//��Ʈ
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
	NAME_OLD_SHORT_SWORD,	//���� �Ұ�	============ �� �� ==========
	NAME_SHORT_SWORD,		//�Ұ�
	NAME_SWORD,				//��
	NAME_SPEAR,				//â
	NAME_BATTLE_AXE,		//���� ����
	NAME_CLOTH,				//�Ϲ� ��	============ �� �� �� =======
	NAME_LEATHER,			//�氩
	NAME_MAIL,				//�߰�
	NAME_RING_POWER,		//���� ����	============ �� �� ==========
	NAME_RING_RECHARGE,		//���� ����
	NAME_LIOYDS_BEACON,		//�ϵ�
	NAME_DART,				//��Ʈ		============ �� ô ==========
	NAME_PARALYSIS_DART,	//���� ��Ʈ
	NAME_POISON_DART,		//�� ��Ʈ
	NAME_LIGHTNING,			//���� �ϵ�	============ �� �� ==========
	NAME_NORMAL,			//���� �ϵ�
	NAME_POISON,			//�� �ϵ�
	NAME_EMERGENCY,			//���ķ�	============ �� ��===========
	NAME_PASTY,				//�Ľ�Ƽ
	NAME_UNKNOWN_MEAT,		//�˼����� ���
	NAME_COOKED_MEAT,		//�������
	NAME_FROZEN_MEAT,		//�� ���
	NAME_IDENTIFY,			//Ȯ��		============ �� �� �� =======
	NAME_UPGRADE,			//��ȭ
	NAME_PURIFY,			//��ȭ
	NAME_MAP,				//����
	NAME_RECHARGE,			//������
	NAME_DEW,				//�̽�		============ �� �� ==========
	NAME_HEAL,				//ȸ��
	NAME_STR,				//��
	NAME_EX,				//���õ�
	NAME_INVISIBLE,			//����ȭ
	NAME_LEVITATION,		//���ߺξ�
	NAME_FORZEN,			//����
	NAME_LIQUID_FIRE,		//��ü ȭ��
	NAME_SEED_HEAL,			//ġ��		============ �� �� ==========
	NAME_SEED_FIRE,			//ȭ����
	NAME_SEED_SNAKE,		//��Ѹ�
	NAME_SEED_FROST,		//����
	NAME_DEWW				//�̽�		============ Ư �� ==========
	*/

	switch (_selectItem)
	{
		//���� �Ұ�
	case NAME_OLD_SHORT_SWORD:
		fream_window_draw(28, 12);
		button_interface(NAME_OLD_SHORT_SWORD, TYPE_WEAPON, 3, 28, 12);

		//char str[] = "��Ʈ�׽�Ʈ";
		//HFONT hFont = CreateFont(50, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("����"));
		//HFONT oldFont = (HFONT)SelectObject(getMemDC(), hFont);
		////TextOut(getMemDC(), 300, 300, str, strlen(str));
		//SelectObject(getMemDC(), oldFont);
		//DeleteObject(hFont);

		break;

		//�Ұ�
	case NAME_SHORT_SWORD:
		fream_window_draw(28, 12);
		button_interface(NAME_SHORT_SWORD, TYPE_WEAPON, 3, 28, 12);
		break;

		//��
	case NAME_SWORD:
		fream_window_draw(28, 12);
		button_interface(NAME_SWORD, TYPE_WEAPON, 3, 28, 12);
		break;

		//â
	case NAME_SPEAR:
		fream_window_draw(28, 12);
		button_interface(NAME_SPEAR, TYPE_WEAPON, 3, 28, 12);
		break;

		//���� ����
	case NAME_BATTLE_AXE:
		fream_window_draw(28, 12);
		button_interface(NAME_BATTLE_AXE, TYPE_WEAPON, 3, 28, 12);
		break;

		//�Ϲ� ��
	case NAME_CLOTH:
		fream_window_draw(28, 12);
		button_interface(NAME_CLOTH, TYPE_ARMOR, 3, 28, 12);
		break;

		//�氩
	case NAME_LEATHER:
		fream_window_draw(28, 12);
		button_interface(NAME_LEATHER, TYPE_ARMOR, 3, 28, 12);
		break;

		//�߰�
	case NAME_MAIL:
		fream_window_draw(28, 12);
		button_interface(NAME_MAIL, TYPE_ARMOR, 3, 28, 12);
		break;

		//���� ����
	case NAME_RING_POWER:
		fream_window_draw(28, 12);
		button_interface(NAME_RING_POWER, TYPE_ACC, 3, 28, 12);
		break;

		//���� ����
	case NAME_RING_RECHARGE:
		fream_window_draw(28, 12);
		button_interface(NAME_RING_RECHARGE, TYPE_ACC, 3, 28, 12);
		break;

		//�ϵ�
	case NAME_LIOYDS_BEACON:
		fream_window_draw(47, 12);
		button_interface(NAME_LIOYDS_BEACON, TYPE_ACC, 5, 47, 12);
		break;

		//��Ʈ
	case NAME_DART:
		fream_window_draw(28, 12);
		button_interface(NAME_DART, TYPE_THROW, 3, 28, 12);
		break;

		//���� ��Ʈ
	case NAME_PARALYSIS_DART:
		fream_window_draw(28, 12);
		button_interface(NAME_PARALYSIS_DART, TYPE_THROW, 3, 28, 12);
		break;

		//�� ��Ʈ
	case NAME_POISON_DART:
		fream_window_draw(28, 12);
		button_interface(NAME_POISON_DART, TYPE_THROW, 3, 28, 12);
		break;

		//���� �ϵ�
	case NAME_LIGHTNING:
		fream_window_draw(28, 12);
		button_interface(NAME_LIGHTNING, TYPE_WAND, 3, 28, 12);
		break;

		//���� �ϵ�
	case NAME_NORMAL:
		fream_window_draw(28, 12);
		button_interface(NAME_NORMAL, TYPE_WAND, 3, 28, 12);
		break;

		//�� �ϵ�
	case NAME_POISON:
		fream_window_draw(28, 12);
		button_interface(NAME_POISON, TYPE_WAND, 3, 28, 12);
		break;

		//���ķ�
	case NAME_EMERGENCY:
		fream_window_draw(28, 12);
		button_interface(NAME_EMERGENCY, TYPE_FOOD, 3, 28, 12);
		break;

		//�Ľ�Ƽ
	case NAME_PASTY:
		fream_window_draw(28, 12);
		button_interface(NAME_PASTY, TYPE_FOOD, 3, 28, 12);
		break;

		//�˼����� ���
	case NAME_UNKNOWN_MEAT:
		fream_window_draw(28, 12);
		button_interface(NAME_UNKNOWN_MEAT, TYPE_FOOD, 3, 28, 12);
		break;

		//���� ���
	case NAME_COOKED_MEAT:
		fream_window_draw(28, 12);
		button_interface(NAME_COOKED_MEAT, TYPE_FOOD, 3, 28, 12);
		break;

		//�� ���
	case NAME_FROZEN_MEAT:
		fream_window_draw(28, 12);
		button_interface(NAME_FROZEN_MEAT, TYPE_FOOD, 3, 28, 12);
		break;

		//Ȯ��
	case NAME_IDENTIFY:
		fream_window_draw(28, 12);
		button_interface(NAME_IDENTIFY, TYPE_SCROLL, 3, 28, 12);
		break;

		//��ȭ
	case NAME_UPGRADE:
		fream_window_draw(28, 20);
		button_interface(NAME_UPGRADE, TYPE_SCROLL, 3, 28, 20);
		break;

		//��ȭ
	case NAME_PURIFY:
		fream_window_draw(28, 12);
		button_interface(NAME_PURIFY, TYPE_SCROLL, 3, 28, 12);
		break;

		//����
	case NAME_MAP:
		fream_window_draw(28, 12);
		button_interface(NAME_MAP, TYPE_SCROLL, 3, 28, 12);
		break;

		//������
	case NAME_RECHARGE:
		fream_window_draw(28, 12);
		button_interface(NAME_RECHARGE, TYPE_SCROLL, 3, 28, 12);
		break;

		//�̽�
	case NAME_BOTTLE:
		fream_window_draw(28, 12);
		button_interface(NAME_BOTTLE, TYPE_POTION, 3, 28, 12);
		break;

		//ȸ��
	case NAME_HEAL:
		fream_window_draw(28, 12);
		button_interface(NAME_HEAL, TYPE_POTION, 3, 28, 12);
		break;

		//��
	case NAME_STR:
		fream_window_draw(28, 12);
		button_interface(NAME_STR, TYPE_POTION, 3, 28, 12);
		break;

		//���õ�
	case NAME_EX:
		fream_window_draw(28, 12);
		button_interface(NAME_EX, TYPE_POTION, 3, 28, 12);
		break;

		//����ȭ
	case NAME_INVISIBLE:
		fream_window_draw(28, 15);
		button_interface(NAME_INVISIBLE, TYPE_POTION, 3, 28, 15);
		break;

		//���� �ξ�
	case NAME_LEVITATION:
		fream_window_draw(28, 15);
		button_interface(NAME_LEVITATION, TYPE_POTION, 3, 28, 15);
		break;

		//����
	case NAME_FROZEN:
		fream_window_draw(28, 12);
		button_interface(NAME_FROZEN, TYPE_POTION, 3, 28, 12);
		break;

		//��ü ȭ��
	case NAME_LIQUID_FIRE:
		fream_window_draw(28, 12);
		button_interface(NAME_LIQUID_FIRE, TYPE_POTION, 3, 28, 12);
		break;

		//ġ��
	case NAME_SEED_HEAL:
		fream_window_draw(28, 12);
		button_interface(NAME_SEED_HEAL, TYPE_SEED, 3, 28, 12);
		break;

		//ȭ����
	case NAME_SEED_FIRE:
		fream_window_draw(28, 12);
		button_interface(NAME_SEED_FIRE, TYPE_SEED, 3, 28, 12);
		break;

		//��Ѹ�
	case NAME_SEED_SNAKE:
		fream_window_draw(28, 12);
		button_interface(NAME_SEED_SNAKE, TYPE_SEED, 3, 28, 12);
		break;

		//����
	case NAME_SEED_FROST:
		fream_window_draw(28, 12);
		button_interface(NAME_SEED_FROST, TYPE_SEED, 3, 28, 12);
		break;

		//�̽�
	case NAME_DEW:
		fream_window_draw(28, 12);
		button_interface(NAME_DEW, TYPE_SPECIAL, 3, 28, 12);
		break;

		//����
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
			//����߸���
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

			//���Ŵ�
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

			//������
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

			//�д´�
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

			//�߻��Ѵ�
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

			//�Դ´�
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

			//�ɴ´�
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

			//����Ѵ�
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

			//�����Ѵ�
			if (button_option_value[buttonNumber].number == BUTTONOPTION_WEAR)
			{
				//������

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

				//��������

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

			//�����Ѵ�
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
		char name[] = "���� �Ұ�";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "�� ������ ������ �⺻���� ��ȣ�� �����մϴ�.";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);

		char explanationLine2[] = "���� �Ұ˺��� ������ ���ظ� �� �����ϴ�.";
		PrintFont(explanationLine2, namehFont, nameoldFont, 220, 300, 15, 255, 255, 255);
	}

	if (itemName == NAME_SHORT_SWORD)
	{
		char name[] = "�Ұ�";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "�� ����� �ܰ˺��� �ܿ� �ѵ� �� ���� �� ���⿡ �Ұ���";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);

		char explanationLine2[] = "�ϴ�.";
		PrintFont(explanationLine2, namehFont, nameoldFont, 220, 300, 15, 255, 255, 255);
	}

	if (itemName == NAME_SWORD)
	{
		char name[] = "��";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "������ �������� ���Դϴ�.";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);

		char explanationLine2[] = "�ʹ� ũ���� ������, Ȯ���� �Ұ˺��ٴ� Ů�ϴ�.";
		PrintFont(explanationLine2, namehFont, nameoldFont, 220, 300, 15, 255, 255, 255);
	}

	if (itemName == NAME_SPEAR)
	{
		char name[] = "â";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "������ ������ ���� ��ī�ο� �谡 �پ��ֽ��ϴ�.";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);
	}

	if (itemName == NAME_BATTLE_AXE)
	{
		char name[] = "���� ����";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);
	}

	if (itemName == NAME_CLOTH)
	{
		char name[] = "õ ����";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "�� ������ ������ �⺻���� ��ȣ�� �����մϴ�.";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);
	}

	if (itemName == NAME_LEATHER)
	{
		char name[] = "���� ����";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "�������� ������ �������� ���� �����Դϴ�.";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);

		char explanationLine2[] = "õ ���� ��ŭ �������� ������ �ξ� �� ���� ��ȣ ȿ����";
		PrintFont(explanationLine2, namehFont, nameoldFont, 220, 300, 15, 255, 255, 255);

		char explanationLine3[] = "������ �ݴϴ�.";
		PrintFont(explanationLine3, namehFont, nameoldFont, 220, 320, 15, 255, 255, 255);
	}

	if (itemName == NAME_MAIL)
	{
		char name[] = "�罽 ����";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "�� ���� ���� ���� ���� �������� �ܴ������� ������";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);

		char explanationLine2[] = "�����Դϴ�.";
		PrintFont(explanationLine2, namehFont, nameoldFont, 220, 300, 15, 255, 255, 255);
	}

	if (itemName == NAME_RING_POWER)
	{
		char name[] = "���� ����";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);
	}

	if (itemName == NAME_RING_RECHARGE)
	{
		char name[] = "���� ����";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);
	}

	if (itemName == NAME_LIOYDS_BEACON)
	{
		char name[] = "���̵��� ��ȣ��";
		PrintFont(name, namehFont, nameoldFont, 120, 245, 25, 255, 255, 0);

		char explanation[] = "���̵��� ��ȣ��� ����ڿ��� �����̵� ������ ������ �� �ִ� ������ ���� ��ġ�Դϴ�.";
		PrintFont(explanation, namehFont, nameoldFont, 70, 280, 15, 255, 255, 255);

		char explanationLine2[] = "��ȣ�⿡ ���ϴ� ��ġ�� ��� ���� ���ư����� ������, ����� ���¿��� �������� �Ҹ��Ͽ� ������ ��";
		PrintFont(explanationLine2, namehFont, nameoldFont, 70, 300, 15, 255, 255, 255);

		char explanationLine3[] = "���̵� ������ �߻��� �� �ֽ��ϴ�. �� ������ ��󿡰� ����ϰų� �ڽſ��Ե� ����� �� �ֽ��ϴ�.";
		PrintFont(explanationLine3, namehFont, nameoldFont, 70, 320, 15, 255, 255, 255);
	}

	if (itemName == NAME_DART)
	{
		char name[] = "��Ʈ";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);
	}

	if (itemName == NAME_PARALYSIS_DART)
	{
		char name[] = "���� ��Ʈ";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);
	}

	if (itemName == NAME_POISON_DART)
	{
		char name[] = "�� ��Ʈ";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);
	}

	if (itemName == NAME_LIGHTNING)
	{
		char name[] = "���� �ϵ�";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);
	}

	if (itemName == NAME_NORMAL)
	{
		char name[] = "���� ����";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "�� ����� ���̴� ����� ������ ���� �������� �߻��մϴ�.";
		PrintFont(explanation, namehFont, nameoldFont, 210, 280, 15, 255, 255, 255);

		char explanationLine2[] = "�ٸ� ���뿡 ���ؼ� �������� ������, �׿� ���� �� ���� ��";
		PrintFont(explanationLine2, namehFont, nameoldFont, 210, 300, 15, 255, 255, 255);

		char explanationLine3[] = "������ �����ϴ�.";
		PrintFont(explanationLine3, namehFont, nameoldFont, 210, 320, 15, 255, 255, 255);
	}

	if (itemName == NAME_POISON)
	{
		char name[] = "�� �ϵ�";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);
	}

	if (itemName == NAME_EMERGENCY)
	{
		char name[] = "��� �ķ�";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);
	}

	if (itemName == NAME_PASTY)
	{
		char name[] = "�Ľ�Ƽ";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);
	}

	if (itemName == NAME_UNKNOWN_MEAT)
	{
		char name[] = "�˼����� ���";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);
	}

	if (itemName == NAME_COOKED_MEAT)
	{
		char name[] = "�������";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);
	}

	if (itemName == NAME_FROZEN_MEAT)
	{
		char name[] = "�󸰰��";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);
	}

	if (itemName == NAME_IDENTIFY)
	{
		char name[] = "������ �ֹ���";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "�� �ֹ����� �ϳ��� �������� ����� ���������� �巯��";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);

		char explanationLine2[] = "�ϴ�.";
		PrintFont(explanationLine2, namehFont, nameoldFont, 220, 300, 15, 255, 255, 255);
	}

	if (itemName == NAME_UPGRADE)
	{
		char name[] = "��ȭ�� �ֹ���";
		PrintFont(name, namehFont, nameoldFont, 260, 185, 25, 255, 255, 0);

		char explanation[] = "�� �ֹ����� �ϳ��� �������� ��ȭ�Ͽ� ǰ���� �����ϴ�.";
		PrintFont(explanation, namehFont, nameoldFont, 210, 220, 15, 255, 255, 255);

		char explanationLine2[] = "���� ����� �� ���������� ���� Ƚ���� �����ϸ�, �����";
		PrintFont(explanationLine2, namehFont, nameoldFont, 210, 240, 15, 255, 255, 255);

		char explanationLine3[] = "�� ���� ���ظ� �� �� �ְ�, ���� ���ظ� �� �� ��� ";
		PrintFont(explanationLine3, namehFont, nameoldFont, 210, 260, 15, 255, 255, 255);

		char explanationLine4[] = "�ϰԵ˴ϴ�. ���� ������ �����ڿ��� �־����� ȿ���� ��";
		PrintFont(explanationLine4, namehFont, nameoldFont, 210, 280, 15, 255, 255, 255);

		char explanationLine5[] = "��ȭ�մϴ�. ����� ������ ���� �����ϴ� �� �ʿ��� ����";
		PrintFont(explanationLine5, namehFont, nameoldFont, 210, 300, 15, 255, 255, 255);

		char explanationLine6[] = "���� ���ҽ�Ű��, ���������� �ֹ������ٴ� �������� ����";
		PrintFont(explanationLine6, namehFont, nameoldFont, 210, 320, 15, 255, 255, 255);

		char explanationLine7[] = "�ۿ� �ɸ� ���ָ� ��ȭ��ų ���� �ֽ��ϴ�.";
		PrintFont(explanationLine7, namehFont, nameoldFont, 210, 340, 15, 255, 255, 255);
	}

	if (itemName == NAME_PURIFY)
	{
		char name[] = "���� ������ �ֹ���";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "�� �ֹ����� ��� ������ ������� ����, ����, ������, ��";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);

		char explanationLine2[] = "���� ��� ���ָ� ��� �����մϴ�.";
		PrintFont(explanationLine2, namehFont, nameoldFont, 220, 300, 15, 255, 255, 255);
	}

	if (itemName == NAME_MAP)
	{
		char name[] = "���� ������ �ֹ���";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "�� �ֹ����� ������, �������� ���� ������ ��￡ ���ε�";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);

		char explanationLine2[] = "��, ���� ���� ��� ����� ������ ������ �巯���� �մ�";
		PrintFont(explanationLine2, namehFont, nameoldFont, 220, 300, 15, 255, 255, 255);

		char explanationLine3[] = "��. �����۰� ����ü���� ��ġ�� ������ �� �� �����ϴ�.";
		PrintFont(explanationLine3, namehFont, nameoldFont, 220, 320, 15, 255, 255, 255);
	}

	if (itemName == NAME_RECHARGE)
	{
		char name[] = "������ �ֹ���";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "�� �ֹ����� ��� �ִ� �״���� ������ Ǯ���� �� �����";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);

		char explanationLine2[] = "�� ���� ���븦 ������ ������ŵ�ϴ�.";
		PrintFont(explanationLine2, namehFont, nameoldFont, 220, 300, 15, 255, 255, 255);
	}

	if (itemName == NAME_BOTTLE)
	{
		char name[] = "�̽�";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);
	}

	if (itemName == NAME_HEAL)
	{
		char name[] = "ġ�� ����";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "�� ȸ������ ü���� �޼ӵ��� ȸ����Ű�� ���� ���� �̻�";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);

		char explanationLine2[] = "�� ġ���մϴ�.";
		PrintFont(explanationLine2, namehFont, nameoldFont, 220, 300, 15, 255, 255, 255);
	}

	if (itemName == NAME_STR)
	{
		char name[] = "���� ����";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "�� ������ ����� ����� ������ Ÿ�� �귯, ����� ����";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);

		char explanationLine2[] = "1��ŭ ���������� �ø��ϴ�.";
		PrintFont(explanationLine2, namehFont, nameoldFont, 220, 300, 15, 255, 255, 255);
	}

	if (itemName == NAME_EX)
	{
		char name[] = "������ ����";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "���� ������� ������ ���� �̾߱⸦ ��ü�� ���� ���̸�,";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);

		char explanationLine2[] = "�� ������ ���ô� ��� ����� ���� ������ �ø� ���Դϴ�.";
		PrintFont(explanationLine2, namehFont, nameoldFont, 220, 300, 15, 255, 255, 255);
	}

	if (itemName == NAME_INVISIBLE)
	{
		char name[] = "����ȭ�� ����";
		PrintFont(name, namehFont, nameoldFont, 260, 225, 25, 255, 255, 0);

		char explanation[] = "�� ������ ���ø� �Ͻ������� ���������ϴ�.";
		PrintFont(explanation, namehFont, nameoldFont, 220, 260, 15, 255, 255, 255);

		char explanationLine2[] = "�������� ���¿����� ������ ����� �� �� �����ϴ�.";
		PrintFont(explanationLine2, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);

		char explanationLine3[] = "���� �����ϰų�, ���� ���븦 ����ϰų�, �� �տ��� ��";
		PrintFont(explanationLine3, namehFont, nameoldFont, 220, 300, 15, 255, 255, 255);

		char explanationLine4[] = "�� �ֹ����� ����ϸ� ���� ȿ���� ������ϴ�.";
		PrintFont(explanationLine4, namehFont, nameoldFont, 220, 320, 15, 255, 255, 255);
	}

	if (itemName == NAME_LEVITATION)
	{
		char name[] = "������ ����";
		PrintFont(name, namehFont, nameoldFont, 260, 225, 25, 255, 255, 0);

		char explanation[] = "�� ȣ����� �ھƳ��� ������ ���ø� �������� ��������";
		PrintFont(explanation, namehFont, nameoldFont, 220, 260, 15, 255, 255, 255);

		char explanationLine2[] = "�˴ϴ�. ����� ������ �� ����� ���� ���ٴ� �� ������";
		PrintFont(explanationLine2, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);

		char explanationLine3[] = "������ �����̸� �Ѿ�ٴ� �� �ֽ��ϴ�.������ ������ ��";
		PrintFont(explanationLine3, namehFont, nameoldFont, 220, 300, 15, 255, 255, 255);

		char explanationLine4[] = "�� ���� ���� ������ ���վ� ������ ���̸��� ����� ����";
		PrintFont(explanationLine4, namehFont, nameoldFont, 220, 320, 15, 255, 255, 255);

		char explanationLine5[] = "������ ��ǽ�ŵ�ϴ�.";
		PrintFont(explanationLine5, namehFont, nameoldFont, 220, 340, 15, 255, 255, 255);
	}

	if (itemName == NAME_FROZEN)
	{
		char name[] = "������ ����";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "�� ȭ�չ��� ���⿡ ��� ��� ������ �������� ��ȭ�մ�";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);

		char explanationLine2[] = "��.";
		PrintFont(explanationLine2, namehFont, nameoldFont, 220, 300, 15, 255, 255, 255);
	}

	if (itemName == NAME_LIQUID_FIRE)
	{
		char name[] = "��ü ȭ�� ����";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "�� ������ �Ҿ����� ȭ�չ��� ���� �� �־� ����� ������";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);

		char explanationLine2[] = "�ް��� ������ ����Ű�� �ֺ��� �ҷ� �����ϴ�.";
		PrintFont(explanationLine2, namehFont, nameoldFont, 220, 300, 15, 255, 255, 255);
	}

	if (itemName == NAME_SEED_HEAL)
	{
		char name[] = "ġ��";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);
	}

	if (itemName == NAME_SEED_FIRE)
	{
		char name[] = "ȭ������ ����";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "�� ������ ���ϴ� ������ ���� �Ĺ��� �ڶ�� �� �� �ֽ���";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);

		char explanationLine2[] = "��. ���𰡰� ȭ���ʸ� �ǵ帮�� �Ǹ� �����Ͽ� �ֺ��� ��";
		PrintFont(explanationLine2, namehFont, nameoldFont, 220, 300, 15, 255, 255, 255);

		char explanationLine3[] = "������ �ڵ����ϴ�.";
		PrintFont(explanationLine3, namehFont, nameoldFont, 220, 320, 15, 255, 255, 255);
	}

	if (itemName == NAME_SEED_SNAKE)
	{
		char name[] = "��Ѹ��� ����";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "�� ������ ���ϴ� ������ ���� �Ĺ��� �ڶ�� �� �� �ֽ��ϴ�.";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);

		char explanationLine2[] = "����ü�� ��Ѹ��� �ǵ帮��, �� �Ѹ��� ����ü�� �ڿ��� ��";
		PrintFont(explanationLine2, namehFont, nameoldFont, 220, 300, 15, 255, 255, 255);

		char explanationLine3[] = "������ ���� ������ �� ���� ����ϴ�.";
		PrintFont(explanationLine3, namehFont, nameoldFont, 220, 320, 15, 255, 255, 255);
	}

	if (itemName == NAME_SEED_FROST)
	{
		char name[] = "���ɼ����� ����";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "�� ������ ���ϴ� ������ ���� �Ĺ��� �ڶ�� �� �� �ֽ��ϴ�.";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);

		char explanationLine2[] = "���� ���̸� �ǵ帮�� �ֺ��� ������ ���ڸ� ��Ѹ��ϴ�.";
		PrintFont(explanationLine2, namehFont, nameoldFont, 220, 300, 15, 255, 255, 255);

		char explanationLine3[] = "������ �õ� ȿ���� �ֺ� ȯ���� ���� �� �� ���������ϴ�.";
		PrintFont(explanationLine3, namehFont, nameoldFont, 220, 320, 15, 255, 255, 255);
	}

	if (itemName == NAME_DEW)
	{
		char name[] = "�̽�";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);
	}

	if (itemName == NAME_MONEY)
	{
		char name[] = "��";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);
	}

	if (itemName == NAME_KEY_IRON)
	{
		char name[] = "�� ����";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);
	}

	if (itemName == NAME_KEY_SILVER)
	{
		char name[] = "�� ����";
		PrintFont(name, namehFont, nameoldFont, 260, 245, 25, 255, 255, 0);

		char explanation[] = "";
		PrintFont(explanation, namehFont, nameoldFont, 220, 280, 15, 255, 255, 255);
	}

	if (itemName == NAME_KEY_GOLD)
	{
		char name[] = "�� ����";
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
	char str[] = "��Ʈ�׽�Ʈ";
	HFONT hFont = CreateFont(50, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("�ü�"));
	HFONT oldFont = (HFONT)SelectObject(getMemDC(), hFont);
	//TextOut(getMemDC(), 300, 300, str, strlen(str));
	SelectObject(getMemDC(), oldFont);
	DeleteObject(hFont);
}
*/

void UI::PrintFont(char name[], HFONT hFont, HFONT oldFont, int x, int y, int size, char r, char g, char b)
{
	namehFont = CreateFont(size, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("����"));
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

	//ī�޶� ��ġ ������
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
		//�賶
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

		//�� ��ŵ
		if (PtInRect(&_TurnSkipRect, _ptMouse))
		{
			if (_player->getAction() == true)
			{
				_player->endTurn();
			}
		}

		//Ž��
		if (PtInRect(&_SearchOptionRect, _ptMouse))
		{
			_selectInterface = INTERFACEMENU_SEARCH;
		}

		//�������ͽ�
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
		//�賶
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

		//�Ͻ�ŵ
	case INTERFACEMENU_TURNSKIP:
		break;

		//Ž��
	case INTERFACEMENU_SEARCH:
		break;

		//�޴�â
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

		//�������ͽ� â
	case INTERFACEMENU_STATUS:
		//status_window();
		break;
	}
}