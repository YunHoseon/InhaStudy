#pragma once

enum ObjectType { type_Block, type_Enemy, type_Player, type_Bullet };

typedef struct MYPOINT
{
	float x;
	float y;
}MYPOINT;

class CObjects
{
public:
	int size;

	ObjectType objType;

	MYPOINT center;
	MYPOINT *points;
	size_t vertexNum;

public:
	CObjects();
	~CObjects();

	virtual void DrawObj(HDC hdc) = 0;
	void Collision();
};

class PlayerObj : public CObjects
{
public:
	PlayerObj(float _x, float _y);
	~PlayerObj();

	void DrawObj(HDC hdc);
};

class EnemyObj : public CObjects
{
public:
	EnemyObj(float _x, float _y);
	~EnemyObj();

	void DrawObj(HDC hdc);
};

class BlockObj : public CObjects
{
public:
	BlockObj(float _x, float _y);
	~BlockObj();

	void DrawObj(HDC hdc);
};

class BulletObj : public CObjects
{
public:
	BulletObj(float _x, float _y);
	~BulletObj();

	void DrawObj(HDC hdc);
};