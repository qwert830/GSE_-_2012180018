#include "stdafx.h"
#include "Object.h"
#include "Renderer.h"

Object::Object()
{

}

Object::Object(Renderer * gRenderer, POS position, COLORS colors, float size)
{
	SetRender(gRenderer);
	SetPos(position);
	SetColor(colors);
	SetSize(size);
	SetLifeTime(5);
}

Object::Object(Renderer * gRenderer, POS position, POS direction, COLORS colors, float size)
{
	SetRender(gRenderer);
	SetPos(position);
	SetColor(colors);
	SetSize(size);
	SetDirection(direction);
	SetLifeTime(5);
	SetSpeed(rand()%100 + 50);
}

Object::~Object()
{
}

void Object::SetPos(float x, float y, float z)
{
	pos.x = x;
	pos.y = y;
	pos.z = z;
}

void Object::SetPos(POS position)
{
	this->pos = position;
}

void Object::SetSize(float size)
{
	this->size = size;
}

void Object::SetColor(float r, float g, float b, float a)
{
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
}

void Object::SetColor(COLORS color)
{
	this->color = color;
}

void Object::SetState(int state)
{
	this->state = state;
}

void Object::SetRender(Renderer* pRenderer)
{
	renderer = pRenderer;
}

void Object::SetDirection(POS direction)
{
	float length = fabs(direction.x) + fabs(direction.y);
	if (length == 0)
	{
		this->direction = { 0,0,0 };
		return;
	}
	direction.x = (float)direction.x / length;
	direction.y = (float)direction.y / length;
	this->direction = direction;
}

void Object::SetSpeed(float inputSpeed)
{
	speed = inputSpeed;
}

void Object::SetWeight(float inputWeight)
{
	weight = inputWeight;
}

void Object::SetLife(float life)
{
	this->life = life;
}

void Object::SetLifeTime(float time)
{
	lifeTime = time;
}

void Object::SetAttackDelay(float time)
{
	attackDelay = time;
}

void Object::AddSpeed(float addSpeed)
{
	speed += addSpeed;
}

void Object::SetLSSD(float life, float speed, int state, POS direction)
{
	this->life = life;
	this->speed = speed;
	this->state = state;
	SetDirection(direction);
}

COLORS Object::NormalizationColor(COLORS color)
{
	color.r = color.r / 255;
	color.g = color.g / 255;
	color.b = color.b / 255;
	color.a = color.a / 255;
	return color;
}

void Object::DrawObject()
{
	renderer->DrawSolidRect(pos.x, pos.y, pos.z, size, color.r, color.g, color.b, color.a);
}


void Object::MoveUpdate(float time)
{
	pos += direction*speed*time;
}

void Object::Update(float time)
{
	if (state != OBJECT_BUILDING)
		lifeTime -= time;
	if (state == OBJECT_BUILDING)
	{
		attackDelay += time;
	}
	MoveUpdate(time);
}
