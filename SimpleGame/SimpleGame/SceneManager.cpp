#include "stdafx.h"
#include "SceneManager.h"
#include <random>

void SceneManager::Init()
{
	m_sound = new Sound();

	int temp = pRenderer->CreatePngTexture("./Textures/Test1.png");
	buildingTextures1 = pRenderer->CreatePngTexture("./Textures/Test1.png");
	buildingTextures2 = pRenderer->CreatePngTexture("./Textures/Test2.png");
	backgroundTextures = pRenderer->CreatePngTexture("./Textures/background.png");
	characterTextures1 = pRenderer->CreatePngTexture("./Textures/character1.png");
	characterTextures2 = pRenderer->CreatePngTexture("./Textures/character2.png");
	bulletTextures1 = pRenderer->CreatePngTexture("./Textures/Bullet1.png");
	bulletTextures2 = pRenderer->CreatePngTexture("./Textures/Bullet2.png");
	snowTextures = pRenderer->CreatePngTexture("./Textures/snow2.png");

	soundBG = m_sound->CreateSound("./Dependencies/SoundSamples/MF-W-90.XM");
	soundExplosion = m_sound->CreateSound("./Dependencies/SoundSamples/explosion.wav");
	m_sound->PlaySound(soundBG, true, 0.2f);

	NewBuilding(100, 75, Team::Team_1);
	NewBuilding(250, 100, Team::Team_1);
	NewBuilding(400, 75, Team::Team_1);

	NewBuilding(100, 725, Team::Team_2);
	NewBuilding(250, 700, Team::Team_2);
	NewBuilding(400, 725, Team::Team_2);
}

