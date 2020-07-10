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

	//�ε��̹��� �Լ�(�̰��� �̹����� ���� �־��)
	void loadingImage();
	//�ε����� �Լ�(�̰��� ���带 ���� �־��)
	void loadingSound();

	loadingScene() {}
	~loadingScene() {}
};

