#pragma once
#include <Windows.h>
#include "BitmapLoader.h"

#define CheckIndex(index) (index >= 0 && index < 16) ? true : false

// 0x00bbggrr
// Hex values for colours for the colour palette
enum HexColours {
	BLACK	= 0x00000000,
	WHITE	= 0x00ffffff,
	GREY	= 0x007f7f7f,
	RED		= 0x000000ff,
	GREEN	= 0x0000ff00,
	BLUE	= 0x00ff0000,
	YELLOW	= 0x0000ffff,
	CYAN	= 0x00ffff00,
	PINK	= 0x00ff00ff,
	MAGENTA = 0x00ff007f,
	PURPLE	= 0x007f007f,
	ORANGE	= 0x00007fff,
	BROWN	= 0x0007458B
};

class ColourPalette {
public:
	ColourPalette();
	~ColourPalette();

	static const COLORREF DEFAULT_COLOURS[16];

	bool AddColour(HexColours colour, unsigned int index);
	bool AddColour(unsigned int r, unsigned int g, unsigned int b, unsigned int index);
	//bool AddColour(const ColourVec colour, unsigned int index);
	bool AddPalette(const char* path);
	
	//ColourVec GetColour(unsigned int index);

	void GetColourRefArray(COLORREF ref[]) const;

	// Pointer to colour array
	const COLORREF const * ColourRef = m_colourRef;

private:

	COLORREF m_colourRef[16]; //COLORREF m_colourRef[16];
};

