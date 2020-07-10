#include "stdafx.h"
#include "dialog.h"

HRESULT dialog::init()
{
	return S_OK;
}

void dialog::release()
{
}

void dialog::update()
{
	if (INPUT->GetKeyDown('Z'))
	{
		if (d_save)
		{
			d_save = false;
		}
		else if (d_fill)
		{
			d_fill = false;
		}
		else if (d_dead)
		{
			if (!_choice)
			{
				PLAYERDATA->loadSaveData();
				tagSaveData tmp = PLAYERDATA->getSavedData();
				PLAYERDATA->SetIsLoaded(true);
				SCENEMANAGER->loadScene(tmp.sceneName);
				d_dead = false;
			}
			else
			{
				d_dead = false;
				SCENEMANAGER->loadScene("startScene");
			}
		}
		else if (_gameClear)
		{
			PostQuitMessage(0);
		}
		dialogOn = false;
	}

	if (d_dead)
	{
		if (INPUT->GetKeyDown(VK_LEFT))
		{
			SOUNDMANAGER->play("select", .5f);
			_choice = 0;
			_arrowrc = RectMakeCenter(_choicerc.left, _rc.top,
				_choiceArrowImg->getWidth(), _choiceArrowImg->getHeight());
		}
		else if (INPUT->GetKeyDown(VK_RIGHT))
		{
			SOUNDMANAGER->play("select", .5f);
			_choice = 1;
			_arrowrc = RectMakeCenter(_choicerc.left + 165, _rc.top,
				_choiceArrowImg->getWidth(), _choiceArrowImg->getHeight());
		}
	}

	if (d_teleport)
	{
		_time += TIMEMANAGER->getElapedTime();

		if (_time > _maxTime)
		{
			d_teleport = false;
			dialogOn = false;
			_time = _maxTime = 0.f;
		}
	}
}

void dialog::render(HDC hdc)
{
	if (d_save)
	{
		_dialogImg->scaleRender(hdc, _rc.left, _rc.top, _scale);
		textOut(hdc, _rc.left + 20, _rc.top + 20, "GAME SAVED");
	}
	else if (d_fill)
	{
		_dialogImg->scaleRender(hdc, _rc.left, _rc.top, _scale);
		textOut(hdc, _rc.left + 20, _rc.top + 20, "LIFE FILLED");
	}
	else if(d_dead)
	{
		_dialogImg->scaleRender(hdc, _rc.left, _rc.top, _scale);
		_choiceImg->render(hdc, _choicerc.left, _choicerc.top);
		_choiceArrowImg->render(hdc, _arrowrc.left, _arrowrc.top);
		textOut(hdc, _rc.left + 20, _rc.top + 20, "LOAD SAVE DATA?");
	}
	if (_gameClear)
	{
		_dialogImg->render(hdc, _rc.left, _rc.top);
	}
	
}

void dialog::SaveDialog()
{
	_dialogImg = IMAGEMANAGER->findImage("textBox");

	_x = WINSIZEX/2;
	
	_width = _dialogImg->getWidth();
	_height = _dialogImg->getHeight();
	_y = WINSIZEY - _height;
	_scale = 1.f;

	_rc = RectMakeCenter(_x, _y, _width, _height);

	dialogOn = d_save = true;
}

void dialog::DeadDialog()
{
	SOUNDMANAGER->stop("start_loop");
	SOUNDMANAGER->stop("start_intro");
	SOUNDMANAGER->stop("anzen_loop");
	SOUNDMANAGER->stop("anzen_intro");
	SOUNDMANAGER->stop("wanpaku_intro");
	SOUNDMANAGER->stop("wanpaku_loop");
	SOUNDMANAGER->stop("lastcave2_loop");
	SOUNDMANAGER->stop("lastcave2_intro");
	_dialogImg = IMAGEMANAGER->findImage("textBox");
	_choiceImg = IMAGEMANAGER->findImage("choiceBox");
	_choiceArrowImg = IMAGEMANAGER->findImage("choiceArrow");
	 

	_x = WINSIZEX/2;
	_width = _dialogImg->getWidth();
	_height = _dialogImg->getHeight();
	_y = WINSIZEY - _height;
	_scale = 1.f;

	_rc = RectMakeCenter(_x, _y, _width, _height);

	_choicerc = RectMakeCenter(_rc.right, _rc.top,
		_choiceImg->getWidth(), _choiceImg->getHeight());
	_arrowrc = RectMakeCenter(_choicerc.left, _rc.top,
		_choiceArrowImg->getWidth(), _choiceArrowImg->getHeight());

	dialogOn = d_dead = true;
}

void dialog::FillDialog()
{
	_dialogImg = IMAGEMANAGER->findImage("textBox");

	_x = WINSIZEX / 2;

	_width = _dialogImg->getWidth();
	_height = _dialogImg->getHeight();
	_y = WINSIZEY - _height;
	_scale = 1.f;

	_rc = RectMakeCenter(_x, _y, _width, _height);

	dialogOn = d_fill = true;
}

void dialog::gameClear()
{
	SOUNDMANAGER->stop("start_loop");
	SOUNDMANAGER->stop("start_intro");
	SOUNDMANAGER->stop("anzen_loop");
	SOUNDMANAGER->stop("anzen_intro");
	SOUNDMANAGER->stop("wanpaku_intro");
	SOUNDMANAGER->stop("wanpaku_loop");
	SOUNDMANAGER->stop("lastcave2_loop");
	SOUNDMANAGER->stop("lastcave2_intro");

	if (!SOUNDMANAGER->isPlaySound("ending"))
	{
		SOUNDMANAGER->play("ending");
	}
	_dialogImg = IMAGEMANAGER->findImage("gameClear");

	_x = 0;

	_width = _dialogImg->getWidth();
	_height = _dialogImg->getHeight();
	_y = 0;
	_scale = 1.f;

	_rc = RectMake(_x, _y, _width, _height);

	dialogOn = _gameClear = true;
}

//void dialog::BossFight()
//{
//	
//	_dialogImg = IMAGEMANAGER->findImage("textBox");
//
//	_x = WINSIZEX / 2;
//
//	_width = _dialogImg->getWidth();
//	_height = 50;
//	_y = WINSIZEY - _height;
//	_scale = 1.f;
//
//	_rc = RectMakeCenter(_x, _y, _width, _height);
//
//	d_bossOn = dialogOn = true;
//}

void dialog::teleport(float maxtime)
{
	d_teleport = dialogOn = true;
	_maxTime = maxtime;
}
