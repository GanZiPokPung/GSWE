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
		iter = NULL;
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
	m_Objects[OBJ_HERO]->SetKey(KIND_HERO);

	m_texIssac = m_pRenderer->CreatePngTexture("../Resources/issac_norm.png");
	//m_texSeq = m_pRenderer->CreatePngTexture("../Resources/animation.png");

	AddObject(POSITION{ 1.f, 1.f }, VELOCITY{ 0.f, 0.f }, OBJSIZE{ 0.75f, -0.8f });
}

int g_Seq = 0;

void CSceneMgr::RenderScene()
{
	/*여러 객체의 상태만 가지고 와서 그것을 기준으로 Redner만 해주는 Method*/

	//다 지운다.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//매개변수 RGBA
	//glClearColor(0.f, 0.f, 0.f, 1.f);
	glClearColor(1.f, 1.f, 1.f, 1.f);

	
	//Professor's code
	/*float x = std::sin(g_Time) * 200.f;
	float y = std::cos(g_Time) * 200.f;
	float size = std::abs(std::sin(g_Time) * 200.f);
	g_Time += 0.001f;*/

	g_Time += 0.001;
	int seqX = g_Seq % 7;
	int seqY = int(g_Seq / 7.f);
	if (g_Time > 0.1)
	{
		g_Seq++;
		g_Time = 0;
	}
	if (g_Seq > 27)
		g_Seq = 0;

	for (int i = 0; i < MAX_OBJECT; i++)
	{
		if (m_Objects[i] == NULL)
			break;

		//Renderer Test
		float x, y;
		m_Objects[i]->GetPosition(x, y);
		float width, height;
		m_Objects[i]->GetSize(width, height);
		float r, g, b, a;
		m_Objects[i]->GetColor(r, g, b, a);
		float posHeight;
		m_Objects[i]->GetPosHeight(posHeight);

		float newX, newY, newPosHeight, newW, newH;
		newX = x * 100.f;
		newY = y * 100.f;
		newPosHeight = posHeight * 100.f;
		newW = width * 100.f;
		newH = height * 100.f;

		//m_pRenderer->DrawSolidRect(newX, newY, 0.f, newW, newH, r, g, b, a);
		//m_pRenderer->DrawTextureRect(newX, newY, 0.f, newW, newH, r, g, b, a, m_texIssac);
		m_pRenderer->DrawTextureRectHeight(newX, newY, 0.f, newW, newH, r, g, b, a, m_texIssac, newPosHeight);
		//m_pRenderer->DrawTextureRectSeqXY(newX, newY, 0.f, newW, newH, r, g, b, a, m_texSeq, seqX, seqY, 7, 4);
	}
}

//float temp = 0.f; //for Test
void CSceneMgr::Update(const float& eTime)
{
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		if (m_Objects[i] == NULL)
			break;
		
		m_Objects[i]->Update(eTime);
	}
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

void CSceneMgr::UpdateCollision()
{
	// 두 Obj의 상호작용을 for loop를 통해
	for(int i = 0; i < MAX_OBJECT; i++)
	{
		if (m_Objects[i] == nullptr)
			continue;

		int collisionCount = 0;

		for (int j = 0; j < MAX_OBJECT; j++)
		{


			if (m_Objects[j] == nullptr)
				continue;

			// 서로 같은 obj가 상호작용을 하지 않도록 예외처리
			if (i == j)
				continue;

			// src
			float srcLeft, srcRight, srcBottom, srcTop;
			float srcPosX, srcPosY, srcSizeX, srcSizeY;

			m_Objects[i]->GetPosition(srcPosX, srcPosY);
			m_Objects[i]->GetSize(srcSizeX, srcSizeY);

			srcLeft = srcPosX - srcSizeX / 2.f;
			srcRight = srcPosX + srcSizeX / 2.f;
			srcBottom = srcPosY - srcSizeY / 2.f;
			srcTop = srcPosY + srcSizeY / 2.f;

			// dst
			float dstLeft, dstRight, dstBottom, dstTop;
			float dstPosX, dstPosY, dstSizeX, dstSizeY;

			m_Objects[j]->GetPosition(dstPosX, dstPosY);
			m_Objects[j]->GetSize(dstSizeX, dstSizeY);

			dstLeft = dstPosX - dstSizeX / 2.f;
			dstRight = dstPosX + dstSizeX / 2.f;
			dstBottom = dstPosY - dstSizeY / 2.f;
			dstTop = dstPosY + dstSizeY / 2.f;

			if (RRCollision(srcLeft, srcBottom, srcRight, srcTop,
							dstLeft, dstBottom, dstRight, dstTop))
			{
				/*std::cout << "Object " << i << " collides "
						  << "Object " << j << " collides "
						  << std::endl;*/
				collisionCount++;
			}
		}

		if (collisionCount > 0)
		{
			m_Objects[i]->SetColor(1, 0, 0, 1);
		}
		else
		{
			m_Objects[i]->SetColor(1, 1, 1, 1);
		}
	}
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
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		if (m_Objects[i] == NULL)
		{
			index = i;
			break;
		}
	}
	if (index == -1)
	{
		//full
		std::cout << "all slots are occupied. \n";
	}

	return index;
}

bool CSceneMgr::RRCollision(float srcLeft, float srcBottom, float srcRight, float srcTop,
							float dstLeft, float dstBottom, float dstRight, float dstTop)
{
	if (srcLeft < dstRight &&
		srcTop < dstBottom &&
		srcRight > dstLeft &&
		srcBottom > dstTop)
	{
		// 충돌된 경우
		return true;
	}

	// 정밀한 충돌지점 Calculation은 여기에다가 하면 됨

	// 충돌되지 않은 경우
	return false;
}

void CSceneMgr::Shoot(ShootType direction)
{
	if (direction == SHOOT_NONE)
		return;

	VELOCITY bv;
	bv.velx = 0.f;
	bv.vely = 0.f;
	float amountSpeed = 5.f;
	
	switch (direction)
	{
	case SHOOT_UP:
		bv.velx = 0.f;
		bv.vely = amountSpeed;
		break;
	case SHOOT_DOWN:
		bv.velx = 0.f;
		bv.vely = -amountSpeed;
		break;
	case SHOOT_RIGHT:
		bv.velx = amountSpeed;
		bv.vely = 0.f;
		break;
	case SHOOT_LEFT:
		bv.velx = -amountSpeed;
		bv.vely = 0.f;
		break;
	}
	POSITION p;
	VELOCITY v;
	m_Objects[OBJ_HERO]->GetPosition(p.x, p.y);
	m_Objects[OBJ_HERO]->GetVel(v.velx, v.vely);

	bv.velx += v.velx;
	bv.vely += v.vely;
	OBJSIZE s;
	s.width = 0.2f;
	s.height = 0.2f;

	AddObject(p, bv, s);
}
