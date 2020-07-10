#include "stdafx.h"
#include "bullet.h"
#include "enemyManager.h"
#include "player.h"

//=============================================================
//	## bullet ## (공용총알 - 너희들이 만들어야 함)
//=============================================================
HRESULT bullet::init(const char * imageName, image* collisionMap, int bulletMax, float range, int atk, bool isFrameImg)
{
	//총알 이미지 초기화
	_imageName = imageName;
	//총알갯수 및 사거리 초기화
	_bulletMax = bulletMax;
	_range = range;
	//총알이미지가 프레임 이미지냐?
	_isFrameImg = isFrameImg;
	_atk = atk;

	_pc = new pixelCollision;
	_pc->init(collisionMap);

	return S_OK;
}

void bullet::release()
{
	_pc->release();
	SAFE_DELETE(_pc);
}

void bullet::update()
{
}

void bullet::render(HDC hdc)
{
	if (_isFrameImg)//프레임 이미지
	{
		for (int i = 0; i < _vBullet.size(); i++)
		{
			if (!_vBullet[i].fire) continue;
			_vBullet[i].bulletImage->frameRender(hdc, _vBullet[i].rc.left, _vBullet[i].rc.top, _vBullet[i].frameX, _vBullet[i].frameY);
			//FrameRect(hdc, _vBullet[i].rc, RGB(0, 0, 255)); 
		}
	}
	else//일반 이미지
	{
		for (int i = 0; i < _vBullet.size(); i++)
		{
			if (!_vBullet[i].fire) continue;
			_vBullet[i].bulletImage->render(hdc, _vBullet[i].rc.left, _vBullet[i].rc.top);
		}
	}

}

void bullet::fire(float x, float y, float angle, float speed, int frameX, int frameY)
{
	//총알 벡터에 담는것을 제한한다
	if (_bulletMax < _vBullet.size() + 1) return;

	//총알 구조체 선언
	tagBullet bullet;
	//총알구조체 초기화
	//제로메모리, 멤셋
	//구조체의 변수들의 값을 한번에 0으로 초기화 시켜준다
	ZeroMemory(&bullet, sizeof(tagBullet));
	//bullet.bulletImage = new image;
	bullet.bulletImage = IMAGEMANAGER->findImage(_imageName);
	bullet.fire = true;
	bullet.speed = speed;
	bullet.angle = angle;
	bullet.frameX = frameX;
	bullet.frameY = frameY;
	bullet.atk = _atk;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	if (_isFrameImg)
	{
		bullet.rc = RectMakeCenter(bullet.x, bullet.y,
			bullet.bulletImage->getFrameWidth(),
			bullet.bulletImage->getFrameHeight());
	}
	else
	{
		bullet.rc = RectMakeCenter(bullet.x, bullet.y,
			bullet.bulletImage->getWidth(),
			bullet.bulletImage->getHeight());
	}

	//벡터에 담기
	_vBullet.push_back(bullet);
}

void bullet::move(player* _player, bool isAnim)
{
	for (int i = 0; i < _vBullet.size(); i++)
	{
		_vBullet[i].x += cosf(_vBullet[i].angle) * _vBullet[i].speed;
		_vBullet[i].y += -sinf(_vBullet[i].angle) * _vBullet[i].speed;

		if (_isFrameImg)
		{
			_vBullet[i].rc = RectMakeCenter(_vBullet[i].x, _vBullet[i].y,
				_vBullet[i].bulletImage->getFrameWidth(),
				_vBullet[i].bulletImage->getFrameHeight());
		}
		else
		{
			_vBullet[i].rc = RectMakeCenter(_vBullet[i].x, _vBullet[i].y,
				_vBullet[i].bulletImage->getWidth(),
				_vBullet[i].bulletImage->getHeight());
		}

		if (isAnim)
		{
			if (_vBullet[i].count % 10 == 0)
			{
				_vBullet[i].bulletImage->setFrameX(_vBullet[i].frameX);
				_vBullet[i].frameX++;

				if (_vBullet[i].frameX > _vBullet[i].bulletImage->getMaxFrameX())
				{
					_vBullet[i].frameX = 0;
				}
			}
		}


		float distance = getDistance(_vBullet[i].fireX, _vBullet[i].fireY,
			_vBullet[i].x, _vBullet[i].y);
		if (_range < distance)
		{
			this->removeBullet(i);
			break;
		}

		this->checkBulletColl(_vBullet[i], _player, i);

	}
}

