/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include <iostream>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#include "ObjectClass.h"
#include "SceneMgr.h"

//Renderer *g_Renderer = NULL;

float g_posX = 0.f;
float g_posY = 0.f;



//CObjectClass* g_TestObj = nullptr;

void RenderScene(void)
{
	//SceneMgr
	CSceneMgr::GetInstance()->Update();
	CSceneMgr::GetInstance()->RenderScene();


	////다 지운다.
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	////매개변수 RGBA
	//glClearColor(0.0f, 0.3f, 0.3f, 1.0f);


	//Professor's code
	/*float x = std::sin(g_Time) * 200.f;
	float y = std::cos(g_Time) * 200.f;
	float size = std::abs(std::sin(g_Time) * 200.f);
	g_Time += 0.001f;*/

	

	//Renderer Test
	/*float x, y;
	g_TestObj->GetPosition(x, y);
	float width, height;
	g_TestObj->GetSize(width, height);
	float r, g, b, a;
	g_TestObj->GetColor(r, g, b, a);

	g_Renderer->DrawSolidRect(x, y, 0, width, r, g, b, a);*/
	


	// Renderer Test
	//g_Renderer->DrawSolidRect(g_posX, g_posY, 0.f, 4.f, 1.f, 0.f, 1.f, 1.f);


	glutSwapBuffers();
}

void Idle(void)
{
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	RenderScene();
}

void KeyInput(unsigned char key, int x, int y)
{
	if (key == 'w')
	{
		float x, y;
		CSceneMgr::GetInstance()->GetpPlayer()->GetPosition(x, y);
		y += 5.f;
		CSceneMgr::GetInstance()->GetpPlayer()->SetPos(x, y);
		//g_posY += 5.f;
	}
	else if (key == 's')
	{
		float x, y;
		CSceneMgr::GetInstance()->GetpPlayer()->GetPosition(x, y);
		y -= 5.f;
		CSceneMgr::GetInstance()->GetpPlayer()->SetPos(x, y);
		//g_posY -= 5.f;
	}
	else if (key == 'a')
	{
		float x, y;
		CSceneMgr::GetInstance()->GetpPlayer()->GetPosition(x, y);
		x -= 5.f;
		CSceneMgr::GetInstance()->GetpPlayer()->SetPos(x, y);
		//g_posX -= 5.f;
	}
	else if (key == 'd')
	{
		float x, y;
		CSceneMgr::GetInstance()->GetpPlayer()->GetPosition(x, y);
		x += 5.f;
		CSceneMgr::GetInstance()->GetpPlayer()->SetPos(x, y);
		//g_posX += 5.f;
	}

	RenderScene();
}

void SpecialKeyInput(int key, int x, int y)
{
	RenderScene();
}

int main(int argc, char **argv)
{
	//Pos

	// Initialize GL things
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Game Software Engineering KPU");

	glewInit();
	if (glewIsSupported("GL_VERSION_3_0"))
	{
		std::cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		std::cout << "GLEW 3.0 not supported\n ";
	}

	CSceneMgr::GetInstance()->Initialize();

	//// Initialize Renderer
	//g_Renderer = new Renderer(500, 500);
	//if (!g_Renderer->IsInitialized())
	//{
	//	std::cout << "Renderer could not be initialized.. \n";
	//}

	////Init
	//g_TestObj = new CObjectClass();
	//g_TestObj->SetPos(0.f, 0.f);
	//g_TestObj->SetSize(5.f, 5.f);
	//g_TestObj->SetColor(1.f, 1.f, 1.f, 1.f);

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	glutMainLoop();

	//delete g_Renderer;
	CSceneMgr::GetInstance()->Free();
	CSceneMgr::ReleaseInstance();

    return 0;
}

