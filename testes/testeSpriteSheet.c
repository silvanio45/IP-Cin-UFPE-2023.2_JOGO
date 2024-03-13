#include "raylib.h"
#include "movimentacao.h"
#include "entity.h"
#include <stdio.h>

void movx(Player *player, Platforms *platforms) {

    if ((IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) && (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) ) {player->rec.x += 0;}
    else if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
        // if (platforms[0].rec.x <) 
        if(!CheckCollisionRecs(player->rec, platforms->rec)){
            player->rec.x += player->speed;
        }
        else if(player->rec.y <= platforms[0].rec.y) {
            player->rec.x += player->speed;
        }

    }
    else if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
            
        if(!CheckCollisionRecs(player->rec, platforms->rec)){
            player->rec.x -= player->speed;
        }
        else if(player->rec.y <= platforms[0].rec.y) {
            player->rec.x -= player->speed;
        }
        int teste = CheckCollisionRecs(player->rec, platforms->rec);
        printf("%d\n", teste);
    }   
    
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

void pulo(Player *player, float gravidade, Platforms *platforms){
    
 // Jumping
        if (IsKeyDown(KEY_SPACE) && !player->isJumping)
        {
            player->isJumping = true;
            player->jumpSpeed = -6.0f; // Set the initial jump speed
        }

        // Apply gravity
        if (player->isJumping && CheckCollisionRecs(player->rec, platforms[0].rec)){

                if(player->rec.y <= platforms[0].rec.y) {
                    player->isJumping = false;
                }
                else {
                    player->jumpSpeed = 3.f;
                }
                // printf("AAA\n");
        }
        if (player->isJumping || !CheckCollisionRecs(player->rec, platforms[0].rec)) {
            player->jumpSpeed += gravidade * GetFrameTime();
            player->rec.y += player->jumpSpeed;
            // printf("%.2f\n", player->jumpSpeed);
        }

                // player->jumpSpeed += gravidade * GetFrameTime();
                // player->rec.y += player->jumpSpeed;

        // Check if player is on the ground
        if (player->rec.y >= GROUND_LEVEL)
        {
            player->rec.y = GROUND_LEVEL;
            player->isJumping = false;
        }

}


