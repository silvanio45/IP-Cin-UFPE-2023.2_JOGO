#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
#define MAX_ENEMIES 10

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
Texture2D gameOver;

Rectangle botaoStartColis;
// Rectangle playerRect;

int numEnemies = 0;

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
bool endGame = false;
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

 Music Start; 

Color color = WHITE;

Music jogo_g1;

//Spawn points




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
    gameOver =               LoadTexture("./resources/miscellaneous/maxresdefault.png");

    color.a = 0.f;

    scrollingBack = 0.f;
    scrollingClouds = 0.f;

    Start = LoadMusicStream("resources/sound/abertura.mp3");
   
    PlayMusicStream(Start);

    jogo_g1 = LoadMusicStream("resources/sound/jogo_g1.mp3");

    //----------------------------------------------------------------------------------
    //  Animacoes
    //  Player
    player.direc = 1;
    player.isJumping = false;
    player.speed = 6.0f;
    player.health = 20;
    player.damage = 40;
    player.isAlive = true;
    player.deathTimer = 1.0f;
    

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
//spawn points:
// 1 - x: 1200, y: 400
// 2 - x: 0, y: 400
//spawn points:
Vector2 spawnPoints[] = {
    {1200, 400}, // 1
    {0, 400},    // 2
};

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
        
        
         // Choose a random spawn point
        int spawnIndex = GetRandomValue(0, sizeof(spawnPoints)/sizeof(spawnPoints[0]) - 1);
        Vector2 spawnPoint = spawnPoints[spawnIndex];

        if(numEnemies < MAX_ENEMIES){
            if(timeSinceLastRu >= RuDelay){ //Caranguejo
                Ru = addEnemy(Ru, &cont, inimigo1SpriteSheet, 0.3f, 80, spawnPoint.x, spawnPoint.y, 1.2f);
                timeSinceLastRu = 0.0f;
                numEnemies++;
            }
            else if(timeSinceLastCAC >= CACDelay){//Dengue
                CAC = addEnemy(CAC, &contCAC, inimigo1SpriteSheet, 0.3f, 80, spawnPoint.x, spawnPoint.y, 1.f);
                timeSinceLastCAC = 0.0f;
                numEnemies++;
            }
            else if(timeSinceLastCTG >= CTGDelay){//Estudante de Engenharia
                CTG = addEnemy(CTG, &contCTG, inimigo2SpriteSheet, 0.3f, 45, spawnPoint.x, spawnPoint.y, 0.4f);
                timeSinceLastCTG = 0.0f;
                numEnemies++;
            }
        }    


        if(IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) player.isPlayerLookingUp = true;
        else player.isPlayerLookingUp = false;

       pulo(&player, gravidade, platforms, 2);


        if(IsKeyDown(KEY_X)){
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
    // player.isAlive = false;
    // Desenho
    if (menu_open)
    {
        
        BeginDrawing();
            ClearBackground(WHITE);
            DrawTexture(cenarioLog, 0, 0, WHITE);
            DrawTexture(botaoStart, BOTAOINICIAL_POS_X, BOTAOINICIAL_POS_Y, WHITE);
        EndDrawing();
    }
    else if (!endGame && !menu_open){
        // scrollingBack += 0.1f;
        // if (scrollingBack <= -skyBackground.width*2) scrollingBack = 0;
        StopMusicStream(Start);
        PlayMusicStream(jogo_g1);
        // UpdateMusicStream(Start);
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
            
            


            collisionRU = updateProjectils(bulletTexture, sourceRecBullet, SCREEN_WIDTH, Ru, &cont, player.isPlayerLookingUp, platforms, player);    
            
            collisionCAC = updateProjectils(bulletTexture, sourceRecBullet, SCREEN_WIDTH, CAC, &contCAC, player.isPlayerLookingUp, platforms , player);

            collisionCTG = updateProjectils(bulletTexture, sourceRecBullet, SCREEN_WIDTH, CTG, &contCTG, player.isPlayerLookingUp, platforms , player);

            updateEnemy(1, Ru, &cont, SCREEN_WIDTH, &Ru->direct, player.rec.x, bulletTexture, &GunRU, &contGunRU, collisionRU, &player);
            updateEnemy(2, CAC, &contCAC, SCREEN_WIDTH, &CAC->direct, player.rec.x, bulletTexture, &GunCAC, &contGunCAC, collisionCAC, &player);
            updateEnemy(3, CTG, &contCTG, SCREEN_WIDTH, &CTG->direct, player.rec.x, bulletTexture, &GunCTG, &contGunCTG, collisionCTG, &player);

            if(player.deathTimer >= 0.0f || player.isAlive) playerAnimation(player.direc, player.rec, &player);
            
            // if(player.deathTimer <= 0.0f && !player.isAlive) {
            //     color.a += 5.f;
            //     if (color.a >= 255) {color.a = 255; endGame = true;}
            //     DrawTexture(gameOver, 0, -140, color);
                
            // }

            printf("x = %.2f, y = %.2f\n", player.rec.x, player.rec.y);

        EndDrawing();
    } 

    // while (bulletList != NULL) {
    //     removeBullet(bulletList);
    // }



}void playMusicAndSoundEffects() {
    Music Start = LoadMusicStream("resources/sound/abertura.mp3");
   
    PlayMusicStream(Start);

     Music jogo_g1 = LoadMusicStream("resources/sound/jogo_g1.mp3");
    // Lembre-se de atualizar a música no loop principal do jogo
    // UpdateMusicStream(music);
}

