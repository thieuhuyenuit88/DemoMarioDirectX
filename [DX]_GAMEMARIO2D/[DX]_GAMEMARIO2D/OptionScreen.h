#pragma once
#include "MyButton.h"
#include "IState.h"
#include "DXFont.h"

class OptionScreen: public IState{
private:
	MyButton<OptionScreen>* btnSoundOn;
	MyButton<OptionScreen>* btnSoundOff;

	MyButton<OptionScreen>* btnMusicOn;
	MyButton<OptionScreen>* btnMusicOff;


	Sprite* mainMenuBG;
	ISprite iBG;

	int btnChoosing;
	bool isChoosed;

	LPD3DXSPRITE spriteHandler;

	DXFont* menuFont;

	bool isSound;
	bool isMusic;
public:
	OptionScreen(IPlay *iPlay);
	~OptionScreen(void);

	void IsKeyDown(int keyCode){}
	void OnKeyDown(int keyCode);
	void OnKeyUp(int keyCode){}

	void Init();
	void Update(float deltaTime);
	void UpdateViewPosBeforeDraw(float interpolation){}
	void Draw();
	void Release();

	void BtnSoundOnChoosed(int _id);
	void BtnSoundOffChoosed(int _id);
	void BtnMusicOffChooosed(int _id);
	void BtnMusicOnChoosed(int _id);
};