#include "Line.h"
#include "RCEngine.h"


Line::Line() : Object2D(0x2588, PaletteIndex::FG_WHITE, CollisionType::PLANE) {
	this->m_start = Vector2(-5, 0);
	this->m_start = Vector2(5, 0);
	this->m_origin = Vector2(0, 0);
	this->m_normal = Vector2::Normal(Vector2(-5, 0), Vector2(5, 0));
	this->m_size = Vector2::Distance(this->m_start, this->m_origin);

	Vertices points = { this->m_start, this->m_end };
	SetPoints(points);
}

Line::Line(Vector2 start, Vector2 end, short character, int colour) : Object2D(character, colour, CollisionType::PLANE) {
	this->m_origin = (start / 2) + (end / 2);
	this->m_start = start;
	this->m_end = end;
	this->m_normal = Vector2::Normal(start, end);
	this->m_size = Vector2::Distance(start, this->m_origin);

	Vertices points = { start, end };
	SetPoints(points);
}

Line::~Line() {
}

void Line::Render(RCEngine & engine) {
	engine.RCDrawLine(
		m_verts[0].X, m_verts[0].Y,
		m_verts[1].X, m_verts[1].Y,
		m_character, m_colour);

	Vector2 dot = Vector2::Normal(m_start, m_end);
	dot.Normalise();
	engine.RCDrawLine(m_origin.X, m_origin.Y, m_origin.X + (dot.X * 10), m_origin.Y + (dot.Y * 10), m_character, PaletteIndex::FG_RED);
}

Object2D * Line::GetType() {
	return this;
}

Vector2 Line::GetNormal() const {
	return m_normal;
}

float Line::GetSize() const {
	return this->m_size;
}
