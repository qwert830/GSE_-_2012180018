#pragma once
#include "Object.h"
#include "Renderer.h"
#include <vector>
#include <iostream>

using namespace std;

class SceneManager
{
private:
	int windowW;
	int windowH;
	Renderer* pRenderer;
public:
	vector<Object*> manager;
	void Update(float time);
	void NewObject(int x, int y, COLORS colors,float size);
	void NewObject(int x, int y, COLORS colors, POS direction, float size);
	void Draw(); 
	void CreateRenderer() { pRenderer = new Renderer(windowW * 2, windowH * 2); }
	void CreateTest();
	void CollisionRect();
	void CollisionObject();
	SceneManager();
	SceneManager(int x, int y) : windowW(x / 2), windowH(y / 2) {}
	~SceneManager();
};

