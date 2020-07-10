#pragma once
#include "scene.h"

enum START_MENU
{
	MENU_STARTMODE,
	MENU_MAPTOOLMODE,
	MENU_GAMEOPTIONS,
	MENU_QUIT,
};

class startScene : public scene
{
private:

	RECT logo_rc;
	image* _bg;
	image* _logo;
	START_MENU _state;

	bool loopSoundOn;

	int _menu;

	int _loop1, _loop2, _loop3, _loop4;	// ·çÇÁ¿ë
	int _count, _index;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void animation();

	startScene() {}
	~startScene() {}
};

