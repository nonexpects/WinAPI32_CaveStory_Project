#pragma once
#include "image.h"

//����� �̹����� �̹����Ŵ����� ��Ƶα�
static image* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZEX, WINSIZEY);
static image* _camDC = IMAGEMANAGER->addImage("camBuffer", TILESIZEX, TILESIZEY);
//static image* _collDC = IMAGEMANAGER->addImage("collisionBuffer", TILESIZEX, TILESIZEY);
static image* _mapToolDC = IMAGEMANAGER->addImage("mapToolBuffer", TILESIZEX, TILESIZEY);

class gameNode
{
private:
	HDC _hdc;		

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	//����� �̹��� ���
	image* getBackBuffer() { return _backBuffer; }
	image* getCamBuffer() { return _camDC; }
	image* getMapToolBuffer() { return _mapToolDC; }
	//ȭ�� HDC ���
	HDC getHDC() { return _hdc; }
	//�޸� DC ���
	HDC getMemDC() { return _backBuffer->getMemDC(); }
	HDC getCamMemDC() { return _camDC->getMemDC(); }
	HDC getmapToolDC() { return _mapToolDC->getMemDC(); }
	//HDC getcollDC() { return _collDC->getMemDC(); }

	//���� ���ν���
	LRESULT CALLBACK MainProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	gameNode() {}
	virtual ~gameNode() {}
};

