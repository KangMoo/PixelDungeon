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
	POINT _movePoint;	//�����̱� ���� ����Ʈ
	RECT attackRange;
	vector<TILE> aStar;
	vector<TILE> temp;

	bool _isMove;

	image* wIdle, *wAttack, *wMove, *wDead;
	image* bIdle, *bAttack, *bMove, *bDead;

public:
	virtual HRESULT init(POINT point, int floor);//�νĹ��� �߱�
	void release();
	void update();
	void draw(POINT camera);
	void action();

	void frameUpdate();
	//������ �޾��� ��, ȸ���� ����Ͽ� �Լ� �����
	void getDamaged(int damage);

	Rat();
	~Rat();
};

