#pragma once

enum LengthType
{
	MAX_OBJECT = 300
};

enum ObjType
{
	OBJ_HERO
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