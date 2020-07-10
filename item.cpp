#include "stdafx.h"
#include "item.h"

HRESULT item::init(float x, float y)
{
	_x = x;
	_y = y;
	_rc = RectMakeCenter(_x, _y, _itemImg->getFrameWidth(), _itemImg->getFrameHeight());

	return S_OK;
}

void item::release()
{
}

void item::update()
{
	
}

void item::render(HDC hdc)
{
	_itemImg->frameAlphaRender(hdc, _rc.left, _rc.top, _alpha);
}

void item::animation()
{
	_count++;
	if (_count % 10 == 0)
	{
		_frameX++;
		if (_frameX > _itemImg->getMaxFrameX())
		{
			_frameX = 0;
		}
		_itemImg->setFrameX(_frameX);
	}
	if (_time > 6.f)
	{
		if (_count % 5 == 0)
		{
			if (_alpha == 255) _alpha = 0;
			else _alpha = 255;
		}
	}
}

bool item::timeOver()
{
	if (10.f < _time)
	{
		return true;
	}
	return false;
}

//===================================================================================
//==## 고정형 아이템 Parent #################=========================================
//===================================================================================


HRESULT item_fixed::init(float x, float y)
{
	_x = x;
	_y = y;
	_rc = RectMakeCenter(_x, _y, _itemImg->getFrameWidth(), _itemImg->getFrameHeight());

	return S_OK;
}

void item_fixed::release()
{
}

void item_fixed::update()
{
	animation();
}

void item_fixed::render(HDC hdc)
{
	_itemImg->frameAlphaRender(hdc, _rc.left, _rc.top, _alpha);

	//FrameRect(hdc, _rc, RGB(255, 255, 0));
}

void item_fixed::animation()
{
	_count++;
	if (_count % 8 == 0)
	{
		_frameX++;
		if (_frameX > _itemImg->getMaxFrameX())
		{
			_frameX = 0;
		}
		_itemImg->setFrameX(_frameX);
	}
}

void item_fixed::run(bool isOn)
{
	_isOn = isOn;
}
