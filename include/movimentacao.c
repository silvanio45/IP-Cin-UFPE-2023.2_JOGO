#include "raylib.h"
#include "movimentacao.h"
#include "entity.h"
#include <stdio.h>

void movx(Player *player, Platforms *platforms) {

    if ((IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) && (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) ) {player->rec.x += 0;}
    else if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
      
        player->rec.x += player->speed;

    }
    else if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) player->rec.x -= player->speed;
    
    if (player->rec.x < 0) player->rec.x = 0;
    if (player->rec.x > 1200) player->rec.x = 1200;

    // printf("x: %.2f, y: %.2f\n", player.rec.x, player.rec.y);

    // return posx;
}


float movy(float posy, float gravidade) {
    if (posy < 0) posy = 0;
    if (posy > 600) posy = 600;
    posy = posy + gravidade;

    return posy;
}

void pulo(Player *player, float gravidade, Platforms *platforms, int platformsLenght){
    
    // Jumping
    if (IsKeyDown(KEY_SPACE) && !player->isJumping)
    {
        player->isJumping = true;
        player->jumpSpeed = -6.0f; // Set the initial jump speed
    }

    // int platformsLenght = sizeof(platforms)/sizeof(platforms[0]);

    // Apply gravity
        if (player->isJumping && CheckCollisionRecs(player->rec, platforms[0].rec)){
            
            if(player->rec.y > 200) {
                player->isJumping = false;
                player->jumpSpeed = 0.0f;
                printf("%.2f %.2f\n", player->rec.x, player->rec.y);
            }
            else {
                player->jumpSpeed = 3.f;
            }
        }
        if (player->isJumping || !CheckCollisionRecs(player->rec, platforms[0].rec)) {
            player->jumpSpeed += gravidade * GetFrameTime();
            player->rec.y += player->jumpSpeed;
        }

        // Check if player is on the ground
        if (player->rec.y >= GROUND_LEVEL)
        {
            player->rec.y = GROUND_LEVEL;
            player->isJumping = false;
        }

        // Check for side collisions
        // if (CheckCollisionRecs(player->rec, platforms[0].rec) && (player->rec.y > 200) && !player->isJumping){
        
        //     if(player->rec.x <= platforms[0].rec.x) {
        //         player->rec.x = platforms[0].rec.x - player->rec.width;
        //         // printf("%.2f %.2f\n", player->rec.x, platforms[0].rec.x);
        //     }
        //     else if(player->rec.x <= platforms[0].rec.x + platforms[0].rec.width) {
        //         player->rec.x = platforms[0].rec.x + platforms[0].rec.width;
        //         // printf("AAAAAAAA %.2f\n", platforms[0].rec.x + platforms[0].rec.width);

        //     }
        // }
}
