
#ifndef INIMIGOS_H
#define INIMIGOS_H

#include "raylib.h"
#include "../include/entity.h"
#include <stdio.h>
#include <stdlib.h>

float RonaldoUmidadef2(float RUPosx, float speed);

void updateRu(Texture2D playerSpriteSheet, Texture2D inimigo1SpriteSheet, Texture2D inimigo2SpriteSheet, Texture2D inimigo3SpriteSheet, RU* Ru, int* cont, int SCREEN_WIDTH, bool collision);

RU* addRu(RU* Ru, int* cont, Texture2D playerSpriteSheet, Texture2D inimigo1SpriteSheet, Texture2D inimigo2SpriteSheet, Texture2D inimigo3SpriteSheet);

#endif // INIMIGOS_H