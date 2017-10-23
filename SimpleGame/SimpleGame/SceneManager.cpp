#include "stdafx.h"
#include "SceneManager.h"
#include <time.h>
#include <random>

void SceneManager::Update(float time)
{
	CollisionRect();
	CollisionObject();
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
	for (int i = 0; i < 10; i++)
	{
		float x = (float)(rand() % 5) - 0.99f;
		float y = (float)(rand() % 5) - 0.99f;
		if (i == 0)
			NewObject(rand() % windowW * 2, rand() % windowH * 2, COLORS(1, 1, 1, 1), 5);
		else
			NewObject(rand() % windowW * 2, rand() % windowH * 2, COLORS(0, 0, 1, 1), 5);
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
	if(manager.size() >= 2)
	for (int i = 0; i < manager.size(); i++)
	{
		POS tempObj1 = manager[i]->GetPos();
		float tempSize1 = manager[i]->GetSize();
		manager[i]->SetColor(0, 1, 1, 1);

		for (int j = 1; j < manager.size(); j++)
		{
			POS tempObj2 = manager[j]->GetPos();
			float tempSize2 = manager[j]->GetSize();

			if (tempObj1.y - tempSize1 <= tempObj2.y + tempSize2 && tempObj1.y - tempSize1 >= tempObj2.y - tempSize2)
			{
				if (tempObj1.x - tempSize1 <= tempObj2.x + tempSize2 && tempObj1.x - tempSize1 >= tempObj2.x - tempSize2)
				{
					manager[i]->SetColor(1, 0, 0, 1);
					break;
				}
				else if (tempObj1.x + tempSize1 <= tempObj2.x + tempSize2 && tempObj1.x + tempSize1 >= tempObj2.x - tempSize2)
				{
					break;
				}
			}
			else if (tempObj1.y + tempSize1 <= tempObj2.y + tempSize2 && tempObj1.y + tempSize1 >= tempObj2.y - tempSize2)
			{
				if (tempObj1.x - tempSize1 <= tempObj2.x + tempSize2 && tempObj1.x - tempSize1 >= tempObj2.x - tempSize2)
				{
					break;
				}
				else if (tempObj1.x + tempSize1 <= tempObj2.x + tempSize2 && tempObj1.x + tempSize1 >= tempObj2.x - tempSize2)
				{
					break;
				}
			}
		}
	}
}

SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
	manager.~vector();
}
