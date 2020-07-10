#include "stdafx.h"
#include "mapTool_main.h"

HRESULT mapTool_main::init()
{
	this->mapToolSetup();

	//타일 드래그 스위치
	tileDragOn = false;

	pt.x = ((float)_ptMouse.x / WINSIZEX) * TILESIZEX;
	pt.y = ((float)_ptMouse.y / WINSIZEY) * TILESIZEY;
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         
	// 지형 그리기 속성으로 시작
	_ctrlSelect = CTRL_NULL;
	_terrainSelect = TR_NULL;

	// 메뉴 HOUSE로 시작
	_menu = MENU_HOUSE;

	CAMERA->setBool(true);

	return S_OK;
}

void mapTool_main::release()
{
}

void mapTool_main::update()
{
	this->input();
	if(!PtInRect(&_ui->getbgRect(), _ptMouse)) this->drag();

	switch (_ctrlSelect)
	{
	case CTRL_SAVE:
		this->save();
		break;
	case CTRL_LOAD:
		this->load();
		break;
	case CTRL_RESET:
		this->reset();
		break;
	case CTRL_ENEMY:
		break;
	case CTRL_COLLISION:
		break;
	}

	// 타일 RECT 초기화
	for (int i = 0; i < MAP_TILEY; i++)
	{
		for (int j = 0; j < MAP_TILEX; j++)
		{
			_mapTile[i][j].rc = RectMake(j * TILESIZE, i * TILESIZE, TILESIZE, TILESIZE);
		}
	}
	
	pt.x = _ptMouse.x + CAMERA->getCamRect().left;
	pt.y = _ptMouse.y + CAMERA->getCamRect().top;


	CAMERA->update();
}

void mapTool_main::render(HDC hdc)
{
	// 인게임 맵 타일 렌더
	for (int i = 0; i < MAP_TILEY; i++)
	{
		for (int j = 0; j < MAP_TILEX; j++)
		{
			if (IntersectRect(&tmp, &CAMERA->getCamRect(), &_mapTile[i][j].rc))
			{
				if (_mapTile[i][j].bg != BG_NULL)
				{
					IMAGEMANAGER->frameRender("bgTileMap", hdc, _mapTile[i][j].rc.left, _mapTile[i][j].rc.top,
						_mapTile[i][j].bgFrameX, _mapTile[i][j].bgFrameY);
				}

				if (_mapTile[i][j].rc.left < 0) continue;

				IMAGEMANAGER->frameRender("sampleTileMap", hdc, _mapTile[i][j].rc.left, _mapTile[i][j].rc.top,
					_mapTile[i][j].terrainFrameX, _mapTile[i][j].terrainFrameY);
				
				// 인게임 맵 오브젝트 렌더
				if (_mapTile[i][j].obj == OBJ_NONE && _mapTile[i][j].col == COL_NULL) continue;

				IMAGEMANAGER->frameRender("sampleTileMap", hdc, _mapTile[i][j].rc.left, _mapTile[i][j].rc.top,
					_mapTile[i][j].objFrameX, _mapTile[i][j].objFrameY);

				if (_mapTile[i][j].col == COL_NULL) continue;

				IMAGEMANAGER->frameAlphaRender("collisionMap", hdc, _mapTile[i][j].rc.left, _mapTile[i][j].rc.top,
					_mapTile[i][j].collisionFrameX, _mapTile[i][j].collisionFrameY, 100);

			}
		}
	}



	// 타일에서 드래그한 부분 표시
	for (int i = 0; i < MAP_TILEY; i++)
	{
		for (int j = 0; j < MAP_TILEX; j++)
		{
			if (IntersectRect(&tmp, &_mapTile[i][j].rc, &_rcDragTile) && !PtInRect(&_ui->getbgRect(), _ptMouse))
			{
				_mapTile[i][j].isSelect = true;
			}
			if (_mapTile[i][j].isSelect)
			{
				IMAGEMANAGER->alphaRender("dragImage", hdc, _mapTile[i][j].rc.left, _mapTile[i][j].rc.top, 100);
			}
		}
	}

	//토글 확인
	if (INPUT->GetToggleKey(VK_F1))
	{
		for (int i = 0; i < MAP_TILEY; i++)
		{
			for (int j = 0; j < MAP_TILEX; j++)
			{
				if (IntersectRect(&tmp, &CAMERA->getCamRect(), &_mapTile[i][j].rc))
				{
					FrameRect(getmapToolDC(), _mapTile[i][j].rc, RGB(100, 100, 250));
				}
			}
		}
	}

	sprintf(str, " x : %d", pt.x);
	TextOut(getMemDC(), 0, 40, str, strlen(str));
	sprintf(str, " y : %d", pt.y);
	TextOut(getMemDC(), 0, 60, str, strlen(str));
	
}

