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
	//정석적인 방법
	//miSceneList iter = _mSceneList.begin();
	//for (; iter != _mSceneList.end();)
	//{
	//	if (iter->second != NULL)
	//	{
	//		//여기서 삭제
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

	//C++ 고오급 문법
	int a;
	float b;

	//for (auto scene in _mSceneList) 지금은 사용불가
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
	//현재씬이 존재하면 해당하는 씬을 업데이트해라
	
	if (_currentScene) _currentScene->update();
}

void sceneManager::render()
{
	//현재씬이 존재하면 해당하는 씬을 렌더해라
	if (_currentScene) _currentScene->render();
}

scene * sceneManager::addScene(string sceneName, scene * scene)
{
	//씬이 없으면 그냥 널 리턴
	if (!scene) return NULL;

	//씬이 있으면 맵에 담기
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

	//못찾았다면 E_fail
	if (find == _mSceneList.end()) return E_FAIL;

	//바꾸려는 씬과 현재씬이 같다면 E_fail
	if (find->second == _currentScene) return E_FAIL;

	//여기까지 왔으면 문제 없으니 씬을 변경처리하자
	if (SUCCEEDED(find->second->init()))
	{
		_prevScene = _currentScene;
		_currentScene = find->second;
		//if(tmp != NULL) tmp->release();
		return S_OK;
	}

	return E_FAIL;
}
