#ifndef DAS_TEXTURE_H
#define DAS_TEXTURE_H

#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include <string>
#include <cstring>
#include <stdio.h>

class DAS_Texture
{
public:
	DAS_Texture();
	DAS_Texture(std::string path);
	~DAS_Texture();

	void deallocate();

	void load(std::string path, SDL_Renderer* renderer);
	void load(std::string path);

	//These renders gotta be cleaned up and tested throughly
	void render(double, double, SDL_Rect*, SDL_Renderer*);
	void render(double, double, SDL_Renderer*);
	void render(SDL_Rect*, SDL_Renderer*);
	void render(SDL_Renderer*);
	void render();

	bool getVisible();
	void setVisible(bool visible);

	double getWidth();
	double getHeight();

	double getX();
	double getY();

	void setX(double);
	void setY(double);

	SDL_Texture* getTexture();

	SDL_Texture* texture;

private:
	bool isVisible;

	double width;
	double height;

	double xpos;
	double ypos;
};

DAS_Texture::DAS_Texture()
{
	texture = NULL;
	width = 0;
	height = 0;
	xpos = 0;
	ypos = 0;
	isVisible = true;
}

DAS_Texture::DAS_Texture(std::string path)
{
	texture = NULL;
	width = 0;
	height = 0;
	xpos = 0;
	ypos = 0;
	load(path);
}

DAS_Texture::~DAS_Texture()
{
	deallocate();
}

void DAS_Texture::load(std::string path, SDL_Renderer* renderer)
{
	deallocate();

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Failed to Load Image \n");
	}
	else
	{
		SDL_SetColorKey(loadedSurface, SDL_TRUE,
				SDL_MapRGB(loadedSurface->format, 0xFF, 0, 0xFF));
		texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (texture != NULL)
		{
			width = loadedSurface->w;
			height = loadedSurface->h;
		}
		else
		{
			printf("Failed to Create Texture of %s\n", path.c_str());
		}

		SDL_FreeSurface(loadedSurface);
	}
}

bool DAS_Texture::getVisible()
{
	return isVisible;
}

void DAS_Texture::setVisible(bool visible)
{
	isVisible = visible;
}

void DAS_Texture::load(std::string path)
{
	DAS_Texture::load(path, das_renderer);
}

void DAS_Texture::deallocate()
{
	if (texture != NULL)
	{
		SDL_DestroyTexture(texture);
		texture = NULL;
		width = 0;
		height = 0;
	}
}

void DAS_Texture::render(double xpos, double ypos, SDL_Rect* clip,
		SDL_Renderer* renderer)
{
	SDL_Rect renderQuad =
	{ (int) xpos, (int) ypos, (int) width, (int) height };

	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopy(renderer, texture, clip, &renderQuad);
}

void DAS_Texture::render(SDL_Rect* clip, SDL_Renderer* renderer)
{
	render(this->xpos, this->ypos, clip, renderer);
}

void DAS_Texture::render(double xpos, double ypos, SDL_Renderer* renderer)
{
	render(this->xpos, this->ypos, NULL, renderer);
}

void DAS_Texture::render(SDL_Renderer* renderer)
{
	render(this->xpos, this->ypos, NULL, renderer);
}

void DAS_Texture::render()
{
	render(this->xpos, this->ypos, NULL, das_renderer);
}

SDL_Texture* DAS_Texture::getTexture()
{
	return texture;
}

double DAS_Texture::getWidth()
{
	return width;
}

double DAS_Texture::getHeight()
{
	return height;
}

double DAS_Texture::getX()
{
	return this->xpos;
}

double DAS_Texture::getY()
{
	return this->ypos;
}

void DAS_Texture::setX(double x)
{
	this->xpos = x;
}

void DAS_Texture::setY(double y)
{
	this->ypos = y;
}

#endif
