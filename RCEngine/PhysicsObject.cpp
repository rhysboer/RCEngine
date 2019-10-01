#include "PhysicsObject.h"

PhysicsObject::PhysicsObject() {
}

PhysicsObject::~PhysicsObject() {
}

bool PhysicsObject::IsUsingPhysics() const {
	return m_usePhysics;
}

bool PhysicsObject::IsCollidable() const {
	return m_isCollidable;
}

CollisionType PhysicsObject::GetCollisionType() const {
	return m_collisionType;
}

void PhysicsObject::UseCollision(bool isCollidable) {
	m_isCollidable = isCollidable;
}

void PhysicsObject::UsePhysics(bool enable) {
	m_usePhysics = enable;
}

void PhysicsObject::SetMass(const float mass) {
	this->m_mass = mass;
}
