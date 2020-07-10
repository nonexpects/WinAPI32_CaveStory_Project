#pragma once
#include "inven.h"
#include "pixelCollision.h"

class itemManager;
class enemyManager;


enum tagPlayerState {
	P_IDLE,
	P_RUN,
	P_JUMP_UP,
	P_JUMP_DOWN,
	P_STAY_UP,
	P_STAY_DOWN
};

class player : public inven
{
	image* _collisionMap;

	enemyManager* _em;
	itemManager* _im;

	image* _idle;
	image* _run;
	image* _run_up;
	image* _jump;
	image* _jump_down;
	image* _up;
	image* _down;

	tagSensor U, D, L, R;

	float leftRepulsivePower;
	float rightRepulsivePower;

	float _x, _y;
	//float _endX, _endY;
	float _angle, _speed, _gravity;
	float _time, _jumpTime;
	float _jumpPower, _jumpCheck;
	int _width, _height;
	int _index, _count;
	int _maxHp, _hp;
	bool _isLeft, _isUp, _isDown;
	bool _getdamaged, damaged_jump;
	int _alpha;

	int _damageStore, _hpStore;

	bool water;

	int _delay;

	tagPlayerState _state;

	char str[100];
	RECT _rc;
	
public:
	float getPosX() { return _x; }
	float getPosY() { return _y; }
	void setPosX(float x) {_x = x; }
	void setPosY(float y) {_y = y; }

	int getMaxHP() { return _maxHp; }
	int getHP() { return _hp; }

	int getWidth() { return _width; }
	int getHeight() { return _height; }

	float getTime() { return _time; }
	float getGravity() { return _gravity; }
	bool getDamageState() { return _getdamaged; }
	//float getJumpDelay () { return _jumpDelay; }
	RECT getRect() { return _rc; }
	float getSpd() { return _speed; }
	float getAngle() { return _angle; }

	image* getCollisionMap() { return _collisionMap; }

public:
	void setHp(int hp) { _hp = hp; }
	void setMaxHp(int maxHp) { _maxHp = maxHp; }
	void setGravity(float gravity) { _gravity = gravity; }
	void setEM(enemyManager* em) { _em = em; }
	void setIM(itemManager* im) { _im = im; }
	void setState(tagPlayerState state) { _state = state; }
	void setDamage(bool isDamaged) 
	{ 
		_hpStore = _hp;
		_getdamaged = isDamaged;
	}
	void setDownJumpTrue() { D.isJump = true; damaged_jump = true; }
	void setLeft(bool isLeft) { _isLeft = isLeft; }
	HRESULT init(image* collisionMap);
	void release();
	void update();
	void render(HDC hdc);
	void getDamaged();

	void jump();
	void inWater(bool isWater);
	
	void pixelCollision();
	void animation();

	void repulsive();

	void addPlayerFx();

	tagPlayerState getPlayerState() { return _state; }

	player() {};
	~player() {};
};

