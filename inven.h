#pragma once
#include "gameNode.h"
#include "weapon_all.h"

class inven : public gameNode
{
protected:
	vector<weapon*> weapons;
	vector<weapon*>::iterator i_weapons;

	weapon* _currentWeapon;

	polarStar* _polarStar;
	fireGun* _fireGun;
	machineGun* _machineGun;
	launcher* _launcher;
	int _currentIndex;

public:	

	float getWeaponAngle() { return weapons[_currentIndex]->getWeaponAngle(); }
	int getBulletMax() { return weapons[_currentIndex]->getBulletMax(); }
	int getcurrentBullet() { return weapons[_currentIndex]->getcurrentBullet(); }
	int getcurrentWeaponLv() { return weapons[_currentIndex]->getLv(); }
	//tagWeaponType getWeaponType() { return weapons[_currentIndex]->getType(); }
	int getCurrentIndex() { return _currentIndex; }

	void setCurrentIndex(int index) { _currentIndex = index; }

	vector<weapon*>::iterator getIweapon() { return i_weapons; }

	weapon* getCurrentWeapon() { return _currentWeapon; }

	polarStar* getPolarStar() { return _polarStar; }
	fireGun* getFireGun() { return _fireGun; }
	machineGun* getMachineGun() { return _machineGun; }
	launcher* getLancher() { return _launcher; }

	void setExpUp(int exp);

	void loadWeaponData();

	HRESULT init(image* collisionMap);
	void release();
	void update(float x, float y, RECT rc, float angle, bool isLeft, bool isTop, bool isDown);
	void render(HDC hdc, RECT rc);

	inven() {}
	virtual ~inven() { release(); }
};

