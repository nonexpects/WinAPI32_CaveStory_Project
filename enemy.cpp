#include "stdafx.h"
#include "enemy.h"
#include "player.h"

HRESULT enemy::init(player* player)
{
	_player = player;
	_pc = new pixelCollision;
	_pc->init(_player->getCollisionMap());

	return S_OK;
}

void enemy::release(void)
{
	SAFE_DELETE(_pc);
}

void enemy::update(void)
{
	if (_hp <= 0)
	{
		SOUNDMANAGER->play("enemy_dead", .5f);
		if (_type == ENEMY_MOB2 || _type == ENEMY_FLYING_MOB2)
		{
			
			FX->play("enemy_dead_B", _x, _y, 4);
			FX->play("enemy_smoke_B", RANDOM->Range(_x - 80, _x + 80), RANDOM->Range(_y - 80, _y + 80), 2);
			FX->play("enemy_smoke_B", RANDOM->Range(_x - 80, _x + 80), RANDOM->Range(_y - 80, _y + 80), 2);
			FX->play("enemy_smoke_B", RANDOM->Range(_x - 80, _x + 80), RANDOM->Range(_y - 80, _y + 80), 2);
			FX->play("enemy_smoke_B", RANDOM->Range(_x - 80, _x + 80), RANDOM->Range(_y - 80, _y + 80), 2);
		}
		else if (_type == ENEMY_BOSS1)
		{
			this->wiggling(10.f);
			FX->play("enemy_smoke_B", RANDOM->Range(_x - 80, _x + 80), RANDOM->Range(_y - 80, _y + 80), 2);
			FX->play("enemy_smoke_B", RANDOM->Range(_x - 80, _x + 80), RANDOM->Range(_y - 80, _y + 80), 2);
			FX->play("enemy_smoke_B", RANDOM->Range(_x - 80, _x + 80), RANDOM->Range(_y - 80, _y + 80), 2);
			FX->play("enemy_smoke_B", RANDOM->Range(_x - 80, _x + 80), RANDOM->Range(_y - 80, _y + 80), 2);
			FX->play("enemy_smoke_B", RANDOM->Range(_x - 80, _x + 80), RANDOM->Range(_y - 80, _y + 80), 2);
			FX->play("enemy_smoke_B", RANDOM->Range(_x - 80, _x + 80), RANDOM->Range(_y - 80, _y + 80), 2);
			FX->play("enemy_smoke_B", RANDOM->Range(_x - 80, _x + 80), RANDOM->Range(_y - 80, _y + 80), 2);
		}
		else
		{
			FX->play("enemy_dead", _x, _y, 4);
			FX->play("enemy_smoke", RANDOM->Range(_x - 50, _x + 50), RANDOM->Range(_y - 50, _y + 50), 2);
			FX->play("enemy_smoke", RANDOM->Range(_x - 50, _x + 50), RANDOM->Range(_y - 50, _y + 50), 2);
			FX->play("enemy_smoke", RANDOM->Range(_x - 50, _x + 50), RANDOM->Range(_y - 50, _y + 50), 2);
			FX->play("enemy_smoke", RANDOM->Range(_x - 50, _x + 50), RANDOM->Range(_y - 50, _y + 50), 2);
			FX->play("enemy_smoke", RANDOM->Range(_x - 50, _x + 50), RANDOM->Range(_y - 50, _y + 50), 2);
		}

		_state = ES_DEAD;
	}



	if (!_isLeft)
	{
		_angle = 0.f;
	}
	else
	{
		_angle = PI;
	}
}

void enemy::render(HDC hdc)
{
	if (_enemyImage != nullptr)
	{
		_enemyImage->frameRender(hdc, _rc.left, _rc.top, _frameX, _frameY);
		//FrameRect(hdc, _rc, RGB(255, 255, 0));
		//FrameRect(hdc, _reactionRange.rc, RGB(255, 255, 0));
	}
}

void enemy::animation()
{
	if (_state != ES_NULL)
	{
		_count++;
		if (_count % 10 == 0)
		{
			_frameX++;
			if (_frameX > _enemyImage->getMaxFrameX())
				_frameX = 0;
		}
	}

}

void enemy::move()
{
}

void enemy::damagedFX()
{
	FX->play("damaged", _x, _y, 2, false, 1.f, PI2 / RANDOM->Range(1, 8), true);
	FX->play("damaged", _x, _y, 2, false, 1.f, PI2 / RANDOM->Range(1, 8), true);
	FX->play("damaged", _x, _y, 2, false, 1.f, PI2 / RANDOM->Range(1, 8), true);
	FX->play("damaged", _x, _y, 2, false, 1.f, PI2 / RANDOM->Range(1, 8), true);
	FX->play("damaged", _x, _y, 2, false, 1.f, PI2 / RANDOM->Range(1, 8), true);
}

void enemy::wiggling(float strength)
{
	if (_wiggle)
	{
		_x -= strength;
		_wiggle = false;
	}
	else
	{
		_x += strength;
		_wiggle = true;
	}

}
