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
	float fps = 1 / 60.0f; // fps½Ã°£ 1/fps
	float timecount = 0.0f;
	int characterID = 0;
	Renderer* pRenderer;
	int buildingTextures = 0;
public:
	vector<Object*> manager;
	void Init();
	void Update(float time);
	void NewObject(int x, int y, COLORS colors,float size);
	void NewObject(int x, int y, COLORS colors, POS direction, float size);
	void NewBuilding(int x, int y);
	void NewCharacter(int x, int y);
	void NewBullet(int x, int y);
	void NewArrow(int x, int y, int id);
	void Draw(); 
	void CreateRenderer() { pRenderer = new Renderer(windowW * 2, windowH * 2); }
	void CollisionObject();
	int CollisionEffect(int Obj1, int Obj2);
	float GetRandom();
	SceneManager();
	SceneManager(int x, int y) : windowW(x / 2), windowH(y / 2) {}
	~SceneManager();
};

