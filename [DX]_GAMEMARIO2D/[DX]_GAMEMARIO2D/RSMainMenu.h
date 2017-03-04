#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "Sprite.h"
#include "DXFont.h"

class RSMainMenu{
private:
	static RSMainMenu* instance;
	void InitRS(LPDIRECT3DDEVICE9 pDeviceDx);

	Sprite* btnPlayGame;
	Sprite* btnLoadGame;
	Sprite* btnOption;
	Sprite* btnAboutAndHelp;
	Sprite* btnExit;

	Sprite* btnSoundOn;
	Sprite* btnSoundOff;
	Sprite* btnMusicOn;
	Sprite* btnMusicOff;

	Sprite* mainMenuBG;
	Sprite* mainAboutBG;

	Sprite* btnLevel;
	DXFont* gameFont;
	DXFont* levelFont;
public:
	RSMainMenu(void);
	~RSMainMenu(void);

	static RSMainMenu* getRSMainMenu();
	
	Sprite* getBtnLevel(){
		return btnLevel;
	}

	DXFont* getLevelFont(){
		return levelFont;
	}

	Sprite* getAboutBG(){
		return mainAboutBG;
	}

	DXFont* getGameFont(){
		return gameFont;
	}

	Sprite* getBtnSoundOff(){
		return btnSoundOff;
	}

	Sprite* getBtnSoundOn(){
		return btnSoundOn;
	}

	Sprite* getBtnMusicOff(){
		return btnMusicOff;
	}

	Sprite* getBtnMusicOn(){
		return btnMusicOn;
	}

	Sprite* getMainMenuBG(){
		return mainMenuBG;
	}

	Sprite* getBtnExit(){
		return btnExit;
	}

	Sprite* getBtnAboutAndHelp(){
		return btnAboutAndHelp;
	}

	Sprite* getBtnOption(){
		return btnOption;
	}

	Sprite* getBtnLoadGame(){
		return btnLoadGame;
	}

	Sprite* getBtnPlayGame(){
		return btnPlayGame;
	}
};