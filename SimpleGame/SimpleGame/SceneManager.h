#pragma once
#include "Object.h"
#include <vector>
#include <iostream>

using namespace std;

class SceneManager
{
private:
	vector<Object*> manager;
	int windowW;
	int windowH;
	Renderer* pRenderer;
public:
	void Update(float time);
	void NewObject(int x, int y, COLORS colors,float size);
	void Draw(); 
	void SetRenderer(Renderer* g_Renderer) { pRenderer = g_Renderer; }
	void CreateTest();
	void CollisionRect();
	void CollisionObject();
	SceneManager();
	SceneManager(int x, int y) : windowW(x / 2), windowH(y / 2){}
	~SceneManager();
};

