#pragma once

#include "src/DAS.h"

class player_entity: public DAS_Entity
{
public:
	player_entity(std::string path, int x, int y) :
			DAS_Entity()
	{
		load(path);
		isJump = false;
		isDoubleJump = false;
		jdjcurve = false;
		jumpReleased = true;
		isFalling = false;
		isRight = false;
		isLeft = false;
		vel = 300;
		jumpCap = 300; //Lower value equals Higher jump
		doubleJumpMod = -300; //Modifier of jump cap the second jump will jump off the first jumps current point
		doubleJumpCap = jumpCap; //Cap initializes to equal jump cap but will get modified on use to jump f
		velmod.start();
		floorTMP = 600; //Temporary variable for the ground level until collision detection is added

		spawn(x, y - getHeight());
	}

	~player_entity()
	{
		deallocate();
	}

	void logic()
	{
		if (!getCollid())
		{
			if (isFalling)
			{
				if (isJump || isDoubleJump)
				{
					jump();
				}
				else
				{
					gravity();
				}
			}
		}

		movement();

		checkFalling();

		if (getCollid())
		{
			isDoubleJump = false;
			jdjcurve = false;
		}
	}

	void input(SDL_Event& event)
	{
		if (event.type == SDL_KEYDOWN)
		{
			if (DAS_KEY == SDLK_LEFT || DAS_KEY == SDLK_a)
			{
				isLeft = true;
			}
			if (DAS_KEY == SDLK_RIGHT || DAS_KEY == SDLK_d)
			{
				isRight = true;
			}
			if (DAS_KEY == SDLK_SPACE || DAS_KEY == SDLK_w
					|| DAS_KEY == SDLK_UP)
			{
				if (jumpReleased)
				{
					if (isFalling && !isDoubleJump && !jdjcurve)
					{
						doubleJumpCap = getY() + doubleJumpMod;
						isJump = false;
						isDoubleJump = true;
					}

					if (!isFalling)
					{
						isJump = true;
						isFalling = true;
					}

					jumpReleased = false;
				}
			}
		}

		if (event.type == SDL_KEYUP)
		{
			if (DAS_KEY == SDLK_LEFT || DAS_KEY == SDLK_a)
			{
				isLeft = false;
			}
			if (DAS_KEY == SDLK_RIGHT || DAS_KEY == SDLK_d)
			{
				isRight = false;
			}
			if (DAS_KEY == SDLK_SPACE || DAS_KEY == SDLK_w
					|| DAS_KEY == SDLK_UP)
			{
				jumpReleased = true;
			}
		}
	}

private:
	bool isJump;
	bool isDoubleJump;
	bool jdjcurve;
	bool jumpReleased;
	bool isFalling;
	bool isRight;
	bool isLeft;
	DAS_Ficond velmod;
	int vel;
	int jumpCap;
	int doubleJumpMod;
	int doubleJumpCap;
	int floorTMP;

	void spawn(int x, int y)
	{
		setX(x);
		setY(y);
	}

	void movement()
	{
		if (isRight)
		{
			moveRight();
		}

		if (isLeft)
		{

			moveLeft();
		}

		velmod.restart();
	}

	void moveRight()
	{
		setX(getX() + calvel());
		collider();
	}

	void moveLeft()
	{
		setX(getX() - calvel());
		collider();
	}

	void jump()
	{

		if (getY() > jumpCap && isJump && !isDoubleJump)
		{
			setY(getY() - calvel());
		}
		else
		{
			isJump = false;
		}

		if (getY() > doubleJumpCap && isDoubleJump)
		{
			setY(getY() - calvel());
		}
		else
		{
			isDoubleJump = false;
		}

		if (getY() <= doubleJumpCap)
		{
			jdjcurve = true;
		}
	}

	void checkFalling()
	{
		if (getY() > (floorTMP - getHeight()))
		{
			setY(floorTMP - getHeight());
			isFalling = false;
			isJump = false;
			isDoubleJump = false;
			jdjcurve = false;
		}

		if (getY() == floorTMP - getHeight())
		{
			isFalling = false;
			isJump = false;
			isDoubleJump = false;
			jdjcurve = false;
		}

		if (getY() < floorTMP - getHeight())
		{
			isFalling = true;
		}
	}

	void gravity()
	{

		if (getY() < (floorTMP - getHeight()))
		{
			setY(getY() + calvel());

		}
	}

	double calvel()
	{
		double velcal = velmod.getTicks() / 1000.0f;
		velcal *= vel;
		return velcal;
	}

}
;

