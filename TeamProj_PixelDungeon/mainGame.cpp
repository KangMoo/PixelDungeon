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

	//============================= S O U N D ================================

	SOUNDMANAGER->addSound("00.alert", "sound/snd_alert.mp3", false, false);
	SOUNDMANAGER->addSound("01.badge", "sound/snd_badge.mp3", false, false);
	SOUNDMANAGER->addSound("02.beacon", "sound/snd_beacon.mp3", false, false);
	SOUNDMANAGER->addSound("03.bee", "sound/snd_bee.mp3", false, false);
	SOUNDMANAGER->addSound("04.blast", "sound/snd_blast.mp3", false, false);
	SOUNDMANAGER->addSound("05.bonse", "sound/snd_bonse.mp3", false, false);
	SOUNDMANAGER->addSound("06.boss", "sound/snd_boss.mp3", false, false);
	SOUNDMANAGER->addSound("07.burning", "sound/snd_burning.mp3", true, false);
	SOUNDMANAGER->addSound("08.challenge", "sound/snd_challenge.mp3", false, false);
	SOUNDMANAGER->addSound("09.charms", "sound/snd_charms.mp3", false, false);
	SOUNDMANAGER->addSound("10.click", "sound/snd_click.mp3", false, false);
	SOUNDMANAGER->addSound("11.cursed", "sound/snd_cursed.mp3", false, false);
	SOUNDMANAGER->addSound("12.death", "sound/snd_death.mp3", false, false);
	SOUNDMANAGER->addSound("13.degrade", "sound/snd_degrade.mp3", false, false);
	SOUNDMANAGER->addSound("14.descend", "sound/snd_descend.mp3", false, false);
	SOUNDMANAGER->addSound("15.dewdrop", "sound/snd_dewdrop.mp3", false, false);
	SOUNDMANAGER->addSound("16.door_open", "sound/snd_door_open.mp3", false, false);
	SOUNDMANAGER->addSound("17.drink", "sound/snd_drink.mp3", false, false);
	SOUNDMANAGER->addSound("18.eat", "sound/snd_eat.mp3", false, false);
	SOUNDMANAGER->addSound("19.evoke", "sound/snd_evoke.mp3", false, false);
	SOUNDMANAGER->addSound("20.falling", "sound/snd_falling.mp3", false, false);
	SOUNDMANAGER->addSound("21.ghost", "sound/snd_ghost.mp3", false, false);
	SOUNDMANAGER->addSound("22.gold", "sound/snd_gold.mp3", false, false);
	SOUNDMANAGER->addSound("23.hit", "sound/snd_hit.mp3", false, false);
	SOUNDMANAGER->addSound("24.item", "sound/snd_item.mp3", false, false);
	SOUNDMANAGER->addSound("25.levelup", "sound/snd_levelup.mp3", false, false);
	SOUNDMANAGER->addSound("26.lightning", "sound/snd_lightning.mp3", false, false);
	SOUNDMANAGER->addSound("27.lullaby", "sound/snd_lullaby.mp3", false, false);
	SOUNDMANAGER->addSound("28.mastery", "sound/snd_mastery.mp3", false, false);
	SOUNDMANAGER->addSound("29.meld", "sound/snd_meld.mp3", false, false);
	SOUNDMANAGER->addSound("30.mimic", "sound/snd_mimic.mp3", false, false);
	SOUNDMANAGER->addSound("31.miss", "sound/snd_miss.mp3", false, false);
	SOUNDMANAGER->addSound("32.plant", "sound/snd_plant.mp3", false, false);
	SOUNDMANAGER->addSound("33.puff", "sound/snd_puff.mp3", false, false);
	SOUNDMANAGER->addSound("34.ray", "sound/snd_ray.mp3", false, false);
	SOUNDMANAGER->addSound("35.read", "sound/snd_read.mp3", false, false);
	SOUNDMANAGER->addSound("36.rocks", "sound/snd_rocks.mp3", false, false);
	SOUNDMANAGER->addSound("37.secret", "sound/snd_secret.mp3", false, false);
	SOUNDMANAGER->addSound("38.shatter", "sound/snd_shatter.mp3", false, false);
	SOUNDMANAGER->addSound("39.step", "sound/snd_step.mp3", false, false);
	SOUNDMANAGER->addSound("40.teleport", "sound/snd_teleport.mp3", false, false);
	SOUNDMANAGER->addSound("41.tomb", "sound/snd_tomb.mp3", false, false);
	SOUNDMANAGER->addSound("42.trap", "sound/snd_trap.mp3", false, false);
	SOUNDMANAGER->addSound("43.unlock", "sound/snd_unlock.mp3", false, false);
	SOUNDMANAGER->addSound("44.water", "sound/snd_water.mp3", false, false);
	SOUNDMANAGER->addSound("45.zap", "sound/snd_zap.mp3", false, false);
	SOUNDMANAGER->addSound("46.main", "sound/bgm_background_main.mp3", true, true);
	SOUNDMANAGER->addSound("47.game", "sound/bgm_background_game.mp3", true, true);
	SOUNDMANAGER->addSound("48.map", "sound/bgm_background_map.mp3", true, true);



	//=========================== S C E N E   M A N A G E R ============================
	SCENEMANAGER->addScene("���Ӿ�", new GameScene);
	SCENEMANAGER->addScene("���θ޴���", new MainMenuScene);
	SCENEMANAGER->addScene("������", new MapToolScene);
	SCENEMANAGER->changeScene("���θ޴���");
	return S_OK;
}

void mainGame::release(void)
{
	
}


void mainGame::update(void)	
{
	gameNode::update();

	SCENEMANAGER->update();

	SOUNDMANAGER->update();
}


void mainGame::render(void)	
{
	//��� ��ȭ�� �� �� �ʿ�
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==============================================================

	SCENEMANAGER->render();
	
	
	//========================================================================
	//����ۿ� �ִ°� HDC�� �׷��ִ� ����
	this->getBackBuffer()->render(getHDC(), 0, 0);

}