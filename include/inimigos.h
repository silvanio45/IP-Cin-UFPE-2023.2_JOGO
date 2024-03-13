
#ifndef INIMIGOS_H
#define INIMIGOS_H

#include "raylib.h"
#include "entity.h"
#include <stdio.h>
#include <stdlib.h>

float RonaldoUmidadef2(float RUPosx, float speed, int direct);

float CarangueijoArmandoCarlosf2(float CACPosx, float speed, int direct);

float CalabresoTarcioGeometriaf2(float CTGPosx, float speed, int direct);

void updateGunRU(GUNRU* GunRU, int contGun, Texture2D bulletTexture);

void updateGunCAC(GUNCAC* GunCAC, int contGun, Texture2D bulletTexture);

void updateGunCTG(GUNCTG* GunCTG, int contGun, Texture2D bulletTexture);

void updateRu(Texture2D inimigo1SpriteSheet, RU* Ru, int* cont, int SCREEN_WIDTH, int* direct, float Pposx, Texture2D bala, GUNCTG** GunRU, int* contRU);

void updateCAC(Texture2D inimigo1SpriteSheet, CarangueijoArmandoCarlos* CAC, int* contCAC, int SCREEN_WIDTH, int* direct, float Pposx, Texture2D bala, GUNCAC** GunCAC, int* contGun);

void updateCTG(Texture2D inimigo2SpriteSheet, CalabresoTarcioGeometria* CTG, int* contCTG, int SCREEN_WIDTH, int* direct, float Pposx, Texture2D bala, GUNCTG** GunCTG, int* contGun);

GUNRU* addGunRU(float posX, float posY, GUNRU* Bala, int* cont, Texture2D bala, int* direct);

GUNCAC* addGunCAC(float posX, float posY, GUNCAC* Bala, int* cont, Texture2D bala, int* direct);

GUNCTG* addGunCTG(float posX, float posY, GUNCTG* Bala, int* cont, Texture2D bala, int* direct);

RU* addRu(RU* Ru, int* cont, Texture2D inimigo1SpriteSheet);

CarangueijoArmandoCarlos* addCAC(CarangueijoArmandoCarlos* CAC, int* contCAC, Texture2D inimigo1SpriteSheet);

CalabresoTarcioGeometria* addCTG(CalabresoTarcioGeometria* CTG, int* contCTG, Texture2D inimigo2SpriteSheet);

#endif // INIMIGOS_H