#include "RSMainGame.h"
#include "DXDeviceManager.h"

RSMainGame* RSMainGame::instance = NULL;

RSMainGame::RSMainGame(void){

}

RSMainGame::~RSMainGame(void){

}

RSMainGame* RSMainGame::getRSMainGame(){
	if (instance == NULL)
	{
		instance = new RSMainGame();
		instance->InitRS(DXDeviceManager::getInstanceDXDevice()->getDevice());
	}
	return instance;
}

void RSMainGame::InitRS(LPDIRECT3DDEVICE9 pDeviceDX){
	marioSmallSprite = new Sprite(pDeviceDX, "data//Image//MarioSmaller.png", 50, 50, 6);
	marioBigSprite = new Sprite(pDeviceDX, "data//Image//MarioLager.png", 50, 100, 6);
	marioSuperSprite = new Sprite(pDeviceDX, "data//Image//MarioSuper.png", 50, 100, 6);
	baseLandSprite = new Sprite(pDeviceDX, "data//Image//Base.png", 50, 50, 3);
	brickSprite = new Sprite(pDeviceDX, "data//Image//brick.png", 50, 50, 2);
	brickBreakSprite = new Sprite(pDeviceDX, "data//Image//Brick_Break.png", 50, 50, 1);
	brickExplodeSprite = new Sprite(pDeviceDX, "data//Image//Brick_Break.png", 25, 25, 2);
	mushroomBadSprite = new Sprite(pDeviceDX, "data//Image//Fungi.png", 50, 50, 3);
	turtleSprite = new Sprite(pDeviceDX, "data//Image//tittle.png", 50, 72, 5);
	coinSprite = new Sprite(pDeviceDX, "data//Image//Coin.png", 50, 50, 7);
	mushroomSprite = new Sprite(pDeviceDX, "data//Image//Lager.png", 50, 50, 2);
	questionBrickSprite = new Sprite(pDeviceDX, "data//Image//Question.png", 50, 50, 3);
	flowerSprite = new Sprite(pDeviceDX, "data//Image//Flower.png", 50, 50, 4);
	baseLandSprite = new Sprite(pDeviceDX, "data//Image//Base.png", 50, 50, 3);
	pipeSprite = new Sprite(pDeviceDX, "data//Image//pipe.png", 50, 50, 2);
	bulletMarioSprite = new Sprite(pDeviceDX, "data//Image//Fire.png", 34, 34, 10);
	bulletBossSprite = new Sprite(pDeviceDX, "data//Image//FireBoss.png", 89, 50, 3);
	bossSprite = new Sprite(pDeviceDX, "data//Image//Boss.png", 100, 110, 4);
	bossBreakSprite = new Sprite(pDeviceDX, "data//Image//Boss.png", 25, 22, 4);

	gameFont = new DXFont(pDeviceDX, "data//Font//QlassikBold_TB.ttf", "QlassikBold", 33, false);
	
	cloudSprite = new Sprite(pDeviceDX, "data//Image//Cloud.png", 100, 80, 3);
	grassSprite = new Sprite(pDeviceDX, "data//Image//Grass.png", 100, 50, 3);
	winPoleSprite = new Sprite(pDeviceDX, "data//Image//win_pole.png", 50, 450, 1);
	buildingSprite = new Sprite(pDeviceDX, "data//Image//Building.png", 500, 550, 1);

	fenceSprite = new Sprite(pDeviceDX, "data//Image//fence.png", 50, 50, 6);
	postSprite = new Sprite(pDeviceDX, "data//Image//post.png", 50, 50, 3);
	poleSprite = new Sprite(pDeviceDX, "data//Image//pole.png", 50, 50, 6);

	iconMario = new Sprite(pDeviceDX, "data//Image//icon.png", 21, 22, 1);
	iconBlood = new Sprite(pDeviceDX, "data//Image//Blood.png", 10, 21, 1);


	btnResume = new Sprite(pDeviceDX, "data//Image//btnResume.png", 90, 90, 2);
	btnSaveAndQuit = new Sprite(pDeviceDX, "data//Image//btnSaveAndQuit.png", 90, 90, 2);
	btnBackMainMenu = new Sprite(pDeviceDX, "data//Image//btnBackMenu.png", 90, 90, 2);
	btnSoundOn = new Sprite(pDeviceDX, "data//Image//btnSoundOn.png", 90, 90, 2);
	btnSoundOff = new Sprite(pDeviceDX, "data//Image//btnSoundOff.png", 90, 90, 2);
	btnMusicOn = new Sprite(pDeviceDX, "data//Image//btnMusicOn.png", 90, 90, 2);
	btnMusicOff = new Sprite(pDeviceDX, "data//Image//btnMusicOff.png", 90, 90, 2);
	dialogPause = new Sprite(pDeviceDX, "data//Image//DialogPause.png", 400, 300, 1);
	

	btnNextLevel = new Sprite(pDeviceDX, "data//Image//btnNextLevel.png", 90, 90, 2);
	btnPlayAgain = new Sprite(pDeviceDX, "data//Image//btnAgain.png", 90, 90, 2);
	dialogWin = new Sprite(pDeviceDX, "data//Image//DialogWin.png", 400, 300, 1);
	dialogLost = new Sprite(pDeviceDX, "data//Image//DialogLost.png", 400, 300, 1);
}