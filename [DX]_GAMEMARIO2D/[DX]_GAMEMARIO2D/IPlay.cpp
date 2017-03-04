#include "IPlay.h"

IPlay::IPlay(LPDIRECT3DDEVICE9 pDeviceDX){
	this->pDeviceDX = pDeviceDX;
}

IPlay::~IPlay(){

}

void IPlay::setCurState(IState* curState){
	this->curState = curState;
}

void IPlay::setNextState(IState* nextState){
	this->nextState = nextState;
}

IState* IPlay::getCurState(){
	return curState;
}

IState* IPlay::getNextState(){
	return nextState;
}

void IPlay::setDevice(LPDIRECT3DDEVICE9 pDeviceDX){
	this->pDeviceDX = pDeviceDX;
}

LPDIRECT3DDEVICE9 IPlay::getDevice(){
	return pDeviceDX;
}