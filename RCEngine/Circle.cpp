#include "Circle.h"
#include "RCEngine.h"

Circle::Circle() : Object2D(0x2588, PaletteIndex::FG_WHITE, CollisionType::SPHERE) {
	this->m_origin = Vector2(0, 0);
	this->m_radius = 5.0f;
}

Circle::Circle(Vector2 pos, float radius, short character, int colour) : Object2D(character, colour, CollisionType::SPHERE) {
	this->m_origin = pos;
	this->m_radius = radius;
}

Circle::~Circle() {
}

void Circle::Render(RCEngine & engine) {
	engine.RCDrawCircle(m_origin.X, m_origin.Y, abs(m_radius + m_scale.X), m_character, m_colour);
}

float Circle::GetRadius() const {
	return m_radius;
}

Object2D * Circle::GetType() {
	return this;
}
