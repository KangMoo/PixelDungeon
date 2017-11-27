#pragma once
#include "gameNode.h"
#include "UI.h"

struct sightAngle {
	float sangle;
	float eangle;
};

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
	TILE* _maptile;
	int _currentFrameX, _currentFrameY;
	PLAYERSTATE _playerState;
	vector<tagDebuff> _vdebuff;
	int _frameUpdateTimer;
	float _frameTimer;
	TILE _goalTile;
	bool _action;
	bool _keepMove;
	

	//test~
	vector<TILE> tileCanSee;
	vector<sightAngle> angleCanTSee;
	vector<TILE> astar;
	//~test

public:
	HRESULT init();
	HRESULT init(POINT point);
	void release();
	void update();
	void render(POINT camera);
	void draw(POINT camera);
	
	void addImg();
	void frameUpdate();


	void actionCheck();
	void action();

	//이미지 변환
	void imageChange(const char* str);
	
	void move();

	void getDamaged(int damange);

	//시야처리 함수
	void addCanTSeeAngle(float sangle, float eangle);
	void addCanTSeeAngleByRect(RECT rc);
	void fovCheck();


	//디버프 추가
	void addDebuff(DEBUFF debuffType, int lefttime, int damage);

	//행동 명령
	void action_Move(POINT point);
	void action_Attack(POINT point);
	void action_Scroll();
	void action_Eat();

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
	vector<tagDebuff> getPlayerDebuffList() { return _vdebuff; }
	void setPlayerDebuffList(vector<tagDebuff> vDbuff) { _vdebuff = _vdebuff; }

	

	void setEnemyManagerAddressLink(EnemyManager* em) { _em = em; }
	void setMapAddressLink(Map* map) { _map = map; }
	void setUiAddressLink(UI* ui) { _ui = ui; }
	void setItemManagerAddressLink(ItemManager* im) { _im = im; }

	Player();
	~Player();
};

