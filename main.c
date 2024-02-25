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
Texture2D cenario;
Texture2D cenarioLog;
Texture2D botaoStart;

SpriteAnimation playerAnim_walkingRight;
SpriteAnimation playerAnim_walkingLeft;
SpriteAnimation playerAnim_idleRight;
SpriteAnimation playerAnim_idleLeft;
SpriteAnimation playerAnim_idleShotingRight;
SpriteAnimation playerAnim_idleShotingLeft;
SpriteAnimation playerAnim_runningShotingRight;
SpriteAnimation playerAnim_runningShotingLeft;



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
    cenario = LoadTexture("./resources/cenario2.png");
    cenarioLog = LoadTexture("./resources/cenario0.png");
    botaoStart = LoadTexture("./resources/botao2.png");

    botaoStartColis = (Rectangle){ BOTAOINICIAL_POS_X, BOTAOINICIAL_POS_Y, botaoStart.width, botaoStart.height };
    playerRect = (Rectangle){PLAYER_POSINICIAL_X, PLAYER_POSINICIAL_Y, PLAYER_DIM_X, PLAYER_DIM_Y};

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
