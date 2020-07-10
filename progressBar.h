#pragma once
#include "gameNode.h"

//=============================================================
//	## progressBar ## (프로그래스바 = 체력바 = 로딩바 등등)
//=============================================================
class progressBar : public gameNode
{
private:
	image* _progressBarFront;	//체력바 앞 이미지
	image* _progressBarMiddle;	//체력바 뒤 이미지
	image* _progressBarBack;	//체력바 뒤 이미지
	RECT _rcProgress;			//체력바 렉트
	float _x, _y;				//체력바 위치좌표
	float _width;				//체력바 가로길이
	float _height;				//체력바 세로길이
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

	//체력바 위치 세팅하기
	void setPos(float x, float y) { _x = x; _y = y; }
	//체력바 게이지 세팅하기
	void setGauge(float maxHp, float currentHp);
	void setGauge(float maxHp, float middleGauge, float currentHp);


	void gaugeEffect(unsigned char alpha);

	progressBar() : _middleAlpha(0), _isHpBar(false) {}
	~progressBar() {}
};

