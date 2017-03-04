#pragma once
#include "MyButton.h"
#include "IState.h"
#include "DXFont.h"

class ChooseLevelScreen: public IState{
private:
	MyButton<ChooseLevelScreen>* btnLevel1;
	MyButton<ChooseLevelScreen>* btnLevel2;
	MyButton<ChooseLevelScreen>* btnLevel3;

	Sprite* mainMenuBG;
	ISprite iBG;

	int btnChoosing;
	bool isChoosed;

	LPD3DXSPRITE spriteHandler;

	DXFont* menuFont;
	DXFont* levelFont;
public:
	ChooseLevelScreen(IPlay *iPlay);
	~ChooseLevelScreen(void);

	void IsKeyDown(int keyCode){}
	void OnKeyDown(int keyCode);
	void OnKeyUp(int keyCode){}

	void Init();
	void Update(float deltaTime);
	void UpdateViewPosBeforeDraw(float interpolation){}
	void Draw();
	void Release();

	void BtnLevel1Choosed(int _id);
	void BtnLevel2Choosed(int _id);
	void BtnLevel3Choosed(int _id);
};