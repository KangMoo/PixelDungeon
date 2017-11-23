#include "stdafx.h"
#include "ItemManager.h"
#include "Player.h"
#include "EnemyManager.h"
#include "Map.h"
#include "UI.h"

ItemManager::ItemManager()
{
}


ItemManager::~ItemManager()
{

}
HRESULT ItemManager::init()
{
	//================ F U N C T I O N =================
	swap();
	imgInit();


	//==================================================
	_item = new Item;
	_item->init();

	return S_OK;
}
void ItemManager::release()
{

}
void ItemManager::update()
{
	_item->update();

	for ( _viBag = _vBag.begin(); _viBag != _vBag.end(); ++_viBag)
	{
		switch (_viBag->name)
		{
		case NAME_OLD_SHORT_SWORD:
			_viBag->minPoint = 1 + _viBag->upgrade;
			_viBag->maxPoint = 10 + _viBag->upgrade * 2;
			break;
		case NAME_SHORT_SWORD:
			_viBag->minPoint = 2 + _viBag->upgrade;
			_viBag->maxPoint = 15 + _viBag->upgrade * 3;
			break;
		case NAME_SWORD:
			_viBag->minPoint = 3 + _viBag->upgrade;
			_viBag->maxPoint = 20 + _viBag->upgrade * 4;
			break;
		case NAME_SPEAR:
			_viBag->minPoint = 2 + _viBag->upgrade;
			_viBag->maxPoint = 20 + _viBag->upgrade * 3;
			break;
		case NAME_BATTLE_AXE:
			_viBag->minPoint = 4 + _viBag->upgrade;
			_viBag->maxPoint = 20 + _viBag->upgrade * 9;
			break;
		case NAME_CLOTH:
			_viBag->minPoint = 0 + _viBag->upgrade;
			_viBag->maxPoint = 2 + _viBag->upgrade;
			break;
		case NAME_LEATHER:
			_viBag->minPoint = 0 + _viBag->upgrade;
			_viBag->maxPoint = 4 + _viBag->upgrade * 2;
			break;
		case NAME_MAIL:
			_viBag->minPoint = 0 + _viBag->upgrade;
			_viBag->maxPoint = 6 + _viBag->upgrade * 3;
			break;
		case NAME_RING_POWER:
			_viBag->stat.str = 1 + _viBag->upgrade;
			break;
		case NAME_LIOYDS_BEACON:
			_viBag->maxCharge = 3 + _viBag->upgrade;
			break;
		case NAME_LIGHTNING:
			_viBag->minPoint = 4 + _viBag->upgrade * 2;
			_viBag->maxPoint = 10 + _viBag->upgrade * 2;
			_viBag->maxCharge = 3 + _viBag->upgrade;
			break;
		case NAME_NORMAL:
			_viBag->minPoint = 4 + _viBag->upgrade * 2;
			_viBag->maxPoint = 6 + _viBag->upgrade * 2;
			_viBag->maxCharge = 4 + _viBag->upgrade;
			break;
		case NAME_POISON:
			_viBag->minPoint = 4 + _viBag->upgrade * 2;
			_viBag->maxPoint = 6 + _viBag->upgrade * 2;
			_viBag->maxCharge = 3 + _viBag->upgrade;
			break;
		}

	}
}
void ItemManager::render(POINT camera)
{
	draw(camera);
}
void ItemManager::draw(POINT camera)
{
	_item->render(_ui->getCamera());
}

void ItemManager::setItemToBag(ITEMNAME name)
{
	if (_vBag.size() > 24) return;

	int count = 0;
	bool end = false;
	bool overlap = false;
	tagItem item;

	ZeroMemory(&item, sizeof(tagItem));

	item.upgrade = 0;

	setItem(&item, name);

	if (item.name == NAME_DEW) overlap = true;


	item.numOfItem = 1;

	for (_viBag = _vBag.begin(); _viBag != _vBag.end(); ++_viBag)
	{
		if (_viBag->name == item.name && (item.type == TYPE_SCROLL ||
			item.type == TYPE_SEED || item.type == TYPE_POTION || item.type ==TYPE_FOOD))
		{
			overlap = true;
			_viBag->numOfItem += item.numOfItem;
		}
	}

	

	if (!overlap)
	{
		while (true)
		{
			if (!_vBag.size())
			{
				end = true;
			}
			else
			{

				for ( _viBag = _vBag.begin(); _viBag != _vBag.end(); ++_viBag)
				{
					if (_viBag->position == count)
					{
						count++;
						end = false;
						break;
					}
					end = true;
				}
			}

			if (end)
			{
				item.position = count;
				break;
			}
		}

		_vBag.push_back(item);
	}
	else
	{
		if (item.name == NAME_DEW)
		{
			for ( _viBag = _vBag.begin(); _viBag != _vBag.end(); ++_viBag)
			{
				if (_viBag->name == NAME_BOTTLE)
				{
					_viBag->currentCharge++;
					break;
				}
			}
		}
		else return;
	}

}

