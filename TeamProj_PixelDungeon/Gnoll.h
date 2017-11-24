#pragma once
#include "Enemy.h"
class Gnoll :
	public Enemy
{
private:

	image* _stay;
	image* _move;
	image* _attack;
	image* _dead;

	bool _isMove;
	POINT _movePoint;

	int _frameCount;

public:
	HRESULT init(POINT point); //초기 생성
	void getDamaged(int damage);

	void action();
	void frameUpdate();
	void draw(POINT camera);
	void release();

	Gnoll();
	~Gnoll();
};

