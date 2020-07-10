#include "stdafx.h"
#include "pixelCollision.h"

HRESULT pixelCollision::init(image* collisionMap)
{
	ZeroMemory(&U, sizeof(tagSensor));
	ZeroMemory(&D, sizeof(tagSensor));
	ZeroMemory(&L, sizeof(tagSensor));
	ZeroMemory(&R, sizeof(tagSensor));

	_collisionMap = collisionMap;

	return S_OK;
}

void pixelCollision::release()
{
}

void pixelCollision::collisonCheck(float x, float y, float width, float height, bool isJumpUp)
{
	//픽셀 충돌시 충돌 확인할 픽셀
	U.x = D.x = x;
	U.y = y - height / 2;
	D.y = y + height / 2;

	L.y = R.y = y;
	L.x = x - width / 2;
	R.x = x + width / 2;

	U.rc = RectMakeCenter(U.x, U.y, 10, 10);
	D.rc = RectMakeCenter(D.x, D.y, 10, 10);
	L.rc = RectMakeCenter(L.x, L.y, 10, 10);
	R.rc = RectMakeCenter(R.x, R.y, 10, 10);

	U.isTouch = false;
	D.isTouch = false;
	L.isTouch = false;
	R.isTouch = false;

	/*이부분이 픽셀충돌의 핵심*/

	for (int i = U.y + 3; i > U.y - 3; --i)
	{
		COLORREF color = GetPixel(_collisionMap->getMemDC(), U.x, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 0 && b == 255))
		{
			//if (_gravity < 0) _gravity = 0;
			U.isTouch = true;
			y = i + height / 2;
			break;
		}
	}
	for (int i = D.y - 5; i < D.y + 5; ++i)
	{
		COLORREF color = GetPixel(_collisionMap->getMemDC(), D.x, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 0 && b == 255) && !isJumpUp)//&& _state != P_JUMP_UP
		{
			//if (_state == P_JUMP_DOWN)
			//{
			//	_state = P_IDLE;
			//}
			//_jumpTime = 0.f;
			//_jumpPower = 4.f;
			//_jumpCheck = 0;
			D.isTouch = true;
			D.isJump = false;
			//_gravity = 0.f;
			y = i - height / 2;
			break;
		}
		else
		{
			y++;
		}
	}

	for (int i = L.x + 2; i > L.x - 2; --i)
	{
		COLORREF color = GetPixel(_collisionMap->getMemDC(), i, L.y);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 255 && g == 0 && b == 255)
		{
			L.isTouch = true;
			x = i + width / 2;
			break;
		}
	}

	for (int i = R.x - 2; i < R.x + 2; ++i)
	{
		COLORREF color = GetPixel(_collisionMap->getMemDC(), i, R.y);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 255 && g == 0 && b == 255)
		{
			R.isTouch = true;
			x = i - width / 2;
			break;
		}
	}
}

bool pixelCollision::Upcheck(float x, float y, float width, float height)
{
	U.x = x;
	U.y = y - height / 2;

	U.rc = RectMakeCenter(U.x, U.y, 10, 10);
	U.isTouch = false;

	for (int i = U.y + 3; i > U.y - 3; --i)
	{
		COLORREF color = GetPixel(_collisionMap->getMemDC(), U.x, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 0 && b == 255))
		{
			U.isTouch = true;
			return true;
		}
	}

	return false;
}

bool pixelCollision::Downcheck(float x, float y, float width, float height)
{
	D.x = x;
	D.y = y + height / 2;

	D.rc = RectMakeCenter(D.x, D.y, 10, 10);
	D.isTouch = false;

	for (int i = D.y - 5; i < D.y + 5; ++i)
	{
		COLORREF color = GetPixel(_collisionMap->getMemDC(), D.x, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 0 && b == 255))
		{
			D.isTouch = true;
			D.isJump = false;
			return true;
		}
	}
	return false;
}

