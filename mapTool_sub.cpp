#include "stdafx.h"
#include "mapTool_sub.h"

HRESULT mapTool_sub::init()
{
	this->setupUI();
	tileDragOn = sampleDragOn = sampleDragCheck = _dragsubUIOn = false;

	_sampleX = _sampleY = _salpha = _alpha = 0;

	// 드래그 구조체 초기화
	ZeroMemory(&_dragSamples, sizeof(tagSampleTile));
	ZeroMemory(&dragIndex, sizeof(tagDragIndex));

	return S_OK;
}

void mapTool_sub::release()
{
}

void mapTool_sub::update()
{
	this->input();

	if (PtInRect(&_rcUIbg, _ptMouse) || PtInRect(&_rcSub, _ptMouse))
	{
		this->drag();
	}

	_rcX = RectMake(_rcSub.right - 20, _rcSub.top, 20, 20);

	if (_main->getCTRL() != CTRL_SAVE || _main->getCTRL() != CTRL_LOAD)
	{
		// 마우스 왼클릭으로 타일맵 세팅
		if (INPUT->GetKey(VK_LBUTTON))
		{
			if (_main->getCTRL() == CTRL_COLLISION)
			{
				_main->setMap(_collisionTile, _dragSamples, dragIndex);
			}
			else
			{
				_main->setMap(_sampleTile, _dragSamples, dragIndex);
			}
		}

	}
	
	// 샘플 타일 RECT 초기화
	for (int i = 0; i < TILEMAPSIZEY; i++)
	{
		for (int j = 0; j < TILEMAPSIZEX; j++)
		{
			_sampleTile[i][j].rc = RectMake(_rcSample.left + 10 + j * TILESIZE, _rcSample.top + 50 + i * TILESIZE, TILESIZE, TILESIZE);
			_sampleTile[i][j].terrainFrameX = _sampleX + j;
			_sampleTile[i][j].terrainFrameY = _sampleY + i;
		}
	}
	if (_main->getCTRL() == CTRL_COLLISION)
	{
		for (int i = 0; i < COLLI_TILEY; i++)
		{
			for (int j = 0; j < COLLI_TILEX; j++)
			{
				_collisionTile[i][j].rc = RectMake(_rcSub.left + 10 + j * TILESIZE, _rcSub.top + 10 + i * TILESIZE, TILESIZE, TILESIZE);
				_collisionTile[i][j].terrainFrameX = j;
				_collisionTile[i][j].terrainFrameY = i;
			}
		}
	}
}

void mapTool_sub::render()
{
	//============================= U I =================================//
	this->renderUI();

	IMAGEMANAGER->render("sampleTileMap", getMemDC(), _rcSample.left + 10, _rcSample.top + 50, TILESIZE * _sampleX, TILESIZE * _sampleY, 4 * TILESIZE, 6 * TILESIZE);
	
	if (_main->getCTRL() == CTRL_COLLISION || _main->getCTRL() == CTRL_ENEMY)
	{
		IMAGEMANAGER->findImage("bg_maptool_subUI")->render(getMemDC(), _rcSub.left, _rcSub.top);
		IMAGEMANAGER->findImage("collisionMap")->render(getMemDC(), _rcSub.left + 10, _rcSub.top + 10);
		IMAGEMANAGER->findImage("bg_maptool_subUI_X")->render(getMemDC(), _rcX.left, _rcX.top);
	}

	this->dragSampleRender();

	// 드래그 관련
	if (tileDragOn) FrameRect(getMemDC(), _rcDragTile, RGB(0, 0, 255));

	sprintf(str, "%d , %d", d_mouse.x, d_mouse.y);
	TextOut(getMemDC(), 0, 60, str, strlen(str));

}

void mapTool_sub::setupUI()
{
	//=================================================================================================================//

	_alpha = 255;
	_rcUIbg = RectMake(WINSIZEX - 300, 0, 300, WINSIZEY);
	_rcSave = RectMake(WINSIZEX - 260, 80, 140, 40);
	_rcLoad = RectMake(WINSIZEX - 140, 80, 140, 40);
	_rcReset = RectMake(WINSIZEX - 260, 130, 100, 40);
	_rcBG = RectMake(WINSIZEX - 140, 130, 100, 40);
	_rcTerrain = RectMake(WINSIZEX - 260, 200, 100, 40);
	_rcObj = RectMake(WINSIZEX - 140, 200, 100, 40);
	_rcEnemy = RectMake(WINSIZEX - 260, 250, 100, 40);
	_rcCollision = RectMake(WINSIZEX - 140, 250, 100, 40);
	_rcbgTile = RectMake(WINSIZEX - 290, 310, 280, 128);

	_rcSub = RectMake(0, 0, 0, 0);
	
	for (int i = 0; i < 3; i++)
	{
		_rcBgButton[i] = RectMakeCenter(WINSIZEX - 250 + (100 * i), 40, 32, 32);
	}

	_rcSample = RectMake(WINSIZEX - 290, 500, 280, 450);

	_rcArrowL = RectMake(_rcSample.left + 20, _rcSample.top + 10, 32, 32);
	_rcArrowR = RectMake(_rcSample.right - 50, _rcSample.top + 10, 32, 32);
	_rcArrowU = RectMake(_rcSample.left + 100, _rcSample.top + 10, 32, 32);
	_rcArrowD = RectMake(_rcSample.right - 130, _rcSample.top + 10, 32, 32);
}

