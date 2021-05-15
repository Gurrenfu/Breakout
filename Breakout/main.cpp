#include "setup.h"
#include "media.h"
#include "entity.h"


//dot has been fired
bool gFired = false;

// player to entity
//put entities into array and have close deallocate each
void close(Player* player, Player* dot)
{
	//Free loaded image
	SDL_DestroyTexture(player->texture);
	player->texture = NULL;

	//Free loaded image
	SDL_DestroyTexture(dot->texture);
	dot->texture = NULL;

	//Destroy window    
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}


int main(int argc, char* args[])
{
	Player player;
	Player dot; 

	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{	
		bool quit = false;
		Uint32 lastTime = 0;
		Uint32 currentTime = 0;
		double deltaTime = 0;

		player.posX = SCREEN_WIDTH/2;
		player.posY = SCREEN_HEIGHT/2;
		player.velX = 0;
		player.velY = 0;
		player.velMag = 200;
		player.texture = NULL;

		dot.posX = player.posX + 28;
		dot.posY = player.posY - 7;
		dot.velX = player.velX;
		dot.velY = player.velY;
		dot.velMag = 200;
		dot.texture = NULL;

		//Event handler
		SDL_Event event; 


		//Load media
		if (!(loadMedia(&player, "../Assets/greenBlock.png") && loadMedia(&dot, "../Assets/blueDot.png")))
		{
			printf("Failed to load media!\n");
		}
		else
		{
			//player.texture = gTexture;
			currentTime = SDL_GetTicks();

			while (!quit)
			{
				lastTime = currentTime;
				currentTime = SDL_GetTicks();
				deltaTime = (currentTime - lastTime)/1000.0f;

				while (SDL_PollEvent(&event) != 0)
				{
					if (event.type == SDL_QUIT)
					{
						quit = true;
					}

					getInput(event, player);

					if (gFired)
					{
						setVelVector(dot, 0, -200);
					}
					else
					{
						setVelVector(dot, player.velX, player.velY);
					}
				}

				move(player, deltaTime);
				move(dot, deltaTime);
				//Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);
				//Render texture to screen
				blit(player.texture, player.posX, player.posY);
				blit(dot.texture, dot.posX, dot.posY);
				//Update screen
				SDL_RenderPresent(gRenderer);
			}
		}
	}

	//Free resources and close SDL
	close(&player, &dot);

	return 0;
}




