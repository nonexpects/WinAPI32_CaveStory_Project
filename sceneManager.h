#pragma once
#include "singletonBase.h"
//=============================================================
//	## sceneManager ## (���Ŵ���)
//=============================================================

//�̱����� ��ӹ��� ���̵��� static���� ����� ���⶧����
//�Ϲ�Ŭ������ ���ӳ�带 ����Ϸ��� �ϸ� ������

class scene;

class sceneManager : public singletonBase <sceneManager>
{
private:
	typedef map<string, scene*> mSceneList;
	typedef map<string, scene*>::iterator miSceneList;

private:
	mSceneList _mSceneList;		//������ ��(ȭ��)���� ��Ƶ� ��
	scene* _currentScene;	//�����

	scene* _prevScene;
public:
	HRESULT init();
	void release();
	void update();
	void render();

	//���߰�
	scene* addScene(string sceneName, scene* scene);
	//������
	HRESULT loadScene(string sceneName);

	sceneManager() : _currentScene(NULL), _prevScene(NULL) {}
	~sceneManager() {}
};

