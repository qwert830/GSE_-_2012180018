#include "stdafx.h"
#include "SceneManager.h"
#include <random>

void SceneManager::Init()
{
	buildingTextures = pRenderer->CreatePngTexture("./Textures/Test.png");
}

void SceneManager::Update(float time)
{
	CollisionObject();
	for (int i = 0; i< manager.size();i++)
	{
		if (manager[i]->GetLifeTime() <= 0 && manager[i]->GetState() == 0)
		{
			//manager.erase(manager.begin() + i);
			//i--;
		}
		else if (manager[i]->GetLife() <= 0)
		{
			manager.erase(manager.begin() + i);
			break;
		}
		if (manager[i]->GetState() == OBJECT_BUILDING)
		{
			if (manager[i]->GetAttackDelay() >= 0.5f)
			{
				POS temp = manager[i]->GetPos();
				NewBullet(temp.x + windowW, -temp.y + windowH);
				manager[i]->SetAttackDelay(0);
			}
		}
		else if (manager[i]->GetState() == OBJECT_CHARACTER)
		{
			if (manager[i]->GetAttackDelay() >= 0.5f)
			{
				POS temp = manager[i]->GetPos();
				NewArrow(temp.x + windowW, -temp.y + windowH, manager[i]->GetID());
				manager[i]->SetAttackDelay(0);
			}
		}
		if (i >= manager.size())
		{
			break;
		}
	}
	timecount += time;
	if (timecount >= fps)
	{
		for (int i = 0; i < manager.size(); i++)
		{
			manager[i]->Update(timecount);
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
	manager[index]->SetLSSD(500, 0, OBJECT_BUILDING, POS(0, 0, 0));
}

void SceneManager::NewCharacter(int x, int y)
{
	manager.push_back(new Object(pRenderer, POS(x - windowW, -y + windowH, 0), COLORS(1, 1, 1, 1), 10));
	int index = manager.size() - 1;
	float dx = GetRandom();
	float dy = GetRandom();
	manager[index]->SetLSSD(10, 100, OBJECT_CHARACTER, POS(dx, dy, 0));
	manager[index]->SetID(characterID);
	characterID++;
}

void SceneManager::NewBullet(int x, int y)
{
	manager.push_back(new Object(pRenderer, POS(x - windowW, -y + windowH, 0), COLORS(1, 0, 0, 1), 2));
	int index = manager.size() - 1;
	float dx = GetRandom();
	float dy = GetRandom();
	manager[index]->SetLSSD(20, 300, OBJECT_BULLET, POS(dx, dy, 0));
}

void SceneManager::NewArrow(int x, int y, int id)
{
	manager.push_back(new Object(pRenderer, POS(x - windowW, -y + windowH, 0), COLORS(0, 1, 0, 1), 2));
	int index = manager.size() - 1;
	float dx = GetRandom();
	float dy = GetRandom();
	manager[index]->SetLSSD(10, 100, OBJECT_ARROW, POS(dx, dy, 0));
	manager[index]->SetID(id);
}

void SceneManager::Draw()
{
	for (auto &d : manager)
	{
		switch (d->GetState())
		{
		case OBJECT_BUILDING: d->DrawObject(buildingTextures); break;
		case OBJECT_CHARACTER: d->DrawObject(0); break;
		case OBJECT_BULLET:d->DrawObject(0); break;
		case OBJECT_ARROW:d->DrawObject(0); break;
		}
	}
}

inline void SceneManager::CollisionObject()
{
	for (int i = 0; i < manager.size(); i++)
		if (manager[i]->GetState() == OBJECT_CHARACTER)
			manager[i]->SetColor(1, 1, 1, 1);
	
	if(manager.size() > 1)
	for (int i = 0; i < manager.size(); )
	{
		POS tempObj1 = manager[i]->GetPos();
		float tempSize1 = manager[i]->GetSize()/2.0f;

		if (tempObj1.x <-windowW || tempObj1.x > windowW)
		{
			POS temp = manager[i]->GetDirection();
			manager[i]->SetDirection(POS(-temp.x, temp.y, 0));
			manager[i]->MoveUpdate(1.0f/60.0f);
		}
		if (tempObj1.y < -windowH || tempObj1.y > windowH)
		{
			POS temp = manager[i]->GetDirection();
			manager[i]->SetDirection(POS(temp.x, -temp.y, 0));
			manager[i]->MoveUpdate(1.0f / 60.0f);
		}
		for (int j = 0; j < manager.size();)
		{
			POS tempObj2 = manager[j]->GetPos();
			float tempSize2 = manager[j]->GetSize()/2.0f;

			if(i != j)
				if (tempObj1.x - tempSize1 <= tempObj2.x - tempSize2 && tempObj2.x - tempSize2 <= tempObj1.x + tempSize1)
				{
					if (tempObj1.y - tempSize1 <= tempObj2.y - tempSize2 && tempObj2.y - tempSize2 <= tempObj1.y + tempSize1)
					{
						if (manager[i]->GetState() == OBJECT_CHARACTER)
							manager[i]->SetColor(1, 0, 0, 1);
						if (manager[j]->GetState() == OBJECT_CHARACTER)
							manager[j]->SetColor(1, 0, 0, 1);
						if (manager[i]->GetState() == OBJECT_BUILDING && (manager[j]->GetState() == OBJECT_CHARACTER || manager[j]->GetState() == OBJECT_ARROW))
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
						else if (manager[i]->GetState() == OBJECT_CHARACTER && manager[j]->GetState() == OBJECT_ARROW
							&& manager[i]->GetID() != manager[j]->GetID())
						{
							manager[i]->SetLife(manager[i]->GetLife() - manager[j]->GetLife());
							manager.erase(manager.begin() + j);
							j--;
						}
					}
					else if (tempObj1.y - tempSize1 <= tempObj2.y + tempSize2 && tempObj2.y + tempSize2 <= tempObj1.y + tempSize1)
					{
						if (manager[i]->GetState() == OBJECT_CHARACTER)
							manager[i]->SetColor(1, 0, 0, 1);
						if (manager[j]->GetState() == OBJECT_CHARACTER)
							manager[j]->SetColor(1, 0, 0, 1);
						if (manager[i]->GetState() == OBJECT_BUILDING && (manager[j]->GetState() == OBJECT_CHARACTER || manager[j]->GetState() == OBJECT_ARROW))
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
						else if (manager[i]->GetState() == OBJECT_CHARACTER && manager[j]->GetState() == OBJECT_ARROW
							&& manager[i]->GetID() != manager[j]->GetID())
						{
							manager[i]->SetLife(manager[i]->GetLife() - manager[j]->GetLife());
							manager.erase(manager.begin() + j);
							j--;
						}
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
						if (manager[i]->GetState() == OBJECT_BUILDING && (manager[j]->GetState() == OBJECT_CHARACTER || manager[j]->GetState() == OBJECT_ARROW))
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
						else if (manager[i]->GetState() == OBJECT_CHARACTER && manager[j]->GetState() == OBJECT_ARROW
							&& manager[i]->GetID() != manager[j]->GetID())
						{
							manager[i]->SetLife(manager[i]->GetLife() - manager[j]->GetLife());
							manager.erase(manager.begin() + j);
							j--;
						}
					}
					else if (tempObj1.y - tempSize1 <= tempObj2.y + tempSize2 && tempObj2.y + tempSize2 <= tempObj1.y + tempSize1)
					{
						if (manager[i]->GetState() == OBJECT_CHARACTER)
							manager[i]->SetColor(1, 0, 0, 1);
						if (manager[j]->GetState() == OBJECT_CHARACTER)
							manager[j]->SetColor(1, 0, 0, 1);
						if (manager[i]->GetState() == OBJECT_BUILDING && (manager[j]->GetState() == OBJECT_CHARACTER || manager[j]->GetState() == OBJECT_ARROW))
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
						else if (manager[i]->GetState() == OBJECT_CHARACTER && manager[j]->GetState() == OBJECT_ARROW
							&& manager[i]->GetID() != manager[j]->GetID())
						{
							manager[i]->SetLife(manager[i]->GetLife() - manager[j]->GetLife());
							manager.erase(manager.begin() + j);
							j--;
						}
					}
				}
			j++;
			if (j >= manager.size() || i >= manager.size())
				break;
		}

		i++;
		if (i >= manager.size())
			break;
		if (manager.size() < 2)
		{
			break;
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
