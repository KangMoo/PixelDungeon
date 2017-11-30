#pragma once
#include "gameNode.h"
#include <list>

#define TILESIZE 32

#define GRIDX (int)(WINSIZEX / TILESIZE - 9)
#define GRIDY (int)(WINSIZEY / TILESIZE - 2)
#define GRIDNUM GRIDX * GRIDY

#define PALETTEX 6
#define PALETTEY 13
#define PALETTENUM PALETTEX * PALETTEY

#define BUTTONNUM 10


enum LAYER {
	LAYER_TILE, 
	LAYER_DECO,
	LAYER_OBJ,
	LAYER_ITEM,
	LAYER_MONSTER
};

enum INPUTMODE {
	MODE_NULL,

	//TERRAIN
	MODE_FLOOR,	MODE_WATER,	MODE_CHASM,
	MODE_GRASS,	MODE_GRASS_UN,
	MODE_WALL,	MODE_BARRICADE,	MODE_STATUE,
	MODE_DOOR,	MODE_DOOR_LOCKED,

	//OBJECT
	MODE_CHEST,
	MODE_STAIR_START, MODE_STAIR_END,
	MODE_POT,
	MODE_WELL,
	MODE_TRAP,

	MODE_VIEWING,
	MODE_VIEWING_TILE,
	
	MODE_DELET
};


class MapToolScene : public gameNode
{
	typedef vector<GRID> vGrid;
	typedef vector<GRID>::iterator viGrid;
	typedef vector<TILE> vTile;
	typedef vector<TILE>::iterator viTile;
	typedef vector<tagSelectTile> vSelectTile;
	typedef vector<tagSelectTile>::iterator viSelectTile;
	typedef vector<GAMEOBJECT> vObj;
	typedef vector<GAMEOBJECT>::iterator viObj;

private:
	bool _leftClicking;

	vector<string> _imgNameList;
	vector<image*> _imgList;

	RECT _selectRangeRect;
	POINT _selectRangePoint;

	vTile _vMapTile; // 맵에 깔아놓은 타일
	viTile _viMapTile;
	vTile _vDecoTile; // 이미지 겹치기 위한 장식용 타일
	viTile _viDecoTile;

	vGrid _vMapSelected; //선택한 맵 그리드
	viGrid _viMapSelected; 
	GRID _mapRect[GRIDNUM]; //맵 전체 그리드 rect
	
	vObj _vObj;  // 오브젝트 리스트 (상자, 계단, 항아리 등)
	viObj _viObj; 
	
	vTile _vPaletTile; // 팔레트에 깔아놓은 타일
	viTile _viPaletTile;
	vSelectTile _paletSelected; //선택한 팔레트 그리드
	GRID _paletRect[PALETTENUM]; //팔레트 전체 그리드 rect
	int _paletPage; // 팔레트 현재 페이지



	bool _showTile;
	int _showTileIndex;

	
	
	int _check;


	vTile _copyTile;
		
	INPUTMODE _inputMode;
	LAYER _inputLayer;


	vector<RECT> _tileButton;
	
	BUTTON _buttonRect[BUTTONNUM];
	
		
	float _inputCountdown;

	int _cameraX, _cameraY;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void imageSetup();
	void paletteSetup();


	void input();

	void input_ModeChange();
	void input_SelectMapGrid();
	void input_AddTile();
	void input_ClickPalet();
	void input_ClickButton();

	void cameraMove(int x, int y);

	void save();
	void load();

	MapToolScene();
	~MapToolScene();
};

