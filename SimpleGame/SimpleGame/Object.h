#pragma once

class Object
{
private:
	float x, y, z, s;
	float r, g, b, a;
	float state;
public:
	Object();
	Object(float xpos, float ypos, float zpos, float size) : x(xpos), y(ypos), z(zpos), s(size) {}
	~Object();

	void SetPos();
	void SetSize();
	void SetColor();
	void NormalizationColor();
	void DrawObject();

};

