#include "Sprite.h"

Sprite::Sprite() {
	m_bitmap = nullptr;
}

Sprite::Sprite(const Bitmap & bitmap) {
	m_bitmap = new Bitmap;
	m_bitmap->height = bitmap.height;
	m_bitmap->width = bitmap.width;
	m_bitmap->pixels = std::vector<PIXEL*>(bitmap.pixels);
}

Sprite::~Sprite() {
	BitmapLoader::DestroyBitmap(m_bitmap);
}

bool Sprite::LoadSprite(const std::string file, bool calibrateRGBtoRCColour, const COLORREF * palette) {
	m_bitmap = BitmapLoader::LoadBMP(file.c_str(), calibrateRGBtoRCColour, palette);
	if (m_bitmap) {
		return true;
	}

	return false;
}

const Bitmap * Sprite::GetSprite() const {
	return m_bitmap;
}

void Sprite::ConvertToRCColour() {
	if (m_bitmap != nullptr) {
		m_bitmap->ConvertPixelsToRCColour();
	}
}
