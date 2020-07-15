#pragma once

class CShape
{
public:
	int x;
	int y;

	int size;
	int type;

	int speed;
	int dir;
	double rotation;

	int moveToX;
	int moveToY;

public:
	CShape();
	~CShape();

	virtual void Update() = 0;
	virtual void Collision() = 0;
	virtual void DrawShape(HDC hdc) = 0;

	virtual void SetXY(int _x, int _y) { x = _x; y = _y; }
	virtual void SetSize(int _size) { size = _size; }
	virtual void SetType(int _type) { type = _type; }

	virtual int GetSpeed() { return speed; }
	virtual void SetSpeed(int _speed) { speed = _speed; }
	virtual void SetRot(double _rot) { rotation = _rot; }

	virtual void SetmoveToX(int _moveToX) { moveToX = _moveToX; }
	virtual void SetmoveToY(int _moveToY) { moveToY = _moveToY; }
};

class CRectangle : public CShape
{
	int type;

public:
	CRectangle();
	~CRectangle();

	void Update();
	void Collision();
	void DrawShape(HDC hdc);
};

//class CCircle : public CShape
//{
//public:
//	CCircle();
//	~CCircle();
//};
//
//class CStar : public CShape
//{
//public:
//	CStar();
//	~CStar();
//};