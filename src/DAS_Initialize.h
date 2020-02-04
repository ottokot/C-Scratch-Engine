#ifndef DAS_INITIALIZE_H
#define DAS_INITIALIZE_H

#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

//Not implemented yet
#include <SDL_ttf.h>

#include <string>
#include <cstring>
#include <stdio.h>

const std::string PROJECT_TITLE = "Wahl";
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

bool DAS_InitSDLSuccess = false;
bool DAS_InitWindowSuccess = false;
bool DAS_InitRendererSuccess = false;
bool DAS_InitScreenSuccess = false;

SDL_Window* das_window = NULL;
SDL_Renderer* das_renderer = NULL;

bool DAS_InitComponentsComplete()
{
	//I don't like this
	if (!DAS_InitRendererSuccess || !DAS_InitSDLSuccess
			|| !DAS_InitWindowSuccess)
	{
		printf("SDL %d\n", DAS_InitSDLSuccess);
		printf("Window %d\n", DAS_InitWindowSuccess);
		printf("renderer%d\n", DAS_InitRendererSuccess);
		printf("One or more components of DAS failed to Init\n");
		return false;
	}
	else
	{
		return true;
	}

	if ((!DAS_InitScreenSuccess || !DAS_InitSDLSuccess || !DAS_InitWindowSuccess))
	{
		printf("SDL %d\n", DAS_InitSDLSuccess);
		printf("Window %d\n", DAS_InitWindowSuccess);
		printf("Screen %d\n", DAS_InitScreenSuccess);
		printf("One or more components of DAS failed to Init\n");
		return false;
	}

	return true;
}

void DAS_InitSDL()
{
	DAS_InitSDLSuccess = false;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("Failed to Init SDL\n");
	}
	else
	{
		int imgFlags = IMG_INIT_PNG;
		if (!(IMG_Init(imgFlags) & imgFlags))
		{
			printf("Failed to Init SDL_image\n");
		}
		else
		{
			DAS_InitSDLSuccess = true;
		}

		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			printf("Failed to Init SDL_mixer (Audio)");
		}
	}
}

SDL_Window* DAS_InitWindow()
{
	DAS_InitWindowSuccess = false;

	SDL_Window* window = NULL;

	if (!DAS_InitSDLSuccess)
	{
		printf("Could not Init Window because DAS failed to Init\n");
	}
	else
	{
		window = SDL_CreateWindow(PROJECT_TITLE.c_str(),
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
				SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		if (window == NULL)
		{
			printf("Failed to Init Window\n");
		}
		else
		{
			DAS_InitWindowSuccess = true;
		}
	}

	return window;
}

SDL_Renderer* DAS_InitRenderer(SDL_Window* window)
{
	SDL_Renderer* renderer = NULL;
	DAS_InitRendererSuccess = false;

	if (!DAS_InitWindowSuccess)
	{
		printf("Failed to Init Renderer because Window Failed to Init\n");
	}
	else
	{
		renderer = SDL_CreateRenderer(window, -1,
				SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
		if (renderer == NULL)
		{
			printf("Failed to Init Renderer\n");
		}
		else
		{
			SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
			DAS_InitRendererSuccess = true;
		}
	}

	return renderer;
}

SDL_Surface* DAS_InitScreen(SDL_Window* window)
{
	DAS_InitScreenSuccess = false;

	SDL_Surface* screen = NULL;

	if (!DAS_InitWindowSuccess)
	{
		printf("Could not Init Screen because Window Failed to Init\n");
	}
	else
	{
		screen = SDL_GetWindowSurface(window);
		if (screen == NULL)
		{
			printf("Failed to Init Screen\n");
		}
		else
		{
			DAS_InitScreenSuccess = true;
		}
	}

	return screen;
}

#endif
