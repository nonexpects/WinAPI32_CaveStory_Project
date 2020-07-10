#include "stdafx.h"
#include "player.h"
#include "effect.h"

HRESULT player::init(image* collisionMap)
{
	_idle = IMAGEMANAGER->findImage("player_idle");
	_run = IMAGEMANAGER->findImage("player_run");
	_run_up = IMAGEMANAGER->findImage("player_run_up");
	_jump = IMAGEMANAGER->findImage("player_jump");
	_jump_down = IMAGEMANAGER->findImage("player_jump_down");
	_up = IMAGEMANAGER->findImage("player_up");
	_down = IMAGEMANAGER->findImage("player_down");
	
	this->addPlayerFx();

	_collisionMap = collisionMap;
	
	_x = 1000;
	_y = WINSIZEY / 2;

	_width = 54;
	_height = 64;
	_alpha = 255;

	_isUp = _isDown = _getdamaged = damaged_jump = false;
	_isLeft = true;
	_count = _index = _delay = 0;
	rightRepulsivePower = 0.f;
	leftRepulsivePower = 0.f;

	_gravity = 0.f;
	_angle = 0;
	_speed = 3.0f;
	_time = _jumpTime = _jumpCheck = 0.f;
	_jumpPower = 15.f;

	_hp = _maxHp = 20;

	//물
	water = false;

	ZeroMemory(&U, sizeof(tagSensor));
	ZeroMemory(&D, sizeof(tagSensor));
	ZeroMemory(&L, sizeof(tagSensor));
	ZeroMemory(&R, sizeof(tagSensor));

	_state = P_IDLE;

	_rc = RectMakeCenter(_x, _y, _width, _height);

	inven::init(_collisionMap);

	getMachineGun()->setPlayer(this);

	return S_OK;
}

void player::release()
{
}

void player::update()
{
	if (_hp > _maxHp)
	{
		_hp = _maxHp;
	}
	if (_hp < 0)
	{
		FX->play("enemy_smoke", RANDOM->Range(_x - 50, _x + 50), RANDOM->Range(_y - 50, _y + 50), 2);
		FX->play("enemy_smoke", RANDOM->Range(_x - 50, _x + 50), RANDOM->Range(_y - 50, _y + 50), 2);
		FX->play("enemy_smoke", RANDOM->Range(_x - 50, _x + 50), RANDOM->Range(_y - 50, _y + 50), 2);
		FX->play("enemy_smoke", RANDOM->Range(_x - 50, _x + 50), RANDOM->Range(_y - 50, _y + 50), 2);
		FX->play("enemy_smoke", RANDOM->Range(_x - 50, _x + 50), RANDOM->Range(_y - 50, _y + 50), 2);
		SOUNDMANAGER->play("player_dead", .5f);
		_hp = 0;
	}

	if (_isLeft)
	{
		_angle = PI;
		
	}
	else
	{
		_angle = 0;
	}
	if (_isUp)
	{
		_angle = PI_2;
	}
	if (_isDown)
	{
		_angle = PI2 * 0.75;
	}

	inven::update(_x, _y, _rc, _angle, _isLeft, _isUp, _isDown);
	//FX->update();

	if (water)
	{
		_gravity += .5f;
		_speed = 2.f;
	}
	else
	{
		_speed = 3.0f;
	}

	_gravity += .6f;
	
	if (_gravity > 12.f)
	{
		_gravity = 12.f;
	}
	this->pixelCollision();
	
	if (INPUT->GetKey(VK_UP))
	{
		_isUp = true;
		_state = P_STAY_UP;
		
	}
	if (INPUT->GetKeyUp(VK_DOWN) || INPUT->GetKeyUp(VK_UP))
	{
		_isDown = false;
		_isUp = false;
		_state = P_IDLE;
	}
	if (INPUT->GetKey(VK_LEFT))
	{
		_isLeft = true;
		
	}
	if (INPUT->GetKeyUp(VK_LEFT))
	{
		_isLeft = true;
		_state = P_IDLE;
	}
	if (!L.isTouch)
	{
		if (INPUT->GetKey(VK_LEFT))
		{
			if (!SOUNDMANAGER->isPlaySound("walksound"))
			{
				SOUNDMANAGER->play("walksound");
			}
			_x -= _speed;
			_state = P_RUN;
			if (leftRepulsivePower < 3.f)
			{
				leftRepulsivePower += .3f;
			}
		}
	}
	if (INPUT->GetKey(VK_RIGHT))
	{
		_isLeft = false;
		
	}
	if (!R.isTouch)
	{
		if (INPUT->GetKey(VK_RIGHT))
		{
			if (!SOUNDMANAGER->isPlaySound("walksound"))
			{
				SOUNDMANAGER->play("walksound");
			}
			_x += _speed;
			_state = P_RUN;
			if (rightRepulsivePower < 3.f)
			{
				rightRepulsivePower += .3f;
			}
		}
	}
	if (INPUT->GetKeyUp(VK_RIGHT))
	{
		_isLeft = false;
		_state = P_IDLE;

	}
	if (!D.isJump && D.isTouch)
	{
		if (INPUT->GetKeyDown(VK_SPACE) && _state != P_JUMP_UP)
		{
			SOUNDMANAGER->play("jump", .5f);
			_state = P_JUMP_UP;
			D.isJump = true;
			_gravity -= 15.f;
		}

	}
	else
	{
		if (INPUT->GetKey(VK_SPACE) && !water)
		{
			if (_jumpPower < 10.f)
			{
				_jumpPower += .3f;
			}
		}
	}
	if (INPUT->GetKeyDown(VK_DOWN))
	{
		if (D.isJump)
		{
			_isDown = true;
		}
		else
		{
			_state = P_STAY_DOWN;
		}
	}

	if (_isDown && _currentIndex == 3 && getcurrentWeaponLv() == 3)
	{
		if (INPUT->GetKey('X'))
		{
			_gravity -= -2.f;
		}
	}
	if (_getdamaged)
	{
		_time += TIMEMANAGER->getElapedTime();
		_damageStore = (_hp - _hpStore);
		FX->numberPop(_x, _y - 40, _damageStore, 2.f);
		if (_time > 2.f)
		{
			_alpha = 255;
			_getdamaged = false;
			_time = 0.f;
			_damageStore = 0.f;
		}
		else
		{
			this->getDamaged();
		}
	}
	if (_state == P_STAY_DOWN || _delay > 0)
	{
		_delay++;
		_state = P_STAY_DOWN;
		if (_delay > 30)
		{
			_state = P_IDLE;
			_delay = 0;
		}
	}

	if (D.isJump) this->jump();

	_rc = RectMakeCenter(_x, _y, 64, 64);

	
	this->animation();

	_y += _gravity;

	if (!water)
	{
		_x -= leftRepulsivePower;
		_x += rightRepulsivePower;
	}

	if(leftRepulsivePower != 0.f || rightRepulsivePower != 0.f)
	{
		this->repulsive();
	}

}

