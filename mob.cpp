#include "stdafx.h"
#include "mob.h"
#include "player.h"

//===================================
//	## Critter - ENEMY_MOB1 ##
//===================================

HRESULT critter::init(float x, float y, player* player)
{
	enemy::init(player);
	_enemyName = "critter";
	_enemyImage = IMAGEMANAGER->findImage(_enemyName);
	_type = EMENY_MOB1;
	_isLeft = RANDOM->Range(1);
	_x = x;
	_y = y;
	_width = 64;
	_height = 64;
	_hp = 4;
	_angle = getAngle(_x, _y, _player->getPosX(), _player->getPosY());
	_delay = .5f;
	eyeOpen = _jump = false;
	_rc = RectMakeCenter(_x, _y, _width, _height);
	_openEye = RectMakeCenter(_x, _y, 700, 300);
	
	_reactionRange.rangeWidth = 400;
	_reactionRange.rangeHeight = 300;

	_reactionRange.rc = RectMakeCenter(_x, _y,
		_reactionRange.rangeWidth, _reactionRange.rangeHeight);

	return S_OK;
}

void critter::release(void)
{
	enemy::release();
}

void critter::update(void)
{

	if (_state == ES_SPAWN)
	{
		if (_hp <= 0)
		{
			FX->play("enemy_dead", _x, _y, 5);
			FX->play("enemy_smoke", RANDOM->Range(_x - 50, _x + 50), RANDOM->Range(_y - 50, _y + 50), 2);
			FX->play("enemy_smoke", RANDOM->Range(_x - 50, _x + 50), RANDOM->Range(_y - 50, _y + 50), 2);
			FX->play("enemy_smoke", RANDOM->Range(_x - 50, _x + 50), RANDOM->Range(_y - 50, _y + 50), 2);
			FX->play("enemy_smoke", RANDOM->Range(_x - 50, _x + 50), RANDOM->Range(_y - 50, _y + 50), 2);
			FX->play("enemy_smoke", RANDOM->Range(_x - 50, _x + 50), RANDOM->Range(_y - 50, _y + 50), 2);
			_state = ES_DEAD;
		}
		_seeingAngle = getAngle(_x, _y, _player->getPosX(), _player->getPosY());
		if (_seeingAngle >= PI_2 && _seeingAngle < PI2 - PI_2)
		{
			_isLeft = true;
			_seeingAngle = PI;
		}
		else
		{
			_isLeft = false;
			_seeingAngle = 0;
		}

		if (IntersectRect(&tmp, &_openEye, &_player->getRect()))
		{
			eyeOpen = true;
		}
		else
		{
			eyeOpen = false;
		}

		if (IntersectRect(&tmp, &_reactionRange.rc, &_player->getRect()) && !_jump)
		{
			
			if (_delay >= .5f)
			{
				_angle = _seeingAngle;
				_gravity = -3.f;
				_jump = true;
				_delay = 0.f;
			}
			else
			{
				_delay += TIMEMANAGER->getElapedTime();
			}
		}

		if (_jump)
		{
			
			this->move();
		}

		this->animation();
	}
}

void critter::render(HDC hdc)
{
	enemy::render(hdc);
	//FrameRect(hdc, _openEye, RGB(0, 0, 255));

	//_pc->sensorCheck(hdc, _pc->getDownSensor());
}

void critter::animation()
{
	//enemy::animation();
	
	if (_state == ES_SPAWN)
	{
		_count++;

		if (!_isLeft)
		{
			_frameY = 1;
		}
		else
		{
			_frameY = 0;
		}
		if (eyeOpen && !_jump)
		{
			_frameX = 1;
		}
		if (!eyeOpen)
		{
			_frameX = 0;
		}

		if (_jump)
		{
			_frameX = 2;
		}
	}
}

