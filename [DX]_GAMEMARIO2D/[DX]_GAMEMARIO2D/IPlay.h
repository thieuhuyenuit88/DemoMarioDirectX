#pragma once
#include <d3d9.h>
#include <d3dx9.h>
class IState;

class IPlay{
protected:
	IState* curState;
	IState* nextState;

	LPDIRECT3DDEVICE9 pDeviceDX;
public:
	IPlay(LPDIRECT3DDEVICE9 pDeviceDX);
	virtual ~IPlay();

	void setCurState(IState* curState);
	void setNextState(IState* nextState);
	IState* getCurState();
	IState* getNextState();

	void setDevice(LPDIRECT3DDEVICE9 pDeviceDX);
	LPDIRECT3DDEVICE9 getDevice();

	virtual void Init() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void UpdateViewPosBeforeDraw(float interpolation) = 0;
	virtual void Draw() = 0;
	virtual void Release() = 0;
};
