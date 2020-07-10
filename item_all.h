#pragma once
#include "item.h"
#include "pixelCollision.h"

class i_exp : public item
{
	float _angle, _gravity;
	image* _collisionMap;

	pixelCollision* _pc;

public:
	virtual HRESULT init(float x, float y, image* collisionMap);
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
	virtual void animation();

	virtual RECT getRect() { return _rc; }
	virtual tagItemType getType() { return _type; }
	virtual bool getGet() { return _isGet; }

	virtual void setGet(bool isGet) { _isGet = isGet; }
	void move();
	void collision();

	i_exp() {}
	~i_exp() {}
};

class i_hp_1 : public item
{
public:
	virtual HRESULT init(float x, float y);
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
	virtual void animation();

	virtual RECT getRect() { return _rc; }
	virtual tagItemType getType() { return _type; }
	virtual bool getGet() { return _isGet; }

	virtual void setGet(bool isGet) { _isGet = isGet; }

	i_hp_1() {}
	~i_hp_1() {}
};


class i_hp_3 : public item
{
public:
	virtual HRESULT init(float x, float y);
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
	virtual void animation();

	virtual RECT getRect() { return _rc; }
	virtual tagItemType getType() { return _type; }
	virtual bool getGet() { return _isGet; }

	virtual void setGet(bool isGet) { _isGet = isGet; }

	i_hp_3() {}
	~i_hp_3() {}
};

class i_missile_1 : public item
{
public:
	virtual HRESULT init(float x, float y);
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
	virtual void animation();

	virtual RECT getRect() { return _rc; }
	virtual tagItemType getType() { return _type; }
	virtual bool getGet() { return _isGet; }

	virtual void setGet(bool isGet) { _isGet = isGet; }

	i_missile_1() {}
	~i_missile_1() {}
};


class i_missile_3 : public item
{
public:
	virtual HRESULT init(float x, float y);
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
	virtual void animation();

	virtual RECT getRect() { return _rc; }
	virtual tagItemType getType() { return _type; }
	virtual bool getGet() { return _isGet; }

	virtual void setGet(bool isGet) { _isGet = isGet; }

	i_missile_3() {}
	~i_missile_3() {}
};