#include <stdio.h>

#include "raylib.h"

#include "movimentacao.h"
#include "animacao.h"

#define BOTAOINICIAL_POS_X (1280 - botaoStart.width) / 2
#define BOTAOINICIAL_POS_Y (720 - botaoStart.height) / 2
#define PLAYER_POSINICIAL_X 105
#define PLAYER_POSINICIAL_Y 1205
#define PLAYER_DIM_X 105
#define PLAYER_DIM_Y 105


#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

//----------------------------------------------------------------------------------
// Variáveis Locais (local para este módulo)
//----------------------------------------------------------------------------------

Texture2D playerSpriteSheet;
Texture2D inimigo1SpriteSheet;
Texture2D inimigo2SpriteSheet;
Texture2D inimigo3SpriteSheet;
Texture2D cenario;
Texture2D cenarioLog;
Texture2D botaoStart;

//----------------------------------------------------------------------------------
//  Animacoes
// Player
SpriteAnimation playerAnim_walkingRight;
SpriteAnimation playerAnim_walkingLeft;
SpriteAnimation playerAnim_idleRight;
SpriteAnimation playerAnim_idleLeft;
SpriteAnimation playerAnim_idleShotingRight;
SpriteAnimation playerAnim_idleShotingLeft;
SpriteAnimation playerAnim_runningShotingRight;
SpriteAnimation playerAnim_runningShotingLeft;
SpriteAnimation playerAnim_jumppingMovRight;
SpriteAnimation playerAnim_jumppingMovLeft;
SpriteAnimation playerAnim_jumppingRight;
SpriteAnimation playerAnim_jumppingLeft;

