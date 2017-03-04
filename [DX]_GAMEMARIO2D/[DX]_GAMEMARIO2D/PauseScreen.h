#pragma once
#include "MyButton.h"

class StateTestGame;
class PauseScreen{
private:
	StateTestGame* mainGame;

	MyButton<PauseScreen>* btnResume;
	MyButton<PauseScreen>* btnSaveAndQuit;
	MyButton<PauseScreen>* btnBackMenu;

	MyButton<PauseScreen>* btnMusicOn;
	MyButton<PauseScreen>* btnMusicOff;

	MyButton<PauseScreen>* btnSoundOn;
	MyButton<PauseScreen>* btnSoundOff;

	Sprite* dialogPauseBG;
	ISprite iDialogBG;

	bool isSound;
	bool isMusic;

	int btnChoosing;
	bool isChoosed;
public:
	PauseScreen(void);
	~PauseScreen(void);

	PauseScreen(StateTestGame* _mainGame);

	void OnKeyDown(int _keyCode);

	void Init();
	void Update(float deltaTime);
	void Draw(LPD3DXSPRITE spriteHandler);
	void Release();

	void BtnResumeChoosed(int _id);
	void BtnSaveAndQuitChoosed(int _id);
	void BtnBackMenuChoosed(int _id);
	void BtnMusicOnChoosed(int _id);
	void BtnMusicOffChoosed(int _id);
	void BtnSoundOnChoosed(int _id);
	void BtnSoundOffChoosed(int _id);
};