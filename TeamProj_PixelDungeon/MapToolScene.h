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
	LAYER_ITEM,
	LAYER_MONSTER
};

enum INPUTMODE {
	MODE_FLOOR,
	MODE_WATER,
	MODE_CHASM,

	MODE_GRASS,
	MODE_GRASS_UN,

	MODE_WALL,
	MODE_BARRICADE,
	MODE_STATUE,
	
	MODE_DOOR,
	MODE_DOOR_LOCKED,

	MODE_TRAP,
	
	MODE_DECO,
	
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


private:
	bool _leftClicking;

	vector<string> _imgNameList;
	vector<image*> _imgList;

	RECT _selectRangeRect;
	POINT _selectRangePoint;

	vTile _vMapTile; // �ʿ� ��Ƴ��� Ÿ��
	viTile _viMapTile;
	vTile _vDecoTile; // �̹��� ��ġ�� ���� ��Ŀ� Ÿ��
	viTile _viDecoTile;

	vGrid _vMapSelected; //������ �� �׸���
	viGrid _viMapSelected; 
	GRID _mapRect[GRIDNUM]; //�� ��ü �׸��� rect
	
	
	
	vTile _vPaletTile; // �ȷ�Ʈ�� ��Ƴ��� Ÿ��
	viTile _viPaletTile;
	vSelectTile _paletSelected; //������ �ȷ�Ʈ �׸���
	GRID _paletRect[PALETTENUM]; //�ȷ�Ʈ ��ü �׸��� rect
	int _paletPage; // �ȷ�Ʈ ���� ������

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