void ItemManager::setItemToField(ITEMNAME name, float x, float y)
{
	bool overlap = false;
	tagItem item;

	ZeroMemory(&item, sizeof(tagItem));

	item.upgrade = 0;

	setItem(&item, name);

	item.point.x = x;
	item.point.y = y;
	item.rc = RectMakeCenter(item.point.x, item.point.y,
		item.img->getWidth(), item.img->getHeight());

	for ( _viItem = _vItem.begin(); _viItem != _vItem.end(); ++_viItem)
	{
		if (item.point.x == _viItem->point.x && item.point.y == _viItem->point.y &&
			item.name == _viItem->name && (item.type == TYPE_FOOD || item.type == TYPE_SCROLL ||
				item.type == TYPE_SEED || item.type == TYPE_POTION))
		{
			overlap = true;
			_viItem->numOfItem += _viItem->numOfItem;
		}

	}

	if(!overlap) _vItem.push_back(item);


}

void ItemManager::setItemToBag(ITEMNAME name, bool identify, bool isCursed, int upgrade, int numOfItem)
{
	if (_vBag.size() > 24) return;

	int count = 0;
	bool end = false;
	bool overlap = false;
	tagItem item;

	ZeroMemory(&item, sizeof(tagItem));

	item.upgrade = upgrade;

	setItem(&item, name);

	item.numOfItem = numOfItem;
	item.contentsHide = identify;
	item.isCursed = isCursed;

	if (item.type == TYPE_SPECIAL) overlap = true;


	for (_viBag = _vBag.begin(); _viBag != _vBag.end(); ++_viBag)
	{
		if (_viBag->name == item.name && (item.type == TYPE_SCROLL ||
			item.type == TYPE_SEED || item.type == TYPE_POTION || item.type == TYPE_FOOD))
		{
			overlap = true;
			_viBag->numOfItem += item.numOfItem;
		}
	}



	if (!overlap)
	{
		while (true)
		{
			if (!_vBag.size())
			{
				end = true;
			}

			else
			{

				for (_viBag = _vBag.begin(); _viBag != _vBag.end(); ++_viBag)
				{
					if (_viBag->position == count)
					{
						count++;
						end = false;
						break;
					}
					end = true;
				}
			}

			if (end)
			{
				item.position = count;
				break;
			}
		}


		_vBag.push_back(item);
	}
	else
	{
		if (item.name == NAME_DEW)
		{
			for (_viBag = _vBag.begin(); _viBag != _vBag.end(); ++_viBag)
			{
				if (_viBag->name == NAME_BOTTLE)
				{
					_viBag->currentCharge++;
					break;
				}
			}
		}
		else return;
	}

}

void ItemManager::setItemToField(ITEMNAME name, float x, float y, bool identify, bool isCursed, int upgrade, int numOfItem)
{
	bool overlap = false;
	tagItem item;

	ZeroMemory(&item, sizeof(tagItem));

	item.upgrade = upgrade;

	setItem(&item, name);

	item.contentsHide = identify;
	item.isCursed = isCursed;
	item.numOfItem = numOfItem;

	item.point.x = x;
	item.point.y = y;
	item.rc = RectMakeCenter(item.point.x, item.point.y,
		item.img->getWidth(), item.img->getHeight());

	for (_viItem = _vItem.begin(); _viItem != _vItem.end(); ++_viItem)
	{
		if (item.point.x == _viItem->point.x && item.point.y == _viItem->point.y &&
			item.name == _viItem->name && (item.type == TYPE_FOOD || item.type == TYPE_SCROLL ||
				item.type == TYPE_SEED || item.type == TYPE_POTION))
		{
			overlap = true;
			_viItem->numOfItem += _viItem->numOfItem;
		}

	}

	if (!overlap) _vItem.push_back(item);

}

