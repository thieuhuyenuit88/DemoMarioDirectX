#include "WinScreen.h"
#include "RSMainGame.h"
#include <dinput.h>
#include "StateTestGame.h"
#include "AudioManager.h"
#include "LevelController.h"
#include "MainMenuScreen.h"
#include "LoadingScreen.h"

WinScreen::WinScreen(void){

}

WinScreen::~WinScreen(void){

}

WinScreen::WinScreen(StateTestGame* _mainGame){
	mainGame = _mainGame;
	btnChoosing = 0;
	isChoosed = false;
	Init();
}

void WinScreen::OnKeyDown(int _keyCode){
	switch(_keyCode){
	case DIK_LEFT:
	case DIK_RIGHT:
		AudioManager::getAudioManager()->Play("e_chose");
		if (btnChoosing == 0)
		{
			btnChoosing = 1;
		}else{
			btnChoosing = 0;
		}
		break;
	case DIK_SPACE:
		AudioManager::getAudioManager()->Play("e_click");
		isChoosed = true;
		break;
	}
}

void WinScreen::Init(){
	dialogBG = RSMainGame::getRSMainGame()->getDialogWin();
	iDialogBG.setXY((g_SCREEN_WIDTH - 400)/2, (g_SCREEN_HEIGHT - 300)/2);

	btnNextLevel = new MyButton<WinScreen>(RSMainGame::getRSMainGame()->getBtnNextLevel(), 
		iDialogBG.getX() + 180, iDialogBG.getY() + 180, 0);
	btnNextLevel->fire->SetCallBack(this, &WinScreen::BtnNextLevelChoosed);

	btnBackMenu = new MyButton<WinScreen>(RSMainGame::getRSMainGame()->getBtnBackToMainMenu(), 
		iDialogBG.getX() + 290, iDialogBG.getY() + 180, 1);
	btnBackMenu->fire->SetCallBack(this, &WinScreen::BtnBackMenuChoosed);
}

void WinScreen::Update(float deltaTime){
	btnNextLevel->UpdateInput(btnChoosing, isChoosed);
	btnBackMenu->UpdateInput(btnChoosing, isChoosed);
}

void WinScreen::Draw(LPD3DXSPRITE spriteHandler){

	dialogBG->Draw(spriteHandler, iDialogBG);

	btnNextLevel->Draw(spriteHandler);
	btnBackMenu->Draw(spriteHandler);
}

void WinScreen::BtnBackMenuChoosed(int _id)
{
	isChoosed = false;
	mainGame->GetGamePlay()->setNextState(new MainMenuScreen(mainGame->GetGamePlay()));
}

void WinScreen::BtnNextLevelChoosed(int _id){
	isChoosed = false;
	
	if (LevelController::getLevelController()->LEVELCHOOSED + 1 <= LevelController::getLevelController()->NUMLEVEL)
	{
		LevelController::getLevelController()->LEVELCHOOSED +=1;
		mainGame->GetGamePlay()->setNextState(new LoadingScreen(mainGame->GetGamePlay()));
	}else{
		mainGame->GetGamePlay()->setNextState(new MainMenuScreen(mainGame->GetGamePlay()));
	}
}

void WinScreen::Release(){

}