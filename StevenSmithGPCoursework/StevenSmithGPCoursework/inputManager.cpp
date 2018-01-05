#include "inputManager.h"
//Sets Input Manager instance to NULL
InputManager* InputManager::sInstance = NULL;
//Creates an instance of input manager
InputManager* InputManager::Instance()
{
	if (sInstance == NULL)
	{
		sInstance = new InputManager();
	}

	return sInstance;
}
//Deletes the Input Manager
void InputManager::Release()
{
	delete sInstance;
	sInstance = NULL;
}
//Constructor
InputManager::InputManager()
{

}
//Destructor
InputManager::~InputManager()
{

}
//Checks if a certain key is pressed
bool InputManager::KeyDown(SDL_Scancode scanCode)
{
	return mKeyboardStates[scanCode];
}
//Updates the keyboard states
void InputManager::Update()
{
	mKeyboardStates = SDL_GetKeyboardState(NULL);
}
