/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/
#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"
#include "Renderer.h"
#include "Object.h"
#include "SceneManager.h"
#include <vector>

#define MY_WINDOW_W 500
#define MY_WINDOW_H 500

using namespace std;

SceneManager manager(MY_WINDOW_W, MY_WINDOW_H);

bool buttonClick = false;

DWORD preTime = 0;
DWORD curTime = 0;
DWORD elapsedTime = 0;

void RenderScene(void) // update call
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);	
	
	manager.Update(elapsedTime);
	manager.Draw();
	preTime = curTime;

	glutSwapBuffers();
}

void Idle(void) // update call
{
	manager.Update(elapsedTime);
	RenderScene();
}

// 구현 : 클릭 & 드래그

void MouseInput(int button, int state, int x, int y)
{
	// state == 0 : buttonDown
	// state == 1 : buttonUp
	if (button == GLUT_LEFT_BUTTON&&state == GLUT_DOWN)
	{
		buttonClick = true;
	}
	if (button == GLUT_LEFT_BUTTON&&state == GLUT_UP&&buttonClick)
	{
		manager.NewObject(x, y, COLORS(1, 0, 0, 1), 5);
		buttonClick = false;
	}
	RenderScene();
}

void KeyInput(unsigned char key, int x, int y)
{
	RenderScene();
}

void SpecialKeyInput(int key, int x, int y)
{
	RenderScene();
}

int main(int argc, char **argv)
{
	// Initialize GL things
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(MY_WINDOW_W, MY_WINDOW_H);
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
	
	manager.CreateRenderer();
	manager.CreateTest();
	//렌더러 포인터 설정

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	glutMainLoop();

    return 0;
}

