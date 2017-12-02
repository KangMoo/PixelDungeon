#pragma once
#include "gameNode.h"
#include "Map.h"
#include "progressBar.h"

class Player;
class UI;
class ItemManager;
class EnemyManager;

class Enemy : public gameNode
{
protected:
	Player* _player;		//�÷��̾� ����
	UI* _ui;				//ui
	Map* _map;				//�� �νĿ� ������
	ItemManager* _im;
	EnemyManager* _em;
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

	int _floor;

	RECT _cog;				//���� �νĹ���	��Ʈ����
	int _deadAlpha;			//������ ��������Դϴ�
	bool _deleteForeEm;		//���İ� 0�� �Ǿ� �Ⱥ��̸� ������ϴ�.

	//A*~
	vector<vertex> _openlist;
	vector<vertex> _closelist;
	//~A*

public:
	virtual HRESULT init();
	virtual HRESULT init(POINT _point); //����Ʈ �߰�
	virtual HRESULT init(POINT _point, int _floor); //���� 

	//virtual HRESULT init(POINT point, int cog);//�νĹ��� �߱�

	virtual void release();
	virtual void update();
	virtual void render(POINT camera);
	virtual void draw(POINT camera);
	virtual void action();

	virtual void attack();
	virtual void move();
	virtual void frameUpdate();
	//������ �޾��� ��, ȸ���� ����Ͽ� �Լ� �����
	virtual void getDamaged(int damage);

	//���ͼ���~
	bool getAction() { return _action; }
	void setAction(bool action) { _action = action; }
	ENEMYSTAT getStat() { return _statistics; }
	void setStat(ENEMYSTAT stat) { _statistics = stat; }
	virtual POINT getPoint() { return PointMake(_point.x*TILESIZE + TILESIZE / 2, _point.y*TILESIZE + TILESIZE / 2); }
	virtual void setPoint(POINT point) { _point = point; }
	int getHP() { return _statistics.hp; }
	void setHP(int hp) { _statistics.hp = hp; }
	int getCHP() { return _currntHp; }
	int getFloor() { return _floor; }

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
	void setEnemyManagerAddressLink(EnemyManager* em) { _em = em; }


	//A*~
	vector<TILE> aStar(POINT currentPoint, POINT goalPoint);	//Astar�����Լ�
	void add_openlist(vertex v);					//openlist�� �߰�
	vertex pop_openlist();							//openlist���� pop
	vertex pop_openlist(int x, int y);				//openlist���� pop
	vertex search_openlist(int x, int y);			//openlistŽ��
	bool search_openlist_exsist(int x, int y);		//closelist�� �ִ��� ���� Ȯ��
	void add_closelist(vertex v);					//closelist�� �߰�
	vertex pop_closelist(int x, int y);				//closelist���� pop
	bool search_closelist_exsist(int x, int y);		//closelist�� �ִ��� ���� Ȯ��

	vertex calc_vertex(vertex v, vertex p, POINT goalPoint);		//F,G,H�� ���
	void add_eightway(vertex v, POINT goalPoint);					//8���� Ž�� �� �߰�
	bool check_goal();												//������ Ž��

	//~A*





	Enemy();
	~Enemy();
};

