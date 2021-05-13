//Using SDL and standard IO
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

//Functions Declaration
// 
//start up SDL
bool init();
//load media;
bool loadMedia();
//free media and close SDL
void close();
//load texture
SDL_Texture* loadTexture(std::string path);
//load image 
//SDL_Surface* loadSurface(std::string path);

//Variables and Constants
// 
//The window we'll be rendering to
SDL_Window* gWindow = NULL;
//The window renderer
SDL_Renderer* gRenderer = NULL;
//Current Display Texture
SDL_Texture* gTexture = NULL;
//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;
//The greenblock image
SDL_Surface* gcurrentSurface = NULL;
//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


bool init()
{
	//init flag
	bool wasSuccessful = true; 

	//Init SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		wasSuccessful = false;
	}
	//Create window
	gWindow = SDL_CreateWindow("Breakout", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (gWindow == NULL)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		wasSuccessful = false;
	}
	else
	{
		//create renderer 
		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
		if (gRenderer == NULL)
		{
			printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
			wasSuccessful = false;
		}
		else
		{
			//Initialize renderer color
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			//Init PNG loading
			int imgFlags = IMG_INIT_PNG;
			if(!(IMG_Init(imgFlags) & imgFlags))
			{
				printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
				wasSuccessful = false;
			}
			//Get window surface
			//gScreenSurface = SDL_GetWindowSurface(gWindow);
		}
	}
	return wasSuccessful;
}

//load texture
SDL_Texture* loadTexture(std::string path)
{
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}
	
	return newTexture;
}

////optimized surfaces
//SDL_Surface* loadSurface(std::string path)
//{
//	SDL_Surface* optimizedSurface = NULL;
//	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
//
//	if (loadedSurface == NULL)
//	{
//		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
//	}
//	else
//	{
//		//Convert surface to screen format
//		optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, 0);
//		if (optimizedSurface == NULL)
//		{
//			printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
//		}
//
//		//Get rid of old loaded surface
//		SDL_FreeSurface(loadedSurface);
//	}
//
//	return optimizedSurface;
//}


bool loadMedia() 
{	//loading flag
	bool wasSuccessful = true;
	
	//Load image
	//send to surface loader first
	gTexture = loadTexture("../Assets/greenBlock.png");
	if (gTexture == NULL)
	{
		printf("Unable to LOAD image %s! SDL Error: %s\n", "../Assets/greenBlock.png", SDL_GetError());
		wasSuccessful = false;
	}

	return wasSuccessful;

}

void close()
{
	//Free loaded image
	SDL_DestroyTexture(gTexture);
	gTexture = NULL;

	//Destroy window    
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

typedef struct
{
	float posX;
	float posY;
	int velX;
	int velY;
	SDL_Texture* texture; 
}Player;


void blit(SDL_Texture* texture, int x, int y)
{
	SDL_Rect blitBox; 
	blitBox.x = x;
	blitBox.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &blitBox.w, &blitBox.h);
	SDL_RenderCopy(gRenderer, texture, NULL, &blitBox);
}



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
	player.posX += player.velX*dT;
	//If the dot went too far to the left or right
	if ((player.posX < 0) || (player.posX + 64 > SCREEN_WIDTH))
	{
		//Move back
		player.posX -= player.velX*dT;
	}

	player.posY += player.velY*dT;
	//If the dot went too far to the left or right
	if ((player.posY < 0) || (player.posY + 20 > SCREEN_HEIGHT))
	{
		//Move back
		player.posY -= player.velY*dT;
	}
	printf("dT %f!\n", dT);
	printf("Player.posX %f! Player.velX: %i\n", player.posX, player.velX);
	//printf("Player.posY %d! Player.posX: %d\n", player.posY, player.posX);
}



int main(int argc, char* args[])
{
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

		Player player;
		player.posX = SCREEN_WIDTH/2;
		player.posY = SCREEN_HEIGHT/2;
		player.velX = 0;
		player.velY = 0;
		player.texture = NULL;


		//Event handler
		SDL_Event event; 
		//Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			player.texture = gTexture;
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

				
				
				//printf("current %d! last: %d\n", currentTime, lastTime);
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}




