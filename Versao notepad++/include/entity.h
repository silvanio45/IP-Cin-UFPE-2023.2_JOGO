#ifndef ENTITY_H
#define ENTITY_H

#include "raylib.h"

typedef struct {
    Vector2 position;
    Rectangle rec;

    int direc;
    bool isJumping;

    float health;
    float damage;
    float speed;
} Player;  






#endif 