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
    int pontuacao;

    int lives; //qtd vidas do player 

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

typedef enum {

    RonaldoUmidade,
    CalabresoTarcioGeometria, // CTG
    CarangueijoArmandoCarlos,

} TipoInimigo;

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
    bool set;
    
    float hitTimer;
    float deathTimer;
    float pontuacao;

    float hitDelay; 
    float attackAnimationLength; 
    float attackAnimationTimer; 
    float timeSinceLastHit;      
    float attackThreshold;
    
    float health;
    float damage;
    float speed;
    
} Enemy; 


typedef struct {
    
    float posx;
    float posy;
    int direct;
    int contGun;
    float speed;
    Rectangle rec;
    
} gun;


#endif