#include "Square.h"
#include "RCEngine.h"


Square::Square() : Object2D(0x2588, PaletteIndex::FG_WHITE, CollisionType::AABB) {
	this->m_origin = Vector2(0, 0);
	this->size = Vector2(3, 3);
	this->m_isCollidable = false;

	SetPoints(VectorShapes::Square(size.X, size.Y));
	// Generate AABB
}

Square::Square(Vector2 pos, Vector2 size, short character, int colour) : Object2D(character, colour, CollisionType::AABB) {
	this->m_origin = pos;
	this->size = size;

	SetPoints(VectorShapes::Square(size.X, size.Y));
	// TODO Generate AABB
}

Square::~Square() {
}

Vertices Square::GetAABB() const {
	return aabb;
}

Object2D * Square::GetType() {
	return this;
}

void Square::Render(RCEngine & engine) {
	for (int i = 0; i < m_verts.size(); i++) {
		Vector2 point1 = m_verts[i];
		Vector2 point2 = (i >= m_verts.size() - 1) ? m_verts[0] : m_verts[i + 1];

		engine.RCDrawLine(
			(point1.X * m_scale.X) + m_origin.X, (point1.Y * m_scale.Y) + m_origin.Y,
			(point2.X * m_scale.X) + m_origin.X, (point2.Y * m_scale.Y) + m_origin.Y,
			m_character, m_colour);

		if (m_verts.size() <= 2) break;
	}
}
