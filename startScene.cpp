#include "stdafx.h"
#include "startScene.h"

HRESULT startScene::init()
{
	SOUNDMANAGER->stop("start_loop");
	SOUNDMANAGER->stop("start_intro");
	SOUNDMANAGER->stop("anzen_loop");
	SOUNDMANAGER->stop("anzen_intro");
	SOUNDMANAGER->stop("wanpaku_intro");
	SOUNDMANAGER->stop("wanpaku_loop");
	SOUNDMANAGER->stop("lastcave2_loop");
	SOUNDMANAGER->stop("lastcave2_intro");

	SOUNDMANAGER->play("start_intro", 0.5f);
	
	_bg = IMAGEMANAGER->findImage("bg_title");
	_logo = IMAGEMANAGER->findImage("logo_title");

	_loop1 = _loop2 = _loop3 = _loop4 = _count = _index = 0;

	int x = WINSIZEX / 2  + 10;
	int y = 275;
	logo_rc = RectMakeCenter(x, y, _logo->getWidth(), _logo->getHeight());
	
	loopSoundOn = false;
	
	_menu= 0;

	return S_OK;
}

void startScene::release()
{
}

void startScene::update()
{
	if (!SOUNDMANAGER->isPlaySound("start_intro") && !loopSoundOn)
	{
		SOUNDMANAGER->play("start_loop", 0.5f);
		loopSoundOn = true;
	}

	_loop1 += 15;
	_loop2 += 10;
	_loop3 += 5;
	_loop4++;

	if (INPUT->GetKeyDown(VK_DOWN))
	{
		SOUNDMANAGER->play("select", .5f);
		if (_menu == 3) return;
		_menu++;
	}
	else if (INPUT->GetKeyDown(VK_UP))
	{
		SOUNDMANAGER->play("select", .5f);
		if (_menu == 0) return;
		_menu--;
	}
	//menu에 따른 state 지정
	switch (_menu)
	{
	case 0:
		_state = MENU_STARTMODE;
		break;
	case 1:
		_state = MENU_MAPTOOLMODE;
		break;
	case 2:
		_state = MENU_GAMEOPTIONS;
		break;
	case 3:
		_state = MENU_QUIT;
		break;
	}

	if (INPUT->GetKeyDown('Z'))
	{
		switch (_state)
		{
		case MENU_STARTMODE:
			SCENEMANAGER->loadScene("bossScene");
			//SCENEMANAGER->loadScene("houseScene");
			//SCENEMANAGER->loadScene("eggScene");
			break;
		case MENU_MAPTOOLMODE:
			SCENEMANAGER->loadScene("maptoolScene");
			break;
		case MENU_GAMEOPTIONS:
			//SCENEMANAGER->loadScene("startScene");
			break;
		case MENU_QUIT:
			PostQuitMessage(0);
			break;
		}
	}

	this->animation();
}

void startScene::render()
{
	RECT _rc = RectMake(0, 0, WINSIZEX, WINSIZEY);
	_bg->render(getMemDC());
	//구름
	IMAGEMANAGER->findImage("bg_title_cloud04")->loopRender(getMemDC(), &_rc, _loop4, 0);
	IMAGEMANAGER->findImage("bg_title_cloud03")->loopRender(getMemDC(), &_rc, _loop3, 0);
	IMAGEMANAGER->findImage("bg_title_cloud02")->loopRender(getMemDC(), &_rc, _loop2, 0);
	IMAGEMANAGER->findImage("bg_title_cloud01")->loopRender(getMemDC(), &_rc, _loop1, 0);
	//메뉴
	IMAGEMANAGER->findImage("title_menu")->render(getMemDC(), WINSIZEX/2 - 220,WINSIZEY/2 + 50);
	int x = WINSIZEX/2 - 190;
	switch (_state)
	{
	case MENU_STARTMODE:
		IMAGEMANAGER->findImage("player_run")->frameRender(getMemDC(), x, WINSIZEY / 2 + 70, _index, 0);
		break;
	case MENU_MAPTOOLMODE:
		IMAGEMANAGER->findImage("player_run")->frameRender(getMemDC(), x, WINSIZEY / 2 + 150, _index, 0);
		break;
	case MENU_GAMEOPTIONS:
		IMAGEMANAGER->findImage("player_run")->frameRender(getMemDC(), x, WINSIZEY / 2 + 230, _index, 0);
		break;
	case MENU_QUIT:
		IMAGEMANAGER->findImage("player_run")->frameRender(getMemDC(), x, WINSIZEY / 2 + 310, _index, 0);
		break;
	}
	_logo->render(getMemDC(), logo_rc.left, logo_rc.top);
}

void startScene::animation()
{
	_count++;

	if (_count % 8 == 0)
	{
		_index++;
		if (_index > IMAGEMANAGER->findImage("player_run")->getMaxFrameX())
		{
			_index = 0;
		}
	}
}
