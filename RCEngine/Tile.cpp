#include "Tile.h"

/*
Tile::Tile() {
	m_position = Vector2(0, 0);
	m_character = 0x2588;
	m_isCollidable = false;
}
*/

Tile::Tile(const Sprite* const sprite, Vector2 pos, short character) {
	m_sprite = sprite;
	m_position = pos;
	m_character = character;
	m_isCollidable = false;
}

Tile::~Tile() {
}

Sprite const * Tile::GetSprite() const {
	return m_sprite;
}

Vector2 Tile::GetPosition() const {
	return m_position;
}

short Tile::GetCharacter() const {
	return m_character;
}

void Tile::SetPosition(const Vector2 vec) {
	m_position = vec;
}

void Tile::SetCharacter(const short character) {
	m_character = character;
}

void Tile::SetSprite(const Sprite const * sprite) {
	m_sprite = sprite;
}

void Tile::SetCollision(bool collision) {
	m_isCollidable = collision;
}

void Tile::Translate(const Vector2 vec) {
	m_position = vec;
}
