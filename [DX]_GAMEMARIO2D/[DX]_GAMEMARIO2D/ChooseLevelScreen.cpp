#include "ChooseLevelScreen.h"
#include "RSMainMenu.h"
#include "AudioManager.h"
#include "MainMenuScreen.h"
#include "LevelController.h"
#include "InGameController.h"
#include "LoadingScreen.h"

ChooseLevelScreen::ChooseLevelScreen(IPlay *iPlay):IState(iPlay){
	this->ID = CHOOSELEVEL;
	btnChoosing = 0;
	isChoosed = false;
}

ChooseLevelScreen::~ChooseLevelScreen(void){

}

void ChooseLevelScreen::OnKeyDown(int keyCode){
	switch(keyCode){
	case DIK_LEFT:
		AudioManager::getAudioManager()->Play("e_chose");
		if (btnChoosing == 0)
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
		this->GetGamePlay()->setNextState(new MainMenuScreen(this->GetGamePlay()));
		break;
	}
}

void ChooseLevelScreen::Init(){
	D3DXCreateSprite(pDeviceDX, &spriteHandler);

	AudioManager::getAudioManager()->StopAllBack();
	AudioManager::getAudioManager()->Play("b_menu");

	menuFont = RSMainMenu::getRSMainMenu()->getGameFont();
	levelFont = RSMainMenu::getRSMainMenu()->getLevelFont();

	mainMenuBG = RSMainMenu::getRSMainMenu()->getMainMenuBG();
	iBG.setXY(0,0);
	iBG.setDepth(0.02f);

	btnLevel1 = new MyButton<ChooseLevelScreen>(RSMainMenu::getRSMainMenu()->getBtnLevel(),
		iBG.getX() + 282, iBG.getY() + 340, 0);
	btnLevel1->fire->SetCallBack(this, &ChooseLevelScreen::BtnLevel1Choosed);
	btnLevel1->iSkinButton.setDepth(0.01f);

	btnLevel2 = new MyButton<ChooseLevelScreen>(RSMainMenu::getRSMainMenu()->getBtnLevel(),
		iBG.getX() + 282 + 180, iBG.getY() + 340, 1);
	btnLevel2->fire->SetCallBack(this, &ChooseLevelScreen::BtnLevel2Choosed);
	btnLevel2->iSkinButton.setDepth(0.01f);

	btnLevel3 = new MyButton<ChooseLevelScreen>(RSMainMenu::getRSMainMenu()->getBtnLevel(),
		iBG.getX() + 282 + 360, iBG.getY() + 340, 2);
	btnLevel3->fire->SetCallBack(this, &ChooseLevelScreen::BtnLevel3Choosed);
	btnLevel3->iSkinButton.setDepth(0.01f);
}

void ChooseLevelScreen::Update(float deltaTime){
	btnLevel1->UpdateInput(btnChoosing, isChoosed);
	btnLevel2->UpdateInput(btnChoosing, isChoosed);
	btnLevel3->UpdateInput(btnChoosing, isChoosed);
}

void ChooseLevelScreen::Draw(){
	if(pDeviceDX->BeginScene())
	{
		pDeviceDX->Clear(0,NULL,D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, D3DCOLOR_XRGB(135,206,250), 1.0f, 0);
		spriteHandler->Begin(D3DXSPRITE_SORT_DEPTH_FRONTTOBACK | D3DXSPRITE_ALPHABLEND);

		mainMenuBG->Draw(spriteHandler, iBG);

		menuFont->RenderText(320, 260, "CHOOSE LEVEL", D3DXCOLOR(255, 0 ,0, 255));

		/*menuFont->RenderText(362, 360, "Sound", D3DXCOLOR(255, 127 ,80, 255));
		menuFont->RenderText(382 + 150, 360, "Music", D3DXCOLOR(50,205,50, 255));*/

		levelFont->RenderText(288, 370, "Level1", D3DXCOLOR(255, 127 ,80, 255));
		levelFont->RenderText(288 + 180, 370, "Level2", D3DXCOLOR(255, 127 ,80, 255));
		levelFont->RenderText(288 + 360, 370, "Level3", D3DXCOLOR(255, 127 ,80, 255));

		menuFont->RenderText(180, 650, "Press ESC to back Main Menu", D3DXCOLOR(255,140,0, 255));

		btnLevel1->Draw(spriteHandler);
		btnLevel3->Draw(spriteHandler);
		btnLevel2->Draw(spriteHandler);

		spriteHandler->End();
		pDeviceDX->EndScene();
	}

	pDeviceDX->Present(NULL,NULL,NULL,NULL);
}

void ChooseLevelScreen::Release(){

}

void ChooseLevelScreen::BtnLevel1Choosed(int _id){
	LevelController::getLevelController()->LEVELCHOOSED = 1;
	InGameController::getInGameController()->ResetBasicFigure();
	this->GetGamePlay()->setNextState(new LoadingScreen(this->GetGamePlay()));
	isChoosed = false;
}

void ChooseLevelScreen::BtnLevel2Choosed(int _id){
	LevelController::getLevelController()->LEVELCHOOSED = 2;
	InGameController::getInGameController()->ResetBasicFigure();
	this->GetGamePlay()->setNextState(new LoadingScreen(this->GetGamePlay()));
	isChoosed = false;
}

void ChooseLevelScreen::BtnLevel3Choosed(int _id){
	LevelController::getLevelController()->LEVELCHOOSED = 3;
	InGameController::getInGameController()->ResetBasicFigure();
	this->GetGamePlay()->setNextState(new LoadingScreen(this->GetGamePlay()));
	isChoosed = false;
}