#pragma once
#include "IState.h"

class TestState: public IState{
protected:

public:
	TestState(IPlay* iPlay):IState(iPlay){}
	~TestState(){}

	void IsKeyDown(int KeyCode){}
	void OnKeyDown(int KeyCode){}
	void OnKeyUp(int KeyCode){}
	void ProcessMouse(DIMOUSESTATE MouseState,POINT Positon){}

	void Init (){}
	void Update (float deltaTime){}
	void UpdateViewPosBeforeDraw(float interpolation){}
	void Draw () {}
	void Release () {}
};