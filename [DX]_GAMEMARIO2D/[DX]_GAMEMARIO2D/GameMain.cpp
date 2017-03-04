#include "GameMain.h"
#include "IState.h"
#include "DXDeviceManager.h"
#include "CLog.h"

GameMain::GameMain(){
	gameName = "";
}

bool GameMain::Init(HINSTANCE hInstance, int nCmdShow, char* gameName){
	this->gameName = gameName;
	winForm = new WinForm();
	winForm = WinForm::InitWinForm(hInstance, nCmdShow, g_SCREEN_WIDTH, g_SCREEN_HEIGHT, gameName);
	
	dxCreater = new DXCreater();
	dxCreater = DXCreater::InitDX(winForm->getHWND(), !g_FULLSCREEN);

	pKeyboard = InputManager::getInstanceInput(hInstance, winForm->getHWND())->KeyBoard();
	pMouse = InputManager::getInstanceInput(hInstance, winForm->getHWND())->Mouse();

	if (pKeyboard==NULL|| pMouse==NULL)
	{
		return false;
	}

	DXDeviceManager::getInstanceDXDevice()->setDevice(dxCreater->getDevice());
	DXDeviceManager::getInstanceDXDevice()->setHInstance(hInstance);
	DXDeviceManager::getInstanceDXDevice()->setHwnd(winForm->getHWND());

	gamePlay = new GamePlay(dxCreater->getDevice());
	gamePlay->Init();

	return true;
}

GameMain* GameMain::InitGameMain(HINSTANCE hInstance, int nCmdShow, char* gameName){

	GameMain* gameMain = new GameMain();

	if(!gameMain->Init(hInstance,nCmdShow, gameName)){
		MessageBox (NULL, TEXT ("Create GameMain failed!"), gameName, MB_ICONERROR);
	}

	return gameMain;
}

void GameMain::Run(){

	bool  isRunning	   = true;
	float deltaTime    = float(1000.0f/g_TICKS_PER_SECOND);

	// Variable for solution 1
	float accumulator  = 0.0f;
	float lastTime	   = timeGetTime();

	// Variable for calculate FPS
	float countTime	   = 0.0f;
	int   countFpsGame = 0;
	float fpsGame      = 0.0f;

	// Variable for solution 2
	float nextGameTick = timeGetTime();
	int loops = 0;
	float interpolation;

	// Enter the infinite message loop
	while(isRunning)
	{
		// Check to see if any messages are waiting in the queue
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			// If the message is WM_QUIT, exit the while loop
			if(msg.message == WM_QUIT){
				isRunning = false;
			}

			// Translate the message and dispatch it to WinProc()
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		//If get command quit - release resource, device and break the loop
		if (!isRunning)
		{
			Release();
			continue; //Break;
		}
		/**********SOLUTION 1*************/
		//float newTime = timeGetTime();
		//float frameTime = newTime - lastTime;
		////Clog::getClogInstance()->outLog("%f", frameTime);
		//if (frameTime > 0.1f)
		//{
		//	frameTime = 0.1f; // max frame time to avoid spiral of death
		//}

		//lastTime = timeGetTime();
		//accumulator += frameTime * 1000.0f;
		//countTime += frameTime;
		//
		//// Input here
		//ProcessInput();

		//while(accumulator >= deltaTime){
		//	Update(deltaTime);
		//	accumulator -= deltaTime;
		//}
		//
		//UpdateViewPosBeforeRender(accumulator/deltaTime);
		/*************END SOLUTION 1**************/

		/*************SOLUTION 2*****************/
		float diffTime = timeGetTime() - lastTime;
		int numOfUpdate = floor(diffTime/deltaTime);
		lastTime = timeGetTime();
		countTime += diffTime;
		for (int i = 0; i < numOfUpdate; i++)
		{
			// Input here
			ProcessInput();
			Update(deltaTime);
			DXDeviceManager::getInstanceDXDevice()->setDeltaTime(deltaTime);
		}
		if (diffTime >= deltaTime) {
			Render();
			countFpsGame++;
		}
		//lastTime += deltaTime * numOfUpdate;
		diffTime -= deltaTime * numOfUpdate;
		float sleepTime = deltaTime - diffTime;
		Sleep(sleepTime);

		if (countTime >= 1000.0f)
		{
			fpsGame = floor(countFpsGame * 1000.0f/float(countTime));
			char str[100];
			sprintf(str,"GAMEMARIO - FPS: %f",fpsGame);
			SetWindowText(winForm->getHWND(), str);
			countTime = -1000;
			countFpsGame = 0;
		}
		/*************END SOLUTION 2**************/

		/*************SOLUTION 2*****************/
		//loops = 0;
		//float newTime = (float)timeGetTime();
		//float frameTime = newTime - lastTime;
		//countTime += frameTime;
		//lastTime = (float)timeGetTime();
		//
		//// Input here
		//ProcessInput();
		//
		//while(timeGetTime() >= nextGameTick && loops <= g_MAX_FRAME_SKIP){
		//	Update(deltaTime);
		//	DXDeviceManager::getInstanceDXDevice()->setDeltaTime(deltaTime);
		//	nextGameTick += deltaTime;
		//	loops++;
		//}

		//interpolation = float(timeGetTime() + deltaTime - nextGameTick) / deltaTime;
		//UpdateViewPosBeforeRender(interpolation);
		//
		//Render();
		//countFpsGame++;

		//if (countTime >= 1000)
		//{
		//	fpsGame = float(countFpsGame * 1000.0f/float(countTime));
		//	char str[100];
		//	sprintf(str,"GAMEMARIO - FPS: %f",fpsGame);
		//	SetWindowText(winForm->getHWND(), str);
		//	countTime = -1000;
		//	countFpsGame = 0;
		//}
		/*************END SOLUTION 2**************/

		/*************SOLUTION 3*****************/
		/*float newTime = timeGetTime();		
		float frameTime = newTime - lastTime;
		if (frameTime > 1000.0f/60.0f)
		{			
		lastTime = newTime;
		countTime+= frameTime;
		countFpsGame++;
		ProcessInput();
		Update(frameTime);
		Render();

		if(countTime >= 1000)
		{	
		fpsGame = (float)countFpsGame*1000.0f / (float)countTime;
		char str[100];
		sprintf(str,"GAMEMARIO - FPS: %f",fpsGame);
		SetWindowText(winForm->getHWND(), str);
		countFpsGame = 0;
		countTime -=1000;
		}
		}*/
		/*************END SOLUTION 3**************/
	}
}

