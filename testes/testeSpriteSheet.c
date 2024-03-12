#include "raylib.h"
// #include "movimentacao.h"

#define CHARACTER_HEIGHT 40
#define CHARACTER_WIDTH 40

#define LEGS_HEIGHT 40
#define LEGS_WIDTH 40


Texture2D atlas;

#define CHARACTERC_COUNT 6
int characterIndex = 0;

void UpdateDrawFrame(void);

int main() {

    srand(time(0));

    InitWindow(1000, 400, "Tela Inicial");

    
    atlas = LoadTexture("./resources/base2.png");


    while(!WindowShouldClose()){
        WaitTime(0.1);
        UpdateDrawFrame();
    }

    CloseWindow();

    return 0;
}

void UpdateDrawFrame(void) {


    
    if (IsKeyDown(KEY_RIGHT)){
        characterIndex++;
        if(characterIndex >= CHARACTERC_COUNT) {
            characterIndex = 0;
        }
    }
    if (IsKeyDown(KEY_LEFT)){
        
        characterIndex--;
        if(characterIndex < CHARACTERC_COUNT) {
            characterIndex = 0;
        }
    }

    BeginDrawing();


        ClearBackground(RAYWHITE);

        // DrawTexture(atlas, 0, 0, WHITE);
        // DrawTextureV(atlas, (Vector2){0, 0}, WHITE);
        // DrawTextureEx(atlas, (Vector2){0, 0}, 0, 1.0f, WHITE);
        // DrawTextureRec(atlas, source, (Vector2){0, 0}, WHITE);

        // 30 x 40


        Rectangle source_legs = (Rectangle){LEGS_WIDTH * characterIndex, CHARACTER_HEIGHT,  LEGS_WIDTH, LEGS_HEIGHT};
        Rectangle dest_legs = (Rectangle){15, 45, source_legs.width*3, source_legs.height*3};

        DrawTexturePro(atlas, source_legs, dest_legs, (Vector2){0, 0}, 0, WHITE);

        Rectangle source_character = (Rectangle){CHARACTER_WIDTH * characterIndex, 0,  CHARACTER_WIDTH, CHARACTER_HEIGHT};
        Rectangle dest_character = (Rectangle){30, 0, source_character.width*3, source_character.height*3};

        DrawTexturePro(atlas, source_character, dest_character, (Vector2){0, 0}, 0, WHITE);

    EndDrawing();

} 