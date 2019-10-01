#include "RCEngine.h"

float RCEngine::m_deltaTime = 0.00001f;
RCEngine* RCEngine::m_instance = nullptr;
COLORREF RCEngine::m_colours[16];

RCEngine::RCEngine() {
	m_title = L"RCEngine";
	m_engineRunning = false;
	m_isEngineCreate = false;

	m_deltaTime = 0.0f;

	m_input = new InputManager();
	m_objects = new ObjectManager();
}

RCEngine::~RCEngine() {
	delete[] m_buffer;
	delete m_input;
}

bool RCEngine::CreateEngine(int width, int height, int pixelWidth, int pixelHeight) {
	if (RCEngine::Get() != nullptr) return false;

	m_console = GetStdHandle(STD_OUTPUT_HANDLE);
	m_defaultConsole = m_console;

	m_width = width;
	m_height = height;

	// Change console visual size to a minimum so ScreenBuffer can shrink
	// below the actual visual size
	//m_rectSize = {0, 0, 1, 1};
	//SetConsoleWindowInfo(m_console, TRUE, &m_rectSize);

	// Set the size of the screen buffer
	COORD coord = {(short)m_width, (short)m_height};
	if (!SetConsoleScreenBufferSize(m_console, coord)) {
		ErrorHandler("Failed to set screen buffer size");
		return false;
	}

	// Assign screen buffer to the console
	if (!SetConsoleActiveScreenBuffer(m_console)) {
		ErrorHandler("Failed to set active screen buffer");
		return false;
	}

	
	// Set the font size now that the screen buffer has been assigned to the console
	CONSOLE_FONT_INFOEX font_info;
	font_info.cbSize = sizeof(font_info);
	font_info.dwFontSize.X = pixelWidth; // 8
	font_info.dwFontSize.Y = pixelHeight; // 8
	font_info.FontFamily = FF_DONTCARE;
	font_info.FontWeight = FW_NORMAL;
	font_info.nFont = 0;
	
	wcscpy_s(font_info.FaceName, L"Lucida Console"); // Consolas
	if (!SetCurrentConsoleFontEx(m_console, false, &font_info)) {
		ErrorHandler("Failed to set console font info.");
		return false;
	}
	
	// Get screen buffer info and check the maximum allowed window size. Return
	// error if exceeded, so user knows their dimensions/fontsize are too large
	CONSOLE_SCREEN_BUFFER_INFOEX csbi;
	csbi.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
	if (!GetConsoleScreenBufferInfoEx(m_console, &csbi)) {
		ErrorHandler("Failed to set console screen buffer.");
		return false;
	}
	if (m_height > csbi.dwMaximumWindowSize.Y && m_width > csbi.dwMaximumWindowSize.X) {
		ErrorHandler("Font size is too large/small.");
		return false;
	}
	
	// Set colour palette
	for (int i = 0; i < 16; i++) {
		m_colours[i] = csbi.ColorTable[i];
	}

	// Set Physical Console Window Size
	m_rectSize = {0, 0, (short)m_width - 1, (short)m_height - 1};
	if (!SetConsoleWindowInfo(m_console, TRUE, &m_rectSize)) {
		ErrorHandler("Failed to set console window size.");
		return false;
	}
	
	// Allocate memory for screen buffer
	m_buffer = new CHAR_INFO[m_width*m_height];
	memset(m_buffer, 0, sizeof(CHAR_INFO) * m_width * m_height);

	HWND consoleWindow = GetConsoleWindow();
	SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);

	SetConsoleTitle(L"RCEngine");

	m_instance = this;
	m_isEngineCreate = true;
	return true;
}

void RCEngine::Run() {
	if (!m_isEngineCreate)
		return;

	m_engineRunning = true;

	std::thread thread = std::thread(&RCEngine::GameLoop, this);
	thread.join();
}

/////////////////////// Draw Functions
#pragma region Draw Functions

void RCEngine::RCDrawString(int x, int y, std::string string, int colour) {
	for (int i = 0; i < string.length(); i++) {
		if (x + i < m_width) {
			m_buffer[y * m_width + x + i].Char.UnicodeChar = string[i];
			m_buffer[y * m_width + x + i].Attributes = colour;
		}
	}
}