void bullet::move(enemyManager* _em)
{
	for (int i = 0; i < _vBullet.size(); i++)
	{
		_vBullet[i].x += cosf(_vBullet[i].angle) * _vBullet[i].speed;
		_vBullet[i].y += -sinf(_vBullet[i].angle) * _vBullet[i].speed;

		if (_isFrameImg)
		{
			_vBullet[i].rc = RectMakeCenter(_vBullet[i].x, _vBullet[i].y,
				_vBullet[i].bulletImage->getFrameWidth(),
				_vBullet[i].bulletImage->getFrameHeight());
		}
		else
		{
			_vBullet[i].rc = RectMakeCenter(_vBullet[i].x, _vBullet[i].y,
				_vBullet[i].bulletImage->getWidth(),
				_vBullet[i].bulletImage->getHeight());
		}

		
		
		//총알이 사거리 보다 커졌을때
		float distance = getDistance(_vBullet[i].fireX, _vBullet[i].fireY,
			_vBullet[i].x, _vBullet[i].y);
		if (_range < distance)
		{
			this->removeBullet(i);
			break;
		}
		
		this->checkBulletColl(_vBullet[i], _em, i);

	}
}
void bullet::checkBulletColl(tagBullet & bullet, enemyManager* _em, int index)
{
	if (bullet.angle == 0)
	{
		if (_pc->Rightcheck(bullet.x, bullet.y, bullet.bulletImage->getFrameWidth(), bullet.bulletImage->getFrameHeight() - 10))
		{
			this->removeBullet(index);
		}
	}
	else if (bullet.angle == PI_2)
	{
		if (_pc->Upcheck(bullet.x, bullet.y, bullet.bulletImage->getFrameWidth(), bullet.bulletImage->getFrameHeight() - 10))
		{
			this->removeBullet(index);
		}
	}
	else if (bullet.angle == PI)
	{
		if (_pc->Leftcheck(bullet.x, bullet.y, bullet.bulletImage->getFrameWidth() - 10, bullet.bulletImage->getFrameHeight()))
		{
			this->removeBullet(index);
		}
	}
	else
	{
		if (_pc->Downcheck(bullet.x, bullet.y, bullet.bulletImage->getFrameWidth() - 10, bullet.bulletImage->getFrameHeight()))
		{
			this->removeBullet(index);
		}
	}
	RECT tmp;
	for (int i = 0; i < _em->getEnemies().size(); i++)
	{
		if (IntersectRect(&tmp, &bullet.rc, &_em->getEnemies()[i]->getRect()))
		{
			removeBullet(index);
			if (_em->getEnemies()[i]->getEnemyType() != ENEMY_RING)
			{
				if (_em->getEnemies()[i]->getEnemyType() == EMENY_MOB1)
				{
					SOUNDMANAGER->play("enemy_damaged", .5f);
				}
				_em->getEnemies()[i]->setHp(_em->getEnemies()[i]->getHp() - bullet.atk);
			}
			break;
		}
	}
}

void bullet::checkBulletColl(tagBullet & bullet, player * _player, int index)
{
	if (bullet.angle == 0)
	{
		if (_pc->Rightcheck(bullet.x, bullet.y, bullet.bulletImage->getFrameWidth(), bullet.bulletImage->getFrameHeight() - 10))
		{
			this->removeBullet(index);
		}
	}
	else if (bullet.angle == PI_2)
	{
		if (_pc->Upcheck(bullet.x, bullet.y, bullet.bulletImage->getFrameWidth(), bullet.bulletImage->getFrameHeight() - 10))
		{
			this->removeBullet(index);
		}
	}
	else if (bullet.angle == PI)
	{
		if (_pc->Leftcheck(bullet.x, bullet.y, bullet.bulletImage->getFrameWidth() - 10, bullet.bulletImage->getFrameHeight()))
		{
			this->removeBullet(index);
		}
	}
	else
	{
		if (_pc->Downcheck(bullet.x, bullet.y, bullet.bulletImage->getFrameWidth() - 10, bullet.bulletImage->getFrameHeight()))
		{
			this->removeBullet(index);
		}
	}
	RECT tmp;
	if (IntersectRect(&tmp, &bullet.rc, &_player->getRect()) && !_player->getDamageState())
	{
		_player->setGravity(-10.f);
		_player->setDownJumpTrue();
		_player->jump();
		_player->setDamage(true);
		_player->setExpUp(-1);
		removeBullet(index);
		_player->setHp(_player->getHP() - bullet.atk);
	}

}

void bullet::changeBullet(const char* imageName, int atk, float range)
{
	_imageName = imageName;
	_atk = atk;
	_range = range;
}

//폭탄 삭제
void bullet::removeBullet(int index)
{
	if (_vBullet.empty()) return;
	SOUNDMANAGER->play("hitSound1", .5f);
	FX->play("collision", _vBullet[index].x, _vBullet[index].y, FX_SPEED);
	_vBullet.erase(_vBullet.begin() + index);
}



