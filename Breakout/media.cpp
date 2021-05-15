#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "defs.h"
#include "entity.h"


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

//TODO 
//have it take in a texture pointer and path
bool loadMedia(Player* player, std::string path)
{	//loading flag
	bool wasSuccessful = true;

	//Load image
	//send to surface loader first
	player->texture = loadTexture(path);
	if (player->texture == NULL)
	{
		printf("Unable to LOAD image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		wasSuccessful = false;
	}

	return wasSuccessful;

}


void blit(SDL_Texture* texture, int x, int y)
{
	SDL_Rect blitBox;
	blitBox.x = x;
	blitBox.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &blitBox.w, &blitBox.h);
	SDL_RenderCopy(gRenderer, texture, NULL, &blitBox);
}