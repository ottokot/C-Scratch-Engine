#ifndef DAS_ENTITY_H
#define DAS_ENTITY_H

#pragma once

#include "DAS_Texture.h"

class DAS_Entity: public DAS_Texture
{
public:
	DAS_Entity() :
			DAS_Texture()
	{
		objrect = new SDL_Rect();
		objrect->x = 0;
		objrect->y = 0;
		objrect->w = 0;
		objrect->h = 0;

		isVisible = true;
		isInput = true;
		isCollid = false;
		isDestroy = false;
	}

	virtual ~DAS_Entity();

	virtual void input(SDL_Event& event);
	virtual void logic();

	SDL_Rect* collider();
	SDL_Rect* examineCollider();

	bool getInputOn();
	bool getVisible();
	bool getCollid();
	bool getDestroy();

	void setInputOn(bool input);
	void setVisible(bool visible);
	void setCollid(bool collid);
	void setDestroy(bool destroy);

private:
	bool isInput;
	bool isVisible;
	bool isCollid;
	bool isDestroy;
	SDL_Rect* objrect;

};

DAS_Entity::~DAS_Entity()
{
	deallocate();
	delete objrect;
}

bool DAS_Entity::getVisible()
{
	return isVisible;
}

bool DAS_Entity::getInputOn()
{
	return isInput;
}

bool DAS_Entity::getCollid()
{
	return isCollid;
}

bool DAS_Entity::getDestroy()
{
	return isDestroy;
}

void DAS_Entity::setVisible(bool visible)
{
	isVisible = visible;
}

void DAS_Entity::setInputOn(bool input)
{
	isInput = input;
}

void DAS_Entity::setCollid(bool collid)
{
	isCollid = collid;
}

void DAS_Entity::setDestroy(bool destroy)
{
	isDestroy = destroy;
}

SDL_Rect* DAS_Entity::collider()
{
	objrect->x = (int) getX();
	objrect->y = (int) getY();
	objrect->w = (int) getWidth();
	objrect->h = (int) getHeight();
	return objrect;
}

SDL_Rect* DAS_Entity::examineCollider()
{
	return objrect;
}

void DAS_Entity::input(SDL_Event& event)
{
}

void DAS_Entity::logic()
{
}

#endif