void ItemManager::setItem(tagItem* item, ITEMNAME name)
{
	item->name = name;

	switch (name)
	{
	case NAME_OLD_SHORT_SWORD:
		item->type = TYPE_WEAPON;
		item->img = IMAGEMANAGER->findImage("old_short_sword");
		item->equip = false;
		item->isCursed = false;
		item->contentsHide = true;
		item->range = 1;
		item->minPoint = 1 + item->upgrade;
		item->maxPoint = 10 + item->upgrade * 2;
		item->tier = 1;
		item->Power = 10;
		break;
	case NAME_SHORT_SWORD:
		item->type = TYPE_WEAPON;
		item->img = IMAGEMANAGER->findImage("short_sword");
		item->equip = false;
		item->isCursed = false;
		item->contentsHide = true;
		item->minPoint = 2 + item->upgrade;
		item->maxPoint = 15 + item->upgrade * 3;
		item->tier = 2;
		item->Power = 12;
		item->range = 1;
		break;
	case NAME_SWORD:
		item->type = TYPE_WEAPON;
		item->img = IMAGEMANAGER->findImage("sword");
		item->equip = false;
		item->isCursed = false;
		item->contentsHide = true;
		item->minPoint = 3 + item->upgrade ;
		item->maxPoint = 20 + item->upgrade * 4;
		item->tier = 3;
		item->Power = 14;
		item->range = 1;
		break;
	case NAME_SPEAR:
		item->type = TYPE_WEAPON;
		item->img = IMAGEMANAGER->findImage("spear");
		item->equip = false;
		item->isCursed = false;
		item->contentsHide = true;
		item->minPoint = 2 + item->upgrade ;
		item->maxPoint = 20 + item->upgrade * 3;
		item->tier = 2;
		item->Power = 12;
		item->range = 2;
		break;
	case NAME_BATTLE_AXE:
		item->type = TYPE_WEAPON;
		item->img = IMAGEMANAGER->findImage("battle_axe");
		item->equip = false;
		item->isCursed = false;
		item->contentsHide = true;
		item->minPoint = 4 + item->upgrade;
		item->maxPoint = 20 + item->upgrade * 9;
		item->tier = 4;
		item->Power = 16;
		item->range = 1;
		item->stat.atk_lck = 5;
		break;
	case NAME_CLOTH:
		item->type = TYPE_ARMOR;
		item->img = IMAGEMANAGER->findImage("cloth");
		item->equip = false;
		item->isCursed = false;
		item->contentsHide = true;
		item->minPoint = 0 + item->upgrade;
		item->maxPoint = 2 + item->upgrade;
		item->tier = 1;
		item->Power = 10;
		break;
	case NAME_LEATHER:
		item->type = TYPE_ARMOR;
		item->img = IMAGEMANAGER->findImage("leather");
		item->equip = false;
		item->isCursed = false;
		item->contentsHide = true;
		item->minPoint = 0 + item->upgrade;
		item->maxPoint = 4 + item->upgrade * 2;
		item->tier = 2;
		item->Power = 12;
		break;
	case NAME_MAIL:
		item->type = TYPE_ARMOR;
		item->img = IMAGEMANAGER->findImage("mail");
		item->equip = false;
		item->isCursed = false;
		item->contentsHide = true;
		item->minPoint = 0 + item->upgrade;
		item->maxPoint = 6 + item->upgrade * 3;
		item->tier = 3;
		item->Power = 14;
		break;
	case NAME_RING_POWER:
		item->type = TYPE_ACC;
		switch (_acc[0])
		{
		case 0:
			item->img = IMAGEMANAGER->findImage("ring_blue");
			break;
		case 1:
			item->img = IMAGEMANAGER->findImage("ring_red");
			break;
		}
		item->equip = false;
		item->isCursed = false;
		item->contentsHide = true;
		item->stat.str = 1 + item->upgrade;
		break;
	case NAME_RING_RECHARGE:
		item->type = TYPE_ACC;
		switch (_acc[1])
		{
		case 0:
			item->img = IMAGEMANAGER->findImage("ring_blue");
			break;
		case 1:
			item->img = IMAGEMANAGER->findImage("ring_red");
			break;
		}
		item->equip = false;
		item->isCursed = false;
		item->contentsHide = true;
		break;
	case NAME_LIOYDS_BEACON:
		item->type = TYPE_ACC;
		item->img = IMAGEMANAGER->findImage("acc_wand");
		item->throwImg = IMAGEMANAGER->findImage("magic_missile_beacon");
		item->equip = false;
		item->isCursed = false;
		item->contentsHide = true;
		item->maxCharge = 3 + item->upgrade;
		item->currentCharge = item->maxCharge;
		item->range = 4;
		break;
	case NAME_DART:						// 투척 무기 : 다트 =========================================== 
		item->type = TYPE_THROW;
		item->img = IMAGEMANAGER->findImage("dart");
		item->equip = false;
		item->minPoint = 1;
		item->maxPoint = 3;
		item->tier = 1;
		item->Power = 10;
		break;
	case NAME_PARALYSIS_DART:
		item->type = TYPE_THROW;
		item->img = IMAGEMANAGER->findImage("dart");
		item->equip = false;
		item->minPoint = 1;
		item->maxPoint = 3;
		item->tier = 2;
		item->Power = 12;
		break;
	case NAME_POISON_DART:
		item->type = TYPE_THROW;
		item->img = IMAGEMANAGER->findImage("dart");
		item->equip = false;
		item->minPoint = 1;
		item->maxPoint = 3;
		item->tier = 2;
		item->Power = 12;
		break;
	case NAME_LIGHTNING:
		item->type = TYPE_WAND;
		item->img = IMAGEMANAGER->findImage("wand_lightning");
		item->throwImg = IMAGEMANAGER->findImage("magic_missile_lightning");
		item->equip = false;
		item->isCursed = false;
		item->contentsHide = true;
		item->minPoint = 4 + item->upgrade * 2;
		item->maxPoint = 10 + item->upgrade * 2;
		item->maxCharge = 3 + item->upgrade;
		item->currentCharge = item->maxCharge;
		item->range = 4;
		break;
	case NAME_NORMAL:
		item->type = TYPE_WAND;
		item->img = IMAGEMANAGER->findImage("wand_normal");
		item->throwImg = IMAGEMANAGER->findImage("magic_missile");
		item->equip = false;
		item->isCursed = false;
		item->contentsHide = true;
		item->minPoint = 4 + item->upgrade * 2;
		item->maxPoint = 6 + item->upgrade * 2;
		item->maxCharge = 4 + item->upgrade;
		item->currentCharge = item->maxCharge;
		item->range = 4;
		break;
	case NAME_POISON:
		item->type = TYPE_WAND;
		item->img = IMAGEMANAGER->findImage("wand_poison");
		item->throwImg = IMAGEMANAGER->findImage("magic_missile_poison");
		item->equip = false;
		item->isCursed = false;
		item->contentsHide = true;
		item->minPoint = 4 + item->upgrade * 2;
		item->maxPoint = 6 + item->upgrade * 2;
		item->maxCharge = 3 + item->upgrade;
		item->currentCharge = item->maxCharge;
		item->range = 4;
		break;
	case NAME_EMERGENCY:
		item->type = TYPE_FOOD;
		item->img = IMAGEMANAGER->findImage("emergency_food");
		item->contentsHide = false;
		item->minPoint = 220;
		break;
	case NAME_PASTY:
		item->type = TYPE_FOOD;
		item->img = IMAGEMANAGER->findImage("pasty");
		item->contentsHide = false;
		item->minPoint = 300;
		break;
	case NAME_UNKNOWN_MEAT:
		item->type = TYPE_FOOD;
		item->img = IMAGEMANAGER->findImage("meat_unknown");
		item->contentsHide = false;
		item->minPoint = 80;
		break;
	case NAME_COOKED_MEAT:
		item->type = TYPE_FOOD;
		item->img = IMAGEMANAGER->findImage("meat_cooked");
		item->contentsHide = false;
		item->minPoint = 80;
		break;
	case NAME_FROZEN_MEAT:
		item->type = TYPE_FOOD;
		item->img = IMAGEMANAGER->findImage("meat_frozen");
		item->contentsHide = false;
		item->minPoint = 80;
		break;
	case NAME_IDENTIFY:			// 사용 아이템 : 주문서 ===========================================
		item->type = TYPE_SCROLL;
		switch (_scroll[0])
		{
		case 0:item->img = IMAGEMANAGER->findImage("scroll_berkanan");
			break;
		case 1:item->img = IMAGEMANAGER->findImage("scroll_gyfu");
			break;
		case 2:item->img = IMAGEMANAGER->findImage("scroll_kaunan");
			break;
		case 3:item->img = IMAGEMANAGER->findImage("scroll_laguz ");
			break;
		case 4:item->img = IMAGEMANAGER->findImage("scroll_yngvi");
			break;
		}
		item->equip = false;
		item->contentsHide = true;
		break;
	case NAME_UPGRADE:
		item->type = TYPE_SCROLL;
		switch (_scroll[1])
		{
		case 0:item->img = IMAGEMANAGER->findImage("scroll_berkanan");
			break;
		case 1:item->img = IMAGEMANAGER->findImage("scroll_gyfu");
			break;
		case 2:item->img = IMAGEMANAGER->findImage("scroll_kaunan");
			break;
		case 3:item->img = IMAGEMANAGER->findImage("scroll_laguz ");
			break;
		case 4:item->img = IMAGEMANAGER->findImage("scroll_yngvi");
			break;
		}
		item->equip = false;
		item->contentsHide = true;
		break;
	case NAME_PURIFY:
		item->type = TYPE_SCROLL;
		switch (_scroll[2])
		{
		case 0:item->img = IMAGEMANAGER->findImage("scroll_berkanan");
			break;
		case 1:item->img = IMAGEMANAGER->findImage("scroll_gyfu");
			break;
		case 2:item->img = IMAGEMANAGER->findImage("scroll_kaunan");
			break;
		case 3:item->img = IMAGEMANAGER->findImage("scroll_laguz ");
			break;
		case 4:item->img = IMAGEMANAGER->findImage("scroll_yngvi");
			break;
		}
		item->equip = false;
		item->contentsHide = true;
		break;
	case NAME_MAP:
		item->type = TYPE_SCROLL;
		switch (_scroll[3])
		{
		case 0:item->img = IMAGEMANAGER->findImage("scroll_berkanan");
			break;
		case 1:item->img = IMAGEMANAGER->findImage("scroll_gyfu");
			break;
		case 2:item->img = IMAGEMANAGER->findImage("scroll_kaunan");
			break;
		case 3:item->img = IMAGEMANAGER->findImage("scroll_laguz ");
			break;
		case 4:item->img = IMAGEMANAGER->findImage("scroll_yngvi");
			break;
		}
		item->equip = false;
		item->contentsHide = true;
		break;
	case NAME_RECHARGE:
		item->type = TYPE_SCROLL;
		switch (_scroll[4])
		{
		case 0:item->img = IMAGEMANAGER->findImage("scroll_berkanan");
			break;
		case 1:item->img = IMAGEMANAGER->findImage("scroll_gyfu");
			break;
		case 2:item->img = IMAGEMANAGER->findImage("scroll_kaunan");
			break;
		case 3:item->img = IMAGEMANAGER->findImage("scroll_laguz ");
			break;
		case 4:item->img = IMAGEMANAGER->findImage("scroll_yngvi");
			break;
		}
		item->equip = false;
		item->contentsHide = true;
		break;
	case NAME_BOTTLE:		// ===============포션 ===================
		item->type = TYPE_POTION;
		item->img = IMAGEMANAGER->findImage("potion_bottle");
		item->equip = false;
		item->contentsHide = false;
		item->maxCharge = 20;
		item->currentCharge = 0;
		item->numOfItem = 1;
		break;
	case NAME_HEAL:
		item->type = TYPE_POTION;
		switch (_potion[0])
		{
		case 0:item->img = IMAGEMANAGER->findImage("potion_black");
			break;
		case 1:item->img = IMAGEMANAGER->findImage("potion_green");
			break;
		case 2:item->img = IMAGEMANAGER->findImage("potion_magenta");
			break;
		case 3:item->img = IMAGEMANAGER->findImage("potion_orange ");
			break;
		case 4:item->img = IMAGEMANAGER->findImage("potion_purple");
			break;
		case 5:item->img = IMAGEMANAGER->findImage("potion_red");
			break;
		case 6:item->img = IMAGEMANAGER->findImage("potion_yellow");
			break;
		}
		item->equip = false;
		item->contentsHide = true;
		break;
	case NAME_STR:
		item->type = TYPE_POTION;
		switch (_potion[1])
		{
		case 0:item->img = IMAGEMANAGER->findImage("potion_black");
			break;
		case 1:item->img = IMAGEMANAGER->findImage("potion_green");
			break;
		case 2:item->img = IMAGEMANAGER->findImage("potion_magenta");
			break;
		case 3:item->img = IMAGEMANAGER->findImage("potion_orange ");
			break;
		case 4:item->img = IMAGEMANAGER->findImage("potion_purple");
			break;
		case 5:item->img = IMAGEMANAGER->findImage("potion_red");
			break;
		case 6:item->img = IMAGEMANAGER->findImage("potion_yellow");
			break;
		}
		item->equip = false;
		item->contentsHide = true;
		break;
	case NAME_EX:
		item->type = TYPE_POTION;
		switch (_potion[2])
		{
		case 0:item->img = IMAGEMANAGER->findImage("potion_black");
			break;
		case 1:item->img = IMAGEMANAGER->findImage("potion_green");
			break;
		case 2:item->img = IMAGEMANAGER->findImage("potion_magenta");
			break;
		case 3:item->img = IMAGEMANAGER->findImage("potion_orange ");
			break;
		case 4:item->img = IMAGEMANAGER->findImage("potion_purple");
			break;
		case 5:item->img = IMAGEMANAGER->findImage("potion_red");
			break;
		case 6:item->img = IMAGEMANAGER->findImage("potion_yellow");
			break;
		}
		item->equip = false;
		item->contentsHide = true;
		break;
	case NAME_INVISIBLE:
		item->type = TYPE_POTION;
		switch (_potion[3])
		{
		case 0:item->img = IMAGEMANAGER->findImage("potion_black");
			break;
		case 1:item->img = IMAGEMANAGER->findImage("potion_green");
			break;
		case 2:item->img = IMAGEMANAGER->findImage("potion_magenta");
			break;
		case 3:item->img = IMAGEMANAGER->findImage("potion_orange ");
			break;
		case 4:item->img = IMAGEMANAGER->findImage("potion_purple");
			break;
		case 5:item->img = IMAGEMANAGER->findImage("potion_red");
			break;
		case 6:item->img = IMAGEMANAGER->findImage("potion_yellow");
			break;
		}
		item->equip = false;
		item->contentsHide = true;
		break;
	case NAME_LEVITATION:
		item->type = TYPE_POTION;
		switch (_potion[4])
		{
		case 0:item->img = IMAGEMANAGER->findImage("potion_black");
			break;
		case 1:item->img = IMAGEMANAGER->findImage("potion_green");
			break;
		case 2:item->img = IMAGEMANAGER->findImage("potion_magenta");
			break;
		case 3:item->img = IMAGEMANAGER->findImage("potion_orange ");
			break;
		case 4:item->img = IMAGEMANAGER->findImage("potion_purple");
			break;
		case 5:item->img = IMAGEMANAGER->findImage("potion_red");
			break;
		case 6:item->img = IMAGEMANAGER->findImage("potion_yellow");
			break;
		}
		item->equip = false;
		item->contentsHide = true;
		break;
	case NAME_FORZEN:
		item->type = TYPE_POTION;
		switch (_potion[5])
		{
		case 0:item->img = IMAGEMANAGER->findImage("potion_black");
			break;
		case 1:item->img = IMAGEMANAGER->findImage("potion_green");
			break;
		case 2:item->img = IMAGEMANAGER->findImage("potion_magenta");
			break;
		case 3:item->img = IMAGEMANAGER->findImage("potion_orange ");
			break;
		case 4:item->img = IMAGEMANAGER->findImage("potion_purple");
			break;
		case 5:item->img = IMAGEMANAGER->findImage("potion_red");
			break;
		case 6:item->img = IMAGEMANAGER->findImage("potion_yellow");
			break;
		}
		item->equip = false;
		item->contentsHide = true;
		break;
	case NAME_LIQUID_FIRE:
		item->type = TYPE_POTION;
		switch (_potion[6])
		{
		case 0:item->img = IMAGEMANAGER->findImage("potion_black");
			break;
		case 1:item->img = IMAGEMANAGER->findImage("potion_green");
			break;
		case 2:item->img = IMAGEMANAGER->findImage("potion_magenta");
			break;
		case 3:item->img = IMAGEMANAGER->findImage("potion_orange ");
			break;
		case 4:item->img = IMAGEMANAGER->findImage("potion_purple");
			break;
		case 5:item->img = IMAGEMANAGER->findImage("potion_red");
			break;
		case 6:item->img = IMAGEMANAGER->findImage("potion_yellow");
			break;
		}
		item->equip = false;
		item->contentsHide = true;
		break;
	case NAME_SEED_HEAL:	//============ 씨 앗 ==========
		item->type = TYPE_SEED;
		item->img = IMAGEMANAGER->findImage("seed_heal");
		item->equip = false;
		break;
	case NAME_SEED_FIRE:
		item->type = TYPE_SEED;
		item->img = IMAGEMANAGER->findImage("seed_fire");
		item->equip = false;
		break;
	case NAME_SEED_SNAKE:
		item->type = TYPE_SEED;
		item->img = IMAGEMANAGER->findImage("seed_snake");
		item->equip = false;
		break;
	case NAME_SEED_FROST:
		item->type = TYPE_SEED;
		item->img = IMAGEMANAGER->findImage("seed_frost");
		item->equip = false;
		break;
	case NAME_DEW:
		item->type = TYPE_SPECIAL;
		item->img = IMAGEMANAGER->findImage("dew");
		break;
	case NAME_MONEY:
		item->type = TYPE_SPECIAL;
		item->img = IMAGEMANAGER->findImage("money");
		break;
	case NAME_END:
		break;
	}

}

