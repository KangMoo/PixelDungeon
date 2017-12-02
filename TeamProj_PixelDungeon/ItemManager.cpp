#include "stdafx.h"
#include "ItemManager.h"
#include "Player.h"
#include "EnemyManager.h"
#include "Map.h"
#include "UI.h"
#include<assert.h>
ItemManager::ItemManager()
{
}


ItemManager::~ItemManager()
{

}

HRESULT ItemManager::init()
{
	//================ F U N C T I O N =================
	imgInit();	
	swap();
	
	//================ I D E N T I F I E D ==================
	for (int i = 0; i < 7; i++)
	{
		_potionIdentified[i] = false;
	}

	for (int i = 0; i < 5; i++)
	{
		_scrollIdentified[i] = false;
	}
	_fire = false;
	_frozen = false;
	for (int i = 0; i < 20; i++)
	{
		frozenE[i].img = IMAGEMANAGER->findImage("effectFrozen");
		frozenE[i].size = 10;
		frozenE[i].Trans = RND->getFromIntTo(0, 255);
		frozenE[i].isSee = true;
		fireE[i].img = IMAGEMANAGER->findImage("effectFire");
		fireE[i].size = RND->getFromIntTo(1,5);
		fireE[i].Trans = RND->getFromIntTo(0, 150);
		fireE[i].isSee = true;

	}
	//==================================================

	setItemToBag(NAME_EMERGENCY);
	setItemToBag(NAME_OLD_SHORT_SWORD, false, false, 9, 1);
	setItemToBag(NAME_CLOTH);
	setItemToBag(NAME_NORMAL);
	setItemToBag(NAME_BATTLE_AXE);
	setItemToBag(NAME_LIOYDS_BEACON);

	setItemToBag(NAME_FROZEN);
	setItemToBag(NAME_FROZEN);
	setItemToBag(NAME_FROZEN);
	setItemToBag(NAME_FROZEN);
	setItemToBag(NAME_FROZEN);
	setItemToBag(NAME_FROZEN);

	setItemToBag(NAME_LIQUID_FIRE);
	setItemToBag(NAME_UNKNOWN_MEAT);

	setItemToBag(NAME_IDENTIFY);
	setItemToBag(NAME_UPGRADE);
	setItemToBag(NAME_PURIFY);

	setItemToBag(NAME_SEED_HEAL);
	setItemToBag(NAME_SEED_FIRE);
	setItemToBag(NAME_SEED_SNAKE);

	return S_OK;
}
void ItemManager::release()
{

}
void ItemManager::update()
{
	
	keyControl();

	for ( _viBag = _vBag.begin(); _viBag != _vBag.end(); ++_viBag)
	{

		switch (_viBag->name)
		{
		case NAME_OLD_SHORT_SWORD:
			_viBag->minPoint = 1 + _viBag->upgrade;
			_viBag->maxPoint = 10 + _viBag->upgrade * 2;
			_viBag->Power = 10 - (_viBag->upgrade / 3) - 1;
			break;
		case NAME_SHORT_SWORD:
			_viBag->minPoint = 2 + _viBag->upgrade;
			_viBag->maxPoint = 15 + _viBag->upgrade * 3;
			_viBag->Power = 12 - (_viBag->upgrade / 3) - 1;
			break;
		case NAME_SWORD:
			_viBag->minPoint = 3 + _viBag->upgrade;
			_viBag->maxPoint = 20 + _viBag->upgrade * 4;
			_viBag->Power = 14 - (_viBag->upgrade / 3) - 1;
			break;
		case NAME_SPEAR:
			_viBag->minPoint = 2 + _viBag->upgrade;
			_viBag->maxPoint = 20 + _viBag->upgrade * 3;
			_viBag->Power = 12 - (_viBag->upgrade / 3) - 1;
			break;
		case NAME_BATTLE_AXE:
			_viBag->minPoint = 4 + _viBag->upgrade;
			_viBag->maxPoint = 20 + _viBag->upgrade * 9;
			_viBag->Power = 16 - (_viBag->upgrade / 3) - 1;
			break;
		case NAME_CLOTH:
			_viBag->minPoint = 0 + _viBag->upgrade;
			_viBag->maxPoint = 2 + _viBag->upgrade;
			_viBag->Power = 10 - (_viBag->upgrade / 3) - 1;
			break;
		case NAME_LEATHER:
			_viBag->minPoint = 0 + _viBag->upgrade;
			_viBag->maxPoint = 4 + _viBag->upgrade * 2;
			_viBag->Power = 12 - (_viBag->upgrade / 3) - 1;
			break;
		case NAME_MAIL:
			_viBag->minPoint = 0 + _viBag->upgrade;
			_viBag->maxPoint = 6 + _viBag->upgrade * 3;
			_viBag->Power = 14 - (_viBag->upgrade / 3) - 1;
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

	for (int i = 0; i < _vBag.size(); i++)
	{
		_vBag[i].position = i;
	}
	for ( _viItem = _vItem.begin(); _viItem != _vItem.end(); ++_viItem)
	{
		_viItem->rc = RectMakeCenter(_viItem->point.x, _viItem->point.y,
			_viItem->img->getWidth(), _viItem->img->getHeight());
	}
	//================== I T E M   D R O P =========================
	for ( _viItem = _vItem.begin(); _viItem != _vItem.end(); ++_viItem)
	{
		if (!_viItem->drop)
		{
			_viItem->point.y-=1;
			if (_viItem->point.y < _viItem->initPoint.y -10)
				_viItem->drop = true;
		}
		else
		{
			_viItem->point.y+=1;
			if (_viItem->point.y > _viItem->initPoint.y)
				_viItem->point.y = _viItem->initPoint.y;
		}

	}

	bulletMove();
	throwMove();




}
void ItemManager::render(POINT camera)
{
	draw(camera);
}
void ItemManager::draw(POINT camera)
{
	for ( _viBullet = _vBullet.begin(); _viBullet < _vBullet.end(); ++_viBullet)
	{
		_viBullet->img->render(getMemDC(), _viBullet->x + camera.x, _viBullet->y + camera.y);
	}
	for ( _viThrow = _vThrow.begin(); _viThrow != _vThrow.end(); ++_viThrow)
	{
		_viThrow->img->render(getMemDC(), _viThrow->x + camera.x, _viThrow->y + camera.y);
	}
	for ( _viItem = _vItem.begin(); _viItem != _vItem.end(); ++_viItem)
	{
		if (_viItem->floor == _map->getCurStageNum() && _map->getTile(_viItem->point.x / TILESIZE, _viItem->point.y / TILESIZE).tileview == TILEVIEW_ALL)
		_viItem->img->render(getMemDC(), _viItem->rc.left + camera.x, _viItem->rc.top + camera.y);
	}
		for (int i = 0; i < 20; i++)
		{
			Rectangle(getMemDC(), frozenE[i].rc.left+camera.x, frozenE[i].rc.top + camera.y, frozenE[i].rc.right + camera.x, frozenE[i].rc.bottom + camera.y);
		}
	if (_fire)
	{
	}
}

void ItemManager::setItemToBag(ITEMNAME name)
{
	if (_vBag.size() >= 20) return;

	int count = 0;
	bool end = false;
	bool overlap = false;
	tagItem item;

	ZeroMemory(&item, sizeof(tagItem));

	item.upgrade = 0;

	setItem(&item, name);

	if (item.type == TYPE_SPECIAL) overlap = true;


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

	item.drop = false;
	item.upgrade = 0;
	item.floor = _map->getCurStageNum();
	setItem(&item, name);

	item.initPoint.x = item.point.x = (int)(x / TILESIZE)*TILESIZE + 16;
	item.initPoint.y = item.point.y = (int)(y / TILESIZE)*TILESIZE + 16;
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
	if (_vBag.size() >= 20) return;

	int count = 0;
	bool end = false;
	bool overlap = false;
	tagItem item;

	ZeroMemory(&item, sizeof(tagItem));


	setItem(&item, name);

	item.upgrade = upgrade;
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

	item.drop = false;
	item.upgrade = upgrade;
	item.floor = _map->getCurStageNum();
	setItem(&item, name);

	item.contentsHide = identify;
	item.isCursed = isCursed;
	item.numOfItem = numOfItem;

	item.initPoint.x = item.point.x = (int)(x / TILESIZE)*TILESIZE + 16;
	item.initPoint.y = item.point.y = (int)(y / TILESIZE)*TILESIZE + 16;
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
		item->throwImg = IMAGEMANAGER->findImage("magic_missile_beacon");

		item->equip = false;
		item->minPoint = 1;
		item->maxPoint = 3;
		item->tier = 1;
		item->Power = 10;
		break;
	case NAME_PARALYSIS_DART:
		item->type = TYPE_THROW;
		item->img = IMAGEMANAGER->findImage("dart");
		item->throwImg = IMAGEMANAGER->findImage("magic_missile");

		item->equip = false;
		item->minPoint = 1;
		item->maxPoint = 3;
		item->tier = 2;
		item->Power = 12;
		break;
	case NAME_POISON_DART:
		item->type = TYPE_THROW;
		item->img = IMAGEMANAGER->findImage("dart");
		item->throwImg = IMAGEMANAGER->findImage("magic_missile");

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
		case 3:item->img = IMAGEMANAGER->findImage("scroll_laguz");
			break;
		case 4:item->img = IMAGEMANAGER->findImage("scroll_yngvi");
			break;
		}
		item->equip = false;
		if(!_scrollIdentified[0]) item->contentsHide = true;
		else item->contentsHide = false;

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
		case 3:item->img = IMAGEMANAGER->findImage("scroll_laguz");
			break;
		case 4:item->img = IMAGEMANAGER->findImage("scroll_yngvi");
			break;
		}
		item->equip = false;
		if(!_scrollIdentified[1]) item->contentsHide = true;
		else item->contentsHide = false;
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
		case 3:item->img = IMAGEMANAGER->findImage("scroll_laguz");
			break;
		case 4:item->img = IMAGEMANAGER->findImage("scroll_yngvi");
			break;
		}
		item->equip = false;
		if (!_scrollIdentified[2]) item->contentsHide = true;
		else item->contentsHide = false;
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
		case 3:item->img = IMAGEMANAGER->findImage("scroll_laguz");
			break;
		case 4:item->img = IMAGEMANAGER->findImage("scroll_yngvi");
			break;
		}
		item->equip = false;
		if (!_scrollIdentified[3]) item->contentsHide = true;
		else item->contentsHide = false;
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
		case 3:item->img = IMAGEMANAGER->findImage("scroll_laguz");
			break;
		case 4:item->img = IMAGEMANAGER->findImage("scroll_yngvi");
			break;
		}
		item->equip = false;
		if (!_scrollIdentified[4]) item->contentsHide = true;
		else item->contentsHide = false;
		break;
	case NAME_BOTTLE:		// ===============포션 ===================
		item->type = TYPE_POTION;
		item->img = IMAGEMANAGER->findImage("potion_bottle");
		item->equip = false;
		item->contentsHide = false;
		item->maxCharge = 20;
		item->currentCharge = 0;
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
		case 3:item->img = IMAGEMANAGER->findImage("potion_orange");
			break;
		case 4:item->img = IMAGEMANAGER->findImage("potion_purple");
			break;
		case 5:item->img = IMAGEMANAGER->findImage("potion_red");
			break;
		case 6:item->img = IMAGEMANAGER->findImage("potion_yellow");
			break;
		}
		item->equip = false;
		if (!_potionIdentified[0]) item->contentsHide = true;
		else item->contentsHide = false;
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
		case 3:item->img = IMAGEMANAGER->findImage("potion_orange");
			break;
		case 4:item->img = IMAGEMANAGER->findImage("potion_purple");
			break;
		case 5:item->img = IMAGEMANAGER->findImage("potion_red");
			break;
		case 6:item->img = IMAGEMANAGER->findImage("potion_yellow");
			break;
		}
		item->equip = false;
		if (!_potionIdentified[1]) item->contentsHide = true;
		else item->contentsHide = false;
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
		case 3:item->img = IMAGEMANAGER->findImage("potion_orange");
			break;
		case 4:item->img = IMAGEMANAGER->findImage("potion_purple");
			break;
		case 5:item->img = IMAGEMANAGER->findImage("potion_red");
			break;
		case 6:item->img = IMAGEMANAGER->findImage("potion_yellow");
			break;
		}
		item->equip = false;
		if (!_potionIdentified[2]) item->contentsHide = true;
		else item->contentsHide = false;
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
		case 3:item->img = IMAGEMANAGER->findImage("potion_orange");
			break;
		case 4:item->img = IMAGEMANAGER->findImage("potion_purple");
			break;
		case 5:item->img = IMAGEMANAGER->findImage("potion_red");
			break;
		case 6:item->img = IMAGEMANAGER->findImage("potion_yellow");
			break;
		}
		item->equip = false;
		if (!_potionIdentified[3]) item->contentsHide = true;
		else item->contentsHide = false;
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
		case 3:item->img = IMAGEMANAGER->findImage("potion_orange");
			break;
		case 4:item->img = IMAGEMANAGER->findImage("potion_purple");
			break;
		case 5:item->img = IMAGEMANAGER->findImage("potion_red");
			break;
		case 6:item->img = IMAGEMANAGER->findImage("potion_yellow");
			break;
		}
		item->equip = false;
		if (!_potionIdentified[4]) item->contentsHide = true;
		else item->contentsHide = false;
		break;
	case NAME_FROZEN:
		item->type = TYPE_POTION;
		switch (_potion[5])
		{
		case 0:item->img = IMAGEMANAGER->findImage("potion_black");
			break;
		case 1:item->img = IMAGEMANAGER->findImage("potion_green");
			break;
		case 2:item->img = IMAGEMANAGER->findImage("potion_magenta");
			break;
		case 3:item->img = IMAGEMANAGER->findImage("potion_orange");
			break;
		case 4:item->img = IMAGEMANAGER->findImage("potion_purple");
			break;
		case 5:item->img = IMAGEMANAGER->findImage("potion_red");
			break;
		case 6:item->img = IMAGEMANAGER->findImage("potion_yellow");
			break;
		}
		item->equip = false;		
		if (!_potionIdentified[5]) item->contentsHide = true;
		else item->contentsHide = false;
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
		case 3:item->img = IMAGEMANAGER->findImage("potion_orange");
			break;
		case 4:item->img = IMAGEMANAGER->findImage("potion_purple");
			break;
		case 5:item->img = IMAGEMANAGER->findImage("potion_red");
			break;
		case 6:item->img = IMAGEMANAGER->findImage("potion_yellow");
			break;
		}
		item->equip = false;
		if (!_potionIdentified[6]) item->contentsHide = true;
		else item->contentsHide = false;
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
	case NAME_KEY_IRON:
		item->type = TYPE_SPECIAL;
		item->img = IMAGEMANAGER->findImage("key_iron");
		break;
	case NAME_KEY_SILVER:
		item->type = TYPE_SPECIAL;
		item->img = IMAGEMANAGER->findImage("key_silver");
		break;
	case NAME_KEY_GOLD:
		item->type = TYPE_SPECIAL;
		item->img = IMAGEMANAGER->findImage("key_gold");
		break;
	case NAME_FLOWER_HEAL:
		item->type = TYPE_SPECIAL;
		item->img = IMAGEMANAGER->findImage("flower_heal");
		break;
	case NAME_FLOWER_FIRE:
		item->type = TYPE_SPECIAL;
		item->img = IMAGEMANAGER->findImage("flower_fire");
		break;
	case NAME_FLOWER_FROST:
		item->type = TYPE_SPECIAL;
		item->img = IMAGEMANAGER->findImage("flower_frost");
		break;
	case NAME_FLOWER_SNAKE:
		item->type = TYPE_SPECIAL;
		item->img = IMAGEMANAGER->findImage("flower_snake");
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

}


