#ifndef PROJETIL_H
#define PROJETIL_H

#include "raylib.h"

typedef struct Bullet {
    Vector2 position;
    float speed;
    struct Bullet* next; // Pointer to the next bullet in the list
} Bullet;

extern Bullet* bulletList; // Pointer to the first bullet in the list

// Function to add a bullet to the list
void addBullet(Rectangle playerRect, float speed, int playerDirec);

// Function to remove a bullet from the list
void removeBullet(Bullet* bullet);

void updateBullets(Texture2D bulletTexture, Rectangle sourceRecBullet, int SCREEN_WIDTH);

#endif // PROJETIL_H