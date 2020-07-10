#include "stdafx.h"
#include "eggScene.h"

HRESULT eggScene::init()
{
	collisionMap = IMAGEMANAGER->addImage("egg_collision", TILESIZEX, TILESIZEY);

	scene::init();

	_name = "eggScene";

	_player->init(collisionMap);

	this->setScene("map/egg.map", SCENE_EGG, 353, 416);

	_doorBossMap = RectMakeCenter(18720, 544, 64, 64);

	loadSaveData();


	CAMERA->setSpd(3.f);
	CAMERA->setLimitHeight(544);
	CAMERA->setLimitWidth(18240);
	//CAMERA->setCam(WINSIZEX / 2, 515);

	_teleporter = new teleporter;
	_teleporter->init(353, 386);
	_filler = new filler;
	_filler_b = new filler;
	_filler->init(7720, 672);
	_filler_b->init(18600, 544);
	_saver = new saver;
	_saver->init(7910, 800);

	//scene::playerDataLoad();

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
	_filler->setPlayer(_player);
	_filler_b->setPlayer(_player);
	// 무조건 상호참조 뒤에 
	_em->setScene(SCENE_EGG);

	loopSoundOn = false;
	SOUNDMANAGER->stop("anzen_loop");
	SOUNDMANAGER->stop("anzen_intro");
	SOUNDMANAGER->stop("wanpaku_intro");
	SOUNDMANAGER->stop("wanpaku_loop");
	SOUNDMANAGER->play("wanpaku_intro", .5f);

	return S_OK;
}

void eggScene::release()
{
	scene::release();

	_player->release();
	SAFE_DELETE(_player);

	_teleporter->release();
	SAFE_DELETE(_teleporter);

	_filler->release();
	SAFE_DELETE(_filler);
	_filler_b->release();
	SAFE_DELETE(_filler_b);

	_saver->release();
	SAFE_DELETE(_saver);
}

void eggScene::update()
{
	if (!SOUNDMANAGER->isPlaySound("wanpaku_intro") && !loopSoundOn)
	{
		SOUNDMANAGER->play("wanpaku_loop", 0.5f);
		loopSoundOn = true;
	}

	CAMERA->setCam(_player->getPosX(), _player->getPosY());

	if (PLAYERDATA->IsLoaded())
	{
		saveDataLoad();
	}
	if (!DIALOG->isDialogOn())
	{
		scene::update();

		_em->update();

		if (INPUT->GetKeyDown(VK_TAB))
		{
			SCENEMANAGER->loadScene("startScene");
		}

		if (IntersectRect(&tmp, &_doorBossMap, &_player->getRect()))
		{
			if (INPUT->GetKeyDown(VK_DOWN))
			{
				PLAYERDATA->SetIsSaved(true);
				CAMERA->setCam(640, 515);
				SCENEMANAGER->loadScene("bossScene");
			}
		}
		if (IntersectRect(&tmp, &_filler->getRect(), &_player->getRect()))
		{
			if (INPUT->GetKey(VK_DOWN))
			{
				_filler->run(true);
			}
		}
		else if (IntersectRect(&tmp, &_filler_b->getRect(), &_player->getRect()))
		{
			if (INPUT->GetKey(VK_DOWN))
			{
				_filler_b->run(true);
			}
		}
		if (IntersectRect(&tmp, &_saver->getRect(), &_player->getRect()))
		{
			if (INPUT->GetKey(VK_DOWN))
			{
				_saver->run(true);
			}
		}
		_filler->update();
		_filler_b->update();
		_saver->update(_player, _name);
		_teleporter->update();
		

		_player->update();
		if (_player->getHP() <= 0)
		{
			DIALOG->DeadDialog();
		}
	}

	
	CAMERA->update();
}

void eggScene::render()
{

	this->eggMapRender(getCamMemDC());

	_em->render(getCamMemDC());

	_im->render(getCamMemDC());
	_filler->render(getCamMemDC());
	_filler_b->render(getCamMemDC());
	_teleporter->render(getCamMemDC());
	_saver->render(getCamMemDC());
	_player->render(getCamMemDC());

	//FrameRect(getCamMemDC(), _doorBossMap, RGB(255, 0, 255));

	scene::render();
}

void eggScene::eggMapRender(HDC hdc)
{
	RECT temp;
	char str[100];

	IMAGEMANAGER->findImage("bg_green")->loopRender(getCamMemDC(), &CAMERA->getCamRect(), 0, 0);

	for (int i = 0; i < MAP_TILEY; i++)
	{
		for (int j = 0; j < MAP_TILEX; j++)
		{
			if (IntersectRect(&temp, &CAMERA->getCamRect(), &_mapTile[i][j].rc))
			{
				IMAGEMANAGER->frameRender("sampleTileMap", hdc, _mapTile[i][j].rc.left, _mapTile[i][j].rc.top,
					_mapTile[i][j].terrainFrameX, _mapTile[i][j].terrainFrameY);

				// 인게임 맵 오브젝트 렌더
				if (_mapTile[i][j].obj == OBJ_NONE && _mapTile[i][j].col == COL_NULL) continue;

				if (_mapTile[i][j].obj != OBJ_NONE)
				{
					IMAGEMANAGER->frameRender("sampleTileMap", hdc, _mapTile[i][j].rc.left, _mapTile[i][j].rc.top,
						_mapTile[i][j].objFrameX, _mapTile[i][j].objFrameY);
				}

				if (_mapTile[i][j].col != COL_NULL)
				{
					IMAGEMANAGER->frameRender("collisionMap", collisionMap->getMemDC(), _mapTile[i][j].rc.left, _mapTile[i][j].rc.top,
						_mapTile[i][j].collisionFrameX, _mapTile[i][j].collisionFrameY);
				}

			}
		}
	}

	if (INPUT->GetToggleKey(VK_F3))
	{
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < MAP_TILEX; j++)
			{
				if (IntersectRect(&temp, &CAMERA->getCamRect(), &_mapTile[i][j].rc))
				{
					IMAGEMANAGER->frameRender("collisionMap", hdc, _mapTile[i][j].rc.left, _mapTile[i][j].rc.top,
						_mapTile[i][j].collisionFrameX, _mapTile[i][j].collisionFrameY);
				}
			}
		}
	}
}
