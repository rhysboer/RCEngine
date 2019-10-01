#pragma once
#include <vector>
#include "Object2D.h"
#include "Circle.h"
#include "Square.h"
#include "Line.h"

class RCEngine;
class PhysicsManager;
class ObjectManager {
public:
	ObjectManager();
	~ObjectManager();

	Object2D* CreateCircle(Vector2 pos, float radius, const short character, const int colour);
	Object2D* CreateSquare(Vector2 pos, Vector2 size, const short character, const int colour);
	Object2D* CreateLine(Vector2 start, Vector2 end, const short character, const int colour);
	
	void UpdateObjects();
	void DestroyObject(Object2D& object);

	void Render(RCEngine& engine);

	void DestroyAll();
private:

	PhysicsManager* m_physics;

	std::vector<Object2D*> m_objects;
};

