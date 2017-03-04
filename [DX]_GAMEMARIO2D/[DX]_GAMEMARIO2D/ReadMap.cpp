#include "ReadMap.h"

ReadMap* ReadMap::instance = NULL;

ReadMap::ReadMap(void){
	
}

ReadMap::~ReadMap(void){

}

ReadMap* ReadMap::getReadMap(){
	if (instance == NULL)
	{
		instance = new ReadMap();
	}

	return instance;
}