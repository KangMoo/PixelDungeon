#pragma once
#include "gameNode.h"
#include "Map.h"
#include "progressBar.h"

class Player;
class UI;
class ItemManager;
class Enemy : public gameNode
{
protected:
	Player* _player;		//�÷��̾� ����
	UI* _ui;				//ui
	Map* _map;				//�� �νĿ� ������
	ItemManager* _im;
	//progressBar* _hpBar;	//ü�¹�

	ENEMYSTAT _statistics;	//���� ����
	POINT _point;				//��ǥ
	image* _image;				//�׷��� �̹���~
	bool _action;				//�׼ǰ��� ���� ��� ���� �ൿ

	RECT _hitBox;			//��Ʈ�ڽ�
	RECT _attBox;			//���ݷ�Ʈ ������ �ڽ��Դϴ�. �ʱ�ȭ �� ���ּž� �մϴ�.
	bool _isLive;			//��������
	bool _right;			//�������� �ٶ󺸰� �ִ��� ����
	bool _findPlayer;
	bool _active;

	int _currntFrameX, _currntFrameY;	//������
	int _pointX, _pointY;				//Ȥ�� ���� �����ξ����ϴ�.....
	int _currntHp;						//maxHp�� statistics.hp �� �ֽ��ϴ�, hpHar���Դϴ�.
	int _myState;						//���� ����

	int _frameFPS;
	int	_frameTime;
	int _currentFrameY, _currentFrameX;

	RECT _cog;				//���� �νĹ���	��Ʈ����
	int _deadAlpha;			//������ ��������Դϴ�
	bool _deleteForeEm;		//���İ� 0�� �Ǿ� �Ⱥ��̸� ������ϴ�.


public:
	virtual HRESULT init();
	virtual HRESULT init(POINT _point); //����Ʈ �߰�
	virtual HRESULT init(POINT point, int cog);//�νĹ��� �߱�
	virtual void release();
	virtual void update();
	virtual void render(POINT camera);
	virtual void draw(POINT camera);
	virtual void action();

	virtual void attack();
	virtual void move();
	virtual void frameUpdate();
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

	//Ÿ�� ��ǥ �޾ƿ���
	virtual POINT getTilePt() { return _point; }
	//ȭ�鿡 ������ ��Ÿ���� ��ǥ �޾ƿ���
	virtual POINT getRenderPt() { return PointMake(_pointX, _pointY); }

	bool getLive() { return _isLive; }

	//�÷��̾�, ui�� ����
	void setPlayerAddressLink(Player* player)				{ _player = player; }
	void setUiAddressLink(UI* ui)							{ _ui = ui; }
	void setItemManagerAddressLink(ItemManager* itemManager) { _im = itemManager; }
	void setMapAddressLink(Map* map)							{ _map = map; }

	Enemy();
	~Enemy();
};

