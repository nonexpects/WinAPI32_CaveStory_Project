#include "stdafx.h"
#include "effect.h"

HRESULT effect::init(image* image, float time, int startFrameX, int startFrameY, int maxframeX, float speed, bool isTrail)
{
	if (!image) return E_FAIL;

	_fxImage = image;
	_maxTime = time;
	_isRunning = false;
	_startframeX = startFrameX;
	_startframeY = startFrameY;
	_speed = speed;
	_isTrail = isTrail;
	_maxframeX = (maxframeX == -1) ? _fxImage->getMaxFrameX() : maxframeX;

	return S_OK;
}

void effect::release()
{
	
}

void effect::updateFX()
{
	if (_isRunning)
	{
		this->animation();

		if (_movedir)
		{
			_x += cosf(_angle) * _speed;
			_y += -sinf(_angle) * _speed;
		}
	}
	
}

void effect::render(HDC hdc)
{
	if (_isRunning)
	{
		_fxImage->frameRender(hdc, _x, _y);
		
	}
}

void effect::animation()
{
	_time += TIMEMANAGER->getElapedTime();
	_count++;
	
	_fxImage->setFrameY(_frameY);
	if (_frameCount == 0) return;
	if (_count % _frameCount == 0)
	{
		_frameX++;
		if (_frameX > _maxframeX)
		{
			if (_isLoop)
			{
				if (_maxTime != 0.f)
				{
					if (_time > _maxTime)
					{
						this->FXoff();
					}
					else
					{
						_frameX = _startframeX;
					}
				}
				else
					_frameX = 0;
			}
			else
			{
				this->FXoff();
				return;
			}
		}
		_fxImage->setFrameX(_frameX);
	}
}

void effect::startEffect(float x, float y, int count, bool loop, float time, float angle, bool movedir)
{
	_x = x - (_fxImage->getFrameWidth() / 2);
	_y = y - (_fxImage->getFrameHeight() / 2);
	_frameCount = count;
	_isLoop = loop;
	_angle = angle;
	_maxTime = time;
	_movedir = movedir;
	_frameX = _startframeX - 1;
	_frameY = _startframeY;

	_isRunning = true;
}

void effect::FXoff()
{
	_isRunning = false;
	_frameCount = _count =0;
	_frameX = -1;
	_maxTime = _time = 0.f;
	_x = _y = 0.f;
}
