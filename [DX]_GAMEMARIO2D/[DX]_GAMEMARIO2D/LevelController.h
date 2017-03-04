#pragma once
#include <stdio.h>

class LevelController{
private:
	static LevelController* instance;
public:
	LevelController(void);
	~LevelController(void);

	static LevelController* getLevelController();

	int NUMLEVEL;
	int LEVELCHOOSED;
	bool ISLOADGAME;

};