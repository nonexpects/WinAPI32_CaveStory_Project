#pragma once
#include "scene.h"
#include "fixed_item.h"

class bossScene : public scene
{
	progressBar* _bossBar;
	RECT _bossBarbg;
	saver* _saver;

	int prevBossHp;

	bool _bossOn;
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void bossMapRender(HDC hdc);

	bossScene() {}
	~bossScene() {}
};

