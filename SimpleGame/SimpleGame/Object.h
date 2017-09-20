#pragma once

class Renderer;

struct POS {
public :
	float x, y, z;
	POS() {}
	POS(float x, float y, float z) : x(x),y(y),z(z) {}
};

struct COLORS {
public:
	float r, g, b, a;
	COLORS() { r = 1; g = 0; b = 0; a = 1; }
	COLORS(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}
};
class Object
{
private:
	POS			pos;    // 생성위치
	COLORS		color; // 색상
	float		size; // 사이즈 
	int			state;  // 추후 사용 될 상태

	Renderer*	renderer; // 렌더러 포인터

public:
	Object();
	Object(float xpos, float ypos, float zpos, float size) : pos(xpos,ypos,zpos),size(size) {}
	~Object();

	void	SetPos(float x, float y, float z);
	void	SetPos(POS position);
	void	SetSize(float size);
	void	SetColor(float r, float g, float b, float a);
	void	SetColor(COLORS color);
	void	SetState(int state);
	void	SetRender(Renderer* pRenderer);

	COLORS	NormalizationColor(COLORS color);
	
	int		GetState() { return state; }
	float	GetSize() { return size; }
	POS		GetPos() { return pos; }
	COLORS	GetColor() { return color; }

	void	DrawObject();
};

