#ifndef ENTITY_H
#define ENTITY_H

#include "raylib.h"


typedef struct {

    char type[30];
    float damage;
    float bulletSpeed;
    float shotDelay;
    float timeSinceLastShot;

} Gun;

typedef struct {
    Vector2 position;
    Rectangle rec;

    int direc;
    bool isJumping;
    bool isAlive;
    float deathTimer;
    float health;
    float damage;
    float speed;
    float hitTimer;
    
    Gun gun;

} Player;  




#endif 