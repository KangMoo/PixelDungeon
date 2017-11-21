#include "stdafx.h"
#include "Item.h"


Item::Item()
{
}


Item::~Item()
{

}

HRESULT Item::init()			
{

	return S_OK;
}
void Item::release()			
{

}
void Item::update()				
{
	bulletMove();
}
void Item::render(POINT camera)	
{
	draw(camera);
}
void Item::draw(POINT camera)	
{
	for ( _viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->img->render(getMemDC(), _viBullet->x + camera.x, _viBullet->y + camera.y);
	}
}

void Item::fire(image* img, float x, float y, float destX, float destY)
{
	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.x = bullet.initX = x;
	bullet.y = bullet.initY = y;
	bullet.destX = destX;
	bullet.destY = destY;
	bullet.angle = getAngle(x,y,destX,destY);
	bullet.speed = 7;
	bullet.img = img;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.img->getWidth(), bullet.img->getHeight());
	bullet.fire = false;
	bullet.count = 0;
	
	_vBullet.push_back(bullet);
}

void Item::bulletMove()
{
	for ( _viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); )
	{
		_viBullet->x += _viBullet->speed * cosf(_viBullet->angle);
		_viBullet->y += _viBullet->speed * sinf(_viBullet->angle);

		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->img->getWidth(), _viBullet->img->getHeight());

		if (getDistance(_viBullet->initX, _viBullet->initY, _viBullet->x, _viBullet->y) >
			getDistance(_viBullet->initX, _viBullet->initY, _viBullet->destX, _viBullet->destY))
		{
			_viBullet = _vBullet.erase(_viBullet);
			break;
		}
		else ++_viBullet;
	}
}

void Item::removeBullet(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);
}