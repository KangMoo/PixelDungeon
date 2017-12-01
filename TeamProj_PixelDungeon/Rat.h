#pragma once
#include "Enemy.h"

//쥐는 색이 두가지입니다
enum MYCOLOR
{
	BROWN,
	WHITE
};

class Rat : public Enemy
{
private:

	int _color;		//랜덤으로 나오기 위한 그의 색
	int _myColor;	//그 색의 결과값
	POINT _movePt;	//움직이기 위한 포인트
	RECT attackRange;
	vector<TILE> astar;

	//image* wIdle, *wAttack, *wMove, *wDead;
	//image* bIdle, *bAttack, *bMove, *bDead;

public:
	virtual HRESULT init(POINT point);//인식범위 추기
	void release();
	void update();
	void render(POINT camera);
	void draw(POINT camera);
	void action();

	void attack();
	void move();
	void frameUpdate();
	//데미지 받았을 때, 회피율 계산하여 함수 만들기
	void getDamaged(int damage);

	Rat();
	~Rat();
};

