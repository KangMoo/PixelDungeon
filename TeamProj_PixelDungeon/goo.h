#pragma once
#include "Boss.h"
class goo : public Boss
{
private:

	bool pumpIt;	//5*5 ���� ��������
	int trunCount;

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
	//������ �޾��� ��, ȸ���� ����Ͽ� �Լ� �����
	void getDamaged(int damage);


	goo();
	~goo();
};

