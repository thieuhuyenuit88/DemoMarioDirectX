#include "AudioManager.h"
#include "DXDeviceManager.h"
AudioManager* AudioManager::instance = NULL;

AudioManager::AudioManager(void){

}

AudioManager::~AudioManager(void){

}

AudioManager* AudioManager::getAudioManager(){
	if (instance == NULL)
	{
		instance = new AudioManager();
		instance->Init(DXDeviceManager::getInstanceDXDevice()->getHwnd());
	}
	return instance;
}

void AudioManager::Init(HWND _hwnd){
	soundDev = new DXSound();
	soundDev->Init(_hwnd);

	isEffect = true;
	isBackground = true;
	isLoop = true;
	isMusicPlaying = false;

	listSounds.insert(SoundPair("e_1up", soundDev->LoadSound("data\\audio\\e_1up.wav")));
	listSounds.insert(SoundPair("e_boss_before_die", soundDev->LoadSound("data\\audio\\e_boss_before_die.wav")));
	listSounds.insert(SoundPair("e_boss_fire", soundDev->LoadSound("data\\audio\\e_boss_fire.wav")));
	listSounds.insert(SoundPair("e_boss_die", soundDev->LoadSound("data\\audio\\e_boss_die.wav")));
	listSounds.insert(SoundPair("e_boss_hurt", soundDev->LoadSound("data\\audio\\e_boss_hurt.wav")));
	listSounds.insert(SoundPair("e_brick_up", soundDev->LoadSound("data\\audio\\e_brick_up.wav")));
	listSounds.insert(SoundPair("e_broken", soundDev->LoadSound("data\\audio\\e_broken.wav")));
	listSounds.insert(SoundPair("e_chose", soundDev->LoadSound("data\\audio\\e_chose.wav")));

	listSounds.insert(SoundPair("e_click", soundDev->LoadSound("data\\audio\\e_click.wav")));
	listSounds.insert(SoundPair("e_coin", soundDev->LoadSound("data\\audio\\e_coin.wav")));
	listSounds.insert(SoundPair("e_death", soundDev->LoadSound("data\\audio\\e_death.wav")));
	listSounds.insert(SoundPair("e_death_shot", soundDev->LoadSound("data\\audio\\e_death_shot.wav")));
	listSounds.insert(SoundPair("e_eat", soundDev->LoadSound("data\\audio\\e_eat.wav")));
	listSounds.insert(SoundPair("e_grow", soundDev->LoadSound("data\\audio\\e_grow.wav")));
	listSounds.insert(SoundPair("e_jump", soundDev->LoadSound("data\\audio\\e_jump.wav")));

	listSounds.insert(SoundPair("e_mush_die", soundDev->LoadSound("data\\audio\\e_mush_die.wav")));
	listSounds.insert(SoundPair("e_pipe", soundDev->LoadSound("data\\audio\\e_pipe.wav")));
	listSounds.insert(SoundPair("e_shot", soundDev->LoadSound("data\\audio\\e_shot.wav")));
	listSounds.insert(SoundPair("e_slide", soundDev->LoadSound("data\\audio\\e_slide.wav")));
	listSounds.insert(SoundPair("e_touch_tirtle", soundDev->LoadSound("data\\audio\\e_touch_tirtle.wav")));
	listSounds.insert(SoundPair("e_up", soundDev->LoadSound("data\\audio\\e_up.wav")));
	listSounds.insert(SoundPair("e_win", soundDev->LoadSound("data\\audio\\e_win.wav")));

	listSounds.insert(SoundPair("b_about_state", soundDev->LoadSound("data\\audio\\b_about_state.wav")));
	listSounds.insert(SoundPair("b_game1", soundDev->LoadSound("data\\audio\\b_game1.wav")));
	listSounds.insert(SoundPair("b_game2", soundDev->LoadSound("data\\audio\\b_game2.wav")));
	listSounds.insert(SoundPair("b_loading_state", soundDev->LoadSound("data\\audio\\b_loading_state.wav")));
	listSounds.insert(SoundPair("b_lose_state", soundDev->LoadSound("data\\audio\\b_lose_state.wav")));
	listSounds.insert(SoundPair("b_menu", soundDev->LoadSound("data\\audio\\b_menu.wav")));
	listSounds.insert(SoundPair("b_option_state", soundDev->LoadSound("data\\audio\\b_option_state.wav")));
	listSounds.insert(SoundPair("b_win_state", soundDev->LoadSound("data\\audio\\b_win_state.wav")));
}

void AudioManager::Play(const char* nameSound){
	if (nameSound[0] == 'e' && isEffect)
	{
		map<const char*, CSound*>::iterator it = listSounds.find(nameSound);
		if (it != listSounds.end())
		{
			//if(!it->second->IsSoundPlaying()){
				it->second->Play();
			//}
		}
	}

	if (nameSound[0] == 'b' && isBackground)
	{
		if (isMusicPlaying)
		{
			StopAllBack();
		}

		map<const char*, CSound*>::iterator it = listSounds.find(nameSound);
		if (it != listSounds.end())
		{
			if(!it->second->IsSoundPlaying()){
				if (isLoop)
				{
					it->second->Play(0,DSBPLAY_LOOPING);
					isMusicPlaying = true;
				}else{
					it->second->Play();
					isMusicPlaying = true;
				}	
			}
		}
	}
}

void AudioManager::Stop(const char* nameSound){
	if (nameSound[0] == 'e' && isEffect)
	{
		map<const char*, CSound*>::iterator it = listSounds.find(nameSound);
		if (it != listSounds.end())
		{
			if(it->second->IsSoundPlaying()){
				it->second->Stop();
			}
		}
	}

	if (nameSound[0] == 'b' && isBackground)
	{
		map<const char*, CSound*>::iterator it = listSounds.find(nameSound);
		if (it != listSounds.end())
		{
			if(it->second->IsSoundPlaying()){
				it->second->Stop();
			}
		}
	}
}

void AudioManager::StopAllBack(){
	for (map<const char*, CSound*>::iterator it = listSounds.begin(); it != listSounds.end(); it++)
	{
		if (it->first[0] == 'b' && isBackground)
		{
			if(it->second->IsSoundPlaying()){
				it->second->Stop();
				isMusicPlaying = false;
			}	
		}
	}
}

void AudioManager::StopAllSound(){
	for (map<const char*, CSound*>::iterator it = listSounds.begin(); it != listSounds.end(); it++)
	{
		if (it->first[0] == 'e' && isEffect)
		{
			if(it->second->IsSoundPlaying()){
				it->second->Stop();
			}
		}
	}
}

void AudioManager::Release(){
	StopAllBack();
	StopAllSound();

	for (map<const char*, CSound*>::iterator it = listSounds.begin(); it != listSounds.end(); it++)
	{
		delete it->second;
	}

	listSounds.clear();
}