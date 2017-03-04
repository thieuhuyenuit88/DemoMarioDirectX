#include "InputManager.h"
InputManager* InputManager::instance = NULL;

InputManager::InputManager(HINSTANCE hInstance, HWND hHwnd){
	this->hInstance = hInstance;
	this->hWnd = hHwnd;
}

InputManager::~InputManager(void){

}

InputManager* InputManager::getInstanceInput(HINSTANCE hInstance,HWND hWnd){
	if (instance == NULL)
	{
		instance = new InputManager(hInstance, hWnd);
	}

	return instance;
}

LPDIRECTINPUTDEVICE8 InputManager::KeyBoard(){
	HRESULT hr = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&pInput, NULL);
	if (hr != DI_OK) return NULL;
	hr = pInput->CreateDevice(GUID_SysKeyboard, &pKeyboard, NULL); 
	if (hr != DI_OK) return NULL;

	hr = pKeyboard->SetDataFormat(&c_dfDIKeyboard);
	hr = pKeyboard->SetCooperativeLevel(hWnd, DISCL_FOREGROUND );

	DIPROPDWORD dipdw;
	dipdw.diph.dwSize       = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj        = 0;
	dipdw.diph.dwHow        = DIPH_DEVICE;
	dipdw.dwData            = KEYBOARD_BUFFER_SIZE; // Arbitrary buffer size

	hr = pKeyboard->SetProperty( DIPROP_BUFFERSIZE, &dipdw.diph);
	if (hr != DI_OK) return NULL;
	
	hr = pKeyboard->Acquire(); 

	return pKeyboard;
}

LPDIRECTINPUTDEVICE8 InputManager::Mouse(){
	// Create the DirectInput object. 
	HRESULT hr = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&pInput, NULL); 
	if FAILED(hr) return FALSE; 
	
	// Retrieve a pointer to an IDirectInputDevice8 interface 
	hr = pInput->CreateDevice(GUID_SysMouse, &pMouse, NULL); 
	hr = pMouse->SetDataFormat(&c_dfDIMouse); 
	if FAILED(hr) return NULL; 

	// Set the cooperative level 
	hr = pMouse->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE); 
	if FAILED(hr) return NULL;

	// Get access to the input device. 
	pMouse->Acquire(); 

	return pMouse;
}