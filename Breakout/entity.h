#ifndef ENTITY_H
#define ENTITY_H

#include <SDL.h>
#include <stdio.h>
#include <string>
#include "defs.h"

typedef struct
{
	float posX;
	float posY;
	int velX;
	int velY;
	
	int velMag; 
	SDL_Texture* texture;
}Player;


void getInput(SDL_Event& event, Player& player);
void setVelVector(Player& entity, int newVelX, int newVelY);
void move(Player& player, double dT);


#endif // !ENTITY_H

