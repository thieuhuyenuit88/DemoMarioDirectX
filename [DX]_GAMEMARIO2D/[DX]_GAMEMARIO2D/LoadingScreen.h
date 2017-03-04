#pragma once
#include "IState.h"
#include "DXFont.h"

class LoadingScreen: public IState{
private:
	LPD3DXSPRITE spriteHandler;

	DXFont* menuFont;
	int countPercent;
public:
	LoadingScreen(IPlay *iPlay);
	~LoadingScreen(void);

	void IsKeyDown(int keyCode){}
	void OnKeyDown(int keyCode){}
	void OnKeyUp(int keyCode){}

	void Init();
	void Update(float deltaTime){}
	void UpdateViewPosBeforeDraw(float interpolation){}
	void Draw(){}

	void DrawLoading();

	void Release();
};