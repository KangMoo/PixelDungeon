#pragma once
#include "gameNode.h"
#include <algorithm>
class EnemyManager;
class Player;
class UI;
class ItemManager;
//A*~
struct vertex {
	int f;
	int g;
	int h;
	int x, y;
	int px, py;
	bool operator<(const vertex &v) const {
		return (f > v.f);
	}
};
//~A*
class Map : public gameNode
{
private:
	EnemyManager* _em;
	Player* _player;
	UI* _ui;
	ItemManager* _im;

	bool start;
	TILE _map[100][100];
	int _mapSizeX, _mapSizeY;

	vector<TILE> _vMapTile;
	vector<TILE>::iterator _viMapTile;
	vector<TILE> _vDecoTile;
	vector<TILE>::iterator _viDecoTile;
	vector<GAMEOBJECT> _vObj;
	vector<GAMEOBJECT>::iterator _viObj;

	TILE _mapTest[10000];

	int _renderStartX;
	int _renderStartY;
	int _renderSizeX;
	int _renderSizeY;


	map<string, TILE*> _spareTile; // 바꿔치기용 타일 저장 (flame, grass 등)
	map<string, GAMEOBJECT*> _spareObj; // 바꿔치기용 타일 저장 (flame, grass 등)

	//A*~
	vector<vertex> _openlist;
	vector<vertex> _closelist;
	//~A*

	vector<string> _imgNameList;
	vector<image*> _imgList;

	vector<string> _stageDataList;
	int _curStageNum;

	//그림자테스트
	POINT _camera;

	//

	int _tileNum;
public:
	HRESULT init();
	void release();
	void update();
	void render();
	void render(POINT camera);
	void draw(POINT camera);
	void drawTileShadow(TILE tile);
	void imageSetup(void);

	void load(int stageNum);

	TILE getMap(int i, int j) { return _map[i][j]; }
	TILE getTile(int i, int j) { return _map[i][j]; }
	void setTile(TILE tile, int i, int j) { _map[i][j] = tile; }


	//상태 변화 일으키는 set 모음
	void setTile_Flame(int i, int j);
	void setTile_GrassCut(int i, int j);
	void setTile_OpenDoor(int i, int j);
	void setTile_CloseDoor(int i, int j);
	void setTile_UnlockDoor(int i, int j);
	
	void setObj_OpenChest(int i);
	void setObj_UseWell(int i);
	void setObj_ActivTrap(int i);
	

	void changeFloor(int floor, bool firstTime);




	//A*~
	vector<TILE> aStar(POINT currentPoint, POINT goalPoint);	//Astar실행함수
	void add_openlist(vertex v);					//openlist에 추가
	vertex pop_openlist();							//openlist에서 pop
	vertex pop_openlist(int x, int y);				//openlist에서 pop
	vertex search_openlist(int x, int y);			//openlist탐색
	bool search_openlist_exsist(int x, int y);		//closelist에 있는지 여부 확인
	void add_closelist(vertex v);					//closelist에 추가
	vertex pop_closelist(int x, int y);				//closelist에서 pop
	bool search_closelist_exsist(int x, int y);		//closelist에 있는지 여부 확인

	vertex calc_vertex(vertex v, vertex p, POINT goalPoint);		//F,G,H값 계산
	void add_eightway(vertex v, POINT goalPoint);					//8방향 탐색 후 추가
	bool check_goal();												//목적지 탐색

	void playerTurnEnd() {};

	//~A*

	void spareTileSetup();
	void spareObjSetup();

	void setPlayerAddressLink(Player* player) { _player = player; }
	void setEnemyManagerAddressLink(EnemyManager* em) { _em = em; }
	void setUiAddressLink(UI* ui) { _ui = ui; }
	void setItemManagerAddressLink(ItemManager* im) { _im = im; }
	Map();
	~Map();

	int getCurStageNum() { return _curStageNum; }
	int getMapSizeX() { return _mapSizeX; }
	int getMapSizeY() { return _mapSizeY; }
};
