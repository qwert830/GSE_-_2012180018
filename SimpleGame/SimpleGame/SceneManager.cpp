#include "stdafx.h"
#include "SceneManager.h"
#include <random>

void SceneManager::Update(float time)
{
	CollisionRect();
	CollisionObject();

	for (int i = 0; i< manager.size(); i++)
	{
		if (manager[i]->GetLifeTime() <= 0 && manager[i]->GetState() != OBJECT_BUILDING && manager[i]->GetState() != OBJECT_CHARACTER)
		{
			//manager.erase(manager.begin() + i);
			//i--;
		}
		if (manager[i]->GetLife() <= 0)
		{
			manager.erase(manager.begin() + i);
			i--;
		}
	}
	timecount += time;
	cout << timecount << endl;

	if (timecount >= fps)
	{
		for (int i = 0; i < manager.size(); i++)
		{
			manager[i]->Update(time);
			if (manager[i]->GetState() == OBJECT_BUILDING)
			{
				if (manager[i]->GetAttackDelay() >= 0.5f)
				{
					POS temp = manager[i]->GetPos();
					NewBullet(temp.x + windowW, temp.y + windowH);
					manager[i]->SetAttackDelay(0);
				}
			}
		}
		timecount = 0;
	}
}

void SceneManager::NewObject(int x, int y, COLORS colors, float size)
{
	manager.push_back(new Object(pRenderer, POS(x - windowW, -y + windowH, 0), colors, size));
}

void SceneManager::NewObject(int x, int y, COLORS colors, POS direction, float size)
{
	manager.push_back(new Object(pRenderer, POS(x - windowW, -y + windowH, 0), direction, colors, size));
}

void SceneManager::NewBuilding(int x, int y)
{
	manager.push_back(new Object(pRenderer, POS(x - windowW, -y + windowH, 0), COLORS(1, 1, 0, 1), 50));
	int index = manager.size() - 1;
	manager[index]->SetLife(500);
	manager[index]->SetSpeed(0);
	manager[index]->SetState(OBJECT_BUILDING);
}

void SceneManager::NewCharacter(int x, int y)
{
	manager.push_back(new Object(pRenderer, POS(x - windowW, -y + windowH, 0), COLORS(1, 1, 1, 1), 10));
	int index = manager.size() - 1;
	manager[index]->SetLife(10);
	manager[index]->SetSpeed(100);
	manager[index]->SetState(OBJECT_CHARACTER);
	float dx = GetRandom();
	float dy = GetRandom();
	manager[index]->SetDirection(POS(dx, dy, 0));
}

