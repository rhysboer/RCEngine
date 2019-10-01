#pragma once
#include <vector>
#include "Object2D.h"

/*

Position - Where your object is
Velocity - The direction and rate your object is changing its position
Acceleration - The direction and rate your object is changing its velocity

Position += Velocity * dt
Velocity += acceleration * dt
Acceleration += vector * dt

*/

typedef bool(*fn)(Object2D*, Object2D*);

class RCEngine;
class PhysicsManager {
public:
	PhysicsManager();
	~PhysicsManager();

	void Update(std::vector<Object2D*>& objects);
	
	void SetGravity(const Vector2 gravity);
	void EnablePhysics(const bool usePhysics);

#pragma region Collision Checks

	static bool Plane2Plane(Object2D* obj1, Object2D* obj2) { return false; };	/* To Do */
	static bool Plane2Sphere(Object2D* obj1, Object2D* obj2) { return false; }; /* To Do */
	static bool Plane2AABB(Object2D* obj1, Object2D* obj2) { return false; }; /* To Do */

	static bool Sphere2Plane(Object2D* obj1, Object2D* obj2);
	static bool Sphere2Sphere(Object2D* obj1, Object2D* obj2);
	static bool Sphere2AABB(Object2D* obj1, Object2D* obj2) { return false; }; /* To Do */

	static bool AABB2Plane(Object2D* obj1, Object2D* obj2) { return false; }; /* To Do */
	static bool AABB2Sphere(Object2D* obj1, Object2D* obj2) { return false; }; /* To Do */
	static bool AABB2AABB(Object2D* obj1, Object2D* obj2) { return false; }; /* To Do */

#pragma endregion


private:

	void CheckCollision(std::vector<Object2D*>& objects);

	float m_timestep;
	bool m_isOn;
	Vector2 m_gravity;
};

