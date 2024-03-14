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
    
    float health;
    float damage;
    float speed;
    
} Enemy; 


// typedef struct {
//     float Ru_POSINICIAL_X;
//     float Ru_POSINICIAL_Y;
//     float Ru_DIM_X;
//     float Ru_DIM_Y;

//     Rectangle rec;

//     int direct;
//     bool isJumping;
//     bool isAlive;
//     bool hit;

//     float health;
//     float damage;
//     float speed;
    
// } RU; 

// typedef struct {
//     float CAC_POSINICIAL_X;
//     float CAC_POSINICIAL_Y;
//     float CAC_DIM_X;
//     float CAC_DIM_Y;

//     Rectangle rec;

//     int direct;
//     bool isJumping;

//     float health;
//     float damage;
//     float speed;
    
// } CarangueijoArmandoCarlos; 

// typedef struct {
//     float CTG_POSINICIAL_X;
//     float CTG_POSINICIAL_Y;
//     float CTG_DIM_X;
//     float CTG_DIM_Y;

//     Rectangle rec;

//     int direct;
//     int contGun;
    
//     bool isJumping;
    
//     float health;
//     float damage;
//     float speed;
    
// } CalabresoTarcioGeometria; 

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