#include "DXCreater.h"

DXCreater::DXCreater(){
	s_DesktopWidth = s_DesktopHeight = 0;
}

bool DXCreater::CreateDX(){
	pDX = Direct3DCreate9(D3D_SDK_VERSION);
	if (!pDX)
	{
		MessageBox( NULL,"No compatible Direct3D object could be created.",
			"Fatal Error!", MB_OK | MB_ICONSTOP | MB_APPLMODAL );
		return false;
	}
	
	return true;
}

bool DXCreater::CreateParameters(HWND hWnd, bool isFullScreen){
	// Fill out a simple set of present parameters
	ZeroMemory(&presentPara, sizeof(presentPara));

	
	presentPara.BackBufferFormat			= D3DFMT_A8R8G8B8;
	presentPara.BackBufferCount				= 1;
	presentPara.MultiSampleType				= D3DMULTISAMPLE_NONE;
	presentPara.MultiSampleQuality			= 0;
	presentPara.SwapEffect					= D3DSWAPEFFECT_DISCARD; 
	presentPara.hDeviceWindow				= hWnd;
	presentPara.EnableAutoDepthStencil		= true; 
	presentPara.AutoDepthStencilFormat		= D3DFMT_D24S8;
	presentPara.Flags						= 0;
	presentPara.FullScreen_RefreshRateInHz	= D3DPRESENT_RATE_DEFAULT;
	presentPara.PresentationInterval		= D3DPRESENT_INTERVAL_IMMEDIATE;

	getResolutionScreen();
	if (isFullScreen)
	{
		presentPara.Windowed					= false;
		presentPara.BackBufferHeight			= s_DesktopHeight;
		presentPara.BackBufferWidth				= s_DesktopWidth;
	}
	else
	{
		presentPara.Windowed					= true;
		presentPara.BackBufferHeight			= g_SCREEN_HEIGHT;
		presentPara.BackBufferWidth				= g_SCREEN_WIDTH;
	}

	return true;
}

bool DXCreater::CreateDevice(HWND hWnd){

	//// Checking for Hardware Vertex Processing
	//D3DCAPS9 caps;
	//pDX->GetDeviceCaps(
	//	D3DADAPTER_DEFAULT, // Denotes primary display adapter
	//	D3DDEVTYPE_HAL,		// Specifies the device type, usually D3DDEVTYPE_HAL
	//	&caps);				// Return filled D3DCAPS9 structure that contains
	//						// the capabilities of the primary display adapter
	//// can we use Hardware vertex processing?
	//int vp = 0;

	//if(caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	//{
	//	// yes, save in "vp" the fact that hardware vertex processing is supported.
	//	vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	//}
	//else{

	//	// no, save in "vp" the fact that we must use software vertex processing.
	//	vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	//}

	// Create Device DX with capabilities supported
	pDX->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
		hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&presentPara, &pDXDevice);

	if (pDXDevice == NULL )
	{
		MessageBox(hWnd,"Could not Create device with D3DDEVTYPE_HAL & D3DCREATE_HARDWARE_VERTEXPROCESSING \n Try again !!! ","Warning!!",MB_OK);
		pDX->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
			hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&presentPara, &pDXDevice);
		if (pDXDevice == NULL )
		{
			MessageBox(hWnd,"Could not Create device with D3DDEVTYPE_HAL & D3DCREATE_SOFTWARE_VERTEXPROCESSING /n Try again !!! ","Warning!!",MB_OK);
			pDX->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_REF,
				hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&presentPara, &pDXDevice);
			if (pDXDevice == NULL )
			{
				MessageBox(hWnd,"Could not Create device with D3DDEVTYPE_REF & D3DCREATE_SOFTWARE_VERTEXPROCESSING /n Try again !!! ","Warning!!",MB_OK);
				pDX->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_SW,
					hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING,
					&presentPara, &pDXDevice);
				if (pDXDevice == NULL )
				{
					MessageBox(hWnd,"Could not Create device with D3DDEVTYPE_SW & D3DCREATE_SOFTWARE_VERTEXPROCESSING /n Try again !!! ","Warning!!",MB_OK);
					return false;
				} 
			} 	
		} 	
	} 		 
	return true;
}

bool DXCreater::InitDXCreater(HWND hWnd, bool isFullScreen){
	if (!CreateDX())
	{
		return false;
	}

	if (!CreateParameters(hWnd, isFullScreen))
	{
		MessageBox(hWnd,"Could not Create Parameters","Warning!!",MB_OK);
		return false;
	}

	if (!CreateDevice(hWnd))
	{
		MessageBox(hWnd,"Could not Create Device","Warning!!",MB_OK);
		return false;
	}

	if (!CreateBackBuffer(hWnd))
	{
		return false;
	}

	return true;
}

DXCreater* DXCreater::InitDX(HWND hWnd, bool isFullScreen){
	DXCreater* dxCreater =  new DXCreater();
	if (!dxCreater->InitDXCreater(hWnd, isFullScreen))
	{
		MessageBox (NULL, TEXT ("Create DirectX failed!"), "Failed DX", MB_ICONERROR);
	}
	return dxCreater;
}

bool DXCreater::CreateBackBuffer(HWND hWnd){
	pDXDevice->GetBackBuffer(0,0,D3DBACKBUFFER_TYPE_MONO,&pBackBuffer);
	if(pBackBuffer == NULL){
		MessageBox(hWnd,"Could not Create BackBuffer","Warning!!",MB_OK);
		return false;
	}
}

void DXCreater::Release(){
	if (pBackBuffer != NULL)
	{
		pBackBuffer->Release();
	}

	if (pDXDevice!= NULL)
	{
		pDXDevice->Release();
	}

	if (pDX!= NULL)
	{
		pDX->Release();
	}	
}

void DXCreater::getResolutionScreen()
{
	if(s_DesktopWidth == 0)
	{
		D3DDISPLAYMODE d3dDm;
		pDX->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3dDm);

		s_DesktopWidth = d3dDm.Width;
		s_DesktopHeight = d3dDm.Height;
	}
}