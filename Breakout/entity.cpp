#include <SDL.h>
#include "entity.h"
#include "defs.h"
#include "media.h"


void getInput(SDL_Event& event, Player& player)
{
	//key press
	if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_UP: player.velY -= player.velMag; break;
		case SDLK_DOWN:  player.velY += player.velMag; break;
		case SDLK_LEFT: player.velX -= player.velMag; break;
		case SDLK_RIGHT: player.velX += player.velMag; break;
		case SDLK_SPACE: gFired = true; break;

		}
	}
	else if (event.type == SDL_KEYUP && event.key.repeat == 0)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_UP: player.velY += player.velMag; break;
		case SDLK_DOWN:  player.velY -= player.velMag; break;
		case SDLK_LEFT: player.velX += player.velMag; break;
		case SDLK_RIGHT: player.velX -= player.velMag; break;
		}
	}
}

void setVelVector(Player& entity, int newVelX, int newVelY)
{
	entity.velX = newVelX;
	entity.velY = newVelY;
}

void move(Player& entity, double dT)
{
	entity.posX += entity.velX * dT;
	//If the dot went too far to the left or right
	if ((entity.posX < 0) || (entity.posX + 64 > SCREEN_WIDTH))
	{
		//Move back
		entity.posX -= entity.velX * dT;
	}

	entity.posY += entity.velY * dT;
	//If the dot went too far to the left or right
	if ((entity.posY < 0) || (entity.posY + 20 > SCREEN_HEIGHT))
	{
		//Move back
		entity.posY -= entity.velY * dT;
	}
	//printf("dT %f!\n", dT);
	//printf("Player.posX %f! Player.velX: %i\n", player.posX, player.velX);
	//printf("Player.posY %d! Player.posX: %d\n", player.posY, player.posX);
}

void initPlayerStruct(Player& entity, std::string path, float posX, float posY, int velX, int velY, int velMag)
{
	if (!loadMedia(&entity, path))
	{
		printf("Failed to load media for player struct!\n");
	}
	else
	{
		entity.posX = posX;
		entity.posY = posY;
		entity.velX = velX;
		entity.velY = velY;
		entity.velMag = velMag;
		playerEntites.push_back(entity);
	}
}