void ItemManager::swap()
{
	int dest;
	int sour;
	int temp;

	for (int i = 0; i < 7; i++)
	{
		_potion[i] = i;
	}

	for (int i = 0; i < 3; i++)
	{
		_wand[i] = i;
	}

	for (int i = 0; i < 5; i++)
	{
		_scroll[i] = i;
	}
	for (int i = 0; i < 2; i++)
	{
		_acc[i] = i;
	}

	for (int i = 0; i < 10; i++)
	{
		dest = RND->getInt(7);
		sour = RND->getInt(7);
		
		temp = _potion[dest];
		_potion[dest] = _potion[sour];
		_potion[sour] = temp;
	}

	for (int i = 0; i < 10; i++)
	{
		dest = RND->getInt(3);
		sour = RND->getInt(3);

		temp = _wand[dest];
		_wand[dest] = _wand[sour];
		_wand[sour] = temp;
	}

	for (int i = 0; i < 10; i++)
	{
		dest = RND->getInt(5);
		sour = RND->getInt(5);

		temp = _scroll[dest];
		_scroll[dest] = _scroll[sour];
		_scroll[sour] = temp;
	}

	for (int i = 0; i < 10; i++)
	{
		dest = RND->getInt(2);
		sour = RND->getInt(2);

		temp = _acc[dest];
		_acc[dest] = _acc[sour];
		_acc[sour] = temp;
	}

}