void ItemManager::unequipItem(int position)
{
	for ( _viBag = _vBag.begin(); _viBag != _vBag.end(); ++_viBag)
	{
		if (_viBag->position == position)
		{
			_viBag->equip = false;
			switch (_viBag->type)
			{
			case TYPE_WEAPON:
			{

				PLAYERSTAT temp = _player->getStat();

				temp.mindmg -= _viBag->minPoint;
				temp.maxdmg -= _viBag->maxPoint;

				_player->setStat(temp);
			}
				break;
			case TYPE_ARMOR:
			{
				PLAYERSTAT temp = _player->getStat();

				temp.mindef -= _viBag->minPoint;
				temp.maxdef -= _viBag->maxPoint;

				_player->setStat(temp);
			}
				break;
			}

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
			{
				for (int i = 0; i < _vBag.size(); i++)
				{
					if (_vBag[i].type == TYPE_WEAPON && _vBag[i].equip) _vBag[i].equip = false;
				}
				_viBag->equip = true;
				PLAYERSTAT temp = _player->getStat();

				temp.mindmg += _viBag->minPoint;
				temp.maxdmg += _viBag->maxPoint;

				_player->setStat(temp);
			}
				break;
			case TYPE_ARMOR:
			{
				for (int i = 0; i < _vBag.size(); i++)
				{
					if (_vBag[i].type == TYPE_ARMOR && _vBag[i].equip) _vBag[i].equip = false;
				}
				_viBag->equip = true;
				PLAYERSTAT temp = _player->getStat();

				temp.mindef += _viBag->minPoint;
				temp.maxdef += _viBag->maxPoint;

				_player->setStat(temp);
			}
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
	for (_viBag = _vBag.begin(); _viBag != _vBag.end();)
	{
		if (_viBag->position == position)
		{
			switch (_viBag->type)
			{
			case TYPE_FOOD:
				_viBag->numOfItem--;
				PLAYERSTAT temp = _player->getStat();
				temp.hunger +=_viBag->minPoint;
				_player->setStat(temp);
				if (_viBag->numOfItem <= 0) _viBag = _vBag.erase(_viBag);
				goto stop;
				break;
			case TYPE_POTION:
			{
				PLAYERSTAT temp = _player->getStat();

				switch (_viBag->name)
				{
				case NAME_BOTTLE:  // 플레이어 체력*0.05 * currentCharge
				{
					if (_viBag->currentCharge != 0)
					{
						_viBag->currentCharge = 0;
						_player->setHP((_player->getStat().maxhp *0.05)*_viBag->currentCharge);
					}
					else
					{
						//아무런 효과가 발생하지 않는다.
					}
				}
				break;
				case NAME_HEAL: // 플레이어의 체력을 최대 회복.
				{
					_potionIdentified[0] = true;
					_player->setHP(_player->getStat().maxhp);
					_viBag->numOfItem--;
					goto stop;

				}
				break;
				case NAME_STR: // 플레이어의 힘 +1
				{
					temp.str += 1;
					_player->setStat(temp);
	
					_potionIdentified[1] = true;
					_viBag->numOfItem--;
					goto stop;

				}
				break;
				case NAME_EX: // 플레이어의 레벨 +1 , 경험치 0;ㄴ
				{
					temp.lv += 1;
					temp.exp = 0;
					_player->setStat(temp);

					_potionIdentified[2] = true;
					
					

					_viBag->numOfItem--;
					goto stop;

				}
				break;
				case NAME_INVISIBLE: // 플레이어 투명화 버프
				{
					_potionIdentified[3] = true;
					_viBag->numOfItem--;
					goto stop;

				}
				break;
				case NAME_LEVITATION: // 플레이어 공중부양 버프
				{
					_potionIdentified[4] = true;
					_viBag->numOfItem--;
					goto stop;

				}
				break;
				case NAME_FROZEN:	// 플레이어 혹은 던진장소 중심 x 5*5 서리디버프
				{
					_potionIdentified[5] = true;
					_viBag->numOfItem--;
					frozen(_player->getPoint().x, _player->getPoint().y);
					goto stop;
				}
				break;
				case NAME_LIQUID_FIRE: // 플레이어 혹은 던징장소 중심 3*3 화염
				{
					_potionIdentified[6] = true;
					_viBag->numOfItem--;
					liquidFire(_player->getPoint().x, _player->getPoint().y);
					
					goto stop;
				}
				break;
				}
			}
			break;
			case TYPE_SCROLL:
			{
				switch (_viBag->name)
				{
					case NAME_IDENTIFY: // 사용 x
					{

					}
					break;
					case NAME_UPGRADE: // 사용 x
					{

					}
					break;
					case NAME_PURIFY: // 사용 x
					{

					}
					break;
					case NAME_MAP: // 맵의 시야를 밝혀주는용 
					{
						_viBag->numOfItem--;
						for (int i = 0; i < 100; i++)
						{
							for (int j = 0; j < 100; j++)
							{
								TILE temp = _map->getTile(i, j);
								if (temp.tileview == TILEVIEW_NO)
								{
									temp.tileview = TILEVIEW_HALF;
									_map->setTile(temp, i, j);
								}
							}
						}
						goto stop;
					}
					break;
					case NAME_RECHARGE:
					{
						_viBag->numOfItem--;
						for (_viBag = _vBag.begin(); _viBag != _vBag.end(); ++_viBag)
						{
							if (_viBag->type == TYPE_WAND)
							{
								_viBag->currentCharge = _viBag->maxCharge;
							}continue;
						}

						goto stop;
					}
					break;

				default:
					break;
				}
			}
			break;




			default:
				break;
			}
		}
		else  ++_viBag;

	}
	stop:
	for (_viBag = _vBag.begin(); _viBag != _vBag.end();)
	{
		if (_viBag->numOfItem <= 0)
		{
			_viBag = _vBag.erase(_viBag);
		}
		else ++_viBag;
	}

}
void ItemManager::useItem(int position, float x, float y)
{
	for (_viBag = _vBag.begin(); _viBag != _vBag.end();)
	{
		if (_viBag->position == position)
		{
			switch (_viBag->type)
			{
			case TYPE_WAND:
				if (_viBag->currentCharge > 0)
				{
					fire(_viBag->throwImg, x, y);
					_viBag->currentCharge--;
				}
				break;
			case TYPE_SEED:
				switch (_viBag->name)
				{
				case NAME_SEED_HEAL:
					setItemToField(NAME_FLOWER_HEAL, x, y);
					break;
				case NAME_SEED_FIRE:
					setItemToField(NAME_FLOWER_FIRE, x, y);
					break;
				case NAME_SEED_FROST:
					setItemToField(NAME_FLOWER_FROST, x, y);
					break;
				case NAME_SEED_SNAKE:
					setItemToField(NAME_FLOWER_SNAKE, x, y);
					break;
				default:
					break;
				}
				break;
			case TYPE_POTION:
			{
				switch (_viBag->name)
				{
				case NAME_BOTTLE:
				{
					setItemToField(NAME_BOTTLE, x, y);
				}
				break;
				case NAME_HEAL: // 아무런 효과가 발생하지 않는다 ( 아이템 식별 불가 )
				{
					fire(_viBag->throwImg, x, y);
					_viBag->numOfItem--;
					goto stop;
				}
				break;
				case NAME_STR: // 아무런 효과가 발생하지 않는다 ( 아이템 식별 불가 )
				{
					fire(_viBag->img, x, y);
					_viBag->numOfItem--;
					goto stop;
				}
				break;
				case NAME_EX:// 아무런 효과가 발생하지 않는다 ( 아이템 식별 불가 )
				{
					fire(_viBag->img, x, y);
					_viBag->numOfItem--;
					goto stop;
				}
				break;
				case NAME_INVISIBLE:// 아무런 효과가 발생하지 않는다 ( 아이템 식별 불가 )
				{
					fire(_viBag->img, x, y);
					_viBag->numOfItem--;
					goto stop;
				}
				break;
				case NAME_LEVITATION:// 아무런 효과가 발생하지 않는다 ( 아이템 식별 불가 )
				{
					fire(_viBag->img, x, y);
					_viBag->numOfItem--;
					goto stop;
				}
				break;
				case NAME_FROZEN:
				{
					_potionIdentified[5] = true;
					frozen(x, y);
					_viBag->numOfItem--;
					goto stop;
				}
				break;
				case NAME_LIQUID_FIRE:
				{
					_potionIdentified[6] = true;
					liquidFire(x, y);
					_viBag->numOfItem--;
					goto stop;
				}
				break;
				}
			}
			break;
			case TYPE_THROW:
				switch (_viBag->name)
				{
				case NAME_DART:
				{
					fire(_viBag->throwImg, x, y);
					_viBag->numOfItem--;
					goto stop;

				}
				break;

				case NAME_PARALYSIS_DART:
				{
					fire(_viBag->throwImg, x, y);
					_viBag->numOfItem--;
					goto stop;
				}
				break;

				case NAME_POISON_DART:
				{
					fire(_viBag->throwImg, x, y);
					_viBag->numOfItem--;
					goto stop;
				}
				break;


				default:
					break;

				}


				break;
			default:
				break;
			}
			break;
		}
		else  ++_viBag;
	}
	stop:
	for (_viBag = _vBag.begin(); _viBag != _vBag.end();)
	{
		if (_viBag->numOfItem <= 0)
		{
			_viBag = _vBag.erase(_viBag);
		}
		else ++_viBag;
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
					for (_viBag = _vBag.begin(); _viBag != _vBag.end(); ++_viBag)
					{
						if (_viBag->position == target)
						{
							if (_viBag->type == TYPE_ACC || _viBag->type == TYPE_ARMOR || _viBag->type == TYPE_WEAPON)
							{
								_viBag->upgrade++;
								_scrollIdentified[1] = true;
								//_viBag->numOfItem--;
							}
							goto stop;
						}
					}
					break;

					case NAME_IDENTIFY:
					for (_viBag = _vBag.begin(); _viBag != _vBag.end(); ++_viBag)
					{
						if (_viBag->position == target)
						{
							if (_viBag->contentsHide == true)
							{
								_viBag->contentsHide = false;
								_scrollIdentified[0] = true;
								_viBag->numOfItem--;
							}
							goto stop;
						}
					}
					break;

					case NAME_PURIFY:
					for (_viBag = _vBag.begin(); _viBag != _vBag.end(); ++_viBag)
					{
						if (_viBag->position == target)
						{
							if (_viBag->type == TYPE_ACC || _viBag->type == TYPE_ARMOR || _viBag->type == TYPE_WEAPON)
							{
								_viBag->isCursed = false;
								_scrollIdentified[2] = true;
								_viBag->numOfItem--;
							}
							goto stop;
						}
					}
					break;


					default:
					break;
				}
				break;

				default:
				break;
			}
			break;

		}

	}
