#pragma once
#include "item_all.h"

class player;

class itemManager
{
	player* _player;

	i_exp* exp;
	i_hp_1* hp_1;
	i_hp_3* hp_3;
	i_missile_1* missile_1;
	i_missile_3* missile_3;

	vector<item*> items;

	RECT tmp;

public:
	void setPlayer(player* player) { _player = player; }

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void addItem(int type, float x, float y);


	void eraseItem(int index);

	itemManager() {}
	~ itemManager() {}
};

