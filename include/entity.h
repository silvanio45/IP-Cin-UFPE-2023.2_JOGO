#ifndef ENTITY_H
#define ENTITY_H

#include "raylib.h"

typedef struct {
    Vector2 position;
    Rectangle rec;

    int direc;
    bool isJumping;
    bool isPlayerLookingUp;
    bool isPlayerFalling;
    float jumpSpeed;

    float health;
    float damage;
    float speed;
} Player;  

typedef struct Platforms{
    Rectangle rec;
    bool isBlocking;    

} Platforms;


typedef struct RU {
    float Ru_POSINICIAL_X;
    float Ru_POSINICIAL_Y;
    float Ru_DIM_X;
    float Ru_DIM_Y;

    Rectangle rec;

    int direc;
    bool isJumping;
    bool isAlive;

    float health;
    float damage;
    float speed;
    
    float hitTimer;
    float deathTimer;
    bool hit;

    int currentFrame;
    int frameCount;
    int frameWidth;
    int frameHeight;
    
} RU; 

#endif
