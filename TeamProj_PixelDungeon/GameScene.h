#pragma once
#include "gameNode.h"
#include "EnemyManager.h"
#include "Player.h"
#include "Map.h"
#include "UI.h"
#include "ItemManager.h"

class GameScene : public gameNode
{
private:
	EnemyManager* _em;
	Player* _player;
	Map* _map;
	UI* _ui;
	ItemManager* _im;
	POINT _camera;		//camera�� ȭ���� �߽��� ��

public:
	HRESULT init();
	void release();
	void update();
	void render();

	GameScene();
	~GameScene();
};

