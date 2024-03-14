#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "entity.h"
#include "animacao.h"


float f2(float posx, float speed, int direct) {
    if(posx >= -100 && direct == 1){
        posx += speed;
    }else if(posx >= -100 && direct == -1){
        posx -= speed;
    }
    return posx;
}


void updateGun(gun* GunCTG, int contGun, Texture2D bulletTexture) {
    for(int i = 0; i < contGun; i++) {
        if(GunCTG[i].direct == 1) {
            GunCTG[i].posx -= GunCTG[i].speed;
        } else if(GunCTG[i].direct == -1) {
            GunCTG[i].posx += GunCTG[i].speed;
        }

        GunCTG[i].rec.x = GunCTG[i].posx;
        GunCTG[i].rec.y = GunCTG[i].posy;

        DrawTextureRec(bulletTexture, (Rectangle){0, 0, bulletTexture.width, bulletTexture.height}, (Vector2){GunCTG[i].rec.x, GunCTG[i].rec.y}, WHITE);
    }
}



gun* addGun(float posX, float posY, gun* Bala, int* cont, Texture2D bala, int* direct) {
    if (Bala == NULL) {
        Bala = (gun*)malloc(sizeof(gun));
    } else {
        Bala = (gun*)realloc(Bala, (*cont + 1) * sizeof(gun));
    }

    if (Bala == NULL) {
        
        printf("Erro ao alocar memória para a lista de balas.\n");
        exit(EXIT_FAILURE);
    }

    Bala[*cont].posx = posX;
    Bala[*cont].posy = posY;
    Bala[*cont].direct = *direct;
    Bala[*cont].speed = 6;
    Bala[*cont].rec = (Rectangle){Bala[*cont].posx, Bala[*cont].posy, bala.width, bala.height};
    (*cont)++;
    printf("+1");
    return Bala;
}


Enemy* addEnemy(Enemy* CAC, int* contCAC, Texture2D inimigo1SpriteSheet){
    CAC = (Enemy*) realloc(CAC, (*contCAC+1)*(sizeof(Enemy)));
    
    CAC[*contCAC].enemy_POSINICIAL_X = 1280;
    CAC[*contCAC].enemy_POSINICIAL_Y = 400;
    CAC[*contCAC].enemy_DIM_X = 105;
    CAC[*contCAC].enemy_DIM_Y = 105;
    CAC[*contCAC].speed = -1;
    CAC[*contCAC].health = 100;
    CAC[*contCAC].damage = 10;
    CAC[*contCAC].isAlive = true;
    CAC[*contCAC].hit = false;
    CAC[*contCAC].hitTimer = 0.f;
    CAC[*contCAC].deathTimer = 0.f;


    printf("AAA\n");


    CAC[*contCAC].rec =(Rectangle){CAC[*contCAC].enemy_POSINICIAL_X, CAC[*contCAC].enemy_POSINICIAL_Y, CAC[*contCAC].enemy_DIM_X, CAC[*contCAC].enemy_DIM_Y}; 
    
    (*contCAC)++;

    return CAC;
}

void updateEnemy(int type, Enemy* enemy, int* cont, int SCREEN_WIDTH, int* direct, float Pposx, Texture2D bala, gun** GunRU, int* contRU, bool collision, Player player){
    
    
    SpriteAnimation inimAnim_walkingRight;
    SpriteAnimation inimAnim_walkingLeft;
    SpriteAnimation inimAnim_dyingLeft;
    SpriteAnimation inimAnim_dyingRight;
    
    if (type == 1) {
        inimAnim_walkingRight = inim1Anim_walkingRight;
        inimAnim_walkingLeft = inim1Anim_walkingLeft;
        inimAnim_dyingLeft = inim1Anim_dyingLeft;
        inimAnim_dyingRight = inim1Anim_dyingRight;

    }
    else if (type == 2) {
        inimAnim_walkingRight = inim2Anim_walkingRight;
        inimAnim_walkingLeft = inim2Anim_walkingLeft;
        inimAnim_dyingLeft = inim2Anim_dyingLeft;
        inimAnim_dyingRight = inim2Anim_dyingRight;

    }
    else if (type == 3) {
        inimAnim_walkingRight = inim3Anim_walkingRight;
        inimAnim_walkingLeft = inim3Anim_walkingLeft;
        inimAnim_dyingLeft = inim3Anim_dyingLeft;
        inimAnim_dyingRight = inim3Anim_dyingRight;

    }

    for(int i = 0; i < *cont; i++){
        if(Pposx <= enemy[i].enemy_POSINICIAL_X){
            *direct = 1;
        }else{
            *direct = -1;
        }
        
        
        if (enemy[i].isAlive) enemy[i].enemy_POSINICIAL_X = f2(enemy[i].enemy_POSINICIAL_X, enemy[i].speed, *direct);
        enemy[i].rec = (Rectangle){enemy[i].enemy_POSINICIAL_X, enemy[i].enemy_POSINICIAL_Y, enemy[i].enemy_DIM_X, enemy[i].enemy_DIM_Y};
        


        if (enemy[i].hitTimer > 0.0f && enemy[i].isAlive) {
            enemy[i].hitTimer -= GetFrameTime(); // Decrease the timer by the frame time
            
            

            if (*direct == 1) {     
                DrawSpriteAnimationPro(inimAnim_walkingLeft, enemy[i].rec, (Vector2){0, 0}, 0, RED);
            }
            else if(*direct == -1 ){ 
                DrawSpriteAnimationPro(inimAnim_walkingRight, enemy[i].rec, (Vector2){0, 0}, 0, RED);
            }

        } 
        else if (enemy[i].health >= 0 ) {
            if (*direct == 1) { 
                DrawSpriteAnimationPro(inimAnim_walkingLeft, enemy[i].rec, (Vector2){0, 0}, 0, WHITE);
            }else if(*direct == -1 ){ 
                DrawSpriteAnimationPro(inimAnim_walkingRight, enemy[i].rec, (Vector2){0, 0}, 0, WHITE);
            }
        }

        if (enemy[i].health < 0 && enemy[i].isAlive) {
            enemy[i].isAlive = false;
            enemy[i].deathTimer = 1.2f; // Set the timer to the length of the death animation
        }

        // If the deathTimer is greater than 0, draw the death animation
        if (enemy[i].deathTimer > 0.0f) {
            enemy[i].deathTimer -= GetFrameTime(); // Decrease the timer by the frame time
            if (*direct == 1) { 
                DrawSpriteAnimationPro(inimAnim_dyingLeft, enemy[i].rec, (Vector2){0, 0}, 0, WHITE);
            }else if(*direct == -1 ){ 
                DrawSpriteAnimationPro(inimAnim_dyingRight, enemy[i].rec, (Vector2){0, 0}, 0, WHITE);
            }

        }
        
        // printf("enemy health %f playey damage %f\n", enemy[i].health, player.damage);

        if(IsKeyDown(KEY_E)){// Verifique se a tecla "E" está pressionada e adicione balas conforme necessário
            *GunRU = addGun(enemy[i].enemy_POSINICIAL_X, enemy[i].enemy_POSINICIAL_Y, *GunRU, contRU, bala, direct);
        }
    }
    updateGun(*GunRU, *contRU, bala);
}
