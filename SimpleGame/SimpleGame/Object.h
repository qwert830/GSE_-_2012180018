#pragma once

class Renderer;

struct POS {
public :
	float x, y, z;
	POS() {}
	POS(float x, float y, float z) : x(x),y(y),z(z) {}
	POS operator *(int a) { x *= a, y *= a, z *= a; return POS(x,y,z); }
	POS& operator +=(POS temp) { x += temp.x; y += temp.y; z += temp.z; return POS(x, y, z); }
	POS operator =(POS temp) { x = temp.x; y = temp.y; z = temp.z; return POS(x, y, z); }
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
	POS			pos;		// 생성위치
	POS			direction;  // 이동방향
	COLORS		color;		// 색상
	float		size;		// 사이즈 
	int			state;		// 상태
	
	float		speed;		// 이동속도
	float		weight;		// 무게
	
	Renderer*	renderer;	// 렌더러 포인터

public:
	Object();
	Object(float xpos, float ypos, float zpos, float size) : pos(xpos,ypos,zpos),size(size) {}
	Object(Renderer* gRenderer, POS position, COLORS colors, float size);
	~Object();

	void	SetPos(float x, float y, float z);
	void	SetPos(POS position);
	void	SetSize(float size);
	void	SetColor(float r, float g, float b, float a);
	void	SetColor(COLORS color);
	void	SetState(int state);
	void	SetRender(Renderer* pRenderer);
	void	SetDirection(POS direction);
	void	SetSpeed(float inputSpeed);
	void	SetWeight(float inputWeight);
	void	AddSpeed(float addSpeed);

	COLORS	NormalizationColor(COLORS color); // 0~255의 값을 0~1로 정규화
	
	int		GetState() { return state; }
	float	GetSize() { return size; }
	float	GetSpeed() { return speed; }
	float   GetWeight() { return weight; }
	POS		GetPos() { return pos; }
	COLORS	GetColor() { return color; }
	POS		GetDirection() { return direction; }

	void	DrawObject();
	void	MoveUpdate(float time);
	void	Update(float time);
};

