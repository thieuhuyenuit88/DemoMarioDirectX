#pragma once
#include "MyButton.h"

class StateTestGame;

class WinScreen{
private:
	StateTestGame* mainGame;

	MyButton<WinScreen>* btnNextLevel;
	MyButton<WinScreen>* btnBackMenu;

	Sprite* dialogBG;
	ISprite iDialogBG;

	int btnChoosing;
	bool isChoosed;
public:
	WinScreen(void);
	~WinScreen(void);

	WinScreen(StateTestGame* _mainGame);

	void OnKeyDown(int _keyCode);

	void Init();
	void Update(float deltaTime);
	void Draw(LPD3DXSPRITE spriteHandler);
	void Release();

	void BtnNextLevelChoosed(int _id);
	void BtnBackMenuChoosed(int _id);
};