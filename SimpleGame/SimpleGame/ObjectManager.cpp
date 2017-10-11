#include "stdafx.h"
#include "ObjectManager.h"


void ObjectManager::update(float time)
{
	for (auto &d : manager)
	{
		d->DrawObject();
		d->Update(0);
	}
}

void ObjectManager::newObject(Renderer* g_Renderer,int x, int y, COLORS colors)
{
	manager.emplace_back(new Object(g_Renderer,POS(x-windowW,-y+windowH,0),colors));
}

ObjectManager::ObjectManager()
{
}


ObjectManager::~ObjectManager()
{
}
