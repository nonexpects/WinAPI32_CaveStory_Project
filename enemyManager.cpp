#include "stdafx.h"
#include "enemyManager.h"
#include "itemManager.h"

void enemyManager::eraseEnemy(int index)
{
	allEnemy.erase(allEnemy.begin() + index);
}

void enemyManager::setBehemoth(int x, int y)
{
	behemoth* tmp = new behemoth;
	tmp->init(x, y, _player);
	allEnemy.push_back(tmp);
}

void enemyManager::setBasil(int x, int y)
{
	basil* tmp = new basil;
	tmp->init(x, y, _player);
	allEnemy.push_back(tmp);
}

void enemyManager::setBasu(int x, int y)
{
	basu* tmp = new basu;
	tmp->init(x, y, _player);
	allEnemy.push_back(tmp);
}

void enemyManager::setBeetle(int x, int y, BEETLETYPE type)
{
	beetle* tmp = new beetle;
	tmp->init(x, y, type, _player);
	allEnemy.push_back(tmp);
}

void enemyManager::setCritter(int x, int y)
{
	critter* tmp = new critter;
	tmp->init(x, y, _player);
	allEnemy.push_back(tmp);
}

void enemyManager::setBird(int x, int y, int dir)
{
	bird* tmp = new bird;
	tmp->init(x, y, dir, _player);
	allEnemy.push_back(tmp);
	_birdCounter++;
}

HRESULT enemyManager::init()
{
	_bossDeadCount = _birdTime =  0.f;
	bossOn = birdOn = false;
	_birdCounter = 0;

	FX->addEffect("enemy_dead", "fx_dead", 3, 10);
	FX->addEffect("enemy_dead_B", "fx_dead_B", 3, 10);
	FX->addEffect("enemy_smoke", "fx_smoke1", 3, 10);
	FX->addEffect("enemy_smoke_B", "fx_smoke1_B", 3, 4);
	FX->addEffect("damaged", "fx_damaged", 1, 5, 0, 0, -1, 7.f);
	FX->addEffect("fade_L", "boss_fade_L", .5f, 2, 0, 0, -1, 2.f);
	FX->addEffect("fade_R", "boss_fade_R", .5f, 2, 0, 0, -1, 2.f);

	return S_OK;
}

HRESULT enemyManager::setScene(int i)
{

	switch (i)
	{
	case 2:
		
		setBeetle(680, 480, INPLACE);
		setBeetle(8730, 544, INPLACE);
		setBeetle(9760, 608, INPLACE);
		setBeetle(9760, 736, INPLACE);
		setBeetle(10788, 736, INPLACE);
		setBeetle(11808, 480, INPLACE);
		setBeetle(13018, 288, INPLACE);
		setBeetle(12826, 480, INPLACE);
		setBeetle(12826, 608, INPLACE);
		setBeetle(12957, 736, INPLACE);
		setBeetle(15005, 224, INPLACE);
		setBeetle(15140, 352, INPLACE);
		setBeetle(14888, 672, INPLACE);

		setBeetle(8900, 100, FLY);
		setBeetle(9400, 100, FLY);
		setBeetle(10000, 100, FLY);
		setBeetle(11650, 100, FLY);
		setBeetle(11880, 200, FLY);
		setBeetle(14945, 100, FLY);
		setBeetle(14945, 400, FLY);
		setBeetle(15135, 100, FLY);
		setBeetle(16150, 100, FLY);

		//테스트용
		setBasu(12150, 100);
		
		setBasu(13680, 216);
		setBasu(14810, 280);
		setBasu(15515, 224);
		setBasu(16135, 300);
		
		setBehemoth(793, 450);
		setBehemoth(1700, 450);
		setBehemoth(1800, 450);
		setBehemoth(3850, 450);
		setBehemoth(4750, 514);
		setBehemoth(4890, 514);
		setBehemoth(5830, 450);
		setBehemoth(16130, 450);   

		setCritter(1335, 416);
		setCritter(2235, 416);
		setCritter(2370, 416);
		setCritter(2694, 480);
		setCritter(2890, 480);
		setCritter(2980, 480);
		setCritter(3677, 480);
		setCritter(3740, 288);
		setCritter(3930, 224);
		setCritter(3865, 480);
		setCritter(5785, 480);
		setCritter(6000, 480);
		setCritter(6180, 416);
		setCritter(10909, 160);
		setCritter(10997, 800);
		setCritter(11168, 288);
		setCritter(13730, 416);
		setCritter(13917, 480);
		setCritter(16510, 416);
		setCritter(16630, 416);
		setCritter(16760, 416);
		setCritter(17050, 800);

		setBasil(400, 928);
		bossOn = false;
		break;
	case 3:
		_boss = new boss;
		_boss->init(1823, 258, _player);
		bossOn = true;
		allEnemy.push_back(_boss);
		break;
	}

	return S_OK;
}

