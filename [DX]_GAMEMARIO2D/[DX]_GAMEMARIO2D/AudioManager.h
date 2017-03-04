#pragma once
#include "SoundDev.h"
#include <map>

using namespace std;

class AudioManager{
private:
	static AudioManager* instance;
	DXSound* soundDev;

	map<const char*, CSound*> listSounds;
	
	typedef pair<const char*, CSound*> SoundPair;

	AudioManager(void);
public:
	~AudioManager(void);
	
	bool isEffect;
	bool isBackground;
	bool isMusicPlaying;
	bool isLoop;

	static AudioManager* getAudioManager();
	void Init(HWND _hwnd);
	void Play(const char* nameSound);
	void StopAllBack();
	void Stop(const char* nameSound);
	void StopAllSound();
	void Release();
};