void critter::move()
{
	
	_gravity += 0.15f;

	_x += cosf(_angle) * 3.f;
	_y += -sinf(PI_2) * 3.f + _gravity;

	_rc = RectMakeCenter(_x, _y,
		_enemyImage->getFrameWidth(),
		_enemyImage->getFrameHeight());

	_reactionRange.rc = RectMakeCenter(_x, _y,
		_reactionRange.rangeWidth, _reactionRange.rangeHeight);

	_openEye = RectMakeCenter(_x, _y, 700, 300);


	this->collision();
}

void critter::collision()
{
	if (_pc->Downcheck(_x, _y, _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight() - 20))
	{
		_gravity = 0.f;
		_jump = false;
	}
	if (_pc->Upcheck(_x, _y, _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight()))
	{
		if (_gravity < 0) _gravity = 0;
		_gravity++;
	}
	if (_pc->Leftcheck(_x, _y, _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight()))
	{
		_x +=3.f;
	}
	if (_pc->Rightcheck(_x, _y, _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight()))
	{
		_x -=3.5f;
	}

}

//===================================
//	## Beetle - ENEMY_FLYING_MOB1 ##
//===================================

HRESULT beetle::init(float x, float y, BEETLETYPE type, player* player)
{
	enemy::init(player);
	_type = ENEMY_FLYING_MOB1;
	b_type = type;
	if (b_type == INPLACE)
	{
		_enemyName = "beetle_FLY";
		_x = x;
		_y = y;
	}
	else
	{
		_enemyName = "beetle";
		_x = x - WINSIZEX / 2 - 10;
		_targetX = x;
		_y = _targetY = y;
	}
	_enemyImage = IMAGEMANAGER->findImage(_enemyName);
	_isLeft = RANDOM->Range(1);
	if (b_type == INPLACE)
	{
		_frameX = 3;
	}
	_speed = 10.f;
	_playerX = player->getPosX();
	_width = 64;
	_height = 64;
	_hp = 4;
	moveOn = _turnLeft = false;
	_isApproach = true;
	_time = _movetime = 0;
	_rc = RectMakeCenter(_x, _y, _width, _height);

	_reactionRange.rangeWidth = 700;
	_reactionRange.rangeHeight = 100;

	_reactionRange.rc = RectMake(_rc.left - 100, _rc.top,
		_reactionRange.rangeWidth, _reactionRange.rangeHeight);


	return S_OK;
}

void beetle::release(void)
{
	enemy::release();
}

void beetle::update(void)
{
	enemy::update();
	_playerX = _player->getPosX();
	
	if (_state == ES_SPAWN)
	{
		this->animation();

		if (b_type == INPLACE)
		{
			if (IntersectRect(&tmp, &_player->getRect(), &_reactionRange.rc))
			{
				moveOn = true;
			}
			if (moveOn)
			{
				_time += TIMEMANAGER->getElapedTime();
			}
		}
		else
		{
			//_time += TIMEMANAGER->getElapedTime();

			_isLeft = (_x >= _playerX) ? true : false;

			if (_x > _playerX + 100)
			{
				_turnLeft = true;
			}
			if (_x < _playerX - 100)
			{
				_turnLeft = false;
			}
			
		}

		this->move();
		
	}
}

void beetle::move()
{

	if (b_type == INPLACE)
	{
		if (moveOn)
		{
			_x += cos(_angle) * _speed * _time;

			_rc = RectMakeCenter(_x, _y,
				_enemyImage->getFrameWidth(),
				_enemyImage->getFrameHeight());

			this->collision();
		}
	}
	else
	{
		
		_isApproach = (abs(_x - _playerX) > 100) ? false : true;

		if (!_isApproach)
		{
			_x += (_x <= _playerX + 20) ? 3 : -3;
		}
		else
		{
			_x += (_turnLeft) ? -3 : 3;
		}

		_y = -sinf(TIMEMANAGER->getWorldTime() * 5) * _speed * 2 + _targetY;

		_rc = RectMakeCenter(_x, _y,
			_enemyImage->getFrameWidth(),
			_enemyImage->getFrameHeight());

	}
}

