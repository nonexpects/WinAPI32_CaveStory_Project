#pragma once
#include "gameNode.h"
#include "pixelCollision.h"

class player;

#define ENEMY_SPEED 2.f

struct tagReactionRange
{
	int rangeWidth, rangeHeight;
	RECT rc;
};

enum tagEnemyType
{
	ENEMY_NULL,
	EMENY_MOB1,
	ENEMY_MOB2,
	ENEMY_FLYING_MOB1,
	ENEMY_FLYING_MOB2,
	ENEMY_MOB3,
	ENEMY_BOSS1,
	ENEMY_RING,
	ENEMY_BIRD,
};

enum tagEnemyState
{
	ES_NULL,
	ES_SPAWN,
	ES_ATTACK,
	ES_DAMAGED,
	ES_TELEPORTED,
	ES_DEAD
};

class enemy : public gameNode
{
protected:

	player* _player;
	char str[100];
	pixelCollision* _pc;
	tagEnemyType _type;
	tagEnemyState _state;
	image* _enemyImage;
	string _enemyName;
	float _x, _y;
	int _width, _height;
	float _angle, _speed, _gravity, _time;
	int _count, _frameX, _frameY;
	int _hp;
	tagReactionRange _reactionRange;
	bool _isLeft, _wiggle;
	RECT _rc;

	RECT tmp;

public:
	//void update(void);
	virtual HRESULT init(player* player);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);
	virtual void animation();
	virtual void move();

	virtual float getPosX() { return _x; }
	virtual float getPosY() { return _y; }
	virtual float getSpd() { return _speed; }

	virtual int getHp() { return _hp; }
	virtual void setHp(int hp) { _hp = hp; }
	void damagedFX();

	void wiggling(float strength);

	tagEnemyType getEnemyType() { return _type; }
	tagEnemyState getEnemyState() { return _state; }

	RECT getRect() { return _rc; }
	RECT getReactionRect() { return _reactionRange.rc; }

	void setEnemyState(tagEnemyState state) { _state = state; }
	
	enemy() : _wiggle(false), _state(ES_NULL), _speed (ENEMY_SPEED), _angle(PI_2),
		_gravity(0.f), _frameX(0), _frameY(0), _count(0), _time(0.f),
		_isLeft(false) {}
	virtual ~enemy() {}
};

