#include "LoadingScreen.h"
#include "Global.h"
#include "RSMainMenu.h"
#include "AudioManager.h"
#include "ManagerObject.h"
#include "InGameController.h"
#include "LevelController.h"
#include "RSMainGame.h"
#include "StateTestGame.h"

LoadingScreen::LoadingScreen(IPlay *iPlay):IState(iPlay){
	this->ID = LOADINGSCREEN;
	countPercent = 0;
}

LoadingScreen::~LoadingScreen(void){

}

void LoadingScreen::Init(){
	D3DXCreateSprite(pDeviceDX, &spriteHandler);

	menuFont = RSMainMenu::getRSMainMenu()->getGameFont();
	AudioManager::getAudioManager()->StopAllBack();
	AudioManager::getAudioManager()->Play("b_loading_state");

	if (countPercent == 0)
	{
		ManagerObject::getManagerObject()->setListDynamicObject(new vector<MyObject*>());
		ManagerObject::getManagerObject()->setListEffect(new vector<Effect*>());
		ManagerObject::getManagerObject()->setListSkill(new vector<Skill*>());

		countPercent = 20;
		DrawLoading();
	}if (countPercent == 20)
	{
		if (!LevelController::getLevelController()->ISLOADGAME)
		{
			InGameController::getInGameController()->LoadInfoFromMap(LevelController::getLevelController()->LEVELCHOOSED);
		}else{
			LevelController::getLevelController()->ISLOADGAME = false;
		}

		countPercent = 60;
		DrawLoading();
	}if (countPercent == 60)
	{
		RSMainGame::getRSMainGame();

		countPercent = 100;
		DrawLoading();
	}if (countPercent == 100)
	{
		this->GetGamePlay()->setNextState(new StateTestGame(this->GetGamePlay()));
	}
}


void LoadingScreen::DrawLoading(){
	if(pDeviceDX->BeginScene())
	{
		pDeviceDX->Clear(0,NULL,D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, D3DCOLOR_XRGB(0,0,0), 1.0f, 0);
		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		menuFont->RenderText(330, 300, "LOADING...", D3DXCOLOR(255, 255 , 255, 255));

		spriteHandler->End();
		pDeviceDX->EndScene();
	}

	pDeviceDX->Present(NULL,NULL,NULL,NULL);
}

void LoadingScreen::Release(){

}