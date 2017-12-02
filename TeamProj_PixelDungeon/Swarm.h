#pragma once
#include "Enemy.h"

#include "EnemyManager.h"

class Swarm :
	public Enemy
{
private:
	/*
	progressBar* _hpBar;	//체력바

	ENEMYSTAT _statistics;	//몬스터 스텟
	POINT _point;				//좌표
	image* _image;				//그려줄 이미지~
	bool _action;				//액션값이 참일 경우 몬스터 행동

	RECT _hitBox;			//히트박스
	RECT _attBox;			//공격렉트 생성할 박스입니다. 초기화 꼭 해주셔야 합니다.
	bool _isLive;			//생존여부
	bool _right;			//오른쪽을 바라보고 있는지 여부
	bool _findPlayer;

	int _currntFrameX, _currntFrameY;	//프레임
	int _pointX, _pointY;				//혹시 몰라 만들어두었습니다.....
	int _currntHp;						//maxHp는 statistics.hp 에 있습니다, hpHar용입니다.
	int _myState;						//현재 상태
	*/
	image* _move;
	image* _dead;

	bool _isMove;
	POINT _movePoint;

	int _frameCount;

	vector<TILE> astarTest;
	EnemyManager* _em;
	
	int _deadAlpha;

public:
	HRESULT init(POINT point, int floor); //초기 생성
	HRESULT init(POINT point, int currntHp, int floor); //분열
	void update();

	POINT getTilePt() { return _point; }
	POINT getRenderPt() { return PointMake(_pointX, _pointY); }
	POINT getPoint() { return PointMake(_pointX, _pointY); }

	void getDamaged(int damage);

	void action(); 
	void frameUpdate();
	void draw(POINT camera);
	void release();

	void setEm(EnemyManager* em) { _em = em; }
	bool getLive() { return _isLive; }

	Swarm();
	~Swarm();
};

