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

	_backPackRect = RectMake(437, WINSIZEY - IMAGEMANAGER->findImage("toolbar")->getFrameHeight(), 72, (WINSIZEY - IMAGEMANAGER->findImage("toolbar")->getFrameHeight()));
	_SearchOptionRect = RectMake(509, WINSIZEY - IMAGEMANAGER->findImage("toolbar")->getFrameHeight(), 58.5, (WINSIZEY - IMAGEMANAGER->findImage("toolbar")->getFrameHeight()));
	_TurnSkipRect = RectMake(567.5, WINSIZEY - IMAGEMANAGER->findImage("toolbar")->getFrameHeight(), 567.5, (WINSIZEY - IMAGEMANAGER->findImage("toolbar")->getFrameHeight()));

	_Monster_DisplyRect = RectMake(WINSIZEX - IMAGEMANAGER->findImage("Monster_Display")->getFrameWidth(), 40, IMAGEMANAGER->findImage("Monster_Display")->getFrameWidth(), IMAGEMANAGER->findImage("Monster_Display")->getFrameHeight());
	_Special_ButtonRect = RectMake(WINSIZEX - IMAGEMANAGER->findImage("Special_Button")->getFrameWidth(), 380, IMAGEMANAGER->findImage("Special_Button")->getFrameWidth(), IMAGEMANAGER->findImage("Special_Button")->getFrameHeight());
	_Target_ButtonRect = RectMake(WINSIZEX - IMAGEMANAGER->findImage("Target_button")->getFrameWidth(), 460, IMAGEMANAGER->findImage("Target_button")->getFrameWidth(), IMAGEMANAGER->findImage("Target_button")->getFrameHeight());
	
	_interface_button_timer1 = TIMEMANAGER->getWorldTime();
	_interface_button_timer2 = TIMEMANAGER->getWorldTime();
	_interface_button_timer3 = TIMEMANAGER->getWorldTime();

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

	TIMEMANAGER->render(getMemDC());
}

void UI::draw(POINT camera)
{
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
	
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON) && (TIMEMANAGER->getWorldTime() - _interface_button_timer1) > 0.3 && _selectInterface == INTERFACEMENU_END && !_player->getIsPlayerMoving())
	{
		//�賶
		if (PtInRect(&_backPackRect, _ptMouse) && _selectInterface == INTERFACEMENU_END)
		{
			_selectInterface = INTERFACEMENU_BACKPACK;
			_player->setUsingUI(true);

			ResetInventory();

			for (int i = 0; i < 10; i++)
				SortInventory();
		}

		//Ž��
		else if (PtInRect(&_SearchOptionRect, _ptMouse) && _selectInterface == INTERFACEMENU_END)
		{
			if (_player->getAction() == true)
			{
				_player->setAction(false);
			}

			//_selectInterface = INTERFACEMENU_TURNSKIP;
		}

		//�Ͻ�ŵ
		else if (PtInRect(&_TurnSkipRect, _ptMouse) && _selectInterface == INTERFACEMENU_END)
		{
			_selectInterface = INTERFACEMENU_SEARCH;
		}

		_interface_button_timer1 = TIMEMANAGER->getWorldTime();
	}

	else if (KEYMANAGER->isStayKeyDown(VK_LBUTTON) && (TIMEMANAGER->getWorldTime() - _interface_button_timer1) > 0.3 && _selectInterface != INTERFACEMENU_END && !_player->getIsPlayerMoving())
	{
		if (PtInRect(&_backPackRect, _ptMouse) || PtInRect(&_SearchOptionRect, _ptMouse) || PtInRect(&_TurnSkipRect, _ptMouse))
		{
			_selectInterface = INTERFACEMENU_END;
			_player->setUsingUI(false);
		}

		_interface_button_timer1 = TIMEMANAGER->getWorldTime();
	}

	switch (_selectInterface)
	{
		//�賶
		case INTERFACEMENU_BACKPACK:
			BackPack();
			break;
		
		//Ž��
		case INTERFACEMENU_SEARCH:
			break;

		//�Ͻ�ŵ
		case INTERFACEMENU_TURNSKIP:
			break;
	}

	//IMAGEMANAGER->findImage("status_pane")->render(getMemDC(), _status_pane_pos.x, _status_pane_pos.y); //����
	//TIMEMANAGER->render(getMemDC());
}

