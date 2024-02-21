#include "raylib.h"
#include "movimentacao.h"

int main() {
    InitWindow(1280, 720, "Tela Inicial");

    Texture2D boneco = LoadTexture("./resources/boneco3.png");
    Texture2D cenario = LoadTexture("./resources/cenario2.png");
    Texture2D cenarioLog = LoadTexture("./resources/cenario0.png");
    Texture2D botaoStart = LoadTexture("./resources/botao2.png");

    Rectangle botaoinicio = { 300, 250, (1280 - botaoStart.width) / 2, (720 - botaoStart.height + 50) / 2 };

    // Define a rectangle for the character
    Rectangle bonecoRec = { 0 + boneco.width, 1100 + boneco.height, boneco.width, boneco.height };
    float gravidade = 0.4;

    bool loading = false;

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

            bonecoRec.x = movx(bonecoRec.x);
            bonecoRec.y = movy(bonecoRec.y, gravidade);
            bonecoRec.y = pulo(bonecoRec.y, gravidade);

            BeginDrawing();
            ClearBackground(WHITE);
            DrawTexture(cenario, 0, 0, WHITE);
            DrawTextureRec(boneco, (Rectangle){ 0, 0, boneco.width, boneco.height }, (Vector2){ bonecoRec.x, bonecoRec.y }, WHITE);
       
            EndDrawing();
        }
    }

    CloseWindow();
    UnloadTexture(boneco);
    UnloadTexture(cenario);
    UnloadTexture(botaoStart);

    return 0;
}

