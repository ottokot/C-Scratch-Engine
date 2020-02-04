/*
 * Depecrated and combined with state because of memory leaks
 * needs restructuring before it can renenter use
#ifndef DAS_ENTITYMANAGER_H
#define DAS_ENTITYMANAGER_H

#pragma once

#include "DAS_Entity.h"

#include <vector>

class DAS_EntityManager
{
public:
	void start();
	void logic();
	void input(SDL_Event& event);
	void clear();
	void destroyEntity(int element);
	void deallocate();

	std::vector<DAS_Entity*>* getELV();
	void setELV(std::vector<DAS_Entity*>*);
private:
	std::vector<DAS_Entity*>* container;
};

std::vector<DAS_Entity*>* DAS_EntityManager::ELVget()
{
	return container;
}

void DAS_EntityManager::ELVlogic()
{
	for (unsigned int i = 0; i < container->size(); i++)
	{
		container->at(i)->logic();

		if (container->at(i)->getVisible() == true)
		{
			container->at(i)->render();
		}
	}
}

void DAS_EntityManager::ELVinput(SDL_Event& event)
{
	for (unsigned int i = 0; i < container->size(); i++)
	{
		if (container->at(i)->getInputOn() == true)
		{

			container->at(i)->input(event);
		}
	}
}

void DAS_EntityManager::ELVdestroyEntity(int element)
{
	if (container->at(element) != NULL)
	{
		container->at(element)->deallocate();
		delete container->at(element);
		container->at(element) = NULL;
		container->erase(container->begin() + element);
	}
}

void DAS_EntityManager::ELVclear()
{
	for (unsigned int i = 0; i < container->size(); i++)
	{
		destroyEntity(i);
	}
}

void DAS_EntityManager::ELVdeallocate()
{
	clear();
	container->clear();
	delete container;
	container = NULL;
}

#endif
 */
