#pragma once
#include "MyButton.h"
#include "IState.h"
#include "DXFont.h"

class MainMenuScreen: public IState{
private:
	MyButton<MainMenuScreen>* btnPlayGame;
	MyButton<MainMenuScreen>* btnLoadGame;
	MyButton<MainMenuScreen>* btnOption;
	MyButton<MainMenuScreen>* btnAboutAndHelp;
	MyButton<MainMenuScreen>* btnExit;

	Sprite* mainMenuBG;
	ISprite iBG;

	int btnChoosing;
	bool isChoosed;

	DXFont* menuFont;

	LPD3DXSPRITE spriteHandler;
public:
	MainMenuScreen(IPlay *iPlay);
	~MainMenuScreen(void);

	void IsKeyDown(int keyCode){}
	void OnKeyDown(int keyCode);
	void OnKeyUp(int keyCode){}

	void Init();
	void Update(float deltaTime);
	void UpdateViewPosBeforeDraw(float interpolation){}
	void Draw();
	void Release();

	void BtnPlayGameChoosed(int _id);
	void BtnLoadGameChoosed(int _id);
	void BtnOptionChooosed(int _id);
	void BtnAboutAndHelpChoosed(int _id);
	void BtnExitChoosed(int _id);
};