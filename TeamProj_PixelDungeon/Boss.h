#pragma once
#include "gameNode.h"
#include "Map.h"
#include "UI.h"

class Player;
class UI;
class Boss : public gameNode
{
private:
	Player* _player;													//플레이어 정보
	UI* _ui;															//ui
	Map* _map;


public:
	HRESULT init();
	virtual HRESULT init(POINT point);
	void release();
	void update();
	void render();
	void render(POINT camera);
	void draw(POINT camera);

	void setPlayerAddressLink(Player* player) { _player = player; }
	void setUiAddressLink(UI* ui) { _ui = ui; }
	void setMapAddressLink(Map* map) { _map = map; }

	Boss();
	~Boss();
};

