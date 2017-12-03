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
	addImg();
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
	_player->init(PointMake(0,0));
	_em->init();
	_im->init();

	SOUNDMANAGER->play("47.game", 1.0);

	_player->setAction(true);
	_camera = PointMake(WINSIZEX, WINSIZEY);

	return S_OK;
}
void GameScene::release()
{
	SOUNDMANAGER->stop("47.game");
}
void GameScene::update()
{
	_em->update();
	_ui->update();
	_player->update();
	_map->update();
	_im->update();
	//ui로부터 카메라 정보 받아오기
	_camera = _ui->getCamera();

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		_ui->LbuttonClickEvnet();
		if (!_ui->usingInterface())
		{
			_player->mouseClickEvent();
		}
		
	}
	SOUNDMANAGER->update();


}
void GameScene::render()
{
	_map->render(_camera);
	_im->render(_camera);
	_em->render(_camera);
	_player->render(_camera);
	_ui->render(_camera);

}

void GameScene::addImg()
{
	IMAGEMANAGER->addImage("blackTile", "Img//Map//blacktile.bmp", 32, 32, true, RGB(255, 0, 255));
}