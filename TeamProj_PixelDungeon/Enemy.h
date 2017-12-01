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
	Player* _player;		//플레이어 정보
	UI* _ui;				//ui
	Map* _map;				//적 인식용 맵정보
	ItemManager* _im;
	//progressBar* _hpBar;	//체력바

	ENEMYSTAT _statistics;	//몬스터 스텟
	POINT _point;				//좌표
	image* _image;				//그려줄 이미지~
	bool _action;				//액션값이 참일 경우 몬스터 행동

	RECT _hitBox;			//히트박스
	RECT _attBox;			//공격렉트 생성할 박스입니다. 초기화 꼭 해주셔야 합니다.
	bool _isLive;			//생존여부
	bool _right;			//오른쪽을 바라보고 있는지 여부
	bool _findPlayer;
	bool _active;

	int _currntFrameX, _currntFrameY;	//프레임
	int _pointX, _pointY;				//혹시 몰라 만들어두었습니다.....
	int _currntHp;						//maxHp는 statistics.hp 에 있습니다, hpHar용입니다.
	int _myState;						//현재 상태

	int _frameFPS;
	int	_frameTime;
	int _currentFrameY, _currentFrameX;

	RECT _cog;				//최초 인식범위	렉트형태
	int _deadAlpha;			//죽으면 사라져야함니다
	bool _deleteForeEm;		//알파가 0이 되어 안보이면 사라집니다.


public:
	virtual HRESULT init();
	virtual HRESULT init(POINT _point); //포인트 추가
	virtual HRESULT init(POINT point, int cog);//인식범위 추기
	virtual void release();
	virtual void update();
	virtual void render(POINT camera);
	virtual void draw(POINT camera);
	virtual void action();

	virtual void attack();
	virtual void move();
	virtual void frameUpdate();
	//데미지 받았을 때, 회피율 계산하여 함수 만들기
	void getDamaged(int damage);

	//게터세터~
	bool getAction() { return _action; }
	void setAction(bool action) { _action = action; }
	ENEMYSTAT getStat() { return _statistics; }
	void setStat(ENEMYSTAT stat) { _statistics = stat; }
	POINT getPoint() { return _point; }
	void setPoint(POINT point) { _point = point; }
	int getHP() { return _statistics.hp; }
	void setHP(int hp) { _statistics.hp = hp; }

	//타일 좌표 받아오기
	virtual POINT getTilePt() { return _point; }
	//화면에 실제로 나타나는 좌표 받아오기
	virtual POINT getRenderPt() { return PointMake(_pointX, _pointY); }

	bool getLive() { return _isLive; }

	//플레이어, ui랑 연결
	void setPlayerAddressLink(Player* player)				{ _player = player; }
	void setUiAddressLink(UI* ui)							{ _ui = ui; }
	void setItemManagerAddressLink(ItemManager* itemManager) { _im = itemManager; }
	void setMapAddressLink(Map* map)							{ _map = map; }

	Enemy();
	~Enemy();
};

