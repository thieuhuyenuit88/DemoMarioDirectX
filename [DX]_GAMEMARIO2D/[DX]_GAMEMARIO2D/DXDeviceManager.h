#pragma once
#include <Windows.h>
#include <d3d9.h>

class DXDeviceManager{
private:
	LPDIRECT3DDEVICE9 pDeviceDX;
	HINSTANCE hInstance;
	HWND hWnd;
	static DXDeviceManager* instance;
	float deltaTime;
public:
	DXDeviceManager(void);
	~DXDeviceManager(void);

	static DXDeviceManager* getInstanceDXDevice(){
		if (instance == NULL)
		{
			instance = new DXDeviceManager();
		}

		return instance;
	}

	LPDIRECT3DDEVICE9 getDevice(){
		return pDeviceDX;
	}

	HINSTANCE getHInstance(){
		return hInstance;
	}

	HWND getHwnd(){
		return hWnd;
	}

	float getDeltaTime(){
		return deltaTime;
	}

	void setDeltaTime(float _deltaTime){
		deltaTime = _deltaTime;
	}

	void setDevice(LPDIRECT3DDEVICE9 pDeviceDX){
		this->pDeviceDX = pDeviceDX;
	}

	void setHInstance(HINSTANCE hInstance){
		this->hInstance = hInstance;
	}

	void setHwnd(HWND hWnd){
		this->hWnd = hWnd;
	}
};
