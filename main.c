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

#define MAX_SOUNDS 2
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 540

Sound sounds[MAX_SOUNDS];



Texture2D playerSpriteSheet;
Texture2D inimigo2SpriteSheet;
Texture2D inimigo3SpriteSheet;
Texture2D inimigo1SpriteSheet;
Texture2D cenario;
Texture2D cenarioLog;
Texture2D botaoStart;
Texture2D skyBackground;
Texture2D clouds;
Texture2D clouds1;
Texture2D gameOver;
Texture2D musicON;
Texture2D musicOFF;
Texture2D pontuacaoTable;


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

int MAX_ENEMIES = 5;

Rectangle musicButton;


//Músicas 

int musica = 0, numSounds = 0;

//----------------------------------------------------------------------------------
// Declaração de Funções Locais
//----------------------------------------------------------------------------------
bool collisionRU, collisionCAC, collisionCTG;
static void UpdateDrawFrame(void);

//----------------------------------------------------------------------------------
// Ponto de Entrada Principal
//----------------------------------------------------------------------------------

FILE *file;
bool nameInput = false;

Music Start; 

Color color = WHITE;

Music jogo_g1;

#define MAX_INPUT_CHARS  20

//Spawn points

char name[MAX_INPUT_CHARS + 1] = "\0";      // NOTE: One extra space required for null terminator char '\0'
int letterCount = 0;

Rectangle textBox = { SCREEN_WIDTH/2.0f - 100, 180, 225, 50 };
bool mouseOnText = false;

int framesCounter = 0;

Vector2 spawnPoints[] = {
    {1200, 400}, // 1
    {0, 400},    // 2
};


void loadTextures(){


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
    musicON =               LoadTexture("resources/miscellaneous/sound_on.png");
    musicOFF =              LoadTexture("resources/miscellaneous/sound_off.png");
    pontuacaoTable =              LoadTexture("resources/miscellaneous/pontuacaoTable.png");


}


void mouseText() { 
       if (CheckCollisionPointRec(GetMousePosition(), textBox)) mouseOnText = true;
        else mouseOnText = false;

        if (mouseOnText)
        {
            // Set the window's cursor to the I-Beam
            SetMouseCursor(MOUSE_CURSOR_IBEAM);

            // Get char pressed (unicode character) on the queue
            int key = GetCharPressed();

            // Check if more characters have been pressed on the same frame
            while (key > 0)
            {
                // NOTE: Only allow keys in range [32..125]
                if ((key >= 32) && (key <= 125) && (letterCount < MAX_INPUT_CHARS))
                {
                    name[letterCount] = (char)key;
                    name[letterCount+1] = '\0'; // Add null terminator at the end of the string.
                    letterCount++;
                }

                key = GetCharPressed();  // Check next character in the queue
            }

            if (IsKeyPressed(KEY_BACKSPACE))
            {
                letterCount--;
                if (letterCount < 0) letterCount = 0;
                name[letterCount] = '\0';
            }
        }
        else SetMouseCursor(MOUSE_CURSOR_DEFAULT);

        if (mouseOnText) framesCounter++;
        else framesCounter = 0;
}

