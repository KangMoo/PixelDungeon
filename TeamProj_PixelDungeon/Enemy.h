#pragma once
#include "gameNode.h"
#include "Map.h"

class Player;
class UI;
class Enemy : public gameNode
{
protected:
	Player* _player;		//�÷��̾� ����
	UI* _ui;				//ui
	Map* _map;				//�� �νĿ� ������

	ENEMYSTAT _statistics;	//���� ����
	POINT _point;				//��ǥ
	image* _image;				//�׷��� �̹���~
	bool _action;				//�׼ǰ��� ���� ��� ���� �ൿ

	RECT _hitBox;			//��Ʈ�ڽ�
	RECT _attBox;			//���ݷ�Ʈ ������ �ڽ��Դϴ�. �ʱ�ȭ �� ���ּž� �մϴ�.
	bool _isLive;			//��������
	bool _right;			//�������� �ٶ󺸰� �ִ��� ����

	int _currntFrameX, _currntFrameY; //������
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(POINT camera);
	virtual void draw(POINT camera);
	virtual void action();

	//������ �޾��� ��, ȸ���� ����Ͽ� �Լ� �����
	void getDamaged(int damage);

	//���ͼ���~
	bool getAction() { return _action; }
	void setAction(bool action) { _action = action; }
	ENEMYSTAT getStat() { return _statistics; }
	void setStat(ENEMYSTAT stat) { _statistics = stat; }
	POINT getPoint() { return _point; }
	void setPoint(POINT point) { _point = point; }
	int getHP() { return _statistics.hp; }
	void setHP(int hp) { _statistics.hp = hp; }

	//�÷��̾�, ui�� ����
	void setPlayerAddressLink(Player* player) { _player = player; }
	void setUiAddressLink(UI* ui) { _ui = ui; }

	Enemy();
	~Enemy();
};