stop:
	for (_viBag = _vBag.begin(); _viBag != _vBag.end();)
	{
		if (_viBag->numOfItem <= 0)
		{
			_viBag = _vBag.erase(_viBag);
		}
		else ++_viBag;
	}
}

void ItemManager::fire(image* img, float destX, float destY)
{
	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.x = bullet.initX = _player->getPoint().x;
	bullet.y = bullet.initY = _player->getPoint().y;
	bullet.destX = destX;
	bullet.destY = destY;
	bullet.angle = atan2f(bullet.destY - bullet.y, bullet.destX - bullet.x);
	bullet.speed = 7;
	bullet.img = img;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.img->getWidth(), bullet.img->getHeight());
	bullet.fire = true;
	bullet.count = 0;

	_vBullet.push_back(bullet);
}

void ItemManager::throwItem(int position, float destX, float destY)
{
	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.x = bullet.initX = _player->getPoint().x;
	bullet.y = bullet.initY = _player->getPoint().y;
	bullet.destX = destX;
	bullet.destY = destY;
	bullet.angle = atan2f(bullet.destY - bullet.y, bullet.destX - bullet.x);
	bullet.speed = 7;
	bullet.position = position;
	for ( _viBag = _vBag.begin(); _viBag != _vBag.end(); _viBag++)
	{
		if (_viBag->position == bullet.position)
		{
			bullet.img = _viBag->img;
			break;
		}
	}
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.img->getWidth(), bullet.img->getHeight());
	bullet.fire = true;
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
			getDistance(_viThrow->initX, _viThrow->initY, _viThrow->destX, _viThrow->destY)
			|| (_map->getMap(_viThrow->x/TILESIZE, _viThrow->y/TILESIZE).terrain & ATTRIBUTE_UNGO) == ATTRIBUTE_UNGO)
		{
			for ( _viBag = _vBag.begin(); _viBag != _vBag.end(); )
			{
				if (_viBag->position == _viThrow->position)
				{
					setItemToField(_viBag->name, _viThrow->x - cosf(_viThrow->angle)*TILESIZE, 
						_viThrow->y - sinf(_viThrow->angle)*TILESIZE,
						_viBag->contentsHide, _viBag->isCursed, _viBag->upgrade,
						_viBag->numOfItem);
					
					_viBag = _vBag.erase(_viBag);
			
					break;
			
				}
				else ++_viBag;
			}
			_viThrow = _vThrow.erase(_viThrow);
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

void ItemManager::removeFieldItem(int arrNum)
{
	_vItem.erase(_vItem.begin() + arrNum);
}

void ItemManager::removeBagItem(int arrNum)
{
	int j = 0;
	_vBag.erase(_vBag.begin() + arrNum);
	int a = 0;
}	


void ItemManager::liquidFire(float x, float y)
{
	int TileX[3];
	int TileY[3];

	for (int i = 0; i < 3; i++)
	{
		TileX[i] = x / TILESIZE - 2 + i;
		TileY[i] = y / TILESIZE - 2 + i;
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (_player->getPoint().x / TILESIZE == TileX[i] && _player->getPoint().y / TILESIZE == TileY[j])
			{
				for (_viBag = _vBag.begin(); _viBag != _vBag.end();)
				{
					if (_viBag->name == NAME_UNKNOWN_MEAT)
					{
						int temp = _viBag->numOfItem;
						_viBag->numOfItem = 0;
						_viBag = _vBag.erase(_viBag);

						for (int i = 0; i < temp; i++)
						{
							setItemToBag(NAME_COOKED_MEAT);
						}
						break;

					}
					else ++_viBag;
				}
				//����& �����  �߰�
			}
			for (auto k : _em->getEnemyVector())
			{
				if (k->getPoint().x / TILESIZE == TileX[i] && k->getPoint().y / TILESIZE == TileY[j])
				{
					//���� ����� �߰�

				}
			}
			liquidFireEffect(TileX[i], TileY[i]);
			_fire = true;
		}
	}

}