bool pixelCollision::Rightcheck(float x, float y, float width, float height)
{
	R.y = y;
	R.x = x + width / 2;

	R.rc = RectMakeCenter(R.x, R.y, 10, 10);
	R.isTouch = false;

	for (int i = R.x - 3; i < R.x + 3; ++i)
	{
		COLORREF color = GetPixel(_collisionMap->getMemDC(), i, R.y);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 255 && g == 0 && b == 255)
		{
			R.isTouch = true;
			return true;
		}
	}
	return false;
}

bool pixelCollision::Leftcheck(float x, float y, float width, float height)
{
	L.y = y;
	L.x = x - width / 2;

	L.rc = RectMakeCenter(L.x, L.y, 10, 10);
	L.isTouch = false;

	for (int i = L.x + 3; i > L.x - 3; --i)
	{
		COLORREF color = GetPixel(_collisionMap->getMemDC(), i, L.y);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 255 && g == 0 && b == 255)
		{
			L.isTouch = true;
			return true;
		}
	}
	return false;
}

//int pixelCollision::I_Upcheck(float x, float y, float width, float height)
//{
//	U.x = x;
//	U.y = y - height / 2;
//
//	U.rc = RectMakeCenter(U.x, U.y, 10, 10);
//	U.isTouch = false;
//
//	for (int i = U.y + 3; i > U.y - 3; --i)
//	{
//		COLORREF color = GetPixel(_collisionMap->getMemDC(), U.x, i);
//		int r = GetRValue(color);
//		int g = GetGValue(color);
//		int b = GetBValue(color);
//
//		if ((r == 255 && g == 0 && b == 255))
//		{
//			U.isTouch = true;
//			return i;
//		}
//	}
//}
//
//int pixelCollision::I_Downcheck(float x, float y, float width, float height)
//{
//	D.x = x;
//	D.y = y + height / 2;
//
//	D.rc = RectMakeCenter(D.x, D.y, 10, 10);
//	D.isTouch = false;
//
//	for (int i = D.y - 5; i < D.y + 5; ++i)
//	{
//		COLORREF color = GetPixel(_collisionMap->getMemDC(), D.x, i);
//		int r = GetRValue(color);
//		int g = GetGValue(color);
//		int b = GetBValue(color);
//
//		if ((r == 255 && g == 0 && b == 255))
//		{
//			D.isTouch = true;
//			D.isJump = false;
//			return i;
//		}
//	}
//}
//
//int pixelCollision::I_Rightcheck(float x, float y, float width, float height)
//{
//	R.y = y;
//	R.x = x + width / 2;
//
//	R.rc = RectMakeCenter(R.x, R.y, 10, 10);
//	R.isTouch = false;
//
//	for (int i = R.x - 3; i < R.x + 3; ++i)
//	{
//		COLORREF color = GetPixel(_collisionMap->getMemDC(), i, R.y);
//		int r = GetRValue(color);
//		int g = GetGValue(color);
//		int b = GetBValue(color);
//
//		if (r == 255 && g == 0 && b == 255)
//		{
//			R.isTouch = true;
//			return i;
//		}
//	}
//}
//
//int pixelCollision::I_Leftcheck(float x, float y, float width, float height)
//{
//	L.y = y;
//	L.x = x - width / 2;
//
//	L.rc = RectMakeCenter(L.x, L.y, 10, 10);
//	L.isTouch = false;
//
//	for (int i = L.x + 3; i > L.x - 3; --i)
//	{
//		COLORREF color = GetPixel(_collisionMap->getMemDC(), i, L.y);
//		int r = GetRValue(color);
//		int g = GetGValue(color);
//		int b = GetBValue(color);
//
//		if (r == 255 && g == 0 && b == 255)
//		{
//			L.isTouch = true;
//			return i;
//		}
//	}
//}

void pixelCollision::sensorCheck(HDC hdc, tagSensor sensor)
{
	HBRUSH red_brush = CreateSolidBrush(RGB(255, 0, 0));
	HBRUSH green_brush = CreateSolidBrush(RGB(0, 255, 0));
	if (sensor.isTouch)
	{
		FillRect(hdc, &sensor.rc, red_brush);
	}
	else
	{
		FillRect(hdc, &sensor.rc, green_brush);
	}
	DeleteObject(red_brush);
	DeleteObject(green_brush);
}
