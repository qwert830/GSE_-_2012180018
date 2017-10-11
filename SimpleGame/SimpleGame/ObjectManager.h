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
	void update(float time);
	void newObject(Renderer* g_Renderer, int x, int y, COLORS colors);
	ObjectManager();
	ObjectManager(int x, int y) : windowW(x / 2), windowH(y / 2) {}
	~ObjectManager();
};

