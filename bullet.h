#pragma once
#include "gameNode.h"
#include "pixelCollision.h"

class enemyManager;

//총알 구조체
struct tagBullet
{
	image* bulletImage;
	RECT rc;
	float x, y;
	float fireX, fireY;
	int frameX, frameY;
	int width, height;
	float speed;
	float angle;
	float gravity;
	float radius;
	bool fire;
	bool meet;
	int count;
	float time;
	int atk;
	int lv;
};

//=============================================================
//	## bullet ## (공용총알 - 너희들이 만들어야 함)
//=============================================================
class bullet : public gameNode
{
private:
	//총알 구조체를 담을 벡터, 반복자
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	pixelCollision* _pc;
private:
	const char* _imageName;	//총알 이미지 이름
	float _range;			//총알 사거리
	int _bulletMax;			//총알 최대갯수
	bool _isFrameImg;		//프레임 이미지냐?
	int _atk;
public:
	HRESULT init(const char* imageName, image* collisionMap, int bulletMax, float range, int atk, bool isFrameImg = true);
	void release();
	void update();
	void render(HDC hdc);

	//총알발사
	void fire(float x, float y, float angle, float speed, int frameX, int frameY);
	//총알무브
	void move(player* _player, bool isAnim = false);
	void move(enemyManager* _em);

	void checkBulletColl(tagBullet & bullet, enemyManager* _em, int index);
	void checkBulletColl (tagBullet & bullet, player* _player, int index);

	void changeBullet(const char* imageName, int atk, float range);

	void animation();

	//총알벡터 가져오기
	vector<tagBullet> getBullet() { return _vBullet; }
	//폭탄 삭제
	void removeBullet(int index);

	bullet() {}
	~bullet() {}
};

//=============================================================
//	## missile ## (missile[0] -> 배열처럼 미리 장전해두고 총알발사)
//=============================================================
class missile : public gameNode
{
private:
	//총알 구조체를 담을 벡터, 반복자
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	pixelCollision* _pc;
private:
	const char* _imageName;	//총알 이미지 이름
	float _range;			//총알 사거리
	int _bulletMax;			//총알 최대갯수
	bool _isFrameImg;		//프레임 이미지냐?
	int _atk;
	int _width, _height;
	int _lv;
	float _time;

	bool _isLauncher;

public:
	HRESULT init(const char* imageName, image* collisionMap, int bulletMax, float range, int atk, bool isLauncher,  bool isFrameImg = true);
	void release();
	void update();
	void render(HDC hdc);

	//총알발사
	void fire(float x, float y, float angle, float speed, int frameX, int frameY);
	//총알무브
	void move(enemyManager* _em);

	void checkBulletColl(tagBullet & bullet, enemyManager* _em, int index);
	void changeBullet(const char* imageName, int atk, float range);

	// 총알벡터 가져오기
	vector<tagBullet> getBullet() { return _vBullet; }
	// 총알 삭제 
	void removeBullet(int index);
	void addBullet(int num);

	void setBulletLv(int lv, bool isLauncher) 
	{ 
		_lv = lv; 
		_isLauncher = isLauncher;
	}


	missile() {}
	~missile() {}
};
//=============================================================
//	## firebullet ##
//=============================================================
class firebullet : public gameNode
{
private:
	//총알 구조체를 담을 벡터, 반복자
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	pixelCollision* _pc;

private:
	const char* _imageName;	//총알 이미지 이름
	float _range;		 	//총알 사거리
	int _bulletMax;			//총알 최대갯수
	bool _isFrameImg;		//프레임 이미지냐?
	int _count;
	int _atk;
	int _width, _height;
	int _lv;

	int trail[3];

	int _FXcount;

	POINT tmp;

public:
	HRESULT init(const char* imageName, image* collisionMap, int bulletMax, float range, int atk, bool isFrameImg = true);
	void release();
	void update();
	void render(HDC hdc);

	//총알발사
	void fire(float x, float y, float angle, float speed, int frameX, int frameY);
	//총알무브
	void move(enemyManager* _em);

	void checkBulletColl(tagBullet& bullet, enemyManager* _em, int index);
	void changeBullet(const char* imageName, int atk, float range, bool isSizeChange = false,  int width = 0, int height = 0);

	//총알벡터 가져오기
	vector<tagBullet> getBullet() { return _vBullet; }
	
	//폭탄 삭제
	void removeBullet(int index);
	void setBulletLv(int lv) { _lv = lv; }

	firebullet() {}
	~firebullet() {}
};

//=============================================================
//	## boss_bird ## 
//=============================================================
class boss_bullet : public gameNode
{
private:
	player* _player;
	//총알 구조체를 담을 벡터, 반복자
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	pixelCollision* _pc;

	int bulletCount;
	bool fireOn;

private:
	const char* _imageName;	//총알 이미지 이름
	float _range;			//총알 사거리
	int _bulletMax;			//총알 최대갯수
	int _atk;
	float _time;
	float _fireX, _fireY, _angle;

public:
	HRESULT init(const char* imageName, player* _player, int bulletMax);
	void release();
	void update();
	void render(HDC hdc);

	//총알발사
	void fire(float x, float y, float angle);
	//총알무브
	void move();

	void checkBulletColl(tagBullet & bullet, int index);

	//총알벡터 가져오기
	vector<tagBullet> getBullet() { return _vBullet; }
	//폭탄 삭제
	void removeBullet(int index);

	boss_bullet() {}
	~boss_bullet() {}
};



//=============================================================
//	## bomb ## (폭탄처럼 한발씩 발사하고 생성하고 자동삭제)
//=============================================================
//class bomb : public gameNode
//{
//private:
//	//총알 구조체를 담을 벡터, 반복자
//	vector<tagBullet> _vBullet;
//	vector<tagBullet>::iterator _viBullet;
//
//private:
//	const char* _imageName;	//총알 이미지 이름
//	float _range;			//총알 사거리
//	int _bulletMax;			//총알 최대갯수
//	bool _isFrameImg;		//프레임 이미지냐?
//
//public:
//	HRESULT init(const char* imageName, int bulletMax, float range, bool isFrameImg = false);
//	void release();
//	void update();
//	void render(HDC hdc);
//
//	//총알발사
//	void fire(float x, float y, float angle, float speed, int frameX, int frameY);
//	//총알무브
//	void move();
//
//	//총알벡터 가져오기
//	vector<tagBullet> getBullet() { return _vBullet; }
//	//폭탄 삭제
//	void removeBomb(int index);
//
//	bomb() {}
//	~bomb() {}
//};



