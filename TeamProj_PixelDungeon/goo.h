#pragma once
#include "Boss.h"
class goo : public Boss
{
private:

	bool _pumpIt;	//5*5 ���� ��������? ���ϰ���? �����Ÿ�2ĭ? ���� ���ϴ°���?
	int trunCount;
	POINT _movePt;

public:
	HRESULT init(POINT point, int cog);//�νĹ��� �߱�
	void release();
	void update();
	void render(POINT camera);
	void draw(POINT camera);
	void action();

	void attack();
	//void pumpIt();
	void move();
	void frameUpdate();
	//������ �޾��� ��, ȸ���� ����Ͽ� �Լ� �����
	void getDamaged(int damage);


	goo();
	~goo();
};

