#pragma once
#include "Boss.h"
class goo : public Boss
{
private:

	bool _pumpIt;	//5*5 범위 범위공격? 단일공격? 사정거리2칸? 뭐지 뭐하는거지?
	int trunCount;
	POINT _movePt;

public:
	HRESULT init(POINT point, int cog);//인식범위 추기
	void release();
	void update();
	void render(POINT camera);
	void draw(POINT camera);
	void action();

	void attack();
	//void pumpIt();
	void move();
	void frameUpdate();
	//데미지 받았을 때, 회피율 계산하여 함수 만들기
	void getDamaged(int damage);


	goo();
	~goo();
};

