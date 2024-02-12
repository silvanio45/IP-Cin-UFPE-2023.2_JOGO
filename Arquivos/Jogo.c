#include "raylib.h"
#include "movimentacao.h"

int main() {
    InitWindow(1280, 720, "Tela Inicial");

    Texture2D boneco = LoadTexture("./boneco1.png");
    Texture2D cenario = LoadTexture("./cenario1.png");
    Texture2D botaoStart = LoadTexture("./botao2.png");

    Rectangle botaoinicio = { 300, 250, botaoStart.width, botaoStart.height };

    float posx = 0;
    float posy = 720 - boneco.height;
    float gravidade = 0.4;

    bool loading = false;

    while (!WindowShouldClose()) {
        if (!loading) {
            BeginDrawing();
            ClearBackground(WHITE);
            DrawText("CInvire", 20, 60, 30, BLUE);
            DrawTexture(botaoStart, botaoinicio.x, botaoinicio.y, WHITE);
            EndDrawing();

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
                CheckCollisionPointRec(GetMousePosition(), botaoinicio)) {
                loading = true;
            }
        } else {
            posx = movx(posx);
            posy = movy(posy, gravidade);

            BeginDrawing();
            ClearBackground(WHITE);
            DrawText("CInvire", 20, 60, 30, BLUE);
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
