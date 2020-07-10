#pragma once
#include "scene.h"
#include "fixed_item.h"

class houseScene : public scene
{
private:
	filler* _filler;
	saver* _saver;
	computer* _computer;
	teleporter* _teleporter;

	RECT _doorMimiga;
	RECT _doorEgg;
	RECT _water;
	RECT tmp;
	char str[100];


public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void teleportToEgg();

	houseScene() {}
	~houseScene() {}
};

