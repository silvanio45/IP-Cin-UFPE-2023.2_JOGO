
#ifndef MOVIMENTACAO_H
#define MOVIMENTACAO_H

#include "raylib.h"
#include <stdlib.h>

float mov(float pos, float speed);

float movx(float posx, float speed);

float movy(float posy, float gravidade);

float pulo(float posy, float *velY, float gravidade, float bonecoHeight, float delta, bool *isJumping, bool *jump);


#endif // MOVIMENTACAO_H