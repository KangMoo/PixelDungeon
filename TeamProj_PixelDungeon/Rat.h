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
	POINT _movePt;

public:
	virtual HRESULT init(POINT point, int cog);//�νĹ��� �߱�
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

	Rat();
	~Rat();
};