void RCEngine::RCDrawChar(int x, int y, const short ch, int colour) {
	if (x > 0 && x < m_width && y > 0 && y < m_height) {
		m_buffer[y * m_width + x].Char.UnicodeChar = ch;
		m_buffer[y * m_width + x].Attributes = colour;
	}
}


void RCEngine::RCDrawSquare(int posX, int posY, int width, int height, short character, int colour) {
	int index;

	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			index = (y + posY) * m_width + posX + x;
			m_buffer[index].Char.UnicodeChar = character;
			m_buffer[index].Attributes = colour;
		}
	}
}

void RCEngine::RCDrawSquareEmpty(int x, int y, int width, int height, short character, int colour) {
	RCDrawLine(x, y, x + width, y, character, colour); // Top Line
	RCDrawLine(x + width, y, x + width, y - height, character, colour); // Right Line
	RCDrawLine(x + width, y - height, x, y - height, character, colour); // Bottom Line
	RCDrawLine(x, y - height, x, y, character, colour); // Left Line
}

void RCEngine::RCDrawLine(int x1, int y1, int x2, int y2, short character, int colour) {
	bool steep = (abs(y2 - y1) > abs(x2 - x1));
	if (steep) {
		std::swap(x1, y1);
		std::swap(x2, y2);
	}

	if (x1 > x2) {
		std::swap(x1, x2);
		std::swap(y1, y2);
	}

	float dx = x2 - x1;
	float dy = abs(y2 - y1);

	float error = dx / 2.0f;
	int ystep = (y1 < y2) ? 1 : -1;
	int y = y1;

	int maxX = x2;

	for (int x = x1; x <= maxX; x++) {
		if (steep) {
			int index = x * m_width + y;
			if (index > 0 && index < m_width * m_height) {
				RCDrawChar(y, x, character, colour);
			}
		} else {
			int index = y * m_width + x;
			if (index > 0 && index < m_width * m_height) {
				RCDrawChar(x, y, character, colour);
			}
		}

		error -= dy;
		if (error < 0) {
			y += ystep;
			error += dx;
		}
	}
}

void RCEngine::RCDrawCircle(int xc, int yc, float radius, short character, int colour) {
	int x = radius;
	int y = 0;
	int err = 0;
	
	while (x >= y) {
		RCDrawChar(xc + x, yc + y, character, colour);
		RCDrawChar(xc + y, yc + x, character, colour);
		RCDrawChar(xc - y, yc + x, character, colour);
		RCDrawChar(xc - x, yc + y, character, colour);
		RCDrawChar(xc - x, yc - y, character, colour);
		RCDrawChar(xc - y, yc - x, character, colour);
		RCDrawChar(xc + y, yc - x, character, colour);
		RCDrawChar(xc + x, yc - y, character, colour);
	
		if (err <= 0) {
			y += 1;
			err += 2 * y + 1;
		}
		if (err > 0) {
			x -= 1;
			err -= 2 * x + 1;
		}
	
	}
}

void RCEngine::RCDrawArray(const std::vector<Vector2> list, short character, int colour) {
	for (auto vec : list) {
		RCDrawChar(vec.X, vec.Y, character, colour);
	}
}

void RCEngine::RCDrawArray(const Vector2 list[], int size, short character, int colour) {
	for (int i = 0; i < size; i++) {
		RCDrawChar(list[i].X, list[i].Y, character, colour);
	}
}

void RCEngine::RCDrawObject2D(Object2D& object) {
	object.Render(*this);
}

void RCEngine::RCDrawSprite(const Vector2 pos, const Sprite* sprite, const short character) {
	if (sprite) {
		for (int y = 0; y < sprite->GetSprite()->height; y++) {
			for (int x = 0; x < sprite->GetSprite()->width; x++) {
				int index = (pos.Y + y) * m_width + x + pos.X;

				m_buffer[index].Char.UnicodeChar = character;
				m_buffer[index].Attributes = sprite->GetSprite()->pixels[(y * sprite->GetSprite()->width) + x]->colourIndex;
			}
		}
	}
}

