#pragma once
#include "IPlay.h"
#include <dinput.h>

class IState{
protected:
	int ID;
	IPlay* iPlay;
	LPDIRECT3DDEVICE9 pDeviceDX;
public:
	IState(IPlay* iPlay);
	virtual ~IState() = 0;

	void SetIDState (int ID);
	void SetGamePlay (IPlay* GamePlay);
	int GetIDState ();
	IPlay* GetGamePlay ();

	virtual void IsKeyDown(int KeyCode){};
	virtual void OnKeyDown(int KeyCode){};
	virtual void OnKeyUp(int KeyCode){};
	virtual void ProcessMouse(DIMOUSESTATE MouseState,POINT Positon){};
	
	virtual void Init () = 0;
	virtual void Update (float deltaTime) = 0;
	virtual void UpdateViewPosBeforeDraw(float interpolation) = 0;
	virtual void Draw () = 0;
	virtual void Release () = 0;
};