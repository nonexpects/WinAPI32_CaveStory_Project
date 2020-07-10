#pragma once
#include "loading.h"
#include "scene.h"

class loadingScene : public scene
{
	loading* _loading;
	int _count;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	//로딩이미지 함수(이곳에 이미지를 전부 넣어라)
	void loadingImage();
	//로딩사운드 함수(이곳에 사운드를 전부 넣어라)
	void loadingSound();

	loadingScene() {}
	~loadingScene() {}
};

