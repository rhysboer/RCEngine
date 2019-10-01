#pragma once
#include "Object2D.h"

class RCEngine;
class Square : public Object2D {
public:
	Square();
	Square(Vector2 pos, Vector2 size, short character, int colour);
	~Square();

	Vertices GetAABB() const;

	virtual Object2D* GetType() override;

private:
	// Inherited via Object2D
	virtual void Render(RCEngine & engine) override;

	Vector2 size;

	// Collision AABB
	Vertices aabb;
};

