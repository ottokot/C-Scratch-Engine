#ifndef DAS_FUNCTIONS_H
#define DAS_FUNCTIONS_H

#pragma once
#include "DAS_Sound.h"

void DAS_Debug(std::string string)
{
	printf(string.c_str());
}

SDL_Texture* DAS_LoadTexture(std::string path, SDL_Renderer* renderer)
{
	SDL_Texture* texture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Failed to load Image \n");
	}
	else
	{
		texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (texture == NULL)
		{
			printf("Failed to Create Texture of ");
		}

		SDL_FreeSurface(loadedSurface);
	}

	return texture;
}

//Supports BMP, GIF, JPEG, LBM, PCX, PNG, PNM, TGA, TIFF, WEBP, XCF, XPM, XV
SDL_Surface* DAS_LoadImage(std::string path, SDL_Surface* screen)
{
	SDL_Surface* optimizedSurface = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Failed to load Image \n");
	}
	else
	{
		optimizedSurface = SDL_ConvertSurface(loadedSurface, screen->format, 0);
		if (optimizedSurface != NULL)
		{
			//Section for color keying code
		}
		else
		{
			printf("Failed to optimize Image \n");
		}

		//Deallocate
		SDL_FreeSurface(loadedSurface);
	}

	return optimizedSurface;
}

#endif
