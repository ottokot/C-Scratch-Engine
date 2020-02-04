#ifndef DAS_STATEMANAGER_H
#define DAS_STATEMANAGER_H

#pragma once

#include "DAS_State.h"
#include "DAS_EntityManager.h"
#include <stack>
#include <iostream>

class DAS_StateManager
{
public:
	DAS_StateManager(DAS_State* state);
	~DAS_StateManager();
	DAS_State* getState();
	bool changeState();
	void setState(DAS_State* state);
	void deallocate();
	//direct access state modification
	void dasm(DAS_State* state);

	bool getTerminationRequest();

private:

	void push(DAS_State* state);
	void pop();

	std::stack<DAS_State*> state_stack;
	DAS_State* state;
};

DAS_StateManager::DAS_StateManager(DAS_State* state)
{
	this->state = state;
}

DAS_StateManager::~DAS_StateManager()
{
	deallocate();
}

//A work around for the NULL statemanager in order to intialize out side of it declaration
void DAS_StateManager::dasm(DAS_State* state)
{
	this->state = state;
	push(state);
	state_stack.top()->load();
}

bool DAS_StateManager::changeState()
{
	if (state_stack.top()->isChangeState())
	{
		state_stack.top()->deallocate();
		setState(state_stack.top()->getNextState());
		state_stack.top()->load();
		return true;
	}

	return false;
}

DAS_State* DAS_StateManager::getState()
{
	return state_stack.top();
}

void DAS_StateManager::setState(DAS_State* state)
{
	delete state_stack.top();
	state_stack.top() = NULL;
	if (state_stack.top() != NULL)
	{
		printf("Failed to deallocate state.");
	}
	pop();
	push(state);
}



void DAS_StateManager::push(DAS_State* state)
{
	state_stack.push(state);
}

void DAS_StateManager::pop()
{
	state_stack.pop();
}

void DAS_StateManager::deallocate()
{
	if (getState() != NULL)
	{
		getState()->deallocate();
		delete getState();
		setState(NULL);
	}
}

bool DAS_StateManager::getTerminationRequest()
{
	return state_stack.top()->getTerminationRequest();
}

#endif
