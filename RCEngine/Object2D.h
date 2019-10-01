#pragma once
#include "PhysicsObject.h"

class RCEngine;
class Object2D : public PhysicsObject {
public:
	Object2D();
	Object2D(const short character, const int colour, const CollisionType type);
	virtual ~Object2D();

	// Sets
	void Rotate(const float degrees);
	void Translate(const Vector2 trans);
	void Scale(const Vector2 scale);

	void SetRotation(float degrees);
	void SetPoints(const std::vector<Vector2> points);
	void SetPosition(const Vector2 pos);
	void SetCharacter(const char c);
	void SetColour(const int colour);
	void SetVelocity(const Vector2 vel);

	// Gets
	std::vector<Vector2> GetDrawPoints();
	const short GetCharacter();
	const int GetColour();
	Vector2 GetPosition() const;
	Vector2 GetVelocity() const;

	void AddForce(const Vector2 force);

	// Virtual
	virtual void Render(RCEngine& engine) = 0;
	virtual Object2D* GetType() = 0;

	virtual void FixedUpdate(const Vector2 gravity);

protected:

	Vertices m_verts;		// Points of the object
	Vector2 m_origin;		// Position
	Vector2 m_scale;		// objects scale
	Vector2 m_velocity;		// Velocity of the object
	Vector2 m_acceleration; // Acceration
	Vector2 m_drag;			// Drag / Air resistence

	short m_character;		// Character
	int m_colour;			// Objects colour
};

