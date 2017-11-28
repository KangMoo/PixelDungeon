#pragma once
#include "Boss.h"
class goo : public Boss
{
private:

	bool pumpIt;	//5*5 범위 범위공격
	int trunCount;

public:
	HRESULT init(POINT point, int cog);//인식범위 추기
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


	goo();
	~goo();
};