void SceneManager::NewBullet(int x, int y)
{
	manager.push_back(new Object(pRenderer, POS(x - windowW, -y + windowH, 0), COLORS(1, 0, 0, 1), 2));
	int index = manager.size() - 1;
	manager[index]->SetLife(20);
	manager[index]->SetSpeed(300);
	manager[index]->SetState(OBJECT_BULLET);
	float dx = GetRandom();
	float dy = GetRandom();
	manager[index]->SetDirection(POS(dx, dy, 0));
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
	for (int i = 0; i < 100; i++)
	{
		float x = GetRandom();
		float y = GetRandom();
		NewObject(rand() % windowW * 2, rand() % windowH * 2, COLORS(1, 1, 1, 1),POS(x,y,0), 10);
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
	for (int i = 0; i < manager.size(); i++)
		if (manager[i]->GetState() == OBJECT_CHARACTER)
			manager[i]->SetColor(1, 1, 1, 1);

	if(manager.size() >= 2)
	for (int i = 0; i < manager.size(); i++)
	{
		POS tempObj1 = manager[i]->GetPos();
		float tempSize1 = manager[i]->GetSize()/2.0f;

		for (int j = i+1; j < manager.size(); j++)
		{
			POS tempObj2 = manager[j]->GetPos();
			float tempSize2 = manager[j]->GetSize()/2.0f;

			if (tempObj1.x - tempSize1 <= tempObj2.x - tempSize2 && tempObj2.x - tempSize2 <= tempObj1.x + tempSize1)
			{
				if (tempObj1.y - tempSize1 <= tempObj2.y - tempSize2 && tempObj2.y - tempSize2 <= tempObj1.y + tempSize1)
				{
					if (manager[i]->GetState() == OBJECT_CHARACTER)
						manager[i]->SetColor(1, 0, 0, 1);
					if (manager[j]->GetState() == OBJECT_CHARACTER)
						manager[j]->SetColor(1, 0, 0, 1);
					if (manager[i]->GetState() == OBJECT_BUILDING && manager[j]->GetState() == OBJECT_CHARACTER)
					{
						manager[i]->SetLife(manager[i]->GetLife() - manager[j]->GetLife());
						manager.erase(manager.begin() + j);
						j--;
					}
					else if (manager[i]->GetState() == OBJECT_CHARACTER && manager[j]->GetState() == OBJECT_BULLET)
					{
						manager[i]->SetLife(manager[i]->GetLife() - manager[j]->GetLife());
						manager.erase(manager.begin() + j);
						j--;
					}
					break;
				}
				else if (tempObj1.y - tempSize1 <= tempObj2.y + tempSize2 && tempObj2.y + tempSize2 <= tempObj1.y + tempSize1)
				{
					if (manager[i]->GetState() == OBJECT_CHARACTER)
						manager[i]->SetColor(1, 0, 0, 1);
					if (manager[j]->GetState() == OBJECT_CHARACTER)
						manager[j]->SetColor(1, 0, 0, 1);
					if (manager[i]->GetState() == OBJECT_BUILDING && manager[j]->GetState() == OBJECT_CHARACTER)
					{
						manager[i]->SetLife(manager[i]->GetLife() - manager[j]->GetLife());
						manager.erase(manager.begin() + j);
						j--;
					}
					else if (manager[i]->GetState() == OBJECT_CHARACTER && manager[j]->GetState() == OBJECT_BULLET)
					{
						manager[i]->SetLife(manager[i]->GetLife() - manager[j]->GetLife());
						manager.erase(manager.begin() + j);
						j--;
					}
					break;
				}
			}
			else if (tempObj1.x - tempSize1 <= tempObj2.x + tempSize2 && tempObj2.x + tempSize2 <= tempObj1.x + tempSize1)
			{
				if (tempObj1.y - tempSize1 <= tempObj2.y - tempSize2 && tempObj2.y - tempSize2 <= tempObj1.y + tempSize1)
				{
					if (manager[i]->GetState() == OBJECT_CHARACTER)
						manager[i]->SetColor(1, 0, 0, 1);
					if (manager[j]->GetState() == OBJECT_CHARACTER)
						manager[j]->SetColor(1, 0, 0, 1);
					if (manager[i]->GetState() == OBJECT_BUILDING && manager[j]->GetState() == OBJECT_CHARACTER)
					{
						manager[i]->SetLife(manager[i]->GetLife() - manager[j]->GetLife());
						manager.erase(manager.begin() + j);
						j--;
					}
					else if (manager[i]->GetState() == OBJECT_CHARACTER && manager[j]->GetState() == OBJECT_BULLET)
					{
						manager[i]->SetLife(manager[i]->GetLife() - manager[j]->GetLife());
						manager.erase(manager.begin() + j);
						j--;
					}
					break;
				}
				else if (tempObj1.y - tempSize1 <= tempObj2.y + tempSize2 && tempObj2.y + tempSize2 <= tempObj1.y + tempSize1)
				{
					if (manager[i]->GetState() == OBJECT_CHARACTER)
						manager[i]->SetColor(1, 0, 0, 1);
					if (manager[j]->GetState() == OBJECT_CHARACTER)
						manager[j]->SetColor(1, 0, 0, 1);
					if (manager[i]->GetState() == OBJECT_BUILDING && manager[j]->GetState() == OBJECT_CHARACTER)
					{
						manager[i]->SetLife(manager[i]->GetLife() - manager[j]->GetLife());
						manager.erase(manager.begin() + j);
						j--;
					}
					else if (manager[i]->GetState() == OBJECT_CHARACTER && manager[j]->GetState() == OBJECT_BULLET)
					{
						manager[i]->SetLife(manager[i]->GetLife() - manager[j]->GetLife());
						manager.erase(manager.begin() + j);
						j--;
					}
					break;
				}
			}
		}
	}
}

float SceneManager::GetRandom()
{
	random_device rn;
	mt19937_64 rnd(rn());

	uniform_real_distribution<float> range(-1, 1);

	return range (rnd);
}

SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
	manager.~vector();
}
