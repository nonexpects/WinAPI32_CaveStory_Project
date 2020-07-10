#pragma once
#include "gameNode.h"
#include "itemManager.h"
#include "enemyManager.h"
#include "tileNode.h"
#include "camera.h"
#include "player.h"
#include "ui.h"

enum SCENES
{
	SCENE_HOUSE,
	SCENE_MIMIGA,
	SCENE_EGG,
	SCENE_WHITE
};

class scene : public gameNode
{
protected:

	string _mapName;
	string _name;

	SCENES _sceneName;
	float startX, startY;

	itemManager* _im;
	enemyManager* _em;

	player* _player;

	RECT door;
	RECT tmp;
	char str[100];

	tagTile _mapTile[MAP_TILEY][MAP_TILEX];		// 인게임 화면에 사용되는 타일

	ui* _ui;

	image* collisionMap;

	bool loopSoundOn;

public:
	virtual HRESULT init();
	virtual HRESULT setScene(string mapName, SCENES sceneName, float startX, float startY);
	virtual void release();
	virtual void update();
	virtual void render();

	void loadSaveData();
	void load();
	void mapRender(HDC hdc);
	void playerDataLoad();
	void saveDataLoad();
	//HDC getCollDC() { return _collDC->getMemDC(); }

	scene() : loopSoundOn(false) {}
	virtual ~scene() {}
};

