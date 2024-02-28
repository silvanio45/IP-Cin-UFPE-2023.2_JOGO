#include "raylib.h"
#include <stdio.h>
#include "movimentacao.h"
#include <stdlib.h>
#include "projetil.h"

#define SCREEN_HEIGHT 540
#define SCREE_WIDTH 1280

int main() {
    InitWindow(SCREE_WIDTH, SCREEN_HEIGHT, "Tela Inicial");

    Texture2D boneco = LoadTexture("./resources/boneco3.png");
    Texture2D bulletTexture = LoadTexture("./resources/bullet2.png");
    Texture2D cenario = LoadTexture("./resources/cenario.png");
    Texture2D cenarioLog = LoadTexture("./resources/cenario0.png");
    Texture2D botaoStart = LoadTexture("./resources/botao2.png");

    Rectangle botaoinicio = { 300, 250, (SCREE_WIDTH - botaoStart.width) / 2, (SCREEN_HEIGHT - botaoStart.height + 20) / 2 };

    
    // Define the source rectangle for the texture
    Rectangle sourceRecBoneco = { 0, 0, boneco.width, boneco.height };

    // Define the source rectangle for the bullet
    Rectangle sourceRecBullet = {0, 0, bulletTexture.width, bulletTexture.height};


    int bulletCount = 0;
   

    float velY = 0;
    float jumpSpeed = 500.0f; // The initial upward speed when the player jumps

    float posx = 0 + boneco.width;
    float posy = 1100 + boneco.height;
    float gravidade = 2.8f;

    bool loading = false;
    bool isJumping = false; bool jump = true;

    // Set the target frames per second
    SetTargetFPS(60);

    // Add a new variable to keep track of the time since the last shot
    float timeSinceLastShot = 0.0f;
    // Define the delay between each shot (1.0f means one second)
    float shotDelay = 0.2f;

    while (!WindowShouldClose()) {

         timeSinceLastShot += GetFrameTime();
        if (!loading) {
            BeginDrawing();
            ClearBackground(WHITE);
            DrawTexture(cenarioLog, 0, 0, WHITE);
            DrawTexture(botaoStart, (SCREE_WIDTH - botaoinicio.x) / 2, (SCREEN_HEIGHT - botaoinicio.y + 50) / 2, WHITE);
            EndDrawing();

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
                CheckCollisionPointRec(GetMousePosition(), botaoinicio)) {
                loading = true;
            }
        } else {
            float delta = GetFrameTime();
            posx = movx(posx);
            posy = movy(posy, gravidade);

            

                if(IsKeyDown(KEY_Z)){
                    if(timeSinceLastShot >= shotDelay){
                        addBullet((Vector2) {posx+50, posy+(boneco.height-30)/2}, 15.f);
                        timeSinceLastShot = 0.0f;
                    }
                }





            if((IsKeyPressed(KEY_SPACE) && (posy >= ((SCREEN_HEIGHT - 140) - boneco.height))) || isJumping){
                isJumping = 1;
                velY = jumpSpeed; // Start the jump by setting the upward speed
                posy = pulo(posy, &velY, gravidade, boneco.height, delta, &isJumping, &jump);
            }   

            if (posy > (SCREEN_HEIGHT - 140) ) {
                posy = (SCREEN_HEIGHT - 140);
            }

            BeginDrawing();
            ClearBackground(WHITE);
            DrawTexture(cenario, 0, SCREEN_HEIGHT - cenario.height, WHITE);

            // Define the destination rectangle for the texture
            Rectangle destRec = { posx, posy, boneco.width, boneco.height };

            // Draw the texture as a rectangle
            DrawTextureRec(boneco, sourceRecBoneco, (Vector2){ destRec.x, destRec.y }, WHITE);
            
            
            updateBullets(bulletTexture, sourceRecBullet, SCREE_WIDTH, bulletList);
            EndDrawing();

           
        }
    }

    CloseWindow();
    UnloadTexture(boneco);
    UnloadTexture(cenario);
    UnloadTexture(bulletTexture);
    UnloadTexture(botaoStart);

    return 0;

        // Free all remaining bullets
    while (bulletList != NULL) {
        removeBullet(bulletList);
    }

}