void player::render(HDC hdc)
{
	

	inven::render(hdc, _rc);

	switch (_state)
	{
	case P_IDLE:
		if (_isLeft)
		{
			_idle->frameAlphaRender(hdc, _rc.left, _rc.top, 1, 0, _alpha);
		}
		else
		{
			_idle->frameAlphaRender(hdc, _rc.left, _rc.top, 0, 0, _alpha);
		}
		break;
	case P_RUN:
		if (_isUp)
		{
			if (_isLeft)
			{
				_run_up->frameAlphaRender(hdc, _rc.left, _rc.top, _index, 1, _alpha);
			}
			else
			{
				_run_up->frameAlphaRender(hdc, _rc.left, _rc.top, _index, 0, _alpha);
			}
		}
		else
		{
			if (_isLeft)
			{
				_run->frameAlphaRender(hdc, _rc.left, _rc.top, _index, 1, _alpha);
			}
			else
			{
				_run->frameAlphaRender(hdc, _rc.left, _rc.top, _index, 0, _alpha);
			}
		}
		break;
	case P_JUMP_UP:
		if (_isDown)
		{
			if (_isLeft)
			{
				_jump_down->frameAlphaRender(hdc, _rc.left, _rc.top, 0, 1, _alpha);
				break;
			}
			else
			{
				_jump_down->frameAlphaRender(hdc, _rc.left, _rc.top, 0, 0, _alpha);
				break;
			}
		}
		else if (_isUp)
		{
			if (_isLeft)
			{
				_run_up->frameAlphaRender(hdc, _rc.left, _rc.top, 1, 0, _alpha);
				break;
			}
			else
			{
				_run_up->frameAlphaRender(hdc, _rc.left, _rc.top, 2, 1, _alpha);
				break;
			}
		}
		else
		{
			if (_isLeft)
			{
				_jump->frameAlphaRender(hdc, _rc.left, _rc.top, 1, 1, _alpha);
				break;
			}
			else
			{
				_jump->frameAlphaRender(hdc, _rc.left, _rc.top, 0, 0, _alpha);
				break;
			}
		}
		break;
	case P_JUMP_DOWN:
		if (_isDown)
		{
			if (_isLeft)
			{
				_jump_down->frameAlphaRender(hdc, _rc.left, _rc.top, 0, 1, _alpha);
				break;
			}
			else
			{
				_jump_down->frameAlphaRender(hdc, _rc.left, _rc.top, 0, 0, _alpha);
				break;
			}
		}
		else if (_isUp)
		{
			if (_isLeft)
			{
				_run_up->frameAlphaRender(hdc, _rc.left, _rc.top, 0, 1, _alpha);
				break;
			}
			else
			{
				_run_up->frameAlphaRender(hdc, _rc.left, _rc.top, 3, 0, _alpha);
				break;
			}
		}
		else
		{
			if (_isLeft)
			{
				_jump->frameAlphaRender(hdc, _rc.left, _rc.top, 0, 1, _alpha);
			}
			else
			{
				_jump->frameAlphaRender(hdc, _rc.left, _rc.top, 1, 0, _alpha);
			}
			break;
		}
		break;
	case P_STAY_UP:
		if (_isLeft)
		{
			_up->frameAlphaRender(hdc, _rc.left, _rc.top, 0, 0, _alpha);
		}
		else
		{
			_up->frameAlphaRender(hdc, _rc.left, _rc.top, 0, 1, _alpha);
		}
		break;
	case P_STAY_DOWN:
		if (_isLeft)
		{
			_down->frameAlphaRender(hdc, _rc.left, _rc.top, 0, 0, _alpha);
		}
		else
		{
			_down->frameAlphaRender(hdc, _rc.left, _rc.top, 0, 1, _alpha);
		}
		break;
	}

	FX->render("shoot", hdc);
	FX->render("collision", hdc);
	FX->render("Lv_down", hdc);
	FX->render("Lv_up", hdc);
	FX->render("empty", hdc);
	FX->render("missile_smoke", hdc);
	FX->render("head", hdc);
	FX->render("question", hdc);
	FX->render("damaged", hdc);
	FX->render("water_splash", hdc);

	if (_getdamaged)
	{
		FX->popRender(hdc);
	}
}

