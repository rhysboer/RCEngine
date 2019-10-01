#pragma once
#include "Sprite.h"
#include "Vector2.h"
#include "BitmapLoader.h"

class Tile {
public:
	//Tile();
	Tile(const Sprite const * sprite, Vector2 pos, short character);
	~Tile();

	Sprite const * GetSprite() const;
	Vector2 GetPosition() const;
	short GetCharacter() const;

	void SetPosition(const Vector2 vec);
	void SetCharacter(const short character);
	void SetSprite(const Sprite const * sprite);
	void SetCollision(bool collision);

	void Translate(const Vector2 vec);

private:

	Sprite const * m_sprite;
	Vector2 m_position;
	short m_character;

	bool m_isCollidable;
};

