#pragma once
#include "mob.h"
#include "scene.h"

#define BEHEMOTH_MAX 6
class player;
class itemManager;

class enemyManager
{
	image* _collisionMap;
	itemManager* _im;
	player* _player;

	critter* _critter;
	//vector <critter*> v_critter;

	beetle* _beetle1;
	beetle* _beetle2;
	//vector <beetle*> v_beetle;

	basu* _basu;
	//vector <basu*> v_basu;
	missile* e_missile;

	behemoth* _behemoth[BEHEMOTH_MAX];
	//vector <behemoth*> v_behemoth;

	basil* _basil;
	//vector <basil*> v_basil;

	boss* _boss;
	bird* _bird;

	vector<enemy*> allEnemy;

	RECT tmp;
	
	int _birdCounter;
	float _bossDeadCount, _birdTime;
	bool bossOn, birdOn;

public:
	void setPlayer(player* player) { _player = player; }
	void setIM(itemManager* im) { _im = im; }

	//vector <critter*> getCritter() { return v_critter; }
	//vector <beetle*> getBeetle() { return v_beetle; }
	//vector <basu*> getBasu() { return v_basu; }
	//vector <behemoth*> getBehemoth() { return v_behemoth; }
	//vector <basil*> getBasil() { return v_basil; }

	vector<enemy*> getEnemies() { return allEnemy; }
	boss* getBoss() { return _boss; }

	missile* getMissile() { return e_missile; }

	void eraseEnemy(int index);

	void setBehemoth(int x, int y);
	void setBasil(int x, int y);
	void setBasu(int x, int y);
	void setBeetle(int x, int y, BEETLETYPE type);
	void setCritter(int x, int y);
	void setBird(int x, int y, int dir);

	bool isBossOn() { return bossOn; }

	HRESULT init();
	HRESULT setScene(int i);
	void release();
	void update();
	void render(HDC hdc);

	enemyManager() {}
	~enemyManager() {}
};