void ItemManager::imgInit()
{
	//=========================== W E A P O N ===========================
	IMAGEMANAGER->addImage("old_short_sword", "Img/Item/weapon_old_short_sword.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("short_sword", "Img/Item/weapon_short_sword.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("sword", "Img/Item/weapon_sword.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("spear", "Img/Item/weapon_spear.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("hammer", "Img/Item/weapon_hammer.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("battle_axe", "Img/Item/weapon_battle_axe.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("scimitar", "Img/Item/weapon_scimitar.bmp", 32, 32, true, RGB(255, 0, 255));
	//=========================== A R M O R =============================
	IMAGEMANAGER->addImage("cloth", "Img/Item/cloth.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("leather", "Img/Item/light_armor.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("mail", "Img/Item/heavy_armor.bmp", 32, 32, true, RGB(255, 0, 255));
	//=========================== P O T I O N ===========================
	IMAGEMANAGER->addImage("potion_black", "Img/Item/potion_black.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("potion_green", "Img/Item/potion_green.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("potion_magenta", "Img/Item/potion_magenta.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("potion_orange", "Img/Item/potion_orange.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("potion_purple", "Img/Item/potion_purple.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("potion_red", "Img/Item/potion_red.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("potion_yellow", "Img/Item/potion_yellow.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("potion_bottle", "Img/Item/bottle.bmp", 32, 32, true, RGB(255, 0, 255));
	//=========================== S C R O L L ============================
	IMAGEMANAGER->addImage("scroll_berkanan", "Img/Item/scroll_berkanan.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("scroll_gyfu", "Img/Item/scroll_gyfu.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("scroll_kaunan", "Img/Item/scroll_kaunan.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("scroll_laguz", "Img/Item/scroll_laguz.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("scroll_yngvi", "Img/Item/scroll_yngvi.bmp", 32, 32, true, RGB(255, 0, 255));
	//=========================== S E E D ================================
	IMAGEMANAGER->addImage("seed_fire", "Img/Item/seed_fire.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("seed_frost", "Img/Item/seed_frost.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("seed_heal", "Img/Item/seed_heal.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("seed_snake", "Img/Item/seed_snake.bmp", 32, 32, true, RGB(255, 0, 255));
	//=========================== F O O D =================================
	IMAGEMANAGER->addImage("meat_unknown", "Img/Item/unknown_meat.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("meat_cooked", "Img/Item/cooked_meat.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("meat_frozen", "Img/Item/frozen_meat.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("emegency_food", "Img/Item/emergency_food.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("pasty", "Img/Item/pasty.bmp", 32, 32, true, RGB(255, 0, 255));
	//=========================== A C C E S O R Y =========================
	IMAGEMANAGER->addImage("ring_blue", "Img/Item/ring_blue.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ring_red", "Img/Item/ring_red.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("acc_wand", "Img/Item/acc_wand.bmp", 32, 32, true, RGB(255, 0, 255));
	//=========================== T H R O W ===============================
	IMAGEMANAGER->addImage("dart", "Img/Item/dart.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("dart_effect", "Img/Item/dart_effect.bmp", 32, 32, true, RGB(255, 0, 255));
	//=========================== W A N D =================================
	IMAGEMANAGER->addImage("wand_normal", "Img/Item/wand_normal.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("wand_lightning", "Img/Item/wand_lightning.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("wand_poison", "Img/Item/wand_poison.bmp", 32, 32, true, RGB(255, 0, 255));
	//=========================== S P E C I A L ===========================
	IMAGEMANAGER->addImage("dew", "Img/Item/dew.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("money", "Img/Item/money.bmp", 32, 32, true, RGB(255, 0, 255));
	//=========================== T H R O W ===============================
	IMAGEMANAGER->addImage("magic_missile", "Img/Item/magic_missile.bmp",16,16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("magic_missile_lightning", "Img/Item/magic_missile_lightning.bmp", 16, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("magic_missile_poison", "Img/Item/magic_missile_poison.bmp", 16, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("magic_missile_beacon", "Img/Item/magic_missile_beacon.bmp", 16, 16, true, RGB(255, 0, 255));
	//=========================== F L O W E R =============================
	IMAGEMANAGER->addImage("flower_fire", "Img/Item/flower_fire.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("flower_frost", "Img/Item/flower_frost.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("flower_heal", "Img/Item/flower_heal.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("flower_snake", "Img/Item/flower_snake.bmp", 32, 32, true, RGB(255, 0, 255));


}

void ItemManager::unequipItem(int position)
{
	for ( _viBag = _vBag.begin(); _viBag != _vBag.end(); ++_viBag)
	{
		if (_viBag->position == position)
		{
			_viBag->equip = false;
		}
	}
}

void ItemManager::equipItem(int position)
{
	for ( _viBag = _vBag.begin(); _viBag != _vBag.end(); ++_viBag)
	{
		if (_viBag->position == position)
		{
			switch (_viBag->type)
			{
			case TYPE_WEAPON:
				for (int i = 0; i < _vBag.size(); i++)
				{
					if(_vBag[i].type ==TYPE_WEAPON && _vBag[i].equip) _vBag[i].equip = false;
				}
				_viBag->equip = true;

				break;
			case TYPE_ARMOR:
				for (int i = 0; i < _vBag.size(); i++)
				{
					if (_vBag[i].type == TYPE_ARMOR && _vBag[i].equip) _vBag[i].equip = false;
				}
				_viBag->equip = true;
				break;
			case TYPE_ACC:
				_viBag->equip = true;
				break;
			default:
				break;
			}
		}

	}
}
void ItemManager::useItem(int position)
{
	for (_viBag = _vBag.begin(); _viBag != _vBag.end(); ++_viBag)
	{
		if (_viBag->position == position)
		{
			switch (_viBag->type)
			{
			case TYPE_FOOD:
				_viBag->numOfItem--;
				if (_viBag->numOfItem <= 0) _viBag = _vBag.erase(_viBag);
				break;

			default:
				break;
			}
		}

	}
}
void ItemManager::useItem(int position, float x, float y)
{
	for (_viBag = _vBag.begin(); _viBag != _vBag.end(); ++_viBag)
	{
		if (_viBag->position == position)
		{
			switch (_viBag->type)
			{
			case TYPE_WAND:
				if (_viBag->currentCharge > 0)
				{
					_item->fire(_viBag->img, _player->getPoint().x, _player->getPoint().y, x, y);
					_viBag->currentCharge--;
				}
				break;

			default:
				break;
			}
		}

	}
}

void ItemManager::useItem(int position, int target)
{
	for (_viBag = _vBag.begin(); _viBag != _vBag.end(); ++_viBag)
	{
		if (_viBag->position == position)
		{
			switch (_viBag->type)
			{
			case TYPE_SCROLL:
				switch (_viBag->name)
				{
				case NAME_UPGRADE:

					break;

				}
				break;

			default:
				break;
			}
		}

	}
}

void ItemManager::fire(image* img, float x, float y, float destX, float destY)
{
	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.x = bullet.initX = x;
	bullet.y = bullet.initY = y;
	bullet.destX = destX;
	bullet.destY = destY;
	bullet.angle = getAngle(x, y, destX, destY);
	bullet.speed = 7;
	bullet.img = img;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.img->getWidth(), bullet.img->getHeight());
	bullet.fire = false;
	bullet.count = 0;

	_vBullet.push_back(bullet);
}

void ItemManager::throwItem(image* img, float x, float y, float destX, float destY)
{
	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.x = bullet.initX = x;
	bullet.y = bullet.initY = y;
	bullet.destX = destX;
	bullet.destY = destY;
	bullet.angle = getAngle(x, y, destX, destY);
	bullet.speed = 7;
	bullet.img = img;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.img->getWidth(), bullet.img->getHeight());
	bullet.fire = false;
	bullet.count = 0;

	_vThrow.push_back(bullet);
}


void ItemManager::bulletMove()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); )
	{
		_viBullet->x += _viBullet->speed * cosf(_viBullet->angle);
		_viBullet->y += _viBullet->speed * sinf(_viBullet->angle);

		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->img->getWidth(), _viBullet->img->getHeight());

		if (getDistance(_viBullet->initX, _viBullet->initY, _viBullet->x, _viBullet->y) >
			getDistance(_viBullet->initX, _viBullet->initY, _viBullet->destX, _viBullet->destY))
		{
			_viBullet = _vBullet.erase(_viBullet);
			break;
		}
		else ++_viBullet;
	}
}

void ItemManager::throwMove()
{
	for (_viThrow = _vThrow.begin(); _viThrow != _vThrow.end(); )
	{
		_viThrow->x += _viThrow->speed * cosf(_viThrow->angle);
		_viThrow->y += _viThrow->speed * sinf(_viThrow->angle);

		_viThrow->rc = RectMakeCenter(_viThrow->x, _viThrow->y,
			_viThrow->img->getWidth(), _viThrow->img->getHeight());

		if (getDistance(_viThrow->initX, _viThrow->initY, _viThrow->x, _viThrow->y) >
			getDistance(_viThrow->initX, _viThrow->initY, _viThrow->destX, _viThrow->destY))
		{
			_viThrow = _vBullet.erase(_viThrow);
			break;
		}
		else ++_viThrow;
	}
}


void ItemManager::removeBullet(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);
}

void ItemManager::removeThrow(int arrNum)
{
	_vThrow.erase(_vThrow.begin() + arrNum);
}




