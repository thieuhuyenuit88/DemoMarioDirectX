#pragma once
#include "Winpole.h"
#include "Building.h"
#include "Boss.h"
#include "Mario.h"
#include "QuadTree.h"
#include "ReadMap.h"

using namespace std;

class InGameController{
private:
	static InGameController* instance;
public:
	InGameController(void);
	~InGameController(void);
	
	//Basic digital in game
	int LIFE;
	int NUMBERCOIN;
	int SCORE;

	//Info from map
	Winpole* oWINPOLE;
	Building* oBUILDING;
	Boss* oBOSS;
	QuadTree* QUADTREE;
	Mario* oMARIO;

	int MAXHEIGHT;
	int MAXWIDTH;
	int LEVELMAP;
	int TIMEPLAY;
	int POSX, POSY;

	char* SONG_PLAYING;

	static InGameController* getInGameController();
	void LoadInfoFromMap(int _level);

	int LoadInfoFromSaved();
	void SavedDataToQuadTree(const string &_strNodeID, vector<tObj*> &_listObjects);

	//Deserialize Objects To QuadTree
	void DeserializeObjectToQuadTree(const string &_strNodeID, vector<tObj*> &_listObjects);
	
	void SaveBasicFigure(int _life, int _numberCoin, int _score){
		LIFE = _life;
		NUMBERCOIN = _numberCoin;
		SCORE = _score;
	}

	void ResetBasicFigure(){
		LIFE = 3;
		NUMBERCOIN = 0;
		SCORE = 0;
	}
};