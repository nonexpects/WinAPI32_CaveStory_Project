#include "stdafx.h"
#include "mainGame.h"

//=============================================================
//	## �ʱ�ȭ ## init()
//=============================================================
HRESULT mainGame::init()
{
	gameNode::init();
	//Ŭ���� �ʱ�ȭ�� �̰����� �Ѵ�

	/*������ ���ΰ����� ������ ���鸸 ������ �Ѵ�*/
	//������ ������ ���ΰ��� ������ �Ѵ�

	/*���߰�*/
	SCENEMANAGER->addScene("loadingScene", new loadingScene);
	SCENEMANAGER->addScene("startScene", new startScene);
	SCENEMANAGER->addScene("houseScene", new houseScene);
	SCENEMANAGER->addScene("maptoolScene", new mapToolScene);
	SCENEMANAGER->addScene("mimigaScene", new mimigaScene);
	SCENEMANAGER->addScene("eggScene", new eggScene);
	SCENEMANAGER->addScene("bossScene", new bossScene);
	
	/*����� ����*/
	SCENEMANAGER->loadScene("loadingScene");

	return S_OK;
}

//=============================================================
//	## ���� ## release()
//=============================================================
void mainGame::release()
{
	gameNode::release();

}

//=============================================================
//	## ������Ʈ ## update()
//=============================================================
void mainGame::update()
{
	gameNode::update();
	
	//���Ŵ��� ������Ʈ
	SCENEMANAGER->update();
	//����Ŵ��� ������Ʈ(�̳�����ָ� ���尡 �����۵�����)
	SOUNDMANAGER->update();

	FX->update();
	DIALOG->update();
}

//=============================================================
//	## ���� ## render()
//=============================================================
void mainGame::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
//=============================================================	
	//���Ŵ��� ����
	SCENEMANAGER->render();
	//Ÿ�ӸŴ��� ����
	TIMEMANAGER->render(getMemDC());
	DIALOG->render(getMemDC());

	//���ڻ� ��� ���ֱ�
	SetBkMode(getMemDC(), TRANSPARENT);
	//�ؽ�Ʈ ���� ����
	SetTextColor(getMemDC(), RGB(255, 255, 255));
	
//=============================================================
	//������� ������ ȭ��DC�� �׸���
	this->getBackBuffer()->render(getHDC());
}
