#include "InGameController.h"
#include "BaseLand.h"
#include "BossBreak.h"
#include "BrickBreak.h"
#include "BrickHard.h"
#include "Cloud.h"
#include "Coin.h"
#include "Flower.h"
#include "Grass.h"
#include "Mushroom.h"
#include "MushroomBad.h"
#include "Post.h"
#include "Pole.h"
#include "Fence.h"
#include "Pipe.h"
#include "QuestionBrick.h"
#include "Turtle.h"
#include "ManagerObject.h"
#include "LevelController.h"

InGameController* InGameController::instance = NULL;

InGameController::InGameController(void){
	SONG_PLAYING = NULL;
}

InGameController::~InGameController(void){

}

InGameController* InGameController::getInGameController(){
	if (instance == NULL)
	{
		instance = new InGameController();
	}
	return instance;
}

void InGameController::LoadInfoFromMap(int _level){
	ReadMap::getReadMap()->mapData.clear();
	ReadMap::getReadMap()->ReadFile(_level);

	POSX = ReadMap::getReadMap()->basicDigital[0];
	POSY = ReadMap::getReadMap()->basicDigital[1];
	MAXWIDTH = ReadMap::getReadMap()->basicDigital[2] * 50;
	MAXHEIGHT = ReadMap::getReadMap()->basicDigital[3] * 50;
	LEVELMAP = ReadMap::getReadMap()->basicDigital[4];
	TIMEPLAY = ReadMap::getReadMap()->basicDigital[5];
	
	oMARIO = new Mario();
	oMARIO->setXY(POSX, 400);

	QUADTREE = new QuadTree(CRECT(0, MAXWIDTH, MAXHEIGHT, 0));
	QUADTREE->CreateQuadTree();

	for (map<string, vector<tObj*>>::iterator i = ReadMap::getReadMap()->mapData.begin(); 
		i!= ReadMap::getReadMap()->mapData.end(); i++)
	{
		DeserializeObjectToQuadTree(i->first, i->second);
	}
}

int InGameController::LoadInfoFromSaved(){
	ReadMap::getReadMap()->savedData.clear();
	if(ReadMap::getReadMap()->ReadFile() == 1){
		POSX = ReadMap::getReadMap()->digitalGameSaved[0];
		POSY = ReadMap::getReadMap()->digitalGameSaved[1];

		int ID = ReadMap::getReadMap()->digitalGameSaved[2];

		TIMEPLAY = ReadMap::getReadMap()->digitalGameSaved[3];
	
		LIFE = ReadMap::getReadMap()->digitalGameSaved[4];
		NUMBERCOIN = ReadMap::getReadMap()->digitalGameSaved[5];
		SCORE = ReadMap::getReadMap()->digitalGameSaved[6];

		LEVELMAP = ReadMap::getReadMap()->digitalGameSaved[7];
		LevelController::getLevelController()->LEVELCHOOSED = LEVELMAP;
		MAXWIDTH = ReadMap::getReadMap()->digitalGameSaved[8];
		MAXHEIGHT = ReadMap::getReadMap()->digitalGameSaved[9];

		oMARIO = new Mario();
		oMARIO->setXY(POSX, POSY);
		oMARIO->setID(ID);

		QUADTREE = new QuadTree(CRECT(0, MAXWIDTH, MAXHEIGHT, 0));
		QUADTREE->CreateQuadTree();

		for (map<string, vector<tObj*>>::iterator i = ReadMap::getReadMap()->savedData.begin(); 
			i!= ReadMap::getReadMap()->savedData.end(); i++)
		{
			SavedDataToQuadTree(i->first, i->second);
		}

		return 1;
	}else{
		return 0;
	}
}

