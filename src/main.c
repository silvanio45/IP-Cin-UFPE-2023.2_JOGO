#include <stdio.h>

#include "raylib.h"

#include "../include/movimentacao.h"
#include "../include/animacao.h"


#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif


//----------------------------------------------------------------------------------
// Variáveis Locais (local para este módulo)
//----------------------------------------------------------------------------------

Texture2D playerSpriteSheet;
Texture2D inimigo2SpriteSheet;
Texture2D inimigo3SpriteSheet;
Texture2D inimigo1SpriteSheet;
Texture2D cenario;
Texture2D cenarioLog;
Texture2D botaoStart;

Rectangle botaoStartColis;
Rectangle playerRect;


float velY = 0;
float jumpSpeed = 200.0f;
float gravidade = 2.8f;
int playerDirec;

bool menu_open = true;
bool isJumping = false; 
bool jump = true;

//----------------------------------------------------------------------------------
// Declaração de Funções Locais
//----------------------------------------------------------------------------------

static void UpdateDrawFrame(void);

//----------------------------------------------------------------------------------
// Ponto de Entrada Principal
//----------------------------------------------------------------------------------

int main()
{
    // Inicialização
    InitWindow(1280, 720, "Tela Inicial");

    playerSpriteSheet = LoadTexture("./resources/Personagem_SpriteSheet.png");
    inimigo1SpriteSheet = LoadTexture("resources/Inimigo1_SpriteSheet.png");
    inimigo2SpriteSheet = LoadTexture("resources/Inimigo2_SpriteSheet.png");
    inimigo3SpriteSheet = LoadTexture("resources/Inimigo3_SpriteSheet.png");
    cenario = LoadTexture("./resources/cenario2.png");
    cenarioLog = LoadTexture("./resources/cenario0.png");
    botaoStart = LoadTexture("./resources/botao2.png");

    botaoStartColis = (Rectangle){ BOTAOINICIAL_POS_X, BOTAOINICIAL_POS_Y, botaoStart.width, botaoStart.height };
    playerRect = (Rectangle){PLAYER_POSINICIAL_X, PLAYER_POSINICIAL_Y, PLAYER_DIM_X, PLAYER_DIM_Y};

    //----------------------------------------------------------------------------------
    //  Animacoes
    //  Player

    initAnimations(playerSpriteSheet, inimigo1SpriteSheet, inimigo2SpriteSheet, inimigo3SpriteSheet);

    #if defined(PLATFORM_WEB)
        emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
    #else
        SetTargetFPS(60);
        // Loop principal do jogo
        while (!WindowShouldClose())
        {
            UpdateDrawFrame();
        }
    #endif

    // Desinicialização
    CloseWindow();
    UnloadTexture(playerSpriteSheet);
    UnloadTexture(cenario);
    UnloadTexture(botaoStart);
    UnloadTexture(cenarioLog);
    DisposeSpriteAnimation(playerAnim_idleLeft);
    DisposeSpriteAnimation(playerAnim_idleRight);
    DisposeSpriteAnimation(playerAnim_walkingLeft);
    DisposeSpriteAnimation(playerAnim_walkingRight);

    return 0;
}

// Atualiza e desenha um frame do jogo
static void UpdateDrawFrame(void)
{
    // Atualização
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), botaoStartColis)) menu_open = false;
    else
    {
        playerRect.x = movx(playerRect.x);
        playerRect.y = movy(playerRect.y, gravidade);

        if(IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) playerDirec = -1;
        if(IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) playerDirec = 1;

        if((IsKeyPressed(KEY_SPACE) && (playerRect.y >= (600 - playerRect.height))) || isJumping){
            isJumping = true;
            velY = jumpSpeed;
            playerRect.y = pulo(playerRect.y, &velY, gravidade, playerRect.height, GetFrameTime(), &isJumping, &jump);
        }   

        if (playerRect.y > 600 ) playerRect.y = 600;
    }

    // Desenho
    if (menu_open)
    {
        BeginDrawing();
            ClearBackground(WHITE);
            DrawTexture(cenarioLog, 0, 0, WHITE);
            DrawTexture(botaoStart, BOTAOINICIAL_POS_X, BOTAOINICIAL_POS_Y, WHITE);
        EndDrawing();
    }
    else
    {
        BeginDrawing();
            ClearBackground(WHITE);
            DrawTexture(cenario, 0, 0, WHITE);
            playerAnimation(playerDirec, playerRect);
        EndDrawing();
    }
}