void beetle::render(HDC hdc)
{
	enemy::render(hdc);
	char str[100];
	//sprintf(str, "%f", _angle);
	//TextOut(hdc, _rc.left, _rc.top, str, strlen(str));
	//
	////cout << "gravity : " << _gravity << "\n";
	//FrameRect(hdc, _rc, RGB(255, 255, 0));
	//
	//if (_isApproach)
	//{
	//	textOut(hdc, _rc.left + 32, _rc.top + 32, "true", RGB(255, 0, 0));
	//}
	//else
	//{
	//	textOut(hdc, _rc.left + 32, _rc.top + 32, "false", RGB(255, 255, 0));
	//}

}

void beetle::animation()
{
	if (b_type == INPLACE)
	{
		_count++;
		if (!_isLeft)
		{
			_frameY = 1;
		}
		else
		{
			_frameY = 0;
		}

		if (!moveOn)
		{
			_frameX = 0;
		}
		else
		{
			if (_count % 4 == 0)
			{
				_frameX++;
				if (_frameX > _enemyImage->getMaxFrameX())
					_frameX = 1;
			}
		}
	}
	else
	{
		_count++;
		if (!_isLeft)
		{
			_frameY = 1;
		}
		else
		{
			_frameY = 0;
		}

		if (_count % 4 == 0)
		{
			_frameX++;
			if (_frameX > _enemyImage->getMaxFrameX())
				_frameX = 0;
		}
	}
}

void beetle::collision()
{
	if (b_type == INPLACE)
	{
		if (_pc->Leftcheck(_x, _y, _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight()))
		{
			_isLeft = false;
			_frameX = 2;
			_time = 0;
			moveOn = false;
		}
		if (_pc->Rightcheck(_x, _y, _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight()))
		{
			_isLeft = true;
			_frameX = 0;
			_time = 0;
			moveOn = false;
		}
	}
	else
	{

	}
}

//===================================
//	## Basu - ENEMY_FLYING_MOB2 ##
//===================================

HRESULT basu::init(float x, float y, player* player)
{
	enemy::init(player);
	_enemyName = "basu";
	_enemyImage = IMAGEMANAGER->findImage(_enemyName);
	_type = ENEMY_FLYING_MOB2;
	_x = x - WINSIZEX / 2 - 10;
	_targetX = x;
	_y = _targetY = y;
	_width = 64;
	_height = 64;
	_hp = 15;
	_speed = 15.f;
	_playerX = player->getPosX();
	_rc = RectMakeCenter(_x, _y, _width, _height);
	_fireCount = _idleCount = 0;
	_isFire = false;
	_turnLeft = false;
	_isApproach = true;

	_bullet = new bullet;
	_bullet->init("basu_bullet", _player->getCollisionMap(), 10, 800, 2);

	_reactionRange.rangeWidth = 500;
	_reactionRange.rangeHeight = 500;


	_reactionRange.rc = RectMakeCenter(_x, _y,
		_reactionRange.rangeWidth, _reactionRange.rangeHeight);


	return S_OK;
}

void basu::release(void)
{
	enemy::release();

	_bullet->release();
	SAFE_DELETE(_bullet);
}

void basu::update(void)
{
	enemy::update();
	_playerX = _player->getPosX();

	if (_state == ES_SPAWN)
	{

		this->animation();

		_isLeft = (_x >= _playerX) ? true : false;

		if (_x > _playerX + 100)
		{
			_turnLeft = true;
		}
		if (_x < _playerX - 100)
		{
			_turnLeft = false;
		}

		if(!_isApproach) fire();
		this->move();

	}

	_bullet->move(_player, true);
}

void basu::render(HDC hdc)
{
	enemy::render(hdc);
	_bullet->render(hdc);
}

void basu::animation()
{
	_count++;
	if (!_isLeft)
	{
		_frameY = 1;
	}
	else
	{
		_frameY = 0;
	}

	if (_isFire && !_isApproach)
	{
		if (_count % 4 == 0)
		{
			_frameX++;
			if (_frameX > 2)
				_frameX = 0;
		}
	}
	else
	{
		if (_count % 4 == 0)
		{
			_frameX++;
			if (_frameX > 1)
				_frameX = 0;
		}
	}
}

