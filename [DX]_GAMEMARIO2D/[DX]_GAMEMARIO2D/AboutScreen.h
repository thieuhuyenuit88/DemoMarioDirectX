#pragma once
#include "IState.h"
#include "Sprite.h"

class AboutScreen: public IState{
private:
	Sprite* mainMenuBG;
	ISprite iBG;

	int btnChoosing;
	bool isChoosed;

	LPD3DXSPRITE spriteHandler;
public:
	AboutScreen(IPlay *iPlay);
	~AboutScreen(void);

	void IsKeyDown(int keyCode){}
	void OnKeyDown(int keyCode);
	void OnKeyUp(int keyCode){}

	void Init();
	void Update(float deltaTime);
	void UpdateViewPosBeforeDraw(float interpolation){}
	void Draw();
	void Release();
};