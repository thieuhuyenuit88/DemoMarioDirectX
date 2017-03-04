#include "GamePlay.h"
#include "TestState.h"
#include "StateTestGame.h"
#include "MainMenuScreen.h"

GamePlay::GamePlay(LPDIRECT3DDEVICE9 pDeviceDX): IPlay(pDeviceDX){
	curState = new MainMenuScreen(this);
	nextState = curState;
}

GamePlay::~GamePlay(){

}

void GamePlay::Init(){
	curState->Init();
}

void GamePlay::Update(float deltaTime){
	if (curState->GetIDState() == nextState->GetIDState())
	{
		curState->Update(deltaTime);
	}else{
		curState->Release();
		curState = nextState;
		curState->Init();
	}
}

void GamePlay::UpdateViewPosBeforeDraw(float interpolation){
	curState->UpdateViewPosBeforeDraw(interpolation);
}

void GamePlay::Draw(){
	curState->Draw();
}

void GamePlay::Release(){
	curState->Release();
	nextState->Release();
}