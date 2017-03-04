#include "AboutScreen.h"
#include "RSMainMenu.h"
#include "AudioManager.h"
#include "MainMenuScreen.h"

AboutScreen::AboutScreen(IPlay *iPlay):IState(iPlay){
	this->ID = ABOUTANDHELP;
}

AboutScreen::~AboutScreen(void){

}

void AboutScreen::OnKeyDown(int keyCode){
	switch(keyCode){
	case DIK_ESCAPE:
		AudioManager::getAudioManager()->Play("e_chose");
		this->GetGamePlay()->setNextState(new MainMenuScreen(this->GetGamePlay()));
		break;
	}
}

void AboutScreen::Init(){
	D3DXCreateSprite(pDeviceDX, &spriteHandler);

	mainMenuBG = RSMainMenu::getRSMainMenu()->getAboutBG();
	iBG.setXY(0,0);
	iBG.setDepth(0.02f);
}

void AboutScreen::Update(float deltaTime){

}

void AboutScreen::Draw(){
	if(pDeviceDX->BeginScene())
	{
		pDeviceDX->Clear(0,NULL,D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, D3DCOLOR_XRGB(135,206,250), 1.0f, 0);
		spriteHandler->Begin(D3DXSPRITE_SORT_DEPTH_FRONTTOBACK | D3DXSPRITE_ALPHABLEND);

		mainMenuBG->Draw(spriteHandler, iBG);
		
		spriteHandler->End();
		pDeviceDX->EndScene();
	}

	pDeviceDX->Present(NULL,NULL,NULL,NULL);
}

void AboutScreen::Release(){

}