void UI::ResetInventory()
{
	for (size_t i = 0; i < _im->getvBag().size(); i++)
	{
		if (_im->getvBag()[i].equip == false)
			_inventory[i + 4].itemNumber = _im->getvBag()[i].name;

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

		/*�׽�Ʈ ����*/
		//_inventory[0][4].itemNumber = _im->getvBag()[0].name;
		//_inventory[0][5].itemNumber = _im->getvBag()[1].name;
		//_inventory[1][0].itemNumber = _im->getvBag()[2].name;
		//_inventory[1][1].itemNumber = _im->getvBag()[3].name;
		//_inventory[1][2].itemNumber = _im->getvBag()[4].name;
		//_inventory[1][3].itemNumber = _im->getvBag()[5].name;
		/*�׽�Ʈ ����*/

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

		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON) && PtInRect(&_inventory[Line].inventoryRect, _ptMouse) && (TIMEMANAGER->getWorldTime() - _interface_button_timer2) > 0.3 && _selectItem == NAME_END)
		{
			for (int itemNumber = 0; itemNumber < _im->getvBag().size(); itemNumber++)
			{
				if (_inventory[Line].itemNumber == _im->getvBag()[itemNumber].name)
				{
					_selectItem = _im->getvBag()[itemNumber].name;
					_itemPosition = Line;
				}
			}

			_interface_button_timer2 = TIMEMANAGER->getWorldTime();
		}

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
			button_interface(NAME_LIOYDS_BEACON, TYPE_ACC, 5, 28, 12);
			break;

		//��Ʈ
		case NAME_DART:
			fream_window_draw(28, 12);
			button_interface(NAME_DART, TYPE_THROW, 2, 28, 12);
			break;

		//���� ��Ʈ
		case NAME_PARALYSIS_DART:
			fream_window_draw(28, 12);
			button_interface(NAME_PARALYSIS_DART, TYPE_THROW, 2, 28, 12);
			break;

		//�� ��Ʈ
		case NAME_POISON_DART:
			fream_window_draw(28, 12);
			button_interface(NAME_POISON_DART, TYPE_THROW, 2, 28, 12);
			break;

		//���� �ϵ�
		case NAME_LIGHTNING:
			fream_window_draw(28, 12);
			button_interface(NAME_LIGHTNING, TYPE_WAND, 2, 28, 12);
			break;

		//���� �ϵ�
		case NAME_NORMAL:
			fream_window_draw(28, 12);
			button_interface(NAME_NORMAL, TYPE_WAND, 2, 28, 12);
			break;

		//�� �ϵ�
		case NAME_POISON:
			fream_window_draw(28, 12);
			button_interface(NAME_POISON, TYPE_WAND, 2, 28, 12);
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
			fream_window_draw(28, 12);
			button_interface(NAME_UPGRADE, TYPE_SCROLL, 3, 28, 12);
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
			fream_window_draw(28, 12);
			button_interface(NAME_INVISIBLE, TYPE_POTION, 3, 28, 12);
			break;

		//���� �ξ�
		case NAME_LEVITATION:
			fream_window_draw(28, 12);
			button_interface(NAME_LEVITATION, TYPE_POTION, 3, 28, 12);
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

void UI::fream_window_draw(size_t sizeX, size_t sizeY)
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
				((WINSIZEX / 2) - ((sizeX * IMAGEMANAGER->findImage("fream_window1")->getFrameWidth()) / 2)) + (fream_windowX * IMAGEMANAGER->findImage("fream_window1")->getFrameWidth()), 
				((WINSIZEY / 2) - ((sizeY * IMAGEMANAGER->findImage("fream_window1")->getFrameHeight()) / 2)) + (fream_windowY * IMAGEMANAGER->findImage("fream_window1")->getFrameHeight()), 
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

		if (itemCheck == NAME_LIOYDS_BEACON && itemType == TYPE_ACC)
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
					_player->setAction(false);
				}

				_selectItem = NAME_END;
				_selectInterface = INTERFACEMENU_END;
			}

			//���Ŵ�
			if (button_option_value[buttonNumber].number == BUTTONOPTION_DRINK)
			{
				if (_player->getAction() == true)
				{
					_player->setAction(false);
				}

				_selectItem = NAME_END;
				_selectInterface = INTERFACEMENU_END;
			}

			//������
			if (button_option_value[buttonNumber].number == BUTTONOPTION_THROW)
			{
				if (_player->getAction() == true)
				{
					_player->setAction(false);
				}

				_selectItem = NAME_END;
				_selectInterface = INTERFACEMENU_END;
			}

			//�д´�
			if (button_option_value[buttonNumber].number == BUTTONOPTION_READ)
			{
				if (_player->getAction() == true)
				{
					_player->setAction(false);
				}

				_selectItem = NAME_END;
				_selectInterface = INTERFACEMENU_END;
			}

			//�߻��Ѵ�
			if (button_option_value[buttonNumber].number == BUTTONOPTION_LAUNCH)
			{
				if (_player->getAction() == true)
				{
					_player->setAction(false);
				}

				_selectItem = NAME_END;
				_selectInterface = INTERFACEMENU_END;
			}

			//�Դ´�
			if (button_option_value[buttonNumber].number == BUTTONOPTION_EAT)
			{
				if (_player->getAction() == true)
				{
					_player->action_Eat();
					_player->setAction(false);

					//PLAYERSTAT temp = _player->getStat();
					//temp.exp += 3;
					//_player->setStat(temp);
				}

				_selectItem = NAME_END;
				_selectInterface = INTERFACEMENU_END;
			}

			//�ɴ´�
			if (button_option_value[buttonNumber].number == BUTTONOPTION_PLANT)
			{
				if (_player->getAction() == true)
				{
					_player->setAction(false);
				}

				_selectItem = NAME_END;
				_selectInterface = INTERFACEMENU_END;
			}

			//����Ѵ�
			if (button_option_value[buttonNumber].number == BUTTONOPTION_REMEMBER)
			{
				if (_player->getAction() == true)
				{
					_player->setAction(false);
				}

				_selectItem = NAME_END;
				_selectInterface = INTERFACEMENU_END;
			}

			//�����Ѵ�
			if (button_option_value[buttonNumber].number == BUTTONOPTION_WEAR)
			{
				////������

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

				////��������

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
					_player->setAction(false);
				}

				_selectItem = NAME_END;
				_selectInterface = INTERFACEMENU_END;
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
					_player->setAction(false);
				}

				_selectItem = NAME_END;
				_selectInterface = INTERFACEMENU_END;
			}

			if (button_option_value[buttonNumber].number == BUTTONOPTION_END)
				break;

			_interface_button_timer2 = TIMEMANAGER->getWorldTime();
		}
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