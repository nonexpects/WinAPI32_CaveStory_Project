#pragma once
#include "scene.h"
#include "mapTool_main.h"
#include "mapTool_sub.h"

class mapToolScene : public scene
{
	bool isMaptoolOn;
	mapTool_main* _mapToolMain;
	mapTool_sub* _mapToolUI;
public:
	
	HRESULT init();
	void release();
	void update();
	void render();

	mapToolScene() : isMaptoolOn(false) {}
	~mapToolScene() {}
};

