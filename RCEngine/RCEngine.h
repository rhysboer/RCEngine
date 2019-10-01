#pragma once
#include <iostream>
#include <thread>
#include <windows.h>
#include <math.h>
#include <chrono>

#include "Vector2.h"
#include "Object2D.h"

#include "ObjectManager.h"
#include "InputManager.h"

#include "TileMap.h"

#include "ColourPalette.h"

#define PIXEL_FULL 0x2588
#define PIXEL_SHADE_LIGHT 0x2591
#define PIXEL_SHADE_MEDIUM 0x2592
#define PIXEL_SHADE_DARK 0x2593

// Base colour index for the Engine
typedef enum PaletteIndex {
	FG_BLACK		= 0x0000,	// Index = 0
	FG_DARK_BLUE	= 0x0001,	// Index = 1
	FG_DARK_GREEN	= 0x0002,	// Index = 2
	FG_DARK_CYAN	= 0x0003,	// Index = 3
	FG_DARK_RED		= 0x0004,	// Index = 4
	FG_DARK_PURPLE	= 0x0005,	// Index = 5
	FG_DARK_YELLOW	= 0x0006,	// Index = 6
	FG_GREY			= 0x0007,	// Index = 7
	FG_DARK_GREY	= 0x0008,	// Index = 8
	FG_BLUE			= 0x0009,	// Index = 9
	FG_GREEN		= 0x000A,	// Index = 10
	FG_CYAN			= 0x000B,	// Index = 11
	FG_RED			= 0x000C,	// Index = 12
	FG_PURPLE		= 0x000D,	// Index = 13
	FG_YELLOW		= 0x000E,	// Index = 14
	FG_WHITE		= 0x000F,	// Index = 15
	BG_BLACK		= 0x0000,	// Index = 16
	BG_DARK_BLUE	= 0x0010,	// Index = 17
	BG_DARK_GREEN	= 0x0020,	// Index = 18
	BG_DARK_CYAN	= 0x0030,	// Index = 19
	BG_DARK_RED		= 0x0040,	// Index = 20
	BG_DARK_PURPLE	= 0x0050,	// Index = 21
	BG_DARK_YELLOW	= 0x0060,	// Index = 22
	BG_GREY			= 0x0070,	// Index = 23
	BG_DARK_GREY	= 0x0080,	// Index = 24
	BG_BLUE			= 0x0090,	// Index = 25
	BG_GREEN		= 0x00A0,	// Index = 26
	BG_CYAN			= 0x00B0,	// Index = 27
	BG_RED			= 0x00C0,	// Index = 28
	BG_PURPLE		= 0x00D0,	// Index = 29
	BG_YELLOW		= 0x00E0,	// Index = 30
	BG_WHITE		= 0x00F0,	// Index = 31
} RCColours;

class RCEngine {
public:
	RCEngine();
	~RCEngine();

	// Engine Creation
	bool CreateEngine(int width, int height, int pixelWidth = 8, int pixelHeight = 8);
	void Run();

	// Drawing Functions
	void RCDrawString(int x, int y, std::string string, int colour = PaletteIndex::FG_WHITE);
	void RCDrawChar(int x, int y, const short ch, int colour = PaletteIndex::FG_WHITE);
	void RCDrawSquare(int x, int y, int width, int height, short character, int colour = PaletteIndex::FG_WHITE);
	void RCDrawSquareEmpty(int x, int y, int width, int height, short character, int colour = PaletteIndex::FG_WHITE);
	void RCDrawLine(int x1, int y1, int x2, int y2, short character, int colour = PaletteIndex::FG_WHITE);
	void RCDrawCircle(int x, int y, float radius, short character, int colour = PaletteIndex::FG_WHITE);
	void RCDrawArray(const std::vector<Vector2> list, short character, int colour = PaletteIndex::FG_WHITE);
	void RCDrawArray(const Vector2 list[], int size, short character, int colour = PaletteIndex::FG_WHITE);

	void RCDrawObject2D(Object2D& object);
	void RCDrawSprite(const Vector2 pos, const Sprite* sprite, const short character);
	void RCDrawTile(const Tile* tile);
	void RCDrawTileMap(const TileMap* map);

	void RCClear();

	void RCSetPalette(const COLORREF* col);
	void RCSetPalette(const ColourPalette& palette);
	void RCSetTitle(const std::string title);

	// Getter
	static RCEngine* Get();
	Vector2 GetScreenResolution() const;
	static const float DeltaTime();
	static const COLORREF * GetColourPalette();
	const InputManager* Input() const;

protected:

	// Settings & Managers
	ObjectManager* Object2DManager();

	// Virual Functions
	virtual void OnStart() = 0;
	virtual void OnUpdate() = 0;
	virtual void OnExit() = 0;

private:

	// Functions
	void GameLoop();
	//void RCSetPixel(int x, int y, short character, int colour = PaletteIndex::FG_WHITE); // Might delete

	void ErrorHandler(const std::string);

	// Variables
	bool m_engineRunning;
	bool m_isEngineCreate;
	static float m_deltaTime;

	// Managers
	InputManager* m_input;
	ObjectManager* m_objects;

	// Console Setting
	std::wstring m_title;
	static COLORREF m_colours[16];
	HANDLE m_console;
	HANDLE m_defaultConsole;
	CHAR_INFO* m_buffer;
	SMALL_RECT m_rectSize;
	int m_width;
	int m_height;

	// Singleton
	static RCEngine* m_instance;
};

