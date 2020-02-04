#ifndef DAS_H
#define DAS_H

#define DAS_KEY event.key.keysym.sym
#define DEBUG std::cout <<
#define DEBUGSTD std::cout << "DEBUG ACTIVATED" << std::endl;

#define STATE class
#define START : public DAS_State { public:
#define END private: };
#define FUNCTION void

#pragma once

#include "DAS_Main.h"

#include "DAS_Initialize.h"

#include "DAS_Functions.h"

#include "DAS_Camera.h"

#include "DAS_Tile.h"

#include "DAS_Sound.h"

#include "DAS_Texture.h"
#include "DAS_Entity.h"
//EntityManager deprecated until a refractor can happen
#include "DAS_EntityManager.h"

#include "DAS_State.h"
#include "DAS_StateManager.h"

#include "DAS_Ficond.h"

//Oh god magic
void *__gxx_personality_v0;
//end of magic or is it only the begining

#endif
