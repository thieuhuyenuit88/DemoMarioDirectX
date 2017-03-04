#include <d3d9.h>
#include "Global.h"

class DXCreater{
private:
	LPDIRECT3D9 pDX;					// the pointer to Direct3D interface
	LPDIRECT3DDEVICE9 pDXDevice;		// the pointer to the device class
	D3DPRESENT_PARAMETERS presentPara;	// this structure specify some of characteristics of LPDIRECT3DDEVICE9 object
	LPDIRECT3DSURFACE9 pBackBuffer;		// this pointer to back buffer
	int s_DesktopWidth, s_DesktopHeight;

	bool CreateDX();
	bool CreateParameters(HWND hWnd, bool isFullScreen);
	bool CreateDevice(HWND hWnd);
	bool CreateBackBuffer(HWND hWnd);
public:
	DXCreater();
	~DXCreater(){};

	static DXCreater* InitDX(HWND hWnd, bool isFullScreen);
	bool InitDXCreater(HWND hWnd, bool isFullScreen);

	LPDIRECT3DDEVICE9 getDevice(){
		return pDXDevice;
	}

	LPDIRECT3DSURFACE9 getBackBuffer(){
		return pBackBuffer;
	}

	void Release();
	void getResolutionScreen();
};