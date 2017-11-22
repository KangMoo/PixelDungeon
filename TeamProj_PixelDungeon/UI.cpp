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

	//틀만들기 테스트
	IMAGEMANAGER->addFrameImage("fream_window1", "Img/UI/fream_window1.bmp", 60, 60, 4, 4, true, RGB(255, 0, 255));

	//선택창
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
		//배낭
		case INTERFACEMENU_BACKPACK:
			BackPack();
			break;
		
		//탐색
		case INTERFACEMENU_SEARCH:
			break;

		//턴스킵
		case INTERFACEMENU_TURNSKIP:
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
			_inventory[0][4].itemNumber = NAME_OLD_SHORT_SWORD;
			_inventory[0][5].itemNumber = NAME_SHORT_SWORD;
			_inventory[0][6].itemNumber = NAME_SWORD;
			//_inventory[0][1].itemNumber = 2;
			//_inventory[0][2].itemNumber = 3;
			//_inventory[0][3].itemNumber = 4;
			/*테스트 공간*/

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
			button_interface(NAME_LIOYDS_BEACON, TYPE_ACC, 5, 28, 12);
			break;

		//다트
		case NAME_DART:
			fream_window_draw(28, 12);
			button_interface(NAME_DART, TYPE_THROW, 2, 28, 12);
			break;

		//마비 다트
		case NAME_PARALYSIS_DART:
			fream_window_draw(28, 12);
			button_interface(NAME_PARALYSIS_DART, TYPE_THROW, 2, 28, 12);
			break;

		//독 다트
		case NAME_POISON_DART:
			fream_window_draw(28, 12);
			button_interface(NAME_POISON_DART, TYPE_THROW, 2, 28, 12);
			break;

		//전기 완드
		case NAME_LIGHTNING:
			fream_window_draw(28, 12);
			button_interface(NAME_LIGHTNING, TYPE_WAND, 2, 28, 12);
			break;

		//마법 완드
		case NAME_NORMAL:
			fream_window_draw(28, 12);
			button_interface(NAME_NORMAL, TYPE_WAND, 2, 28, 12);
			break;

		//독 완드
		case NAME_POISON:
			fream_window_draw(28, 12);
			button_interface(NAME_POISON, TYPE_WAND, 2, 28, 12);
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
			fream_window_draw(28, 12);
			button_interface(NAME_UPGRADE, TYPE_SCROLL, 3, 28, 12);
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
		case NAME_DEW:
			fream_window_draw(28, 12);
			button_interface(NAME_DEW, TYPE_POTION, 3, 28, 12);
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
			fream_window_draw(28, 12);
			button_interface(NAME_INVISIBLE, TYPE_POTION, 3, 28, 12);
			break;

		//공중 부양
		case NAME_LEVITATION:
			fream_window_draw(28, 12);
			button_interface(NAME_LEVITATION, TYPE_POTION, 3, 28, 12);
			break;

		//서리
		case NAME_FORZEN:
			fream_window_draw(28, 12);
			button_interface(NAME_FORZEN, TYPE_POTION, 3, 28, 12);
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
		case NAME_DEWW:
			fream_window_draw(28, 12);
			button_interface(NAME_DEWW, TYPE_SPECIAL, 3, 28, 12);
			break;

		//없음
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
			//떨어뜨린다
			if (button_option_value[buttonNumber] == BUTTONOPTION_DROP)
			{
				_selectItem = NAME_END;
				_selectInterface = INTERFACEMENU_END;
			}
			
			//마신다
			if (button_option_value[buttonNumber] == BUTTONOPTION_DRINK)
			{
				_selectItem = NAME_END;
				_selectInterface = INTERFACEMENU_END;
			}

			//던진다
			if (button_option_value[buttonNumber] == BUTTONOPTION_THROW)
			{
				_selectItem = NAME_END;
				_selectInterface = INTERFACEMENU_END;
			}

			//읽는다
			if (button_option_value[buttonNumber] == BUTTONOPTION_READ)
			{
				_selectItem = NAME_END;
				_selectInterface = INTERFACEMENU_END;
			}

			//발사한다
			if (button_option_value[buttonNumber] == BUTTONOPTION_LAUNCH)
			{
				_selectItem = NAME_END;
				_selectInterface = INTERFACEMENU_END;
			}

			//먹는다
			if (button_option_value[buttonNumber] == BUTTONOPTION_EAT)
			{
				_selectItem = NAME_END;
				_selectInterface = INTERFACEMENU_END;
			}

			//심는다
			if (button_option_value[buttonNumber] == BUTTONOPTION_PLANT)
			{
				_selectItem = NAME_END;
				_selectInterface = INTERFACEMENU_END;
			}

			//기억한다
			if (button_option_value[buttonNumber] == BUTTONOPTION_REMEMBER)
			{
				_selectItem = NAME_END;
				_selectInterface = INTERFACEMENU_END;
			}

			//착용한다
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