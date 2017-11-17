#include "stdafx.h"
#include "GameScene.h"


GameScene::GameScene()
{
}


GameScene::~GameScene()
{

}
HRESULT GameScene::init()
{
	_em = new EnemyManager;
	_player = new Player;
	_map = new Map;
	_ui = new UI;
	_im = new ItemManager;

	//상호참조 연결
	_map->setEnemyManagerAddressLink(_em);
	_map->setPlayerAddressLink(_player);
	_map->setUiAddressLink(_ui);
	_map->setItemManagerAddressLink(_im);
	_player->setEnemyManagerAddressLink(_em);
	_player->setMapAddressLink(_map);
	_player->setUiAddressLink(_ui);
	_player->setItemManagerAddressLink(_im);
	_em->setPlayerAddressLink(_player);
	_em->setMapAddressLink(_map);
	_em->setUiAddressLink(_ui);
	_em->setItemManagerAddressLink(_im);
	_ui->setPlayerAddressLink(_player);
	_ui->setMapAddressLink(_map);
	_ui->setEnemyManagerAddressLink(_em);
	_ui->setItemManagerAddressLink(_im);
	_im->setEnemyManagerAddressLink(_em);
	_im->setMapAddressLink(_map);
	_im->setUiAddressLink(_ui); 
	_im->setPlayerAddressLink(_player);

	//초기화
	_ui->init();
	_map->init();
	_player->init();
	_em->init();
	_im->init();

	_player->setAction(true);
	_camera = PointMake(WINSIZEX, WINSIZEY);

	return S_OK;
}
void GameScene::release()
{

}
void GameScene::update()
{
	_em->update();
	_player->update();
	_ui->update();
	_map->update();

	//ui로부터 카메라 정보 받아오기
	_camera = _ui->getCamera();

	SOUNDMANAGER->update();


}
void GameScene::render()
{
	_map->render(PointMake(WINSIZEX / 2 - _camera.x, WINSIZEY / 2 - _camera.y));
	_em->render(PointMake(WINSIZEX / 2 - _camera.x, WINSIZEY / 2 - _camera.y));
	_player->render(PointMake(WINSIZEX / 2 - _camera.x, WINSIZEY / 2 - _camera.y));
	_ui->render(PointMake(WINSIZEX / 2 - _camera.x, WINSIZEY / 2 - _camera.y));

	//test~
	TextOut(getMemDC(), 100, 100, "게임씬", strlen("게임씬"));
	//~test
}