void InGameController::SavedDataToQuadTree(const string &_strNodeID, vector<tObj*> &_listObjects){
	if (_strNodeID == "")
	{
		return;
	}

	QuadTreeNode* qtNote = QUADTREE->GetQuadTreeNodeWithID(_strNodeID);

	if (qtNote != NULL)
	{
		for (vector<tObj*>::iterator i = _listObjects.begin(); i != _listObjects.end(); i++)
		{
			switch((*i)->ID){
			case LAND_BASE:
				BaseLand* baseLand;
				baseLand = new BaseLand();
				baseLand->setXY((*i)->x, (*i)->y);
				baseLand->setIDCurFrame((*i)->STT);
				qtNote->Insert(baseLand);
				break;
			case FENCE:
				Fence* fence;
				fence = new Fence();
				fence->setXY((*i)->x, (*i)->y);
				fence->setIDCurFrame((*i)->STT);
				qtNote->Insert(fence);
				break;
			case PIPE:
				Pipe* pipe;
				pipe= new Pipe();
				pipe->setXY((*i)->x, (*i)->y);
				pipe->setIDCurFrame((*i)->STT);
				qtNote->Insert(pipe);
				break;
			case POLE:
				Pole* pole;
				pole = new Pole();
				pole->setXY((*i)->x, (*i)->y);
				pole->setIDCurFrame((*i)->STT);
				qtNote->Insert(pole);
				break;
			case POST:
				Post* post;
				post= new Post();
				post->setXY((*i)->x, (*i)->y);
				post->setIDCurFrame((*i)->STT);
				qtNote->Insert(post);
				break;
			case BRICK_BREAK:
				if ((*i)->STT != DEATH)
				{
				BrickBreak* brickBreak = new BrickBreak();
				brickBreak->setXY((*i)->x, (*i)->y);
				brickBreak->setSTT((*i)->STT);
				qtNote->Insert(brickBreak);
				}
				break;
			case BRICK_HARD:
				BrickHard* brickHard;
				brickHard = new BrickHard();
				brickHard->setXY((*i)->x, (*i)->y);
				brickHard->setSTT((*i)->STT);
				qtNote->Insert(brickHard);
				break;
			case BUILDING:
				oBUILDING = new Building();
				oBUILDING->setXY((*i)->x, (*i)->y);
				oBUILDING->setSTT((*i)->STT);
				qtNote->Insert(oBUILDING);
				break;
			case CLOUD:
				Cloud* cloud;
				cloud= new Cloud();
				cloud->setXY((*i)->x, (*i)->y);
				cloud->setSTT((*i)->STT);
				qtNote->Insert(cloud);
				break;
			case GRASS:
				Grass* grass;
				grass = new Grass();
				grass->setXY((*i)->x, (*i)->y);
				grass->setSTT((*i)->STT);
				qtNote->Insert(grass);
				break;
			case COIN:
				if ((*i)->STT != DEATH && (*i)->STT != 13)
				{
					Coin* coin = new Coin();
					coin->setXY((*i)->x, (*i)->y);
					coin->setSTT(ACTIVE);
					qtNote->Insert(coin);
				}
				break;
			case FLOWER:
				if ((*i)->STT != DEATH && (*i)->STT != 13)
				{
					Flower* flower = new Flower();
					flower->setXY((*i)->x, (*i)->y);

					if ((*i)->STT == 11)
					{
						flower->setSTT(ACTIVE);
						flower->setUpping();
						flower->setVY(0.018f);
					}else if ((*i)->STT == 12)
					{
						flower->setSTT(ACTIVE);
						flower->setNormaling();
					}
					qtNote->Insert(flower);
				}
				break;
			case MUSHROOMBIG:
				if ((*i)->STT != DEATH && (*i)->STT != 13)
				{
					Mushroom* mushroom = new Mushroom();
					mushroom->setXY((*i)->x, (*i)->y);
					if ((*i)->STT == 11)
					{
						mushroom->setSTT(ACTIVE);
						mushroom->setUpping();
						mushroom->setVY(0.018f);
					}else if ((*i)->STT == 12)
					{
						mushroom->setSTT(ACTIVE);
						mushroom->setNormaling();
						mushroom->setAccelY(-0.001f);
						mushroom->setVX(0.2f);
					}
					mushroom->setID(MUSHROOMBIG);
					qtNote->Insert(mushroom);
				}
				break;
			case MUSHROOMUP:
				if ((*i)->STT != DEATH && (*i)->STT != 13)
				{
					Mushroom* mushroom = new Mushroom();
					mushroom->setXY((*i)->x, (*i)->y);
					if ((*i)->STT == 11)
					{
						mushroom->setSTT(ACTIVE);
						mushroom->setUpping();
						mushroom->setVY(0.018f);
					}else if ((*i)->STT == 12)
					{
						mushroom->setSTT(ACTIVE);
						mushroom->setNormaling();
						mushroom->setAccelY(-0.001f);
						mushroom->setVX(0.2f);
					}
					mushroom->setID(MUSHROOMUP);
					qtNote->Insert(mushroom);
				}
				break;
			case MUSHROOM_BAD:
				if ((*i)->STT != DEATH)
				{
					MushroomBad* mushroomBad = new MushroomBad();
					mushroomBad->setXY((*i)->x, (*i)->y);
					mushroomBad->setSTT((*i)->STT);
					qtNote->Insert(mushroomBad);
				}
				break;
			case WINPOLE:
				oWINPOLE = new Winpole();
				oWINPOLE->setXY((*i)->x, (*i)->y);
				oWINPOLE->setSTT((*i)->STT);
				qtNote->Insert(oWINPOLE);
				break;
			case BOSS:
				if ((*i)->STT != DEATH)
				{
					oBOSS = new Boss();
					oBOSS->setXY((*i)->x, (*i)->y);
					oBOSS->blood = (*i)->STT;
					qtNote->Insert(oBOSS);
				}
				break;
			case TURTLE:
				if ((*i)->STT != DEATH)
				{
					Turtle* turtle = new Turtle();
					turtle->setXY((*i)->x, (*i)->y);
					if ((*i)->STT == 11)
					{
						turtle->setNormaling();
					}else if ((*i)->STT == 12)
					{
						turtle->setStaticing();
					}
					qtNote->Insert(turtle);
				}
				break;
			case QUESTION_BRICK:
				QuestionBrick* questionBrick;
				questionBrick = new QuestionBrick();
				questionBrick->setXY((*i)->x, (*i)->y);

				if ((*i)->STT == 50)
				{
					questionBrick->setSTT(ACTIVE);
					questionBrick->setStaticing();
				}else{
					if ((*i)->STT == COIN)
					{
						Coin* coin = new Coin();
						coin->setXY((*i)->x, (*i)->y);
						qtNote->Insert(coin);

						questionBrick->setHideObject(coin);
					}
					if ((*i)->STT == FLOWER)
					{
						Flower* flower = new Flower();
						flower->setXY((*i)->x, (*i)->y);
						qtNote->Insert(flower);

						questionBrick->setHideObject(flower);
					}
					if ((*i)->STT == MUSHROOMBIG)
					{
						Mushroom* mushroomBig = new Mushroom();
						mushroomBig->setXY((*i)->x, (*i)->y);
						mushroomBig->setID(MUSHROOMBIG);
						qtNote->Insert(mushroomBig);

						questionBrick->setHideObject(mushroomBig);
					}

					if ((*i)->STT == MUSHROOMUP)
					{
						Mushroom* mushroomUp = new Mushroom();
						mushroomUp->setXY((*i)->x, (*i)->y);
						mushroomUp->setID(MUSHROOMUP);
						qtNote->Insert(mushroomUp);

						questionBrick->setHideObject(mushroomUp);
					}
				}
				qtNote->Insert(questionBrick);
				break;
			}	
		}
	}
}

