#include "stdafx.h"
#include "playerData.h"
#include "player.h"

HRESULT playerData::init()
{
	isSceneStart = isLoaded = isSceneChange = false;
	ZeroMemory(&tempsaveData, sizeof(tagPlayerData));
	ZeroMemory(&saveData, sizeof(tagSaveData));
	ZeroMemory(&savedData, sizeof(tagSaveData));
	//ZeroMemory(&saveData, sizeof(tagSaveData));

	return S_OK;
}

void playerData::release()
{

}

void playerData::savePlayerData(player * player)
{
	if(!isSceneStart) 
		isSceneStart = true;
	tempsaveData.maxHp = player->getMaxHP();
	tempsaveData.currentHp = player->getHP();
	tempsaveData.posX = player->getPosX();
	tempsaveData.posY = player->getPosY();
	tempsaveData.currentWeaponIndex = player->getCurrentIndex();
	
	tempsaveData.ps_lv = player->getPolarStar()->getLv();
	tempsaveData.ps_currentExp = player->getPolarStar()->getCurrentExp();
	tempsaveData.fg_lv = player->getFireGun()->getLv();
	tempsaveData.fg_currentExp = player->getFireGun()->getCurrentExp();
	tempsaveData.mg_lv = player->getMachineGun()->getLv();
	tempsaveData.mg_currentExp = player->getMachineGun()->getCurrentExp();
	tempsaveData.lc_lv = player->getLancher()->getLv();
	tempsaveData.lc_currentExp = player->getLancher()->getCurrentExp();
	tempsaveData.lc_currentBullet = player->getLancher()->getcurrentBullet();
	tempsaveData.lc_maxBullet = player->getLancher()->getBulletMax();

	isSceneChange = false;
}

