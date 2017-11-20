#pragma once
#include "gameNode.h"

#define TILESIZE 32

#define GRIDX (int)(WINSIZEX / TILESIZE - 7)
#define GRIDY (int)(WINSIZEY / TILESIZE - 2)
#define GRIDNUM GRIDX * GRIDY

#define PALETTEX 4
#define PALETTEY 13
#define PALETTENUM PALETTEX * PALETTEY


#define BUTTONNUM 10

struct tagTile {
	image* img; //받아올 이미지
	int sourX, sourY; //받아올 타일 좌표값
	int destX, destY; //뿌릴 타일 좌표값
};

struct tagGrid {
	int x, y;
	RECT rc;
};

class MapToolScene : public gameNode
{
	typedef vector<tagGrid> _vGrid;
	typedef vector<tagTile> _vTile;

private:
	bool _leftClicking;


	image* _paletteImg;

	

	_vTile _mapTile; // 맵에 깔아놓은 타일
	_vGrid _mapSelected; //선택한 맵 그리드
	tagGrid _mapRect[GRIDNUM]; //맵 전체 그리드 rect
	
	
	_vTile _paletTile; // 팔레트에 깔아놓은 타일
	_vGrid _paletSelected; //선택한 팔레트 그리드
	tagGrid _paletRect[PALETTENUM]; //팔레트 전체 그리드 rect
	
	




	_vTile _copyTile;
		
	
	
	vector<RECT> _tileButton;
	
	RECT _buttonRect[BUTTONNUM];
	
		


	int _cameraX, _cameraY;

public:
	HRESULT init();
	void release();
	void update();
	void render();
	
	void paletteSetup();


	void buttonInput();

	MapToolScene();
	~MapToolScene();
};