//=============================================================
//	## missile ## (missile[0] -> 배열처럼 미리 장전해두고 총알발사)
//=============================================================
HRESULT missile::init(const char * imageName, image* collisionMap, int bulletMax, float range, int atk, bool isLauncher, bool isFrameImg)
{
	_imageName = imageName;
	//총알 사거리 및 총알 갯수 초기화
	_range = range;
	_bulletMax = bulletMax;
	_isFrameImg = isFrameImg;
	_atk = atk;
	_isLauncher = isLauncher;

	if (_isFrameImg)
	{
		_width = IMAGEMANAGER->findImage(_imageName)->getFrameWidth();
		_height = IMAGEMANAGER->findImage(_imageName)->getFrameHeight();
	}
	else
	{
		_width = IMAGEMANAGER->findImage(_imageName)->getWidth();
		_height = IMAGEMANAGER->findImage(_imageName)->getHeight();
	}

	_pc = new pixelCollision;
	_pc->init(collisionMap);

	
	this->addBullet(bulletMax);

	return S_OK;
	
}

void missile::release()
{
	_pc->release();
	SAFE_DELETE(_pc);
}

void missile::update()
{
}

void missile::render(HDC hdc)
{
	FX->render("machine_lv2_W", hdc);
	FX->render("machine_lv2_H", hdc);
	FX->render("machine_lv3_L", hdc);
	FX->render("machine_lv3_R", hdc);
	FX->render("machine_lv3_U", hdc);
	FX->render("machine_lv3_D", hdc);
	FX->render("booster", hdc);

	if (_isFrameImg)//프레임 이미지
	{
		for (int i = 0; i < _vBullet.size(); i++)
		{
			if (!_vBullet[i].fire) continue;
			_vBullet[i].bulletImage->frameRender(hdc, _vBullet[i].rc.left, _vBullet[i].rc.top, _vBullet[i].frameX, _vBullet[i].frameY);
			//FrameRect(hdc, _vBullet[i].rc, RGB(0, 0, 255));
		}
	}
	else//일반 이미지
	{
		for (int i = 0; i < _vBullet.size(); i++)
		{
			if (!_vBullet[i].fire) continue;
			_vBullet[i].bulletImage->render(hdc, _vBullet[i].rc.left, _vBullet[i].rc.top);
		}
	}
}

void missile::fire(float x, float y, float angle, float speed, int frameX, int frameY)
{
	_viBullet = _vBullet.begin();

	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_viBullet->fire) continue;
		_viBullet->bulletImage = IMAGEMANAGER->findImage(_imageName);
		_viBullet->fire = true;
		if (!_isLauncher && _lv == 3)
		{
			if (angle == PI)
			{
				x -= 10;
			}
			else if (angle == 0.f)
			{
				x += 10;
			}
		}

		_viBullet->x = _viBullet->fireX = x;
		_viBullet->y = _viBullet->fireY = y - 10;
		_viBullet->speed = speed;
		_viBullet->angle = angle;
		_viBullet->atk = _atk;
		_viBullet->gravity = RANDOM->Range(-1.f, 1.f);
		_viBullet->frameX = frameX;
		_viBullet->frameY = frameY;
		if (_isFrameImg)
		{
			_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
				_viBullet->bulletImage->getFrameWidth(),
				_viBullet->bulletImage->getFrameHeight());
		}
		else
		{
			_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
				_viBullet->bulletImage->getWidth(),
				_viBullet->bulletImage->getHeight());
		}

		break;
	}
}

