#pragma once

class CObjectClass;
class Renderer;

class CSceneMgr
{
	DECLARE_SINGLETON(CSceneMgr)
public:
	~CSceneMgr();
public:
	CObjectClass* GetpPlayer() { return m_pPlayer; }
	Renderer*     GetpRenderer() { return m_pRenderer; }
public:
	void Initialize();
	void RenderScene();
	void Update();
	void Free();
private:
	CObjectClass* m_pPlayer = nullptr;
	Renderer* m_pRenderer = nullptr;
	
	//position
	//elapsed Time
	//Velocity

	//ÇÑÇÈ¼¿Àº 1cm

};