void SceneManager::Update(float time)
{
	updateTime = min(updateTime += time,1.0f);
	createTime = min(createTime += time,2.5f);
	if (updateTime >= 1.0f)
	{
		float x = RangeRandom(0, windowW * 2);
		float y = RangeRandom(0, windowH);
		NewCharacter(x, y, Team::Team_1);
		updateTime = 0;
	}
	CollisionObject();
	for (int i = 0; i< manager.size();i++)
	{
		if (manager[i]->GetLife() <= 0)
		{
			manager.erase(manager.begin() + i);
			break;
		}
		else if (manager[i]->GetState() == OBJECT_BUILDING)
		{
			if (manager[i]->GetAttackDelay() >= 1.0f)
			{
				POS temp = manager[i]->GetPos();
				NewBullet(temp.x + windowW, -temp.y + windowH, manager[i]->GetTeam());
				manager[i]->SetAttackDelay(0);
				cout << "bullet : " << ++debug << " index : " << manager.size() - 1 << endl;
			}
		}
		else if (manager[i]->GetState() == OBJECT_CHARACTER)
		{
			if (manager[i]->GetAttackDelay() >= 1.0f)
			{
				POS temp = manager[i]->GetPos();
				NewArrow(temp.x + windowW, -temp.y + windowH, manager[i]->GetID(),manager[i]->GetTeam());
				manager[i]->SetAttackDelay(0);
			}
		}
		else if (i >= manager.size())
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

void SceneManager::NewBuilding(int x, int y, Team team)
{
	if (team == Team::Team_1)
		manager.push_back(new Object(pRenderer, POS(x - windowW, -y + windowH, 0), COLORS(1, 1, 1, 1), BUILDING_SIZE));
	else if (team == Team::Team_2)
		manager.push_back(new Object(pRenderer, POS(x - windowW, -y + windowH, 0), COLORS(1, 1, 1, 1), BUILDING_SIZE));
	int index = manager.size() - 1;
	manager[index]->SetLSSD(BUILDING_HP, BUILDING_SPEED, OBJECT_BUILDING, POS(0, 0, 0));
	manager[index]->SetTeam(team);
	manager[index]->SetLevel(LEVEL_SKY);
}

void SceneManager::NewCharacter(int x, int y, Team team)
{
	if (team == Team::Team_1)
		manager.push_back(new Object(pRenderer, POS(x - windowW, -y + windowH, 0), COLORS(0, 0, 0, 1), CHARACTER_SIZE));
	else if (team == Team::Team_2)
		manager.push_back(new Object(pRenderer, POS(x - windowW, -y + windowH, 0), COLORS(0, 0, 0, 1), CHARACTER_SIZE));
	int index = manager.size() - 1;
	float dx = GetRandom();
	float dy = GetRandom();
	manager[index]->SetLSSD(CHARACTER_HP, CHARACTER_SPEED, OBJECT_CHARACTER, POS(dx, dy, 0));
	manager[index]->SetID(characterID);
	manager[index]->SetTeam(team);
	manager[index]->SetLevel(LEVEL_GROUND);
	characterID++;
}

void SceneManager::NewBullet(int x, int y, Team team)
{
	if (team == Team::Team_1)
	{
		manager.push_back(new Object(pRenderer, POS(x - windowW, -y + windowH, 0), COLORS(1, 1, 1, 1), BULLET_SIZE));
		cout << "call newBullet Team_1" << endl;
	}
	else if (team == Team::Team_2)
	{
		manager.push_back(new Object(pRenderer, POS(x - windowW, -y + windowH, 0), COLORS(1, 1, 1, 1), BULLET_SIZE));
		cout << "call newBullet Team_2" << endl;
	}
	int index = manager.size() - 1;
	float dx = GetRandom();
	float dy = GetRandom();
	manager[index]->SetLSSD(BULLET_HP, BULLET_SPEED, OBJECT_BULLET, POS(dx, dy, 0));
	manager[index]->SetTeam(team);
	manager[index]->SetLevel(LEVEL_UNDERGROUND);
}

void SceneManager::NewArrow(int x, int y, int id, Team team)
{
	if (team == Team::Team_1)
		manager.push_back(new Object(pRenderer, POS(x - windowW, -y + windowH, 0), COLORS(0.5, 0.2, 0.7, 1), ARROW_SIZE));
	else if (team == Team::Team_2)
		manager.push_back(new Object(pRenderer, POS(x - windowW, -y + windowH, 0), COLORS(1, 1, 0, 1), ARROW_SIZE));
	int index = manager.size() - 1;
	float dx = GetRandom();
	float dy = GetRandom();
	manager[index]->SetLSSD(ARROW_HP, ARROW_SPEED, OBJECT_ARROW, POS(dx, dy, 0));
	manager[index]->SetID(id);
	manager[index]->SetTeam(team);
	manager[index]->SetLevel(LEVEL_UNDERGROUND);
}

void SceneManager::Draw(float time)
{
	pRenderer->DrawTexturedRect(0, 0, 0, windowH * 2, 1, 1, 1, 1, backgroundTextures, LEVEL_BACKGROUND);
	pRenderer->DrawParticleClimate(0, 0, 0, 1, 1, 1, 1, 1, -0.2, -0.5, snowTextures, cloudTime, 0.01);

	for (auto &d : manager)
	{
		switch (d->GetState())
		{
		case OBJECT_BUILDING: 
			if (d->GetTeam() == Team::Team_1) d->DrawObject(buildingTextures1,time);
			else if (d->GetTeam() == Team::Team_2) d->DrawObject(buildingTextures2,time);
			break;
		case OBJECT_CHARACTER:  
			if (d->GetTeam() == Team::Team_1) d->DrawObject(characterTextures1,time);
			else if (d->GetTeam() == Team::Team_2)  d->DrawObject(characterTextures2,time);
			break;
		case OBJECT_BULLET:
			if (d->GetTeam() == Team::Team_1) d->DrawObject(bulletTextures1,time);
			else if (d->GetTeam() == Team::Team_2)  d->DrawObject(bulletTextures2,time);
			break;
		case OBJECT_ARROW:d->DrawObject(0,time); break;
		}
	}

	cloudTime += time;
}

void SceneManager::CollisionObject()
{
	if(manager.size() > 1)
	for (int i = 0; i < manager.size(); ++i)
	{
		POS tempObj1 = manager[i]->GetPos();
		float tempSize1 = manager[i]->GetSize()/2.0f;

		if (tempObj1.x <-windowW || tempObj1.x > windowW)
		{
			if (manager[i]->GetState() == OBJECT_BULLET || manager[i]->GetState() == OBJECT_ARROW)
			{
				manager.erase(manager.begin() + i);
				i--;
			}
			else
			{
				POS temp = manager[i]->GetDirection();
				manager[i]->SetDirection(POS(-temp.x, temp.y, 0));
				manager[i]->MoveUpdate(1.0f / 60.0f);
			}
		}
		if (tempObj1.y < -windowH || tempObj1.y > windowH)
		{
			if (manager[i]->GetState() == OBJECT_BULLET || manager[i]->GetState() == OBJECT_ARROW)
			{
				manager.erase(manager.begin() + i);
				i--;
			}
			else
			{
				POS temp = manager[i]->GetDirection();
				manager[i]->SetDirection(POS(temp.x, -temp.y, 0));
				manager[i]->MoveUpdate(1.0f / 60.0f);
			}
		}
		for (int j = 0; j < manager.size(); ++j)
		{
			POS tempObj2 = manager[j]->GetPos();
			float tempSize2 = manager[j]->GetSize()/2.0f;

			if(i != j)
				if (tempObj1.x - tempSize1 <= tempObj2.x - tempSize2 && tempObj2.x - tempSize2 <= tempObj1.x + tempSize1)
				{
					if (tempObj1.y - tempSize1 <= tempObj2.y - tempSize2 && tempObj2.y - tempSize2 <= tempObj1.y + tempSize1)
					{
						j = CollisionEffect(i, j);
					}
					else if (tempObj1.y - tempSize1 <= tempObj2.y + tempSize2 && tempObj2.y + tempSize2 <= tempObj1.y + tempSize1)
					{
						j = CollisionEffect(i, j);
					}
				}
				else if (tempObj1.x - tempSize1 <= tempObj2.x + tempSize2 && tempObj2.x + tempSize2 <= tempObj1.x + tempSize1)
				{
					if (tempObj1.y - tempSize1 <= tempObj2.y - tempSize2 && tempObj2.y - tempSize2 <= tempObj1.y + tempSize1)
					{
						j = CollisionEffect(i, j);
					}
					else if (tempObj1.y - tempSize1 <= tempObj2.y + tempSize2 && tempObj2.y + tempSize2 <= tempObj1.y + tempSize1)
					{
						j = CollisionEffect(i, j);
					}
				}
			if (j >= manager.size() || i >= manager.size())
				break;
		}
		if (manager.size() < 2)
		{
			break;
		}
	}
}

void SceneManager::CreateCharacter(int x, int y)
{
	if (createTime >= 2.0f && y >= windowH) {
		NewCharacter(x, y, Team::Team_2);
		createTime = 0;
	}
}

int SceneManager::CollisionEffect(int Obj1, int Obj2)
{
	if(manager[Obj1]->GetTeam() != manager[Obj2]->GetTeam())
	{
		if (manager[Obj1]->GetState() == OBJECT_BUILDING &&
			(manager[Obj2]->GetState() == OBJECT_CHARACTER || manager[Obj2]->GetState() == OBJECT_ARROW))
		{
			manager[Obj1]->SetLife(manager[Obj1]->GetLife() - manager[Obj2]->GetLife());
			manager.erase(manager.begin() + Obj2);
			m_sound->PlaySound(soundExplosion, false, 0.6f);
			return (Obj2 - 1);
		}
		else if (manager[Obj1]->GetState() == OBJECT_BUILDING && manager[Obj2]->GetState() == OBJECT_BULLET)
		{
			manager[Obj1]->SetLife(manager[Obj1]->GetLife() - manager[Obj2]->GetLife());
			manager.erase(manager.begin() + Obj2);
			m_sound->PlaySound(soundExplosion, false, 0.4f);
			return (Obj2 - 1);
		}
		else if (manager[Obj1]->GetState() == OBJECT_CHARACTER && manager[Obj2]->GetState() == OBJECT_BULLET)
		{
			manager[Obj1]->SetLife(manager[Obj1]->GetLife() - manager[Obj2]->GetLife());
			manager.erase(manager.begin() + Obj2);
			m_sound->PlaySound(soundExplosion, false, 0.2f);
			return (Obj2 - 1);
		}
		else if (manager[Obj1]->GetState() == OBJECT_CHARACTER && manager[Obj2]->GetState() == OBJECT_ARROW)
		{
			manager[Obj1]->SetLife(manager[Obj1]->GetLife() - manager[Obj2]->GetLife());
			manager.erase(manager.begin() + Obj2);
			m_sound->PlaySound(soundExplosion, false, 0.3f);
			return (Obj2 - 1);
		}
	}
	return (Obj2);
}

float SceneManager::GetRandom()
{
	random_device rn;
	mt19937_64 rnd(rn());

	uniform_real_distribution<float> range(-1, 1);

	return range (rnd);
}

float SceneManager::RangeRandom(int a, int b)
{
	random_device rn;
	mt19937_64 rnd(rn());

	uniform_real_distribution<float> range(a, b);

	return range(rnd);
}

SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
	manager.~vector();
}
