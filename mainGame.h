#pragma once
#include "gameNode.h"
/*������ ���ΰ����� ������ ���鸸 ������ �Ѵ�*/
/*������ϸ� ���ΰ��ӿ� �߰��ϱ�*/
#include "loadingScene.h"
#include "startScene.h"
#include "houseScene.h"
#include "mapToolScene.h"
#include "mimigaScene.h"
#include "eggScene.h"
#include "bossScene.h"

class mainGame : public gameNode
{
public:
	HRESULT init();
	void release();
	void update();
	void render();

	mainGame() {}
	~mainGame() {}
};

