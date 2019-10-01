#pragma once
#include "Object2D.h"

class RCEngine;
class Line : public Object2D {
public:
	Line();
	Line(Vector2 start, Vector2 end, short character, int colour);
	~Line();

	virtual Object2D * GetType() override;

	Vector2 GetNormal() const;
	float GetSize() const;

private:

	Vector2 m_start;
	Vector2 m_end;
	Vector2 m_normal;
	float m_size;

	// Inherited via Object2D
	virtual void Render(RCEngine & engine) override;
};

