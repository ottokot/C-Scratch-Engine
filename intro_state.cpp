#include "player_entity.cpp"
#include "generic_entity.cpp"

STATE intro_state

START

	void load()
	{
		setBackground("wadc/outside_scene.wad");

		addEntity(new player_entity("wadc/player.wad", 0, 0));
		addEntity(new generic_entity("wadc/npc.wad", 200, 200));
		addEntity(new generic_entity("wadc/block.wad", 450, 200));
		addEntity(new generic_entity("wadc/wall.wad", 300, 200));
		addSound("click", new DAS_Sound("wadc/click_long.wad"));
		addSound("bgmusic", new DAS_Sound("wadc/background_music.wad"));

		playSound("bgmusic");
	}

	void render(SDL_Renderer* renderer)
	{
		message("FPS: " + getFPS_str());

		message("MOLLY!!! ", 170, 170);
	}

	void input(SDL_Event event)
	{
		if (event.type == SDL_KEYUP)
		{
			if (DAS_KEY == SDLK_ESCAPE)
			{
				terminationRequest();
			}

			if (DAS_KEY == SDLK_RETURN)
			{
				playSound("click");
			}
		}
	}

	void logic()
	{
	}

END
