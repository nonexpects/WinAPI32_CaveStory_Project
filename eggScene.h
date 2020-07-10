#pragma once
#include "scene.h"
#include "fixed_item.h"

class eggScene : public scene
{
	teleporter* _teleporter;
	filler* _filler;
	filler* _filler_b;
	saver* _saver;

	RECT _doorBossMap;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void eggMapRender(HDC hdc);

	eggScene() {}
	~eggScene() {}
};