void playerData::savePlayerData(player * player, string sceneName)
{

	strcpy(saveData.sceneName, sceneName.c_str());
	saveData.maxHp = player->getMaxHP();
	saveData.currentHp = player->getHP();
	saveData.posX = player->getPosX();
	saveData.posY = player->getPosY();
	saveData.currentWeaponIndex = player->getCurrentIndex();

	saveData.ps_lv = player->getPolarStar()->getLv();
	saveData.ps_currentExp = player->getPolarStar()->getCurrentExp();
	saveData.fg_lv = player->getFireGun()->getLv();
	saveData.fg_currentExp = player->getFireGun()->getCurrentExp();
	saveData.mg_lv = player->getMachineGun()->getLv();
	saveData.mg_currentExp = player->getMachineGun()->getCurrentExp();
	saveData.lc_lv = player->getLancher()->getLv();
	saveData.lc_currentExp = player->getLancher()->getCurrentExp();
	saveData.lc_currentBullet = player->getLancher()->getcurrentBullet();
	saveData.lc_maxBullet = player->getLancher()->getBulletMax();

	HANDLE file;
	DWORD write;

	char tmp[128];
	
	file = CreateFile("save.txt", GENERIC_WRITE, NULL, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	ZeroMemory(&tmp, sizeof(tmp));
	sprintf_s(tmp, "%s,", saveData.sceneName);
	WriteFile(file, tmp, strlen(tmp), &write, NULL);
	ZeroMemory(&tmp, sizeof(tmp));
	sprintf_s(tmp, "%d,", saveData.maxHp);
	WriteFile(file, tmp, strlen(tmp), &write, NULL);
	ZeroMemory(&tmp, sizeof(tmp));
	sprintf_s(tmp, "%d,", saveData.currentHp);
	WriteFile(file, tmp, strlen(tmp), &write, NULL);
	ZeroMemory(&tmp, sizeof(tmp));
	sprintf_s(tmp, "%f,", saveData.posX);
	WriteFile(file, tmp, strlen(tmp), &write, NULL);
	ZeroMemory(&tmp, sizeof(tmp));
	sprintf_s(tmp, "%f,", saveData.posY);
	WriteFile(file, tmp, strlen(tmp), &write, NULL);
	ZeroMemory(&tmp, sizeof(tmp));
	sprintf_s(tmp, "%d,", saveData.currentWeaponIndex);
	WriteFile(file, tmp, strlen(tmp), &write, NULL);
	ZeroMemory(&tmp, sizeof(tmp));
	sprintf_s(tmp, "%d,", saveData.ps_lv);
	WriteFile(file, tmp, strlen(tmp), &write, NULL);
	ZeroMemory(&tmp, sizeof(tmp));
	sprintf_s(tmp, "%d,", saveData.ps_currentExp);
	WriteFile(file, tmp, strlen(tmp), &write, NULL);
	ZeroMemory(&tmp, sizeof(tmp));
	sprintf_s(tmp, "%d,", saveData.fg_lv);
	WriteFile(file, tmp, strlen(tmp), &write, NULL);
	ZeroMemory(&tmp, sizeof(tmp));
	sprintf_s(tmp, "%d,", saveData.fg_currentExp);
	WriteFile(file, tmp, strlen(tmp), &write, NULL);
	ZeroMemory(&tmp, sizeof(tmp));
	sprintf_s(tmp, "%d,", saveData.mg_lv);
	WriteFile(file, tmp, strlen(tmp), &write, NULL);
	ZeroMemory(&tmp, sizeof(tmp));
	sprintf_s(tmp, "%d,", saveData.mg_currentExp);
	WriteFile(file, tmp, strlen(tmp), &write, NULL);
	ZeroMemory(&tmp, sizeof(tmp));
	sprintf_s(tmp, "%d,", saveData.lc_lv);
	WriteFile(file, tmp, strlen(tmp), &write, NULL);
	ZeroMemory(&tmp, sizeof(tmp));
	sprintf_s(tmp, "%d,", saveData.lc_currentExp);
	WriteFile(file, tmp, strlen(tmp), &write, NULL);
	ZeroMemory(&tmp, sizeof(tmp));
	sprintf_s(tmp, "%d,", saveData.lc_currentBullet);
	WriteFile(file, tmp, strlen(tmp), &write, NULL);
	ZeroMemory(&tmp, sizeof(tmp));
	sprintf_s(tmp, "%d,", saveData.lc_maxBullet);
	WriteFile(file, tmp, strlen(tmp), &write, NULL);

	CloseHandle(file);
}

void playerData::loadSaveData()
{
	vector<string> tmpSave;
	tagSaveData tmp;

	tmpSave = textLoad();

	strcpy(tmp.sceneName, tmpSave[0].c_str());
	tmp.maxHp = atoi(tmpSave[1].c_str());
	tmp.currentHp = atoi(tmpSave[2].c_str());
	tmp.posX = atoi(tmpSave[3].c_str());
	tmp.posY = atoi(tmpSave[4].c_str());
	tmp.currentWeaponIndex = atoi(tmpSave[5].c_str());
	tmp.ps_lv = atoi(tmpSave[6].c_str());
	tmp.ps_currentExp = atoi(tmpSave[7].c_str());
	tmp.fg_lv = atoi(tmpSave[8].c_str());
	tmp.fg_currentExp = atoi(tmpSave[9].c_str());
	tmp.mg_lv = atoi(tmpSave[10].c_str());
	tmp.mg_currentExp = atoi(tmpSave[11].c_str());
	tmp.lc_lv = atoi(tmpSave[12].c_str());
	tmp.lc_currentExp = atoi(tmpSave[13].c_str());
	tmp.lc_currentBullet = atoi(tmpSave[14].c_str());
	tmp.lc_maxBullet = atoi(tmpSave[15].c_str());

	savedData = tmp;
}

vector<string> playerData::textLoad()
{
	HANDLE file;
	DWORD read;

	char str[1024] = {};

	file = CreateFile("save.txt", GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, str, 1024, &read, NULL);

	CloseHandle(file);

	return charArraySeparation(str);
}

vector<string> playerData::charArraySeparation(char charArray[])
{
	vector<string> vArray;

	char* temp;
	const char* separator = ","; //±¸ºÐÀÚ
	char* token;

	token = strtok_s(charArray, separator, &temp);
	vArray.push_back(token);

	while (NULL != (token = strtok_s(NULL, separator, &temp)))
	{
		vArray.push_back(token);
	}

	//300,300,80,100
	//300

	return vArray;
}