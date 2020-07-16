#pragma once
class CShape
{
	int x;
	int y;

	int size;
	int type;

	double speed;
	double rotation;
	double moveTo;

public:
	CShape();
	~CShape();

	virtual void Update() = 0;
	virtual void Collision() = 0;
	virtual void DrawShape() = 0;
	
	void SetXY(int _x, int _y) { x = _x; y = _y; }
	void SetSize(int _size) { size = _size; }
	void SetType(int _type) { type = _type; }

	void SetSpeed(double _speed) { speed = _speed; }
	void SetRot(double _rot) { rotation = _rot; }
	void SetMoveTo(double _moveTo) { moveTo = _moveTo; }
};

class CRectangle : public CShape
{
	int x;
	int y;

	int size;
	int type;

	double speed;
	double rotation;
	double moveTo;
public:
	CRectangle();
	~CRectangle();

	void Update();
	void Collision();
	void DrawShape(HDC hdc, int _x, int _y, int _size);

	void SetXY(int _x, int _y) { x = _x; y = _y; }
	void SetSize(int _size) { size = _size; }
	void SetType(int _type) { type = _type; }

	void SetSpeed(double _speed) { speed = _speed; }
	void SetRot(double _rot) { rotation = _rot; }
	void SetMoveTo(double _moveTo) { moveTo = _moveTo; }
};

class CCircle : public CShape
{
public:
	CCircle();
	~CCircle();
};

class CStar : public CShape
{
public:
	CStar();
	~CStar();
};

