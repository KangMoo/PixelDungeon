#pragma once
#include "gameNode.h"
#include "UI.h"
#include "Enemy.h"
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
	Enemy* _TargetEnemy;
	ItemManager* _im;
	PLAYERSTAT _playerStat;
	POINT _playerPoint;
	RECT _playerRC;
	image* _image;
	TILE* _maptile;
	int _currentFrameX, _currentFrameY;
	PLAYERSTATE _playerState;
	vector<tagDebuff> _vdebuff;
	vector<tagDebuff> _vbuff;
	int _frameUpdateTimer;
	float _frameTimer;
	TILE _goalTile;
	bool _action;
	bool _keepMove;
	bool _isUsingUI;
	bool _isEnemyTargeted;
	
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
	void mouseClickEvent();
	//�̹��� ��ȯ
	void imageChange(const char* str);
	
	void move();
	void getDamaged(int damage);

	//�þ�ó�� �Լ�
	void addCanTSeeAngle(float sangle, float eangle);
	void addCanTSeeAngleByRect(RECT rc);
	void fovCheck();


	//����, ����� �߰�
	void addDebuff(DEBUFF debuffType, int lefttime, int damage);
	void addBuff(BUFF buffType, int lefttime);

	//����, ����� ȿ�� ����
	void effectDebuff();
	void effectBuff();

	//�ൿ ���
	void action_Move(POINT point);
	void action_Attack();
	void action_Scroll();
	void action_Eat();
	void endTurn();
	void expUp(int exp);

	//���ߴ� �Լ�
	void stopMoving();

	//���ͼ���

	bool getAction() { return _action; }
	void setAction(bool action) { _action = action; }
	bool getTurn() { return _action; }
	void setTurn(bool turn) { _action = turn; }

	void activeTurn();

	//PLAYERSTATE getAction() { return _playerState; }
	PLAYERSTAT getStat() { return _playerStat; }
	void setStat(PLAYERSTAT stat) { _playerStat = stat; }
	POINT getPoint() { return _playerPoint; }
	void setPoint(POINT point) { _playerPoint = point; }
	float getHP() { return _playerStat.hp; }
	void setHP(int hp) { _playerStat.hp = hp; }

	vector<tagDebuff> getPlayerDebuffList() { return _vdebuff; }
	void setPlayerDebuffList(vector<tagDebuff> vDbuff) { _vdebuff = _vdebuff; }
	vector<tagDebuff> getPlayerBuffList() { return _vbuff; }
	void setPlayerBuffList(vector<tagDebuff> vBuff) { _vbuff = vBuff; }

	bool getUsingUI() { return _isUsingUI; }
	void setUsingUI(bool usingUI) { _isUsingUI = usingUI; }
	vector<TILE> getPlayerRoute() { return astar; }
	bool getIsPlayerMoving() { return _keepMove; }

	void setEnemyManagerAddressLink(EnemyManager* em) { _em = em; }
	void setMapAddressLink(Map* map) { _map = map; }
	void setUiAddressLink(UI* ui) { _ui = ui; }
	void setItemManagerAddressLink(ItemManager* im) { _im = im; }
	void setChangeFoor();
	Player();
	~Player();

	//����
	bool damaged = false;
	int monster_attack_dp = 0;

	bool attack = false;
	bool player_attack_dp = false;
};

