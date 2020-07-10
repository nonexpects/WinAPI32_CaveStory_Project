#include "stdafx.h"
#include "scene.h"

 HRESULT scene::init()
{
	 _ui = new ui;
	 _ui->init();

	 _im = new itemManager;
	 _im->init();

	 _em = new enemyManager;
	 _em->init();

	 _player = new player;

	return S_OK;
}

HRESULT scene::setScene(string mapName, SCENES sceneName, float p_startX, float p_startY)
{
	_mapName = mapName;
	_sceneName = sceneName;
	startX = p_startX;
	startY = p_startY;
	
	this->load();

	_player->setPosX(startX);
	_player->setPosY(startY); 
	CAMERA->setPosX(_player->getPosX());
	CAMERA->setPosY(_player->getPosY());

	CAMERA->setBool(false);

	return S_OK;
}

void scene::release()
{

	_im->release();
	SAFE_DELETE(_im);

	_em->release();
	SAFE_DELETE(_em);

	_ui->release();
	SAFE_DELETE(_ui);

}

void scene::update()
{
	_ui->update();
	
	

	_im->update();
	

	PLAYERDATA->savePlayerData(_player);

}

void scene::render()
{

	CAMERA->render(getMemDC(), getCamMemDC());

	_ui->render(getMemDC());
	
	//sprintf(str, "%f", _player->getPosY());
	//TextOut(getMemDC(), 20, 50, str, strlen(str));
	//sprintf(str, "%f", _player->getPosX());
	//TextOut(getMemDC(), 20, 70, str, strlen(str));
}

void scene::loadSaveData()
{
	if (PLAYERDATA->isSceneStarted())
	{
		if (PLAYERDATA->IsLoaded())
		{
			saveDataLoad();
		}
		else if (PLAYERDATA->isSceneChanged())
		{
			playerDataLoad();
		}
	}
}

void scene::load()
{
	HANDLE file;
	DWORD read;

	char name[100] = {};
	strcpy(name, _mapName.c_str());

	file = CreateFile(name, GENERIC_READ, 0, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, _mapTile, sizeof(tagTile) * MAP_TILEX * MAP_TILEY, &read, NULL);
	CloseHandle(file);
}

void scene::mapRender(HDC hdc)
{
	RECT temp;
	char str[100];

	for (int i = 0; i < MAP_TILEY; i++)
	{
		for (int j = 0; j < MAP_TILEX; j++)
		{
			if (IntersectRect(&temp, &CAMERA->getCamRect(), &_mapTile[i][j].rc))
			{
				if (_mapTile[i][j].bg != BG_NULL)
				{
					IMAGEMANAGER->frameRender("bgTileMap", hdc, _mapTile[i][j].rc.left, _mapTile[i][j].rc.top,
						_mapTile[i][j].bgFrameX, _mapTile[i][j].bgFrameY);
				}

				IMAGEMANAGER->frameRender("sampleTileMap", hdc, _mapTile[i][j].rc.left, _mapTile[i][j].rc.top,
					_mapTile[i][j].terrainFrameX, _mapTile[i][j].terrainFrameY);

				// ÀÎ°ÔÀÓ ¸Ê ¿ÀºêÁ§Æ® ·»´õ
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

void scene::playerDataLoad()
{
	tagPlayerData tmp = PLAYERDATA->loadTempData();
	_player->setHp(tmp.currentHp);
	_player->setMaxHp(tmp.maxHp);
	_player->setCurrentIndex(tmp.currentWeaponIndex);
	_player->loadWeaponData();
	_player->getPolarStar()->setCurrentExp(tmp.ps_currentExp);
	_player->getPolarStar()->setLv(tmp.ps_lv);
	_player->getMachineGun()->setCurrentExp(tmp.mg_currentExp);
	_player->getMachineGun()->setLv(tmp.mg_lv);
	_player->getFireGun()->setCurrentExp(tmp.fg_currentExp);
	_player->getFireGun()->setLv(tmp.fg_lv);
	_player->getLancher()->setCurrentExp(tmp.lc_currentExp);
	_player->getLancher()->setLv(tmp.lc_lv);
	_player->getLancher()->setCurrentBullet(tmp.lc_currentBullet);
	_player->getLancher()->setMaxBullet(tmp.lc_maxBullet);

	PLAYERDATA->SetIsSaved(false);
}

void scene::saveDataLoad()
{
	tagSaveData save1 = PLAYERDATA->getSavedData();

	_player->setHp(save1.currentHp);
	_player->setMaxHp(save1.maxHp);
	_player->setCurrentIndex(save1.currentWeaponIndex);
	_player->loadWeaponData();
	_player->getPolarStar()->setCurrentExp(save1.ps_currentExp);
	_player->getPolarStar()->setLv(save1.ps_lv);
	_player->getMachineGun()->setCurrentExp(save1.mg_currentExp);
	_player->getMachineGun()->setLv(save1.mg_lv);
	_player->getFireGun()->setCurrentExp(save1.fg_currentExp);
	_player->getFireGun()->setLv(save1.fg_lv);
	_player->getLancher()->setCurrentExp(save1.lc_currentExp);
	_player->getLancher()->setLv(save1.lc_lv);
	_player->getLancher()->setCurrentBullet(save1.lc_currentBullet);
	_player->getLancher()->setMaxBullet(save1.lc_maxBullet);

	
	_player->setPosX(save1.posX);
	_player->setPosY(save1.posY);

	PLAYERDATA->SetIsLoaded(false);
}

