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

#define ATTRIBUTE_UNMOVE 0x0001		// �� �� ���� �Ӽ�
#define ATTRIBUTE_ACTIVATE 0x0002	//Ȱ��ȭ �Ǿ��ִ� �Ӽ�
#define ATTRIBUTE_UNSIGHT 


#define ATTRIBUTE_INVISIBLE			//


enum VIEWMODE {
	VIEW_ONE,
	VIEW_TWO
};

enum INPUTMODE {
	MODE_FLOOR,
	MODE_WALL,
	MODE_GRASS,
	MODE_DOOR,
	
	MODE_DECO,
	
	MODE_VIEWING,
	MODE_DELET
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

	vector<string> _imgNameList;
	vector<image*> _imgList;

	

	vTile _vMapTile; // �ʿ� ��Ƴ��� Ÿ��
	viTile _viMapTile;
	vTile _vDecoTile; // �̹��� ��ġ�� ���� ��Ŀ� Ÿ��
	viTile _viDecoTile;

	vGrid _mapSelected; //������ �� �׸���
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
	VIEWMODE _viewMode;


	vector<RECT> _tileButton;
	
	BUTTON _buttonRect[BUTTONNUM];
	
		


	int _cameraX, _cameraY;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void imageSetup();
	void paletteSetup();


	void buttonInput();

	void save();
	void load();

	MapToolScene();
	~MapToolScene();
};

