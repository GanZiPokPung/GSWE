#include "stdafx.h"
#include "ObjectClass.h"


CObjectClass::CObjectClass()
{
}


CObjectClass::~CObjectClass()
{
}

void CObjectClass::Update()
{
	//float eTime = 1.f / 60.f;
	float eTime = 1.f / 360.f;

	//Calc velocity
	if (m_velX >= 0)
	{
		m_velX = m_velX - eTime * 0.2;
	}
	

	//Calc position
	m_posX = m_posX + eTime * m_velX;
	m_posY = m_posY + eTime * m_velY;

	//가속도
	//vel' = vel + elapsed Time * acc

	//마찰 
	//표면적 질량 need

	//		마찰
	//     (0.2m/s^2)<-ㅁ----> (1m/s)
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
