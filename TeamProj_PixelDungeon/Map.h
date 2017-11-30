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


	map<string, TILE*> _spareTile; // �ٲ�ġ��� Ÿ�� ���� (flame, grass ��)
	map<string, GAMEOBJECT*> _spareObj; // �ٲ�ġ��� Ÿ�� ���� (flame, grass ��)

	//A*~
	vector<vertex> _openlist;
	vector<vertex> _closelist;
	//~A*

	vector<string> _imgNameList;
	vector<image*> _imgList;

	vector<string> _stageDataList;
	int _curStageNum;

	//�׸����׽�Ʈ
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


	//���� ��ȭ ����Ű�� set ����
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
