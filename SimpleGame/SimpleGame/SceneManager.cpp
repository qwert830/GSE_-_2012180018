#include "stdafx.h"
#include "SceneManager.h"
#include <time.h>
#include <random>

void SceneManager::Update(float time)
{
	CollisionRect();
	for (auto &d : manager)
	{
		d->Update(0);
	}
}

void SceneManager::NewObject(int x, int y, COLORS colors, float size)
{
	manager.push_back(new Object(pRenderer, POS(x - windowW, -y + windowH, 0), colors, size));
}

void SceneManager::Draw()
{
	for (auto &d : manager)
	{
		d->DrawObject();
	}
}

void SceneManager::CreateTest()
{
	srand(time(NULL));
	for (int i = 0; i < 500; i++)
	{
		float x = (float)(rand() % 5) - 0.99f;
		float y = (float)(rand() % 5) - 0.99f;
		NewObject(rand() % windowW*2, rand() % windowH*2, COLORS(1, 1, 1, 1), 5);
		manager[i]->SetDirection(POS(x,y,0));
		manager[i]->SetSpeed(1);
	}
}

void SceneManager::CollisionRect()
{
	for (auto& d : manager)
	{
		POS tempPos = d->GetPos();
		if (tempPos.x <-windowW || tempPos.x > windowW)
		{
			POS temp = d->GetDirection();
			d->SetDirection(POS(-temp.x, temp.y, 0));
			d->MoveUpdate(0);
		}
		if (tempPos.y < -windowH || tempPos.y > windowH)
		{
			POS temp = d->GetDirection();
			d->SetDirection(POS(temp.x, -temp.y, 0));
			d->MoveUpdate(0);
		}
	}
}

void SceneManager::CollisionObject()
{
	for (int i = 0; i < manager.max_size()-1; i++)
	{
		POS tempObj1 = manager[i]->GetPos();
		for (int j = 1; j < manager.max_size(); j++)
		{
			POS tempObj2 = manager[j]->GetPos();
			
		}
	}
}

SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
}
