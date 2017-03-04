#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "Sprite.h"
#include "DXFont.h"

class RSMainGame{
	//Singleton
private:
	static RSMainGame* instance;

	Sprite* marioSmallSprite;
	Sprite* marioBigSprite;
	Sprite* marioSuperSprite;
	Sprite* baseLandSprite;
	Sprite* brickSprite;
	Sprite* brickBreakSprite;
	Sprite* brickExplodeSprite;
	Sprite* mushroomBadSprite;
	Sprite* turtleSprite;
	Sprite* coinSprite;
	Sprite* mushroomSprite;
	Sprite* questionBrickSprite;
	Sprite* flowerSprite;
	Sprite* pipeSprite;
	Sprite* bulletMarioSprite;
	Sprite* bulletBossSprite;
	Sprite* bossSprite;
	Sprite* bossBreakSprite;
	Sprite* cloudSprite;
	Sprite* grassSprite;
	Sprite* winPoleSprite;
	Sprite* buildingSprite;
	Sprite* fenceSprite;
	Sprite* poleSprite;
	Sprite* postSprite;
	DXFont* gameFont;

	Sprite* iconMario;
	Sprite* iconBlood;

	Sprite* btnResume;
	Sprite* btnSaveAndQuit;
	Sprite* btnBackMainMenu;
	Sprite* btnSoundOn;
	Sprite* btnSoundOff;
	Sprite* btnMusicOn;
	Sprite* btnMusicOff;
	Sprite* dialogPause;

	Sprite* btnNextLevel;
	Sprite* btnPlayAgain;
	Sprite* dialogLost;
	Sprite* dialogWin;
public:
	RSMainGame(void);
	~RSMainGame();
	static RSMainGame* getRSMainGame();

	void InitRS(LPDIRECT3DDEVICE9 pDeviceDX);

	Sprite* getDialogWin(){
		return dialogWin;
	}

	Sprite* getDialogLost(){
		return dialogLost;
	}

	Sprite* getBtnNextLevel(){
		return btnNextLevel;
	}

	Sprite* getBtnPlayAgain(){
		return btnPlayAgain;
	}

	Sprite* getDialogPause(){
		return dialogPause;
	}

	Sprite* getBtnMusicOff(){
		return btnMusicOff;
	}

	Sprite* getBtnMusicOn(){
		return btnMusicOn;
	}

	Sprite* getBtnBackToMainMenu(){
		return btnBackMainMenu;
	}

	Sprite* getBtnSoundOff(){
		return btnSoundOff;
	}

	Sprite* getBtnSoundOn(){
		return btnSoundOn;
	}

	Sprite* getBtnResume(){
		return btnResume;
	}

	Sprite* getBtnSaveAndQuit(){
		return btnSaveAndQuit;
	}

	Sprite* getIconBlood(){
		return iconBlood;
	}

	Sprite* getIconMario(){
		return iconMario;
	}

	Sprite* getPostSprite(){
		return postSprite;
	}

	Sprite* getPoleSprite(){
		return poleSprite;
	}

	Sprite* getFenceSprite(){
		return fenceSprite;
	}

	Sprite* getWinpoleSprite()
	{
		return winPoleSprite;
	}

	Sprite* getBuildingSprite(){
		return buildingSprite;
	}

	Sprite* getCloudSprite(){
		return cloudSprite;
	}

	Sprite* getGrassSprite(){
		return grassSprite;
	}

	Sprite* getMarioSmallSprite(){
		return marioSmallSprite;
	}

	Sprite* getMarioBigSprite(){
		return marioBigSprite;
	}

	Sprite* getMarioSuperSprite(){
		return marioSuperSprite;
	}

	Sprite* getBaseLandeSprite(){
		return baseLandSprite;
	}

	Sprite* getBrickSprite(){
		return brickSprite;
	}

	Sprite* getBrickBreakSprite(){
		return brickBreakSprite;
	}

	Sprite* getBrickExplode(){
		return brickExplodeSprite;
	}

	Sprite* getMushroomBad(){
		return mushroomBadSprite;
	}

	Sprite* getTurtleSprite(){
		return turtleSprite;
	}

	Sprite* getCoinSprite(){
		return coinSprite;
	}

	Sprite* getMushroomSprite(){
		return mushroomSprite;
	}

	Sprite* getQuestionBrickSprite(){
		return questionBrickSprite;
	}

	Sprite* getFlowerSprite(){
		return flowerSprite;
	}

	Sprite* getBaseLandSprite(){
		return baseLandSprite;
	}

	Sprite* getPipeSprite(){
		return pipeSprite;
	}

	Sprite* getBulletMarioSprite(){
		return bulletMarioSprite;	
	}

	Sprite* getBulletBossSprite(){
		return bulletBossSprite;
	}

	Sprite* getBossSprite(){
		return bossSprite;
	}

	Sprite* getBossBreakSprite(){
		return bossBreakSprite;
	}

	DXFont* getGameFont(){
		return gameFont;
	}
};

