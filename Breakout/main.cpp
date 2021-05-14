#include "setup.h"
#include "media.h"
#include "entity.h"


//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;
//The greenblock image
SDL_Surface* gcurrentSurface = NULL;

// player to entity
//put entities into array and have close deallocate each
void close(Player* player)
{
	//Free loaded image
	SDL_DestroyTexture(player->texture);
	player->texture = NULL;

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
		player.texture = NULL;


		//Event handler
		SDL_Event event; 
		//Load media
		if (!loadMedia(&player))
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
				}

				move(player, deltaTime);
				//Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);
				//Render texture to screen
				blit(player.texture, player.posX, player.posY);
				//Update screen
				SDL_RenderPresent(gRenderer);
			}
		}
	}

	//Free resources and close SDL
	close(&player);

	return 0;
}




