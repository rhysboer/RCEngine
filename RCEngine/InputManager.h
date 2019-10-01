#pragma once
#include <Windows.h>

enum KeyCodes {
	KEY_ARROW_LEFT = 0x25,
	KEY_ARROW_UP = 0x26,
	KEY_ARROW_RIGHT = 0x27,
	KEY_ARROW_DOWN = 0x28,
	KEY_0 = 0x30,
	KEY_1 = 0x31,
	KEY_2 = 0x32,
	KEY_3 = 0x33,
	KEY_4 = 0x34,
	KEY_5 = 0x35,
	KEY_6 = 0x36,
	KEY_7 = 0x37,
	KEY_8 = 0x38,
	KEY_9 = 0x39,
	KEY_A = 0x41,
	KEY_B = 0x42,
	KEY_C = 0x43,
	KEY_D = 0x44,
	KEY_E = 0x45,
	KEY_F = 0x46,
	KEY_G = 0x47,
	KEY_H = 0x48,
	KEY_I = 0x49,
	KEY_J = 0x4A,
	KEY_K = 0x4B,
	KEY_L = 0x4C,
	KEY_M = 0x4D,
	KEY_N = 0x4E,
	KEY_O = 0x4F,
	KEY_P = 0x50,
	KEY_Q = 0x51,
	KEY_R = 0x52,
	KEY_S = 0x53,
	KEY_T = 0x54,
	KEY_U = 0x55,
	KEY_V = 0x56,
	KEY_W = 0x57,
	KEY_X = 0x58,
	KEY_Y = 0x59,
	KEY_Z = 0x5A,
	KEY_NUM_0 = 0x60,
	KEY_NUM_1 = 0x61,
	KEY_NUM_2 = 0x62,
	KEY_NUM_3 = 0x63,
	KEY_NUM_4 = 0x64,
	KEY_NUM_5 = 0x65,
	KEY_NUM_6 = 0x66,
	KEY_NUM_7 = 0x67,
	KEY_NUM_8 = 0x68,
	KEY_NUM_9 = 0x69
};

class InputManager {
public:
	InputManager();
	~InputManager();

	// Input Checks
	bool IsKeyPressed(int key) const;
	bool IsKeyHeld(int key) const;
	bool IsKeyReleased(int key) const;

	// Call once per frame
	void UpdateInput();

	struct KeyState {
		bool m_pressed = false;
		bool m_held = false;
		bool m_released = false;
	};
private:

	KeyState m_keys[256];
	KeyState m_keysOld[256];
};

