#pragma once
#include "singletonBase.h"

class dialog : public singletonBase<dialog>
{
	image* _dialogImg;
	image* _choiceImg;
	image* _choiceArrowImg;
	float _x, _y;
	int _width, _height;
	RECT _rc;
	RECT _choicerc;
	RECT _arrowrc;

	float _scale;

	bool _choice;

	bool dialogOn;
	bool d_fill, d_save, d_dead, d_teleport, d_bossOn;
	bool _gameClear;

	float _time, _maxTime;


public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void SaveDialog();
	void DeadDialog();
	void FillDialog();
	void gameClear();
	//void BossFight();
	void teleport(float maxtime);

	bool isDialogOn() { return dialogOn; }
	bool isTeleportOn() { return d_teleport; }

	float getTime() { return _time; }

	void setTimeStop(bool stop) { dialogOn = stop; }
	void setBossDied(bool isdied) { d_bossOn = isdied; }

	dialog() : _gameClear(false), d_fill(false), d_bossOn(false), dialogOn(false), d_save(false), d_dead(false), d_teleport(false), _time(0.f), _maxTime(0.f), _choice(false) {}
	~dialog() {}
};

