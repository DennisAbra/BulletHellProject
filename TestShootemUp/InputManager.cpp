#pragma warning(push)
#pragma warning(disable : 26812)
#pragma warning(disable : 26495)
#include "InputManager.h"

InputManager* InputManager::instance = nullptr;

InputManager* InputManager::Instance()
{
	if (instance == nullptr)
	{
		instance = new InputManager();
	}

	return instance;
}

void InputManager::Release()
{
	delete instance;
	instance = nullptr;
}

InputManager::InputManager()
{
	keyboardState = SDL_GetKeyboardState(&keyLength);
	prevKeyboardState = new Uint8[keyLength];
	memcpy(prevKeyboardState, keyboardState, keyLength);
}


InputManager::~InputManager()
{
	delete[] prevKeyboardState;
	prevKeyboardState = nullptr;
}

bool InputManager::KeyDown(SDL_Scancode scanCode)
{
	return keyboardState[scanCode];
}

bool InputManager::KeyPressed(SDL_Scancode scanCode)
{
	return !prevKeyboardState[scanCode] && keyboardState[scanCode];
}

bool InputManager::KeyReleased(SDL_Scancode scanCode)
{
	return prevKeyboardState[scanCode] && !keyboardState[scanCode];
}

bool InputManager::MouseButtonDown(Mouse_Button button)
{
	Uint32 mask = 0;

	switch (button)
	{
	case InputManager::left:
		mask = SDL_BUTTON_LMASK;
		break;
	case InputManager::right:
		mask = SDL_BUTTON_RMASK;
		break;
	case InputManager::middle:
		mask = SDL_BUTTON_MMASK;
		break;
	case InputManager::back:
		mask = SDL_BUTTON_X1MASK;
		break;
	case InputManager::forward:
		mask = SDL_BUTTON_X2MASK;
		break;
	}

	return (mouseState & mask);
}

bool InputManager::MouseButtonPressed(Mouse_Button button)
{
	Uint32 mask = 0;

	switch (button)
	{
	case InputManager::left:
		mask = SDL_BUTTON_LMASK;
		break;
	case InputManager::right:
		mask = SDL_BUTTON_RMASK;
		break;
	case InputManager::middle:
		mask = SDL_BUTTON_MMASK;
		break;
	case InputManager::back:
		mask = SDL_BUTTON_X1MASK;
		break;
	case InputManager::forward:
		mask = SDL_BUTTON_X2MASK;
		break;
	}

	return !(prevMouseState & mask) && (mouseState & mask);
}

bool InputManager::MouseButtonReleased(Mouse_Button button)
{
	//Todo: Create a GetMouseButton function so this switch statement doesn't need to be copied 3 times
	Uint32 mask = 0;

	switch (button)
	{
	case InputManager::left:
		mask = SDL_BUTTON_LMASK;
		break;
	case InputManager::right:
		mask = SDL_BUTTON_RMASK;
		break;
	case InputManager::middle:
		mask = SDL_BUTTON_MMASK;
		break;
	case InputManager::back:
		mask = SDL_BUTTON_X1MASK;
		break;
	case InputManager::forward:
		mask = SDL_BUTTON_X2MASK;
		break;
	}

	return (prevMouseState & mask) && !(mouseState & mask);
}

Vector2 InputManager::MousePos()
{
	return Vector2((float)mouseXPos, (float)mouseYPos);
}

void InputManager::Update()
{
	mouseState = SDL_GetMouseState(&mouseXPos, &mouseYPos);
}

void InputManager::UpdatePrevInput()
{
	memcpy(prevKeyboardState, keyboardState, keyLength);
	prevMouseState = mouseState;
}
#pragma warning(pop)