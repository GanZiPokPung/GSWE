#include "stdafx.h"
#include "SceneMgr.h"

#include "Renderer.h"
#include "ObjectClass.h"

INIT_SINGLETON(CSceneMgr)

float g_Time = 0.f;

CSceneMgr::CSceneMgr()
	:m_pPlayer(nullptr)
	, m_pRenderer(nullptr)
{
}

CSceneMgr::~CSceneMgr()
{
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
	m_pPlayer = new CObjectClass();
	m_pPlayer->SetPos(0.f, 0.f);
	m_pPlayer->SetVel(1.f, 0.f);
	m_pPlayer->SetSize(1.f, 1.f);
	m_pPlayer->SetColor(1.f, 1.f, 1.f, 1.f);

	
}

void CSceneMgr::RenderScene()
{
	/*���� ��ü�� ���¸� ������ �ͼ� �װ��� �������� Redner�� ���ִ� Method*/

	//�� �����.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//�Ű����� RGBA
	glClearColor(0.f, 0.f, 1.f, 1.f);

	
	//Professor's code
	/*float x = std::sin(g_Time) * 200.f;
	float y = std::cos(g_Time) * 200.f;
	float size = std::abs(std::sin(g_Time) * 200.f);
	g_Time += 0.001f;*/

	//Renderer Test
	float x, y;
	m_pPlayer->GetPosition(x, y);
	float width, height;
	m_pPlayer->GetSize(width, height);
	float r, g, b, a;
	m_pPlayer->GetColor(r, g, b, a);

	float newX, newY, newW, newH;
	newX = x * 100.f;
	newY = y * 100.f;
	newW = width * 100.f;
	newH = height * 100.f;

	m_pRenderer->DrawSolidRect(newX, newY, 0.f, newW, newH, r, g, b, a);
}

float temp = 0.f; //for Test
void CSceneMgr::Update()
{
	m_pPlayer->Update();

	/*m_pPlayer->SetSize(temp, temp);
	temp += 0.05f;

	if (temp > 200.f)
	{
		temp = 0.f;
	}*/

	//��ǻ�� ���� �ӵ��� �ٸ��� ������ 
	//��ǻ�� ���� ������ ���ؾ� �Ѵ�!
	//������ sec�� ���� ���ϱ� ���� ����
	//1m/s -> 1m/s^2
}


void CSceneMgr::Free()
{
	delete m_pPlayer;
	delete m_pRenderer;
	m_pPlayer = nullptr;
	m_pRenderer = nullptr;
}