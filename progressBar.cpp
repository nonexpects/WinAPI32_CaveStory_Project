#include "stdafx.h"
#include "progressBar.h"

HRESULT progressBar::init(const char * frontImg, const char * backImg)
{
	//ü�¹� �̹��� �ʱ�ȭ
	_progressBarFront = IMAGEMANAGER->findImage(frontImg);
	_progressBarBack = IMAGEMANAGER->findImage(backImg);
	//ü�¹� ��ġ �ʱ�ȭ
	_x = _progressBarBack->getX();
	_y = _progressBarBack->getY();
	//ü�¹� ����, ���α��� �ʱ�ȭ
	_width = _progressBarBack->getWidth();
	_height = _progressBarBack->getHeight();
	//ü�¹� ��Ʈ �ʱ�ȭ
	_rcProgress = RectMake(_x, _y, _width, _height);
	return S_OK;
}

HRESULT progressBar::init(const char * frontImg, const char* middleImg, const char * backImg, bool isHpBar)
{
	//ü�¹� �̹��� �ʱ�ȭ
	_progressBarFront = IMAGEMANAGER->findImage(frontImg);
	_progressBarMiddle = IMAGEMANAGER->findImage(middleImg);
	_progressBarBack = IMAGEMANAGER->findImage(backImg);
	//ü�¹� ��ġ �ʱ�ȭ
	_x = _progressBarBack->getX();
	_y = _progressBarBack->getY();
	//ü�¹� ����, ���α��� �ʱ�ȭ
	_width = _progressBarBack->getWidth();
	_height = _progressBarBack->getHeight();

	_middleWidth = _width;
	//ü�¹� ��Ʈ �ʱ�ȭ
	_rcProgress = RectMake(_x, _y, _width, _height);

	_isHpBar = true;
	return S_OK;
}

void progressBar::release()
{
}

void progressBar::update()
{
	//���α׷����� ��Ʈ ������Ʈ
	_rcProgress = RectMake(_x, _y, _width, _height);

}

void progressBar::render(HDC hdc, int alpha)
{
	//������ �Ǵ� ������ ���ؼ� ������ �Ǵϱ� ������� ���� ��Ų��
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
