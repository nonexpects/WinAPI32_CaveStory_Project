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
	//�巡�׿� 
	tagDragIndex dragIndex;
	
	bool tileDragOn;						// Ÿ�� �巡�� ON
	bool sampleDragOn;						// ����Ÿ�� �巡�� ON
	bool sampleDragCheck;					// ���� Ÿ�� �巡�� ���� �׸��¿�
	POINT d_mouse;							// �巡�� RECT�� mouse ��ǥ
	vector<tagSampleTile> _dragSamples;		// �巡���� ���� Ÿ�� �̹��� ��ǥ�� �����ϴ� ����
	RECT _rcDragSample;						// �巡�׿� ��Ʈ (���� Ÿ�� �巡���ϸ� �� ��Ʈ�� ���콺 ��ǥ�� ����)
	RECT _rcDragTile;						// �巡�׿� ��Ʈ (���� Ÿ�� �巡���ϸ� �� ��Ʈ�� ���콺 ��ǥ�� ����)
	RECT tmp;
	//========================================================================================//

	bool ui_frame[TOTAL_BUTTON] = {};

	bool _dragsubUIOn;
	int _dX, _dY;		// ����â �巡�׿�
	int _sampleX, _sampleY;
	int _alpha, _salpha;

	char str[100];

 public:
	HRESULT init();
	void release();
	void update();
	void render();

	// Ű �Է�
	void input();

	// UI �̹��� ��Ʈ ���ÿ� 
	void setupUI();
	void renderUI();

	//�巡�׿�
	void drag();
	void dragSampleRender();

	void reset_ui_frame();

	void popUpSubUi();

	// ��ȣ������
	void setMain(mapTool_main* main) { _main = main; }

	// UI ��淺Ʈ (�Է����ѿ�)
	RECT getbgRect() { return _rcUIbg; }
	RECT getsubRect() { return _rcSub; }

	mapTool_sub() {}
	~mapTool_sub() {}
};