void basu::move()
{
	_isApproach = (abs(_x - _playerX) > 100) ? false : true;

	if (!_isApproach)
	{
		_x += (_x <= _playerX + 20) ? 4 : -4;
	}
	else
	{
		_x += (_turnLeft) ? -4 : 4;
	}

	_y = -sinf(TIMEMANAGER->getWorldTime() * 7) * _speed * 2 + _targetY;

	_rc = RectMakeCenter(_x, _y,
		_enemyImage->getFrameWidth(),
		_enemyImage->getFrameHeight());
}

void basu::fire()
{
	float distance = getDistance(_x, _y, _player->getPosX(), _player->getPosY());

	if (distance > 1200.f) return;
	if (!_isFire)
	{
		_fireCount++;
		if (_fireCount > 60)
		{
			_isFire = true;
			_fireCount = 0;
		}
	}
	else
	{
		_idleCount++;
		if (_idleCount > 30)
		{
			_bullet->fire(_x, _y,
				getAngle(_x, _y, _player->getPosX(), _player->getPosY()),
				_speed, _frameX, _frameY);

			_isFire = false;
			_idleCount = 0;
		}
	}

}

//===================================
//	## Behemoth - ENEMY_MOB2 ##
//===================================

HRESULT behemoth::init(float x, float y, player* player)
{
	enemy::init(player);
	_enemyName = "behemoth";
	_enemyImage = IMAGEMANAGER->findImage(_enemyName);
	_type = ENEMY_MOB2;
	_x = x;
	_y = y;
	if (RANDOM->Range(1))
	{
		_angle = 0;
	}
	else
	{
		_angle = PI;
	}
	_width = 80;
	_height = 64;
	_hp = 15;
	_prevHp = _hp;
	_rc = RectMakeCenter(_x, _y, _width, _height);
	gotDamage = false;

	_reactionRange.rc = RectMakeCenter(_x, _y,
		_reactionRange.rangeWidth, _reactionRange.rangeHeight);

	return S_OK;
}

void behemoth::release(void)
{
	enemy::release();
}

void behemoth::update(void)
{
	enemy::update();

	if (gotDamage)
	{
		_time += TIMEMANAGER->getElapedTime();
		if (_time > 1.f)
		{
			gotDamage = false;
			_frameX = 0;
			_time = 0.f;
		}
	}
	else
	{
		if (_state == ES_SPAWN || _state == ES_DAMAGED)
		{
			
			this->animation();
			if (IntersectRect(&tmp, &_rc, &CAMERA->getCamRect()))
			{
				this->move();
			}



			if (_state == ES_DAMAGED)
			{
				if (RANDOM->Range(1, 10) == 1)
				{
					FX->play("enemy_smoke_B", RANDOM->Range(_x - 70, _x + 70), RANDOM->Range(_rc.bottom - 50, _rc.bottom), 3);
				}
				if (!SOUNDMANAGER->isPlaySound("behemoth_angry"))
				{
					SOUNDMANAGER->play("behemoth_angry", .5f);
				}
					
				FX->play("enemy_smoke_B", RANDOM->Range(_x - 70, _x + 70), RANDOM->Range(_rc.bottom - 50, _rc.bottom), 3);
				_time += TIMEMANAGER->getElapedTime();
			}

			if (_time > 10.f)
			{
				_frameX = 0;
				_state = ES_SPAWN;
				_prevHp = _hp;
				_speed = RANDOM->Range(1.f,3.f);
				_time = 0.f;
			}
		}
		if (_prevHp - _hp == 1 && _state == ES_SPAWN)
		{
			_frameX = 3;
			_prevHp = _hp;
			gotDamage = true;
		}

		if (_prevHp - _hp >= 3 && _state == ES_SPAWN)
		{
			_state = ES_DAMAGED;
			_speed = 5.f;
			_frameX = 4;
		}
	}
}

void behemoth::render(HDC hdc)
{
	enemy::render(hdc);
}

