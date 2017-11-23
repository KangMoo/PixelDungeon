#pragma once
#include "Enemy.h"
enum MYCOLOR
{
	BROWN,
	WHITE
};
class Rat : public Enemy
{
private:

	int _color;
	int _myColor;

public:
	HRESULT init(POINT point, int cog); //포인트 추가
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

