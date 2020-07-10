#pragma once
#include "enemy.h"
#include "bullet.h"

//===================================
//	## Critter - ENEMY_MOB1 ##
//===================================

class critter : public enemy
{
	bool eyeOpen;
	float _delay;
	float _seeingAngle;
	RECT _openEye;
	bool _jump;

public:
	virtual HRESULT init(float x, float y, player* player);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);
	virtual int getHp() { return _hp; }
	virtual void setHp(int hp) { _hp = hp; }
	virtual void animation();
	virtual void move();

	void collision();

	critter() {}
	~critter() {}
};

enum BEETLETYPE
{
	INPLACE,
	FLY
};

//===================================
//	## Beetle - ENEMY_FLYING_MOB1 ##
//===================================

class beetle : public enemy
{
	BEETLETYPE b_type;
	float _time, _movetime;
	bool moveOn;

	//FLY용
	bool _isApproach, _turnLeft;
	float _targetX, _targetY;	// targetX는 쓰진 않으나 혹시나해서
	float _playerX;

public:
	virtual HRESULT init(float x, float y, BEETLETYPE type, player* player);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);
	virtual int getHp() { return _hp; }
	virtual void setHp(int hp) { _hp = hp; }
	virtual void animation();
	virtual void move();

	void collision();

	beetle() {}
	~beetle() {}
};



//===================================
//	## Basu - ENEMY_FLYING_MOB2 ##
//===================================

class basu : public enemy
{
	bullet* _bullet;
	bool _isFire;
	int _fireCount, _idleCount;

	bool _isApproach, _turnLeft;
	float _targetX, _targetY;	// targetX는 쓰진 않으나 혹시나해서
	float _playerX;

public:
	virtual HRESULT init(float x, float y, player* player);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);
	virtual int getHp() { return _hp; }
	virtual void setHp(int hp) { _hp = hp; }
	virtual void animation();
	virtual void move();

	void fire();

	basu() {}
	~basu() {}
};

//===================================
//	## Behemoth - ENEMY_MOB2 ##
//===================================

class behemoth : public enemy
{
	int _prevHp;
	bool gotDamage;
public:
	virtual HRESULT init(float x, float y, player* player);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	virtual int getHp() { return _hp; }
	virtual void setHp(int hp) { _hp = hp; }
	virtual void animation();
	virtual void move();

	void collision();

	behemoth() {}
	~behemoth() {}
};

//===================================
//	## Basil - ENEMY_MOB3 ##
//===================================

class basil : public enemy
{
	float _time;

public:
	virtual HRESULT init(float x, float y, player* player);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);
	virtual int getHp() { return _hp; }
	virtual void setHp(int hp) { _hp = hp; }
	//virtual void animation();
	virtual void move();

	void collision();

	basil() {}
	~basil() {}
};

//===================================
//	## Boss_Spawn_Bird - ##
//===================================

class bird : public enemy
{
	image* _ringImg;
	bool _isBird;
	int _fireCount, _idleCount, _birdFireCount;
	float _targetX, _targetY;
	float _targAngle, _theta;

	float _omega;

	//bool _turnLeft;
public:
	virtual HRESULT init(float x, float y, int dir, player* player);
	virtual void release(void);
	virtual void update();
	virtual void render(HDC hdc);
	virtual int getHp() { return _hp; }
	virtual void setHp(int hp) { _hp = hp; }
	virtual void animation();
	virtual void move();

	void collision();

	void reset();

	bird() {}
	~bird() {}
};

//===================================
//	## Boss - ##
//===================================

class boss : public enemy
{
	image* _teleportL;
	image* _teleportR;
	bullet* _bullet;
	boss_bullet* _bullet2;

	RECT _block;

	bool _isFire, _teleport;
	int _fireCount, _idleCount;
	float _fireTime;
	float _targetX, _targetY;
	int _fireBullets;


	//bool _turnLeft;
public:
	virtual HRESULT init(float x, float y, player* player);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);
	virtual int getHp() { return _hp; }
	virtual void setHp(int hp) { _hp = hp; }
	virtual void animation();
	virtual void move();

	bullet* getBullet() { return _bullet; }

	void bulletFire();

	boss() {}
	~boss() {}
};