void mapTool_main::mapToolSetup()
{
	// 인게임 화면 RECT 초기화
	for (int i = 0; i < MAP_TILEY; i++)
	{
		for (int j = 0; j < MAP_TILEX; j++)
		{
			_mapTile[i][j].x = j;
			_mapTile[i][j].y = i;
			_mapTile[i][j].bgFrameX = 0;
			_mapTile[i][j].bgFrameY = 3;
			_mapTile[i][j].bg = bgSelect(_mapTile[i][j].bgFrameX, _mapTile[i][j].bgFrameY);
			_mapTile[i][j].terrainFrameX = 0;
			_mapTile[i][j].terrainFrameY = 0;
			_mapTile[i][j].objFrameX = 0;
			_mapTile[i][j].objFrameY = 0;
			_mapTile[i][j].collisionFrameX = 0;
			_mapTile[i][j].collisionFrameY = 5;
			_mapTile[i][j].terrain = terrainSelect(_mapTile[i][j].terrainFrameX, _mapTile[i][j].terrainFrameY);
			_mapTile[i][j].obj = OBJ_NONE;
			_mapTile[i][j].col = COL_NULL;
			_mapTile[i][j].isSelect = false;
		}
	}

}

TERRAIN mapTool_main::terrainSelect(int frameX, int frameY)
{
	return TR_NULL;
}

OBJECT mapTool_main::objectSelect(int frameX, int frameY)
{
	return OBJ_BLOCKS;
}

BG mapTool_main::bgSelect(int frameX, int frameY)
{
	if (frameX < 2)
	{
		return BG_BLACK;
	}
	else if(frameX >= 2 && frameX < 4)
	{
		return BG_BLUE;
	}
	else if (frameX >= 4 && frameX < 6)
	{
		return BG_GREEN;
	}
	return BG_NULL;
}

