#pragma once
#include "singletonBase.h"
#include "tileNode.h"

class camera : public singletonBase<camera>
{
private:
	image* mainCam;

	RECT _rc;

	float _x;
	float _y;
	
	float* _targetX;
	float* _targetY;

	float _speed;

	int _width;
	int _height;

	int _maxWidth;
	int _maxHeight;

	int _limitH;
	int _limitW;

	bool isMaptool;

public:
	

	float getPosX() { return _x; }
	float getPosY() { return _y; }

	int getWidth() { return _width; }
	int getHeight() { return _height; }

	float getSpd() { return _speed; }
	bool getBool() { return isMaptool; }

	int getmaxWidth() { return _maxWidth; }
	int getmaxHeight() { return _maxHeight; }

	void setLimitHeight(int height) { _limitH = height; }
	void setLimitWidth(int width) { _limitW = width; }

	RECT getCamRect() { return _rc; }

	void setPosX(float x) { _x = x; }
	void setPosY(float y) { _y = y; }

	void setSpd(float speed) { _speed = speed; }
	void setBool(bool ismaptool) { isMaptool = ismaptool; }

	void setTarget(float* x, float* y) { _targetX = x; _targetY = y; }
	void setCamSize(int width, int height) { _width = width; _height = height; }
	void setMax(int maxWidth, int maxHeight) { _maxWidth = maxWidth; _maxHeight = maxHeight; }

	void setCam(float x, float y);
	void setCam(float x, float y, int camWidth, int camHeight, int maxWidth, int maxHeight);
	void setCam(float x, float y, int camWidth, int camHeight, int maxWidth, int maxHeight,
		float* targetX, float* targetY);

	HRESULT init();
	void release();
	void render(HDC hdc, HDC renderDC);
	void update();

	camera() : _x(0), _y(0), _width(0), _height(0), _maxWidth(0), _maxHeight(0), _speed(10.f), _targetX(NULL), _targetY(NULL) 
	 , _limitH (0), _limitW (0) {};
	~camera() {};
};