int main()
{   
    
    
    // Inicialização
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Tela Inicial");

    loadTextures();

    color.a = 0.f;
    scrollingBack = 0.f;
    scrollingClouds = 0.f;


    
    //----------------------------------------------------------------------------------
    //  Animacoes
    
    player.direc = 1;
    player.isJumping = false;
    player.speed = 6.0f;
    player.health = 200;
    player.damage = 40;
    player.isAlive = true;
    player.deathTimer = 1.0f;
    player.pontuacao = 0.0f;
    

    botaoStartColis = (Rectangle){ BOTAOINICIAL_POS_X, BOTAOINICIAL_POS_Y, botaoStart.width, botaoStart.height };
    player.rec = (Rectangle){SCREEN_WIDTH/2, SCREEN_HEIGHT-PLAYER_DIM_Y - 40, PLAYER_DIM_X, PLAYER_DIM_Y};

    // Cria o botão de ligar e desligar a música no menu.
    musicButton = (Rectangle) {10, 10, musicON.width, musicON.height}; 

    initAnimations(playerSpriteSheet, inimigo1SpriteSheet, inimigo2SpriteSheet, inimigo3SpriteSheet);

    // Define the source rectangle for the bullet
    sourceRecBullet = (Rectangle) {0, 0, bulletTexture.width, bulletTexture.height};

    #if defined(PLATFORM_WEB)
        emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
    #else
        SetTargetFPS(60);

        InitAudioDevice();


        char linha[256];
        FILE* file = fopen("music.txt", "r");
        
        if (file == NULL) // Verifica se o arquivo foi aberto, caso não foi para o programa e retorna erro.
        {
            printf("Não foi possível abrir o arquivo");
            exit(1);
        }
        
        while (!feof(file)) //Pega linha por linha do arquivo "music.txt" e vai carregando a música na struct sounds.
        {
            
            fscanf(file, "%s\n", linha);
            sounds[numSounds] = LoadSound(linha);
            numSounds++;
        }
        fclose(file);
        
        

        // Loop principal do jogo
        while (!WindowShouldClose())
        {
             // Update
        //----------------------------------------------------------------------------------
            mouseText();

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
    CloseAudioDevice();
    DisposeAllAnimations();

    return 0;
}


static void UpdateDrawFrame(void)
{
    // Atualização
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), botaoStartColis)) {
        menu_open = false;
        StopSound(sounds[0]);
        PlaySound(sounds[1]);
    }
    else
    {
        
        // player.rec.x = movx(player.rec.x, player.speed, platforms, player);
        movx(&player, platforms);
        

        if(IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) player.direc = -1;
        if(IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) player.direc = 1;

        if (player.rec.y > 600 ) player.rec.y = 600;
        
        int numRu = 0, numCAC = 0, numCTG = 0;

        if(numEnemies < MAX_ENEMIES && !menu_open){
        int spawnIndex = GetRandomValue(0, sizeof(spawnPoints)/sizeof(spawnPoints[0]) - 1);
        Vector2 spawnPoint = spawnPoints[spawnIndex];

        int enemyType = GetRandomValue(1, 3); // Randomly choose the type of enemy

        switch(enemyType){
            case 1: // Estudante de Engenharia
                if(timeSinceLastRu >= RuDelay && numRu < MAX_ENEMIES/3){
                    // printf("1\n");
                    Ru = addEnemy(Ru, &cont, 0.3f, 80, spawnPoint.x, spawnPoint.y, RonaldoUmidade);
                    timeSinceLastRu = 0.0f;
                    numEnemies++;
                    numRu++;
                }
                break;
            case 2: // Caranguejo
                if(timeSinceLastCAC >= CACDelay && numCAC < MAX_ENEMIES/3){
                    // printf("2\n");
                    CAC = addEnemy(CAC, &contCAC, 0.3f, 80, spawnPoint.x, spawnPoint.y, CarangueijoArmandoCarlos);
                    timeSinceLastCAC = 0.0f;
                    numEnemies++;
                    numCAC++;
                }
                break;
            case 3: // Dengue
                if(timeSinceLastCTG >= CTGDelay && numCTG < MAX_ENEMIES/3){
                    // printf("3\n");
                    CTG = addEnemy(CTG, &contCTG,  0.3f, 45, spawnPoint.x, spawnPoint.y, CalabresoTarcioGeometria);
                    timeSinceLastCTG = 0.0f;
                    numEnemies++;
                    numCTG++;
                }
                break;
            }
        }
        
        // MAX_ENEMIES = updateInimigo(MAX_ENEMIES, player.pontuacao);

        // printf("%d %d\n", MAX_ENEMIES, player.pontuacao);

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

         if (musica == 0){ //Se a música estiver desligada (inicialização do jogo), ela inicia.
            PlaySound(sounds[0]);
            musica = 1;
        }

        if (CheckCollisionPointRec(GetMousePosition(), musicButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){ // Verifica se clicou no botão de ligar/desligar a música
            if (musica == 1) //Se a música tava ligada, ela é desligada.
            {
                PauseSound(sounds[0]);
                musica = 2;
            }
            else if (musica == 2) //Se tiver desligada, ela é ligada.
            {
                ResumeSound(sounds[0]);
                musica = 1;
            }
        }

        BeginDrawing();
            ClearBackground(WHITE);

            DrawTexture(cenarioLog, 0, 0, WHITE);

            if (musica == 1) //Verifica se a música estiver ligada, se estiver muda o ícone para musicON
                DrawTexture(musicON, musicButton.x, musicButton.y, WHITE);

            else //Se a música acabou de ser desligada, muda o ícone para musicOFF
                DrawTexture(musicOFF, musicButton.x, musicButton.y, WHITE);


            DrawTexture(botaoStart, BOTAOINICIAL_POS_X, BOTAOINICIAL_POS_Y, WHITE);

            DrawText("Digite seu nome!", textBox.x, textBox.y - 30, 20, YELLOW);

            DrawRectangleRec(textBox, LIGHTGRAY);
            if (mouseOnText) DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, RED);
            else DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, DARKGRAY);

            DrawText(name, (int)textBox.x + 5, (int)textBox.y + 8, 40, MAROON);

            // DrawText(TextFormat("INPUT CHARS: %i/%i", letterCount, MAX_INPUT_CHARS), 315, 250, 20, DARKGRAY);

            if (mouseOnText)
            {
                if (letterCount < MAX_INPUT_CHARS)
                {
                    // Draw blinking underscore char
                    if (((framesCounter/20)%2) == 0) DrawText("_", (int)textBox.x + 8 + MeasureText(name, 40), (int)textBox.y + 12, 40, MAROON);
                }
                else DrawText("Press BACKSPACE to delete chars...", 230, 300, 20, GRAY);
            }


        EndDrawing();
    }
    else if (!endGame && !menu_open){

        // UpdateMusicStream(Start);
        BeginDrawing();
            ClearBackground(WHITE);

            if (CheckCollisionPointRec(GetMousePosition(), musicButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){ // Verifica se clicou no botão de ligar/desligar a música        
                if (musica == 1) //Se a música tava ligada, ela é desligada.
                    {
                        PauseSound(sounds[1]);
                        musica = 2;
                    }
                    else if (musica == 2) //Se tiver desligada, ela é ligada.
                    {
                        ResumeSound(sounds[1]);
                        musica = 1;
                    }
        }


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

            updateEnemy(1, Ru, &cont, SCREEN_WIDTH, &Ru->direct, player.rec.x, bulletTexture, &GunRU, &contGunRU, collisionRU, &player, &numEnemies, RonaldoUmidade, &MAX_ENEMIES);
            updateEnemy(2, CAC, &contCAC, SCREEN_WIDTH, &CAC->direct, player.rec.x, bulletTexture, &GunCAC, &contGunCAC, collisionCAC, &player, &numEnemies, CarangueijoArmandoCarlos, &MAX_ENEMIES);
            updateEnemy(3, CTG, &contCTG, SCREEN_WIDTH, &CTG->direct, player.rec.x, bulletTexture, &GunCTG, &contGunCTG, collisionCTG, &player, &numEnemies, CalabresoTarcioGeometria, &MAX_ENEMIES);

            if(player.deathTimer >= 0.0f || player.isAlive) playerAnimation(player.direc, player.rec, &player);
            
            



            if(player.deathTimer <= 0.0f && !player.isAlive){
                endGame = true;
            };

            if(endGame){
                file = fopen("pontuacao.txt", "a");
                if (file == NULL) {
                    printf("Cannot open file \n");
                    return 0;
                }

                fprintf(file, "\n%s %d\n", name, player.pontuacao);

                fclose(file);
            }
            
        EndDrawing();
    }else if(endGame && !menu_open){
        BeginDrawing();
            ClearBackground(WHITE);
            DrawTexture(gameOver, 0, -100, WHITE);

            //Printa pontuação e salva
                FILE *file;
                    char lines[100][100];  // Array to store each line
                    int count = 0;

                    file = fopen("pontuacao.txt", "r");
                    if (file == NULL) {
                        printf("Cannot open file\n");
                    }

                    while (fgets(lines[count], sizeof(lines[count]), file)) {
                        if (lines[count][0] != '\n') {
                            count++;
                        }
                    }

                    fclose(file);

                    for(int i = 0; i < count; i++){
                        DrawText(lines[i], 80, 70+ i * 50, 30, WHITE);
                    }




        EndDrawing();
    }





}void playMusicAndSoundEffects() {
    Music Start = LoadMusicStream("resources/sound/abertura.mp3");
   
    PlayMusicStream(Start);

     Music jogo_g1 = LoadMusicStream("resources/sound/jogo_g1.mp3");
    // Lembre-se de atualizar a música no loop principal do jogo
    // UpdateMusicStream(music);
}





void freePonteiros(){

    
}