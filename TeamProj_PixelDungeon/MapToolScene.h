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

#define ATTRIBUTE_UNMOVE 0x0001		// 갈 수 없는 속성
#define ATTRIBUTE_ACTIVATE 0x0002	//활성화 되어있는 속성
#define ATTRIBUTE_UNSIGHT 


#define ATTRIBUTE_INVISIBLE			//



enum INPUTMODE {
	FLOOR,
	WALL,
	GRASS,
	DOOR,

	VIEWING,
	DELET
};

class MapToolScene : public gameNode
{
	typedef vector<GRID> vGrid;
	typedef vector<TILE> vTile;
	typedef vector<TILE>::iterator viTile;
	typedef vector<tagSelectTile> vSelectTile;
	typedef vector<tagSelectTile>::iterator viSelectTile;


private:
	bool _leftClicking;


	image* _paletteImg;

	

	vTile _vMapTile; // 맵에 깔아놓은 타일
	viTile _viMapTile;

	vGrid _mapSelected; //선택한 맵 그리드
	GRID _mapRect[GRIDNUM]; //맵 전체 그리드 rect
	
	
	
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
	
	vector<RECT> _tileButton;
	
	BUTTON _buttonRect[BUTTONNUM];
	
		


	int _cameraX, _cameraY;

public:
	HRESULT init();
	void release();
	void update();
	void render();
	
	void paletteSetup();


	void buttonInput();

	void save();
	void load();

	MapToolScene();
	~MapToolScene();
};

