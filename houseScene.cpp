#include "stdafx.h"
#include "houseScene.h"

HRESULT houseScene::init()
{
	collisionMap = IMAGEMANAGER->addImage("house_collision", TILESIZEX, TILESIZEY);
	
	scene::init();

	_player->init(collisionMap);

	_name = "houseScene";

	this->setScene("map/house.map", SCENE_HOUSE, 1054, 544);


	_doorMimiga = RectMakeCenter(1055, 545, 64, 64);
	_doorEgg = RectMakeCenter(360, 545, 64, 64);
	_water = RectMake(320, 768, 384, 64);
	
	loadSaveData();
	

	_filler = new filler;
	_filler->init(736, 288);
	_saver = new saver;
	_saver->init(864, 288);
	_computer = new computer;
	_computer->init(500, 510);
	_teleporter = new teleporter;
	_teleporter->init(360, 510);

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

	_em->setScene(SCENE_HOUSE);
	loopSoundOn = false;
	SOUNDMANAGER->stop("start_loop");
	SOUNDMANAGER->stop("start_intro");
	SOUNDMANAGER->stop("anzen_loop");
	SOUNDMANAGER->stop("anzen_intro");
	SOUNDMANAGER->stop("wanpaku_intro");
	SOUNDMANAGER->stop("wanpaku_loop");
	SOUNDMANAGER->play("anzen_intro", .5f);


	return S_OK;
}

void houseScene::release()
{
	scene::release();


	_player->release();
	SAFE_DELETE(_player);

	_filler->release();
	SAFE_DELETE(_filler);
	_saver->release();
	SAFE_DELETE(_saver);
	_teleporter->release();
	SAFE_DELETE(_teleporter);
	_computer->release();
	SAFE_DELETE(_computer);

}

void houseScene::update()
{
	if (!SOUNDMANAGER->isPlaySound("anzen_intro") && !loopSoundOn)
	{
		SOUNDMANAGER->play("anzen_loop", 0.5f);
		loopSoundOn = true;
	}
	
	CAMERA->setCam(WINSIZEX / 2, 515);

	if (INPUT->GetKeyDown(VK_TAB))
	{
		SCENEMANAGER->loadScene("startScene");
	}

	if (!DIALOG->isDialogOn())
	{
		if (IntersectRect(&tmp, &_doorMimiga, &_player->getRect()))
		{
			if (INPUT->GetKeyDown(VK_DOWN))
			{
				PLAYERDATA->SetIsSaved(true);
				SCENEMANAGER->loadScene("mimigaScene");
			}
		}
				
		_player->inWater(IntersectRect(&tmp, &_water, &_player->getRect()));

		//_em->update();

		if (IntersectRect(&tmp, &_filler->getRect(), &_player->getRect()))
		{
			if (INPUT->GetKey(VK_DOWN))
			{
				_filler->run(true);
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
		_saver->update(_player, _name);
	
		_computer->update();
	}
	if (IntersectRect(&tmp, &_doorEgg, &_player->getRect()))
	{
		if (INPUT->GetKeyDown(VK_DOWN))
		{
			_player->setPosX(360);
			_player->setPosY(500);
			DIALOG->teleport(1.3f); 
			
		}

	}

	if (DIALOG->isTeleportOn())
	{
		SOUNDMANAGER->play("teleport", .2f);
		_player->getDamaged();
		_teleporter->setFrameX(1);
		_player->setPosY(500);
		if (DIALOG->getTime() > 1.25f)
		{
			teleportToEgg();
		}
		else if (DIALOG->getTime() > .4f)
		{
			if(_player->getPosX() == 360) _player->setPosX(355);
			else
				_player->setPosX(360);
		}
	}

	_teleporter->update();
	_player->update();

	scene::update();
}

void houseScene::render()
{
	this->mapRender(getCamMemDC());

	//_em->render(getCamMemDC());

	_im->render(getCamMemDC());

	_filler->render(getCamMemDC());
	_saver->render(getCamMemDC());
	_teleporter->render(getCamMemDC());
	_computer->render(getCamMemDC());

	_player->render(getCamMemDC());

	//FrameRect(getCamMemDC(), _doorMimiga, RGB(255, 0, 0));
	//FrameRect(getCamMemDC(), _doorEgg, RGB(255, 0, 0));
	//FrameRect(getCamMemDC(), _water, RGB(0, 0, 255));

	scene::render();

}

void houseScene::teleportToEgg()
{
	PLAYERDATA->SetIsSaved(true);
	SCENEMANAGER->loadScene("eggScene");
	_teleporter->setFrameX(0);
}
