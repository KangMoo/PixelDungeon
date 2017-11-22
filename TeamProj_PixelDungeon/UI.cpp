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

	//Ʋ����� �׽�Ʈ
	IMAGEMANAGER->addFrameImage("fream_window1", "Img/UI/fream_window1.bmp", 60, 60, 4, 4, true, RGB(255, 0, 255));

	//����â
	IMAGEMANAGER->addFrameImage("select_menu_bar", "Img/UI/select_menu_bar.bmp", 130, 430, 1, 10, true, RGB(255, 0, 255));

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

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && _selectItem == NAME_END)
	{
		if (PtInRect(&_backPack, _ptMouse) && _selectInterface == INTERFACEMENU_END)
		{
			_selectInterface = INTERFACEMENU_BACKPACK;
		}

		else if (PtInRect(&_backPack, _ptMouse) && _selectInterface == INTERFACEMENU_BACKPACK)
		{
			_selectInterface = INTERFACEMENU_END;
		}
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
}

void UI::BackPack()
{
	IMAGEMANAGER->render("backpack", getMemDC(), WINSIZEX / 2 - (IMAGEMANAGER->findImage("backpack")->getFrameWidth() / 2), WINSIZEY / 2 - (IMAGEMANAGER->findImage("backpack")->getFrameHeight() / 2));

	for (size_t inventoryY = 0; inventoryY < 4; inventoryY++)
	{
		for (size_t inventoryX = 0; inventoryX < 6; inventoryX++)
		{
			/*�׽�Ʈ ����*/
			_inventory[0][4].itemNumber = NAME_OLD_SHORT_SWORD;
			_inventory[0][5].itemNumber = NAME_SHORT_SWORD;
			_inventory[0][6].itemNumber = NAME_SWORD;
			//_inventory[0][1].itemNumber = 2;
			//_inventory[0][2].itemNumber = 3;
			//_inventory[0][3].itemNumber = 4;
			/*�׽�Ʈ ����*/

			int _ix = ((WINSIZEX / 2 - (IMAGEMANAGER->findImage("backpack")->getFrameWidth() / 2)) + 35) + inventoryX * 92;
			int _iy = ((WINSIZEX / 2 - (IMAGEMANAGER->findImage("backpack")->getFrameWidth() / 2)) + 30) + inventoryY * 92;

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

			if (GetAsyncKeyState(VK_LBUTTON) && PtInRect(&_inventory[inventoryY][inventoryX].inventoryRect, _ptMouse) && _selectItem == NAME_END)
			{
				for (int itemNumber = 0; itemNumber < NAME_END; itemNumber++)
				{
					if (_inventory[inventoryY][inventoryX].itemNumber == itemNumber)
						_selectItem = itemNumber;
				}

				IMAGEMANAGER->render("inventorytile", getMemDC(), _inventory[inventoryY][inventoryX].inventoryRect.left, _inventory[inventoryY][inventoryX].inventoryRect.top);
			}

			if (GetAsyncKeyState(VK_RBUTTON) && _selectItem != NAME_END)
			{
				_selectItem = NAME_END;
			}

			if (_inventory[inventoryY][inventoryX].itemNumber != NAME_END)
			{
				_im->getvBag()[_inventory[inventoryY][inventoryX].itemNumber].img->render(getMemDC(), _ix + (90 / 2) - (_im->getvBag()[_inventory[inventoryY][inventoryX].itemNumber].img->getFrameWidth() / 2), _iy + (90 / 2) - (_im->getvBag()[_inventory[inventoryY][inventoryX].itemNumber].img->getFrameHeight() / 2));
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
		case NAME_DEW:
			fream_window_draw(28, 12);
			button_interface(NAME_DEW, TYPE_POTION, 3, 28, 12);
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
		case NAME_FORZEN:
			fream_window_draw(28, 12);
			button_interface(NAME_FORZEN, TYPE_POTION, 3, 28, 12);
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
		case NAME_DEWW:
			fream_window_draw(28, 12);
			button_interface(NAME_DEWW, TYPE_SPECIAL, 3, 28, 12);
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

void UI::button_interface(int itemName, int itemType, int createNumber, int fream_window_sizeX, int fream_window_sizeY, int positionX, int PositionY)
{
	for (int buttonNumber = 0; buttonNumber < createNumber; buttonNumber++)
	{
		if (buttonNumber == 0)
			button_option_value[buttonNumber] = BUTTONOPTION_DROP;

		if (buttonNumber == 1)
			button_option_value[buttonNumber] = BUTTONOPTION_THROW;

		if (itemType == TYPE_WEAPON || itemType == TYPE_ARMOR || itemType == TYPE_ACC)
		{
			if (buttonNumber == 2)
				button_option_value[buttonNumber] = BUTTONOPTION_WEAR;
		}

		if (itemName == NAME_LIOYDS_BEACON && itemType == TYPE_ACC)
		{
			if (buttonNumber == 3)
				button_option_value[buttonNumber] = BUTTONOPTION_LAUNCH;

			if (buttonNumber == 4)
				button_option_value[buttonNumber] = BUTTONOPTION_REMEMBER;
		}

		if (itemType == TYPE_POTION)
		{
			if (buttonNumber == 2)
				button_option_value[buttonNumber] = BUTTONOPTION_DRINK;
		}

		if (itemType == TYPE_SCROLL)
		{
			if (buttonNumber == 2)
				button_option_value[buttonNumber] = BUTTONOPTION_READ;
		}

		if (itemType == TYPE_SEED)
		{
			if (buttonNumber == 2)
				button_option_value[buttonNumber] = BUTTONOPTION_PLANT;
		}

		if (itemType == TYPE_FOOD)
		{
			if (buttonNumber == 2)
				button_option_value[buttonNumber] = BUTTONOPTION_EAT;
		}

		if (itemType == TYPE_WAND)
		{
			if (buttonNumber == 2)
				button_option_value[buttonNumber] = BUTTONOPTION_LAUNCH;
		}

		for (int optioCheck = 0; optioCheck < 10; optioCheck++)
		{
			for (int itemCheck = 0; itemCheck < NAME_END; itemCheck++)
			{
				if (itemName == itemCheck)
				{
					_im->getvBag()[itemName].img->render(getMemDC(), ((WINSIZEX / 2) - (fream_window_sizeX * IMAGEMANAGER->findImage("fream_window1")->getFrameHeight()) / 2) + 30, ((WINSIZEY / 2) - (fream_window_sizeY * IMAGEMANAGER->findImage("fream_window1")->getFrameHeight()) / 2) + 30);
				}
			}

			if (button_option_value[buttonNumber] == optioCheck)
			{
				IMAGEMANAGER->frameRender("select_menu_bar", getMemDC(),
					((WINSIZEX / 2) - ((IMAGEMANAGER->findImage("select_menu_bar")->getFrameWidth() * createNumber) / 2)) + (buttonNumber * IMAGEMANAGER->findImage("select_menu_bar")->getFrameWidth() + ((buttonNumber + 1) * 3)),
					((WINSIZEY / 2) + (fream_window_sizeY * IMAGEMANAGER->findImage("fream_window1")->getFrameHeight()) / 2) - IMAGEMANAGER->findImage("select_menu_bar")->getFrameHeight() - 3,
					0, button_option_value[buttonNumber]);

				button_option_intersectRect[buttonNumber] = RectMake(
					((WINSIZEX / 2) - ((IMAGEMANAGER->findImage("select_menu_bar")->getFrameWidth() * createNumber) / 2)) + (buttonNumber * IMAGEMANAGER->findImage("select_menu_bar")->getFrameWidth() + ((buttonNumber + 1) * 3)),
					((WINSIZEY / 2) + (fream_window_sizeY * IMAGEMANAGER->findImage("fream_window1")->getFrameHeight()) / 2) - IMAGEMANAGER->findImage("select_menu_bar")->getFrameHeight() - 3,
					130, 43);
			}
		}

		if (GetAsyncKeyState(VK_LBUTTON) && PtInRect(&button_option_intersectRect[buttonNumber], _ptMouse))
		{
			//����߸���
			if (button_option_value[buttonNumber] == BUTTONOPTION_DROP)
			{
				_selectItem = NAME_END;
				_selectInterface = INTERFACEMENU_END;
			}
			
			//���Ŵ�
			if (button_option_value[buttonNumber] == BUTTONOPTION_DRINK)
			{
				_selectItem = NAME_END;
				_selectInterface = INTERFACEMENU_END;
			}

			//������
			if (button_option_value[buttonNumber] == BUTTONOPTION_THROW)
			{
				_selectItem = NAME_END;
				_selectInterface = INTERFACEMENU_END;
			}

			//�д´�
			if (button_option_value[buttonNumber] == BUTTONOPTION_READ)
			{
				_selectItem = NAME_END;
				_selectInterface = INTERFACEMENU_END;
			}

			//�߻��Ѵ�
			if (button_option_value[buttonNumber] == BUTTONOPTION_LAUNCH)
			{
				_selectItem = NAME_END;
				_selectInterface = INTERFACEMENU_END;
			}

			//�Դ´�
			if (button_option_value[buttonNumber] == BUTTONOPTION_EAT)
			{
				_selectItem = NAME_END;
				_selectInterface = INTERFACEMENU_END;
			}

			//�ɴ´�
			if (button_option_value[buttonNumber] == BUTTONOPTION_PLANT)
			{
				_selectItem = NAME_END;
				_selectInterface = INTERFACEMENU_END;
			}

			//����Ѵ�
			if (button_option_value[buttonNumber] == BUTTONOPTION_REMEMBER)
			{
				_selectItem = NAME_END;
				_selectInterface = INTERFACEMENU_END;
			}

			//�����Ѵ�
			if (button_option_value[buttonNumber] == BUTTONOPTION_WEAR)
			{
				_inventory[0][0].itemNumber = itemName;
				_inventory[0][4].itemNumber = 0;
				_selectItem = NAME_END;
				_selectInterface = INTERFACEMENU_END;
			}
		}
	}
}

/*test
void UI::TestFunctin()
{
	
}
*/