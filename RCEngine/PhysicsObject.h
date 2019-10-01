#pragma once
#include <vector>
#include <cmath>
#include "Vector2.h"

typedef std::vector<Vector2> Vertices;

struct VectorShapes {
public:
	static Vertices Square(const int width = 5, const int height = 5) {
		Vertices square = {
			Vector2(-width, height),
			Vector2(width, height),
			Vector2(width, -height),
			Vector2(-width, -height),
		};

		return square;
	}

	static Vertices Triangle(const int width = 5, const int height = 5) {
		Vertices triangle = {
			Vector2(-width, height), // Left
			Vector2(0, -height), // Top
			Vector2(width, height) // Right
		};

		return triangle;
	}
};

enum CollisionType {
	PLANE,
	SPHERE,
	AABB,
	//POINTS


	COUNT // Must be last
};

class PhysicsObject {
public:
	PhysicsObject();
	virtual ~PhysicsObject();
	
	CollisionType GetCollisionType() const;

	bool IsUsingPhysics() const;
	bool IsCollidable() const;

	// Setters
	void UseCollision(bool isCollidable);
	void UsePhysics(bool enable);
	void SetMass(const float mass);

protected:

	//  Collision Settings
	CollisionType m_collisionType;
	bool m_isCollidable;

	// Physic Settings
	bool m_usePhysics;
	float m_mass;
};