void enemyManager::release()
{
	for (int i = 0; i < allEnemy.size(); i++)
	{
		allEnemy[i]->release();
		SAFE_DELETE(allEnemy[i]);
	}
}

void enemyManager::update()
{
	//e_missile->update();

	if (allEnemy.empty()) return;
	for (int i = 0; i < allEnemy.size(); i++)
	{
		if (IntersectRect(&tmp, &CAMERA->getCamRect(), &allEnemy[i]->getRect()) && allEnemy[i]->getEnemyState() == ES_NULL)
		{
			if (allEnemy[i]->getEnemyType() != ENEMY_BOSS1)
			{
				allEnemy[i]->setEnemyState(ES_SPAWN);
			}
		}
	}

	for (int i = 0; i < allEnemy.size(); i++)
	{
		allEnemy[i]->update();
		if (allEnemy[i]->getEnemyState() == ES_DEAD && allEnemy[i]->getEnemyType() != ENEMY_BOSS1)
		{
			if (allEnemy[i]->getEnemyType() == ENEMY_BIRD)
			{
				_birdCounter--;
			}
			int itemNum = RANDOM->Range(ITEM_COUNT);//;
			if (itemNum == 1)
			{
				_im->addItem(1, allEnemy[i]->getPosX(), allEnemy[i]->getPosY());//RANDOM->Range(ITEM_COUNT)
				_im->addItem(1, allEnemy[i]->getPosX(), allEnemy[i]->getPosY());//RANDOM->Range(ITEM_COUNT)
				_im->addItem(1, allEnemy[i]->getPosX(), allEnemy[i]->getPosY());//RANDOM->Range(ITEM_COUNT)
			}
			else
			{
				_im->addItem(itemNum, allEnemy[i]->getPosX(), allEnemy[i]->getPosY());//RANDOM->Range(ITEM_COUNT)
			}
			eraseEnemy(i);
			break;
		}
		else if (allEnemy[i]->getEnemyState() == ES_DEAD && allEnemy[i]->getEnemyType() == ENEMY_BOSS1)
		{
			_bossDeadCount += TIMEMANAGER->getElapedTime();

			if (_bossDeadCount > 5.f)
			{
				eraseEnemy(i);
				break;
			}
		}

		if (IntersectRect(&tmp, &allEnemy[i]->getRect(), &_player->getRect()) && !_player->getDamageState())
		{
			_player->setGravity(-10.f);
			_player->setDownJumpTrue();
			_player->jump();
			_player->setDamage(true);
			_player->setExpUp(-1);

			if (allEnemy[i]->getEnemyType() == ENEMY_MOB2)
			{
				_player->setHp(_player->getHP() - 5);
			}
			else if (allEnemy[i]->getEnemyType() == ENEMY_FLYING_MOB2)
			{
				_player->setHp(_player->getHP() - 4);
			}
			else if (allEnemy[i]->getEnemyType() == ENEMY_MOB3)
			{
				_player->setHp(_player->getHP() - 50);
			}
			else
			{
				_player->setHp(_player->getHP() - 2);
			}
		}
	}

	if (!_birdCounter)
	{
		birdOn = false;
	}

	if (!birdOn) _birdTime += TIMEMANAGER->getElapedTime();

	if (bossOn && _birdTime > 5.f && _boss->getEnemyState() != ES_TELEPORTED && _boss->getEnemyState() != ES_DEAD)
	{
		if (_boss->getHp() && _boss->getHp() > 150)
		{
			birdOn = true;
			setBird(_boss->getPosX(), _boss->getPosY(), 1);
			//setBird(_boss->getPosX(), _boss->getPosY(), 2);
			_birdTime = 0.f;
		}
		else if (_boss->getHp() <= 150)
		{
			birdOn = true;
			setBird(_boss->getPosX(), _boss->getPosY(), 1);
			setBird(_boss->getPosX(), _boss->getPosY(), 2);
			//setBird(_boss->getPosX(), _boss->getPosY(), 3);
			//setBird(_boss->getPosX(), _boss->getPosY(), 4);
			_birdTime = 0.f;
		}
	}
	
	_im->update();
}

void enemyManager::render(HDC hdc)
{
	//e_missile->render();
	
	for (int i = 0; i < allEnemy.size(); i++)
	{
		if (IntersectRect(&tmp, &CAMERA->getCamRect(), &allEnemy[i]->getRect()) && allEnemy[i]->getEnemyType() != ENEMY_BOSS1)
		{
			allEnemy[i]->render(hdc);
		}

		if (bossOn)
		{
			_boss->render(hdc);
		}
	}
	_im->render(hdc);

	FX->render("enemy_dead", hdc);
	FX->render("enemy_dead_B", hdc);
	FX->render("enemy_smoke", hdc);
	FX->render("enemy_smoke_B", hdc);
	FX->render("enemy_smoke_B", hdc);
	FX->render("damaged", hdc);
	FX->render("fade_L", hdc);
	FX->render("fade_R", hdc);
}