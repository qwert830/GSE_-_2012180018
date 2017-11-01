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
	float fps = 1 / 60.0f;
	float timecount = 0.0f;
	Renderer* pRenderer;
public:
	vector<Object*> manager;
	void Update(float time);
	void NewObject(int x, int y, COLORS colors,float size);
	void NewObject(int x, int y, COLORS colors, POS direction, float size);
	void NewBuilding(int x, int y);
	void NewCharacter(int x, int y);
	void NewBullet(int x, int y);
	void Draw(); 
	void CreateRenderer() { pRenderer = new Renderer(windowW * 2, windowH * 2); }
	void CreateTest();
	void CollisionRect();
	void CollisionObject();
	float GetRandom();
	SceneManager();
	SceneManager(int x, int y) : windowW(x / 2), windowH(y / 2) {}
	~SceneManager();
};

