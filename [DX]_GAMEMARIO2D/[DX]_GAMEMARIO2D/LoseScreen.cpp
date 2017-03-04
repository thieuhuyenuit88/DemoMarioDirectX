#include "LoseScreen.h"
#include "RSMainGame.h"
#include <dinput.h>
#include "StateTestGame.h"
#include "AudioManager.h"
#include "LoadingScreen.h"
#include "MainMenuScreen.h"
#include "InGameController.h"

LoseScreen::LoseScreen(void){

}

LoseScreen::~LoseScreen(void){

}

LoseScreen::LoseScreen(StateTestGame* _mainGame){
	mainGame = _mainGame;
	btnChoosing = 0;
	isChoosed = false;
	Init();
}

void LoseScreen::OnKeyDown(int _keyCode){
	switch(_keyCode){
	case DIK_UP:
	case DIK_DOWN:
		AudioManager::getAudioManager()->Play("e_chose");
		if (btnChoosing == 0)
		{
			btnChoosing = 1;
		}else{
			btnChoosing = 0;
		}
		break;
	case DIK_SPACE:
		isChoosed = true;
		AudioManager::getAudioManager()->Play("e_click");
		break;
	}
}

void LoseScreen::Init(){
	dialogBG = RSMainGame::getRSMainGame()->getDialogLost();
	iDialogBG.setXY((g_SCREEN_WIDTH - 400)/2, (g_SCREEN_HEIGHT - 300)/2);

	btnPlayAgain = new MyButton<LoseScreen>(RSMainGame::getRSMainGame()->getBtnPlayAgain(), 
		iDialogBG.getX() + 50, iDialogBG.getY() + 80, 0);
	btnPlayAgain->fire->SetCallBack(this, &LoseScreen::BtnPlayAgainChoosed);

	btnBackMenu = new MyButton<LoseScreen>(RSMainGame::getRSMainGame()->getBtnBackToMainMenu(), 
		iDialogBG.getX() + 50, iDialogBG.getY() + 190, 1);
	btnBackMenu->fire->SetCallBack(this, &LoseScreen::BtnBackMenuChoosed);
}

void LoseScreen::Update(float deltaTime){
	btnPlayAgain->UpdateInput(btnChoosing, isChoosed);
	btnBackMenu->UpdateInput(btnChoosing, isChoosed);
}

void LoseScreen::Draw(LPD3DXSPRITE spriteHandler){

	dialogBG->Draw(spriteHandler, iDialogBG);

	btnPlayAgain->Draw(spriteHandler);
	btnBackMenu->Draw(spriteHandler);
}

void LoseScreen::Release(){

}

void LoseScreen::BtnBackMenuChoosed(int _id){
	isChoosed = false;
	mainGame->GetGamePlay()->setNextState(new MainMenuScreen(mainGame->GetGamePlay()));
}

void LoseScreen::BtnPlayAgainChoosed(int _id){
	isChoosed = false;
	InGameController::getInGameController()->ResetBasicFigure();

	mainGame->GetGamePlay()->setNextState(new LoadingScreen(mainGame->GetGamePlay()));	
}