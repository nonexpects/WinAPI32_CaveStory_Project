#pragma once

// ���� ȭ�� Ÿ��
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

// �̹��� Ÿ�� (ȭ�� ���� ��ܿ� �ٿ� ���� ���� Ÿ��)
// X SIZE ���� 6 (384pixel)

#define SAMPLE_TILEX 16
#define SAMPLE_TILEY 38
#define COLLI_TILEX 4
#define COLLI_TILEY 4

// �������� ����� ��Ʈ�ѵ� ���Ź�

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

// ���� ���Ź�
enum TERRAIN
{
	TR_NULL, TR_PENS, TR_MIMI, TR_EGGS, TR_WHITE, TR_END
};

// ������Ʈ ���Ź�
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

// ���� �޴� ���Ź�
enum MAPTOOL_MENU
{
	MENU_HOUSE,
	MENU_TOWN,
	MENU_BOSS,
	MENU_HOME,
	MENU_CHAR
};

// Ÿ�� ����ü
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
	//�巡�׿�
	bool isSelect;
};

// ���� Ÿ�� ����ü
struct tagSampleTile
{
	RECT rc;
	int terrainFrameX;
	int terrainFrameY;
};

// ���� Ÿ�� ����ü
struct tagCurrentTile
{
	int x, y;
};

// Ÿ�� ������ ����ü
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