#include <Windows.h>
#include "GameMain.h"

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	GameMain* gameMain = new GameMain();
	gameMain = GameMain::InitGameMain(hInstance, nCmdShow, "GameMario");
	gameMain->Run();

	return gameMain->getMsg().wParam;
}