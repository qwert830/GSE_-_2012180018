#include "stdafx.h"
#include "ObjectManager.h"


void ObjectManager::Update(float time)
{
	for (auto &d : manager)
	{
		d->Update(0);
	}
}

void ObjectManager::NewObject(Renderer* g_Renderer,int x, int y, COLORS colors, float size)
{
	manager.push_back(new Object(g_Renderer, POS(x - windowW, -y + windowH, 0), colors, size));
}

void ObjectManager::Draw()
{
	for (auto &d : manager)
	{
		d->DrawObject();
	}
}

ObjectManager::ObjectManager()
{
}


ObjectManager::~ObjectManager()
{
}
