#include "PauseScreen.h"
#include "RSMainGame.h"
#include <dinput.h>
#include "StateTestGame.h"
#include "AudioManager.h"
#include "MainMenuScreen.h"
#include "SaveGame.h"

PauseScreen::PauseScreen(void){

}

PauseScreen::~PauseScreen(void){

}

PauseScreen::PauseScreen(StateTestGame* _mainGame){
	mainGame = _mainGame;
	btnChoosing = 0;
	isChoosed = false;
	Init();
}

void PauseScreen::OnKeyDown(int _keyCode){
	switch(_keyCode){
	case DIK_LEFT:
		AudioManager::getAudioManager()->Play("e_chose");
		if (btnChoosing == 0)
		{
			if (isMusic)
			{
				btnChoosing = 5;
			}else{
				btnChoosing = 6;
			}
		}else if (btnChoosing == 5 || btnChoosing == 6)
		{
			if (isSound)
			{
				btnChoosing = 3;
			}else{
				btnChoosing = 4;
			}
		}else if (btnChoosing == 3 ||btnChoosing == 4)
		{
			btnChoosing = 2;
		}else{
			btnChoosing -= 1;
		}
		break;
	case DIK_RIGHT:
		AudioManager::getAudioManager()->Play("e_chose");
		if (btnChoosing == 2)
		{
			if (isSound)
			{
				btnChoosing = 3;
			}else{
				btnChoosing = 4;
			}
		}else if (btnChoosing == 5 || btnChoosing == 6)
		{
			btnChoosing = 0;
		}else if (btnChoosing == 3 ||btnChoosing == 4)
		{
			if (isMusic)
			{
				btnChoosing = 5;
			}else{
				btnChoosing = 6;
			}
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
		mainGame->stateInGame = RUNNING;
		break;
	}
}

void PauseScreen::Init(){
	dialogPauseBG = RSMainGame::getRSMainGame()->getDialogPause();
	iDialogBG.setXY((g_SCREEN_WIDTH - 400)/2, (g_SCREEN_HEIGHT - 300)/2);

	btnResume = new MyButton<PauseScreen>(RSMainGame::getRSMainGame()->getBtnResume(), 
		iDialogBG.getX() + 80, iDialogBG.getY() + 70, 0);
	btnResume->fire->SetCallBack(this, &PauseScreen::BtnResumeChoosed);

	btnBackMenu = new MyButton<PauseScreen>(RSMainGame::getRSMainGame()->getBtnBackToMainMenu(), 
		iDialogBG.getX() + 155, iDialogBG.getY() + 150, 2);
	btnBackMenu->fire->SetCallBack(this, &PauseScreen::BtnBackMenuChoosed);

	btnSaveAndQuit = new MyButton<PauseScreen>(RSMainGame::getRSMainGame()->getBtnSaveAndQuit(), 
		iDialogBG.getX() + 230, iDialogBG.getY() + 70, 1);
	btnSaveAndQuit->fire->SetCallBack(this, &PauseScreen::BtnSaveAndQuitChoosed);

	btnSoundOn = new MyButton<PauseScreen>(RSMainGame::getRSMainGame()->getBtnSoundOn(), 
		iDialogBG.getX() + 20, iDialogBG.getY() + 200, 3);
	btnSoundOn->fire->SetCallBack(this, &PauseScreen::BtnSoundOnChoosed);

	btnSoundOff = new MyButton<PauseScreen>(RSMainGame::getRSMainGame()->getBtnSoundOff(), 
		iDialogBG.getX() + 20, iDialogBG.getY() + 200, 4);
	btnSoundOff->fire->SetCallBack(this, &PauseScreen::BtnSoundOffChoosed);

	btnMusicOn = new MyButton<PauseScreen>(RSMainGame::getRSMainGame()->getBtnMusicOn(), 
		iDialogBG.getX() + 290, iDialogBG.getY() + 200, 5);
	btnMusicOn->fire->SetCallBack(this, &PauseScreen::BtnMusicOnChoosed);

	btnMusicOff = new MyButton<PauseScreen>(RSMainGame::getRSMainGame()->getBtnMusicOff(), 
		iDialogBG.getX() + 290, iDialogBG.getY() + 200, 6);
	btnMusicOff->fire->SetCallBack(this, &PauseScreen::BtnMusicOffChoosed);

	isMusic = AudioManager::getAudioManager()->isBackground;
	isSound = AudioManager::getAudioManager()->isEffect;
}

void PauseScreen::Update(float deltaTime){
	btnResume->UpdateInput(btnChoosing, isChoosed);
	btnSaveAndQuit->UpdateInput(btnChoosing, isChoosed);
	btnBackMenu->UpdateInput(btnChoosing, isChoosed);
	
	if (isMusic)
	{
		btnMusicOn->UpdateInput(btnChoosing, isChoosed);
	}else{
		btnMusicOff->UpdateInput(btnChoosing, isChoosed);
	}
	
	
	if (isSound)
	{
		btnSoundOn->UpdateInput(btnChoosing, isChoosed);
	}else{
		btnSoundOff->UpdateInput(btnChoosing, isChoosed);
	}
}

void PauseScreen::Draw(LPD3DXSPRITE spriteHandler){

	dialogPauseBG->Draw(spriteHandler, iDialogBG);

	btnResume->Draw(spriteHandler);
	btnSaveAndQuit->Draw(spriteHandler);
	btnBackMenu->Draw(spriteHandler);

	if (isMusic)
	{
		btnMusicOn->Draw(spriteHandler);
	}else{
		btnMusicOff->Draw(spriteHandler);
	}

	if (isSound)
	{
		btnSoundOn->Draw(spriteHandler);
	}else{
		btnSoundOff->Draw(spriteHandler);
	}
}

void PauseScreen::Release(){

}

void PauseScreen::BtnResumeChoosed(int _id){
	mainGame->stateInGame = RUNNING;
	isChoosed = false;
}

void PauseScreen::BtnBackMenuChoosed(int _id){
	mainGame->GetGamePlay()->setNextState(new MainMenuScreen(mainGame->GetGamePlay()));
	isChoosed = false;
}

void PauseScreen::BtnSaveAndQuitChoosed(int _id){
	if (!mainGame->getMario()->isWinning)
	{
		for (vector<DynamicObject*>::iterator f = mainGame->getCameraContentDynamic()->begin(); f!= mainGame->getCameraContentDynamic()->end(); f++){
			InGameController::getInGameController()->QUADTREE->Insert(*f);
		}

		for (vector<StaticObject*>::iterator f = mainGame->getCameraContentStatic()->begin(); f!= mainGame->getCameraContentStatic()->end(); f++){
			InGameController::getInGameController()->QUADTREE->Insert(*f);
		}

		SaveGame::getSaveGame()->posMarioX = mainGame->getMario()->getPosX();
		SaveGame::getSaveGame()->posMarioY = mainGame->getMario()->getPosY();
		SaveGame::getSaveGame()->IDMario = mainGame->getMario()->getID();
		SaveGame::getSaveGame()->timePlay = mainGame->getTimePlay();

		SaveGame::getSaveGame()->SaveGameToFile();
		mainGame->GetGamePlay()->setNextState(new MainMenuScreen(mainGame->GetGamePlay()));
	}

	isChoosed = false;
}

void PauseScreen::BtnMusicOffChoosed(int _id){
	isChoosed = false;
	AudioManager::getAudioManager()->isBackground = true;
	AudioManager::getAudioManager()->Play(InGameController::getInGameController()->SONG_PLAYING);
	isMusic = true;
	btnChoosing = 5;
}

void PauseScreen::BtnMusicOnChoosed(int _id){
	isChoosed = false;
	AudioManager::getAudioManager()->StopAllBack();
	AudioManager::getAudioManager()->isBackground = false;
	isMusic = false;
	btnChoosing = 6;
}

void PauseScreen::BtnSoundOffChoosed(int _id){
	isChoosed = false;
	AudioManager::getAudioManager()->isEffect = true;
	isSound = true;
	btnChoosing = 3;
}

void PauseScreen::BtnSoundOnChoosed(int _id){
	isChoosed = false;
	AudioManager::getAudioManager()->isEffect = false;
	isSound = false;
	btnChoosing = 4;
}