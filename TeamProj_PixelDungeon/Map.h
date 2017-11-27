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
	vector<TILE> _vMapTile;


	TILE _mapTest[10000];

	map<string, TILE*> _spareTile; // 바꿔치기용 타일 저장 (flame, grass 등)

	//A*~
	vector<vertex> _openlist;
	vector<vertex> _closelist;
	//~A*

	int _tileNum;
public:
	HRESULT init();
	void release();
	void update();
	void render();
	void render(POINT camera);
	void draw(POINT camera);

	void load();

	TILE getMap(int i, int j) { return _map[i][j]; }
	TILE getTile(int i, int j) { return _map[i][j]; }
	void setTile(TILE tile, int i, int j) { _map[i][j] = tile; }


	//타일 상태 변화 일으키는 set 모음
	void setTile_Flame(int i, int j);
	void setTile_GrassCut(int i, int j);

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

	//~A*

	void spareTileSetup();

	void setPlayerAddressLink(Player* player) { _player = player; }
	void setEnemyManagerAddressLink(EnemyManager* em) { _em = em; }
	void setUiAddressLink(UI* ui) { _ui = ui; }
	void setItemManagerAddressLink(ItemManager* im) { _im = im; }
	Map();
	~Map();



};
