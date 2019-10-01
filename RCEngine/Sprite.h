#pragma once
#include <string>
#include "Vector2.h"
#include "BitmapLoader.h"

class Sprite {
public:
	Sprite();
	Sprite(const Bitmap& bitmap);
	~Sprite();

	bool LoadSprite(const std::string file, bool calibrateRGBtoRCColour = false, const COLORREF * palette = nullptr);
	const Bitmap* GetSprite() const;

	void ConvertToRCColour();

private:
	
	Bitmap* m_bitmap;
};

