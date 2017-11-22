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

	item.name = name;


	switch (name)
	{
	case NAME_OLD_SHORT_SWORD:
		item.type = TYPE_WEAPON;
		item.img = IMAGEMANAGER->findImage("old_short_sword");
		item.equip = false;
		item.isCursed = false;
		item.range = 1;
		item.minPoint= 1 + item.upgrade * 2;
		item.maxPoint= 10 + item.upgrade * 2;
		item.tier = 1;
		item.Power = 10;
		item.upgrade = 0;
		break;
	case NAME_SHORT_SWORD:
		item.type = TYPE_WEAPON;
		item.img = IMAGEMANAGER->findImage("short_sword");
		item.equip = false;
		item.isCursed = false;
		item.minPoint = 2 + item.upgrade * 2;
		item.maxPoint = 15 + item.upgrade * 2;
		item.tier = 2;
		item.Power = 12;
		item.range = 1;
		item.upgrade = 0;
		break;
	case NAME_SWORD:
		item.type = TYPE_WEAPON;
		item.img = IMAGEMANAGER->findImage("sword");
		item.equip = false;
		item.isCursed = false;
		item.minPoint = 3 + item.upgrade * 2;
		item.maxPoint = 20 + item.upgrade * 2;
		item.tier = 3;
		item.Power = 14;
		item.range = 1;
		item.upgrade = 0;
		break;
	case NAME_SPEAR:
		item.type = TYPE_WEAPON;
		item.img = IMAGEMANAGER->findImage("spear");
		item.equip = false;
		item.isCursed = false;
		item.minPoint = 2 + item.upgrade * 2;
		item.maxPoint = 20 + item.upgrade * 2;
		item.tier = 2;
		item.Power = 12;
		item.range = 2;
		item.upgrade = 0;
		break;
	case NAME_BATTLE_AXE:
		item.type = TYPE_WEAPON;
		item.img = IMAGEMANAGER->findImage("hammer");
		item.equip = false;
		item.isCursed = false;
		item.minPoint = 4 + item.upgrade * 2;
		item.maxPoint = 20 + item.upgrade * 2;
		item.tier = 4;
		item.Power = 16;
		item.range = 1;
		item.upgrade = 0;
		item.stat.atk_lck = 5;
		break;
	case NAME_CLOTH:
		item.type = TYPE_ARMOR;
		item.img = IMAGEMANAGER->findImage("cloth");
		item.equip = false;
		item.isCursed = false;
		item.minPoint = 0 + item.upgrade;
		item.maxPoint = 2 + item.upgrade;
		item.tier = 1;
		item.Power = 10;
		item.upgrade = 0;
		break;
	case NAME_LEATHER:
		item.type = TYPE_ARMOR;
		item.img = IMAGEMANAGER->findImage("leather");
		item.equip = false;
		item.isCursed = false;
		item.minPoint = 0 + item.upgrade;
		item.maxPoint = 4 + item.upgrade;
		item.tier = 2;
		item.Power = 12;
		item.upgrade = 0;
		break;
	case NAME_MAIL:
		item.type = TYPE_ARMOR;
		item.img = IMAGEMANAGER->findImage("mail");
		item.equip = false;
		item.isCursed = false;
		item.minPoint = 0 + item.upgrade;
		item.maxPoint = 6 + item.upgrade;
		item.tier = 3;
		item.Power = 14;
		item.upgrade = 0;
		break;
	case NAME_RING_POWER:
		item.type = TYPE_ACC;
		switch (_acc[0])
		{
		case 0:
			item.img = IMAGEMANAGER->findImage("ring_blue");
			break;
		case 1:
			item.img = IMAGEMANAGER->findImage("ring_red");
			break;
		}
		item.equip = false;
		item.isCursed = false;
		item.upgrade = 0;
		item.stat.str = 1 + item.upgrade;
		break;
	case NAME_RING_RECHARGE:
		item.type = TYPE_ACC;
		switch (_acc[1])
		{
		case 0:
			item.img = IMAGEMANAGER->findImage("ring_blue");
			break;
		case 1:
			item.img = IMAGEMANAGER->findImage("ring_red");
			break;
		}
		item.equip = false;
		item.isCursed = false;
		item.upgrade = 0;
		break;
	case NAME_LIOYDS_BEACON:
		item.type = TYPE_ACC;
		item.img = IMAGEMANAGER->findImage("acc_wand");
		item.throwImg = IMAGEMANAGER->findImage("magic_missile_beacon");
		item.equip = false;
		item.isCursed = false;
		item.maxCharge = 3 + item.upgrade;
		item.currentCharge = item.maxCharge;
		item.range = 4;
		item.upgrade = 0;
		break;
	case NAME_DART:
		break;
	case NAME_PARALYSIS_DART:
		break;
	case NAME_POISON_DART:
		break;
	case NAME_LIGHTNING:
		item.type = TYPE_WAND;
		item.img = IMAGEMANAGER->findImage("wand_lightning");
		item.throwImg = IMAGEMANAGER->findImage("magic_missile_lightning");
		item.equip = false;
		item.isCursed = false;
		item.minPoint = 4 + item.upgrade * 2;
		item.maxPoint = 10 + item.upgrade * 2;
		item.maxCharge = 3 + item.upgrade;
		item.currentCharge = item.maxCharge;
		item.range = 4;
		item.upgrade = 0;
		break;
	case NAME_NORMAL:
		item.type = TYPE_WAND;
		item.img = IMAGEMANAGER->findImage("wand_normal");
		item.throwImg = IMAGEMANAGER->findImage("magic_missile");
		item.equip = false;
		item.isCursed = false;
		item.minPoint = 4 + item.upgrade * 2;
		item.maxPoint = 6 + item.upgrade * 2;
		item.maxCharge = 4 + item.upgrade;
		item.currentCharge = item.maxCharge;
		item.range = 4;
		item.upgrade = 0;
		break;
	case NAME_POISON:
		item.type = TYPE_WAND;
		item.img = IMAGEMANAGER->findImage("wand_poison");
		item.throwImg = IMAGEMANAGER->findImage("magic_missile_poison");
		item.equip = false;
		item.isCursed = false;
		item.minPoint = 4 + item.upgrade * 2;
		item.maxPoint = 6 + item.upgrade * 2;
		item.maxCharge = 3 + item.upgrade;
		item.currentCharge = item.maxCharge;
		item.range = 4;
		item.upgrade = 0;
		break;
	case NAME_EMERGENCY:
		item.type = TYPE_FOOD;
		item.img = IMAGEMANAGER->findImage("emergency_food");
		item.minPoint = 220;
		break;
	case NAME_PASTY:
		item.type = TYPE_FOOD;
		item.img = IMAGEMANAGER->findImage("pasty");
		item.minPoint = 300;
		break;
	case NAME_UNKNOWN_MEAT:
		item.type = TYPE_FOOD;
		item.img = IMAGEMANAGER->findImage("meat_unknown");
		item.minPoint = 80;
		break;
	case NAME_COOKED_MEAT:
		item.type = TYPE_FOOD;
		item.img = IMAGEMANAGER->findImage("meat_cooked");
		item.minPoint = 80;
		break;
	case NAME_FROZEN_MEAT:
		item.type = TYPE_FOOD;
		item.img = IMAGEMANAGER->findImage("meat_frozen");
		item.minPoint = 80;
		break;
	case NAME_IDENTIFY:
		break;
	case NAME_UPGRADE:
		break;
	case NAME_PURIFY:
		break;
	case NAME_MAP:
		break;
	case NAME_RECHARGE:
		break;
	case NAME_DEW:
		break;
	case NAME_HEAL:
		break;
	case NAME_STR:
		break;
	case NAME_EX:
		break;
	case NAME_INVISIBLE:
		break;
	case NAME_LEVITATION:
		break;
	case NAME_FORZEN:
		break;
	case NAME_LIQUID_FIRE:
		break;
	case NAME_SEED_HEAL:
		break;
	case NAME_SEED_FIRE:
		break;
	case NAME_SEED_SNAKE:
		break;
	case NAME_SEED_FROST:
		break;
	}

	for (_viBag = _vBag.begin(); _viBag != _vBag.end(); ++_viBag)
	{
		if (_viBag->name == item.name && (item.type == TYPE_SCROLL ||
			item.type == TYPE_SEED || item.type == TYPE_POTION))
		{
			overlap = true;
			_viBag->numOfItem++;
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

		item.numOfItem = 1;

		_vBag.push_back(item);

	}

}

