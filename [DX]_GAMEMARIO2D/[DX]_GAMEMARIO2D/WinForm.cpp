#include "WinForm.h"

WinForm::WinForm(){
	appName = "";
}

bool WinForm::RegisterClassWD(HINSTANCE hInstance){
	// this struct holds information for the window class
	WNDCLASSEX wc;

	// clear out the window class for use
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	// fill in the struct with the needed information
	wc.cbSize			= sizeof(WNDCLASSEX);
	wc.style			= CS_HREDRAW | CS_VREDRAW;
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;
	wc.lpfnWndProc		= WinProc;
	wc.hInstance		= hInstance;
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);
	wc.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	wc.hbrBackground	= (HBRUSH) GetStockObject (WHITE_BRUSH); //(HBRUSH)COLOR_WINDOW; 
	wc.lpszClassName	= appName;
	wc.lpszMenuName		= NULL;
	wc.hIconSm			= wc.hIcon;

	// register the window class
	if(!RegisterClassEx(&wc)){
		MessageBox (NULL, TEXT ("RegisterClassEx failed!"), appName, MB_ICONERROR);
		return false;
	}

	return true;
}

bool WinForm::CreateWD(HINSTANCE hInstance, int nCmdShow, int width, int height){
	// create the window and use the result as the handle
	hWnd = CreateWindowEx (WS_EX_OVERLAPPEDWINDOW, 
		appName,				// name of window class
		TEXT ("GameMARIO"),		// title of the window
		WS_OVERLAPPEDWINDOW,	// window style
		CW_USEDEFAULT,			// x-pos of window
		CW_USEDEFAULT,			// y-pos of window
		width,					// width of window
		height,					// height of window
		NULL,					// we have no parent window, NULL
		NULL,					// we aren't using menus, NULL
		hInstance,				// application handle
		NULL);					// used with multiple window, NULL

	// check create window
	if (hWnd == NULL)
	{
		MessageBox (NULL, TEXT ("Create Window failed!"), appName, MB_ICONERROR);
		return false;
	}

	// Show and update window
	ShowWindow (hWnd, nCmdShow);
	UpdateWindow (hWnd);

	return true;
}

bool WinForm::CreateWinForm(HINSTANCE hInstance, int nCmdShow, int width, int height, char* appName){
	this->appName = appName;

	if(!RegisterClassWD(hInstance)){
		return false;
	}

	if(!CreateWD(hInstance, nCmdShow, width, height)){
		return false;
	}

	return true;
}

WinForm* WinForm::InitWinForm(HINSTANCE hInstance, int nCmdShow, int width, int height, char* appName){
	WinForm* winForm = new WinForm();

	if (!winForm->CreateWinForm(hInstance, nCmdShow, width, height, appName))
	{
		MessageBox (NULL, TEXT ("Create WinForm failed!"), appName, MB_ICONERROR);
	}

	return winForm;
}

LRESULT CALLBACK WinForm::WinProc(
	HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
		return 0;		
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_SIZE:
		return 0;
	}
	return DefWindowProc (hwnd, message, wParam, lParam);
}

void WinForm::ReleaseWinForm(){
	appName = NULL;
}