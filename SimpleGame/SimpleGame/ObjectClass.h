#pragma once
class CObjectClass
{
public:
	CObjectClass();
	virtual ~CObjectClass();
public:
	//struct
	/*POSITION GetPos(void) { return m_position; }
	SIZE	 GetSize(void) { return m_size; }
	COLOR	 GetColor(void) { return m_color; }*/

	void Update();

	//Get
	const float& GetPosX() { return m_posX; }
	const float& GetPosY() { return m_posY; }

	const float& GetWidth() { return m_width; }
	const float& GetHeight() { return m_height; }

	const float& GetColor_R() { return m_r; }
	const float& GetColor_G() { return m_g; }
	const float& GetColor_B() { return m_b; }
	const float& GetColor_A() { return m_a; }
	//교수님은 포인터로 Get해온다.

	void GetPosition(float& posX, float& posY);
	void GetVel(float& velX, float& velY);
	void GetSize(float& width, float& height);
	void GetColor(float& r, float& g, float& b, float& a);

	//Set
	void SetPos(float posX, float posY);
	void SetVel(float velX, float velY);
	void SetSize(float width, float height);
	void SetColor(float r, float g, float b, float a);

	
	//
	
	//position = position + elapsed Time * Velocity
	

private:
	//stuct
	/*POSITION m_position;
	SIZE	 m_size;
	COLOR	 m_color;*/

	//Pos
	float m_posX;
	float m_posY;
	
	float m_velX;
	float m_velY;

	//Size
	float m_width;
	float m_height;
	
	//Color
	float m_r;
	float m_g;
	float m_b;
	float m_a;
};

