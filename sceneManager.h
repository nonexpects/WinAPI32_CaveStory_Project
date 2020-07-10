#pragma once
#include "singletonBase.h"
//=============================================================
//	## sceneManager ## (씬매니져)
//=============================================================

//싱글톤을 상속받은 아이들은 static으로 만들어 지기때문에
//일반클래스인 게임노드를 사용하려고 하면 터진다

class scene;

class sceneManager : public singletonBase <sceneManager>
{
private:
	typedef map<string, scene*> mSceneList;
	typedef map<string, scene*>::iterator miSceneList;

private:
	mSceneList _mSceneList;		//각각의 씬(화면)들을 담아둘 맵
	scene* _currentScene;	//현재씬

	scene* _prevScene;
public:
	HRESULT init();
	void release();
	void update();
	void render();

	//씬추가
	scene* addScene(string sceneName, scene* scene);
	//씬변경
	HRESULT loadScene(string sceneName);

	sceneManager() : _currentScene(NULL), _prevScene(NULL) {}
	~sceneManager() {}
};

