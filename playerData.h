#pragma once
#include "singletonBase.h"

class player;

struct tagPlayerData
{
	int maxHp;
	int currentHp;
	float posX, posY;
	int ps_lv;
	int ps_currentExp;
	int fg_lv;
	int fg_currentExp;
	int mg_lv;
	int mg_currentExp;
	int lc_lv;
	int lc_currentExp;
	int currentWeaponIndex;
	int lc_currentBullet;
	int lc_maxBullet;
};

struct tagSaveData
{
	char sceneName[20];
	int maxHp;
	int currentHp;
	float posX, posY;
	int ps_lv;
	int ps_currentExp;
	int fg_lv;
	int fg_currentExp;
	int mg_lv;
	int mg_currentExp;
	int lc_lv;
	int lc_currentExp;
	int currentWeaponIndex;
	int lc_currentBullet;
	int lc_maxBullet;

};

class playerData : public singletonBase <playerData>
{
private:
	tagPlayerData tempsaveData;
	tagSaveData saveData;

	tagSaveData savedData;

	vector<string> v_save;

	float _x, _y;
	bool isSceneStart;
	bool isSceneChange;
	bool isLoaded;

public:
	HRESULT init();
	void release();

	tagSaveData getSavedData() { return savedData; }

	bool isSceneStarted() { return isSceneStart; }
	bool isSceneChanged() { return isSceneChange; }
	bool IsLoaded() { return isLoaded; }
	void SetIsSaved(bool SceneChanged) { isSceneChange = SceneChanged; }
	void SetIsLoaded(bool sIsLoaded) { isLoaded = sIsLoaded; }

	void savePlayerData(player* player);
	void savePlayerData(player* player, string sceneName);
	vector<string> charArraySeparation(char charArray[]);
	vector<string> textLoad();
	tagPlayerData loadTempData() { return tempsaveData; }
	void loadSaveData();


	//int getHp() { return _hp; }
	//void setHp(int hp) { _hp = hp; }

	playerData() {}
	~playerData() {}
};