#include "stdafx.h"
#include "mainGame.h"

mainGame::mainGame()
{
}


mainGame::~mainGame()
{

}


HRESULT mainGame::init(void)
{
	gameNode::init(true);
	
	IMAGEMANAGER->addFrameImage("mapTiles", "Img/Map/tiles_sewers.bmp", 0, 0, 512, 512, 16, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("chest", "Img/Map/chest.bmp", 0, 0, 32, 32, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("water", "Img/Map/water0.bmp", 0, 0, 32, 32, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("trap", "Img/Map/trap.bmp", 0, 0, 512, 256, 16, 8, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("well_health", "Img/Map/well.bmp", 0, 0, 1696, 32, 53, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("pot", "Img/Map/pot.bmp", 0, 0, 1600, 32, 50, 1, true, RGB(255, 0, 255));


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
	IMAGEMANAGER->addImage("emergency_food", "Img/Item/emergency_food.bmp", 32, 32, true, RGB(255, 0, 255));
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
	IMAGEMANAGER->addImage("magic_missile", "Img/Item/magic_missile.bmp", 16, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("magic_missile_lightning", "Img/Item/magic_missile_lightning.bmp", 16, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("magic_missile_poison", "Img/Item/magic_missile_poison.bmp", 16, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("magic_missile_beacon", "Img/Item/magic_missile_beacon.bmp", 16, 16, true, RGB(255, 0, 255));
	//=========================== F L O W E R =============================
	IMAGEMANAGER->addImage("flower_fire", "Img/Item/flower_fire.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("flower_frost", "Img/Item/flower_frost.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("flower_heal", "Img/Item/flower_heal.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("flower_snake", "Img/Item/flower_snake.bmp", 32, 32, true, RGB(255, 0, 255));
	//=========================== K E Y ===================================
	IMAGEMANAGER->addImage("key_iron", "Img/Item/key_iron.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("key_silver", "Img/Item/key_silver.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("key_gold", "Img/Item/key_gold.bmp", 32, 32, true, RGB(255, 0, 255));
	//=========================== E F F E C T =============================
	IMAGEMANAGER->addImage("effectFrozen", "Img/Item/effect_snow.bmp", 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("effectFire", "Img/Item/effect_fire.bmp", 4, 4, true, RGB(255, 0, 255));


	SCENEMANAGER->addScene("게임씬", new GameScene);
	SCENEMANAGER->addScene("메인메뉴씬", new MainMenuScene);
	SCENEMANAGER->addScene("맵툴씬", new MapToolScene);
	SCENEMANAGER->changeScene("메인메뉴씬");
	return S_OK;
}

void mainGame::release(void)
{
	
}


void mainGame::update(void)	
{
	gameNode::update();

	SCENEMANAGER->update();

}


void mainGame::render(void)	
{
	//흰색 도화지 한 장 필요
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==============================================================

	SCENEMANAGER->render();
	
	
	//========================================================================
	//백버퍼에 있는걸 HDC로 그려주는 역할
	this->getBackBuffer()->render(getHDC(), 0, 0);

}