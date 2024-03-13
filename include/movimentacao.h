
#ifndef MOVIMENTACAO_H
#define MOVIMENTACAO_H

#include "raylib.h"
#include "entity.h"
#include <stdlib.h>

#define GROUND_LEVEL 400


void movx(Player *player, Platforms *platforms);

float movy(float posy, float gravidade);

void pulo(Player *player, float gravidade, Platforms *platforms, int platformsLenght);


#endif // MOVIMENTACAO_H