#include <SDL.h>
#include "entity.h"


void getInput(SDL_Event& event, Player& player)
{

	int velocity = 200;
	//key press
	if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_UP: player.velY -= velocity; break;
		case SDLK_DOWN:  player.velY += velocity; break;
		case SDLK_LEFT: player.velX -= velocity; break;
		case SDLK_RIGHT: player.velX += velocity; break;

		}
	}
	else if (event.type == SDL_KEYUP && event.key.repeat == 0)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_UP: player.velY += velocity; break;
		case SDLK_DOWN:  player.velY -= velocity; break;
		case SDLK_LEFT: player.velX += velocity; break;
		case SDLK_RIGHT: player.velX -= velocity; break;
		}
	}


}


void move(Player& player, double dT)
{
	player.posX += player.velX * dT;
	//If the dot went too far to the left or right
	if ((player.posX < 0) || (player.posX + 64 > SCREEN_WIDTH))
	{
		//Move back
		player.posX -= player.velX * dT;
	}

	player.posY += player.velY * dT;
	//If the dot went too far to the left or right
	if ((player.posY < 0) || (player.posY + 20 > SCREEN_HEIGHT))
	{
		//Move back
		player.posY -= player.velY * dT;
	}
	printf("dT %f!\n", dT);
	printf("Player.posX %f! Player.velX: %i\n", player.posX, player.velX);
	//printf("Player.posY %d! Player.posX: %d\n", player.posY, player.posX);
}