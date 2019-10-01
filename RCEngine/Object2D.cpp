#include "Object2D.h"
#include "RCEngine.h"

Object2D::Object2D() {
}

Object2D::Object2D(const short character, const int colour, const CollisionType type) {
	this->m_character = character;
	this->m_colour = colour;
	this->m_collisionType = type;
	this->m_mass = 1.0f;
	this->m_scale = Vector2(1, 1);
	this->m_acceleration = Vector2(0, 0);
	this->m_velocity = Vector2(0, 0);
	this->m_drag = Vector2(0.9999f, 0.9999f);

	// Default collision is off
	this->m_isCollidable = false;
	this->m_usePhysics = false;
}

Object2D::~Object2D() {
}

void Object2D::FixedUpdate(const Vector2 gravity) {
	m_acceleration += gravity;// *RCEngine::DeltaTime();
	m_velocity += m_acceleration *RCEngine::DeltaTime();
	m_origin += m_velocity * RCEngine::DeltaTime();

	m_acceleration = Vector2();
}

void Object2D::Rotate(const float degrees) {
	float rad = (degrees * PI) / 180;

	for (int i = 0; i < m_verts.size(); i++) {
		Vector2 vec = m_verts[i];

		float dCos = cos(rad);
		float dSin = sin(rad);

		vec.X = m_verts[i].X * dCos - m_verts[i].Y * dSin;
		vec.Y = m_verts[i].Y * dCos + m_verts[i].X * dSin;

		m_verts[i] = vec;
	}
}

void Object2D::Translate(const Vector2 trans) {
	m_origin += trans;
}

void Object2D::Scale(const Vector2 scale) {
	this->m_scale += scale;
}

void Object2D::SetPoints(const std::vector<Vector2> points) {
	m_verts = Vertices(points);
}

void Object2D::SetPosition(const Vector2 pos) {
	m_origin = pos;
}

void Object2D::SetCharacter(const char c) {
	m_character = c;
}

void Object2D::SetColour(const int colour) {
	this->m_colour = colour;
}

void Object2D::SetVelocity(const Vector2 vel) {
	this->m_velocity = vel;
}

std::vector<Vector2> Object2D::GetDrawPoints() {
	return m_verts;
}

Vector2 Object2D::GetPosition() const {
	return m_origin;
}

Vector2 Object2D::GetVelocity() const {
	return m_velocity;
}

void Object2D::AddForce(const Vector2 force) {
	this->m_velocity += force;
}

const short Object2D::GetCharacter() {
	return m_character;
}

const int Object2D::GetColour() {
	return m_colour;
}


