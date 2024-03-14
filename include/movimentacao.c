#include "raylib.h"
#include "movimentacao.h"
#include "entity.h"
#include <stdio.h>

void movx(Player *player, Platforms *platforms)
{

    if ((IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) && (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)))
    {
        player->rec.x += 0;
    }
    else if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
    {

        player->rec.x += player->speed;
    }
    else if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
        player->rec.x -= player->speed;

    if (player->rec.x < 0)
        player->rec.x = 0;
    if (player->rec.x > 1200)
        player->rec.x = 1200;

    // printf("x: %.2f, y: %.2f\n", player.rec.x, player.rec.y);

    // return posx;
}

float movy(float posy, float gravidade)
{
    if (posy < 0)
        posy = 0;
    if (posy > 600)
        posy = 600;
    posy = posy + gravidade;

    return posy;
}

void pulo(Player *player, float gravidade, Platforms *platforms, int platformsLength)
{
    // Jumping
    if (IsKeyDown(KEY_SPACE) && !player->isJumping){
        player->isJumping = true;
        player->jumpSpeed = -6.1f; // Set the initial jump speed
    }


  
    // Check for collision with platforms
    for (int i = 0; i < platformsLength; i++)
    {
            // Apply gravity if player is jumping or player is not on platform
        if (player->isJumping || (CheckCollisionRecs(player->rec, platforms[i].rec) && player->rec.y <= platforms[i].rec.y - player->rec.height + 10) || !CheckCollisionRecs(player->rec, platforms[i].rec)) {
            player->jumpSpeed += gravidade * GetFrameTime();
            player->rec.y += player->jumpSpeed;
            // printf("jumpSpeed: %.2f\n", player->jumpSpeed);
        }
        // printf("%d\n", (CheckCollisionRecs(player->rec, platforms[i].rec) && (player->rec.y <= platforms[i].rec.y - player->rec.height + 10) &&(player->rec.y + player->rec.height >= platforms[i].rec.y - 10)));
        
        
        if (CheckCollisionRecs(player->rec, platforms[i].rec))
        {
            // player below platform
            if (player->rec.y + player->rec.height > platforms[i].rec.y && player->rec.y < platforms[i].rec.y)
            {
                player->rec.y = platforms[i].rec.y - player->rec.height;
                player->isJumping = false;
                player->jumpSpeed = 0.0f;
            }
            // above platform
            else if (player->rec.y < platforms[i].rec.y + platforms[i].rec.height && player->rec.y + player->rec.height > platforms[i].rec.y + platforms[i].rec.height)
            {
                player->rec.y = platforms[i].rec.y + platforms[i].rec.height;
                player->jumpSpeed = 0.0f;
            }
            // colliding from the left
            else if (player->rec.x + player->rec.width > platforms[i].rec.x && player->rec.x < platforms[i].rec.x)
            {
                player->rec.x = platforms[i].rec.x - player->rec.width;
                player->jumpSpeed = 0.0f;
                
            }
            // colidding from the right
            else if (player->rec.x < platforms[i].rec.x + platforms[i].rec.width && player->rec.x + player->rec.width > platforms[i].rec.x + platforms[i].rec.width)
            {
                player->rec.x = platforms[i].rec.x + platforms[i].rec.width;
                player->jumpSpeed = 0.0f;

            }
        }
    }

    if(player->jumpSpeed > 0.2f) player->isPlayerFalling = true;
    else player->isPlayerFalling = false;

    // printf("isPlayerFalling: %d\n", player->isPlayerFalling);

    // Check if player is on the ground
    if (player->rec.y >= GROUND_LEVEL)
    {
        player->rec.y = GROUND_LEVEL;
        player->isJumping = false;
        player->jumpSpeed = 0.0f;
    }

    if (player->rec.y <= -50) player->rec.y = -50;

}

