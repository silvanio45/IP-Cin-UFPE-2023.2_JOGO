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

#define MAX_STAMINA 100                // Stamina máxima do jogador
#define STAMINA_DECREASE_AMOUNT 5     // Quantidade de stamina a ser consumida ao pressionar 'Z'

const double STAMINA_REGEN_INTERVAL = 5.0; // Intervalo de tempo para regeneração da stamina (em segundos)


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
Texture2D skyBackground;
Texture2D clouds;
Texture2D clouds1;

Rectangle botaoStartColis;
// Rectangle playerRect;

Rectangle sourceRecBullet;
Texture2D bulletTexture;
// Bullet* bulletList = NULL; // Start with an empty list


// float velY = 0;
float jumpSpeed = 2.0f;
float gravidade = 5.f;
// int player.direc = 1;

bool menu_open = true;
// bool player.isJumping = false; 
bool jump = true;


// Add a new variable to keep track of the time since the last shot
float timeSinceLastShot = 0.8f;
float bulletSpeed;
// Define the delay between each shot (1.0f means one second)
float shotDelay = 0.4f; 

int TRU = 0; 

Player player;

int cont = 0;
int contCAC = 0;
int contCTG = 0;
int contGunRU = 0;
int contGunCTG = 0;
int contGunCAC = 0;

// Gun gun;
gun* GunRU = NULL;
gun* GunCAC = NULL;
gun* GunCTG = NULL;

Enemy* Ru = NULL;
Enemy* CAC = NULL;
Enemy* CTG = NULL;

float timeSinceLastRu = 0.0f;
float timeSinceLastCAC = 0.0f;
float timeSinceLastCTG = 0.0f;
float zumbiPosX = 300; 
float  hitTimer = 0.0f;
float RuDelay = 0.4f;
float CACDelay = 0.4f;
float CTGDelay = 0.4f;

float scrollingBack;
float scrollingClouds;
float scrollingClouds1;
//objetos do cenario

int playerStamina = MAX_STAMINA;
double lastRegenTime;

Platforms platforms[] = {
    {{220, 300, 200, 60}, 1},
    {{900, 204, 400, 60}, 1}
};

//----------------------------------------------------------------------------------
// Declaração de Funções Locais
//----------------------------------------------------------------------------------
bool collisionRU, collisionCAC, collisionCTG;
static void UpdateDrawFrame(void);

//----------------------------------------------------------------------------------
// Ponto de Entrada Principal
//----------------------------------------------------------------------------------

