#include "raylib.h"
#include "movimentacao.h"

int main() {
    InitWindow(1280, 720, "Tela Inicial");

    Texture2D boneco = LoadTexture("./boneco3.png");
    Texture2D cenario = LoadTexture("./cenario2.png");
    Texture2D cenarioLog = LoadTexture("./cenario0.png");
    Texture2D botaoStart = LoadTexture("./botao2.png");

    Rectangle botaoinicio = { 300, 250, (1280 - botaoStart.width) / 2, (720 - botaoStart.height + 50) / 2 };

    float posx = 0 + boneco.width;
    float posy = 0 + boneco.height;
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

            posx = movx(posx);
            posy = movy(posy, gravidade);
            posy = pulo(posy, gravidade);

            BeginDrawing();
            ClearBackground(WHITE);
            DrawTexture(cenario, 0, 0, WHITE);
            DrawTexture(boneco, posx, posy, WHITE);
       
            EndDrawing();
        }
    }

    CloseWindow();
    UnloadTexture(boneco);
    UnloadTexture(cenario);
    UnloadTexture(botaoStart);

    return 0;
}
