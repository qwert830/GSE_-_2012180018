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

	float updateTime = 0.0f;
	float createTime = 5.0f;

	int buildingTextures1 = 0;
	int buildingTextures2 = 0;
	int backgroundTextures = 0;
	int characterTextures1 = 0;
	int characterTextures2 = 0;
	int bulletTextures1 = 0;
	int bulletTextures2 = 0;
	
	Sound* m_sound;
	int soundBG;
	int soundExplosion;

public:
	vector<Object*> manager;
	void Init();
	void Update(float time);
	void NewObject(int x, int y, COLORS colors,float size);
	void NewObject(int x, int y, COLORS colors, POS direction, float size);
	void NewBuilding(int x, int y, Team team);
	void NewCharacter(int x, int y, Team team);
	void NewBullet(int x, int y, Team team);
	void NewArrow(int x, int y, int id, Team team);
	void Draw(float time); 
	void CreateRenderer() { pRenderer = new Renderer(windowW * 2, windowH * 2); }
	void CollisionObject();
	void CreateCharacter(int x, int y);
	int CollisionEffect(int Obj1, int Obj2);
	float GetRandom();
	float RangeRandom(int a, int b);
	SceneManager();
	SceneManager(int x, int y) : windowW(x / 2), windowH(y / 2) {}
	~SceneManager();
};

