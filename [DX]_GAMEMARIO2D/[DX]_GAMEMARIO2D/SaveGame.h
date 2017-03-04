#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "InGameController.h"

using namespace std;

class SaveGame{
private:
	static SaveGame* instance;

	SaveGame(void);
public:
	~SaveGame(void);

	static SaveGame* getSaveGame();
	
	int posMarioX;
	int posMarioY;
	int IDMario;
	int timePlay;

	int life;
	int numberCoin;
	int score;
	int level;
	int maxWidth;
	int maxHeight;

	void SaveGameToFile(){
		ofstream inFile;

		char fileName[30];
		sprintf(fileName, "data//Save//gameSaved.txt");

		inFile.open(fileName, std::ofstream::out | std::ofstream::trunc);

		life = InGameController::getInGameController()->LIFE;
		numberCoin = InGameController::getInGameController()->NUMBERCOIN;
		score = InGameController::getInGameController()->SCORE;
		level = InGameController::getInGameController()->LEVELMAP;
		maxWidth = InGameController::getInGameController()->MAXWIDTH;
		maxHeight = InGameController::getInGameController()->MAXHEIGHT;

		inFile<<posMarioX<<" "<<posMarioY<<" "<<IDMario<<" "<<timePlay<<" "<<life<<" "<<numberCoin<<" "<<
			score<<" "<<level<<" "<<maxWidth<<" "<<maxHeight<<endl;

		InGameController::getInGameController()->QUADTREE->SaveQuadTree(inFile);

		inFile.close();
	}
};