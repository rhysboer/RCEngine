#pragma once
#include "Object2D.h"

class RCEngine;
class Circle : public Object2D {
public:
	Circle();
	Circle(Vector2 pos, float radius, short character, int colour);
	~Circle();

	void SetRadius();
	float GetRadius() const;

	virtual Object2D * GetType() override;
private:

	float m_radius;

	// Inherited via Object2D
	virtual void Render(RCEngine & engine) override;

};

