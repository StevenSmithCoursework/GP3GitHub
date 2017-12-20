#pragma once

#include <SDL2\SDL.h>

class InputManager
{
public:
	static InputManager* Instance();
	static void Release();

	bool KeyDown(SDL_Scancode scanCode);

	void Update();

	InputManager();
	~InputManager();

private:
	static InputManager* sInstance;
	const Uint8* mKeyboardStates;
};