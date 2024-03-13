#include <stdio.h>
#include <stdlib.h>

#include "raylib.h"

#include "../include/movimentacao.h"
#include "../include/animacao.h"
#include "../include/projetil.h"
#include "../include/inimigos.h"
#include "../include/entity.h"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif


//----------------------------------------------------------------------------------
// Variáveis Locais (local para este módulo)
//----------------------------------------------------------------------------------

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 540


Texture2D playerSpriteSheet;
Texture2D inimigo2SpriteSheet;
Texture2D inimigo3SpriteSheet;
Texture2D inimigo1SpriteSheet;
Texture2D RonaldoUmidade;
Texture2D ruTexture;
Texture2D cenario;
Texture2D cenarioLog;
Texture2D botaoStart;

Rectangle botaoStartColis;
// Rectangle playerRect;

Rectangle sourceRecBullet;
Texture2D bulletTexture;
// Bullet* bulletList = NULL; // Start with an empty list

int cont = 0;

// float velY = 0;
float jumpSpeed = 2.0f;
float gravidade = 5.f;
// int player.direc = 1;

bool menu_open = true;
// bool player.isJumping = false; 
bool jump = true;

float timeSinceLastRu = 0.0f; // Adicione esta linha
float ruDelay = 1.0f; // Adicione esta linha

// Add a new variable to keep track of the time since the last shot
float timeSinceLastShot = 0.8f;
float bulletSpeed;
// Define the delay between each shot (1.0f means one second)
float shotDelay = 0.4f; 
float RuDelay = 0.4f;

int TRU = 0; 

Player player;
RU* Ru = NULL;


//objetos do cenario

Platforms platforms[] = {
    {{220, 300, 200, 60}, 1},
    {{900, 204, 400, 60}, 1}
};

//----------------------------------------------------------------------------------
// Declaração de Funções Locais
//----------------------------------------------------------------------------------
bool collision;
static void UpdateDrawFrame(void);

//----------------------------------------------------------------------------------
// Ponto de Entrada Principal
//----------------------------------------------------------------------------------

int main()
{
    
    // Inicialização
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Tela Inicial");

    playerSpriteSheet =     LoadTexture("./resources/Personagem_SpriteSheet.png");
    inimigo1SpriteSheet =   LoadTexture("resources/Inimigo1_SpriteSheet.png");
    inimigo2SpriteSheet =   LoadTexture("resources/Inimigo2_SpriteSheet.png");
    inimigo3SpriteSheet =   LoadTexture("resources/Inimigo3_SpriteSheet.png");
    bulletTexture =         LoadTexture("./resources/bullet2.png");
    cenario =               LoadTexture("./resources/cenario4.png");
    cenarioLog =            LoadTexture("./resources/cenarioLogMetal.png");
    botaoStart =            LoadTexture("./resources/botao2.png");




    //----------------------------------------------------------------------------------
    //  Animacoes
    //  Player
    player.direc = 1;
    player.isJumping = false;
    player.speed = 6.0f;
    

    botaoStartColis = (Rectangle){ BOTAOINICIAL_POS_X, BOTAOINICIAL_POS_Y, botaoStart.width, botaoStart.height };
    player.rec = (Rectangle){SCREEN_WIDTH/2, SCREEN_HEIGHT-PLAYER_DIM_Y - 40, PLAYER_DIM_X, PLAYER_DIM_Y};
    //Ru.rec =(Rectangle){Ru.Ru_POSINICIAL_X, Ru.Ru_POSINICIAL_Y, Ru.Ru_DIM_X, Ru.Ru_DIM_Y}; 

    initAnimations(playerSpriteSheet, inimigo1SpriteSheet, inimigo2SpriteSheet, inimigo3SpriteSheet);

    // Define the source rectangle for the bullet
    sourceRecBullet = (Rectangle) {0, 0, bulletTexture.width, bulletTexture.height};

    #if defined(PLATFORM_WEB)
        emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
    #else
        SetTargetFPS(60);



        // Loop principal do jogo
        while (!WindowShouldClose())
        {
            timeSinceLastShot += GetFrameTime();
            timeSinceLastRu += GetFrameTime();
            UpdateDrawFrame();
        }
    #endif

    // Desinicialização
    CloseWindow();
    UnloadTexture(playerSpriteSheet);
    UnloadTexture(cenario);
    UnloadTexture(botaoStart);
    UnloadTexture(cenarioLog);
    UnloadTexture(bulletTexture);
    UnloadTexture(RonaldoUmidade);
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
        
        // player.rec.x = movx(player.rec.x, player.speed, platforms, player);
        movx(&player, platforms);
        

        if(IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) player.direc = -1;
        if(IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) player.direc = 1;

        if (player.rec.y > 600 ) player.rec.y = 600;
        
        if(IsKeyDown(KEY_J)){
            if(timeSinceLastRu >= RuDelay){
                Ru = addRu(Ru, &cont, playerSpriteSheet, inimigo1SpriteSheet, inimigo2SpriteSheet, inimigo3SpriteSheet);
                timeSinceLastRu = 0.0f;
            }
        }
        
        if(IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) player.isPlayerLookingUp = true;
        else player.isPlayerLookingUp = false;

       pulo(&player, gravidade, platforms, 2);


        if(IsKeyDown(KEY_K)){
            if (player.isPlayerLookingUp) {
                    shotDelay = 0.6f;
                }
            else {
                    shotDelay = 0.4f;
                }
            if(timeSinceLastShot >= shotDelay){
                addProjectil(player.rec, 12.f, player.direc, player.isPlayerLookingUp);
                timeSinceLastShot = 0.0f;
            }
        }
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
            
            // printf("%f %f\n", player.rec.x, player.rec.y);
            DrawTexture(cenario, 0, 0, WHITE);
            // DrawRectangleRec(platforms[0].rec, BLACK);
            // DrawRectangleRec(platforms[1].rec, BLACK);
            collision = updateProjectils(bulletTexture, sourceRecBullet, SCREEN_WIDTH, Ru, &cont, player.isPlayerLookingUp, platforms);    
            updateRu(playerSpriteSheet, inimigo1SpriteSheet, inimigo2SpriteSheet, inimigo3SpriteSheet, Ru, &cont, SCREEN_WIDTH, collision);
            playerAnimation(player.direc, player.rec, player);
            //DrawTexture(RonaldoUmidade, Ru.rec.x, Ru.rec.y, WHITE);

            
            
        EndDrawing();
    }

    // while (bulletList != NULL) {
    //     removeBullet(bulletList);
    // }



}
