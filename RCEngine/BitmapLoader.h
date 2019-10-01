#pragma once
#include <vector>
#include <Windows.h>
#include "ColourPalette.h"

// RGB and colourIndex for each pixel of the bitmap
typedef struct ColourVec {
	ColourVec() {}
	ColourVec(int r, int g, int b) : red(r), green(g), blue(b), colourIndex(1) {};

	int red;
	int green;
	int blue;
	int colourIndex; // Colour index for RCColours
} PIXEL;

// Data of a bitmap file
typedef struct BitmapFile{
	int width;
	int height;
	std::vector<PIXEL*> pixels = std::vector<PIXEL*>();

	// Pixels will need their colourIndex recalibrated each time the palette changes
	void ConvertPixelsToRCColour();
} Bitmap;

//typedef std::pair<PIXEL, int> RCColour;

class RCEngine;
class ColourPalette;
class BitmapLoader {
public:
	~BitmapLoader();

	// File: Path to the Bitmap, calibrateRGBtoRCCOlour: Convert RBG to nearest colour in palette, palette: palette to pick nearest colour from, nullptr for default engine palette
	static Bitmap* LoadBMP(const char* file, bool calibrateRGBtoRCColour = false, const COLORREF * palette = nullptr);
	static int RGBtoRCColour(int r, int g, int b, const COLORREF * palette);
	static int RGBtoRCColour(PIXEL pixel, const COLORREF* palette);

	static void DestroyBitmap(Bitmap* bitmap);

private:

	BitmapLoader();
};

