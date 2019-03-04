#pragma once
#include "Renderer.h"

class CObjectClass;

class CSceneMgr
{
	DECLARE_SINGLETON(CSceneMgr)
public:
	~CSceneMgr();
public:
	CObjectClass* GetpPlayer() { return m_Objects[OBJ_HERO]; }
	Renderer*     GetpRenderer() { return m_pRenderer; }
public:
	void Initialize();
	void RenderScene();
	void Update(const float& eTime);
	void ApplyForce(float x, float y, float eTime);
	void Free();
public:
	bool AddObject(POSITION pos, VELOCITY speed, OBJSIZE size);
	bool DeleteObject(ObjType id);
	int  FindEmptySlot();
public:
	// Collision Method
	// Update
	void UpdateCollision();
	// rect to rect 
	bool RRCollision(float srcLeft, float srcBottom, float srcRight, float srcTop,
		float dstLeft, float dstBottom, float dstRight, float dstTop);
	void Shoot(ShootType direction);
private:
	//CObjectClass* m_pPlayer = nullptr;
	CObjectClass* m_Objects[MAX_OBJECT] = {};
	Renderer* m_pRenderer = nullptr;
	
	GLuint m_texIssac = 0;
	GLuint m_texSeq = 0;
	//position
	//elapsed Time
	//Velocity

	//ÇÑÇÈ¼¿Àº 1cm
};

