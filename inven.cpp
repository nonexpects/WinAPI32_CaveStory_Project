#include "stdafx.h"
#include "inven.h"

void inven::setExpUp(int exp)
{
	weapons[_currentIndex]->setCurrentExp(weapons[_currentIndex]->getCurrentExp() + exp);
}

void inven::loadWeaponData()
{
	for (int i = 0; i < weapons.size(); i++)
	{
		weapons[i]->loadData();
	}
}

HRESULT inven::init(image* collisionMap)
{
	_polarStar = new polarStar;
	_polarStar->init(collisionMap);
	weapons.push_back(_polarStar);

	_fireGun = new fireGun;
	_fireGun->init(collisionMap);
	weapons.push_back(_fireGun);

	_machineGun = new machineGun;
	_machineGun->init(collisionMap);
	weapons.push_back(_machineGun);

	_launcher = new launcher;
	_launcher->init(collisionMap);
	weapons.push_back(_launcher);

	_currentIndex = 0;

	_currentWeapon = weapons[_currentIndex];

	return S_OK;
}

void inven::release()
{
	_polarStar->release();
	SAFE_DELETE(_polarStar);
	_fireGun->release();
	SAFE_DELETE(_fireGun);
	_machineGun->release();
	SAFE_DELETE(_machineGun);
	_launcher->release();
	SAFE_DELETE(_launcher);
}

void inven::update(float x, float y, RECT rc, float angle, bool isLeft, bool isTop, bool isDown)
{
	if (INPUT->GetKeyDown('A'))
	{
		_currentIndex--;
		if (_currentIndex < 0)
		{
			_currentIndex = 3;
		}

	}
	if (INPUT->GetKeyDown('S'))
	{
		_currentIndex++;
		if (_currentIndex > 3)
		{
			_currentIndex = 0;
		}
	}

	_polarStar->update(x, y, rc, angle, isLeft, isTop, isDown);
	_fireGun->update(x, y, rc, angle, isLeft, isTop, isDown);
	_machineGun->update(x, y, rc, angle, isLeft, isTop, isDown);
	_launcher->update(x, y, rc, angle, isLeft, isTop, isDown);
	
	weapons[_currentIndex]->fire(rc, y);

	if (INPUT->GetKeyDown(VK_F1))
	{
		weapons[_currentIndex]->setCurrentExp(10);
	}
	if (INPUT->GetKeyDown(VK_F2))
	{
		weapons[_currentIndex]->setCurrentExp(-10);
	}

	_currentWeapon = weapons[_currentIndex];
}

void inven::render(HDC hdc, RECT rc)
{
	for (int i = 0; i < weapons.size(); i++)
	{
		weapons[i]->bulletRender(hdc);
	}

	weapons[_currentIndex]->render(hdc, rc);

}