void mapTool_sub::renderUI()
{
	IMAGEMANAGER->findImage("bg_maptool_UI")->render(getMemDC(), WINSIZEX - 300, 0);

	// 맵툴 버튼 UI
	IMAGEMANAGER->findImage("maptool_ui_save")->frameRender(getMemDC(), _rcSave.left, _rcSave.top, ui_frame[0], 0);
	IMAGEMANAGER->findImage("maptool_ui_load")->frameRender(getMemDC(), _rcLoad.left, _rcLoad.top, ui_frame[1], 0);
	IMAGEMANAGER->findImage("maptool_ui_reset")->frameRender(getMemDC(), _rcReset.left, _rcReset.top, ui_frame[2], 0);
	IMAGEMANAGER->findImage("maptool_ui_bgSelect")->frameRender(getMemDC(), _rcBG.left, _rcBG.top, ui_frame[3], 0);
	IMAGEMANAGER->findImage("maptool_ui_terrain")->frameRender(getMemDC(), _rcTerrain.left, _rcTerrain.top, ui_frame[4], 0);
	IMAGEMANAGER->findImage("maptool_ui_object")->frameRender(getMemDC(), _rcObj.left, _rcObj.top, ui_frame[5], 0);
	IMAGEMANAGER->findImage("maptool_ui_enemy")->frameRender(getMemDC(), _rcEnemy.left, _rcEnemy.top, ui_frame[6], 0);
	IMAGEMANAGER->findImage("maptool_ui_collision")->frameRender(getMemDC(), _rcCollision.left, _rcCollision.top, ui_frame[7], 0);

	IMAGEMANAGER->findImage("bg_maptool_sample_UI")->render(getMemDC(), _rcSample.left, _rcSample.top);

	IMAGEMANAGER->findImage("arrow_left")->alphaRender(getMemDC(), _rcArrowL.left, _rcArrowL.top, _alpha);
	IMAGEMANAGER->findImage("arrow_right")->alphaRender(getMemDC(), _rcArrowR.left, _rcArrowR.top, _alpha);
	IMAGEMANAGER->findImage("arrow_up")->alphaRender(getMemDC(), _rcArrowU.left, _rcArrowU.top, _alpha);
	IMAGEMANAGER->findImage("arrow_down")->alphaRender(getMemDC(), _rcArrowD.left, _rcArrowD.top, _alpha);

	IMAGEMANAGER->findImage("maptool_ui_bg_black")->frameRender(getMemDC(), _rcBgButton[0].left, _rcBgButton[0].top,ui_frame[8], 0);
	IMAGEMANAGER->findImage("maptool_ui_bg_blue")->frameRender(getMemDC(), _rcBgButton[1].left, _rcBgButton[1].top, ui_frame[9], 0);
	IMAGEMANAGER->findImage("maptool_ui_bg_green")->frameRender(getMemDC(), _rcBgButton[2].left, _rcBgButton[2].top, ui_frame[10], 0);
	//IMAGEMANAGER->findImage("maptool_ui_bg_red")->frameRender(getMemDC(), _rcBgButton[1].left,  _rcBgButton[1].top, ui_frame[9], 0);
	//IMAGEMANAGER->findImage("maptool_ui_bg_gard")->frameRender(getMemDC(), _rcBgButton[2].left, _rcBgButton[2].top, ui_frame[10], 0);
	//IMAGEMANAGER->findImage("maptool_ui_bg_gray")->frameRender(getMemDC(), _rcBgButton[3].left, _rcBgButton[3].top, ui_frame[11], 0);
	//IMAGEMANAGER->findImage("maptool_ui_bg_blue")->frameRender(getMemDC(), _rcBgButton[4].left, _rcBgButton[4].top, ui_frame[12], 0);
	//IMAGEMANAGER->findImage("maptool_ui_bg_green")->frameRender(getMemDC(), _rcBgButton[5].left, _rcBgButton[5].top,ui_frame[13], 0);
	//IMAGEMANAGER->findImage("maptool_ui_bg_maze")->frameRender(getMemDC(), _rcBgButton[6].left, _rcBgButton[6].top, ui_frame[14], 0);

	//FrameRect(getMemDC(), _rcbgTile, RGB(255, 255, 0));
}