void ItemManager::frozen(float x, float y)
{
	int TileX[5];
	int TileY[5];

	for (int i = 0; i < 5; i++)
	{
		TileX[i] = x/TILESIZE-2  + i;
		TileY[i] = y/TILESIZE-2 + i;
	}

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
		
			if (_player->getPoint().x / TILESIZE == TileX[i] && _player->getPoint().y / TILESIZE == TileY[j])
			{
				for (_viBag = _vBag.begin(); _viBag != _vBag.end();)
				{
					if (_viBag->name == NAME_UNKNOWN_MEAT)
					{
						int temp = _viBag->numOfItem;
						_viBag->numOfItem = 0;
						_viBag = _vBag.erase(_viBag);

						for (int i = 0; i < temp; i++)
						{
							setItemToBag(NAME_FROZEN_MEAT);
						}
						break;

					}
					else ++_viBag;
				}
				//����& �����  �߰�
			}
			for (auto k : _em->getEnemyVector())
			{
				if (k->getPoint().x / TILESIZE == TileX[i] && k->getPoint().y / TILESIZE == TileY[j])
				{
					//���� ����� �߰�

				}
			}
			_frozen = true;
			frozenEffect(TileX[i], TileY[i]);
		}
	}
}


void ItemManager::liquidFireEffect(float x, float y)
{
	for (int i = 0; i < 20; i++)
	{
		fireE[i].rc = RectMakeCenter(RND->getFromIntTo(x*TILESIZE - TILESIZE / 2, x*TILESIZE + TILESIZE / 2), RND->getFromIntTo(y*TILESIZE - TILESIZE / 2, y*TILESIZE + TILESIZE / 2), frozenE[i].size, frozenE[i].size);
	}
}
void ItemManager::frozenEffect(float x, float y)
{
	for (int i = 0; i < 20; i++)
	{
		frozenE[i].rc = RectMakeCenter(RND->getFromIntTo(x*TILESIZE - TILESIZE / 2, x*TILESIZE + TILESIZE / 2), RND->getFromIntTo(y*TILESIZE - TILESIZE / 2, y*TILESIZE + TILESIZE / 2), frozenE[i].size, frozenE[i].size);
	}
}























