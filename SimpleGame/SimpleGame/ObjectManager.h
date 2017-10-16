#pragma once
#include "Object.h"
#include <list>
#include <iostream>

using namespace std;

class ObjectManager
{
private:
	list<Object*> manager;
	int windowW;
	int windowH;
public:
	void Update(float time);
	void NewObject(Renderer* g_Renderer, int x, int y, COLORS colors,float size);
	void Draw();
	ObjectManager();
	ObjectManager(int x, int y) : windowW(x / 2), windowH(y / 2) {}
	~ObjectManager();
};