void mapTool_sub::input()
{
	if (PtInRect(&_rcUIbg, _ptMouse))
	{
		_alpha = 255;
	}
	else
	{
		_alpha = 100;
	}
	if (PtInRect(&_rcSub, _ptMouse))
	{
		_salpha = 255;
	}
	else
	{
		_salpha = 100;
	}

	if (INPUT->GetKeyDown(VK_LBUTTON))
	{
		
		if (PtInRect(&_rcLoad, _ptMouse))
		{
			reset_ui_frame();
			_main->setCTRL(CTRL_LOAD);
			ui_frame[1] = true;
		}
		else if (PtInRect(&_rcSave, _ptMouse))
		{
			reset_ui_frame();
			_main->setCTRL(CTRL_SAVE);
			ui_frame[0] = true;
		}
		else if (PtInRect(&_rcReset, _ptMouse))
		{
			reset_ui_frame();
			_main->setCTRL(CTRL_RESET);
			ui_frame[2] = true;
		}
		//else if (PtInRect(&_rcBG, _ptMouse))
		//{
		//	reset_ui_frame();
		//	_main->setCTRL(CTRL_BGSELECT);
		//	ui_frame[3] = true;
		//}
		else if (PtInRect(&_rcTerrain, _ptMouse))
		{
			reset_ui_frame();
			_main->setCTRL(CTRL_TERRAIN);
			ui_frame[4] = true;
		}
		else if (PtInRect(&_rcObj, _ptMouse))
		{
			reset_ui_frame();
			_main->setCTRL(CTRL_OBJECT);
			ui_frame[5] = true;
		}
		else if (PtInRect(&_rcEnemy, _ptMouse))
		{
			reset_ui_frame();
			this->popUpSubUi();
			_main->setCTRL(CTRL_ENEMY);
			ui_frame[6] = true;
		}
		else if (PtInRect(&_rcCollision, _ptMouse))
		{
			reset_ui_frame();
			this->popUpSubUi();
			_main->setCTRL(CTRL_COLLISION);
			ui_frame[7] = true;
		}
		else if (PtInRect(&_rcX, _ptMouse) && (_main->getCTRL() == CTRL_COLLISION || _main->getCTRL() == CTRL_ENEMY))
		{
			ui_frame[6] = false;
			ui_frame[7] = false;
			_main->setCTRL(CTRL_NULL);
		}
		else if (PtInRect(&_rcBgButton[0], _ptMouse))
		{
			reset_ui_frame();
			this->popUpSubUi();
			_main->setCTRL(CTRL_BG_1);
			ui_frame[8] = true;
		}
		else if (PtInRect(&_rcBgButton[1], _ptMouse))
		{
			reset_ui_frame();
			this->popUpSubUi();
			_main->setCTRL(CTRL_BG_2);
			ui_frame[9] = true;
		}
		else if (PtInRect(&_rcBgButton[2], _ptMouse))
		{
			reset_ui_frame();
			this->popUpSubUi();
			_main->setCTRL(CTRL_BG_3);
			ui_frame[10] = true;
		}

		if (PtInRect(&_rcArrowL, _ptMouse))
		{
			if (_sampleX > 0)
				_sampleX--;
		}
		else if (PtInRect(&_rcArrowR, _ptMouse))
		{
			if (_sampleX < SAMPLE_TILEX - 4)
				_sampleX++;
		}

		if (PtInRect(&_rcArrowD, _ptMouse))
		{
			if (_sampleY > 0)
				_sampleY--;
		}
		else if (PtInRect(&_rcArrowU, _ptMouse))
		{
			if (_sampleY < SAMPLE_TILEY - 6)
				_sampleY++;
		}
	}
}

