#pragma once
#include "item.h"

class player;

//===================================================================================
//==## 고정형 아이템들 ####################===========================================
//===================================================================================

class filler : public item_fixed
{
	player* _player;
public:
	virtual HRESULT init(float x, float y);
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
	virtual void animation();

	virtual RECT getRect() { return _rc; }
	virtual tagFIXED getType() { return _type; }

	void setPlayer(player* player) { _player = player; }

	filler() {}
	~filler() {}
};

class saver : public item_fixed
{
public:
	virtual HRESULT init(float x, float y);
	virtual void release();
	virtual void update(player* player, string sceneName);
	virtual void render(HDC hdc);
	virtual void animation();

	virtual RECT getRect() { return _rc; }
	virtual tagFIXED getType() { return _type; }

	saver() {}
	~saver() {}
};

class computer : public item_fixed
{
public:
	virtual HRESULT init(float x, float y);
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
	virtual void animation();

	virtual RECT getRect() { return _rc; }
	virtual tagFIXED getType() { return _type; }

	computer() {}
	~computer() {}
};

class log_computer : public item_fixed
{
public:
	virtual HRESULT init(float x, float y);
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
	virtual void animation();

	virtual RECT getRect() { return _rc; }
	virtual tagFIXED getType() { return _type; }

	log_computer() {}
	~log_computer() {}
};

class teleporter : public item_fixed
{
public:
	virtual HRESULT init(float x, float y);
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
	virtual void animation();

	void setFrameX(int frameX) { _itemImg->setFrameX(frameX); }

	virtual RECT getRect() { return _rc; }
	virtual tagFIXED getType() { return _type; }

	teleporter() {}
	~teleporter() {}
};
