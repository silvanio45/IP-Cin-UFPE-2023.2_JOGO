#ifndef PROJETIL_H
#define PROJETIL_H

#include "raylib.h"



typedef struct Projectil {
    Vector2 position;
    float speed;
    struct Projectil* next; // Pointer to the next bullet in the list
} Projectil;

extern Projectil* bulletList; // Pointer to the first bullet in the list

// Function to add a bullet to the list
void addProjectil(Rectangle playerRect, float speed, int playerDirec);

// Function to remove a bullet from the list
void removeProjectil(Projectil* bullet);

bool updateProjectils(Texture2D bulletTexture, Rectangle sourceRecBullet, int SCREEN_WIDTH, Rectangle enemy, bool isAlive, float shotingAngle);





#endif // PROJETIL_H