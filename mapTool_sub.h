#pragma once
#include "gameNode.h"
#include "mapTool_main.h"
#include "tileNode.h"
class mapTool_main;

#define TOTAL_BUTTON 15

class mapTool_sub : public gameNode
{
	mapTool_main* _main;
	tagSampleTile _collisionTile[COLLI_TILEY][COLLI_TILEX];
	tagSampleTile _sampleTile[SAMPLE_TILEY][SAMPLE_TILEX];
	//======================================= R E C T =========================================//
	RECT _rcUIbg;
	RECT _rcArrowR, _rcArrowL, _rcArrowU, _rcArrowD;
	RECT _rcSave, _rcLoad, _rcReset, _rcBG, _rcTerrain, _rcObj, _rcEnemy, _rcCollision;
	RECT _rcbgTile;
	RECT _rcBgButton[3];
	RECT _rcSample;

	RECT _rcSub;
	RECT _rcX;

	//========================================================================================//
	//드래그용 
	tagDragIndex dragIndex;
	
	bool tileDragOn;						// 타일 드래그 ON
	bool sampleDragOn;						// 샘플타일 드래그 ON
	bool sampleDragCheck;					// 샘플 타일 드래그 범위 그리는용
	POINT d_mouse;							// 드래그 RECT용 mouse 좌표
	vector<tagSampleTile> _dragSamples;		// 드래그한 샘플 타일 이미지 좌표값 저장하는 벡터
	RECT _rcDragSample;						// 드래그용 렉트 (샘플 타일 드래그하면 이 렉트가 마우스 좌표에 찍힘)
	RECT _rcDragTile;						// 드래그용 렉트 (샘플 타일 드래그하면 이 렉트가 마우스 좌표에 찍힘)
	RECT tmp;
	//========================================================================================//

	bool ui_frame[TOTAL_BUTTON] = {};

	bool _dragsubUIOn;
	int _dX, _dY;		// 서브창 드래그용
	int _sampleX, _sampleY;
	int _alpha, _salpha;

	char str[100];

 public:
	HRESULT init();
	void release();
	void update();
	void render();

	// 키 입력
	void input();

	// UI 이미지 렉트 세팅용 
	void setupUI();
	void renderUI();

	//드래그용
	void drag();
	void dragSampleRender();

	void reset_ui_frame();

	void popUpSubUi();

	// 상호참조용
	void setMain(mapTool_main* main) { _main = main; }

	// UI 배경렉트 (입력제한용)
	RECT getbgRect() { return _rcUIbg; }
	RECT getsubRect() { return _rcSub; }

	mapTool_sub() {}
	~mapTool_sub() {}
};

