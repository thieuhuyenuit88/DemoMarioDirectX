#include "SaveGame.h"

SaveGame* SaveGame::instance = NULL;

SaveGame::SaveGame(void){

}

SaveGame::~SaveGame(void){

}

SaveGame* SaveGame::getSaveGame(){
	if (instance == NULL)
	{
		instance = new SaveGame();
	}
	return instance;
}