#pragma once
#include "gameNode.h"
#include "pixelCollision.h"

class enemyManager;

//�Ѿ� ����ü
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
//	## bullet ## (�����Ѿ� - ������� ������ ��)
//=============================================================
class bullet : public gameNode
{
private:
	//�Ѿ� ����ü�� ���� ����, �ݺ���
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	pixelCollision* _pc;
private:
	const char* _imageName;	//�Ѿ� �̹��� �̸�
	float _range;			//�Ѿ� ��Ÿ�
	int _bulletMax;			//�Ѿ� �ִ밹��
	bool _isFrameImg;		//������ �̹�����?
	int _atk;
public:
	HRESULT init(const char* imageName, image* collisionMap, int bulletMax, float range, int atk, bool isFrameImg = true);
	void release();
	void update();
	void render(HDC hdc);

	//�Ѿ˹߻�
	void fire(float x, float y, float angle, float speed, int frameX, int frameY);
	//�Ѿ˹���
	void move(player* _player, bool isAnim = false);
	void move(enemyManager* _em);

	void checkBulletColl(tagBullet & bullet, enemyManager* _em, int index);
	void checkBulletColl (tagBullet & bullet, player* _player, int index);

	void changeBullet(const char* imageName, int atk, float range);

	void animation();

	//�Ѿ˺��� ��������
	vector<tagBullet> getBullet() { return _vBullet; }
	//��ź ����
	void removeBullet(int index);

	bullet() {}
	~bullet() {}
};

//=============================================================
//	## missile ## (missile[0] -> �迭ó�� �̸� �����صΰ� �Ѿ˹߻�)
//=============================================================
class missile : public gameNode
{
private:
	//�Ѿ� ����ü�� ���� ����, �ݺ���
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	pixelCollision* _pc;
private:
	const char* _imageName;	//�Ѿ� �̹��� �̸�
	float _range;			//�Ѿ� ��Ÿ�
	int _bulletMax;			//�Ѿ� �ִ밹��
	bool _isFrameImg;		//������ �̹�����?
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

	//�Ѿ˹߻�
	void fire(float x, float y, float angle, float speed, int frameX, int frameY);
	//�Ѿ˹���
	void move(enemyManager* _em);

	void checkBulletColl(tagBullet & bullet, enemyManager* _em, int index);
	void changeBullet(const char* imageName, int atk, float range);

	// �Ѿ˺��� ��������
	vector<tagBullet> getBullet() { return _vBullet; }
	// �Ѿ� ���� 
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
	//�Ѿ� ����ü�� ���� ����, �ݺ���
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	pixelCollision* _pc;

private:
	const char* _imageName;	//�Ѿ� �̹��� �̸�
	float _range;		 	//�Ѿ� ��Ÿ�
	int _bulletMax;			//�Ѿ� �ִ밹��
	bool _isFrameImg;		//������ �̹�����?
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

	//�Ѿ˹߻�
	void fire(float x, float y, float angle, float speed, int frameX, int frameY);
	//�Ѿ˹���
	void move(enemyManager* _em);

	void checkBulletColl(tagBullet& bullet, enemyManager* _em, int index);
	void changeBullet(const char* imageName, int atk, float range, bool isSizeChange = false,  int width = 0, int height = 0);

	//�Ѿ˺��� ��������
	vector<tagBullet> getBullet() { return _vBullet; }
	
	//��ź ����
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
	//�Ѿ� ����ü�� ���� ����, �ݺ���
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	pixelCollision* _pc;

	int bulletCount;
	bool fireOn;

private:
	const char* _imageName;	//�Ѿ� �̹��� �̸�
	float _range;			//�Ѿ� ��Ÿ�
	int _bulletMax;			//�Ѿ� �ִ밹��
	int _atk;
	float _time;
	float _fireX, _fireY, _angle;

public:
	HRESULT init(const char* imageName, player* _player, int bulletMax);
	void release();
	void update();
	void render(HDC hdc);

	//�Ѿ˹߻�
	void fire(float x, float y, float angle);
	//�Ѿ˹���
	void move();

	void checkBulletColl(tagBullet & bullet, int index);

	//�Ѿ˺��� ��������
	vector<tagBullet> getBullet() { return _vBullet; }
	//��ź ����
	void removeBullet(int index);

	boss_bullet() {}
	~boss_bullet() {}
};



//=============================================================
//	## bomb ## (��źó�� �ѹ߾� �߻��ϰ� �����ϰ� �ڵ�����)
//=============================================================
//class bomb : public gameNode
//{
//private:
//	//�Ѿ� ����ü�� ���� ����, �ݺ���
//	vector<tagBullet> _vBullet;
//	vector<tagBullet>::iterator _viBullet;
//
//private:
//	const char* _imageName;	//�Ѿ� �̹��� �̸�
//	float _range;			//�Ѿ� ��Ÿ�
//	int _bulletMax;			//�Ѿ� �ִ밹��
//	bool _isFrameImg;		//������ �̹�����?
//
//public:
//	HRESULT init(const char* imageName, int bulletMax, float range, bool isFrameImg = false);
//	void release();
//	void update();
//	void render(HDC hdc);
//
//	//�Ѿ˹߻�
//	void fire(float x, float y, float angle, float speed, int frameX, int frameY);
//	//�Ѿ˹���
//	void move();
//
//	//�Ѿ˺��� ��������
//	vector<tagBullet> getBullet() { return _vBullet; }
//	//��ź ����
//	void removeBomb(int index);
//
//	bomb() {}
//	~bomb() {}
//};



