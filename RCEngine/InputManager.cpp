#include "InputManager.h"


InputManager::InputManager() {
	memset(m_keys, 0, sizeof(KeyState) * 256);
	memset(m_keysOld, 0, sizeof(KeyState) * 256);
}

InputManager::~InputManager() {
}

bool InputManager::IsKeyPressed(int key) const {
	if (m_keys[key].m_pressed)
		return true;
	return false;
}

bool InputManager::IsKeyHeld(int key) const {
	if (m_keys[key].m_held)
		return true;
	return false;
}

bool InputManager::IsKeyReleased(int key) const {
	if (m_keys[key].m_released)
		return true;
	return false;
}

void InputManager::UpdateInput() {
	for (int i = 0; i < 256; i++) {
		m_keys[i].m_pressed = GetAsyncKeyState(i);

		m_keys[i].m_held = false;
		m_keys[i].m_released = false;

		// Held
		if (m_keys[i].m_pressed == true && (m_keysOld[i].m_pressed == true || m_keysOld[i].m_held == true)) {
			m_keys[i].m_held = true;
			m_keys[i].m_pressed = false;

			// Release
		}  else if (m_keys[i].m_pressed == false && (m_keysOld[i].m_pressed == true || m_keysOld[i].m_held == true)) {
			m_keys[i].m_released = true;
		}

		m_keysOld[i].m_pressed = m_keys[i].m_pressed;
		m_keysOld[i].m_held = m_keys[i].m_held;
		m_keysOld[i].m_released = m_keys[i].m_released;
	}
}