void player::getDamaged()
{
	
	if (_count % 5 == 0)
	{
		if(_alpha == 255) _alpha = 0;
		else _alpha = 255;
	}
}

void player::jump()
{
	//포물선으로 움직임
	_x += cosf(PI_2) * _speed;
	if (damaged_jump)
	{
		_x += cosf(PI - _angle)* _speed;
	}
	_y += -sinf(PI_2) * (_speed + _jumpPower) + (_gravity * _jumpTime * _jumpTime);

	if (_state == P_JUMP_UP)
	{
		//cout << "JUMPUP!!" << endl;
	}

	if (_state == P_JUMP_DOWN || _state == P_JUMP_UP)
	{
		//if (_jumpPower > 0)
		//{
		//	_jumpPower -= 0.2f;
		//}
		_jumpTime += TIMEMANAGER->getElapedTime();
	}

	//cout << "g : " << _gravity << endl;
	//cout << "jT : " << _jumpTime << endl;
	//cout << "jC : " << _jumpCheck << endl;
	//cout << "jP : " << _jumpPower << endl;

	//_jumpCheck값이 _y보다 작아질때 즉 내려가고 있을 때 그리고 height값이 0이 아닐때(바닥에 붙어있지 않을 때) 
	if (_y > _jumpCheck && _jumpCheck != 0)
	{
		_state = P_JUMP_DOWN;
	}
	else //_jumpCheck가 계속해서 _y 값을 받는다
		_jumpCheck = _y;
}

void player::inWater(bool isWater)
{
	if ((isWater && !water) || (water && P_JUMP_UP))
	{
		FX->play("water_splash", _x, _y, 2, false, 1.f, PI-_angle, true);
		
	}
	water = isWater;
	
}