void missile::move(enemyManager* _em)
{
	_time += TIMEMANAGER->getElapedTime();
	for (int i = 0; i < _vBullet.size(); i++)
	{
		if (!_vBullet[i].fire) continue;

		_vBullet[i].x += cosf(_vBullet[i].angle) * _vBullet[i].speed;
		_vBullet[i].y += -sinf(_vBullet[i].angle) * _vBullet[i].speed + _vBullet[i].gravity;
		//총알이 사거리 보다 커졌을때
		float distance = getDistance(_vBullet[i].fireX, _vBullet[i].fireY,
			_vBullet[i].x, _vBullet[i].y);

		if (_isLauncher)
		{
			if((int)distance % 30 == 0)
				FX->play("booster", _vBullet[i].x, _vBullet[i].y, 2);
		}
			
		if (_lv == 2)
		{
			if (!_isLauncher)
			{
				if (_vBullet[i].angle == 0.f || _vBullet[i].angle == PI)
				{
					FX->play("machine_lv2_W", _vBullet[i].x, _vBullet[i].y, 2);
				}														    
				else													    
				{														    
					FX->play("machine_lv2_H", _vBullet[i].x, _vBullet[i].y, 2);
				}
			}
		}
		else if (_lv == 3)
		{
			if (!_isLauncher)
			{
				if (_vBullet[i].angle == 0.f)
				{
					FX->play("machine_lv3_R", _vBullet[i].x - 30, _vBullet[i].y, 2);
				}
				else if (_vBullet[i].angle == PI)
				{
					FX->play("machine_lv3_L", _vBullet[i].x + 30, _vBullet[i].y, 2);
				}
				else if(_vBullet[i].angle == PI_2)
				{
					FX->play("machine_lv3_U", _vBullet[i].x, _vBullet[i].y + 20, 2);
				}
				else
				{
					FX->play("machine_lv3_D", _vBullet[i].x, _vBullet[i].y - 20, 2);
				}
			}
		}

		if (_isFrameImg)
		{
			_vBullet[i].rc = RectMakeCenter(_vBullet[i].x, _vBullet[i].y,
				_vBullet[i].bulletImage->getFrameWidth(),
				_vBullet[i].bulletImage->getFrameHeight());
		}
		else
		{
			_vBullet[i].rc = RectMakeCenter(_vBullet[i].x, _vBullet[i].y,
				_vBullet[i].bulletImage->getWidth(),
				_vBullet[i].bulletImage->getHeight());
		}

		
		if (_range < distance)
		{
			_vBullet.erase(_vBullet.begin() + i);
			break;
		}
		
		this->checkBulletColl(_vBullet[i], _em, i);

	}
}

void missile::checkBulletColl(tagBullet & bullet, enemyManager* _em, int index)
{
	if (bullet.angle == 0)
	{
		if (_pc->Rightcheck(bullet.x, bullet.y, bullet.bulletImage->getFrameWidth(), bullet.bulletImage->getFrameHeight() - 10))
		{
			removeBullet(index);
		}
	}
	else if (bullet.angle == PI_2)
	{
		if (_pc->Upcheck(bullet.x, bullet.y, bullet.bulletImage->getFrameWidth(), bullet.bulletImage->getFrameHeight() - 10))
		{
			removeBullet(index);
		}
	}
	else if (bullet.angle == PI)
	{
		if (_pc->Leftcheck(bullet.x, bullet.y, bullet.bulletImage->getFrameWidth() - 10, bullet.bulletImage->getFrameHeight()))
		{
			removeBullet(index);
		}
	}
	else
	{
		if (_pc->Downcheck(bullet.x, bullet.y, bullet.bulletImage->getFrameWidth() - 10, bullet.bulletImage->getFrameHeight()))
		{
			removeBullet(index);
		}
	}
	RECT tmp;
	for (int i = 0; i < _em->getEnemies().size(); i++)
	{
		if (IntersectRect(&tmp, &bullet.rc, &_em->getEnemies()[i]->getRect()))
		{
			_em->getEnemies()[i]->damagedFX();
			if (_em->getEnemies()[i]->getEnemyType() != ENEMY_RING)
			{
				if (_em->getEnemies()[i]->getEnemyType() == EMENY_MOB1)
				{
					SOUNDMANAGER->play("enemy_damaged", .5f);
				}
				_em->getEnemies()[i]->setHp(_em->getEnemies()[i]->getHp() - bullet.atk);
			}
			removeBullet(index);
			break;
		}
	}
}

void missile::changeBullet(const char * imageName, int atk, float range)
{
	_imageName = imageName;
	_atk = atk;
	_range = range;
}

void missile::removeBullet(int index)
{
	FX->offFX("machine_lv2_W");
	FX->offFX("machine_lv2_H");
	FX->offFX("machine_lv3_L");
	FX->offFX("machine_lv3_R");
	FX->offFX("machine_lv3_U");
	FX->offFX("machine_lv3_D");
	FX->play("collision", _vBullet[index].x, _vBullet[index].y, FX_SPEED);

	if (_isLauncher)
	{
		SOUNDMANAGER->play("hitSound_exp", .5f);
		FX->play("missile_smoke", RANDOM->Range(_vBullet[index].x - 100, _vBullet[index].x + 100),
			RANDOM->Range(_vBullet[index].y - 100, _vBullet[index].y + 100), 3);
		FX->play("missile_smoke", RANDOM->Range(_vBullet[index].x - 100, _vBullet[index].x + 100),
			RANDOM->Range(_vBullet[index].y - 100, _vBullet[index].y + 100), 3);
		FX->play("missile_smoke", RANDOM->Range(_vBullet[index].x - 100, _vBullet[index].x + 100),
			RANDOM->Range(_vBullet[index].y - 100, _vBullet[index].y + 100), 3);
		FX->play("missile_smoke", RANDOM->Range(_vBullet[index].x - 100, _vBullet[index].x + 100),
			RANDOM->Range(_vBullet[index].y - 100, _vBullet[index].y + 100), 3);
	}
	else
	{
		SOUNDMANAGER->play("hitSound1", .5f);
	}
	_time = 0.f;
	_vBullet.erase(_vBullet.begin() + index);
	
}

