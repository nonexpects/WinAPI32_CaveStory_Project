#include "stdafx.h"
#include "mimigaScene.h"

HRESULT mimigaScene::init()
{
	collisionMap = IMAGEMANAGER->addImage("mimiga_collision", TILESIZEX, TILESIZEY);
	scene::init();

	_player->init(collisionMap);

	this->setScene("map/mimiga_town.map", SCENE_MIMIGA, 640, 400);

	loadSaveData();

	CAMERA->setSpd(3.f);
	CAMERA->setLimitHeight(TILESIZEY - WINSIZEY / 2);
	CAMERA->setLimitWidth(TILESIZEX - WINSIZEX / 2);
	PLAYERDATA->savePlayerData(_player);

	//상호참조 연결
	_player->setEM(_em);
	_em->setPlayer(_player);
	_player->setIM(_im);
	_em->setIM(_im);
	_player->getPolarStar()->setEM(_em);
	_player->getMachineGun()->setEM(_em);
	_player->getFireGun()->setEM(_em);
	_player->getLancher()->setEM(_em);
	_im->setPlayer(_player);
	_ui->setPlayer(_player);

	_houseDoor = RectMakeCenter(1060, 3360, 64, 64);
	return S_OK;
}

void mimigaScene::release()
{
	scene::release();

	_player->release();
	SAFE_DELETE(_player);
}

void mimigaScene::update()
{
	scene::update();
	CAMERA->setCam(_player->getPosX(), _player->getPosY());

	CAMERA->update();

	
	if (IntersectRect(&tmp, &_houseDoor, &_player->getRect()))
	{
		if (INPUT->GetKeyDown(VK_DOWN))
		{
			PLAYERDATA->SetIsSaved(true);
			SCENEMANAGER->loadScene("houseScene");
			CAMERA->setCam(640, 515);
		}

	}
	_player->update();
}
	

void mimigaScene::render()
{
	this->mapRender(getCamMemDC());

	_em->render(getCamMemDC());

	_im->render(getCamMemDC());

	_player->render(getCamMemDC());

	//FrameRect(getCamMemDC(), _houseDoor, RGB(255, 255, 0));
	scene::render();

	char str[100];
	//sprintf(str, "gravity : %f", _player->getGravity());
	//textOut(getMemDC(), 20, 50, str, strlen(str));
	
	
}