void ItemManager::setItemToField(ITEMNAME name)
{

}

void ItemManager::setItemToBag(ITEMNAME name, bool identify, bool isCursed, int upgrade)
{

}
void ItemManager::setItemToField(ITEMNAME name, bool identyfy, bool isCursed, int upgrade)
{

}


void ItemManager::swap()
{
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
		int dest;
		int sour;
		int temp;

		dest = RND->getInt(7);
		sour = RND->getInt(7);
		
		temp = _potion[dest];
		_potion[dest] = _potion[sour];
		_potion[sour] = temp;
	}

	for (int i = 0; i < 10; i++)
	{
		int dest;
		int sour;
		int temp;

		dest = RND->getInt(3);
		sour = RND->getInt(3);

		temp = _wand[dest];
		_wand[dest] = _wand[sour];
		_wand[sour] = temp;
	}

	for (int i = 0; i < 10; i++)
	{
		int dest;
		int sour;
		int temp;

		dest = RND->getInt(5);
		sour = RND->getInt(5);

		temp = _scroll[dest];
		_scroll[dest] = _scroll[sour];
		_scroll[sour] = temp;
	}

	for (int i = 0; i < 10; i++)
	{
		int dest;
		int sour;
		int temp;

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
	IMAGEMANAGER->addImage("potion_dew", "Img/Item/bottle.bmp", 32, 32, true, RGB(255, 0, 255));
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
}