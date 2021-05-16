#include "setup.h"
#include "media.h"
#include "entity.h"


//dot has been fired
bool gFired = false;
std::vector<Player> playerEntites;

// player to entity
//put entities into array and have close deallocate each
void close()
{
	//free loaded images
	for (Player e : playerEntites)
	{
		SDL_DestroyTexture(e.texture);
		e.texture = NULL;
	}
	
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
		
		initPlayerStruct(player, "../Assets/greenBlock.png", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0, 0, 200);
		initPlayerStruct(dot, "../Assets/blueDot.png", player.posX + 28, player.posY - 7, player.velX, player.velY, 200);

		//Event handler
		SDL_Event event; 

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

	//Free resources and close SDL
	close();

	return 0;
}




