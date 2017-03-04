#include "StateTestGame.h"
#include "Global.h"
#include "TestState.h"
#include "ManagerObject.h"
#include "RSMainGame.h"
#include <stdio.h>
#include "EffectRenderScore.h"
#include "AudioManager.h"
#include "CRandom.h"
#include "LoadingScreen.h"

StateTestGame::StateTestGame(IPlay *iPlay):IState(iPlay){
	this->ID = MAINGAME;
	timeUpdate = timeUpdate1 = timeUpdate2 = timeDown = 0;
	mario = NULL;
	boss = NULL;
	winPole = NULL;
	building = NULL;

	infoBoss = new vector<ISprite>();
}

StateTestGame::~StateTestGame(void){

}

void StateTestGame::IsKeyDown(int keyCode)
{
	if (stateInGame == RUNNING)
	{
		switch(keyCode)
		{
		case DIK_LEFT:
			if (!mario->isWinning)
			{
				mario->setMoveLeft();
			}
			break;
		case DIK_RIGHT:
			if (!mario->isWinning)
			{
				mario->setMoveRight();
			}
			break;
		}
	}
}

void StateTestGame::OnKeyUp(int keyCode){
	switch(keyCode)
	{

	}
}

void StateTestGame::OnKeyDown(int keyCode)
{
	if (stateInGame == WIN)
	{
		winScreen->OnKeyDown(keyCode);
	}else
	if (stateInGame == LOSE)
	{
		loseScreen->OnKeyDown(keyCode);
	}else
	if (stateInGame == PAUSE)
	{
		pauseScreen->OnKeyDown(keyCode);
	}else
	if (stateInGame == RUNNING)
	{
		switch(keyCode){
		case DIK_UP:
			if (!mario->isWinning)
			{
				mario->setJump();
			}
			break;
		case DIK_Z:
			if (!mario->isWinning)
			{
				mario->setShot();
			}
			break;
		case DIK_P:
			AudioManager::getAudioManager()->Play("e_chose");
			stateInGame = PAUSE;
			break;
		}
	}
}

void StateTestGame::Init(){
	gameFont = RSMainGame::getRSMainGame()->getGameFont();
	D3DXCreateSprite(pDeviceDX, &spriteHandler);

	mario = InGameController::getInGameController()->oMARIO;
	boss = InGameController::getInGameController()->oBOSS;
	winPole = InGameController::getInGameController()->oWINPOLE;
	building = InGameController::getInGameController()->oBUILDING;
	quadTree = InGameController::getInGameController()->QUADTREE;

	camera = new Camera(0, 0, g_SCREEN_WIDTH, g_SCREEN_HEIGHT);
	
	cameraContentDynamic = new vector<DynamicObject*>();
	cameraContentStatic = new vector<StaticObject*>();

	levelMap = InGameController::getInGameController()->LEVELMAP;
	timePlay = InGameController::getInGameController()->TIMEPLAY;

	iconMario = RSMainGame::getRSMainGame()->getIconMario();
	iIcon.setSize(21,22);
	iIcon.setXY(40, 20);
	iIcon.setScaleXY(2.0f, 2.0f);

	infoCoin = new Coin();
	infoCoin->setXY(450, g_SCREEN_HEIGHT - 10);
	infoCoin->setStatusStart(ACTIVE);

	bossBlood = RSMainGame::getRSMainGame()->getIconBlood();
	if (boss)
	{
		ISprite temp;
		for (int i = 0; i < boss->blood/10; i++)
		{
			temp.setXY((boss->getPosX() - ((boss->blood*5/10) - boss->getSizeWidth()) / 2) + i*5,
				boss->getPosY() + 18);
			infoBoss->push_back(temp);
		}
	}

	AudioManager::getAudioManager()->StopAllBack();
	int random = CRandom::RandomBetweenInt(0, 1);
	if (random == 0)
	{
		AudioManager::getAudioManager()->Play("b_game1");
		InGameController::getInGameController()->SONG_PLAYING = "b_game1";
	}else{
		AudioManager::getAudioManager()->Play("b_game2");
		InGameController::getInGameController()->SONG_PLAYING = "b_game2";
	}

	stateInGame = RUNNING;
	pauseScreen = new PauseScreen(this);
	winScreen = new WinScreen(this);
	loseScreen = new LoseScreen(this);

	isTimeOff = false;

	D3DXMatrixIdentity(&mtIndentity);
	D3DXMatrixIdentity(&mtWorld);
}