void missile::addBullet(int max)
{
	if (_vBullet.size() == _bulletMax) return;

	if (_vBullet.size() + max > _bulletMax)
	{
		max = _bulletMax - _vBullet.size();
	}
	
	//총알의 갯수만큼 구조체를 초기화 한 후 벡터에 담기
	for (int i = 0; i < max; i++)
	{
		//총알 구조체 선언
		tagBullet bullet;
		//총알구조체 초기화
		//제로메모리, 멤셋
		//구조체의 변수들의 값을 한번에 0으로 초기화 시켜준다
		ZeroMemory(&bullet, sizeof(tagBullet));
		bullet.bulletImage = IMAGEMANAGER->findImage(_imageName);
		bullet.fire = false;

		//벡터에 담기
		_vBullet.push_back(bullet);
	}

}

//=============================================================
//	## fireBullet ## (폭탄처럼 한발씩 발사하고 생성하고 자동삭제)
//=============================================================

HRESULT firebullet::init(const char * imageName, image* collisionMap, int bulletMax, float range, int atk, bool isFrameImg)
{
	_imageName = imageName;
	_range = range;
	_bulletMax = bulletMax;
	_isFrameImg = isFrameImg;
	_atk = atk;
	_lv = 1;
	_FXcount =  0;

	if (_isFrameImg)
	{
		_width = IMAGEMANAGER->findImage(_imageName)->getFrameWidth();
		_height = IMAGEMANAGER->findImage(_imageName)->getFrameHeight();
	}
	else
	{
		_width = IMAGEMANAGER->findImage(_imageName)->getWidth();
		_height = IMAGEMANAGER->findImage(_imageName)->getHeight();
	}

	_pc = new pixelCollision;
	_pc->init(collisionMap);



	//총알의 갯수만큼 구조체를 초기화 한 후 벡터에 담기
	for (int i = 0; i < bulletMax; i++)
	{
		//총알 구조체 선언
		tagBullet bullet;
		//총알구조체 초기화
		//제로메모리, 멤셋
		//구조체의 변수들의 값을 한번에 0으로 초기화 시켜준다
		ZeroMemory(&bullet, sizeof(tagBullet));
		bullet.atk = _atk;
		bullet.fire = false;

		//벡터에 담기
		_vBullet.push_back(bullet);
	}


	return S_OK;
}

void firebullet::release()
{
	_pc->release();
	SAFE_DELETE(_pc);
}

void firebullet::update()
{
}

void firebullet::render(HDC hdc)
{
	FX->render("firegun_lv2", hdc);
	FX->render("firegun_lv3", hdc);

	if (_isFrameImg)//프레임 이미지
	{
		for (int i = 0; i < _vBullet.size(); i++)
		{
			if (!_vBullet[i].fire) continue;
			_vBullet[i].bulletImage->frameRender(hdc, _vBullet[i].rc.left, _vBullet[i].rc.top);
			//FrameRect(hdc, _vBullet[i].rc, RGB(0, 0, 255));

			//_pc->sensorCheck(hdc, _pc->getDownSensor());
			
		}
	}
	else//일반 이미지
	{
		for (int i = 0; i < _vBullet.size(); i++)
		{
			if (!_vBullet[i].fire) continue;
			_vBullet[i].bulletImage->render(hdc, _vBullet[i].rc.left, _vBullet[i].rc.top);
		}
	}
}

void firebullet::fire(float x, float y, float angle, float speed, int frameX, int frameY)
{

	for (int i = 0; i < _vBullet.size(); i++)
	{
		if (_vBullet[i].fire) continue;
		_vBullet[i].bulletImage = IMAGEMANAGER->findImage(_imageName);
		_vBullet[i].fire = true;
		_vBullet[i].x = _vBullet[i].fireX = x;
		_vBullet[i].y = _vBullet[i].fireY = y - 10;
		_vBullet[i].width = _width;
		_vBullet[i].height = _height;
		_vBullet[i].speed = speed;
		_vBullet[i].angle = angle;
		_vBullet[i].atk = _atk;
		_vBullet[i].lv = _lv;
		//_viBullet->frameX = frameX;
		//_viBullet->frameY = frameY;
		_vBullet[i].rc = RectMakeCenter(_vBullet[i].x, _vBullet[i].y,
			_vBullet[i].width, _vBullet[i].height);
		
		break;
	}

	
}

