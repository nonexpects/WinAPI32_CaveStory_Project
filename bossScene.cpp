#include "stdafx.h"
#include "bossScene.h"


HRESULT bossScene::init()
{
	collisionMap = IMAGEMANAGER->addImage("boss_collision", TILESIZEX, TILESIZEY);

	scene::init();

	_player->init(collisionMap);

	_name = "bossScene";

	this->setScene("map/boss1.map", SCENE_WHITE, 47, 735);
	
	loadSaveData();

	CAMERA->setSpd(3.f);
	CAMERA->setLimitHeight(544);
	CAMERA->setLimitWidth(1920);
	prevBossHp = 500;
	_bossBarbg = RectMakeCenter(WINSIZEX / 2, WINSIZEY - 100, 1000, 50);

	_saver = new saver;
	_saver->init(100, 544);
	_bossBar = new progressBar;
	_bossBar->init("ui_boss_hp_bar_front", "ui_boss_bar_middle", "ui_boss_hp_bar_back");
	_bossBar->setPos(_bossBarbg.left + 140, _bossBarbg.top + 10);


	_bossOn = false;

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
	
	_em->setScene(SCENE_WHITE);
	loopSoundOn = false;
	SOUNDMANAGER->stop("start_loop");
	SOUNDMANAGER->stop("start_intro");
	SOUNDMANAGER->stop("anzen_loop");
	SOUNDMANAGER->stop("anzen_intro");
	SOUNDMANAGER->stop("wanpaku_intro");
	SOUNDMANAGER->stop("wanpaku_loop");

	return S_OK;
}

void bossScene::release()
{
	scene::release();

	_player->release();
	SAFE_DELETE(_player);

	_saver->release();
	SAFE_DELETE(_saver);

	_bossBar->release();
	SAFE_DELETE(_bossBar);

}

void bossScene::update()
{
	if (!SOUNDMANAGER->isPlaySound("lastcave2_intro") && !loopSoundOn && _bossOn)
	{
		SOUNDMANAGER->play("lastcave2_loop", 0.5f);
		loopSoundOn = true;
	}

	

	if (PLAYERDATA->IsLoaded())
	{
		saveDataLoad();
		SOUNDMANAGER->play("lastcave2_intro", .5f);
		loopSoundOn = false;
	}

	CAMERA->setCam(_player->getPosX(), _player->getPosY());

	if (!DIALOG->isDialogOn())
	{
		scene::update();

		if (INPUT->GetKeyDown(VK_TAB))
		{
			SCENEMANAGER->loadScene("startScene");
		}
		if (IntersectRect(&tmp, &_saver->getRect(), &_player->getRect()))
		{
			if (INPUT->GetKey(VK_DOWN))
			{
				_saver->run(true);
			}
		}
		_saver->update(_player, _name);
		

		if (_player->getHP() <= 0 || INPUT->GetKeyDown(VK_F4))
		{
			DIALOG->DeadDialog();
		}

		if ((_player->getPosX() > 1510) && !_bossOn)
		{
			_bossOn = true;
			SOUNDMANAGER->play("lastcave2_intro", .5f);
		}
		if (_bossOn)
		{
			_em->update();
		}

		_player->update();
	}
	
	
	if (!_em->getEnemies().empty())
	{
		_bossBar->setGauge(300, 0, _em->getEnemies()[0]->getHp());
	}
	else
	{
		_bossBar->setGauge(300, 0, 0);
		_bossOn = false;
		DIALOG->gameClear();
	}

	CAMERA->update();
	
}

void bossScene::render()
{
	
	this->bossMapRender(getCamMemDC());

	//_im->render(getCamMemDC());

	_saver->render(getCamMemDC());
	_em->render(getCamMemDC());
	_player->render(getCamMemDC());
	
	scene::render();

	if (_bossOn)
	{
		IMAGEMANAGER->findImage("bossBox")->render(getMemDC(), _bossBarbg.left, _bossBarbg.top);
		IMAGEMANAGER->findImage("bossHp")->render(getMemDC(), _bossBarbg.left+10, _bossBarbg.top+ 10);
		_bossBar->render(getMemDC());
	}
}

void bossScene::bossMapRender(HDC hdc)
{
	RECT temp;
	char str[100];

	IMAGEMANAGER->findImage("bg_bossMap")->loopRender(getCamMemDC(), &CAMERA->getCamRect(), 0, 0);

	for (int i = 0; i < MAP_TILEY; i++)
	{
		for (int j = 0; j < MAP_TILEX; j++)
		{
			if (IntersectRect(&temp, &CAMERA->getCamRect(), &_mapTile[i][j].rc))
			{
				IMAGEMANAGER->frameRender("sampleTileMap", hdc, _mapTile[i][j].rc.left, _mapTile[i][j].rc.top,
					_mapTile[i][j].terrainFrameX, _mapTile[i][j].terrainFrameY);

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
		for (int i = 0; i < MAP_TILEY; i++)
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
