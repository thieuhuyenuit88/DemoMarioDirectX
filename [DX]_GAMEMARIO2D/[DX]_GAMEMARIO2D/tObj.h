#pragma once
#include <stdio.h>

class tObj{
public:
	int ID;
	int x, y;
	int STT;

	tObj(void){
		ID = x = y = STT = 0;
	}

	~tObj(void){

	}

	tObj(int _ID, int _x, int _y){
		ID = _ID;
		x = _x;
		y = _y;
	}

	tObj(int _ID, int _x, int _y, int _STT){
		ID = _ID;
		x = _x;
		y = _y;
		STT = _STT;
	}
};