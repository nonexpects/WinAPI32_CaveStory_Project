#pragma once

struct tagSensor
{
	RECT rc;
	float x, y;
	bool isJump;
	bool isTouch;
};

class pixelCollision
{
	tagSensor U, D, L, R;
	image* _collisionMap;

public:
	HRESULT init(image* collisionMap);
	void release();

	void collisonCheck(float x, float y, float width, float height, bool isJumpUp);
	bool Upcheck(float x, float y, float width, float height);
	bool Downcheck(float x, float y, float width, float height);
	bool Rightcheck(float x, float y, float width, float height);
	bool Leftcheck(float x, float y, float width, float height);
	void sensorCheck(HDC hdc, tagSensor sensor);

	tagSensor getUpSensor() { return U; }
	tagSensor getDownSensor() { return D; }
	tagSensor getLeftSensor() { return L; }
	tagSensor getRightSensor() { return R; }

	void setDownSensorJump(bool isJump) { D.isJump = isJump; }

	pixelCollision() {}
	~pixelCollision() {}
};

