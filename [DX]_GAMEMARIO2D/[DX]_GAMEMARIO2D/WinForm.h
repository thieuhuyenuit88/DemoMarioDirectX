#pragma once
#include <Windows.h>

class WinForm{
private:
	HWND hWnd;
	char* appName;

	bool RegisterClassWD(HINSTANCE hInstance);
	bool CreateWD(HINSTANCE hInstance, int nCmdShow, int width, int height);
public:
	WinForm();
	~WinForm(){};

	bool CreateWinForm(HINSTANCE hInstance, int nCmdShow, int width, int height, char* appName);
	static WinForm* InitWinForm(HINSTANCE hInstance, int nCmdShow, int width, int height, char* appName);
	static LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	
	HWND getHWND(){
		return hWnd;
	}

	void setAppName(char* appName){
		this->appName = appName;
	}

	void ReleaseWinForm();
};