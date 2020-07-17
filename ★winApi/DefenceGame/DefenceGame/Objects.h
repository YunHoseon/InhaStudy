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
	virtual void CreateObj() = 0;
};

class PlayerObj : public CObjects
{
public:
	PlayerObj();
	~PlayerObj();
};

class EnemyObj : public CObjects
{
public:
	EnemyObj(float _x, float _y);
	~EnemyObj();

	void DrawObj(HDC hdc);
	void CreateObj();		//사용x
	void RotateEnemy(EnemyObj *enemeis);//사용x
};

class BlockObj : public CObjects
{
public:
	BlockObj(float _x, float _y);
	~BlockObj();

	void DrawObj(HDC hdc);
	void CreateObj();//사용x
};

class BulletObj : public CObjects
{

};