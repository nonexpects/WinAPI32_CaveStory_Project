#pragma once

enum tagItemType
{
	ITEM_NULL,
	ITEM_EXP,
	ITEM_HP_1,
	ITEM_HP_3,
	ITEM_MISSILE_1,
	ITEM_MISSILE_3,

	ITEM_COUNT
};

enum tagFIXED
{
	FIX_I_NULL,
	FIX_I_FILL,
	FIX_I_SAVE,
	FIX_I_COMPUTER,
	FIX_I_LOG_COMPUTER,
	FIX_I_TELEPORTER,

	FIX_I_COUNT
};

class item
{
protected:
	float _time;

	string _name;							//아이템 이름
	tagItemType _type;					//아이템 설명
	image* _itemImg;							//아이템 이미지
	int _frameX, _frameY;						//아이템 이미지 프레임
	float _x, _y;
	RECT _rc;
	int _count;
	int _alpha;

	bool _isGet;									//아이템을 플레이어가 얻었냐

public :
	virtual HRESULT init(float x, float y);
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
	void animation();

	virtual RECT getRect() { return _rc; }
	virtual tagItemType getType() { return _type; }
	virtual bool getGet() { return _isGet; }

	virtual void setGet(bool isGet) { _isGet = isGet; }
	bool timeOver();

	item() : _name(""), _type(ITEM_NULL),
		_isGet(false), _itemImg(nullptr), _frameX(0), _frameY(0), _count(0),
	_x (0), _y(0), _time(0.f), _alpha(255) {}
	virtual ~item() {}

};

class item_fixed
{
protected:
	float _time;

	string _name;
	tagFIXED _type;
	image* _itemImg;
	int _frameX, _frameY;
	float _x, _y;
	RECT _rc;
	int _count;
	int _alpha;

	bool _isOn;

public:
	virtual HRESULT init(float x, float y);
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
	void animation();

	virtual RECT getRect() { return _rc; }
	virtual tagFIXED getType() { return _type; }
	virtual float getPosX() { return _x; }
	virtual float getPosY() { return _y; }
	void run(bool isOn);

	item_fixed() : _name(""), _type(FIX_I_NULL), _isOn(false),
		_itemImg(nullptr), _frameX(0), _frameY(0), _count(0),
		_x(0), _y(0), _time(0.f), _alpha(255) {}
	virtual ~item_fixed() {}

};

