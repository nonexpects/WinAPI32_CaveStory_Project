#include "stdafx.h"
#include "mapToolScene.h"

HRESULT mapToolScene::init()
{
	_mapToolMain = new mapTool_main;
	_mapToolMain->init();
	_mapToolUI = new mapTool_sub;
	_mapToolUI->init();

	_mapToolUI->setMain(_mapToolMain);
	_mapToolMain->setUI(_mapToolUI);

	// 카메라 세팅
	CAMERA->setCam(WINSIZEX / 2, WINSIZEY / 2, WINSIZEX, WINSIZEY, TILESIZEX, TILESIZEY);
	CAMERA->setSpd(5.f);
	isMaptoolOn = true;


	SOUNDMANAGER->stop("start_loop");
	SOUNDMANAGER->stop("start_intro");

	return S_OK;
}

void mapToolScene::release()
{
	if (isMaptoolOn)
	{
		_mapToolMain->release();
		SAFE_DELETE(_mapToolMain);
		_mapToolUI->release();
		SAFE_DELETE(_mapToolUI);
	}
}

void mapToolScene::update()
{	
	_mapToolMain->update();
	
	_mapToolUI->update();

	CAMERA->update();

	if (INPUT->GetKeyDown(VK_TAB))
	{
		SCENEMANAGER->loadScene("startScene");
	}
}

void mapToolScene::render()
{
	_mapToolMain->render(getmapToolDC());
	CAMERA->render(getMemDC(), getmapToolDC());
	_mapToolUI->render();
}