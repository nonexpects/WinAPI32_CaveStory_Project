#pragma once
#include "scene.h"
class mimigaScene : public scene
{
	RECT _houseDoor;
public:
	virtual HRESULT init();
	void release();
	void update();
	void render();
};

