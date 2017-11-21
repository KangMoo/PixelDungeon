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
	image* img; //�޾ƿ� �̹���
	int sourX, sourY; //�޾ƿ� Ÿ�� ��ǥ��
	int destX, destY; //�Ѹ� Ÿ�� ��ǥ��
	int index;
};

struct tagGrid {
	image* img; //����ִ� �̹���
	int x, y;
	int index;
	RECT rc;
};

struct tagSelectTile {
	image* img; //�޾ƿ� �̹���
	int sourX, sourY; //�޾ƿ� Ÿ�� ��ǥ��
	int index;
	RECT rc; // ������ �ȷ�Ʈ rect
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

	

	vTile _vMapTile; // �ʿ� ��Ƴ��� Ÿ��
	viTile _viMapTile;

	vGrid _mapSelected; //������ �� �׸���
	tagGrid _mapRect[GRIDNUM]; //�� ��ü �׸��� rect
	
	
	
	vTile _vPaletTile; // �ȷ�Ʈ�� ��Ƴ��� Ÿ��
	viTile _viPaletTile;
	vSelectTile _paletSelected; //������ �ȷ�Ʈ �׸���
	tagGrid _paletRect[PALETTENUM]; //�ȷ�Ʈ ��ü �׸��� rect
	int _paletPage; // �ȷ�Ʈ ���� ������

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