void ItemManager::keyControl()
{
	if (KEYMANAGER->isOnceKeyDown('T'))
	{
		for ( _viBag = _vBag.begin(); _viBag != _vBag.end(); ++_viBag)
		{
			if (_viBag->name == NAME_NORMAL)
			{
				fire(_viBag->throwImg, _ptMouse.x, _ptMouse.y);
			}
		}
	}
	if (KEYMANAGER->isOnceKeyDown('Y'))
	{
		for ( _viBag = _vBag.begin(); _viBag != _vBag.end(); ++_viBag)
		{
			if (_viBag->name == NAME_OLD_SHORT_SWORD)
			{
				throwItem(_viBag->position, _ptMouse.x, _ptMouse.y);
			}
		}
	}
	if (KEYMANAGER->isOnceKeyDown('R'))
	{
		for (_viBag = _vBag.begin(); _viBag != _vBag.end();)
		{
			if (_viBag->name == NAME_FROZEN)
			{
				useItem(_viBag->position);
				break;
			}
			else ++_viBag;


		}
	}
	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		for (_viBag = _vBag.begin(); _viBag != _vBag.end();)
		{
			if (_viBag->name == NAME_LIQUID_FIRE)
			{
				useItem(_viBag->position);
				break;
			}
			else ++_viBag;


		}
	}

}