void firebullet::move(enemyManager* _em)
{
	
	for (int i = 0; i < _vBullet.size(); i++)
	{
		if (!_vBullet[i].fire) continue;
		
		
		_vBullet[i].gravity += 0.4f;
		_vBullet[i].time += TIMEMANAGER->getElapedTime();
		_vBullet[i].x += cosf(_vBullet[i].angle) * _vBullet[i].speed;
		_vBullet[i].y += -sinf(_vBullet[i].angle) * _vBullet[i].speed + _vBullet[i].gravity;
		
		//총알이 사거리 보다 커졌을때
		float distance = getDistance(_vBullet[i].fireX, _vBullet[i].fireY,
			_vBullet[i].x, _vBullet[i].y);

		if (_vBullet[i].lv == 2)
		{
			if ((int)distance % 2 == 1)
			FX->play("firegun_lv2", _vBullet[i].x, _vBullet[i].y, 3, false, _range, _vBullet[i].angle);
		}
		if (_vBullet[i].lv == 3)
		{
			if ((int)distance % 2 == 1)
			FX->play("firegun_lv3", _vBullet[i].x, _vBullet[i].y, 3, false, _range, _vBullet[i].angle);
		}
		
		if (_vBullet[i].angle == PI_2)
		{
			if (left)
			{
				_vBullet[i].x += cosf(0);
			}
			else
			{
				_vBullet[i].x -= cosf(PI);
			}
		}


		_vBullet[i].count++;

		_vBullet[i].rc = RectMakeCenter(_vBullet[i].x, _vBullet[i].y,
			_vBullet[i].width, _vBullet[i].height);

		if (_vBullet[i].count % 10 == 0)
		{
			_vBullet[i].bulletImage->setFrameX(_vBullet[i].frameX);
			_vBullet[i].frameX++;

			if (_vBullet[i].frameX > _vBullet[i].bulletImage->getMaxFrameX())
			{
				_vBullet[i].frameX = 0;
			}
		}
		
		if (_range < _vBullet[i].time)
		{
			this->removeBullet(i);
			FX->offFX("firegun_lv2");
			FX->offFX("firegun_lv3");
			break;
		}

		this->checkBulletColl(_vBullet[i], _em, i);
	}

	
}

void firebullet::checkBulletColl(tagBullet & bullet, enemyManager* _em, int index)
{

	if (_pc->Downcheck(bullet.x, bullet.y, bullet.width, bullet.height - 8))
	{
		//bullet.y -= 5;
		bullet.gravity = -5.f;
	}
	if (_pc->Leftcheck(bullet.x, bullet.y, bullet.width - 6, bullet.height))
	{
		bullet.angle = PI2 - (PI - bullet.angle);
	}
	if (_pc->Rightcheck(bullet.x, bullet.y, bullet.width - 6, bullet.height))
	{
		bullet.angle = PI + (bullet.angle);
	}
	RECT tmp;
	for (int i = 0; i < _em->getEnemies().size(); i++)
	{
		if (IntersectRect(&tmp, &bullet.rc, &_em->getEnemies()[i]->getRect()))
		{
			FX->offFX("firegun_lv2");
			FX->offFX("firegun_lv3");
			removeBullet(index);
			if (_em->getEnemies()[i]->getEnemyType() != ENEMY_RING)
			{
				if (_em->getEnemies()[i]->getEnemyType() == EMENY_MOB1)
				{
					SOUNDMANAGER->play("enemy_damaged", .5f);
				}
				_em->getEnemies()[i]->setHp(_em->getEnemies()[i]->getHp() - bullet.atk);
			}
			break;
		}
	}

}

void firebullet::changeBullet(const char * imageName, int atk, float range, bool isSizeChange, int width, int height)
{
	_imageName = imageName;
	_atk = atk;
	_range = range;
	if (isSizeChange)
	{
		_width = width;
		_height = height;
	}
}

void firebullet::removeBullet(int index)
{
	_FXcount--;
	FX->play("shoot", _vBullet[index].x, _vBullet[index].y, FX_SPEED);
	SOUNDMANAGER->play("hitSound1", .5f);
	_vBullet.erase(_vBullet.begin() + index);
}

//===============================================================
//	## boss_bullet ## // 플레이어의 X좌표에 다다르면 아래로 수직낙하
//===============================================================

HRESULT boss_bullet::init(const char* imageName, player* player, int bulletMax)
{
	//총알갯수 및 사거리 초기화
	_atk = 3;
	_player = player;
	fireOn = false;
	_fireX = _fireY = _angle = _time = 0.f;
	bulletCount = 0;
	_bulletMax = bulletMax;
	_imageName = imageName;

	_pc = new pixelCollision;
	_pc->init(_player->getCollisionMap());

	return S_OK;
}

void boss_bullet::release()
{
	_pc->release();
	SAFE_DELETE(_pc);
}

