#pragma once
#include "Boss.h"
class goo : public Boss
{
private:

	bool _PumpedUP;	//�ڽ� �߽� 5*5 ���ϰ���
	bool _isMove;
	int _trunCount;
	POINT _movePoint;	//�����̱� ���� ����Ʈ

	RECT skillRange;
	vector<TILE> aStar;

	image* _stay, *_move, *_dead;

public:
	HRESULT init(POINT point);//�νĹ��� �߱�
	void release();
	void update();
	void draw(POINT camera);
	void action();

	void frameUpdate();
	//������ �޾��� ��, ȸ���� ����Ͽ� �Լ� �����
	void getDamaged(int damage);

	goo();
	~goo();
};

