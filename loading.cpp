#include "stdafx.h"
#include "loading.h"
//=============================================================
//	## loadItem ## (�ε������)
//=============================================================
HRESULT loadItem::init(string strKey, int width, int height)
{
	//�ε����� �ʱ�ȭ
	_kind = LOAD_KIND_IMAGE_0;
	//�̹��� ����ü �ʱ�ȭ
	_imageResource.keyName = strKey;
	_imageResource.width = width;
	_imageResource.height = height;

	return S_OK;
}

HRESULT loadItem::init(string strKey, const char * fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	//�ε����� �ʱ�ȭ
	_kind = LOAD_KIND_IMAGE_1;
	
	//�̹��� ����ü �ʱ�ȭ
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
	//�ε����� �ʱ�ȭ
	_kind = LOAD_KIND_IMAGE_2;

	//�̹��� ����ü �ʱ�ȭ
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
	//�ε����� �ʱ�ȭ
	_kind = LOAD_KIND_FRAMEIMAGE_0;

	//�̹��� ����ü �ʱ�ȭ
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
	//�ε����� �ʱ�ȭ
	_kind = LOAD_KIND_FRAMEIMAGE_1;

	//�̹��� ����ü �ʱ�ȭ
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
//	## loading ## (�ε�Ŭ����)
//=============================================================

HRESULT loading::init()
{
	//�ε�ȭ�� ��׶��� �̹��� �ʱ�ȭ
	_background = IMAGEMANAGER->addImage("bg_loading", "Images/loading/BG_loading.bmp", WINSIZEX, WINSIZEY);

	//�ε��� �̹��� �ʱ�ȭ
	IMAGEMANAGER->addImage("loadingBarFront", "Images/loading/loadingBar_front.bmp", 600, 20);
	IMAGEMANAGER->addImage("loadingBarBack", "Images/loading/loadingBar_back.bmp", 600, 20);

	//�ε��� Ŭ���� �ʱ�ȭ
	_loadingBar = new progressBar;
	_loadingBar->init("loadingBarFront", "loadingBarBack");
	//_loadingBar->setGauge(0, 0);
	//�ε��� ��ġ
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
	//��׶��� ����
	_background->render(getMemDC());
	//�ε��� ����
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
	//�ε��Ϸ��
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
		
		//�� ���� ���� ���� ���� �غ���!!
		case LOAD_KIND_SOUND:
		{
		}
		break;
	}

	//���� ������ ����
	_currentGauge++;

	char str[256];
	char dir[256];
	ZeroMemory(str, sizeof(str));
	ZeroMemory(dir, sizeof(dir));
	sprintf(str, "\\%s", item->getImageResource().fileName);
	GetCurrentDirectory(256, dir);
	strcat(dir, str);
	sprintf(_fileName, "%s", dir);

	//�ε��� �̹��� ����
	_loadingBar->setGauge(_vLoadItem.size(), _currentGauge);


	return false;
}
