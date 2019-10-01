#include "SpriteSheet.h"

SpriteSheet::SpriteSheet() {
	m_sprites = std::vector<Sprite*>();
}

SpriteSheet::~SpriteSheet() {
	// TO DO: Delete m_sprites
}

bool SpriteSheet::LoadSpriteSheet(int totalTilesWidth, int totalTilesHeight, int sizeWidth, int sizeHeight, const char* path, const COLORREF* palette) {
	if (path) {
		bmp = BitmapLoader::LoadBMP(path, true, (palette == nullptr) ? ColourPalette::DEFAULT_COLOURS : palette);

		if (bmp) {

			m_tileSize = Vector2(sizeWidth, sizeHeight);
			
			for (int tileY = 0; tileY < totalTilesHeight; tileY++) {
				for (int tileX = 0; tileX < totalTilesWidth; tileX++) {
					Bitmap* newBitmap = new Bitmap;
					newBitmap->height = sizeHeight;
					newBitmap->width = sizeWidth;

					for (int y = 0; y < sizeHeight; y++) {
						for (int x = 0; x < sizeWidth; x++) {
							int index = ((y + (tileY * sizeWidth)) * bmp->width) + x + (tileX * sizeWidth);
							PIXEL* pixel = bmp->pixels[index];
							newBitmap->pixels.push_back(pixel);
						}
					}

					Sprite* sprite = new Sprite(*newBitmap);
					m_sprites.push_back(sprite);
				}
			}

			return true;
		}
	}

	return false;
}

const Sprite * SpriteSheet::GetSprite(int index) const {
	return m_sprites[index];
}

Vector2 SpriteSheet::GetTileSize() const {
	return m_tileSize;
}