void StateTestGame::Update(float deltaTime){
	if (stateInGame == LOSE)
	{
		loseScreen->Update(deltaTime);
	}else
	if (stateInGame == WIN)
	{
		winScreen->Update(deltaTime);
	}else
	if (stateInGame == PAUSE)
	{
		pauseScreen->Update(deltaTime);
	}else
	if (stateInGame == RUNNING)
	{
		timeDown += deltaTime;
		if (timeDown >= 1000)
		{
			timeDown = 0;
			timePlay -= 1;
		}

		if (timePlay <= 0 && !isTimeOff)
		{
			if (mario->getID() == MARIO_BIG || mario->getID() == MARIO_SUPER)
			{
				mario->setID(MARIO);
				mario->setMarioSprite(RSMainGame::getRSMainGame()->getMarioSmallSprite());
				mario->getISpriteMario().setSize(50,50);
				mario->setSize(50,50);
				//be short :)
			}
			mario->setVX(0.0f);
			mario->setVY(0.9f);
			mario->setSTT(BEFORE_DEATH);
			InGameController::getInGameController()->LIFE -= 1;
			AudioManager::getAudioManager()->Play("e_death");
			isTimeOff = true;
		}

		if (winPole)
		{
			if (mario->DirectionCollision(winPole) != NONE)
			{
				if (mario->getSTT() == ACTIVE)
				{
					AudioManager::getAudioManager()->StopAllBack();
					AudioManager::getAudioManager()->Play("e_slide");
					timeUpdate += deltaTime;
					if (timeUpdate > 100)
					{
						timeUpdate = 0;
						InGameController::getInGameController()->SCORE += 200;
						EffectRenderScore* renderScore = new EffectRenderScore(RSMainGame::getRSMainGame()->getGameFont(), (int)mario->getPosX(), (int)mario->getPosY(), 200);
						ManagerObject::getManagerObject()->getListEffect()->push_back(renderScore);
					}

					if (!mario->isWinning)
					{
						mario->setX(winPole->getPosX() + winPole->getSizeWidth()/2);
						if (mario->getVY() == 0)
						{
							AudioManager::getAudioManager()->Stop("e_slide");
							AudioManager::getAudioManager()->Play("e_win");
							mario->setWinning();
						}
					}
				}
			}
		}

		if (building)
		{
			if (mario->getPosX() > building->getPosX() + 200)
			{
				mario->setSTT(DEATH);
				timeUpdate1 += deltaTime;
				if (timeUpdate1 > 2500)
				{
					timeUpdate1 = 0;
					AudioManager::getAudioManager()->Stop("e_win");
					AudioManager::getAudioManager()->Play("b_win_state");
					stateInGame = WIN;
				}
			}
		}

		if (mario->getSTT() == BEFORE_DEATH && InGameController::getInGameController()->LIFE >= 1)
		{
			timeUpdate2 += deltaTime;
			if (timeUpdate2 >= 2500)
			{
				timeUpdate2 = 0;
				this->GetGamePlay()->setNextState(new LoadingScreen(this->GetGamePlay()));
			}
		}

		if (mario->getSTT() == BEFORE_DEATH && InGameController::getInGameController()->LIFE < 1)
		{
			timeUpdate2 += deltaTime;
			if (timeUpdate2 >= 2500)
			{
				timeUpdate2 = 0;
				AudioManager::getAudioManager()->StopAllBack();
				AudioManager::getAudioManager()->Play("b_lose_state");
				stateInGame = LOSE;
			}
		}
		
		/************************************************************************/
		/*						Update QuadTree                                  */
		/************************************************************************/
		/**************************************Dynamics****************************/
		for (vector<DynamicObject*>::iterator f = cameraContentDynamic->begin(); f!= cameraContentDynamic->end();){
			if (!camera->getRect().isCollision((*f)->getRect()))
			{
				quadTree->Insert(*f);
				f = cameraContentDynamic->erase(f);
			}else{
				f++;
			}
		}

		vector<DynamicObject*>* queryObjects1 = quadTree->QueryDN(camera->getRect());
		cameraContentDynamic->insert(cameraContentDynamic->begin(), queryObjects1->begin(), queryObjects1->end());
		delete queryObjects1;

		/**************************************Statics****************************/
		for (vector<StaticObject*>::iterator f = cameraContentStatic->begin(); f!= cameraContentStatic->end();){
			if (!camera->getRect().isCollision((*f)->getRect()))
			{
				quadTree->Insert(*f);
				f = cameraContentStatic->erase(f);
			}else{
				f++;
			}
		}

		vector<StaticObject*>* queryObjects2 = quadTree->QueryST(camera->getRectStatic());
		cameraContentStatic->insert(cameraContentStatic->begin(), queryObjects2->begin(), queryObjects2->end());
		delete queryObjects2;

		/************************************************************************/
		/*  Update Effects                                                     */
		/************************************************************************/
		for (vector<Effect*>::iterator f = ManagerObject::getManagerObject()->getListEffect()->begin(); f!= ManagerObject::getManagerObject()->getListEffect()->end();){
			(*f)->Update(deltaTime);
			if ((*f)->getSTT() == DEATH)
			{
				(*f)->Realease();
				delete (*f);
				f = ManagerObject::getManagerObject()->getListEffect()->erase(f);
				continue;
			}else
				if (!camera->getRect().isCollision((*f)->getRect()))
				{
					(*f)->Realease();
					delete (*f);
					f = ManagerObject::getManagerObject()->getListEffect()->erase(f);
					continue;
				}
				f++;
		}

		/************************************************************************/
		/*  Update Skills                                                     */
		/************************************************************************/
		for (vector<Skill*>::iterator f = ManagerObject::getManagerObject()->getListSkill()->begin(); f!= ManagerObject::getManagerObject()->getListSkill()->end();){
			(*f)->Update(deltaTime);
			if ((*f)->getSTT() == DEATH)
			{
				(*f)->Realease();
				delete (*f);
				f = ManagerObject::getManagerObject()->getListSkill()->erase(f);
				continue;
			}else
				if (!camera->getRect().isCollision((*f)->getRect()))
				{
					(*f)->Realease();
					delete (*f);
					f = ManagerObject::getManagerObject()->getListSkill()->erase(f);
					continue;
				}
				f++;
		}

		//Update Mario
		mario->Update(deltaTime);

		/************************************************************************/
		/*  Collision skill vs objects in camera                                                     */
		/************************************************************************/
		/*****************************Dynamics***********************************/
		for (vector<Skill*>::iterator f = ManagerObject::getManagerObject()->getListSkill()->begin(); f!= ManagerObject::getManagerObject()->getListSkill()->end(); f++){
			if((*f)->getID() == BULLET_MARIO){
				for (vector<DynamicObject*>::iterator i = cameraContentDynamic->begin(); i!= cameraContentDynamic->end(); i++){
					if ((*i)->getID() == BRICK_BREAK || (*i)->getID() == QUESTION_BRICK)
					{
						(*f)->ProcessCollision(*i);
					}else if ((*i)->getID() == BOSS || (*i)->getID() == MUSHROOM_BAD || (*i)->getID() == TURTLE)
					{
						Skill* temp = new Skill(*f);
						(*f)->ProcessCollision(*i);
						(*i)->ProcessCollision(temp, (*f)->directCollision);
						delete temp;
					}
				}
			}else if((*f)->getID() == BULLET_BOSS){
				for (vector<DynamicObject*>::iterator i = cameraContentDynamic->begin(); i!= cameraContentDynamic->end(); i++){
					if ((*i)->getID() == BRICK_BREAK || (*i)->getID() == QUESTION_BRICK)
					{
						(*f)->ProcessCollision(*i);
					}
				}
			}
		}
		/*****************************Statics***********************************/
		for (vector<Skill*>::iterator f = ManagerObject::getManagerObject()->getListSkill()->begin(); f!= ManagerObject::getManagerObject()->getListSkill()->end(); f++){
			if((*f)->getID() == BULLET_MARIO){
				for (vector<StaticObject*>::iterator i = cameraContentStatic->begin(); i!= cameraContentStatic->end(); i++){
					if ((*i)->getID() == LAND_BASE || (*i)->getID() == BRICK_HARD ||
						(*i)->getID() == PIPE)
					{
						(*f)->ProcessCollision(*i);
					}
					
				}
			}else
			if((*f)->getID() == BULLET_BOSS){
				for (vector<StaticObject*>::iterator i = cameraContentStatic->begin(); i!= cameraContentStatic->end(); i++){
					if ((*i)->getID() == LAND_BASE || (*i)->getID() == BRICK_HARD ||
						(*i)->getID() == PIPE)
					{
						(*f)->ProcessCollision(*i);
					}

				}
			}
		}

		/************************************************************************/
		/*  Collision BulletBoss vs Mario                                                    */
		/************************************************************************/
		for (vector<Skill*>::iterator f = ManagerObject::getManagerObject()->getListSkill()->begin(); f!= ManagerObject::getManagerObject()->getListSkill()->end(); f++){
			if ((*f)->getID() == BULLET_BOSS)
			{
				Mario* marioTemp = new Mario(mario);
				mario->ProcessCollision(*f);
				(*f)->ProcessCollision(marioTemp);
				delete marioTemp;
			}
		}
		/************************************************************************/
		/*  Collision mario vs objects in camera                                                     */
		/************************************************************************/
		/*****************************Dynamics***********************************/
		for (vector<DynamicObject*>::iterator f = cameraContentDynamic->begin(); f!= cameraContentDynamic->end(); f++){
			if ((*f)->getID() == COIN || (*f)->getID() == MUSHROOMUP)
			{
				(*f)->ProcessCollision(mario);
			}else{
				Mario* marioTemp = new Mario(mario);
				mario->ProcessCollision(*f);
				(*f)->ProcessCollision(marioTemp, mario->directCollision);
				delete marioTemp;
			}
		}

		/*****************************Statics***********************************/
		for (vector<StaticObject*>::iterator f = cameraContentStatic->begin(); f!= cameraContentStatic->end(); f++){
			if ((*f)->getID() == LAND_BASE || (*f)->getID() == BRICK_HARD ||
				(*f)->getID() == PIPE)
			{
				mario->ProcessCollision(*f);
			}
		}

		/************************************************************************/
		/*  Collision dynamic objects vs static objects in camera                                                     */
		/************************************************************************/
		for (vector<DynamicObject*>::iterator f = cameraContentDynamic->begin(); f!= cameraContentDynamic->end(); f++){
			if ((*f)->getID() == BOSS || (*f)->getID() == MUSHROOM_BAD || (*f)->getID() == TURTLE || (*f)->getID() == MUSHROOMBIG 
				|| (*f)->getID() == MUSHROOMUP)
			{
				for (vector<StaticObject*>::iterator i = cameraContentStatic->begin(); i!= cameraContentStatic->end(); i++){
					if ((*i)->getID() == LAND_BASE || (*i)->getID() == BRICK_HARD ||
						(*i)->getID() == PIPE)
					{
						(*f)->ProcessCollision(*i);
					}
				}
			}
		}

		/************************************************************************/
		/*  Collision dynamic objects vs dynamic objects in camera                                                     */
		/************************************************************************/
		for (vector<DynamicObject*>::iterator f = cameraContentDynamic->begin(); f!= cameraContentDynamic->end(); f++){
			if ((*f)->getID() == TURTLE || (*f)->getID() == MUSHROOM_BAD)
			{
				for (vector<DynamicObject*>::iterator i = cameraContentDynamic->begin(); i!= cameraContentDynamic->end(); i++){
					if ((*f) == (*i))
					{
						continue;
					}
					if ((*i)->getID() == MUSHROOM_BAD || (*i)->getID() == TURTLE)
					{
						(*f)->ProcessCollision(*i);
						(*i)->ProcessCollision(*f);
					}if ((*i)->getID() == BRICK_BREAK || (*i)->getID() == QUESTION_BRICK)
					{
						(*f)->ProcessCollision(*i);
					}
				}
			}else
				if ((*f)->getID() == BOSS || (*f)->getID() == MUSHROOMBIG || (*f)->getID() == MUSHROOMUP)
				{
					for (vector<DynamicObject*>::iterator i = cameraContentDynamic->begin(); i!= cameraContentDynamic->end(); i++){
						if ((*f) == (*i))
						{
							continue;
						}
						if ((*i)->getID() == BRICK_BREAK || (*i)->getID() == QUESTION_BRICK)
						{
							(*f)->ProcessCollision(*i);
						}
					}
				}
		}

		/************************************************************************/
		/*  Update Objects in camera                                             */
		/************************************************************************/
		/*****************************Dynamics***********************************/
		for (vector<DynamicObject*>::iterator f = cameraContentDynamic->begin(); f!= cameraContentDynamic->end();){
			(*f)->Update(deltaTime);
			if ((*f)->getSTT() == DEATH)
			{
				(*f)->Realease();
				delete (*f);
				f = cameraContentDynamic->erase(f);
				continue;
			}
			f++;
		}
		/*****************************Statics***********************************/
		for (vector<StaticObject*>::iterator f = cameraContentStatic->begin(); f!= cameraContentStatic->end(); f++){
			if ((*f)->getID() == GRASS || (*f)->getID() == CLOUD)
			{
				(*f)->Update(deltaTime);
			}
		}

		if (boss && boss->getSTT() != DEATH && boss->getSTT() != BEFORE_DEATH)
		{
			for (int i = 0; i< boss->blood / 10; i++)
			{
				infoBoss->at(i).setXY((boss->getPosX() - ((boss->blood*5/10) - boss->getSizeWidth()) / 2) + i*5,
					boss->getPosY() + 18);
			}
		}

		camera->Update(mario, InGameController::getInGameController()->MAXWIDTH, InGameController::getInGameController()->MAXHEIGHT);
		mtWorld = camera->getMatrixTransform();

		infoCoin->Update(deltaTime);



		life = InGameController::getInGameController()->LIFE;
		numberCoin = InGameController::getInGameController()->NUMBERCOIN;
		score = InGameController::getInGameController()->SCORE;
	}
	
}

