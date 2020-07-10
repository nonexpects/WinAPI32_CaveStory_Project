#include "stdafx.h"
#include "itemManager.h"
#include "player.h"

HRESULT itemManager::init()
{
	return S_OK;
}

void itemManager::release()
{
	for (int i = 0; i < items.size(); i++)
	{
		items[i]->release();
		SAFE_DELETE(items[i]);
	}
}

void itemManager::update()
{

	for (int i = 0; i < items.size(); i++)
	{
		items[i]->update();

		if (IntersectRect(&tmp, &_player->getRect(), &items[i]->getRect()))
		{
			SOUNDMANAGER->play("getExp", .5f);
			if (items[i]->getType() == ITEM_EXP)
			{
				_player->setExpUp(3);
			}
			if (items[i]->getType() == ITEM_HP_1)
			{
				_player->setHp(_player->getHP() + 1);
			}
			if (items[i]->getType() == ITEM_HP_3)
			{
				_player->setHp(_player->getHP() + 3);
			}
			if (items[i]->getType() == ITEM_MISSILE_1)
			{
				_player->getLancher()->getBullet()->addBullet(1);
				_player->getLancher()->setCurrentBullet(_player->getLancher()->getcurrentBullet() + 1);
			}
			if (items[i]->getType() == ITEM_MISSILE_3)
			{
				_player->getLancher()->getBullet()->addBullet(3);
				_player->getLancher()->setCurrentBullet(_player->getLancher()->getcurrentBullet() + 3);
			}
			eraseItem(i);
			break;
		}
		else
		{
			if (items[i]->timeOver())
			{
				eraseItem(i);
			}
		}
		
	}


}

void itemManager::render(HDC hdc)
{
	for (int i = 0; i < items.size(); i++)
	{
		items[i]->render(hdc);
	}
}

void itemManager::addItem(int type, float x, float y)
{
	switch (type)
	{
	case ITEM_NULL:
		break;
	case ITEM_EXP:
		exp = new i_exp;
		exp->init(x, y, _player->getCollisionMap());
		items.push_back(exp);
		break;
	case ITEM_HP_1:
		hp_1 = new i_hp_1;
		hp_1->init(x, y);
		items.push_back(hp_1);
		break;
	case ITEM_HP_3:
		hp_3 = new i_hp_3;
		hp_3->init(x, y);
		items.push_back(hp_3);
		break;
	case ITEM_MISSILE_1:
		missile_1 = new i_missile_1;
		missile_1->init(x, y);
		items.push_back(missile_1);
		break;
	case ITEM_MISSILE_3:
		missile_3 = new i_missile_3;
		missile_3->init(x, y);
		items.push_back(missile_3);
		break;
	}
}

void itemManager::eraseItem(int index)
{
	items.erase(items.begin() + index);
}
