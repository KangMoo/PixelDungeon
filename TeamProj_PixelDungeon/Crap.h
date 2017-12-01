#pragma once
#include "Enemy.h"
class Crap :
	public Enemy
{
private:
	image* _stay;
	image* _move;
	image* _attack;
	image* _dead;

	bool _isMove;
	POINT _movePoint;

	int _turnCount;

	int _frameCount;
	vector<TILE> astarTest;

public:
	HRESULT init(POINT point); //초기 생성
	void getDamaged(int damage);
	void update();

	POINT getTilePt() { return _point; }
	POINT getRenderPt() { return PointMake(_pointX, _pointY); }
	POINT getPoint() { return PointMake(_pointX, _pointY); }

	void action();
	void frameUpdate();
	void draw(POINT camera);
	void release();

	Crap();
	~Crap();
};

