#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "../include/entity.h"
#include "../include/animacao.h"



float RonaldoUmidadef2(float RUPosx, float speed) {
    if(RUPosx >= -100){
        RUPosx += speed;
    }
    return RUPosx;
}

RU* addRu(RU* Ru, int* cont, Texture2D playerSpriteSheet, Texture2D inimigo1SpriteSheet, Texture2D inimigo2SpriteSheet, Texture2D inimigo3SpriteSheet){
    Ru = (RU*) realloc(Ru, (*cont+1)*(sizeof(RU)));
    
    Ru[*cont].Ru_POSINICIAL_X = 1280;
    Ru[*cont].Ru_POSINICIAL_Y = 600;
    Ru[*cont].Ru_DIM_X = 105;
    Ru[*cont].Ru_DIM_Y = 105;
    Ru[*cont].speed = -1;
    Ru[*cont].isAlive = true;
    Ru[*cont].hitTimer = 0.0f;
    Ru[*cont].deathTimer = 0.0f;
    Ru[*cont].health = 100.0f;

    
    Ru[*cont].rec =(Rectangle){Ru[*cont].Ru_POSINICIAL_X, Ru[*cont].Ru_POSINICIAL_Y, Ru[*cont].Ru_DIM_X, Ru[*cont].Ru_DIM_Y}; 

    (*cont)++;

    return Ru;
}

void updateRu(Texture2D playerSpriteSheet, Texture2D inimigo1SpriteSheet, Texture2D inimigo2SpriteSheet, Texture2D inimigo3SpriteSheet, RU* Ru, int* cont, int SCREEN_WIDTH, bool collision){
    
    // initAnimations(playerSpriteSheet, inimigo1SpriteSheet, inimigo2SpriteSheet, inimigo3SpriteSheet);

    for(int i = 0; i < *cont; i++){
        
        Ru[i].Ru_POSINICIAL_X = RonaldoUmidadef2(Ru[i].Ru_POSINICIAL_X, Ru[i].speed);
        Ru[i].rec = (Rectangle){Ru[i].Ru_POSINICIAL_X, Ru[i].Ru_POSINICIAL_Y, Ru[i].Ru_DIM_X, Ru[i].Ru_DIM_Y};
        
            if (Ru[i].hit) {
                Ru[i].hitTimer = 0.2f; // Set the timer to the desired delay in seconds
                Ru[i].health -= 21.f;
                Ru[i].hit = false;
            }

            if (Ru[i].hitTimer > 0.0f && Ru[i].isAlive) {
                Ru[i].hitTimer -= GetFrameTime(); // Decrease the timer by the frame time
                DrawSpriteAnimationPro(inim1Anim_walkingLeft, Ru[i].rec, (Vector2){0,0}, 0, RED);
            } else if (Ru[i].health >= 0){
                // printf("%f\n", Ru[i].rec.x);
                DrawSpriteAnimationPro(inim1Anim_attackingLeft, Ru[i].rec, (Vector2){0,0}, 0, WHITE);
            }
            // printf("Heath: %f\n", Ru[i].health);



                    // If the enemy's health drops below 0, start the death animation
            if (Ru[i].health < 0 && Ru[i].isAlive) {
                Ru[i].isAlive = false;
                Ru[i].deathTimer = 1.4f; // Set the timer to the length of the death animation
            }

            // If the deathTimer is greater than 0, draw the death animation
            if (Ru[i].deathTimer > 0.0f && !Ru[i].isAlive) {
                printf("A\n");
                Ru[i].deathTimer -= GetFrameTime(); // Decrease the timer by the frame time
                DrawSpriteAnimationPro(inim1Anim_dyingLeft, Ru[i].rec, (Vector2){0,0}, 0, WHITE);
                
            }



    }
}


