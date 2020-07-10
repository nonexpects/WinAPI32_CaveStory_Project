#pragma once
#include "gameNode.h"

//=============================================================
//	## progressBar ## (���α׷����� = ü�¹� = �ε��� ���)
//=============================================================
class progressBar : public gameNode
{
private:
	image* _progressBarFront;	//ü�¹� �� �̹���
	image* _progressBarMiddle;	//ü�¹� �� �̹���
	image* _progressBarBack;	//ü�¹� �� �̹���
	RECT _rcProgress;			//ü�¹� ��Ʈ
	float _x, _y;				//ü�¹� ��ġ��ǥ
	float _width;				//ü�¹� ���α���
	float _height;				//ü�¹� ���α���
	float _time;

	bool _isHpBar;
	float _middleWidth;

	unsigned char _middleAlpha;

public:
	HRESULT init(const char* frontImg, const char* backImg);
	HRESULT init(const char* frontImg, const char* middleImg, const char* backImg, bool isHpBar = false);
	void release();
	void update();
	void render(HDC hdc, int alpha = 255);

	//ü�¹� ��ġ �����ϱ�
	void setPos(float x, float y) { _x = x; _y = y; }
	//ü�¹� ������ �����ϱ�
	void setGauge(float maxHp, float currentHp);
	void setGauge(float maxHp, float middleGauge, float currentHp);


	void gaugeEffect(unsigned char alpha);

	progressBar() : _middleAlpha(0), _isHpBar(false) {}
	~progressBar() {}
};

