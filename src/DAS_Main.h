#ifndef DAS_MAIN_H
#define DAS_MAIN_H

#pragma once

#include "DAS.h"
#include "DAS_Initialize.h"
#include "DAS_StateManager.h"
#include "DAS_Ficond.h"

#include <stdio.h>
#include <SDL.h>

#include <sstream>

//Contains all engine logic so that interfacing with DAS is just states and entities

SDL_Surface* icon = NULL;

SDL_Texture* buffer;

DAS_StateManager statemanager(NULL);

const int SCREEN_FPS = 300;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

bool DAS_Init();
void DAS_Logic();
bool DAS_LoadAssets();
void DAS_Deallocate();

bool isFrameCapped = false;

bool quit = true;
int fps;

void DAS_Main(DAS_State* state)
{
	fps = 0;
	DAS_Init();
	statemanager.dasm(state);
	DAS_Logic();

	DAS_Deallocate();
}

void DAS_Logic()
{
	SDL_Event event;

	DAS_Ficond ficond;
	DAS_Ficond ficondcap;

	quit = false;
	isFrameCapped = true;

	int countedFrames = 0;

	ficond.start();

	while (!quit)
	{
		//Program continues to run even when quit is set to true
		//Created break to ensue it exits
		quit = statemanager.getTerminationRequest();
		if (quit == true)
		{
			break;
		}

		if (isFrameCapped != false)
		{
			ficondcap.start();
		}

		SDL_SetRenderTarget(das_renderer, buffer);
		SDL_RenderClear(das_renderer);


		if (!statemanager.changeState())
		{
			statemanager.getState()->logic();
			statemanager.getState()->renderBackground();
			statemanager.getState()->render(das_renderer);

			statemanager.getState()->ELVlogic();

			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
				{
					quit = true;
				}

				statemanager.getState()->input(event);

				if (statemanager.getState()->getELVCounter() != 0)
				{
					statemanager.getState()->ELVinput(event);
				}
			}
		}

		SDL_SetRenderTarget(das_renderer, NULL);
		SDL_RenderCopy(das_renderer, buffer, NULL, NULL);

		SDL_UpdateWindowSurface(das_window);
		SDL_RenderPresent(das_renderer);

		float avgFPS = countedFrames / (ficond.getTicks() / 1000.0f);

		if ((ficond.getTicks() / 1000.f) >= 1.0f)
		{
			fps = avgFPS;
			countedFrames = 0;
			ficond.restart();
		}

		if (isFrameCapped != false)
		{
			int frameTicks = ficondcap.getTicks();
			if (frameTicks < SCREEN_TICKS_PER_FRAME)
			{
				SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
			}
		}

		++countedFrames;
	}
}
void message(std::string text, int x, int y)
{

	TTF_Font* font = TTF_OpenFont("wadc/font.wad", 30);

	SDL_Color color =
	{ 255, 255, 255 };
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);

	SDL_Texture* message = SDL_CreateTextureFromSurface(das_renderer, surface);

	SDL_Rect messagebox;
	messagebox.x = x;
	messagebox.y = y;
	messagebox.w = 100;
	messagebox.h = 30;

	SDL_RenderCopy(das_renderer, message, NULL, &messagebox);

	SDL_DestroyTexture(message);
	SDL_FreeSurface(surface);
	TTF_CloseFont(font);
}

void message(std::string text)
{
	message(text, 0, 0);
}

int getFPS()
{
	return fps;
}

std::string getFPS_str()
{
	std::ostringstream convert;
	convert << getFPS();

	std::string fps;
	fps = convert.str();

	return fps;
}
//Contains a size locked framebuffer for scaling
bool DAS_Init()
{
	DAS_InitSDL();

	das_window = DAS_InitWindow();
	das_renderer = DAS_InitRenderer(das_window);

	if (DAS_InitComponentsComplete())
	{
		if (TTF_Init() == -1)
		{
			printf("TTF_Init Failed to Load\n");
		}

		if (!DAS_LoadAssets())
		{
			printf("Failed to Load Assets\n");
		}
		else
		{
			buffer = SDL_CreateTexture(das_renderer,
					SDL_GetWindowPixelFormat(das_window),
					SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT);
			return true;
		}

	}

	buffer = SDL_CreateTexture(das_renderer,
			SDL_GetWindowPixelFormat(das_window), SDL_TEXTUREACCESS_TARGET,
			SCREEN_WIDTH, SCREEN_HEIGHT);
	return false;
}

void DAS_Deallocate()
{
	statemanager.deallocate();

	SDL_FreeSurface(icon);
	icon = NULL;

	SDL_DestroyTexture(buffer);
	buffer = NULL;

	SDL_DestroyRenderer(das_renderer);
	das_renderer = NULL;

	SDL_DestroyWindow(das_window);
	das_window = NULL;

	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

bool DAS_LoadAssets()
{
	icon = IMG_Load("wadc/ico.wad");

	if (icon != NULL)
	{
		SDL_SetWindowIcon(das_window, icon);
		return true;
	}
	return false;
}

#endif
