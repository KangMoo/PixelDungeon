#pragma once
#include "gameNode.h"
#include "UI.h"

class EnemyManager;
class Map;
class UI;
class Enemy;
class ItemManager;
class Player : public gameNode
{
private:
	EnemyManager* _em;
	Map* _map;
	UI* _ui;
	ItemManager* _im;
	PLAYERSTAT _playerStat;
	POINT _playerPoint;
	RECT _playerRC;
	image* _image;
	int _currentFrameX, _currentFrameY;
	PLAYERSTATE _playerState;

	int _frameUpdateTimer;
	bool _action;


	//test~
	struct TILE {
		POINT point;
		RECT rc;
		int type;
	};
	TILE tile[20][20];
	vector<TILE> tileCanSee;

	struct sightAngle {
		float sangle;
		float eanlge;
	};

	vector<sightAngle> angleCanTSee;

	//~test

public:
	HRESULT init();
	HRESULT init(POINT point);
	void release();
	void update();
	void render(POINT camera);
	void draw(POINT camera);
	
	void actionCheck();
	void action();

	void frameUpdate();
	void imageChange(const char* str);
	void fovCheck();

	void getDamaged(int damange);

	//게터세터
	bool getAction() { return _action; }
	void setAction(bool action) { _action = action; }
	PLAYERSTAT getStat() { return _playerStat; }
	void setStat(PLAYERSTAT stat) { _playerStat = stat; }
	POINT getPoint() { return _playerPoint; }
	void setPoint(POINT point) { _playerPoint = point; }
	int getHP() { return _playerStat.hp; }
	void setHP(int hp) { _playerStat.hp = hp; }
	bool getTurn() { return _action; }
	void setTurn(bool turn) { _action = turn; }

	void addCanTSeeAngle(float sangle, float eangle);
	void addCanTSeeRect(RECT rc);

	void setEnemyManagerAddressLink(EnemyManager* em) { _em = em; }
	void setMapAddressLink(Map* map) { _map = map; }
	void setUiAddressLink(UI* ui) { _ui = ui; }
	void setItemManagerAddressLink(ItemManager* im) { _im = im; }

	Player();
	~Player();
};

