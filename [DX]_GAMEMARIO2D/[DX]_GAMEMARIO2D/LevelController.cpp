#include "LevelController.h"

LevelController* LevelController::instance = NULL;

LevelController::LevelController(void){
	NUMLEVEL = 3;
	LEVELCHOOSED = 0;
	ISLOADGAME = false;
}

LevelController::~LevelController(void){

}

LevelController* LevelController::getLevelController(){
	if (instance == NULL)
	{
		instance = new LevelController();
	}
	return instance;
}

