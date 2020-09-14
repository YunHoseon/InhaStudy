#include "stdafx.h"
#include "SoundManager.h"

SoundManager::SoundManager()
{
	init();
}


SoundManager::~SoundManager()
{
	
}

void SoundManager::Destroy()
{
	delete fmodSystem;
}

void SoundManager::init()
{
	System_Create(&fmodSystem);
	fmodSystem->init(4, FMOD_INIT_NORMAL, NULL);
}

void SoundManager::AddBGM(string path)
{
	fmodSystem->createStream(path.c_str(), FMOD_LOOP_NORMAL, NULL, &bgm); //¹è°æÀº createStream
}

void SoundManager::AddSFX(string path, string soundName)
{
	fmodSystem->createSound(path.c_str(), FMOD_DEFAULT, NULL, &soundHash[soundName]);
}

void SoundManager::PlayBGM()
{
	fmodSystem->playSound(FMOD_CHANNEL_REUSE, bgm, false, &bgmChannel);
}

void SoundManager::PlaySFX(string soundName)
{
	if (soundHash[soundName] != NULL)
		fmodSystem->playSound(FMOD_CHANNEL_REUSE,soundHash[soundName], false, &sfxChannel);
}

void SoundManager::Stop()
{
	sfxChannel->stop();
	bgmChannel->stop();
}