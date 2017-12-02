#pragma once
#include "gameNode.h"

class progressBar : public gameNode
{
private:
	RECT _rcProgress;
	int _x, _y;
	float _width;

	image* _progressBarTop;
	image* _progressBarBottom;

	image* _bossHpBarTop;
	image* _bossHpBarBottom;

public:
	HRESULT init(int x, int y, int width, int height);
	HRESULT bossinit(int x, int y, int width, int height);

	void release();
	void update();
	void render();
	void render(POINT camera);

	void setGauge(float currentGauge, float maxGauge);

	void setX(int x) { _x = x; }
	void setY(int y) { _y = y; }
	
	progressBar();
	~progressBar();
};

