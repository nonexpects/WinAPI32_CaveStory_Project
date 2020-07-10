#include "stdafx.h"
#include "loading.h"
//=============================================================
//	## loadItem ## (로드아이템)
//=============================================================
HRESULT loadItem::init(string strKey, int width, int height)
{
	//로딩종류 초기화
	_kind = LOAD_KIND_IMAGE_0;
	//이미지 구조체 초기화
	_imageResource.keyName = strKey;
	_imageResource.width = width;
	_imageResource.height = height;

	return S_OK;
}

HRESULT loadItem::init(string strKey, const char * fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	//로딩종류 초기화
	_kind = LOAD_KIND_IMAGE_1;
	
	//이미지 구조체 초기화
	_imageResource.keyName = strKey;
	_imageResource.fileName = fileName;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.isTrans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::init(string strKey, const char * fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{
	//로딩종류 초기화
	_kind = LOAD_KIND_IMAGE_2;

	//이미지 구조체 초기화
	_imageResource.keyName = strKey;
	_imageResource.fileName = fileName;
	_imageResource.x = x;
	_imageResource.y = y;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.isTrans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::init(string strKey, const char * fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	//로딩종류 초기화
	_kind = LOAD_KIND_FRAMEIMAGE_0;

	//이미지 구조체 초기화
	_imageResource.keyName = strKey;
	_imageResource.fileName = fileName;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.frameX = frameX;
	_imageResource.frameY = frameY;
	_imageResource.isTrans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::init(string strKey, const char * fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	//로딩종류 초기화
	_kind = LOAD_KIND_FRAMEIMAGE_1;

	//이미지 구조체 초기화
	_imageResource.keyName = strKey;
	_imageResource.fileName = fileName;
	_imageResource.x = x;
	_imageResource.y = y;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.frameX = frameX;
	_imageResource.frameY = frameY;
	_imageResource.isTrans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}

//=============================================================
//	## loading ## (로딩클래스)
//=============================================================

HRESULT loading::init()
{
	//로딩화면 백그라운드 이미지 초기화
	_background = IMAGEMANAGER->addImage("bg_loading", "Images/loading/BG_loading.bmp", WINSIZEX, WINSIZEY);

	//로딩바 이미지 초기화
	IMAGEMANAGER->addImage("loadingBarFront", "Images/loading/loadingBar_front.bmp", 600, 20);
	IMAGEMANAGER->addImage("loadingBarBack", "Images/loading/loadingBar_back.bmp", 600, 20);

	//로딩바 클래스 초기화
	_loadingBar = new progressBar;
	_loadingBar->init("loadingBarFront", "loadingBarBack");
	//_loadingBar->setGauge(0, 0);
	//로딩바 위치
	_loadingBar->setPos(WINSIZEX/2 - 300, WINSIZEY - 100);

	_currentGauge = tmp = _count = _index = percentage = 0;
	ZeroMemory(_fileName, sizeof(_fileName));

	return S_OK;
}

void loading::release()
{
	_loadingBar->release();
	SAFE_DELETE(_loadingBar);
}

void loading::update()
{
	_loadingBar->update();

	percentage = ((float)_currentGauge / _vLoadItem.size()) * 100;


	_count++;

	if (_count % 8 == 0)
	{
		_index++;
		if (_index > 4)
		{
			_index = 0;
		}
	}
}

void loading::render()
{
	//백그라운드 렌더
	_background->render(getMemDC());
	//로딩바 렌더
	_loadingBar->render(getMemDC());

	if (percentage == 100)
	{
		IMAGEMANAGER->frameRender("loadingPercent", getMemDC(), 920, 700, 1, 0);
		IMAGEMANAGER->frameRender("loadingPercent", getMemDC(), 940, 700, 0, 0);
		IMAGEMANAGER->frameRender("loadingPercent", getMemDC(), 960, 700, 0, 0);
		IMAGEMANAGER->render("Percent_I", getMemDC(), 980, 700);
	}
	else if (percentage < 10)
	{
		IMAGEMANAGER->frameRender("loadingPercent", getMemDC(), 920, 700, percentage % 10, 0);
		IMAGEMANAGER->render("Percent_I", getMemDC(), 940, 700);
	}
	else
	{
		IMAGEMANAGER->frameRender("loadingPercent", getMemDC(), 920, 700, percentage / 10, 0);
		IMAGEMANAGER->frameRender("loadingPercent", getMemDC(), 940, 700, percentage % 10, 0);
		IMAGEMANAGER->render("Percent_I", getMemDC(), 960, 700);
	}
	TextOut(getMemDC(), WINSIZEX / 2 - 200, 900, _fileName, strlen(_fileName));

	IMAGEMANAGER->frameRender("player_run", getMemDC(), 300 + percentage * 6.f, 780, _index, 0);
}

void loading::loadImage(string strKey, int width, int height)
{
	loadItem* item = new loadItem;
	item->init(strKey, width, height);
	_vLoadItem.push_back(item);
}

void loading::loadImage(string strKey, const char * fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->init(strKey, fileName, width, height, isTrans, transColor);
	_vLoadItem.push_back(item);
}

void loading::loadImage(string strKey, const char * fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->init(strKey, fileName, x, y, width, height, isTrans, transColor);
	_vLoadItem.push_back(item);
}

void loading::loadFrameImage(string strKey, const char * fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->init(strKey, fileName, width, height, frameX, frameY, isTrans, transColor);
	_vLoadItem.push_back(item);
}

void loading::loadFrameImage(string strKey, const char * fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->init(strKey, fileName, x, y, width, height, frameX, frameY, isTrans, transColor);
	_vLoadItem.push_back(item);
}

bool loading::loadingDone()
{
	//로딩완료됨
	if (_currentGauge >= _vLoadItem.size())
	{
		return true;
	}

	loadItem* item = _vLoadItem[_currentGauge];
	switch (item->getLoadKind())
	{
		case LOAD_KIND_IMAGE_0:
		{
			tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addImage(img.keyName, img.width, img.height);
		}
		break;
		
		case LOAD_KIND_IMAGE_1:
		{
			tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addImage(img.keyName, img.fileName, img.width, img.height, img.isTrans, img.transColor);
		}
		break;
		
		case LOAD_KIND_IMAGE_2:
		{
			tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addImage(img.keyName, img.fileName, img.x, img.y, img.width, img.height, img.isTrans, img.transColor);
		}
		break;
		
		case LOAD_KIND_FRAMEIMAGE_0:
		{
			tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addFrameImage(img.keyName, img.fileName, img.width, img.height, img.frameX, img.frameY, img.isTrans, img.transColor);
		}
		break;

		case LOAD_KIND_FRAMEIMAGE_1:
		{
			tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addFrameImage(img.keyName, img.fileName, img.x, img.y, img.width, img.height, img.frameX, img.frameY, img.isTrans, img.transColor);
		}
		break;
		
		//곧 사운드 배우고 난후 직접 해보자!!
		case LOAD_KIND_SOUND:
		{
		}
		break;
	}

	//현재 게이지 증가
	_currentGauge++;

	char str[256];
	char dir[256];
	ZeroMemory(str, sizeof(str));
	ZeroMemory(dir, sizeof(dir));
	sprintf(str, "\\%s", item->getImageResource().fileName);
	GetCurrentDirectory(256, dir);
	strcat(dir, str);
	sprintf(_fileName, "%s", dir);

	//로딩바 이미지 변경
	_loadingBar->setGauge(_vLoadItem.size(), _currentGauge);


	return false;
}