// Inimigo 1
SpriteAnimation inim1Anim_walkingRight;
SpriteAnimation inim1Anim_walkingLeft;
SpriteAnimation inim1Anim_attackingRight;
SpriteAnimation inim1Anim_attackingLeft;
SpriteAnimation inim1Anim_dyingRight;
SpriteAnimation inim1Anim_dyingLeft;
// Inimigo 2
SpriteAnimation inim2Anim_walkingRight;
SpriteAnimation inim2Anim_walkingLeft;
SpriteAnimation inim2Anim_attackingRight;
SpriteAnimation inim2Anim_attackingLeft;
SpriteAnimation inim2Anim_dyingRight;
SpriteAnimation inim2Anim_dyingLeft;
// Inimigo 3
SpriteAnimation inim3Anim_walkingRight;
SpriteAnimation inim3Anim_walkingLeft;
SpriteAnimation inim3Anim_attackingRight;
SpriteAnimation inim3Anim_attackingLeft;
SpriteAnimation inim3Anim_dyingRight;
SpriteAnimation inim3Anim_dyingLeft;
//----------------------------------------------------------------------------------



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
    playerAnim_walkingRight = CreateSpriteAnimation(playerSpriteSheet,15,(Rectangle[]){
        (Rectangle){0,  71, 40, 44},
        (Rectangle){40, 71, 40, 44},
        (Rectangle){80, 71, 40, 44},
        (Rectangle){120, 71, 40, 44},
        (Rectangle){160, 71, 40, 44},
        (Rectangle){200, 71, 40, 44},
        (Rectangle){240, 71, 40, 44},
        (Rectangle){280, 71, 40, 44},
        (Rectangle){320, 71, 40, 44},
        (Rectangle){360, 71, 40, 44},
        (Rectangle){400, 71, 40, 44},
        (Rectangle){440, 71, 40, 44}
    }, 12); 
    playerAnim_walkingLeft = CreateSpriteAnimation(playerSpriteSheet,15,(Rectangle[]){
        (Rectangle){0,  115, 40, 44},
        (Rectangle){40, 115, 40, 44},
        (Rectangle){80, 115, 40, 44},
        (Rectangle){120, 115, 40, 44},
        (Rectangle){160, 115, 40, 44},
        (Rectangle){200, 115, 40, 44},
        (Rectangle){240, 115, 40, 44},
        (Rectangle){280, 115, 40, 44},
        (Rectangle){320, 115, 40, 44},
        (Rectangle){360, 115, 40, 44},
        (Rectangle){400, 115, 40, 44},
        (Rectangle){440, 115, 40, 44}
    }, 12); 
    playerAnim_idleRight = CreateSpriteAnimation(playerSpriteSheet,6,(Rectangle[]){
        (Rectangle){0,  159, 40, 44},
        (Rectangle){40, 159, 40, 44},
        (Rectangle){80, 159, 40, 44},
        (Rectangle){120, 159, 40, 44},
    }, 4); 
    playerAnim_idleLeft = CreateSpriteAnimation(playerSpriteSheet,6,(Rectangle[]){
        (Rectangle){0,  203, 40, 44},
        (Rectangle){40, 203, 40, 44},
        (Rectangle){80, 203, 40, 44},
        (Rectangle){120, 203, 40, 44},
    }, 4); 
    playerAnim_idleShotingRight = CreateSpriteAnimation(playerSpriteSheet,15,(Rectangle[]){
        (Rectangle){0,  247, 55, 44},
        (Rectangle){55, 247, 55, 44},
        (Rectangle){110, 247, 55, 44},
        (Rectangle){165, 247, 55, 44},  
        (Rectangle){220, 247, 55, 44},
        (Rectangle){275, 247, 55, 44},
    }, 6); 
    playerAnim_idleShotingLeft = CreateSpriteAnimation(playerSpriteSheet,15,(Rectangle[]){
        (Rectangle){0,  291, 55, 44},
        (Rectangle){55, 291, 55, 44},
        (Rectangle){110, 291, 55, 44},
        (Rectangle){165, 291, 55, 44},  
        (Rectangle){220, 291, 55, 44},
        (Rectangle){275, 291, 55, 44},
    }, 6); 
    playerAnim_runningShotingRight = CreateSpriteAnimation(playerSpriteSheet,15,(Rectangle[]){
        (Rectangle){0,  335, 55, 44},
        (Rectangle){55, 335, 55, 44},
        (Rectangle){110, 335, 55, 44},
        (Rectangle){165, 335, 55, 44},  
        (Rectangle){220, 335, 55, 44},
        (Rectangle){275, 335, 55, 44},
        (Rectangle){330,  335, 55, 44},
        (Rectangle){385, 335, 55, 44},
        (Rectangle){440, 335, 55, 44},
        (Rectangle){495, 335, 55, 44},  
        (Rectangle){550, 335, 55, 44},
        (Rectangle){605, 335, 55, 44},
    }, 12); 
    playerAnim_runningShotingLeft = CreateSpriteAnimation(playerSpriteSheet,15,(Rectangle[]){
        (Rectangle){0,  379, 55, 44},
        (Rectangle){55, 379, 55, 44},
        (Rectangle){110, 379, 55, 44},
        (Rectangle){165, 379, 55, 44},  
        (Rectangle){220, 379, 55, 44},
        (Rectangle){275, 379, 55, 44},
        (Rectangle){330, 379, 55, 44},
        (Rectangle){385, 379, 55, 44},
        (Rectangle){440, 379, 55, 44},
        (Rectangle){495, 379, 55, 44},  
        (Rectangle){550, 379, 55, 44},
        (Rectangle){605, 379, 55, 44},
    }, 12); 
    playerAnim_jumppingMovRight = CreateSpriteAnimation(playerSpriteSheet, 10, (Rectangle[]){
        (Rectangle){0, 423, 40, 44},
        (Rectangle){40, 423, 40, 44},
        (Rectangle){80, 423, 40, 44},
        (Rectangle){120, 423, 40, 44},
        (Rectangle){160, 423, 40, 44},
        (Rectangle){200, 423, 40, 44}
    },6);
    playerAnim_jumppingMovLeft = CreateSpriteAnimation(playerSpriteSheet, 10, (Rectangle[]){
        (Rectangle){0, 467, 40, 44},
        (Rectangle){40, 467, 40, 44},
        (Rectangle){80, 467, 40, 44},
        (Rectangle){120, 467, 40, 44},
        (Rectangle){160, 467, 40, 44},
        (Rectangle){200, 467, 40, 44}
    },6);
    playerAnim_jumppingRight = CreateSpriteAnimation(playerSpriteSheet, 10, (Rectangle[]){
        (Rectangle){0, 511, 40, 50},
        (Rectangle){40, 511, 40, 50},
        (Rectangle){80, 511, 40, 50},
        (Rectangle){120, 511, 40, 50},
        (Rectangle){160, 511, 40, 50},
        (Rectangle){200, 511, 40, 50}
    },6);
     playerAnim_jumppingLeft = CreateSpriteAnimation(playerSpriteSheet, 10, (Rectangle[]){
        (Rectangle){0, 561, 40, 50},
        (Rectangle){40, 561, 40, 50},
        (Rectangle){80, 561, 40, 50},
        (Rectangle){120, 561, 40, 50},
        (Rectangle){160, 561, 40, 50},
        (Rectangle){200, 561, 40, 50}
    },6);
    //  Inimigo 1
    inim1Anim_walkingRight = CreateSpriteAnimation(inimigo1SpriteSheet, 15, (Rectangle[]){
        (Rectangle){575, 843, 55, 47},
        (Rectangle){509, 843, 55, 47},
        (Rectangle){444, 843, 55, 47},
        (Rectangle){379, 843, 55, 47},
        (Rectangle){310, 843, 55, 47},
        (Rectangle){242, 843, 55, 47},
        (Rectangle){175, 843, 55, 47},
    },7);
    inim1Anim_walkingLeft = CreateSpriteAnimation(inimigo1SpriteSheet, 15, (Rectangle[]){
        (Rectangle){14, 88, 55, 47},
        (Rectangle){80, 88, 55, 47},
        (Rectangle){147, 88, 55, 47},
        (Rectangle){207, 88, 55, 47},
        (Rectangle){272, 88, 55, 47},
        (Rectangle){347, 88, 55, 47},
        (Rectangle){412, 88, 55, 47},
    },7);
    inim1Anim_attackingRight = CreateSpriteAnimation(inimigo1SpriteSheet, 18, (Rectangle[]){
        (Rectangle){567, 1110, 55, 47},
        (Rectangle){507, 1110, 55, 47},
        (Rectangle){447, 1104, 55, 52},
        (Rectangle){391, 1104, 55, 52},
        (Rectangle){336, 1104, 55, 52},
        (Rectangle){264, 1109, 64, 47},
        (Rectangle){172,1109, 80, 47},
        (Rectangle){86, 1109, 80, 47},
        (Rectangle){6, 1109, 80, 47},
        (Rectangle){567, 1168, 60, 47},
        (Rectangle){504, 1168, 60, 47},
        (Rectangle){440, 1168, 60, 47},
        (Rectangle){380, 1168, 60, 47}
    },13);
    inim1Anim_attackingLeft = CreateSpriteAnimation(inimigo1SpriteSheet, 15, (Rectangle[]){
        (Rectangle){21, 292, 55, 47},
        (Rectangle){81, 292, 55, 47},
        (Rectangle){141, 286, 55, 52},
        (Rectangle){198, 286, 55, 52},
        (Rectangle){249, 286, 55, 52},
        (Rectangle){316, 291, 64, 47},
        (Rectangle){391,291, 80, 47},
        (Rectangle){477, 291, 80, 47},
        (Rectangle){561, 291, 80, 47},
        (Rectangle){21, 350, 60, 47},
        (Rectangle){84, 350, 60, 47},
        (Rectangle){148, 350, 60, 47},
        (Rectangle){208, 350, 60, 47}
    },13);
    inim1Anim_dyingLeft = CreateSpriteAnimation(inimigo1SpriteSheet, 10,(Rectangle[]){
        (Rectangle){15, 556, 55, 47},
        (Rectangle){81, 556, 55, 47},
        (Rectangle){148, 556, 55, 47},
        (Rectangle){294, 556, 60, 47},
        (Rectangle){371, 556, 65, 47},
        (Rectangle){457, 556, 65, 47},
        (Rectangle){17, 623, 65, 50},
        (Rectangle){98, 623, 65, 50},
        (Rectangle){184, 623, 65, 50},
        (Rectangle){263, 623, 65, 50},
        (Rectangle){345, 623, 65, 50},
        (Rectangle){434, 623, 65, 50},
        (Rectangle){14, 683, 68, 55},
        (Rectangle){91, 683, 68, 55},
        (Rectangle){178, 683, 68, 55},
        (Rectangle){266, 683, 68, 55},
        (Rectangle){339, 683, 68, 55},
        (Rectangle){426, 683, 68, 55},
        (Rectangle){510, 683, 68, 55},
        (Rectangle){23, 750, 55, 55},
        (Rectangle){89, 750, 55, 55},
        (Rectangle){156, 750, 55, 55},
        (Rectangle){210, 750, 50, 55},
        (Rectangle){258, 750, 40, 55},
        (Rectangle){298, 750, 40, 55}
    },26);
    inim1Anim_dyingRight = CreateSpriteAnimation(inimigo1SpriteSheet, 10, (Rectangle[]){
        (Rectangle){573, 1373, 55, 47},
        (Rectangle){507, 1373, 55, 47},
        (Rectangle){440, 1373, 55, 47},
        (Rectangle){365, 1373, 60, 47},
        (Rectangle){289, 1373, 65, 47},
        (Rectangle){207, 1373, 65, 47},
        (Rectangle){122, 1373, 65, 47},
        (Rectangle){560, 1440, 65, 50},
        (Rectangle){478, 1440, 65, 50},
        (Rectangle){394, 1440, 65, 50},
        (Rectangle){316, 1440, 65, 50},
        (Rectangle){232, 1440, 65, 50},
        (Rectangle){144, 1440, 65, 50},
        (Rectangle){561, 1500, 68, 55},
        (Rectangle){484, 1500, 68, 55},
        (Rectangle){395, 1500, 68, 55},
        (Rectangle){309, 1500, 68, 55},
        (Rectangle){235, 1500, 68, 55},
        (Rectangle){148, 1500, 68, 55},
        (Rectangle){65, 1500, 68, 55},
        (Rectangle){565, 1567, 55, 55},
        (Rectangle){499, 1567, 55, 55},
        (Rectangle){432, 1567, 55, 55},
        (Rectangle){384, 1567, 50, 55},
        (Rectangle){346, 1567, 40, 55},
        (Rectangle){306, 1567, 40, 55},
    },26);
    //  Inimigo 2
    //  Inimigo 3
    //----------------------------------------------------------------------------------


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
            //animacao
            switch (playerDirec)
            {
            case 1:
                if(IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) 
                {
                    if(IsKeyDown(KEY_F))DrawSpriteAnimationPro(playerAnim_runningShotingRight, playerRect, (Vector2){0,0}, 0, WHITE );
                    else DrawSpriteAnimationPro(playerAnim_walkingRight, playerRect, (Vector2){0,0}, 0, WHITE );
                }
                else
                {
                    if(IsKeyDown(KEY_F)) DrawSpriteAnimationPro(playerAnim_idleShotingRight, playerRect, (Vector2){0,0}, 0, WHITE );
                    else DrawSpriteAnimationPro(playerAnim_idleRight, playerRect, (Vector2){0,0}, 0, WHITE );
                }
                break;
            case -1:
                if(IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) 
                {
                    if(IsKeyDown(KEY_F)) DrawSpriteAnimationPro(playerAnim_runningShotingLeft, playerRect, (Vector2){0,0}, 0, WHITE );
                    else DrawSpriteAnimationPro(playerAnim_walkingLeft, playerRect, (Vector2){0,0}, 0, WHITE );
                }
                else 
                {
                    if (IsKeyDown(KEY_F)) DrawSpriteAnimationPro(playerAnim_idleShotingLeft, playerRect, (Vector2){0,0}, 0, WHITE );
                    else DrawSpriteAnimationPro(playerAnim_idleLeft, playerRect, (Vector2){0,0}, 0, WHITE );
                }
                break;
            default:
                if (IsKeyDown(KEY_F)) DrawSpriteAnimationPro(playerAnim_idleShotingRight, playerRect, (Vector2){0,0}, 0, WHITE );
                else DrawSpriteAnimationPro(playerAnim_idleRight, playerRect, (Vector2){0,0}, 0, WHITE );
                
                break;
            }
        EndDrawing();
    }
}
