#pragma once
#include "WinForm.h"
#include "DXCreater.h"
#include "Global.h"
#include <stdio.h>
#include <Windows.h>
#include "GamePlay.h"
#include "InputManager.h"

class GameMain{
private:
	WinForm* winForm;
	char* gameName;
	DXCreater* dxCreater;
	GamePlay* gamePlay;

	LPDIRECTINPUTDEVICE8 pKeyboard;
	LPDIRECTINPUTDEVICE8 pMouse;
	// this struct holds Windows event messages
	MSG msg;
	

	bool Init(HINSTANCE hInstance, int nCmdShow, char* gameName);
	void Update(float deltaTime);
	void UpdateViewPosBeforeRender(float interpolation);
	void Render();
	void Release();

	void ProcessInput();
	void ProcessMouse();
	void ProcessKeyboard();
public:
	GameMain();
	~GameMain(){};

	static GameMain* InitGameMain(HINSTANCE hInstance, int nCmdShow, char* gameName);
	void Run();

	MSG getMsg(){
		return msg;
	}
};