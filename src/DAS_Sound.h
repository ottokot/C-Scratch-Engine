#ifndef DAS_SOUND_H
#define DAS_SOUND_H

#pragma once

#include <SDL.h>

#include <string>
#include <cstring>
#include <stdio.h>

class DAS_Sound
{
public:
	DAS_Sound(std::string path);
	~DAS_Sound();
	Mix_Chunk* sound;
	void play();
	void load(std::string path);
	void deallocate();
private:

};
DAS_Sound::DAS_Sound(std::string path)
{
	sound = NULL;
	load(path);
}

DAS_Sound::~DAS_Sound()
{
	deallocate();
}

void DAS_Sound::load(std::string path)
{
	sound = Mix_LoadWAV(path.c_str());
	if (sound == NULL)
	{
		printf("Failed to Load Sound \n");
	}
}

void DAS_Sound::play()
{
	if (sound != NULL)
	{
		Mix_PlayChannel(-1, sound, 0);
	}
}

void DAS_Sound::deallocate()
{
	if (sound != NULL)
	{
		Mix_FreeChunk(sound);
		sound = NULL;
	}
}

#endif