void boss_bullet::update()
{
	_time += TIMEMANAGER->getElapedTime();

	if (fireOn && _time > .4f)
	{
		this->fire(_fireX, _fireY, _angle);
		if (bulletCount > _bulletMax)
		{
			fireOn = false;
			_fireX = _fireY = _angle = _time = 0.f;
			bulletCount = 0;
		}
	}
	
	this->move();

}

void boss_bullet::render(HDC hdc)
{
	for (int i = 0; i < _vBullet.size(); i++)
	{
		if (!_vBullet[i].fire) continue;
		_vBullet[i].bulletImage->frameRender(hdc, _vBullet[i].rc.left, _vBullet[i].rc.top, _vBullet[i].frameX, _vBullet[i].frameY);
		//FrameRect(hdc, _vBullet[i].rc, RGB(0, 0, 255)); 
	}
}

void boss_bullet::fire(float x, float y, float angle)
{
	fireOn = true;
	bulletCount++;
	//총알 구조체 선언
	tagBullet bullet;
	//총알구조체 초기화
	//제로메모리, 멤셋
	//구조체의 변수들의 값을 한번에 0으로 초기화 시켜준다
	ZeroMemory(&bullet, sizeof(tagBullet));
	//bullet.bulletImage = new image;
	bullet.bulletImage = IMAGEMANAGER->findImage(_imageName);
	bullet.fire = true;
	bullet.speed = 3.f;
	bullet.angle = _angle = angle;
	bullet.frameX = 0;
	bullet.frameY = 0;
	bullet.atk = _atk;
	bullet.meet = false;
	bullet.x = bullet.fireX = _fireX = x;
	bullet.y = bullet.fireY = _fireY = y;

	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.bulletImage->getFrameWidth(),
		bullet.bulletImage->getFrameHeight());

	//벡터에 담기
	_vBullet.push_back(bullet);

	_time = 0.f;
}

void boss_bullet::move()
{
	for (int i = 0; i < _vBullet.size(); i++)
	{
		if (!_vBullet[i].fire) continue;
		
		if (_vBullet[i].meet)
		{
			_vBullet[i].bulletImage = IMAGEMANAGER->findImage("boss_bullet03");

			_vBullet[i].frameX = 0;
			_vBullet[i].frameY = 0;
			_vBullet[i].y+= 20;
		}
		else
		{
			_vBullet[i].x += cosf(_vBullet[i].angle) * _vBullet[i].speed;
			_vBullet[i].y += -sinf(_vBullet[i].angle) * _vBullet[i].speed;
			_vBullet[i].y += cosf(TIMEMANAGER->getWorldTime() * 3) * _vBullet[i].speed;

			_vBullet[i].count++;
			if (_vBullet[i].count % 5 == 0)
			{
				_vBullet[i].frameX++;
				if (_vBullet[i].frameX > 1)
				{
					_vBullet[i].frameX = 0;
				}
			}
		}

		_vBullet[i].rc = RectMakeCenter(_vBullet[i].x, _vBullet[i].y,
			_vBullet[i].bulletImage->getFrameWidth(),
			_vBullet[i].bulletImage->getFrameHeight());
		
		if (_vBullet[i].x > _player->getPosX() - 5 && _vBullet[i].x < _player->getPosX() +5)
		{
			_vBullet[i].meet = true;
			_vBullet[i].frameX = 2;
		}

		this->checkBulletColl(_vBullet[i], i);
	}
}
void boss_bullet::checkBulletColl(tagBullet & bullet, int index)
{
	if (bullet.angle == 0)
	{
		if (_pc->Rightcheck(bullet.x, bullet.y, bullet.bulletImage->getFrameWidth(), bullet.bulletImage->getFrameHeight() - 10))
		{
			this->removeBullet(index);
		}
	}
	else if (bullet.angle == PI_2)
	{
		if (_pc->Upcheck(bullet.x, bullet.y, bullet.bulletImage->getFrameWidth(), bullet.bulletImage->getFrameHeight() - 10))
		{
			this->removeBullet(index);
		}
	}
	else if (bullet.angle == PI)
	{
		if (_pc->Leftcheck(bullet.x, bullet.y, bullet.bulletImage->getFrameWidth() - 10, bullet.bulletImage->getFrameHeight()))
		{
			this->removeBullet(index);
		}
	}
	else
	{
		if (_pc->Downcheck(bullet.x, bullet.y, bullet.bulletImage->getFrameWidth() - 10, bullet.bulletImage->getFrameHeight()))
		{
			this->removeBullet(index);
		}
	}
	RECT tmp;
	if (IntersectRect(&tmp, &bullet.rc, &_player->getRect()) && !_player->getDamageState())
	{
		_player->setGravity(-10.f);
		_player->setDownJumpTrue();
		_player->jump();
		_player->setDamage(true);
		_player->setExpUp(-1);
		removeBullet(index);
		_player->setHp(_player->getHP() - bullet.atk);
	}
}

