#include "stdafx.h"
#include "sceneManager.h"
// *****
#include "scene.h"

HRESULT sceneManager::init()
{
	return S_OK;
}
void sceneManager::release()
{
	//�������� ���
	//miSceneList iter = _mSceneList.begin();
	//for (; iter != _mSceneList.end();)
	//{
	//	if (iter->second != NULL)
	//	{
	//		//���⼭ ����
	//		if (iter->second == _currentScene) iter->second->release();
	//		SAFE_DELETE(iter->second);
	//		iter = _mSceneList.erase(iter);
	//	}
	//	else
	//	{
	//		++iter;
	//	}
	//}
	//_mSceneList.clear();

	//C++ ����� ����
	int a;
	float b;

	//for (auto scene in _mSceneList) ������ ���Ұ�
	for(auto s : _mSceneList)
	{
		s.second->release();
		SAFE_DELETE(s.second);
	}
}

void sceneManager::update()
{
	if (_prevScene)
	{
		_prevScene->release();
		_prevScene = NULL;
	}
	//������� �����ϸ� �ش��ϴ� ���� ������Ʈ�ض�
	
	if (_currentScene) _currentScene->update();
}

void sceneManager::render()
{
	//������� �����ϸ� �ش��ϴ� ���� �����ض�
	if (_currentScene) _currentScene->render();
}

scene * sceneManager::addScene(string sceneName, scene * scene)
{
	//���� ������ �׳� �� ����
	if (!scene) return NULL;

	//���� ������ �ʿ� ���
	_mSceneList.insert(make_pair(sceneName, scene));
	//_mSceneList.insert(pair<string, gameNode*>(sceneName, scene));

	return scene;
}

HRESULT sceneManager::loadScene(string sceneName)
{
	//scene* tmp= NULL;
	//if (_currentScene != nullptr)
	//	tmp = _currentScene;
	miSceneList find = _mSceneList.find(sceneName);

	//��ã�Ҵٸ� E_fail
	if (find == _mSceneList.end()) return E_FAIL;

	//�ٲٷ��� ���� ������� ���ٸ� E_fail
	if (find->second == _currentScene) return E_FAIL;

	//������� ������ ���� ������ ���� ����ó������
	if (SUCCEEDED(find->second->init()))
	{
		_prevScene = _currentScene;
		_currentScene = find->second;
		//if(tmp != NULL) tmp->release();
		return S_OK;
	}

	return E_FAIL;
}
