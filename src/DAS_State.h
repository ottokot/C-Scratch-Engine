#ifndef DAS_STATE_H
#define DAS_STATE_H

#pragma once

#include <iostream>

#include "DAS_Entity.h"
#include "DAS_Sound.h"

#include <stdio.h>
#include <SDL.h>

#include <vector>

class DAS_State
{
public:
	DAS_State();
	virtual ~DAS_State();

	virtual void deallocate();

	virtual void load() = 0;
	virtual void logic() = 0;
	virtual void render(SDL_Renderer* renderer) = 0;
	virtual void input(SDL_Event event) = 0;

	DAS_State* getNextState();
	bool isChangeState();
	void changeState(DAS_State* state);

	void terminationRequest();
	bool getTerminationRequest();

	DAS_Entity** getELV();
	void addEntity(DAS_Entity* entity);
	void destroyEntity(int element);

	bool getUpdateELV();
	void setUpdateELV(bool updateELV);

	void ELVdeallocate();
	void ELVclear();
	void ELVdestroyEntity(int element);
	void ELVinput(SDL_Event& event);
	void ELVlogic();

	int getELVCounter();

	void addSound(std::string name, std::string path);
	void addSound(std::string name, DAS_Sound* sound);
	void playSound(std::string path);
	void destroySound(DAS_Sound* sound);

	void setBackground(std::string path);
	void renderBackground();
private:
	bool terminate;
	bool isStateChange;
	bool isUpdateELV;

	DAS_State* nextState;
	DAS_Texture* background;

	//EntityLoadVector
	int ELVCounter;
	int ELVLimit;
	DAS_Entity* container[255];
	int SLVCounter;

	int SLVLimit;
	//SoundLoadVectorKey
	std::string SLVK[24];

	//SoundLoadVector
	DAS_Sound* SLV[24];

	void deallocateSound();
	void deallocateBackground();
};

DAS_State::DAS_State()
{
	ELVCounter = 0;
	ELVLimit = 255;
	SLVCounter = 0;
	SLVLimit = 24;
	isStateChange = false;
	nextState = NULL;
	terminate = false;
	isUpdateELV = false;
	background = NULL;
}

DAS_State::~DAS_State()
{
	deallocate();
	for (int i = 0; i < ELVCounter; i++)
	{
		destroyEntity(i);
	}

	deallocateSound();
	deallocateBackground();
}

void DAS_State::deallocate()
{
}

void DAS_State::renderBackground()
{
	if (background != NULL)
	{
		background->render();
	}
}

void DAS_State::setBackground(std::string path)
{
	deallocateBackground();
	background = new DAS_Texture(path);
}

void DAS_State::deallocateBackground()
{
	if (background != NULL)
	{
		background->deallocate();
		delete background;
		background = NULL;
	}
}

//Entity Load Vector
DAS_Entity** DAS_State::getELV()
{
	return container;
}

void DAS_State::addEntity(DAS_Entity* entity)
{
	if (ELVCounter < ELVLimit)
	{
		container[ELVCounter] = entity;
		isUpdateELV = true;
		ELVCounter++;
	}
	else
	{
		entity->deallocate();
		delete entity;
		entity = NULL;
	}
}

void DAS_State::destroyEntity(int element)
{
	if (container[element] != NULL)
	{
		container[element]->deallocate();
		delete container[element];
		container[element] = NULL;
	}
}

bool DAS_State::getUpdateELV()
{
	return isUpdateELV;
}

void DAS_State::setUpdateELV(bool updateELV)
{
	isUpdateELV = updateELV;
}

bool DAS_State::isChangeState()
{
	return isStateChange;
}

void DAS_State::changeState(DAS_State* state)
{
	nextState = state;
	this->isStateChange = true;
}

DAS_State* DAS_State::getNextState()
{
	return nextState;
}

void DAS_State::terminationRequest()
{
	terminate = true;
}

bool DAS_State::getTerminationRequest()
{
	return terminate;
}

//Memory leaks where occuring when interfaced with EntityManager temporary work around having its methods exist here
//This was caused by vector has since been removed and now use a set array
void DAS_State::ELVlogic()
{
	for (int z = 0; z < ELVCounter; z++)
	{
		if (container[z] != NULL)
		{

			//Extremly ineffecicent and bad collision dectection
			//maybe good enough doesnt check againest self anymore
			//and it does work

			for (int i = 0; i <= ELVCounter - 1; i++)
			{
				if (container[i] != NULL)
				{
					if (z != i)
					{
						if (SDL_HasIntersection(container[z]->collider(),
								container[i]->collider()))
						{
							container[z]->setCollid(true);
							container[i]->setCollid(true);
							break;
						}
						else
						{
							container[z]->setCollid(false);
						}
					}
				}
			}

			container[z]->logic();

			if (container[z]->getVisible() == true)
			{
				container[z]->render();
			}
		}
	}

}

void DAS_State::ELVinput(SDL_Event& event)
{
	for (int i = 0; i < ELVCounter; i++)
	{
		if (container[i] != NULL)
		{
			if (container[i]->getInputOn() == true)
			{
				container[i]->input(event);
			}
		}
	}
}

void DAS_State::ELVclear()
{
	for (int i = 0; i < ELVCounter; i++)
	{
		destroyEntity(i);
	}
}

void DAS_State::ELVdeallocate()
{
	ELVclear();
}

int DAS_State::getELVCounter()
{
	return ELVCounter;
}

//Sound management stored in state using simmilar funcanality to elv should be refracted into its own object eventually
void DAS_State::addSound(std::string name, std::string path)
{
	if (SLVCounter < SLVLimit)
	{
		SLVK[SLVCounter] = name;
		SLV[SLVCounter] = new DAS_Sound(path);
		SLVCounter++;
	}
}

void DAS_State::addSound(std::string name, DAS_Sound* sound)
{
	if (SLVCounter < SLVLimit)
	{
		SLVK[SLVCounter] = name;
		SLV[SLVCounter] = sound;
		SLVCounter++;
	}
	else
	{
		sound->deallocate();
		delete sound;
		sound = NULL;
	}
}

void DAS_State::playSound(std::string path)
{
	for (int i = 0; i < ELVCounter; i++)
	{
		if (path == SLVK[i])
		{
			if (SLV[i] != NULL)
			{
				SLV[i]->play();
			}
		}
	}
}

void DAS_State::destroySound(DAS_Sound* sound)
{
	if (sound != NULL)
	{
		sound->deallocate();
		delete sound;
		sound = NULL;
	}
}

void DAS_State::deallocateSound()
{
	for (int i = 0; i < ELVCounter; i++)
	{
		destroySound(SLV[i]);
	}
}

#endif
