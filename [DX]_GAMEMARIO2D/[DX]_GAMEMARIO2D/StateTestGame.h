#pragma once
#include "IState.h"
#include "Sprite.h"
#include "ISprite.h"
#include "Mario.h"
#include "Camera.h"
#include "BrickHard.h"
#include "BrickBreak.h"
#include "Boss.h"
#include "Winpole.h"
#include "Building.h"
#include <vector>
#include "EffectBrickExplode.h"
#include "MushroomBad.h"
#include "Turtle.h"
#include "DXFont.h"
#include "QuadTree.h"
#include "InGameController.h"
#include "Coin.h"
#include "LoseScreen.h"
#include "PauseScreen.h"
#include "WinScreen.h"

using namespace std;

class StateTestGame: public IState{
private:
	Mario* mario;
	Boss* boss;
	Winpole* winPole;
	Building* building;

	DXFont* gameFont;
	LPD3DXSPRITE spriteHandler;
	D3DXMATRIX mtWorld;
	D3DXMATRIX mtIndentity;

	QuadTree* quadTree;
	Camera* camera;

	vector<StaticObject*>* cameraContentStatic;
	vector<DynamicObject*>* cameraContentDynamic;
	
	int levelMap;
	int timePlay;
	int life;
	int numberCoin;
	int score;

	WinScreen* winScreen;
	PauseScreen* pauseScreen;
	LoseScreen* loseScreen;

	Sprite* iconMario;
	ISprite iIcon;

	Coin* infoCoin;

	float timeUpdate, timeUpdate1, timeUpdate2;
	float timeDown;

	Sprite* bossBlood;
	vector<ISprite>* infoBoss;

	bool isTimeOff;
public:
	StateTestGame(IPlay *iPlay);
	~StateTestGame(void);

	STATUS_STATE stateInGame;

	int getTimePlay(){
		return timePlay;
	}

	Mario* getMario(){
		return mario;
	}

	vector<StaticObject*>* getCameraContentStatic(){
		return cameraContentStatic;
	}

	vector<DynamicObject*>* getCameraContentDynamic(){
		return cameraContentDynamic;
	}

	void IsKeyDown(int keyCode);
	void OnKeyDown(int keyCode);
	void OnKeyUp(int keyCode);

	void Init();
	void Update(float deltaTime);
	void UpdateViewPosBeforeDraw(float interpolation);
	void Draw();
	void Release();
};
