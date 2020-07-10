#pragma once
#include "singletonBase.h"

class effect;

class effectManager : public singletonBase<effectManager>
{
	typedef vector<effect*> effects;
	typedef vector<effect*>::iterator i_effects;

	typedef map<string, effects> fxList;
	typedef map<string, effects>::iterator i_fxList;
	
	vector<fxList> v_allFx;
	vector<fxList>::iterator vi_allFx;

private:
	float numberX, numberY, popTime, popmaxTime;
	float endY;
	int storeNum;
	bool popOn;

public:
	HRESULT init();
	void release();
	void update();
	void render(string fxName, HDC hdc);
	void play(string fxName, float x, float y, int count, bool loop = false, float time = 0.f, float angle = 0.f, bool movedir = false);
	void addEffect(string fxName, const char* imageName, float time, int buffer, int startFrameX = 0, int startFrameY = 0, int maxframeX= -1, float speed = 1.f, bool isTrail = false);
	void offFX(string fxName);

	void numberPop(float x, float y, int num, float time);
	void popRender(HDC hdc);

	bool getIsRunning(string fxName);

	effectManager() : numberX(0.f), endY(0.f), numberY(0.f), popTime(0.f), storeNum(0), popOn(false) {}
	~effectManager() {}
};

