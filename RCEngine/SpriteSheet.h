#pragma once
#include "BitmapLoader.h"
#include "Sprite.h"

class SpriteSheet {
public:
	SpriteSheet();
	~SpriteSheet();

	// totalTlesWidth & totalTilesHeight are the total amount of tiles in the sprite | width & height the are size of individual tiles
	bool LoadSpriteSheet(int totalTilesWidth, int totalTilesHeight, int sizeWidth, int sizeheight, const char* path, const COLORREF* palette = nullptr);
	const Sprite* GetSprite(int index) const;
	Vector2 GetTileSize() const;

private:

	Vector2 m_tileSize;

	Bitmap* bmp = nullptr;
	std::vector<Sprite*> m_sprites;
};

