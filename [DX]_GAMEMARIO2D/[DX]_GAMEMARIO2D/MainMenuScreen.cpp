#include "MainMenuScreen.h"
#include "RSMainMenu.h"
#include "AudioManager.h"
#include "OptionScreen.h"
#include "AboutScreen.h"
#include "ChooseLevelScreen.h"
#include "LoadingScreen.h"
#include "InGameController.h"
#include "LevelController.h"

MainMenuScreen::MainMenuScreen(IPlay *iPlay):IState(iPlay){
	this->ID = MAINMENU;
	btnChoosing = 0;
	isChoosed = false;
}

MainMenuScreen::~MainMenuScreen(void){

}

void MainMenuScreen::OnKeyDown(int keyCode){
	switch(keyCode){
	case DIK_LEFT:
		AudioManager::getAudioManager()->Play("e_chose");
		if (btnChoosing == 0)
		{
			btnChoosing = 4;
		}else{
			btnChoosing -= 1;
		}
		break;
	case DIK_RIGHT:
		AudioManager::getAudioManager()->Play("e_chose");
		if (btnChoosing == 4)
		{
			btnChoosing = 0;
		}else{
			btnChoosing += 1;
		}
		break;
	case DIK_SPACE:
		AudioManager::getAudioManager()->Play("e_click");
		isChoosed = true;
		break;
	case DIK_ESCAPE:
		AudioManager::getAudioManager()->Play("e_chose");
		PostQuitMessage(0);
		break;
	}
}

void MainMenuScreen::Init(){
	D3DXCreateSprite(pDeviceDX, &spriteHandler);

	AudioManager::getAudioManager()->StopAllBack();
	AudioManager::getAudioManager()->Play("b_menu");

	mainMenuBG = RSMainMenu::getRSMainMenu()->getMainMenuBG();
	iBG.setXY(0,0);
	iBG.setDepth(0.02f);

	menuFont = RSMainMenu::getRSMainMenu()->getGameFont();

	btnPlayGame = new MyButton<MainMenuScreen>(RSMainMenu::getRSMainMenu()->getBtnPlayGame(),
		iBG.getX() + 102, iBG.getY() + 360, 0);
	btnPlayGame->fire->SetCallBack(this, &MainMenuScreen::BtnPlayGameChoosed);
	btnPlayGame->iSkinButton.setDepth(0.01f);

	btnLoadGame = new MyButton<MainMenuScreen>(RSMainMenu::getRSMainMenu()->getBtnLoadGame(),
		iBG.getX() + 102 + 180, iBG.getY() + 360, 1);
	btnLoadGame->fire->SetCallBack(this, &MainMenuScreen::BtnLoadGameChoosed);
	btnLoadGame->iSkinButton.setDepth(0.01f);

	btnOption = new MyButton<MainMenuScreen>(RSMainMenu::getRSMainMenu()->getBtnOption(),
		iBG.getX() + 102 + 360, iBG.getY() + 360, 2);
	btnOption->fire->SetCallBack(this, &MainMenuScreen::BtnOptionChooosed);
	btnOption->iSkinButton.setDepth(0.01f);

	btnAboutAndHelp = new MyButton<MainMenuScreen>(RSMainMenu::getRSMainMenu()->getBtnAboutAndHelp(),
		iBG.getX() + 102 + 540, iBG.getY() + 360, 3);
	btnAboutAndHelp->fire->SetCallBack(this, &MainMenuScreen::BtnAboutAndHelpChoosed);
	btnAboutAndHelp->iSkinButton.setDepth(0.01f);

	btnExit = new MyButton<MainMenuScreen>(RSMainMenu::getRSMainMenu()->getBtnExit(),
		iBG.getX() + 102 + 720, iBG.getY() + 360, 4);
	btnExit->fire->SetCallBack(this, &MainMenuScreen::BtnExitChoosed);
	btnExit->iSkinButton.setDepth(0.01f);
}

void MainMenuScreen::Update(float deltaTime){
	btnPlayGame->UpdateInput(btnChoosing, isChoosed);
	btnLoadGame->UpdateInput(btnChoosing, isChoosed);
	btnOption->UpdateInput(btnChoosing, isChoosed);
	btnAboutAndHelp->UpdateInput(btnChoosing, isChoosed);
	btnExit->UpdateInput(btnChoosing, isChoosed);
}

void MainMenuScreen::Draw(){
	if(pDeviceDX->BeginScene())
	{
		pDeviceDX->Clear(0,NULL,D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, D3DCOLOR_XRGB(135,206,250), 1.0f, 0);
		spriteHandler->Begin(D3DXSPRITE_SORT_DEPTH_FRONTTOBACK | D3DXSPRITE_ALPHABLEND);
		
		mainMenuBG->Draw(spriteHandler, iBG);

		menuFont->RenderText(350, 260, "MAIN MENU", D3DXCOLOR(255, 0 ,0, 255));

		btnPlayGame->Draw(spriteHandler);
		btnLoadGame->Draw(spriteHandler);
		btnOption->Draw(spriteHandler);
		btnAboutAndHelp->Draw(spriteHandler);
		btnExit->Draw(spriteHandler);
		
		spriteHandler->End();
		pDeviceDX->EndScene();
	}

	pDeviceDX->Present(NULL,NULL,NULL,NULL);
}

void MainMenuScreen::Release(){

}

void MainMenuScreen::BtnPlayGameChoosed(int _id){
	this->GetGamePlay()->setNextState(new ChooseLevelScreen(this->GetGamePlay()));
	isChoosed = false;
}

void MainMenuScreen::BtnLoadGameChoosed(int _id){
	if (InGameController::getInGameController()->LoadInfoFromSaved() == 1)
	{
		LevelController::getLevelController()->ISLOADGAME = true;
		this->GetGamePlay()->setNextState(new LoadingScreen(this->GetGamePlay()));
	}
	isChoosed = false;
}

void MainMenuScreen::BtnOptionChooosed(int _id){
	this->GetGamePlay()->setNextState(new OptionScreen(this->GetGamePlay()));
	isChoosed = false;
}

void MainMenuScreen::BtnAboutAndHelpChoosed(int _id){
	this->GetGamePlay()->setNextState(new AboutScreen(this->GetGamePlay()));
	isChoosed = false;
}

void MainMenuScreen::BtnExitChoosed(int _id){
	isChoosed = false;
	PostQuitMessage(0);
}