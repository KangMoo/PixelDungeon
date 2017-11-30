#pragma once
#include "Enemy.h"

#include "EnemyManager.h"

class Swarm :
	public Enemy
{
private:
	/*
	progressBar* _hpBar;	//ü�¹�

	ENEMYSTAT _statistics;	//���� ����
	POINT _point;				//��ǥ
	image* _image;				//�׷��� �̹���~
	bool _action;				//�׼ǰ��� ���� ��� ���� �ൿ

	RECT _hitBox;			//��Ʈ�ڽ�
	RECT _attBox;			//���ݷ�Ʈ ������ �ڽ��Դϴ�. �ʱ�ȭ �� ���ּž� �մϴ�.
	bool _isLive;			//��������
	bool _right;			//�������� �ٶ󺸰� �ִ��� ����
	bool _findPlayer;

	int _currntFrameX, _currntFrameY;	//������
	int _pointX, _pointY;				//Ȥ�� ���� �����ξ����ϴ�.....
	int _currntHp;						//maxHp�� statistics.hp �� �ֽ��ϴ�, hpHar���Դϴ�.
	int _myState;						//���� ����
	*/
	image* _move;
	image* _dead;

	bool _isMove;
	POINT _movePoint;

	int _frameCount;

	vector<TILE> astarTest;
	EnemyManager* _em;
	
public:
	HRESULT init(POINT point); //�ʱ� ����
	HRESULT init(POINT point, int currntHp); //�п�

	void getDamaged(int damage);

	void action(); 
	void frameUpdate();
	void draw(POINT camera);
	void release();

	void setEm(EnemyManager* em) { _em = em; }

	Swarm();
	~Swarm();
};

