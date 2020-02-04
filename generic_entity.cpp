#pragma once

#include "src/DAS_Entity.h"

class generic_entity: public DAS_Entity
{
public:
	generic_entity(std::string path, int x, int y) :
			DAS_Entity()
	{
		load(path);
		setX(x);
		setY(y);
		setInputOn(false);
	}

	generic_entity(std::string path) :
			DAS_Entity()
	{
		load(path);
	}

	void logic()
	{
	}

	void input(SDL_Event& event)
	{

	}

private:
};
