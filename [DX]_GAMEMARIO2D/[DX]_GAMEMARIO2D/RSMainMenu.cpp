#include "RSMainMenu.h"
#include "DXDeviceManager.h"

RSMainMenu* RSMainMenu::instance = NULL;

RSMainMenu::RSMainMenu(void){

}

RSMainMenu::~RSMainMenu(void){

}

RSMainMenu* RSMainMenu::getRSMainMenu(){
	if (instance == NULL)
	{
		instance = new RSMainMenu();
		instance->InitRS(DXDeviceManager::getInstanceDXDevice()->getDevice());
	}
	return instance;
}

void RSMainMenu::InitRS(LPDIRECT3DDEVICE9 pDeviceDx){
	btnPlayGame = new Sprite(pDeviceDx, "data//Image//btnPlayGame.png", 100, 100, 2);
	btnOption = new Sprite(pDeviceDx, "data//Image//btnOption.png", 100, 100, 2);
	btnAboutAndHelp = new Sprite(pDeviceDx, "data//Image//btnAboutAndHelp.png", 100, 100, 2);
	btnLoadGame = new Sprite(pDeviceDx, "data//Image//BtnLoadGame.png", 100, 100, 2);
	btnExit = new Sprite(pDeviceDx, "data//Image//btnExitGame.png", 100, 100, 2);

	mainMenuBG = new Sprite(pDeviceDx,"data//Image//BGMainMenu.png", 1024, 768, 1);

	btnSoundOn = new Sprite(pDeviceDx, "data//Image//btnSoundOn.png", 90, 90, 2);
	btnSoundOff = new Sprite(pDeviceDx, "data//Image//btnSoundOff.png", 90, 90, 2);
	btnMusicOn = new Sprite(pDeviceDx, "data//Image//btnMusicOn.png", 90, 90, 2);
	btnMusicOff = new Sprite(pDeviceDx, "data//Image//btnMusicOff.png", 90, 90, 2);

	mainAboutBG = new Sprite(pDeviceDx,"data//Image//AboutAndHelpScreen.png", 1024, 768, 1);

	gameFont = new DXFont(pDeviceDx, "data//Font//QlassikBold_TB.ttf", "QlassikBold", 60, true);
	levelFont = new DXFont(pDeviceDx, "data//Font//QlassikBold_TB.ttf", "QlassikBold", 34, true);

	btnLevel = new Sprite(pDeviceDx, "data//Image//btnLevel.png", 100, 100, 2);
}