void behemoth::animation()
{
	_count++;
	switch (_state)
	{
	case ES_SPAWN:
		if (!_isLeft)
		{
			_frameY = 1;
			if (_count % 10 == 0)
			{
				_frameX++;
				if (_frameX > 2)
					_frameX = 0;
			}
		}
		else
		{
			_frameY = 0;
			if (_count % 10 == 0)
			{
				_frameX++;
				if (_frameX > 2)
					_frameX = 0;
			}
		}
		break;
	case ES_DAMAGED:
		if (!_isLeft)
		{
			_frameY = 1;
			if (_count % 10 == 0)
			{
				_frameX++;
				if (_frameX > 5)
				{
					_frameX = 4;
				}
			}
		}
		else
		{
			_frameY = 0;
			if (_count % 10 == 0)
			{
				_frameX++;
				if (_frameX > 5)
				{
					_frameX = 4;
				}
			}
		}
		break;
	}

}

void behemoth::move()
{
	_x += cos(_angle) * _speed;

	_rc = RectMakeCenter(_x, _y,
		_enemyImage->getFrameWidth(),
		_enemyImage->getFrameHeight());

	_reactionRange.rc = RectMakeCenter(_x, _y,
		_reactionRange.rangeWidth, _reactionRange.rangeHeight);

	this->collision();
}

void behemoth::collision()
{
	if (_pc->Leftcheck(_x, _y, _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight()))
	{
		_isLeft = false;
	}
	if (_pc->Rightcheck(_x, _y, _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight()))
	{
		_isLeft = true;
	}
}

//===================================
//	## Basil - ENEMY_MOB3 ##
//===================================

HRESULT basil::init(float x, float y, player* player)
{
	enemy::init(player);
	_enemyName = "basil";
	_enemyImage = IMAGEMANAGER->findImage(_enemyName);
	_type = ENEMY_MOB3;
	_x = x;
	_y = y;
	_width = 64;
	_height = 64;
	_hp = 1000;
	_angle = 0.f;
	_speed = 10.f;
	_time = 0.f;
	_rc = RectMakeCenter(_x, _y, _width, _height);

	_reactionRange.rangeWidth = 100;
	_reactionRange.rangeHeight = 100;

	_reactionRange.rc = RectMakeCenter(_x, _y,
		_reactionRange.rangeWidth, _reactionRange.rangeHeight);

	return S_OK;
}

void basil::release(void)
{
	enemy::release();
}

void basil::update(void)
{
	this->move();

	_time += TIMEMANAGER->getElapedTime();

	if (!_isLeft && _x > CAMERA->getCamRect().right + 100)
	{
		_isLeft = true;
		_time = 0.f;
	}
	else if (_isLeft && _x < CAMERA->getCamRect().left)
	{
		_isLeft = false;
		_time = 0.f;
	}

	_angle = (_isLeft) ? PI : 0.f;
	_frameX = (_isLeft) ? 0 : 1;

	
}

void basil::render(HDC hdc)
{
	enemy::render(hdc);
}

void basil::move()
{
	_x += cos(_angle) * _speed * _time;

	_rc = RectMakeCenter(_x, _y,
		_enemyImage->getFrameWidth(),
		_enemyImage->getFrameHeight());

	this->collision();
}

void basil::collision()
{
	if (_pc->Leftcheck(_x, _y, _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight()))
	{
		_isLeft = false;
		_time = 0.f;
	}
	if (_pc->Rightcheck(_x, _y, _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight()))
	{
		_isLeft = true;
		_time = 0.f;
	}
}

//===================================
//	## Boss - ##
//===================================

