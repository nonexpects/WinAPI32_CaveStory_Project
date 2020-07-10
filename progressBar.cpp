#include "stdafx.h"
#include "progressBar.h"

HRESULT progressBar::init(const char * frontImg, const char * backImg)
{
	//체력바 이미지 초기화
	_progressBarFront = IMAGEMANAGER->findImage(frontImg);
	_progressBarBack = IMAGEMANAGER->findImage(backImg);
	//체력바 위치 초기화
	_x = _progressBarBack->getX();
	_y = _progressBarBack->getY();
	//체력바 가로, 세로길이 초기화
	_width = _progressBarBack->getWidth();
	_height = _progressBarBack->getHeight();
	//체력바 렉트 초기화
	_rcProgress = RectMake(_x, _y, _width, _height);
	return S_OK;
}

HRESULT progressBar::init(const char * frontImg, const char* middleImg, const char * backImg, bool isHpBar)
{
	//체력바 이미지 초기화
	_progressBarFront = IMAGEMANAGER->findImage(frontImg);
	_progressBarMiddle = IMAGEMANAGER->findImage(middleImg);
	_progressBarBack = IMAGEMANAGER->findImage(backImg);
	//체력바 위치 초기화
	_x = _progressBarBack->getX();
	_y = _progressBarBack->getY();
	//체력바 가로, 세로길이 초기화
	_width = _progressBarBack->getWidth();
	_height = _progressBarBack->getHeight();

	_middleWidth = _width;
	//체력바 렉트 초기화
	_rcProgress = RectMake(_x, _y, _width, _height);

	_isHpBar = true;
	return S_OK;
}

void progressBar::release()
{
}

void progressBar::update()
{
	//프로그레스바 렉트 업데이트
	_rcProgress = RectMake(_x, _y, _width, _height);

}

void progressBar::render(HDC hdc, int alpha)
{
	//렌더링 되는 순서의 의해서 렌더가 되니까 피통부터 렌더 시킨다
	_progressBarBack->alphaRender(getMemDC(), _x, _y, alpha);

	if (_isHpBar)
	{
		_progressBarMiddle->alphaRender(getMemDC(), _x, _y, 0, 0, _middleWidth, _progressBarFront->getHeight(), alpha);
	}
	_progressBarFront->alphaRender(getMemDC(), _x, _y,
		0, 0, _width, _progressBarFront->getHeight(), alpha);
}

void progressBar::setGauge(float maxHp, float currentHp)
{
	_width = (currentHp / maxHp) * _progressBarFront->getWidth();
}

void progressBar::setGauge(float maxHp, float middleGauge, float currentHp)
{
	_middleWidth = (middleGauge / maxHp) * _progressBarFront->getWidth();
	_width = (currentHp / maxHp) * _progressBarFront->getWidth();
}

void progressBar::gaugeEffect(unsigned char alpha)
{
	if (alpha == 255) alpha = 0;
	else alpha = 255;
}
