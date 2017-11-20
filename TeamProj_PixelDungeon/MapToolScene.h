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
	image* img; //�޾ƿ� �̹���
	int sourX, sourY; //�޾ƿ� Ÿ�� ��ǥ��
	int destX, destY; //�Ѹ� Ÿ�� ��ǥ��
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

	

	_vTile _mapTile; // �ʿ� ��Ƴ��� Ÿ��
	_vGrid _mapSelected; //������ �� �׸���
	tagGrid _mapRect[GRIDNUM]; //�� ��ü �׸��� rect
	
	
	_vTile _paletTile; // �ȷ�Ʈ�� ��Ƴ��� Ÿ��
	_vGrid _paletSelected; //������ �ȷ�Ʈ �׸���
	tagGrid _paletRect[PALETTENUM]; //�ȷ�Ʈ ��ü �׸��� rect
	
	




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