HRESULT boss::init(float x, float y, player * player)
{
	enemy::init(player);
	_enemyName = "boss";
	_enemyImage = IMAGEMANAGER->findImage(_enemyName);
	_type = ENEMY_BOSS1;
	_x = _targetX = x;
	_targetY = y;
	_y = y + 350;
	_width = 64;
	_height = 64;
	_hp = 300;
	_speed = 10.f;
	_angle = PI;
	_frameY = 0;
	_frameX = 2;
	_rc = RectMakeCenter(_x, _y, _width, _height);
	_fireCount = _idleCount = _fireBullets = _fireTime = 0;
	_isFire = _teleport = false;

	_teleportL = IMAGEMANAGER->findImage("boss_fade_L");
	_teleportR = IMAGEMANAGER->findImage("boss_fade_R");

	_bullet = new bullet;
	_bullet->init("boss_bullet01", _player->getCollisionMap(), 10, 1200, 2);
	
	_bullet2 = new boss_bullet;
	_bullet2->init("boss_bullet02", _player, 2);

	return S_OK;
}

void boss::release(void)
{
	_bullet->release();
	SAFE_DELETE(_bullet);

}

void boss::update(void)
{
	enemy::update();
	if (_state != ES_DEAD)
	{
		

		if (_state == ES_NULL)
		{
			_frameX = 0;
			if (_targetY < _y)
			{
				if (_y <= _targetY + 150)
				{
					_time -= TIMEMANAGER->getElapedTime();
				}
				else
				{
					_time += TIMEMANAGER->getElapedTime();
				}

				_y -= _speed * _time;
			}

			else
			{
				_state = ES_SPAWN;
				_time = 0.f;
			}

		}

		else
		{
			this->animation();

			_time += TIMEMANAGER->getElapedTime();

			if (_time > 6.f && !_teleport)
			{
				FX->play("fade_L", _x, _y, 1, false, .5f, PI, true);
				FX->play("fade_R", _x, _y, 1, false, .5f, 0.f, true);
				_time = 0.f;
				_teleport = true;
				_x = 0; 
				_y = 0;
				_state = ES_TELEPORTED;
			}
			
			if (_teleport)
			{
				if (_time > RANDOM->Range(1.f, 3.f))
				{
					_teleport = false;
					_state = ES_SPAWN;
					_time = 0.f;
					_x = RANDOM->Range(500.f, 1800.f);
					_y = RANDOM->Range(250.f, 400.f);
					FX->play("fade_L", _x - 40, _y, 1, false, .5f, 0.f, true);
					FX->play("fade_R", _x + 40, _y, 1, false, .5f, PI, true);
				}
			}
			_isLeft = (_x >= _player->getPosX()) ? true : false;

			if (!_teleport)
			{
				bulletFire();
				
			}


			if (_hp < 150)
			{
				_fireTime += TIMEMANAGER->getElapedTime();
			}

			if (_fireTime > 6.f)
			{
				_bullet2->fire(_x, _y, _angle);
				_fireTime = 0.f;
			}
			

			this->move();

		}

		_bullet->move(_player, true);
		_bullet2->update();

		_rc = RectMakeCenter(_x, _y, _width, _height);
	}
}

void boss::render(HDC hdc)
{
	enemy::render(hdc);
	_bullet->render(hdc);
	_bullet2->render(hdc);
}

void boss::animation()
{
	_count++;
	if (!_isLeft)
	{
		_frameY = 1;
	}
	else
	{
		_frameY = 0;
	}
	if (_isFire)
	{
		if (_count % 6 == 0)
		{
			_frameX++;
			if (_frameX > 6)
				_frameX = 4;
		}
	}
	else
	{
		if (_count % 10 == 0)
		{
			_frameX++;
			if (_frameX > 1)
				_frameX = 0;
		}
	}
}

void boss::move()
{
	if (_state == ES_SPAWN)
	{
		_y += sinf(TIMEMANAGER->getWorldTime() * 3) * 3.f;
	}
}

void boss::bulletFire()
{
	float distance = getDistance(_x, _y, _player->getPosX(), _player->getPosY());

	if (distance > 1000.f) return;
	if (!_isFire)
	{
		_fireCount++;
		if (_fireCount > 80)
		{
			_state = ES_TELEPORTED;
			_frameX = 4;
			_isFire = true;
			_fireCount = 0;
		}
	}
	else
	{
		_idleCount++;
		if (_idleCount > 10)
		{
			_bullet->fire(_x, _y,
				getAngle(_x, _y, _player->getPosX(), _player->getPosY()),
				_speed, _frameX, _frameY);

			_fireBullets++;

			if (_fireBullets > 3)
			{
				_state = ES_SPAWN;
				_isFire = false;
				_fireBullets = 0;
				_frameX = 0;
			}
			
			_idleCount = 0;
		}
	}

}