void boss_bullet::removeBullet(int index)
{
	SOUNDMANAGER->play("hitSound1", .5f);
	FX->play("enemy_dead", _vBullet[index].x, _vBullet[index].y, 4);
	FX->play("enemy_smoke_B", RANDOM->Range(_vBullet[index].x - 50, _vBullet[index].x + 40), RANDOM->Range(_vBullet[index].y - 40, _vBullet[index].y + 40), 2);
	FX->play("enemy_smoke_B", RANDOM->Range(_vBullet[index].x - 50, _vBullet[index].x + 40), RANDOM->Range(_vBullet[index].y - 40, _vBullet[index].y + 40), 2);
	FX->play("enemy_smoke_B", RANDOM->Range(_vBullet[index].x - 50, _vBullet[index].x + 40), RANDOM->Range(_vBullet[index].y - 40, _vBullet[index].y + 40), 2);
	FX->play("enemy_smoke_B", RANDOM->Range(_vBullet[index].x - 50, _vBullet[index].x + 40), RANDOM->Range(_vBullet[index].y - 40, _vBullet[index].y + 40), 2);
	_vBullet.erase(_vBullet.begin() + index);
}

//=============================================================
//	## bomb ## (폭탄처럼 한발씩 발사하고 생성하고 자동삭제)
//=============================================================
//HRESULT bomb::init(const char * imageName, int bulletMax, float range, bool isFrameImg)
//{
//	_imageName = imageName;
//	//총알 사거리 및 총알 갯수 초기화
//	_range = range;
//	_bulletMax = bulletMax;
//	_isFrameImg = isFrameImg;
//
//	return S_OK;
//}
//
//void bomb::release()
//{
//}
//
//void bomb::update()
//{
//	this->move();
//}
//
//void bomb::render(HDC hdc)
//{
//	_viBullet = _vBullet.begin();
//	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
//	{
//		_viBullet->bulletImage->frameRender(hdc, _viBullet->rc.left, _viBullet->rc.top, _viBullet->frameX, _viBullet->frameY);
//		
//		_viBullet->count++;
//		if (_viBullet->count % 3 == 0)
//		{
//			_viBullet->bulletImage->setFrameX(_viBullet->bulletImage->getFrameX() + 1);
//			if (_viBullet->bulletImage->getFrameX() >= _viBullet->bulletImage->getMaxFrameX())
//			{
//				_viBullet->bulletImage->setFrameX(0);
//			}
//			_viBullet->count = 0;
//		}
//	}
//}
//
//void bomb::fire(float x, float y, float angle, float speed, int frameX, int frameY)
//{
//	//총알 벡터에 담는것을 제한한다
//	if (_bulletMax < _vBullet.size() + 1) return;
//
//	//총알 구조체 선언
//	tagBullet bullet;
//	//총알구조체 초기화
//	//제로메모리, 멤셋
//	//구조체의 변수들의 값을 한번에 0으로 초기화 시켜준다
//	ZeroMemory(&bullet, sizeof(tagBullet));
//	bullet.bulletImage = new image;
//	bullet.bulletImage = IMAGEMANAGER->findImage(_imageName);
//	bullet.speed = speed;
//	bullet.angle = angle;
//	bullet.x = bullet.fireX = x;
//	bullet.y = bullet.fireY = y;
//	bullet.frameX = frameX;
//	bullet.frameY = frameY;
//	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
//		bullet.bulletImage->getFrameWidth(),
//		bullet.bulletImage->getFrameHeight());
//
//	//벡터에 담기
//	_vBullet.push_back(bullet);
//}
//
//void bomb::move()
//{
//	_viBullet = _vBullet.begin();
//	for (; _viBullet != _vBullet.end();)
//	{
//		_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
//		_viBullet->y += -sinf(_viBullet->angle) * _viBullet->speed;
//		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
//			_viBullet->bulletImage->getFrameWidth(),
//			_viBullet->bulletImage->getFrameHeight());
//	
//		//폭탄이 사거리보다 커졌을때
//		float distance = getDistance(_viBullet->fireX, _viBullet->fireY,
//			_viBullet->x, _viBullet->y);
//		if (_range < distance)
//		{
//			_viBullet->bulletImage->release();
//			SAFE_DELETE(_viBullet->bulletImage);
//			_viBullet = _vBullet.erase(_viBullet);
//		}
//		else
//		{
//			++_viBullet;
//		}
//	}
//}
////폭탄 삭제
//void bomb::removeBomb(int index)
//{
//	_vBullet.erase(_vBullet.begin() + index);
//}
