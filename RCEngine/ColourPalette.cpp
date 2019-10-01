#include "ColourPalette.h"

const COLORREF ColourPalette::DEFAULT_COLOURS[16] = {
	0x00000000, 0x00800000, 0x00008000, 0x00808000,
	0x00000080, 0x00800080, 0x00008080, 0x00c0c0c0,
	0x00808080, 0x00ff0000, 0x0000ff00, 0x00ffff00,
	0x000000ff, 0x00ff00ff, 0x0000ffff, 0x00ffffff
};

ColourPalette::ColourPalette() {
	for (int i = 0; i < 16; i++) {
		m_colourRef[i] = HexColours::BLACK;
	}
}

ColourPalette::~ColourPalette() {
}

bool ColourPalette::AddColour(HexColours colour, unsigned int index) {
	if (CheckIndex(index)) {
		m_colourRef[index] = colour;
		return true;
	}

	return false;
}

bool ColourPalette::AddColour(unsigned int r, unsigned int g, unsigned int b, unsigned int index) {
	if (CheckIndex(index)){
		DWORD colour = RGB(r, g, b);
		
		m_colourRef[index] = colour;
		return true;
	}
	return false;
}

bool ColourPalette::AddPalette(const char* path) {
	Bitmap* palette = BitmapLoader::LoadBMP(path);

	if (palette) {
		if (palette->width != 16 && palette->height != 1) {
			delete palette;
			return false;
		}

		for (int i = 0; i < 15; i++) {
			PIXEL* pixel = palette->pixels[i];
			m_colourRef[i] = RGB(pixel->red, pixel->green, pixel->blue);
		}

		delete palette;
		return true;
	}

	return false;
}

void ColourPalette::GetColourRefArray(COLORREF ref[]) const {
	for (int i = 0; i < 16; i++) {
		ref[i] = m_colourRef[i];
	}
}