HRESULT bird::init(float x, float y, int dir, player * player)
{
	enemy::init(player);
	_ringImg = IMAGEMANAGER->findImage("boss_ring");
	_enemyName = "boss_bird";
	_enemyImage = IMAGEMANAGER->findImage(_enemyName);
	_type = ENEMY_RING;
	_x = _targetX = x;
	_y = _targetY = y;
	_width = 64;
	_height = 64;
	_hp = 5;
	_angle = 360 / dir;
	_speed = 8.f;
	_theta = dir;
	_time = 0.f;
	_omega = 5.f;
	_rc = RectMakeCenter(_x, _y, _width, _height);

	_isBird = false;
	return S_OK;
}

void bird::release(void)
{
}

void bird::update()
{
	enemy::update();

	if (_state == ES_SPAWN)
	{
		_time += TIMEMANAGER->getElapedTime();

		if (_time > 3.f)
		{
			_isBird = true;
			_speed = 4.5f;
			_type = ENEMY_BIRD;
			_targAngle = getAngle(_x, _y, _player->getPosX(), _player->getPosY());
		}

		if (_targAngle >= PI_2 && _targAngle < PI2 *0.75)
		{
			_isLeft = true;
		}
		else
		{
			_isLeft = false;
		}

		this->move();
		this->animation();
	}
}

void bird::render(HDC hdc)
{
	if (_state == ES_SPAWN)
	{
		if (!_isBird)
		{
			_ringImg->render(hdc, _rc.left, _rc.top);
		}
		else
		{
			_enemyImage->frameRender(hdc, _rc.left, _rc.top, _frameX, _frameY);
		}
	}

	//sprintf(str, "%d", _hp);
	//TextOut(hdc, _rc.left, _rc.top, str, strlen(str));
}

void bird::animation()
{
	if (_isBird)
	{
		_count++;
		if (!_isLeft)
		{
			_frameY = 1;
		}
		else
		{
			_frameY = 0;
		}

		if (_count % 4 == 0)
		{
			_frameX++;
			if (_frameX > _enemyImage->getMaxFrameX())
				_frameX = 0;
		}
	}
}

void bird::move()
{
	if (!_isBird)
	{
		_x += cosf(_angle) * _speed * _time;
		_x += cosf(TIMEMANAGER->getWorldTime() * 5)* _speed;
		_y += sinf(_angle) * _speed * _time;
		_y += -sinf(TIMEMANAGER->getWorldTime() * 5)* _speed;

		if (_y > _targetY + 20)
		{
			_y -= (-sinf(_angle)) * _speed * _time;
		}
		if (_x > _targetX + 20)
		{
			_x -= cosf(_angle) * _speed * _time;
		}


		_rc = RectMakeCenter(_x, _y, _width, _height);
	}
	else
	{
		_x += cosf(_targAngle) * _speed;
		_y += -sinf(_targAngle) * _speed;
		_y += -sinf(TIMEMANAGER->getWorldTime()*3) * _speed;

		_rc = RectMakeCenter(_x, _y, _width, _height);

		this->collision();
	}

}

void bird::collision()
{
	if (_pc->Downcheck(_x, _y, _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight() - 20) ||
		_pc->Upcheck(_x, _y, _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight()) ||
		_pc->Leftcheck(_x, _y, _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight()) ||
		_pc->Rightcheck(_x, _y, _enemyImage->getFrameWidth(), _enemyImage->getFrameHeight()))
	{
		_hp = 0;
	}
}

void bird::reset()
{
	_state = ES_NULL;
	_hp = 5;
	_angle = 0.f;
	_speed = 3.f;
	_time = 0.f;
}
