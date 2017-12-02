#pragma once
#include "Enemy.h"
#include "progressBar.h"

class goo : public Enemy
{
private:

	bool _PumpedUP;	//자신 중심 5*5 단일공격
	bool _isMove;
	int _trunCount;
	POINT _movePoint;	//움직이기 위한 포인트


	RECT skillRange;
	vector<TILE> aStar;

	image* _stay, *_move, *_dead;

public:
	HRESULT init(POINT point, int floor);//인식범위 추기
	void release();
	void update();
	void draw(POINT camera);
	void action();

	void frameUpdate();
	//데미지 받았을 때, 회피율 계산하여 함수 만들기
	void getDamaged(int damage);

	progressBar* _hpBar;	//체력바

	goo();
	~goo();
};

