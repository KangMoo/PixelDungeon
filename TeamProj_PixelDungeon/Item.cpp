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

void Item::itemUse(int position)
{

}
void Item::itemUse(ITEMNAME name)
{
	ITEMNAME _name = name;

	switch (_name)
	{
	case NAME_OLD_SHORT_SWORD:		
		break;
	case NAME_SHORT_SWORD:
		break;
	case NAME_SWORD:
		break;
	case NAME_SPEAR:
		break;
	case NAME_BATTLE_AXE:
		break;
	case NAME_CLOTH:
		break;
	case NAME_LEATHER:
		break;
	case NAME_MAIL:
		break;
	case NAME_RING_POWER:
		break;
	case NAME_RING_RECHARGE:
		break;
	case NAME_LIOYDS_BEACON:
		break;
	case NAME_DART:
		break;
	case NAME_PARALYSIS_DART:
		break;
	case NAME_POISON_DART:
		break;
	case NAME_LIGHTNING:
		break;
	case NAME_NORMAL:
		break;
	case NAME_POISON:
		break;
	case NAME_EMERGENCY:
		break;
	case NAME_PASTY:
		break;
	case NAME_UNKNOWN_MEAT:
		break;
	case NAME_COOKED_MEAT:
		break;
	case NAME_FROZEN_MEAT:
		break;
	case NAME_IDENTIFY:
		break;
	case NAME_UPGRADE:
		break;
	case NAME_PURIFY:
		break;
	case NAME_MAP:
		break;
	case NAME_RECHARGE:
		break;
	case NAME_BOTTLE:
		break;
	case NAME_HEAL:
		break;
	case NAME_STR:
		break;
	case NAME_EX:
		break;
	case NAME_INVISIBLE:
		break;
	case NAME_LEVITATION:
		break;
	case NAME_FORZEN:
		break;
	case NAME_LIQUID_FIRE:
		break;
	case NAME_SEED_HEAL:
		break;
	case NAME_SEED_FIRE:
		break;
	case NAME_SEED_SNAKE:
		break;
	case NAME_SEED_FROST:
		break;
	case NAME_DEW:
		break;
	}
}

void Item::itemUse(ITEMNAME name, int position)
{

}
