#pragma once
#include "gameNode.h"
#include "mapTool_sub.h"
#include <commdlg.h>

//==========================================================================
//#######################
//#### MAPTOOL MAIN #####
//#######################
//==========================================================================

class mapTool_sub;

class mapTool_main : public gameNode
{
	mapTool_sub* _ui;
	BG _bgType;
	tagTile _mapTile[MAP_TILEY][MAP_TILEX];
	tagCurrentTile _currentTile;

	MAPTOOL_MENU _menu;
	CTRL _ctrlSelect;
	CTRL _currentCtrl;
	TERRAIN _terrainSelect;

	bool tileDragOn;						//Ÿ�� �巡�� ON
	POINT d_mouse;							// �巡�� RECT�� mouse ��ǥ
	RECT _rcDragTile;						// �巡�׿� ��Ʈ (���� Ÿ�� �巡���ϸ� �� ��Ʈ�� ���콺 ��ǥ�� ����)

	//========================================================================================//
	int _sampleX, _sampleY;
	int _alpha;

	bool eraseOn;

	char str[100];
	POINT pt;
	RECT tmp;

public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void mapToolSetup();

	// ����, ������Ʈ ����
	TERRAIN terrainSelect(int frameX, int frameY);
	OBJECT objectSelect(int frameX, int frameY);
	BG bgSelect(int frameX, int frameY);
	CTRL getCTRL() { return _ctrlSelect; }

	void save();
	void load();
	void reset();

	void drag();
	void setMap(tagSampleTile (*sampleTile)[SAMPLE_TILEX], vector<tagSampleTile> drag, tagDragIndex index);
	void setMap(tagSampleTile(*sampleTile)[COLLI_TILEX], vector<tagSampleTile> drag, tagDragIndex index);
	void setBG(BG bgType);
	void setCTRL(CTRL ctrl) { _ctrlSelect = ctrl; }
	void setUI(mapTool_sub* ui) { _ui = ui; }

	void input();

	mapTool_main() {}
	~mapTool_main() {}
};

