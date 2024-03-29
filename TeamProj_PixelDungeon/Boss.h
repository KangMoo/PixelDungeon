#pragma once
#include "gameNode.h"
#include "Map.h"
#include "UI.h"
#include "progressBar.h"
#include "PDInfo.h"

class Player;
class UI;
class ItemManager;
class Map;
class Boss : public gameNode
{
protected:
	Player* _player;		//플레이어 정보
	UI* _ui;				//ui
	Map* _map;				//적 인식용 맵정보
	ItemManager* _im;		//아이템매니저
	//progressBar* _hpBar;	//체력바

	ENEMYSTAT _statistics;	//몬스터 스텟
	POINT _point;			//좌표
	image* _image;			//그려줄 이미지~
	bool _action;			//액션값이 참일 경우 몬스터 행동

	RECT _hitBox;			//히트박스
	RECT _attBox;			//공격렉트 생성할 박스입니다. 초기화 꼭 해주셔야 합니다.
	bool _isLive;			//생존여부
	bool _right;			//오른쪽을 바라보고 있는지 여부
	bool _findPlayer;		//플레이어를 찾았는지 여부

	int _currntFrameX, _currntFrameY;	//프레임
	int _pointX, _pointY;				//혹시 몰라 만들어두었습니다.....
	int _currntHp;						//maxHp는 statistics.hp 에 있습니다, hpHar용입니다.
	int _myState;						//현재 상태

	int _frameFPS;						//프레임을 넘기기 위한 작은 코드
	int	_frameTime;						//프레임의 속도를 제한하기 위한 작은 코드
	int _currentFrameY, _currentFrameX;	//현재 프레임

	int _floor;

	RECT _cog;				//최초 인식범위	렉트형태
	int	 _deadAlpha;			//죽으면 사라져야함니다
	bool _deleteForeEm;		//알파가 0이 되어 안보이면 사라집니다.


public:
	virtual HRESULT init(POINT _point); //포인트 추가
	virtual HRESULT init(POINT point, int floor);//인식범위 추기
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

	//hp바 용
	int getCurrentHp() { return _currntHp; }

	bool getLive() { return _isLive; }
	
	//플레이어, ui랑 연결
	void setPlayerAddressLink(Player* player) { _player = player; }
	void setUiAddressLink(UI* ui) { _ui = ui; }
	void setItemManagerAddressLink(ItemManager* itemManager) { _im = itemManager; }
	void setMapAddressLink(Map* map) { _map = map; }


	Boss();
	~Boss();
};

