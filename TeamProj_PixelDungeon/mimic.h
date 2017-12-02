#pragma once
#include "Enemy.h"
class Mimic : public Enemy
{
private:

	bool _playerChack; //�÷��̾ �ǵ�ȴ��� ����
	bool _isMove;
	int money; //����Ʈ�� ��

	POINT _movePoint;

	vector<TILE> astar;

	//���� �����̰� �����ΰ�? ����?
	//2017-02-02, �𽺿��̺� �̹����� ���ǹ��Ұ����� �Ǵ��Ͽ� ������
	image *move, *stay, *dead;

public:
	virtual HRESULT init(POINT point , int floor);//�νĹ��� �߱�
	void release();
	void update();
	void draw(POINT camera);
	void action();

	//�������� ����Ʈ����
	void dropitem();

	void frameUpdate();
	//������ �޾��� ��, ȸ���� ����Ͽ� �Լ� �����
	void getDamaged(int damage);


	Mimic();
	~Mimic();
};

