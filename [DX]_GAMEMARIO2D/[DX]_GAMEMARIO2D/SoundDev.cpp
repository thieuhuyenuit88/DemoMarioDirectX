#include "SoundDev.h"

DXSound::DXSound(void)
{
	pDXSound = new CSoundManager();
}

DXSound::~DXSound(void)
{	
	Release();
}

bool DXSound::Init(HWND _hwnd)
{
	pHwnd = _hwnd;
	HRESULT hr=NULL ;
	hr = pDXSound->Initialize(pHwnd,DSSCL_PRIORITY);
	if(hr != DS_OK)
	{
		MessageBox(pHwnd,"Coudln't creata sound manager","Error",MB_OK);
		return 0;
	}
	hr = pDXSound->SetPrimaryBufferFormat(2,22050,16);
	if(hr != DS_OK)
	{
		MessageBox(pHwnd,"Couln't set primary buffer format","Error",MB_OK);
		return 0;
	}
	return 1;
}

CSound* DXSound::LoadSound(char* filename)
{
	CSound* wave;
	HRESULT hr=NULL;
	hr = pDXSound->Create(&wave,filename);
	if(hr!=DS_OK)
	{
		MessageBox(pHwnd,"Coudln't create sound","Error",MB_OK);
		return NULL;
	}
	return wave;
}

void DXSound::Release()
{
	if(pDXSound != NULL)
		delete pDXSound;
}