void RCEngine::RCDrawTile(const Tile * tile) {
	RCDrawSprite(tile->GetPosition(), tile->GetSprite(), tile->GetCharacter());
}

void RCEngine::RCDrawTileMap(const TileMap * map) {
	for (int i = 0; i < map->GetTiles().size(); i++) {
		RCDrawTile(map->GetTiles()[i].tile);
	}
}

void RCEngine::RCClear() {
	memset(m_buffer, 0, sizeof(CHAR_INFO) * m_width * m_height);
}

#pragma endregion
//////////////////////// End Draw Functions

void RCEngine::RCSetPalette(const COLORREF* col) {
	CONSOLE_SCREEN_BUFFER_INFOEX csbi;
	csbi.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);

	if (!GetConsoleScreenBufferInfoEx(m_console, &csbi))
		return;

	csbi.srWindow = {0, 0, (SHORT)m_width, (SHORT)m_height};

	for (int i = 0; i < 16; i++) {
		m_instance->m_colours[i] = col[i];
		csbi.ColorTable[i] = col[i];
	}

	SetConsoleScreenBufferInfoEx(m_console, &csbi);
}

void RCEngine::RCSetPalette(const ColourPalette& palette) {
	RCSetPalette(palette.ColourRef);
}

void RCEngine::RCSetTitle(const std::string title) {
	m_title = std::wstring(title.begin(), title.end());
}


void RCEngine::GameLoop() {
	OnStart();

	auto dt1 = std::chrono::system_clock::now();
	auto dt2 = std::chrono::system_clock::now();

	while (m_engineRunning) {
		dt2 = std::chrono::system_clock::now();
		std::chrono::duration<float> elapsedTime = dt2 - dt1;
		dt1 = dt2;
		m_deltaTime = elapsedTime.count();

		// Handle Input
		m_input->UpdateInput();
		
		// Call Game Update
		OnUpdate();

		// Render Objects
		m_objects->UpdateObjects();
		m_objects->Render(*this);

		// Draw
		WriteConsoleOutput(m_console, m_buffer, {(SHORT)m_width, (SHORT)m_height}, {0,0}, &m_rectSize);

		wchar_t framerateString[24];
		swprintf_s(framerateString, 24, L" fps: %3.2f", 1.0f / m_deltaTime);
		std::wstring title = m_title + framerateString;

		SetConsoleTitle(title.data());
	}

	OnExit();
}

const InputManager * RCEngine::Input() const {
	return m_input;
}

ObjectManager * RCEngine::Object2DManager() {
	return m_objects;
}

RCEngine * RCEngine::Get() {
	// Should never be nullptr unless createengine isnt called;
	return RCEngine::m_instance;
}

Vector2 RCEngine::GetScreenResolution() const {
	return Vector2(m_width, m_height);
}

const float RCEngine::DeltaTime() {
	float time = RCEngine::m_deltaTime;
	if (time > 1.0f)
		time / 60.0f;

	return time;
}

const COLORREF * RCEngine::GetColourPalette() {
	return RCEngine::m_instance->m_colours; 
}

/*
void RCEngine::RCSetPixel(int x, int y, short character, int colour) {
	int index = y * m_width + x;

	if (index < m_width * m_height && index >= 0) {
		m_buffer[index].Char.UnicodeChar = character;
		m_buffer[index].Attributes = colour;
	}
}
*/

void RCEngine::ErrorHandler(const std::string message) {
	SetConsoleActiveScreenBuffer(m_defaultConsole);

	CONSOLE_FONT_INFOEX font_info;
	font_info.cbSize = sizeof(font_info);
	font_info.dwFontSize.X = 7;
	font_info.dwFontSize.Y = 14;
	font_info.FontFamily = FF_DONTCARE;
	font_info.FontWeight = FW_NORMAL;
	font_info.nFont = 0;

	wcscpy_s(font_info.FaceName, L"Consolas"); // Consolas
	SetCurrentConsoleFontEx(m_defaultConsole, false, &font_info);

	std::cout << "Error: " << message << std::endl;
}
