#pragma once
#include "Enemy.h"

//��� ���� �ΰ����Դϴ�
enum MYCOLOR
{
	BROWN,
	WHITE
};

class Rat : public Enemy
{
private:

	int _color;		//�������� ������ ���� ���� ��
	int _myColor;	//�� ���� �����
	POINT _movePt;	//�����̱� ���� ����Ʈ
	RECT attackRange;
	vector<TILE> astar;

	//image* wIdle, *wAttack, *wMove, *wDead;
	//image* bIdle, *bAttack, *bMove, *bDead;

public:
	virtual HRESULT init(POINT point);//�νĹ��� �߱�
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

