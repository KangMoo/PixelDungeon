#pragma once
#include "Enemy.h"
class Mimic : public Enemy
{
private:

	bool _playerChack; //�÷��̾ �ǵ�ȴ��� ����
	int money;

	POINT _movePt;

	vector<TILE> astar;

public:
	HRESULT init(POINT point, int cog);//�νĹ��� �߱�
	void release();
	void update();
	void render(POINT camera);
	void draw(POINT camera);
	void action();

	void attack();
	void move();
	void frameUpdate();

	void itemDrop();
	//������ �޾��� ��, ȸ���� ����Ͽ� �Լ� �����
	void getDamaged(int damage);

	Mimic();
	~Mimic();
};

