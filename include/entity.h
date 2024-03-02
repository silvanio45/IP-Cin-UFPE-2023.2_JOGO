#ifndef ENTITY_H
#define ENTITY_H

#include "raylib.h"

typedef struct {
    Vector2 position;
    Rectangle playerRect;

    int direc;
    int isJumping;

    float health;
    float damage;
    float speed;
} Player;  






#endif 