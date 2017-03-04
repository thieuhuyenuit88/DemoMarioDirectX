#pragma once
#include "MyButton.h"

class StateTestGame;
class LoseScreen{
private:
	StateTestGame* mainGame;

	MyButton<LoseScreen>* btnPlayAgain;
	MyButton<LoseScreen>* btnBackMenu;

	Sprite* dialogBG;
	ISprite iDialogBG;

	int btnChoosing;
	bool isChoosed;
public:
	LoseScreen(void);
	~LoseScreen(void);

	LoseScreen(StateTestGame* _mainGame);

	void OnKeyDown(int _keyCode);

	void Init();
	void Update(float deltaTime);
	void Draw(LPD3DXSPRITE spriteHandler);
	void Release();

	void BtnPlayAgainChoosed(int _id);
	void BtnBackMenuChoosed(int _id);
};