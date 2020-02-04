#include "intro_state.cpp"

class start_state: public DAS_State
{
public:

	DAS_Texture* scene;

	void load()
	{
		scene = new DAS_Texture("wadc/start_scene.wad");
	}

	void deallocate()
	{
		scene->deallocate();
		delete scene;
		scene = NULL;
	}

	void logic()
	{

	}

	void input(SDL_Event event)
	{
		if (event.type == SDL_KEYDOWN)
		{
			if (DAS_KEY == SDLK_RETURN)
			{
				changeState(new intro_state);
			}
		}
	}

	void render(SDL_Renderer* renderer)
	{
		scene->render();
	}

private:

};
