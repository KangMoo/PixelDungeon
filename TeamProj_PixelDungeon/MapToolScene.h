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

struct tagTile {
	image* img; //받아올 이미지
	int sourX, sourY; //받아올 타일 좌표값
	int destX, destY; //뿌릴 타일 좌표값
	int index;
};

struct tagGrid {
	image* img; //들어있는 이미지
	int x, y;
	int index;
	RECT rc;
};

struct tagSelectTile {
	image* img; //받아올 이미지
	int sourX, sourY; //받아올 타일 좌표값
	int index;
	RECT rc; // 선택한 팔레트 rect
};

struct tagButton {
	RECT rc;
	char text[128];
	bool isClicked;	
};


class MapToolScene : public gameNode
{
	typedef vector<tagGrid> vGrid;
	typedef vector<tagTile> vTile;
	typedef vector<tagTile>::iterator viTile;
	typedef vector<tagSelectTile> vSelectTile;
	typedef vector<tagSelectTile>::iterator viSelectTile;
	typedef list<tagGrid> lGrid;
	typedef list<tagTile> lTile;

private:
	bool _leftClicking;


	image* _paletteImg;

	

	vTile _vMapTile; // 맵에 깔아놓은 타일
	viTile _viMapTile;

	vGrid _mapSelected; //선택한 맵 그리드
	tagGrid _mapRect[GRIDNUM]; //맵 전체 그리드 rect
	
	
	
	vTile _vPaletTile; // 팔레트에 깔아놓은 타일
	viTile _viPaletTile;
	vSelectTile _paletSelected; //선택한 팔레트 그리드
	tagGrid _paletRect[PALETTENUM]; //팔레트 전체 그리드 rect
	int _paletPage; // 팔레트 현재 페이지

	bool _showTile;
	int _showTileIndex;

	
	
	int _check;



	vTile _copyTile;
		
	
	
	vector<RECT> _tileButton;
	
	tagButton _buttonRect[BUTTONNUM];
	
		


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

