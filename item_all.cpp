#include "stdafx.h"
#include "item_all.h"

HRESULT i_exp::init(float x, float y, image* collisionMap)
{
	_name = "i_exp";
	_type = ITEM_EXP;
	_itemImg = IMAGEMANAGER->findImage(_name);
	_angle = RANDOM->Range(0.f, PI);
	_gravity = 0.f;
	_collisionMap = collisionMap;
	_pc = new pixelCollision;
	_pc->init(_collisionMap);

	item::init(x, y);
	return S_OK;
}

void i_exp::release()
{
	SAFE_DELETE(_pc);
}

void i_exp::update()
{
	_time += TIMEMANAGER->getElapedTime();
	this->animation();
	this->move();
	this->timeOver();
}

void i_exp::render(HDC hdc)
{
	item::render(hdc);
}

void i_exp::animation()
{
	item::animation();
}

void i_exp::move()
{
	_gravity += 0.15f;

	_x += cosf(_angle) * 2.f;
	_y += -sinf(_angle) * 2.f + _gravity;

	_rc = RectMakeCenter(_x, _y,
		_itemImg->getFrameWidth(),
		_itemImg->getFrameHeight());

	if (_time > 4.f)
	{
		_angle = PI_2;
		_gravity += .2f;
	}

	this->collision();
}

void i_exp::collision()
{
	if (_pc->Downcheck(_x, _y, 16, 16))
	{
		SOUNDMANAGER->play("expColl", .5f);
		_gravity = -3.f;
	}
	if (_pc->Leftcheck(_x, _y, 16, 16))
	{
		SOUNDMANAGER->play("expColl", .5f);
		_angle = PI_2 - (PI - _angle);
	}
	if (_pc->Rightcheck(_x, _y, 16, 16))
	{
		SOUNDMANAGER->play("expColl", .5f);
		_angle = PI - _angle;
	}
	
}

HRESULT i_hp_1::init(float x, float y)
{
	_name = "i_life_1";
	_type = ITEM_HP_1;
	_itemImg = IMAGEMANAGER->findImage(_name);

	item::init(x, y);
	return S_OK;
}

void i_hp_1::release()
{
}

void i_hp_1::update()
{
	_time += TIMEMANAGER->getElapedTime();
	this->animation();

	this->timeOver();
}

void i_hp_1::render(HDC hdc)
{
	item::render(hdc);
}

void i_hp_1::animation()
{
	item::animation();
}

HRESULT i_hp_3::init(float x, float y)
{
	_name = "i_life_3";
	_type = ITEM_HP_3;
	_itemImg = IMAGEMANAGER->findImage(_name);

	item::init(x, y);
	return S_OK;
}

void i_hp_3::release()
{
}

void i_hp_3::update()
{
	_time += TIMEMANAGER->getElapedTime();
	this->animation();

	this->timeOver();
}

void i_hp_3::render(HDC hdc)
{
	item::render(hdc);
}

void i_hp_3::animation()
{
	item::animation();
}

HRESULT i_missile_1::init(float x, float y)
{
	_name = "i_missile_1";
	_type = ITEM_MISSILE_1;
	_itemImg = IMAGEMANAGER->findImage(_name);

	item::init(x, y);
	return S_OK;
}

void i_missile_1::release()
{
}

void i_missile_1::update()
{
	_time += TIMEMANAGER->getElapedTime();
	this->animation();

	this->timeOver();
}

void i_missile_1::render(HDC hdc)
{
	item::render(hdc);
}

void i_missile_1::animation()
{
	item::animation();
}

HRESULT i_missile_3::init(float x, float y)
{
	_name = "i_missile_3";
	_type = ITEM_MISSILE_3;
	_itemImg = IMAGEMANAGER->findImage(_name);

	item::init(x, y);
	return S_OK;
}

void i_missile_3::release()
{
}

void i_missile_3::update()
{
	_time += TIMEMANAGER->getElapedTime();
	this->animation();

	this->timeOver();
}

void i_missile_3::render(HDC hdc)
{
	item::render(hdc);
}

void i_missile_3::animation()
{
	item::animation();
}
