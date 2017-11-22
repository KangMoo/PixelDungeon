#pragma once
#include "gameNode.h"
#include "Map.h"

class Player;
class UI;
class Enemy : public gameNode
{
protected:
	Player* _player;		//플레이어 정보
	UI* _ui;				//ui
	Map* _map;				//적 인식용 맵정보

	ENEMYSTAT _statistics;	//몬스터 스텟
	POINT _point;				//좌표
	image* _image;				//그려줄 이미지~
	bool _action;				//액션값이 참일 경우 몬스터 행동

	RECT _hitBox;			//히트박스
	RECT _attBox;			//공격렉트 생성할 박스입니다. 초기화 꼭 해주셔야 합니다.
	bool _isLive;			//생존여부
	bool _right;			//오른쪽을 바라보고 있는지 여부

	int _currntFrameX, _currntFrameY; //프레임
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(POINT camera);
	virtual void draw(POINT camera);
	virtual void action();

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

	//플레이어, ui랑 연결
	void setPlayerAddressLink(Player* player) { _player = player; }
	void setUiAddressLink(UI* ui) { _ui = ui; }

	Enemy();
	~Enemy();
};

