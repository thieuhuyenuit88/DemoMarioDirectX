#pragma once
#include <d3d9.h>
#include <dinput.h>

#define KEYBOARD_BUFFER_SIZE 1024
#define DIRECTINPUT_VERSION 0x0800

class InputManager{
private:
	LPDIRECTINPUT8 pInput; // Pointer to dx input
	LPDIRECTINPUTDEVICE8 pKeyboard; // Pointer to dx device input
	LPDIRECTINPUTDEVICE8 pMouse;

	HINSTANCE hInstance;
	HWND hWnd;
	static InputManager* instance; // Singleton
	InputManager(HINSTANCE hInstance, HWND hWnd);
public:
	~InputManager(void);
	LPDIRECTINPUTDEVICE8 KeyBoard();
	LPDIRECTINPUTDEVICE8 Mouse();
	static InputManager* getInstanceInput(HINSTANCE hInstance,HWND hWnd);
};