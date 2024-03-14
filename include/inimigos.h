
#ifndef INIMIGOS_H
#define INIMIGOS_H

#include "raylib.h"
#include "entity.h"
#include <stdio.h>
#include <stdlib.h>

float f2(float posx, float speed, int direct);

void updateGun(gun* GunCTG, int contGun, Texture2D bulletTexture);

void updateEnemy(int type, Enemy* CTG, int* contCTG, int SCREEN_WIDTH, int* direct, float Pposx, Texture2D bala, gun** GunCTG, int* contGun, bool collision, Player player);

gun* addGun(float posX, float posY, gun* Bala, int* cont, Texture2D bala, int* direct);

Enemy* addEnemy(Enemy* CAC, int* contCAC, Texture2D inimigo1SpriteSheet);

#endif // INIMIGOS_H