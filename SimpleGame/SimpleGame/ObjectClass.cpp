#include "stdafx.h"
#include "ObjectClass.h"

CObjectClass::CObjectClass()
{
}


CObjectClass::~CObjectClass()
{
}

void CObjectClass::Update(const float& eTime)
{
	//시간값
	m_life += eTime;

	//마찰력
	////speed stop : 잘못된것 같음
	////Y
	//if (m_forceY <= -7.5f)
	//{
	//	if (m_velY <= 0.f)
	//	{
	//		m_forceY = 0.f;
	//		m_velY = 0.f;
	//	}
	//}
	//else if (m_forceY >= 7.5f)
	//{
	//	if (m_velY >= 0.f)
	//	{
	//		m_forceY = 0.f;
	//		m_velY = 0.f;
	//	}
	//}
	////X
	//if (m_forceX <= -7.5f)
	//{
	//	if (m_velX <= 0.f)
	//	{
	//		m_forceX = 0.f;
	//		m_velX = 0.f;
	//	}
	//}
	//else if (m_forceX >= 7.5f)
	//{
	//	if (m_velX >= 0.f)
	//	{
	//		m_forceX = 0.f;
	//		m_velX = 0.f;
	//	}
	//}

	//Friction

	//Size of velocity
	//속도의 크기
	float velocity = sqrtf(m_velX * m_velX + m_velY * m_velY);

	
	//FLT_EPSILON >> 작은 오차 범위
	if (velocity < FLT_EPSILON)
	{
		//멈춤
	}
	else
	{
		//움직이는 경우
		//마찰력의 크기
		//gravity force
		float gZ;
		// 수직항력
		gZ = 9.8 * m_mass;
		float friction;
		friction = m_frictionCoef * gZ;

		float fX, fY;
		//현재 속도의 크기까지 가지고 있음 
		//그래서 Normalize해야함
		//방향값만..
		fX = -friction * m_velX / velocity;
		fY = -friction * m_velY / velocity;

		//Calc acc
		float accX, accY;
		accX = fX / m_mass;
		accY = fY / m_mass;

		//Calc vel by acc
		float afterVelX = m_velX + eTime * accX;
		float afterVelY = m_velY + eTime * accY;

		if (afterVelX * m_velX < 0.f)
		{
			m_velX = 0.f;
		}
		else
		{
			m_velX = m_velX + eTime * accX;
		}

		if (afterVelY * m_velY < 0.f)
		{
			m_velY = 0.f;
		}
		else
		{
			m_velY = m_velY + eTime * accY;
		}
	}

	//Calc vel by acc
	m_velX = m_velX + eTime * m_accX;
	m_velY = m_velY + eTime * m_accY;

	//Calc position
	m_posX = m_posX + eTime * m_velX;
	m_posY = m_posY + eTime * m_velY;

	//가속도
	//vel' = vel + elapsed Time * acc

	//마찰 
	//표면적 질량 need

	//		마찰
	//     (0.2m/s^2)<-ㅁ----> (1m/s)

	//올라감
	m_posHeight = m_heightTest + sin(m_life * 1.5f) * 1.f;

	//system("cls");
	//std::cout << "X : " << m_posX << "  Y : " << m_posY << std::endl;
}

void CObjectClass::ApplyForce(float x, float y, float eTime)
{
	//Cal acc
	m_accX = x / m_mass;
	m_accY = y / m_mass;

	m_velX = m_velX + m_accX * eTime;
	m_velY = m_velY + m_accY * eTime;

	//나중에 업데이트에 영향을 미치지 않도록
	m_accX = 0.f;
	m_accY = 0.f;
}

void CObjectClass::GetPosition(float & posX, float & posY)
{
	posX = m_posX;
	posY = m_posY;
}

void CObjectClass::GetVel(float & velX, float & velY)
{
	velX = m_velX;
	velY = m_velY;
}

void CObjectClass::GetAcc(float & accX, float & accY)
{
	accX = m_accX;
	accY = m_accY;
}

void CObjectClass::GetForce(float& forceX, float& forceY)
{
	forceX = m_forceX;
	forceY = m_forceY;
}

void CObjectClass::GetMass(float & mass)
{
	mass = m_mass;
}

void CObjectClass::GetFrictionCoef(float & x)
{
	x = m_frictionCoef;
}

void CObjectClass::GetSize(float & width, float & height)
{
	width = m_width;
	height = m_height;
}

void CObjectClass::GetColor(float & r, float & g, float & b, float & a)
{
	r = m_r;
	g = m_g;
	b = m_b;
	a = m_a;
}

void CObjectClass::GetPosHeight(float & height)
{
	height = m_posHeight;
}

void CObjectClass::GetKey(int & kind)
{
	kind = m_kind;
}

void CObjectClass::SetPos(float posX, float posY)
{
	m_posX = posX;
	m_posY = posY;
}

void CObjectClass::SetVel(float velX, float velY)
{
	m_velX = velX;
	m_velY = velY;
}

void CObjectClass::SetAcc(float accX, float accY)
{
	m_accX = accX;
	m_accY = accY;
}

void CObjectClass::SetForceX(float forceX)
{
	m_forceX = forceX;
}

void CObjectClass::SetForceY(float forceY)
{
	m_forceY = forceY;
}

void CObjectClass::SetMass(float mass)
{
	m_mass = mass;
}

void CObjectClass::SetFrictionCoef(float x)
{
	m_frictionCoef = x;
}

void CObjectClass::SetSize(float width, float height)
{
	m_width = width;
	m_height = height;
}

void CObjectClass::SetColor(float r, float g, float b, float a)
{
	m_r = r;
	m_g = g;
	m_b = b;
	m_a = a;
}

void CObjectClass::SetPosHeight(float height)
{
	m_posHeight = height;
	m_heightTest = m_posHeight;
}

void CObjectClass::SetKey(int kind)
{
	m_kind = kind;
}
