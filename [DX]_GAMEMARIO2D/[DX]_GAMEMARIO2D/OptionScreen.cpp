#include "OptionScreen.h"
#include "RSMainMenu.h"
#include "AudioManager.h"
#include "MainMenuScreen.h"

OptionScreen::OptionScreen(IPlay *iPlay):IState(iPlay){
	this->ID = OPTION;
	btnChoosing = 0;
	isChoosed = false;
}

OptionScreen::~OptionScreen(void){

}

void OptionScreen::OnKeyDown(int keyCode){
	switch(keyCode){
	case DIK_LEFT:
		AudioManager::getAudioManager()->Play("e_chose");
		if (btnChoosing == 0 || btnChoosing == 1)
		{
			if (isMusic)
			{
				btnChoosing = 2;
			}else{
				btnChoosing = 3;
			}
		}else if (btnChoosing == 2 || btnChoosing == 3){
			if (isSound)
			{
				btnChoosing = 0;
			}else{
				btnChoosing = 1;
			}
		}
		break;
	case DIK_RIGHT:
		AudioManager::getAudioManager()->Play("e_chose");
		if (btnChoosing == 0 || btnChoosing == 1)
		{
			if (isMusic)
			{
				btnChoosing = 2;
			}else{
				btnChoosing = 3;
			}
		}else if (btnChoosing == 2 || btnChoosing == 3){
			if (isSound)
			{
				btnChoosing = 0;
			}else{
				btnChoosing = 1;
			}
		}
		break;
	case DIK_SPACE:
		AudioManager::getAudioManager()->Play("e_click");
		isChoosed = true;
		break;
	case DIK_ESCAPE:
		AudioManager::getAudioManager()->Play("e_chose");
		this->GetGamePlay()->setNextState(new MainMenuScreen(this->GetGamePlay()));
		break;
	}
}

void OptionScreen::Init(){
	D3DXCreateSprite(pDeviceDX, &spriteHandler);

	AudioManager::getAudioManager()->StopAllBack();
	AudioManager::getAudioManager()->Play("b_option_state");

	menuFont = RSMainMenu::getRSMainMenu()->getGameFont();

	mainMenuBG = RSMainMenu::getRSMainMenu()->getMainMenuBG();
	iBG.setXY(0,0);
	iBG.setDepth(0.02f);

	btnSoundOn = new MyButton<OptionScreen>(RSMainMenu::getRSMainMenu()->getBtnSoundOn(),
		iBG.getX() + 382, iBG.getY() + 420, 0);
	btnSoundOn->fire->SetCallBack(this, &OptionScreen::BtnSoundOnChoosed);

	btnSoundOff = new MyButton<OptionScreen>(RSMainMenu::getRSMainMenu()->getBtnSoundOff(),
		iBG.getX() + 382, iBG.getY() + 420, 1);
	btnSoundOff->fire->SetCallBack(this, &OptionScreen::BtnSoundOffChoosed);

	btnMusicOn = new MyButton<OptionScreen>(RSMainMenu::getRSMainMenu()->getBtnMusicOn(),
		iBG.getX() + 382 + 170, iBG.getY() + 420, 2);
	btnMusicOn->fire->SetCallBack(this, &OptionScreen::BtnMusicOnChoosed);

	btnMusicOff = new MyButton<OptionScreen>(RSMainMenu::getRSMainMenu()->getBtnMusicOff(),
		iBG.getX() + 382 + 170, iBG.getY() + 420, 3);
	btnMusicOff->fire->SetCallBack(this, &OptionScreen::BtnMusicOffChooosed);

	isMusic = AudioManager::getAudioManager()->isBackground;
	isSound = AudioManager::getAudioManager()->isEffect;
}

void OptionScreen::Update(float deltaTime){
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

void OptionScreen::Draw(){
	if(pDeviceDX->BeginScene())
	{
		pDeviceDX->Clear(0,NULL,D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, D3DCOLOR_XRGB(135,206,250), 1.0f, 0);
		spriteHandler->Begin(D3DXSPRITE_SORT_DEPTH_FRONTTOBACK | D3DXSPRITE_ALPHABLEND);

		mainMenuBG->Draw(spriteHandler, iBG);

		menuFont->RenderText(420, 260, "OPTION", D3DXCOLOR(255, 140, 0, 255));

		menuFont->RenderText(362, 360, "Sound", D3DXCOLOR(255, 127 ,80, 255));
		menuFont->RenderText(382 + 150, 360, "Music", D3DXCOLOR(50,205,50, 255));

		menuFont->RenderText(180, 650, "Press ESC to back Main Menu", D3DXCOLOR(255,140,0, 255));

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

		spriteHandler->End();
		pDeviceDX->EndScene();
	}

	pDeviceDX->Present(NULL,NULL,NULL,NULL);
}

void OptionScreen::Release(){

}

void OptionScreen::BtnSoundOnChoosed(int _id){
	isChoosed = false;

	AudioManager::getAudioManager()->isEffect = false;
	isSound = false;

	btnChoosing = 1;
}

void OptionScreen::BtnSoundOffChoosed(int _id){
	isChoosed = false;

	AudioManager::getAudioManager()->isEffect = true;
	isSound = true;

	btnChoosing = 0;
}

void OptionScreen::BtnMusicOnChoosed(int _id){
	isChoosed = false;

	AudioManager::getAudioManager()->StopAllBack();
	AudioManager::getAudioManager()->isBackground = false;
	isMusic = false;

	btnChoosing = 3;
}

void OptionScreen::BtnMusicOffChooosed(int _id){
	isChoosed = false;

	AudioManager::getAudioManager()->isBackground = true;
	AudioManager::getAudioManager()->Play("b_option_state");
	isMusic = true;

	btnChoosing = 2;
}
