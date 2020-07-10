#pragma once

// 게임 화면 타일
#define TILESIZE 64
//#define SAMPLETILESIZE 16
#define MAP_TILEX 300
#define MAP_TILEY 100
#define TILESIZEX (MAP_TILEX * TILESIZE)
#define TILESIZEY (MAP_TILEY * TILESIZE)

#define TILEMAPSIZEX 4
#define TILEMAPSIZEY 6

#define CAMERA_TILEX WINSIZEX/TILESIZE
#define CAMERA_TILEY WINSIZEY/TILESIZE

// 이미지 타일 (화면 우측 상단에 붙여 놓을 샘플 타일)
// X SIZE 고정 6 (384pixel)

#define SAMPLE_TILEX 16
#define SAMPLE_TILEY 38
#define COLLI_TILEX 4
#define COLLI_TILEY 4

// 맵툴에서 사용할 컨트롤들 열거문

enum BG
{
	BG_NULL, BG_BLACK, BG_RED, BG_GARD, BG_GRAY, BG_BLUE, BG_GREEN, BG_MAZE, BG_COUNT
};
enum CTRL
{
	CTRL_NULL,CTRL_BG_1, CTRL_BG_2, CTRL_BG_3,
	CTRL_SAVE, CTRL_LOAD, CTRL_OBJERASER, CTRL_TERERASER, CTRL_COLERASER, CTRL_BGERASER, CTRL_RESET,
	CTRL_TERRAIN, CTRL_OBJECT, CTRL_COLLISION, CTRL_ENEMY,
	CTRL_END
};

// 지형 열거문
enum TERRAIN
{
	TR_NULL, TR_PENS, TR_MIMI, TR_EGGS, TR_WHITE, TR_END
};

// 오브젝트 열거문
enum OBJECT
{
	OBJ_CARPET,
	OBJ_BLOCK1, OBJ_BLOCK2, OBJ_BLOCK3, OBJ_BLOCKS,
	OBJ_LINK, OBJ_BOSS, OBJ_MOB1, OBJ_MOB2,
	OBJ_NONE
};

enum COLLISION
{
	COL_NULL,
	COL_TRUE
};

// 맵툴 메뉴 열거문
enum MAPTOOL_MENU
{
	MENU_HOUSE,
	MENU_TOWN,
	MENU_BOSS,
	MENU_HOME,
	MENU_CHAR
};

// 타일 구조체
struct tagTile
{
	BG bg;
	TERRAIN terrain;
	OBJECT obj;
	COLLISION col;
	RECT rc;

	int x, y;
	int bgFrameX;
	int bgFrameY;
	int terrainFrameX;
	int terrainFrameY;
	int objFrameX;
	int objFrameY;
	int collisionFrameX;
	int collisionFrameY;
	//드래그용
	bool isSelect;
};

// 샘플 타일 구조체
struct tagSampleTile
{
	RECT rc;
	int terrainFrameX;
	int terrainFrameY;
};

// 현재 타일 구조체
struct tagCurrentTile
{
	int x, y;
};

// 타일 데이터 구조체
struct tagTileData
{
	tagTile tile[MAP_TILEY][MAP_TILEX];
};

struct tagDragIndex
{
	int _dragIndexStartX;
	int _dragIndexStartY;
	int _dragIndexEndX;
	int _dragIndexEndY;
};