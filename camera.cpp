#include "stdafx.h"
#include "camera.h"

HRESULT camera::init()
{
	_x = WINSIZEX / 2;
	_y = WINSIZEY / 2;
	_width = WINSIZEX;
	_height = WINSIZEY;
	_maxWidth = WINSIZEX;
	_maxHeight = WINSIZEY;
	_limitH = TILESIZEY - WINSIZEY / 2;
	_limitW = TILESIZEX - WINSIZEX / 2;

	_rc = RectMakeCenter(_x, _y, _width, _height);

	isMaptool = true;

	return S_OK;
}

void camera::setCam(float x, float y)
{
	_x = x;
	_y = y;
	_rc = RectMakeCenter(_x, _y, _width, _height);
}

void camera::setCam(float x, float y, int camWidth, int camHeight, int maxWidth, int maxHeight)
{
	_x = x;
	_y = y;
	_width = camWidth;
	_height = camHeight;
	_maxWidth = maxWidth;
	_maxHeight = maxHeight;

	_rc = RectMakeCenter(_x, _y, _width, _height);
}

void camera::setCam(float x, float y, int camWidth, int camHeight, int maxWidth, int maxHeight, float * targetX, float * targetY)
{
	_x = x;
	_y = y;
	_width = camWidth;
	_height = camHeight;
	_maxWidth = maxWidth;
	_maxHeight = maxHeight;
	_targetX = targetX;
	_targetY = targetY;

	_rc = RectMakeCenter(*_targetX, *_targetY, _width, _height);
}

void camera::release()
{
	
}

void camera::update()
{
	if (isMaptool)
	{
		if (INPUT->GetKey('A'))
		{
			_x -= _speed;
			if (_x < _width / 2)
				_x = _width / 2;
		}

		if (INPUT->GetKey('D'))
		{
			_x += _speed;
			if (_maxWidth < _x + _width / 2)
				_x = _maxWidth - _width / 2;
		}

		if (INPUT->GetKey('W'))
		{
			_y -= _speed;
			if (_y < _height / 2)
				_y = _height / 2;
		}
		if (INPUT->GetKey('S'))
		{
			_y += _speed;
			if (_maxHeight < _y + _height / 2)
				_y = _maxHeight - _height / 2;
		}
		_rc = RectMakeCenter(_x, _y, _width, _height);
	}
	else
	{
		if (_y - WINSIZEY / 2 < 0)
		{
			_y = WINSIZEY / 2;
		}
		if (_y > _limitH)
		{
			_y = _limitH;
		}

		if (_x - WINSIZEX / 2 < 0)
		{
			_x = WINSIZEX / 2;
		}
		if (_x > _limitW)
		{
			_x = _limitW;
		}

		_rc = RectMakeCenter(_x, _y, _width, _height);

	}
	
}

void camera::render(HDC hdc, HDC renderDC)
{
	char str[100];
	//PatBlt(renderDC, _rc.left, _rc.top, _rc.left + WINSIZEX, _rc.top + WINSIZEY, BLACKNESS);
	BitBlt(hdc, 0, 0, _width, _height, renderDC, _rc.left, _rc.top, SRCCOPY);

}