void mapTool_sub::drag()
{
	// 서브 UI창 드래그로 옮기기용
	if (INPUT->GetKey(VK_LBUTTON) && PtInRect(&_rcSub, _ptMouse))
	{
		if (!_dragsubUIOn)
		{
			d_mouse.x = _ptMouse.x;
			d_mouse.y = _ptMouse.y;
			_dragsubUIOn = true;
			_dX = d_mouse.x - _rcSub.left;
			_dY = d_mouse.y - _rcSub.top;
		}
		else
		{
			_rcSub = RectMake(_ptMouse.x - _dX, _ptMouse.y - _dY, 280, 280);
		}
	}
	if (INPUT->GetKeyUp(VK_LBUTTON) && _dragsubUIOn)
	{
		ZeroMemory(&d_mouse, sizeof(POINT));
		_dragsubUIOn = false;
	}
	if (INPUT->GetKey(VK_RBUTTON) && !PtInRect(&_rcSub, _ptMouse))
	{
		
		// 처음 마우스 오른버튼 클릭할 때의 마우스 값을 저장한다.
		if (!tileDragOn)
		{
			tileDragOn = true;
			d_mouse.x = _ptMouse.x;
			d_mouse.y = _ptMouse.y;
		}
		// 오른 마우스 버튼을 놓기 전까지 
		else
		{
			if (_ptMouse.y > d_mouse.y)
			{
				_rcDragTile = RectMake(d_mouse.x, d_mouse.y, _ptMouse.x - d_mouse.x, _ptMouse.y - d_mouse.y);
			}
			else
			{
				_rcDragTile = RectMake(_ptMouse.x, _ptMouse.y, d_mouse.x - _ptMouse.x, d_mouse.y - _ptMouse.y);
			}
		}
	}

	// 오른 마우스 버튼을 떼면 tileDragOn이 false로 변하고 선택했던 타일의 렉트를 초기화
	if (INPUT->GetKeyUp(VK_RBUTTON))
	{
		tileDragOn = false;
		ZeroMemory(&d_mouse, sizeof(POINT));

		//샘플 드래그 체크
		if (sampleDragOn)
		{
			sampleDragCheck = true;
			_dragSamples.clear();
			for (int i = 0; i < abs(dragIndex._dragIndexEndY - dragIndex._dragIndexStartY) + 1; i++)
			{
				for (int j = 0; j < abs(dragIndex._dragIndexEndX - dragIndex._dragIndexStartX) + 1; j++)
				{
					tagSampleTile tmp;
					ZeroMemory(&tmp, sizeof(tagSampleTile));
					tmp.rc = RectMake(j * TILESIZE, i * TILESIZE, TILESIZE, TILESIZE);
					tmp.terrainFrameX = dragIndex._dragIndexStartX + j;
					tmp.terrainFrameY = dragIndex._dragIndexStartY + i;
					_dragSamples.push_back(tmp);
				}
			}
			sampleDragOn = false;
		}

		_rcDragTile = RectMake(0, 0, 0, 0);
	}

	
}

void mapTool_sub::dragSampleRender()
{
	if (sampleDragCheck)
	{
		_rcDragSample = RectMake(_ptMouse.x, _ptMouse.y, (abs(dragIndex._dragIndexEndX - dragIndex._dragIndexStartX) + 1) * 64, (abs(dragIndex._dragIndexEndY - dragIndex._dragIndexStartY) + 1) * 64);
		if (INPUT->GetKeyDown(VK_SPACE))
		{
			sampleDragCheck = false;
		}
	}
	else
	{
		_dragSamples.clear();
		_rcDragSample = RectMake(0, 0, 0, 0);
	}

	// 샘플 타일 드래그
	for (int i = 0; i < TILEMAPSIZEY; i++)
	{
		for (int j = 0; j < TILEMAPSIZEX; j++)
		{
			if (IntersectRect(&tmp, &_sampleTile[i][j].rc, &_rcDragTile) && PtInRect(&_rcUIbg, _ptMouse))
			{
				if (!sampleDragOn)
				{
					dragIndex._dragIndexStartX = _sampleX + j;
					dragIndex._dragIndexStartY = _sampleY + i;
					sampleDragOn = true;
				}
				else
				{
					dragIndex._dragIndexEndX = _sampleX + j;
					dragIndex._dragIndexEndY = _sampleY + i;
				}
			}
		}
	}
	//드래그 이미지 렌더
	if (sampleDragCheck)
	{
		//드래그한 이미지 보여주기
		IMAGEMANAGER->alphaRender("sampleTileMap", getMemDC(), _rcDragSample.left, _rcDragSample.top,
			(_dragSamples[0].terrainFrameX) * 64, (_dragSamples[0].terrainFrameY) * 64,
			(_rcDragSample.right - _rcDragSample.left), (_rcDragSample.bottom - _rcDragSample.top), 100);
	}
}

inline void mapTool_sub::reset_ui_frame()
{
	for (int i = 0; i < TOTAL_BUTTON; i++)
	{
		ui_frame[i] = false;
	}
}

void mapTool_sub::popUpSubUi()
{
	_rcSub = RectMake(_rcUIbg.left - 280, 0, 280, 280);
	_rcX = RectMake(_rcSub.right - 20, _rcSub.top, 20, 20);
}