void InGameController::DeserializeObjectToQuadTree(const string &_strNodeID, vector<tObj*> &_listObjects){
	if (_strNodeID == "")
	{
		return;
	}

	DynamicObject* dynamicObj;
	StaticObject* staticObj;

	QuadTreeNode* qtNote = QUADTREE->GetQuadTreeNodeWithID(_strNodeID);

	if (qtNote != NULL)
	{
		for (vector<tObj*>::iterator i = _listObjects.begin(); i != _listObjects.end(); i++)
		{
			switch((*i)->ID){
			case 1:
				Turtle* turtle;
				turtle = new Turtle();
				turtle->setXY((*i)->x, (*i)->y);
				qtNote->Insert(turtle);
				break;
			case 2:
				MushroomBad* mushroomBad;
				mushroomBad = new MushroomBad();
				mushroomBad->setXY((*i)->x, (*i)->y);
				qtNote->Insert(mushroomBad);
				break;
			case 3:
				staticObj = new BaseLand();
				((BaseLand*)staticObj)->setIDCurFrame(0);
				staticObj->setXY((*i)->x, (*i)->y);
				qtNote->Insert(staticObj);
				break;
			case 4:
				staticObj = new BaseLand();
				((BaseLand*)staticObj)->setIDCurFrame(3);
				staticObj->setXY((*i)->x, (*i)->y);
				qtNote->Insert(staticObj);
				break;
			case 5:
				staticObj = new BaseLand();
				((BaseLand*)staticObj)->setIDCurFrame(1);
				staticObj->setXY((*i)->x, (*i)->y);
				qtNote->Insert(staticObj);
				break;
			case 6:
				staticObj = new BaseLand();
				((BaseLand*)staticObj)->setIDCurFrame(4);
				staticObj->setXY((*i)->x, (*i)->y);
				qtNote->Insert(staticObj);
				break;
			case 7:
				staticObj = new BaseLand();
				((BaseLand*)staticObj)->setIDCurFrame(2);
				staticObj->setXY((*i)->x, (*i)->y);
				qtNote->Insert(staticObj);
				break;
			case 8:
				staticObj = new BaseLand();
				((BaseLand*)staticObj)->setIDCurFrame(5);
				staticObj->setXY((*i)->x, (*i)->y);
				qtNote->Insert(staticObj);
				break;
			case 9:
				staticObj = new Pipe();
				((Pipe*)staticObj)->setIDCurFrame(0);
				staticObj->setXY((*i)->x, (*i)->y);
				qtNote->Insert(staticObj);
				break;
			case 10:
				staticObj = new Pipe();
				((Pipe*)staticObj)->setIDCurFrame(2);
				staticObj->setXY((*i)->x, (*i)->y);
				qtNote->Insert(staticObj);
				break;
			case 11:
				staticObj = new Pipe();
				((Pipe*)staticObj)->setIDCurFrame(1);
				staticObj->setXY((*i)->x, (*i)->y);
				qtNote->Insert(staticObj);
				break;
			case 12:
				staticObj = new Pipe();
				((Pipe*)staticObj)->setIDCurFrame(3);
				staticObj->setXY((*i)->x, (*i)->y);
				qtNote->Insert(staticObj);
				break;
			case 13:
				staticObj = new BrickHard();
				staticObj->setXY((*i)->x, (*i)->y);
				qtNote->Insert(staticObj);
				break;
			case 14:
				dynamicObj = new BrickBreak();
				((BrickBreak*)dynamicObj)->setXY((*i)->x, (*i)->y);
				qtNote->Insert(dynamicObj);
				break;
			case 15:
				dynamicObj = new Coin();
				((Coin*)dynamicObj)->setStatusStart(ACTIVE);
				dynamicObj->setXY((*i)->x, (*i)->y);
				qtNote->Insert(dynamicObj);
				break;
			case 16:
				Flower* flower;
				flower = new Flower();
				flower->setXY((*i)->x, (*i)->y);
				qtNote->Insert(flower);

				dynamicObj = new QuestionBrick();
				dynamicObj->setXY((*i)->x, (*i)->y);
				((QuestionBrick*)dynamicObj)->setHideObject(flower);
				qtNote->Insert(dynamicObj);
				break;
			case 17:
				Mushroom* mushroomUp;
				mushroomUp = new Mushroom();
				mushroomUp->setXY((*i)->x, (*i)->y);
				mushroomUp->setID(MUSHROOMUP);
				qtNote->Insert(mushroomUp);

				dynamicObj = new QuestionBrick();
				dynamicObj->setXY((*i)->x, (*i)->y);
				((QuestionBrick*)dynamicObj)->setHideObject(mushroomUp);
				qtNote->Insert(dynamicObj);
				break;
			case 18:
				Mushroom* mushroomBig;
				mushroomBig = new Mushroom();
				mushroomBig->setXY((*i)->x, (*i)->y);
				mushroomBig->setID(MUSHROOMBIG);
				qtNote->Insert(mushroomBig);

				dynamicObj = new QuestionBrick();
				dynamicObj->setXY((*i)->x, (*i)->y);
				((QuestionBrick*)dynamicObj)->setHideObject(mushroomBig);
				qtNote->Insert(dynamicObj);
				break;
			case 19:
				Coin* coin;
				coin = new Coin();
				coin->setXY((*i)->x, (*i)->y);
				coin->setStatusStart(READY);
				qtNote->Insert(coin);

				dynamicObj = new QuestionBrick();
				dynamicObj->setXY((*i)->x, (*i)->y);
				((QuestionBrick*)dynamicObj)->setHideObject(coin);
				qtNote->Insert(dynamicObj);
				break;
			case 20:
				staticObj = new Cloud();
				staticObj->setXY((*i)->x, (*i)->y);
				qtNote->Insert(staticObj);
				break;
			case 21:
				staticObj = new Grass();
				staticObj->setXY((*i)->x, (*i)->y);
				qtNote->Insert(staticObj);
				break;
			case 22:
				oBUILDING = new Building();
				oBUILDING->setXY((*i)->x, (*i)->y);
				qtNote->Insert(oBUILDING);
				break;
			case 23:
				staticObj = new Fence();
				((Fence*)staticObj)->setIDCurFrame(0);
				staticObj->setXY((*i)->x, (*i)->y);
				qtNote->Insert(staticObj);
				break;
			case 24:
				staticObj = new Fence();
				((Fence*)staticObj)->setIDCurFrame(1);
				staticObj->setXY((*i)->x, (*i)->y);
				qtNote->Insert(staticObj);
				break;
			case 25:
				staticObj = new Fence();
				((Fence*)staticObj)->setIDCurFrame(2);
				staticObj->setXY((*i)->x, (*i)->y);
				qtNote->Insert(staticObj);
				break;
			case 26:
				staticObj = new Fence();
				((Fence*)staticObj)->setIDCurFrame(3);
				staticObj->setXY((*i)->x, (*i)->y);
				qtNote->Insert(staticObj);
				break;
			case 27:
				staticObj = new Fence();
				((Fence*)staticObj)->setIDCurFrame(4);
				staticObj->setXY((*i)->x, (*i)->y);
				qtNote->Insert(staticObj);
				break;
			case 28:
				staticObj = new Fence();
				((Fence*)staticObj)->setIDCurFrame(5);
				staticObj->setXY((*i)->x, (*i)->y);
				qtNote->Insert(staticObj);
				break;
			case 29:
				staticObj = new Pole();
				((Pole*)staticObj)->setIDCurFrame(0);
				staticObj->setXY((*i)->x, (*i)->y);
				qtNote->Insert(staticObj);
				break;
			case 30:
				staticObj = new Pole();
				((Pole*)staticObj)->setIDCurFrame(1);
				staticObj->setXY((*i)->x, (*i)->y);
				qtNote->Insert(staticObj);
				break;
			case 31:
				staticObj = new Pole();
				((Pole*)staticObj)->setIDCurFrame(2);
				staticObj->setXY((*i)->x, (*i)->y);
				qtNote->Insert(staticObj);
				break;
			case 32:
				staticObj = new Pole();
				((Pole*)staticObj)->setIDCurFrame(3);
				staticObj->setXY((*i)->x, (*i)->y);
				qtNote->Insert(staticObj);
				break;
			case 33:
				staticObj = new Pole();
				((Pole*)staticObj)->setIDCurFrame(4);
				staticObj->setXY((*i)->x, (*i)->y);
				qtNote->Insert(staticObj);
				break;
			case 34:
				staticObj = new Pole();
				((Pole*)staticObj)->setIDCurFrame(5);
				staticObj->setXY((*i)->x, (*i)->y);
				qtNote->Insert(staticObj);
				break;
			case 35:
				staticObj = new Post();
				((Post*)staticObj)->setIDCurFrame(0);
				staticObj->setXY((*i)->x, (*i)->y);
				qtNote->Insert(staticObj);
				break;
			case 36:
				staticObj = new Post();
				((Post*)staticObj)->setIDCurFrame(1);
				staticObj->setXY((*i)->x, (*i)->y);
				qtNote->Insert(staticObj);
				break;
			case 37:
				staticObj = new Post();
				((Post*)staticObj)->setIDCurFrame(2);
				staticObj->setXY((*i)->x, (*i)->y);
				qtNote->Insert(staticObj);
				break;
			case 38:
				oWINPOLE = new Winpole();
				oWINPOLE->setXY((*i)->x, (*i)->y);
				qtNote->Insert(oWINPOLE);
				break;
			case 40:
				oBOSS = new Boss();
				oBOSS->setXY((*i)->x, (*i)->y);
				qtNote->Insert(oBOSS);
				break;
			}
		}
	}
}
