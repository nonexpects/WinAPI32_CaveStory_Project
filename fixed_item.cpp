#include "stdafx.h"
#include "fixed_item.h"
#include "player.h"

HRESULT filler::init(float x, float y)
{
	_name = "i_lifefill";
	_type = FIX_I_FILL;
	_itemImg = IMAGEMANAGER->findImage(_name);

	item_fixed::init(x, y);

	return S_OK;
}

void filler::release()
{
}

void filler::update()
{
	item_fixed::update();

	if (_isOn)
	{
		SOUNDMANAGER->play("fill", .5f);
		_player->setHp(20);
		_player->getLancher()->setCurrentBullet(_player->getLancher()->getBulletMax());
		DIALOG->FillDialog();
		_isOn = false;
	}
}

void filler::render(HDC hdc)
{
	item_fixed::render(hdc);
}

void filler::animation()
{

}

HRESULT saver::init(float x, float y)
{
	_name = "i_save";
	_type = FIX_I_SAVE;
	_itemImg = IMAGEMANAGER->findImage(_name);

	item_fixed::init(x, y);

	return S_OK;
}

void saver::release()
{
}

void saver::update(player* player, string sceneName)
{
	animation();
	if (_isOn)
	{
		PLAYERDATA->savePlayerData(player, sceneName);
		DIALOG->SaveDialog();
		_isOn = false;
	}
}

void saver::render(HDC hdc)
{
	item_fixed::render(hdc);
}

void saver::animation()
{
	_count++;
	if (_count % 8 == 0)
	{
		_frameX++;
		if (_frameX > _itemImg->getMaxFrameX())
		{
			_frameX = 0;
		}
		_itemImg->setFrameX(_frameX);
	}
}

HRESULT computer::init(float x, float y)
{
	_name = "i_computer";
	_type = FIX_I_COMPUTER;
	_itemImg = IMAGEMANAGER->findImage(_name);

	item_fixed::init(x, y);

	return S_OK;
}

void computer::release()
{
}

void computer::update()
{
	item_fixed::update();
}

void computer::render(HDC hdc)
{
	item_fixed::render(hdc);
}

void computer::animation()
{
}

HRESULT log_computer::init(float x, float y)
{
	_name = "i_log_computer";
	_type = FIX_I_LOG_COMPUTER;
	_itemImg = IMAGEMANAGER->findImage(_name);

	item_fixed::init(x, y);

	return S_OK;
}

void log_computer::release()
{
}

void log_computer::update()
{
	//item_fixed::update();
}

void log_computer::render(HDC hdc)
{
	item_fixed::render(hdc);
}

HRESULT teleporter::init(float x, float y)
{
	_name = "i_teleporter";
	_type = FIX_I_TELEPORTER;
	_itemImg = IMAGEMANAGER->findImage(_name);

	item_fixed::init(x, y);


	return S_OK;
}

void teleporter::release()
{
}

void teleporter::update()
{
	
}

void teleporter::render(HDC hdc)
{
	item_fixed::render(hdc);
}

void teleporter::animation()
{

}