#include <stdio.h>
#include <stdlib.h>

#include "raylib.h"

#include "../include/movimentacao.h"
#include "../include/animacao.h"
#include "../include/projetil.h"
#include "../include/entity.h"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif


//----------------------------------------------------------------------------------
// Variáveis Locais (local para este módulo)
//----------------------------------------------------------------------------------

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

Texture2D playerSpriteSheet;
Texture2D inimigo2SpriteSheet;
Texture2D inimigo3SpriteSheet;
Texture2D inimigo1SpriteSheet;
Texture2D cenario;
Texture2D cenarioLog;
Texture2D botaoStart;

Rectangle botaoStartColis;
// Rectangle playerRect;

Rectangle sourceRecBullet;
Texture2D bulletTexture;
// Bullet* bulletList = NULL; // Start with an empty list

bool collision;

// float velY = 0;
float jumpSpeed = 200.0f;
float gravidade = 5.f;
// int player.direc = 1;

bool menu_open = true;
// bool player.isJumping = false; 
bool jump = true;

// Add a new variable to keep track of the time since the last shot
// float timeSinceLastShot = 0.8f;
// float bulletSpeed;
// Define the delay between each shot (1.0f means one second)
// float shotDelay = 0.4f; 


Player player;
Player enemy;
Gun gun;

float zumbiPosX = 300; 
float  hitTimer = 0.0f;
//----------------------------------------------------------------------------------
// Declaração de Funções Locais
//----------------------------------------------------------------------------------

static void UpdateDrawFrame(void);

//----------------------------------------------------------------------------------
// Ponto de Entrada Principal
//----------------------------------------------------------------------------------

// Rectangle enemy;

int main()
{
    // Inicialização
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Tela Inicial");

    playerSpriteSheet =     LoadTexture("./resources/Personagem_SpriteSheet.png");
    inimigo1SpriteSheet =   LoadTexture("resources/Inimigo1_SpriteSheet.png");
    inimigo2SpriteSheet =   LoadTexture("resources/Inimigo2_SpriteSheet.png");
    inimigo3SpriteSheet =   LoadTexture("resources/Inimigo3_SpriteSheet.png");
    bulletTexture =         LoadTexture("./resources/bullet2.png");
    cenario =               LoadTexture("./resources/cenario3.png");
    cenarioLog =            LoadTexture("./resources/cenarioLogMetal.png");
    botaoStart =            LoadTexture("./resources/botao2.png");

    botaoStartColis = (Rectangle){ BOTAOINICIAL_POS_X, BOTAOINICIAL_POS_Y, botaoStart.width, botaoStart.height };
    player.rec = (Rectangle){PLAYER_POSINICIAL_X, PLAYER_POSINICIAL_Y, PLAYER_DIM_X, PLAYER_DIM_Y};
    
    enemy.rec = (Rectangle){PLAYER_POSINICIAL_X + 600, PLAYER_POSINICIAL_Y, PLAYER_DIM_X, PLAYER_DIM_Y};
    

    //----------------------------------------------------------------------------------
    //  Animacoes

    //gun
    gun.damage = 21;
    gun.shotDelay = 0.4f;
    gun.timeSinceLastShot = 0.8f;
    gun.bulletSpeed = 12.f;

    //  Player
    player.direc = 1;
    player.isJumping = false;
    player.speed = 6.0f;
    player.health = 100.f;

    //enemy teste
    enemy.direc = 1;
    enemy.isJumping = false;
    enemy.speed = 6.0f;
    enemy.health = 100.f;
    enemy.deathTimer = 0.0f;
    enemy.hitTimer = 0.0f;
    enemy.isAlive = true;


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
            gun.timeSinceLastShot += GetFrameTime();
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
        player.rec.x = movx(player.rec.x, player.speed);
        // player.rec.y = movy(player.rec.y, gravidade);

        if(IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) player.direc = -1;
        if(IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) player.direc = 1;

        // if((IsKeyPressed(KEY_SPACE) && (player.rec.y >= (600 - player.rec.height))) || player.isJumping){
        //     player.isJumping = true;
        //     player.rec.y = pulo(player.rec.y, &jumpSpeed, gravidade, player.rec.height, GetFrameTime(), &player.isJumping, &jump);
        // }   

        if (player.rec.y > 600 ) player.rec.y = 600;
        
        if(IsKeyDown(KEY_Z)){
                    if(gun.timeSinceLastShot >= gun.shotDelay){
                        addBullet(player.rec, gun.bulletSpeed, player.direc);
                        gun.timeSinceLastShot = 0.0f;
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
            collision = updateBullets(bulletTexture, sourceRecBullet, SCREEN_WIDTH, enemy.rec, enemy.isAlive);
            playerAnimation(player.direc, player.rec);
            
            if (collision) {
                enemy.hitTimer = 0.2f; // Set the timer to the desired delay in seconds
                enemy.health -= gun.damage;
            }




            if (enemy.hitTimer > 0.0f && enemy.isAlive) {
                enemy.hitTimer -= GetFrameTime(); // Decrease the timer by the frame time
                DrawSpriteAnimationPro(inim1Anim_walkingLeft, enemy.rec, (Vector2){0,0}, 0, RED);
            } else if (enemy.health >= 0){
                DrawSpriteAnimationPro(inim1Anim_walkingLeft, enemy.rec, (Vector2){0,0}, 0, WHITE);
            }
            // printf("Heath: %f\n", enemy.health);



                    // If the enemy's health drops below 0, start the death animation
            if (enemy.health < 0 && enemy.isAlive) {
                printf("BBBBBBBB");
                enemy.isAlive = false;
                enemy.deathTimer = 1.f; // Set the timer to the length of the death animation
            }

            // If the deathTimer is greater than 0, draw the death animation
            if (enemy.deathTimer > 0.0f) {
                printf("AAAA");
                enemy.deathTimer -= GetFrameTime(); // Decrease the timer by the frame time
                DrawSpriteAnimationPro(inim1Anim_dyingLeft, enemy.rec, (Vector2){0,0}, 0, WHITE);
            }

            // printf("%f\n", enemy.deathTimer);


        EndDrawing();
    }

    // while (bulletList != NULL) {
    //     removeBullet(bulletList);
    // }



}
