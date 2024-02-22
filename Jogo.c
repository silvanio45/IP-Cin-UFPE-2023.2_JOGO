#include "raylib.h"
#include <stdio.h>
#include "movimentacao.h"

int main() {
    InitWindow(1280, 720, "Tela Inicial");

    Texture2D boneco = LoadTexture("./resources/boneco3.png");
    Texture2D cenario = LoadTexture("./resources/cenario2.png");
    Texture2D cenarioLog = LoadTexture("./resources/cenario0.png");
    Texture2D botaoStart = LoadTexture("./resources/botao2.png");

    Rectangle botaoinicio = { 300, 250, (1280 - botaoStart.width) / 2, (720 - botaoStart.height + 50) / 2 };

    // Define the source rectangle for the texture
    Rectangle sourceRec = { 0, 0, boneco.width, boneco.height };

    float velY = 0;
    float jumpSpeed = 200.0f; // The initial upward speed when the player jumps

    float posx = 0 + boneco.width;
    float posy = 1100 + boneco.height;
    float gravidade = 2.8f;

    bool loading = false;
    bool isJumping = false; bool jump = true;

    // Set the target frames per second
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        if (!loading) {
            BeginDrawing();
            ClearBackground(WHITE);
            DrawTexture(cenarioLog, 0, 0, WHITE);
            DrawTexture(botaoStart, (1280 - botaoinicio.x) / 2, (720 - botaoinicio.y + 50) / 2, WHITE);
            EndDrawing();

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
                CheckCollisionPointRec(GetMousePosition(), botaoinicio)) {
                loading = true;
            }
        } else {
            float delta = GetFrameTime();
            posx = movx(posx);
            posy = movy(posy, gravidade);

            
            if((IsKeyPressed(KEY_SPACE) && (posy >= (600 - boneco.height))) || isJumping){
                isJumping = 1;
                velY = jumpSpeed; // Start the jump by setting the upward speed
                posy = pulo(posy, &velY, gravidade, boneco.height, delta, &isJumping, &jump);
            }   

            printf("%d", isJumping);

            if (posy > 600 ) {
                posy = 600;
            }

            BeginDrawing();
            ClearBackground(WHITE);
            DrawTexture(cenario, 0, 0, WHITE);

            // Define the destination rectangle for the texture
            Rectangle destRec = { posx, posy, boneco.width, boneco.height };

            // Draw the texture as a rectangle
            DrawTextureRec(boneco, sourceRec, (Vector2){ destRec.x, destRec.y }, WHITE);
       
            EndDrawing();
        }
    }

    CloseWindow();
    UnloadTexture(boneco);
    UnloadTexture(cenario);
    UnloadTexture(botaoStart);

    return 0;
}
