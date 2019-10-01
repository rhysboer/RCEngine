#include "BitmapLoader.h"
#include "RCEngine.h"
#include "ColourPalette.h"

BitmapLoader::BitmapLoader() { }

BitmapLoader::~BitmapLoader() { }

Bitmap* BitmapLoader::LoadBMP(const char * file, bool calibrateRGBtoRCColour, const COLORREF * palette) {
	FILE* bmpFile;
	fopen_s(&bmpFile, file, "rb");

	if (bmpFile) {
		Bitmap* bitmap = new Bitmap();
		
		fseek(bmpFile, 0, SEEK_END);
		int length = ftell(bmpFile);
		rewind(bmpFile);

		unsigned char* data = new unsigned char[length];
		fread(data, sizeof(unsigned char), length, bmpFile);

		if (data[0] == 'B' && data[1] == 'M') {
			bitmap->width = data[18];
			bitmap->height = data[22];
			int bitPerPixel = data[28];
			int of = 54; // header size

			if (bitPerPixel != 24)
				return nullptr;

			COLORREF const * currentPalette = (palette == nullptr) ? RCEngine::GetColourPalette() : palette;

			for (int y = 0; y < 3 * bitmap->height; y+=3) {
				for (int x = 3 * bitmap->width; x > 0; x-=3) {
					PIXEL* pixel = new PIXEL();
					int index = of + (y * bitmap->width) + x;

					pixel->red = data[index - 1];
					pixel->green = data[index - 2];
					pixel->blue = data[index - 3];

					if (calibrateRGBtoRCColour) {
						pixel->colourIndex = RGBtoRCColour(pixel->red, pixel->green, pixel->blue, currentPalette);
					}

					bitmap->pixels.push_back(pixel);
				}
			}

			std::reverse(bitmap->pixels.begin(), bitmap->pixels.end());
		}

		return bitmap;
	}

	return nullptr;
}

int BitmapLoader::RGBtoRCColour(int r, int g, int b, const COLORREF * palette) {
	double difference = 10000.0;
	int index = 0;

	for (int i = 0; i < 16; i++) {
		PIXEL colour = PIXEL(GetRValue(palette[i]), GetGValue(palette[i]), GetBValue(palette[i]));
		double power = 2.0;

		double currentDifference = sqrt(
			pow((colour.red - r), power) +
			pow((colour.green - g), power) +
			pow((colour.blue - b), power) );

		if (currentDifference < difference) {
			difference = currentDifference;
			index = i;
		}
	}

	return index;
}

int BitmapLoader::RGBtoRCColour(PIXEL pixel, const COLORREF * palette) {
	return RGBtoRCColour(pixel.red, pixel.green, pixel.blue, palette);
}

void BitmapLoader::DestroyBitmap(Bitmap * bitmap) {
	if (bitmap != nullptr) {
		for (int i = 0; i < bitmap->pixels.size(); i++) {
			delete bitmap->pixels[i];
			bitmap->pixels[i] = nullptr;
		}

		delete bitmap;
	}

	bitmap = nullptr;
}

#pragma region Bitmap Functions

void BitmapFile::ConvertPixelsToRCColour() {
	for (int i = 0; i < this->height * this->width; i++) {
		this->pixels[i]->colourIndex = BitmapLoader::RGBtoRCColour(*this->pixels[i], RCEngine::GetColourPalette());
	}
}

#pragma endregion