int main()
{
    
    // Inicialização
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Tela Inicial");

    playerSpriteSheet =     LoadTexture("./resources/player/Personagem_SpriteSheet.png");
    inimigo1SpriteSheet =   LoadTexture("resources/enemys/Inimigo1_SpriteSheet.png");
    inimigo2SpriteSheet =   LoadTexture("resources/enemys/Inimigo2_SpriteSheet.png");
    inimigo3SpriteSheet =   LoadTexture("resources/enemys/Inimigo3_SpriteSheet.png");
    bulletTexture =         LoadTexture("./resources/miscellaneous/bullet2.png");
    botaoStart =            LoadTexture("./resources/miscellaneous/botao2.png");
    cenario =               LoadTexture("./resources/scenario/front_scenario.png");
    cenarioLog =            LoadTexture("./resources/scenario/cenarioLogMetal.png");
    skyBackground =         LoadTexture("./resources/scenario/skyBackground.png");
    clouds =                LoadTexture("./resources/scenario/clouds1.png");
    clouds1 =               LoadTexture("./resources/scenario/clouds2.png");


    scrollingBack = 0.f;
    scrollingClouds = 0.f;

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

        lastRegenTime = GetTime(); // Inicializa lastRegenTime fora do contexto constante


        // Loop principal do jogo
        while (!WindowShouldClose())
        {
            // Atualização do jogo
        if (IsKeyDown(KEY_F) && playerStamina >= STAMINA_DECREASE_AMOUNT) {
            if(playerStamina >= STAMINA_DECREASE_AMOUNT){
            playerStamina -= STAMINA_DECREASE_AMOUNT;}
            else if (playerStamina >= STAMINA_DECREASE_AMOUNT){
            playerStamina=0;}
        }

        double currentTime = GetTime(); // Tempo atual do jogo

        // Verifica se passaram 5 segundos desde a última regeneração de stamina
        if (currentTime - lastRegenTime >= STAMINA_REGEN_INTERVAL) {
            if (playerStamina < MAX_STAMINA) {
                playerStamina += 10; // Regenera 1 ponto de stamina
                if (playerStamina > MAX_STAMINA) {
                    playerStamina = MAX_STAMINA;
                }
            }
            lastRegenTime = currentTime; // Atualiza o tempo da última regeneração
        }
            timeSinceLastShot += GetFrameTime();
            timeSinceLastRu += GetFrameTime();
            timeSinceLastCAC += GetFrameTime();
            timeSinceLastCTG += GetFrameTime();
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
                Ru = addEnemy(Ru, &cont, inimigo1SpriteSheet);
                timeSinceLastRu = 0.0f;
            }
        }
        if(IsKeyDown(KEY_K)){
            if(timeSinceLastCAC >= CACDelay){
                CAC = addEnemy(CAC, &contCAC, inimigo1SpriteSheet);
                timeSinceLastCAC = 0.0f;
            }
        }
        if(IsKeyDown(KEY_L)){
            if(timeSinceLastCTG >= CTGDelay){
                CTG = addEnemy(CTG, &contCTG, inimigo2SpriteSheet);
                timeSinceLastCTG = 0.0f;
            }
        }
        
        if(IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) player.isPlayerLookingUp = true;
        else player.isPlayerLookingUp = false;

       pulo(&player, gravidade, platforms, 2);


        if(IsKeyDown(KEY_F)){
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
        // scrollingBack += 0.1f;
        // if (scrollingBack <= -skyBackground.width*2) scrollingBack = 0;
        
        BeginDrawing();
            ClearBackground(WHITE);

            scrollingBack -= 0.08f;
            if (scrollingBack <= -skyBackground.width*1.5) scrollingBack = 0;

            scrollingClouds -= 0.2f;
            if (scrollingClouds <= -clouds.width) scrollingClouds = 0;

            scrollingClouds1 -= 0.35f;
            if (scrollingClouds1 <= -clouds1.width) scrollingClouds1 = 0;


            DrawTextureEx(skyBackground, (Vector2){ scrollingBack, -270}, 0.0f, 1.5f, WHITE);
            DrawTextureEx(skyBackground, (Vector2){ skyBackground.width*1.5 + scrollingBack, -270 }, 0.0f, 1.5f, WHITE);


            DrawTextureEx(clouds, (Vector2){ scrollingClouds, 0}, 0.0f, 1.0f, WHITE);
            DrawTextureEx(clouds, (Vector2){ clouds.width*1 + scrollingClouds, 0 }, 0.0f, 1.0f, WHITE);

            DrawTextureEx(clouds1, (Vector2){ scrollingClouds1, 0}, 0.0f, 1.0f, WHITE);
            DrawTextureEx(clouds1, (Vector2){ clouds1.width*1 + scrollingClouds1, 0 }, 0.0f, 1.0f, WHITE);

            DrawTexture(cenario, 0, 0, WHITE);
            
            DrawText(TextFormat("Stamina: %d", playerStamina), 10, 40, 20, DARKGRAY);


            collisionRU = updateProjectils(bulletTexture, sourceRecBullet, SCREEN_WIDTH, Ru, &cont, player.isPlayerLookingUp, platforms);    
            
            collisionCAC = updateProjectils(bulletTexture, sourceRecBullet, SCREEN_WIDTH, CAC, &contCAC, player.isPlayerLookingUp, platforms);

            collisionCTG = updateProjectils(bulletTexture, sourceRecBullet, SCREEN_WIDTH, CTG, &contCTG, player.isPlayerLookingUp, platforms);

            updateEnemy(1, Ru, &cont, SCREEN_WIDTH, &Ru->direct, player.rec.x, bulletTexture, &GunRU, &contGunRU, collisionRU);
            updateEnemy(2, CAC, &contCAC, SCREEN_WIDTH, &CAC->direct, player.rec.x, bulletTexture, &GunCAC, &contGunCAC, collisionCAC);
            updateEnemy(3, CTG, &contCTG, SCREEN_WIDTH, &CTG->direct, player.rec.x, bulletTexture, &GunCTG, &contGunCTG, collisionCTG);

            playerAnimation(player.direc, player.rec, player);
            
        EndDrawing();
    }

    // while (bulletList != NULL) {
    //     removeBullet(bulletList);
    // }



}