#ifndef ENTITY_H
#define ENTITY_H

#include <SDL.h>
#include <stdio.h>
#include <string>
#include <vector>
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


typedef struct
{
	float posX;
	float posY;
	SDL_Texture* texture;

}Obstacle;

extern std::vector<Player> playerEntites;
void getInput(SDL_Event& event, Player& player);
void setVelVector(Player& entity, int newVelX, int newVelY);
void move(Player& player, double dT);
void initPlayerStruct(Player& entity, std::string path, float posX, float posY, int velX = 0, int velY = 0, int velMag = 100);


#endif // !ENTITY_H

