#ifndef DAS_ENGINE_H
#define DAS_ENGINE_H

#pragma once

#include <SDL.h>

class DAS_Ficond
{
public:
	DAS_Ficond();

	void start();
	void stop();
	void restart();
	void pause();
	void unpause();
	Uint32 getTicks();
	bool isStarted();
	bool isPaused();

private:
	Uint32 startTicks;
	Uint32 pausedTicks;

	bool paused;
	bool started;
};

DAS_Ficond::DAS_Ficond()
{
	startTicks = 0;
	pausedTicks = 0;

	paused = false;
	started = false;
}

void DAS_Ficond::start()
{
	started = true;

	paused = false;

	startTicks = SDL_GetTicks();
	pausedTicks = 0;
}

void DAS_Ficond::stop()
{
	started = false;

	paused = false;

	startTicks = 0;
	pausedTicks = 0;
}

void DAS_Ficond::restart()
{
	stop();
	start();
}

void DAS_Ficond::pause()
{
	if (started && !paused)
	{
		paused = true;

		pausedTicks = SDL_GetTicks() - startTicks;
		startTicks = 0;
	}
}

void DAS_Ficond::unpause()
{
	if (started && paused)
	{
		paused = false;

		startTicks = SDL_GetTicks() - pausedTicks;

		pausedTicks = 0;
	}
}

Uint32 DAS_Ficond::getTicks()
{
	Uint32 time = 0;

	if (started)
	{
		if (paused)
		{
			time = pausedTicks;
		}
		else
		{
			time = SDL_GetTicks() - startTicks;
		}
	}

	return time;
}

bool DAS_Ficond::isStarted()
{
	return started;
}

bool DAS_Ficond::isPaused()
{
	return paused && started;
}

#endif
