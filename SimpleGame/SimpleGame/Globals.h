#pragma once

enum LengthType
{
	MAX_OBJECT = 3000
};

enum ObjType
{
	OBJ_HERO
};

enum KindType
{
	KIND_HERO,
	KIND_BULLET
};

enum ShootType
{
	SHOOT_NONE,
	SHOOT_UP,
	SHOOT_DOWN,
	SHOOT_LEFT,
	SHOOT_RIGHT
};

template<typename T>
void Delete_Array(T& inArray)
{
	for (auto& iter : inArray)
	{
		if (iter)
		{
			delete iter;
			iter = NULL;
		}
	}
}

typedef struct _tagPosition
{
	float x;
	float y;
}POSITION;

typedef struct _tagVelocity
{
	float velx;
	float vely;
}VELOCITY;


typedef struct _tagObjSize
{
	float width;
	float height;
}OBJSIZE;