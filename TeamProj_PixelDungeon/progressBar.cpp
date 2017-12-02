#include "stdafx.h"
#include "progressBar.h"


progressBar::progressBar()
{
}


progressBar::~progressBar()
{
}

HRESULT progressBar::init(int x, int y, int width, int height)
{
	 _x = x;
	 _y = y;

	_rcProgress = RectMake(x, y, width, height);

	_progressBarTop = IMAGEMANAGER->addImage("frontBar", "Img//Enemy//boss_hp_top_bar2.bmp", x , y, width - 60 , height-40, true, RGB(255, 0, 255));
	_progressBarBottom = IMAGEMANAGER->addImage("backBar", "Img//Enemy//boss_hp_bottom.bmp", x, y, width, height, true, RGB(255, 0, 255));

	_width = _progressBarTop->getWidth();

	return S_OK;
}
HRESULT progressBar::bossinit(int x, int y, int width, int height)
{	//
	//_x = x;
	//_y = y;
	//
	//_rcProgress = RectMake(x, y, width, height);
	//
	//_progressBarTop = IMAGEMANAGER->addImage("frontBar", "Img//Enemy//boss_hp_top_bar.bmp", x, y, width, height, true, RGB(255, 0, 255));
	//_progressBarBottom = IMAGEMANAGER->addImage("backBar", "Img//Enemy//boss_hp_bottom.bmp", x, y, width, height, true, RGB(255, 0, 255));
	//
	//_width = _progressBarTop->getWidth();

	return S_OK;
}

void progressBar::release()
{

}

void progressBar::update()
{
	_rcProgress = RectMakeCenter(_x, _y,
		_progressBarBottom->getWidth(), _progressBarBottom->getHeight());
}

void progressBar::render()
{
	IMAGEMANAGER->render("backBar", getMemDC(), _x,
		_y + _progressBarBottom->getHeight() / 2,
		0, 0,
		_progressBarBottom->getWidth(), _progressBarBottom->getHeight());

	IMAGEMANAGER->render("frontBar", getMemDC(),
		_x + 28*2,
		_y + _progressBarBottom->getHeight() / 2+ 20,
		0, 0,
		_width, _progressBarTop->getHeight());
}

void progressBar::render(POINT camera)
{
	IMAGEMANAGER->render("backBar", getMemDC(), _x + camera.x, _y + _progressBarBottom->getHeight() / 2 + camera.y, 0, 0,_progressBarBottom->getWidth(), _progressBarBottom->getHeight());

	IMAGEMANAGER->render("frontBar", getMemDC(),
		_x + camera.x,
		_y + _progressBarBottom->getHeight() / 2 + camera.y,
		0, 0,
		_width, _progressBarBottom->getHeight());

}

void progressBar::setGauge(float currentGauge, float maxGauge)
{
	_width = (currentGauge / maxGauge) * _progressBarTop->getWidth();
}