void mapTool_main::save()
{
	char str[500];
	OPENFILENAME OFN;
	const UINT nFileNameMaxLen = 512;
	char szFileName[nFileNameMaxLen] = {};
	HANDLE file;
	DWORD write;

	memset(&OFN, 0, sizeof(OPENFILENAME));
	OFN.lStructSize = sizeof(OPENFILENAME);
	OFN.hwndOwner = _hWnd;
	OFN.lpstrFilter = "Map File(*.map)";
	OFN.lpstrFile = szFileName;
	OFN.nMaxFile = nFileNameMaxLen;
	if (0 != GetOpenFileName(&OFN))
	{
		wsprintf(str, "%s 파일을 저장했습니다.", OFN.lpstrFile);
		MessageBox(_hWnd, str, "파일 세이브 성공", MB_OK);
	}

	file = CreateFile(szFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(file, _mapTile, sizeof(tagTile) * MAP_TILEX * MAP_TILEY, &write, NULL);
	CloseHandle(file);
	EndDialog(_hWnd, IDOK);

	_ctrlSelect = CTRL_NULL;

}

void mapTool_main::load()
{	
	char str[500];
	OPENFILENAME OFN;
	const UINT nFileNameMaxLen = 512;
	char szFileName[nFileNameMaxLen] = {};
	HANDLE file;
	DWORD read;
	
	memset(&OFN, 0, sizeof(OPENFILENAME));
	OFN.lStructSize = sizeof(OPENFILENAME);
	OFN.hwndOwner = _hWnd;
	OFN.lpstrFilter = "Map File(*.map)";
	OFN.lpstrFile = szFileName;
	OFN.nMaxFile = nFileNameMaxLen;
	if (0 != GetOpenFileName(&OFN))
	{
		wsprintf(str, "%s 파일을 불러왔습니다.", OFN.lpstrFile);
		MessageBox(_hWnd, str, "파일 로드 성공", MB_OK);
	}
	
	file = CreateFile(szFileName, GENERIC_READ, 0, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, _mapTile, sizeof(tagTile) * MAP_TILEX * MAP_TILEY, &read, NULL);
	CloseHandle(file);
	EndDialog(_hWnd, IDOK);

	_ctrlSelect = CTRL_NULL;
}

void mapTool_main::reset()
{
	// 왼쪽 인게임 화면 모두 잔디가 기본 타일이 되도록 세팅
	for (int i = 0; i < MAP_TILEY; i++)
	{
		for (int j = 0; j < MAP_TILEX; j++)
		{
			_mapTile[i][j].bgFrameX = 0;
			_mapTile[i][j].bgFrameY = 3;
			_mapTile[i][j].bg = bgSelect(_mapTile[i][j].bgFrameX, _mapTile[i][j].bgFrameY);
			_mapTile[i][j].terrainFrameX = 0;
			_mapTile[i][j].terrainFrameY = 0;
			_mapTile[i][j].objFrameX = 0;
			_mapTile[i][j].objFrameY = 0;
			_mapTile[i][j].collisionFrameX = 0;
			_mapTile[i][j].collisionFrameY = 5;
			_mapTile[i][j].terrain = terrainSelect(_mapTile[i][j].terrainFrameX, _mapTile[i][j].terrainFrameY);
			_mapTile[i][j].obj = OBJ_NONE;
			_mapTile[i][j].col = COL_NULL;
			_mapTile[i][j].isSelect = false;
		}
	}
}

void mapTool_main::drag()
{
	if (INPUT->GetKey(VK_RBUTTON))
	{
		// 처음 마우스 오른버튼 클릭할 때의 마우스 값을 저장한다.
		if (!tileDragOn)
		{
			tileDragOn = true;
			d_mouse.x = pt.x;
			d_mouse.y = pt.y;
		}
		// 오른 마우스 버튼을 놓기 전까지 
		else
		{
			if (pt.y > d_mouse.y)
			{
				_rcDragTile = RectMake(d_mouse.x, d_mouse.y, pt.x - d_mouse.x, pt.y - d_mouse.y);
			}
			else
			{
				_rcDragTile = RectMake(pt.x, pt.y, d_mouse.x - pt.x, d_mouse.y - pt.y);
			}
		}
	}
	// 오른 마우스 버튼을 떼면 tileDragOn이 false로 변하고 선택했던 타일의 렉트를 초기화
	if (INPUT->GetKeyUp(VK_RBUTTON))
	{
		tileDragOn = false;

		_rcDragTile = RectMake(0, 0, 0, 0);
	}
}

void mapTool_main::setMap(tagSampleTile(*sampleTile)[SAMPLE_TILEX], vector<tagSampleTile> drag, tagDragIndex index)
{
	// 샘플타일 맵 선택
	for (int i = 0; i < SAMPLE_TILEY; i++)
	{
		for (int j = 0; j < SAMPLE_TILEX; j++)
		{
			if (PtInRect(&sampleTile[i][j].rc, _ptMouse))
			{
				_currentTile.x = sampleTile[i][j].terrainFrameX;
				_currentTile.y = sampleTile[i][j].terrainFrameY;
				_currentCtrl = _ctrlSelect;
				//select_tile = RectMake(_sampleTile[i][j].rc.left, _sampleTile[i][j].rc.top, 64, 64);
				break;
			}
		}
	}

	// 인게임 화면과 RECT 간의 충돌 처리
	for (int i = 0; i < MAP_TILEY; i++)
	{
		for (int j = 0; j < MAP_TILEX; j++)
		{
			if ((PtInRect(&_mapTile[i][j].rc, pt) || _mapTile[i][j].isSelect) && !PtInRect(&_ui->getbgRect(), _ptMouse))
			{

				if (drag.empty())
				{
					if (_ctrlSelect == CTRL_OBJERASER)
					{
						_mapTile[i][j].objFrameX = 0;
						_mapTile[i][j].objFrameY = 0;
						_mapTile[i][j].obj = OBJ_NONE;
						_mapTile[i][j].isSelect = false;
					}
					else if (_ctrlSelect == CTRL_TERERASER)
					{
						_mapTile[i][j].terrainFrameX = 0;
						_mapTile[i][j].terrainFrameY = 0;
						_mapTile[i][j].terrain = TR_NULL;
						_mapTile[i][j].isSelect = false;
					}
					else if (_ctrlSelect == CTRL_COLERASER)
					{
						_mapTile[i][j].collisionFrameX = 0;
						_mapTile[i][j].collisionFrameY = 5;
						_mapTile[i][j].col = COL_NULL;
						_mapTile[i][j].isSelect = false;
					}
					else if (_ctrlSelect == CTRL_BGERASER)
					{
						_mapTile[i][j].bgFrameX = 0;
						_mapTile[i][j].bgFrameY = 0;
						_mapTile[i][j].bg = BG_NULL;
						_mapTile[i][j].isSelect = false;
					}

					else
					{
						// 현재 버튼에 따라 타일 생성
						if (_ctrlSelect == CTRL_TERRAIN)
						{
							_mapTile[i][j].terrainFrameX = _currentTile.x;
							_mapTile[i][j].terrainFrameY = _currentTile.y;
							_mapTile[i][j].terrain = terrainSelect(_currentTile.x, _currentTile.y);
							_mapTile[i][j].isSelect = false;
						}

						else if (_ctrlSelect == CTRL_OBJECT)
						{
							_mapTile[i][j].objFrameX = _currentTile.x;
							_mapTile[i][j].objFrameY = _currentTile.y;
							_mapTile[i][j].obj = objectSelect(_currentTile.x, _currentTile.y);
							_mapTile[i][j].isSelect = false;
						}

						else if (_ctrlSelect == CTRL_BG_1)
						{
							_mapTile[i][j].bgFrameX = 0;
							_mapTile[i][j].bgFrameY = 0;
							_mapTile[i][j + 1].bgFrameX = 1;
							_mapTile[i][j + 1].bgFrameY = 0;
							_mapTile[i + 1][j].bgFrameX = 0;
							_mapTile[i + 1][j].bgFrameY = 1;
							_mapTile[i + 1][j + 1].bgFrameX = 1;
							_mapTile[i + 1][j + 1].bgFrameY = 1;
							_mapTile[i][j].bg = bgSelect(_currentTile.x, _currentTile.y);
							_mapTile[i][j].isSelect = false;
						}
						else if (_ctrlSelect == CTRL_BG_2)
						{
							_mapTile[i][j].bgFrameX = 2;
							_mapTile[i][j].bgFrameY = 0;
							_mapTile[i][j + 1].bgFrameX = 3;
							_mapTile[i][j + 1].bgFrameY = 0;
							_mapTile[i + 1][j].bgFrameX = 2;
							_mapTile[i + 1][j].bgFrameY = 1;
							_mapTile[i + 1][j + 1].bgFrameX = 3;
							_mapTile[i + 1][j + 1].bgFrameY = 1;
							_mapTile[i][j].bg = bgSelect(_currentTile.x, _currentTile.y);
							_mapTile[i][j].isSelect = false;
						}
						else if (_ctrlSelect == CTRL_BG_3)
						{
							_mapTile[i][j].bgFrameX = 4;
							_mapTile[i][j].bgFrameY = 0;
							_mapTile[i][j + 1].bgFrameX = 5;
							_mapTile[i][j + 1].bgFrameY = 0;
							_mapTile[i + 1][j].bgFrameX = 4;
							_mapTile[i + 1][j].bgFrameY = 1;
							_mapTile[i + 1][j + 1].bgFrameX = 5;
							_mapTile[i + 1][j + 1].bgFrameY = 1;
							_mapTile[i][j].bg = bgSelect(_currentTile.x, _currentTile.y);
							_mapTile[i][j].isSelect = false;
						}

					}
				}
				else
				{
					if (PtInRect(&_mapTile[i][j].rc, pt))
					{
						int x = j;
						int y = i;
						for (int k = 0; k < drag.size(); k++)
						{
							if (x == j + abs(index._dragIndexEndX - index._dragIndexStartX) + 1)
							{
								x = j;
								y++;
							}
							if (_ctrlSelect == CTRL_OBJECT)
							{
								_mapTile[y][x].objFrameX = drag[k].terrainFrameX;
								_mapTile[y][x].objFrameY = drag[k].terrainFrameY;
								_mapTile[y][x].obj = objectSelect(drag[k].terrainFrameX, drag[k].terrainFrameY);
							}
							else if (_ctrlSelect == CTRL_TERRAIN)
							{
								_mapTile[y][x].terrainFrameX = drag[k].terrainFrameX;
								_mapTile[y][x].terrainFrameY = drag[k].terrainFrameY;
								_mapTile[y][x].terrain = terrainSelect(drag[k].terrainFrameX, drag[k].terrainFrameY);
							}

							_mapTile[y][x].isSelect = false;

							x++;

							if (y > i + abs(index._dragIndexEndY - index._dragIndexStartY) + 1) break;
						}
						break;
					}
				}

			}
			
		}
	}
}

void mapTool_main::setMap(tagSampleTile(*sampleTile)[COLLI_TILEX], vector<tagSampleTile> drag, tagDragIndex index)
{

	// 샘플타일 맵 선택
	for (int i = 0; i < COLLI_TILEY; i++)
	{
		for (int j = 0; j < COLLI_TILEX; j++)
		{
			if (PtInRect(&sampleTile[i][j].rc, _ptMouse))
			{
				_currentTile.x = sampleTile[i][j].terrainFrameX;
				_currentTile.y = sampleTile[i][j].terrainFrameY;
				_currentCtrl = _ctrlSelect;
				//select_tile = RectMake(_sampleTile[i][j].rc.left, _sampleTile[i][j].rc.top, 64, 64);
				break;
			}
		}
	}
	for (int i = 0; i < MAP_TILEY; i++)
	{
		for (int j = 0; j < MAP_TILEX; j++)
		{
			if ((PtInRect(&_mapTile[i][j].rc, pt) || _mapTile[i][j].isSelect) && !PtInRect(&_ui->getbgRect(), _ptMouse) && !PtInRect(&_ui->getsubRect(), _ptMouse))
			{

				if (drag.empty())
				{
					if (_ctrlSelect == CTRL_COLLISION)
					{
						_mapTile[i][j].collisionFrameX = _currentTile.x;
						_mapTile[i][j].collisionFrameY = _currentTile.y;
						_mapTile[i][j].isSelect = false;
						_mapTile[i][j].col = COL_TRUE;
					}
				}
				else
				{
					if (PtInRect(&_mapTile[i][j].rc, pt))
					{
						int x = j;
						int y = i;
						for (int k = 0; k < drag.size(); k++)
						{
							if (x == j + abs(index._dragIndexEndX - index._dragIndexStartX) + 1)
							{
								x = j;
								y++;
							}
							if (_ctrlSelect == CTRL_COLLISION)
							{
								_mapTile[i][j].collisionFrameX = _currentTile.x;
								_mapTile[i][j].collisionFrameY = _currentTile.y;
								_mapTile[i][j].col = COL_TRUE;
							}

							_mapTile[y][x].isSelect = false;

							x++;

							if (y > i + abs(index._dragIndexEndY - index._dragIndexStartY) + 1) break;
						}
						break;
					}
				}

			}

		}
	}				
}

void mapTool_main::input()
{
	if (INPUT->GetKeyDown('E'))
	{
		_ctrlSelect = CTRL_TERERASER;
	}
	else if (INPUT->GetKeyDown('R'))
	{
		_ctrlSelect = CTRL_OBJERASER;
	}
	else if (INPUT->GetKeyDown('T'))
	{
		_ctrlSelect = CTRL_COLERASER;
	}	
	else if (INPUT->GetKeyDown('G'))
	{
		_ctrlSelect = CTRL_BGERASER;
	}
	
	// 선택 해제용
	if (INPUT->GetKeyDown(VK_RBUTTON))
	{
		// 드래그 선택된거 취소
		for (int i = 0; i < MAP_TILEY; i++)
		{
			for (int j = 0; j < MAP_TILEX; j++)
			{
				_mapTile[i][j].isSelect = false;
			}
		}

	}
}
