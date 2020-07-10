#pragma once
#include "singletonBase.h"
#include "gameNode.h"
#include "bullet.h"

class effect : public gameNode
{
protected:
	float _x;						
	float _y;
	float _angle, _gravity;
	int _frameX, _frameY;
	int _startframeX, _startframeY;
	int _maxframeX;

	float _speed;
	RECT _rc;

	image* _fxImage;		   //이펙트 이미지
	bool _isRunning;
	bool _isLoop;
	bool _isTrail;
	float _time, _maxTime;			   //이펙트 경과시간
	int _count, _frameCount;

	bool _movedir;

	int tmp;
	//float _delay;

public:
	HRESULT init(image* image, float time, int startFrameX, int startFrameY, int maxframeX, float speed, bool isTrail= false);
	void release();
	void updateFX();
	void render(HDC hdc);
	void animation();
	void startEffect(float x, float y, int count, bool loop, float time, float angle, bool movedir);
	void FXoff();
	//void FXoff();

	bool IsRunning() { return _isRunning; }
	bool IsTrail() { return _isTrail; }
	int getCount() { return _frameCount; }
	float getMaxTime() { return _maxTime; }
	float getAngle() { return _angle; }
	void setIsTrail(bool istrail) { _isTrail = istrail; }
	void setCount(int count) { _count = count; }
	void setAngle(float angle) { _angle = angle; }
	

	float getPosX() { return _x; }
	float getPosY() { return _y; }
	void setPosX(int x) { _x = x; }
	void setPosY(int y) { _y = y; }
	float getGravity() { return _gravity; }
	void setGravity(float gravity) { _gravity = gravity; }
	
	effect() : _speed(1.f), tmp(0), _x(0), _y(0), _frameX(-1), _frameY(0), _startframeX(0), _startframeY(0), _isLoop(false), _isTrail(false), _movedir(false),
		_rc(), _fxImage(nullptr), _isRunning(false), _time(0.f) , _angle(0.f), _gravity(0) {}
	~effect() {}
};