void GameMain::ProcessInput(){
	ProcessKeyboard();
	ProcessMouse();
}

void GameMain::ProcessKeyboard(){
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];
	BYTE  keyStates[256];

	// Collect all key states first
	if(pKeyboard->GetDeviceState(sizeof(keyStates), keyStates))
	{
		pKeyboard->Acquire();

	}else{
		// Collect all buffered events
		DWORD dwElements = KEYBOARD_BUFFER_SIZE;
		HRESULT hr = pKeyboard->GetDeviceData( sizeof(DIDEVICEOBJECTDATA), keyEvents, &dwElements, 0 );

		// Scan through all data, check if the key is pressed or released
		for (int i=0;i<256;i++)
		{
			if ((keyStates[i] & 0x80) > 0)
			{
				//Is Key down
				gamePlay->getCurState()->IsKeyDown(i);
			}
		}
		for( DWORD i = 0; i < dwElements; i++ ) 
		{
			int KeyCode = keyEvents[i].dwOfs;
			int KeyState = keyEvents[i].dwData;
			// 		if ((keyStates[(int)i] & 0x80) > 0)
			// 		{
			// 			//Is Key down
			// 			_GamePlay->GetCurState()->IsKeyDown(KeyCode);
			// 		}
			if ( (KeyState & 0x80) > 0)
			{
				// On key down
				gamePlay->getCurState()->OnKeyDown(KeyCode);
			}
			else 
			{
				// On key Up
				gamePlay->getCurState()->OnKeyUp(KeyCode);
			}
		}
	}
}

void GameMain::ProcessMouse(){
	POINT Postion;
	DIMOUSESTATE mouseState;
	pMouse->Poll();
	if (!SUCCEEDED(pMouse->GetDeviceState(sizeof(DIMOUSESTATE),&mouseState)))
	{
		//mouse device lose, try to re-acquire
		pMouse->Acquire();
	}
	else
	{
		GetCursorPos(&Postion);
		ScreenToClient(winForm->getHWND(), &Postion);
		gamePlay->getCurState()->ProcessMouse(mouseState,Postion);
	}
}

void GameMain::Update(float deltaTime){
	gamePlay->Update(deltaTime);
}

void GameMain::UpdateViewPosBeforeRender(float interpolation){
	gamePlay->UpdateViewPosBeforeDraw(interpolation);
}

void GameMain::Render(){
	gamePlay->Draw();
}

void GameMain::Release(){
	gamePlay->Release();
	winForm->ReleaseWinForm();
	dxCreater->Release();
	pMouse->Release();
	pKeyboard->Release();
	gameName = NULL;
}