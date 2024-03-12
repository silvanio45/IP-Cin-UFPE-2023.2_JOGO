#ifndef ENTITY_H
#define ENTITY_H

#include "raylib.h"
#include "animacao.h"

typedef struct {

    char type[30];
    float damage;
    float bulletSpeed;
    float shotDelay;
    float timeSinceLastShot;

} Gun;

typedef struct {
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

typedef struct Enemy{
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
    

} Enemy;  





#endif 