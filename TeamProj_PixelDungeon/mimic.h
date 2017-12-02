#pragma once
#include "Enemy.h"
class Mimic : public Enemy
{
private:

	bool _playerChack; //플레이어가 건드렸는지 여부
	bool _isMove;
	int money;

	POINT _movePoint;

	vector<TILE> astar;

	//뭐지 스테이가 공격인가? 뭐지?
	//2017-02-02, 디스에이블 이미지는 무의미할것으로 판단하여 삭제함
	image *move, *stay, *dead;

public:
	virtual HRESULT init(POINT point);//인식범위 추기
	void release();
	void update();
	void draw(POINT camera);
	void action();

	void frameUpdate();
	//데미지 받았을 때, 회피율 계산하여 함수 만들기
	void getDamaged(int damage);


	Mimic();
	~Mimic();
};

