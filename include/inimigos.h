
#ifndef INIMIGOS_H
#define INIMIGOS_H

#include "raylib.h"
#include "entity.h"
#include <stdio.h>
#include <stdlib.h>
#include "animacao.h"
#include <math.h>

extern SpriteAnimation inimAnim_walkingRight;
extern SpriteAnimation inimAnim_walkingLeft;
extern SpriteAnimation inimAnim_dyingLeft;
extern SpriteAnimation inimAnim_dyingRight;
extern SpriteAnimation inimAnim_attackingLeft;
extern SpriteAnimation inimAnim_attackingRight;

float f2(float posx, float speed, int direct);

void updateGun(gun* GunCTG, int contGun, Texture2D bulletTexture);

void updateEnemy(int type, Enemy* CTG, int* contCTG, int SCREEN_WIDTH, int* direct, float Pposx, Texture2D bala, gun** GunCTG, int* contGun, bool collision, Player *player);

gun* addGun(float posX, float posY, gun* Bala, int* cont, Texture2D bala, int* direct);

Enemy* addEnemy(Enemy* enemy, int* contEnemy,  float SpawnX, float SpawnY, TipoInimigo tipo);

void selectEnemy(Enemy* enemy, TipoInimigo tipo);


#endif // INIMIGOS_H