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
    bool isAlive;
    
    float hitTimer;


    float deathTimer;
    float jumpSpeed;

    float health;
    float damage;
    float speed;


} Player;  

typedef struct Platforms{
    Rectangle rec;
    bool isBlocking;    

} Platforms;



typedef struct {
    float enemy_POSINICIAL_X;
    float enemy_POSINICIAL_Y;
    float enemy_DIM_X;
    float enemy_DIM_Y;

    Rectangle rec;

    int direct;
    bool isJumping;
    bool isAlive;
    bool attackPosition;
    

    float hitTimer;
    float deathTimer;

    float hitDelay; 
    float attackAnimationLength; 
    float attackAnimationTimer; 
    float timeSinceLastHit;      
    float attackThreshold;
    
    float health;
    float damage;
    float speed;
    
} Enemy; 


typedef enum {
    CarangueijoArmandoCarlos,
    RonaldoUmidade,
    CalabresoTarcioGeometria
} TipoInimigo;


typedef struct {
    
    float posx;
    float posy;
    int direct;
    int contGun;
    float speed;
    Rectangle rec;
    
} gun;


// typedef struct {
    
//     float posx;
//     float posy;
//     int direct;
//     int contGun;
//     float speed;
//     Rectangle rec;
    
// }GUNCTG;

// typedef struct {
    
//     float posx;
//     float posy;
//     int direct;
//     int contGun;
//     float speed;
//     Rectangle rec;
    
// }GUNRU;

// typedef struct {
    
//     float posx;
//     float posy;
//     int direct;
//     int contGun;
//     float speed;
//     Rectangle rec;
    
// }GUNCAC;


#endif