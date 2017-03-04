#include "IState.h"

IState::IState(IPlay* gamePlay)
{
	iPlay = gamePlay;
	pDeviceDX = gamePlay->getDevice();
}

IState::~IState()
{

}

void IState::SetGamePlay(IPlay* gamePlay)
{
	iPlay = gamePlay;
}

void IState::SetIDState(int ID)
{
	this->ID = ID;
}

int IState::GetIDState ()
{
	return this->ID;
}

IPlay* IState::GetGamePlay()
{
	return iPlay;
}