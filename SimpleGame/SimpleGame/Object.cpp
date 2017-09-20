#include "stdafx.h"
#include "Object.h"
#include "Renderer.h"

Object::Object()
{
	//test init;
	pos = { 10,10,0 };
	size = 10;
	color = { 1,0,0,1 };
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

void Object::SetSpeed(float inputSpeed)
{
	speed = inputSpeed;
}

void Object::SetWeight(float inputWeight)
{
	weight = inputWeight;
}

void Object::AddSpeed(float addSpeed)
{
	speed += addSpeed;
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
