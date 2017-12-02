#pragma once
#include "Enemy.h"
#include "progressBar.h"

class goo : public Enemy
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
	HRESULT init(POINT point, int floor);//�νĹ��� �߱�
	void release();
	void update();
	void draw(POINT camera);
	void action();

	void frameUpdate();
	//������ �޾��� ��, ȸ���� ����Ͽ� �Լ� �����
	void getDamaged(int damage);

	progressBar* _hpBar;	//ü�¹�

	goo();
	~goo();
};

