#pragma once
#include <SDL.h>
#include <string.h>
#include "MathHelper.h"

class InputManager
{
private:
	static InputManager* instance;

	Uint8* prevKeyboardState;
	const Uint8* keyboardState;
	int keyLength;

	Uint32 prevMouseState;
	Uint32 mouseState;

	int mouseXPos;
	int mouseYPos;

	InputManager();
	~InputManager();
public:
	enum Mouse_Button { left = 0, right, middle, back, forward };

	static InputManager* Instance();
	static void Release();

	bool KeyDown(SDL_Scancode scanCode);
	bool KeyPressed(SDL_Scancode scanCode);
	bool KeyReleased(SDL_Scancode scanCode);

	bool MouseButtonDown(Mouse_Button button);
	bool MouseButtonPressed(Mouse_Button button);
	bool MouseButtonReleased(Mouse_Button button);

	Vector2 MousePos();

	void Update();
	void UpdatePrevInput();
};