#ifndef PROJETIL_H
#define PROJETIL_H

#include "raylib.h"
#include "inimigos.h"
#include "entity.h"

typedef struct Projectil {
    Vector2 position;
    Vector4 position_;
    Vector2 speed;
    bool isFacingUp;
    struct Projectil* next; // Pointer to the next bullet in the list
} Projectil;

extern Projectil* bulletList; // Pointer to the first bullet in the list

// Function to add a bullet to the list
void addProjectil(Rectangle playerRect, float speed, int playerDirec, bool isPlayerLookingUp);

// Function to remove a bullet from the list
void removeProjectil(Projectil* bullet);

bool updateProjectils(Texture2D projectilTexture, Rectangle sourceRecProject, int SCREEN_WIDTH, RU* Ru, int* cont, bool isPlayerLookingUp, Platforms *platforms);





#endif // PROJETIL_H