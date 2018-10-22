#include "stdafx.h"
#include "SceneMgr.h"

//헤더에서 포함시켰음
//#include "Renderer.h"
#include "ObjectClass.h"

INIT_SINGLETON(CSceneMgr)

float g_Time = 0.f;

CSceneMgr::CSceneMgr()
	: m_pRenderer(nullptr)
{
	for (auto& iter : m_Objects)
	{
		iter = nullptr;
	}
}

CSceneMgr::~CSceneMgr()
{
	m_pRenderer->DeleteTexture(m_texIssac);
}

void CSceneMgr::Initialize()
{
	// Initialize Renderer
	m_pRenderer = new Renderer(500, 500);
	if (!m_pRenderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}

	//init object
	m_Objects[OBJ_HERO] = new CObjectClass();
	m_Objects[OBJ_HERO]->SetPos(0.f, 0.f);
	m_Objects[OBJ_HERO]->SetVel(0.f, 0.f);
	m_Objects[OBJ_HERO]->SetAcc(0.f, 0.f);
	m_Objects[OBJ_HERO]->SetForceX(0.f);
	m_Objects[OBJ_HERO]->SetForceY(0.f);
	m_Objects[OBJ_HERO]->SetMass(2.5f);
	m_Objects[OBJ_HERO]->SetFrictionCoef(0.3f);
	m_Objects[OBJ_HERO]->SetSize(0.75f, -0.8f);
	m_Objects[OBJ_HERO]->SetColor(1.f, 1.f, 1.f, 1.f);
	m_Objects[OBJ_HERO]->SetPosHeight(1.5f);

	m_texIssac = m_pRenderer->CreatePngTexture("../Resources/issac_norm.png");
}

void CSceneMgr::RenderScene()
{
	/*여러 객체의 상태만 가지고 와서 그것을 기준으로 Redner만 해주는 Method*/

	//다 지운다.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//매개변수 RGBA
	glClearColor(0.f, 0.f, 1.f, 1.f);
	//glClearColor(1.f, 1.f, 1.f, 1.f);

	
	//Professor's code
	/*float x = std::sin(g_Time) * 200.f;
	float y = std::cos(g_Time) * 200.f;
	float size = std::abs(std::sin(g_Time) * 200.f);
	g_Time += 0.001f;*/

	//Renderer Test
	float x, y;
	m_Objects[OBJ_HERO]->GetPosition(x, y);
	float width, height;
	m_Objects[OBJ_HERO]->GetSize(width, height);
	float r, g, b, a;
	m_Objects[OBJ_HERO]->GetColor(r, g, b, a);
	float posHeight;
	m_Objects[OBJ_HERO]->GetPosHeight(posHeight);

	float newX, newY, newPosHeight, newW, newH;
	newX = x * 100.f;
	newY = y * 100.f;
	newPosHeight = posHeight * 100.f;
	newW = width * 100.f;
	newH = height * 100.f;

	//m_pRenderer->DrawSolidRect(newX, newY, 0.f, newW, newH, r, g, b, a);
	//m_pRenderer->DrawTextureRect(newX, newY, 0.f, newW, newH, r, g, b, a, m_texIssac);
	m_pRenderer->DrawTextureRectHeight(newX, newY, 0.f, newW, newH, r, g, b, a, m_texIssac, newPosHeight);
}

//float temp = 0.f; //for Test
void CSceneMgr::Update(const float& eTime)
{
	m_Objects[OBJ_HERO]->Update(eTime);

	/*m_pPlayer->SetSize(temp, temp);
	temp += 0.05f;

	if (temp > 200.f)
	{
		temp = 0.f;
	}*/

	//컴퓨터 마다 속도가 다르기 때문에 
	//컴퓨터 마다 단위를 정해야 한다!
	//보통은 sec로 많이 쓰니까 단위 통일
	//1m/s -> 1m/s^2
}

void CSceneMgr::ApplyForce(float x, float y, float eTime)
{
	m_Objects[OBJ_HERO]->ApplyForce(x, y, eTime);
}


void CSceneMgr::Free()
{
	Delete_Array(m_Objects);
	delete m_pRenderer;
	m_pRenderer = nullptr;
}

bool CSceneMgr::AddObject(POSITION pos, VELOCITY speed, OBJSIZE size)
{
	//find empty slot
	int index = FindEmptySlot();


	//allocate
	if (index < 0)
		return false;

	m_Objects[index] = new CObjectClass;
	m_Objects[index]->SetPos(pos.x, pos.y);
	m_Objects[index]->SetVel(speed.velx, speed.vely);
	m_Objects[index]->SetAcc(0.f, 0.f);
	m_Objects[index]->SetForceX(0.f);
	m_Objects[index]->SetForceY(0.f);
	m_Objects[index]->SetMass(2.5f);
	m_Objects[index]->SetFrictionCoef(0.3f);
	m_Objects[index]->SetSize(size.width, size.height);
	m_Objects[index]->SetColor(1.f, 1.f, 1.f, 1.f);
	m_Objects[index]->SetPosHeight(1.5f);


	return true;
}

bool CSceneMgr::DeleteObject(ObjType id)
{
	if (m_Objects[id])
	{
		delete(m_Objects[id]);
		m_Objects[id] = nullptr;
	}

	return true;
}

int CSceneMgr::FindEmptySlot()
{
	int index = -1;
	for (auto& iter : m_Objects)
	{
		if (iter == nullptr)
		{
			break;
		}
		index++;
	}
	if (index == -1)
	{
		//full
		std::cout << "all slots are occupied. \n";
	}

	return index;
}
