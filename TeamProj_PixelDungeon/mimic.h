#pragma once
#include "Enemy.h"
class Mimic : public Enemy
{
private:

	bool _playerChack; //플레이어가 건드렸는지 여부
	int money;

	POINT _movePt;

	vector<TILE> astar;

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

	void itemDrop();
	//데미지 받았을 때, 회피율 계산하여 함수 만들기
	void getDamaged(int damage);

	Mimic();
	~Mimic();
};

