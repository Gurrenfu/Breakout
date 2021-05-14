#ifndef MEDIA_H
#define MEDIA_H

#include <SDL.h>
#include <string>
#include "entity.h"

bool loadMedia(Player* player);
SDL_Texture* loadTexture(std::string path);
void blit(SDL_Texture* texture, int x, int y);

#endif // !MEDIA_H