void StateTestGame::UpdateViewPosBeforeDraw(float interpolation){

}

void StateTestGame::Draw(){
	if(pDeviceDX->BeginScene())
	{
		pDeviceDX->Clear(0,NULL,D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, D3DCOLOR_XRGB(135,206,250), 1.0f, 0);
		spriteHandler->Begin(D3DXSPRITE_SORT_DEPTH_FRONTTOBACK | D3DXSPRITE_SORT_TEXTURE | D3DXSPRITE_ALPHABLEND);// || D3DXSPRITE_OBJECTSPACE);
		
		for (vector<Skill*>::iterator f = ManagerObject::getManagerObject()->getListSkill()->begin(); f!= ManagerObject::getManagerObject()->getListSkill()->end(); f++){
			(*f)->Draw(spriteHandler, mtWorld);
		}

		for (vector<Effect*>::iterator f = ManagerObject::getManagerObject()->getListEffect()->begin(); f!= ManagerObject::getManagerObject()->getListEffect()->end(); f++){
			(*f)->Draw(spriteHandler, mtWorld);
		}

		for (vector<DynamicObject*>::iterator f = cameraContentDynamic->begin(); f!= cameraContentDynamic->end(); f++){
			(*f)->Draw(spriteHandler, mtWorld);
		}

		for (vector<StaticObject*>::iterator f = cameraContentStatic->begin(); f!= cameraContentStatic->end(); f++){
			(*f)->Draw(spriteHandler, mtWorld);
		}

		mario->Draw(spriteHandler, mtWorld);

		if (boss)
		{
			for (int i = 0; i< boss->blood/10; i++)
			{
				bossBlood->Draw(spriteHandler, mtWorld, infoBoss->at(i));
			}
		}

		iconMario->Draw(spriteHandler, iIcon);
		infoCoin->Draw(spriteHandler, mtIndentity);

		char stringTemp[30];
		sprintf(stringTemp," X %d", numberCoin);
		gameFont->RenderText(500, 20, stringTemp, D3DXCOLOR(1,0,0,1));

		sprintf(stringTemp," X %d", life);
		gameFont->RenderText(75, 20, stringTemp, D3DXCOLOR(1,0,0,1));

		sprintf(stringTemp,"LEVEL: %d", levelMap);
		gameFont->RenderText(460, 70, stringTemp, D3DXCOLOR(1,0,0,1));

		sprintf(stringTemp,"SCORE: %d", score);
		gameFont->RenderText(35, 70, stringTemp, D3DXCOLOR(1,0,0,1));

		sprintf(stringTemp,"TIME(s):");
		gameFont->RenderText(850, 20, stringTemp, D3DXCOLOR(1,0,0,1));

		sprintf(stringTemp,"%d", timePlay);
		gameFont->RenderText(870, 70, stringTemp, D3DXCOLOR(1,0,0,1));

		if (stateInGame == WIN)
		{
			winScreen->Draw(spriteHandler);
		}else
		if (stateInGame == LOSE)
		{
			loseScreen->Draw(spriteHandler);
		}else
		if (stateInGame == PAUSE)
		{
			pauseScreen->Draw(spriteHandler);
		}

		spriteHandler->End();
		pDeviceDX->EndScene();
	}

	pDeviceDX->Present(NULL,NULL,NULL,NULL);
}

void StateTestGame::Release(){

}