void player::pixelCollision()
{
	//픽셀 충돌시 충돌 확인할 픽셀
	U.x = D.x = _x;
	U.y = _y - _height / 2;
	D.y = _y + _height / 2;
	
	L.y = R.y = _y;
	L.x = _x - _width / 2;
	R.x = _x + _width / 2;
	
	U.rc = RectMakeCenter(U.x, U.y, 10, 10);
	D.rc = RectMakeCenter(D.x, D.y, 10, 10);
	L.rc = RectMakeCenter(L.x, L.y, 10, 10);
	R.rc = RectMakeCenter(R.x, R.y, 10, 10);
	
	U.isTouch = false;
	D.isTouch = false;
	L.isTouch = false;
	R.isTouch = false;
	
	//이부분이 픽셀충돌의 핵심
	
	for (int i = U.y + 3; i > U.y - 3; --i)
	{
		COLORREF color = GetPixel(_collisionMap->getMemDC(), U.x, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
	
		if ((r == 255 && g == 0 && b == 255))
		{
			if (_gravity < 0) _gravity = 0;
			U.isTouch = true;
			FX->play("head", U.x, U.y, 1, true, 0.2f, RANDOM->Range(0.f, PI2), true);
			FX->play("head", U.x, U.y, 1, true, 0.2f, RANDOM->Range(0.f, PI2), true);
			_y = i + _height / 2;
			_gravity++;
			break;
		}
	}
	for (int i = D.y - 5; i < D.y + 5; ++i)
	{
		COLORREF color = GetPixel(_collisionMap->getMemDC(), D.x, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
	
		if ((r == 255 && g == 0 && b == 255) && _state != P_JUMP_UP)
		{
			if (_state == P_JUMP_DOWN)
			{
				_state = P_IDLE;
			}
			damaged_jump = false;
			_jumpTime = 0.f;
			_jumpPower = 4.f;
			_jumpCheck = 0;
			D.isTouch = true;
			D.isJump = false;
			_isDown = false;
			_gravity = 0.f;
			_y = i - _height / 2;
			break;
		}
		else
		{
			_y++;
			_state = P_JUMP_DOWN;
		}
	}
	
	for (int i = L.x + 2; i > L.x -2; --i)
	{
		COLORREF color = GetPixel(_collisionMap->getMemDC(), i, L.y);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
	
		if (r == 255 && g == 0 && b == 255)
		{
			L.isTouch = true;
			_x = i + _width / 2;
			break;
		}
	}
	
	for (int i = R.x - 2; i < R.x + 2; ++i)
	{
		COLORREF color = GetPixel(_collisionMap->getMemDC(), i, R.y);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
	
		if (r == 255 && g == 0 && b == 255)
		{
			R.isTouch = true;
			_x = i - _width / 2;
			break;
		}
	}
}

void player::animation()
{
	_count++;

	switch (_state)
	{
	case P_RUN:
		if (_count % 8 == 0)
		{
			_index++;
			if (_index > _run->getMaxFrameX())
			{
				_index = 0;
			}
			//_run->setFrameX(_index);
		}
		break;
	//case P_STAY_UP:
	//	if (_count % 8 == 0)
	//	{
	//		_index++;
	//		if (_index > _run_up->getMaxFrameX())
	//		{
	//			_index = 0;
	//		}
	//		//_run->setFrameX(_index);
	//	}
	//	break;
	}
}

void player::repulsive()
{

	if (leftRepulsivePower > 0)
	{
		leftRepulsivePower -= 0.2f;
	}
	else
	{
		leftRepulsivePower = 0.f;
	}
	if (rightRepulsivePower > 0)
	{
		rightRepulsivePower -= 0.2f;
	}
	else
	{
		rightRepulsivePower = 0.f;
	}

	if (L.isTouch)
	{
		leftRepulsivePower = 0.f;
	}
	if (R.isTouch)
	{
		rightRepulsivePower = 0.f;
	}

}

void player::addPlayerFx()
{

	FX->addEffect("shoot", "fx_shoot", 1, 30);
	FX->addEffect("collision", "fx_collision", 1, 30);
	//FX->addEffect("damaged", "fx_damaged", 1, 5);
	FX->addEffect("Lv_down", "fx_lv_down", 3, 1);
	FX->addEffect("Lv_up", "fx_lv_up", 3, 1);
	FX->addEffect("empty", "fx_empty", 3, 1);
	FX->addEffect("firegun_lv2", "fx_fireball_lv2", 5, 30, 0, RANDOM->Range(2), -1, true);
	FX->addEffect("firegun_lv3", "fx_fireball_lv3", 5, 30, 0, RANDOM->Range(2), -1, true);
	FX->addEffect("machine_lv2_W", "fx_machine_lv2_w", 2, 10);
	FX->addEffect("machine_lv2_H", "fx_machine_lv2_h", 2, 10);
	FX->addEffect("machine_lv3_L", "fx_machine_lv3", 2, 10, 0, 0, 0);
	FX->addEffect("machine_lv3_R", "fx_machine_lv3", 2, 10, 1, 0, 1);
	FX->addEffect("machine_lv3_U", "fx_machine_lv3_1", 2, 10, 0, 0, 0);
	FX->addEffect("machine_lv3_D", "fx_machine_lv3_1", 2, 10, 1, 0, 1);
	FX->addEffect("booster", "fx_booster", 3, 10, 0, 0, -1, true);
	FX->addEffect("missile_smoke", "fx_smoke2", 10, 5);
	FX->addEffect("head", "fx_head", 5, 2, 0,0, 1);
	FX->addEffect("question", "fx_question", 5, 1);
	FX->addEffect("water_splash", "fx_water", 3.f, 5, RANDOM->Range(0, 4), RANDOM->Range(0, 5), -1, 10.f);
}
