#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "entity.h"
#include "animacao.h"


SpriteAnimation inimAnim_walkingRight;
SpriteAnimation inimAnim_walkingLeft;
SpriteAnimation inimAnim_dyingLeft;
SpriteAnimation inimAnim_dyingRight;
SpriteAnimation inimAnim_attackingLeft;
SpriteAnimation inimAnim_attackingRight;


// int updateInimigo(int MAX_ENEMIES, int pontuacao){
//     MAX_ENEMIES += (pontuacao%50);
//     return MAX_ENEMIES;
// }

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

void removeEnemy(Enemy** CAC, int* contCAC, int index) {
    if (index < 0 || index >= *contCAC) {
        return;
    }

    for (int i = index; i < *contCAC - 1; i++) {
        (*CAC)[i] = (*CAC)[i + 1];
    }

    (*contCAC)--;

    Enemy* temp = (Enemy*)realloc(*CAC, (*contCAC + 1) * sizeof(Enemy));
    if (temp == NULL) {
        // Handle the error, e.g., by logging an error message and exiting the program
        printf("Error reallocating memory!\n");
        exit(1);
    } else {
        *CAC = temp;
    }

}


void selectEnemyTexture(Enemy* enemy, TipoInimigo tipo){
  if (tipo == CarangueijoArmandoCarlos) {
        inimAnim_walkingRight = inim1Anim_walkingRight;
        inimAnim_walkingLeft = inim1Anim_walkingLeft;
        inimAnim_dyingLeft = inim1Anim_dyingLeft;
        inimAnim_dyingRight = inim1Anim_dyingRight;
        inimAnim_attackingLeft = inim1Anim_attackingLeft;
        inimAnim_attackingRight = inim1Anim_attackingRight;

    }
    else if (tipo == CalabresoTarcioGeometria) {
        inimAnim_walkingRight = inim2Anim_walkingRight;
        inimAnim_walkingLeft = inim2Anim_walkingLeft;
        inimAnim_dyingLeft = inim2Anim_dyingLeft;
        inimAnim_dyingRight = inim2Anim_dyingRight;
        inimAnim_attackingLeft = inim2Anim_attackingLeft;
        inimAnim_attackingRight = inim2Anim_attackingRight;


    }
    else if (tipo == RonaldoUmidade) {
        inimAnim_walkingRight = inim3Anim_walkingRight;
        inimAnim_walkingLeft = inim3Anim_walkingLeft;
        inimAnim_dyingLeft = inim3Anim_dyingLeft;
        inimAnim_dyingRight = inim3Anim_dyingRight;
        inimAnim_attackingLeft = inim3Anim_attackingLeft;
        inimAnim_attackingRight = inim3Anim_attackingRight;


    }
}

void selectEnemyAtributes(Enemy *enemy, TipoInimigo tipo){
    
    if (tipo == CarangueijoArmandoCarlos) {

        enemy->enemy_DIM_X = 120;
        enemy->enemy_DIM_Y = 120;

        enemy->health = 150;
        enemy->damage = 30;
        enemy->speed = -1.f;
        enemy->pontuacao = 51;

        enemy->attackAnimationLength = 0.3f;
        enemy->attackThreshold = 80;




    }

    else if (tipo == CalabresoTarcioGeometria) {

        enemy->enemy_DIM_X = 105;
        enemy->enemy_DIM_Y = 105;

        enemy->health = 100;
        enemy->damage = 10;
        enemy->speed = -1.4f;
        enemy->pontuacao = 41;

        enemy->attackAnimationLength = 0.3f;
        enemy->attackThreshold = 80;

    }
    else if (tipo == RonaldoUmidade) {

        enemy->enemy_DIM_X = 105;
        enemy->enemy_DIM_Y = 105;


        enemy->health = 80;
        enemy->damage = 15;
        enemy->speed = -0.3f;
        enemy->pontuacao = 11;

        enemy->attackAnimationLength = 0.3f;
        enemy->attackThreshold = 50;

    }
}





Enemy* addEnemy(Enemy* CAC, int* contCAC, float attackAnimationLength, float atackThreshold, float SpawnX, float SpawnY, TipoInimigo tipo){
    CAC = (Enemy*) realloc(CAC, (*contCAC+1)*(sizeof(Enemy)));
    
    

    CAC[*contCAC].enemy_POSINICIAL_X = SpawnX;
    CAC[*contCAC].enemy_POSINICIAL_Y = SpawnY;
    CAC[*contCAC].isAlive = true;
    CAC[*contCAC].attackPosition = false;
    CAC[*contCAC].hitTimer = 0.f;
    CAC[*contCAC].deathTimer = 0.f;
    CAC[*contCAC].hitDelay = 0.5f;
    CAC[*contCAC].timeSinceLastHit = 0.f;
    CAC[*contCAC].attackAnimationTimer = 0.0f;


    // printf("AAA\n");


    //print tipo
    // printf("tipo: %d\n", tipo);

    selectEnemyAtributes(&CAC[*contCAC], tipo);


    CAC[*contCAC].rec =(Rectangle){CAC[*contCAC].enemy_POSINICIAL_X, CAC[*contCAC].enemy_POSINICIAL_Y, CAC[*contCAC].enemy_DIM_X, CAC[*contCAC].enemy_DIM_Y}; 
    
    (*contCAC)++;

    return CAC;
}

void updateEnemy(int type, Enemy* enemy, int* cont, int SCREEN_WIDTH, int* direct, float Pposx, Texture2D bala, gun** GunRU, int* contRU, bool collision, Player *player, int* numEnemies, TipoInimigo tipo, int* MAX_ENEMIES){
    


    for(int i = 0; i < *cont; i++){
        if(Pposx <= enemy[i].enemy_POSINICIAL_X){
            *direct = 1;
        }else{
            *direct = -1;
        }
        
        selectEnemyTexture(&enemy[i], tipo);

        enemy[i].timeSinceLastHit += GetFrameTime();

        if (enemy[i].isAlive && !enemy[i].attackPosition) enemy[i].enemy_POSINICIAL_X = f2(enemy[i].enemy_POSINICIAL_X, enemy[i].speed, *direct);
        enemy[i].rec = (Rectangle){enemy[i].enemy_POSINICIAL_X, enemy[i].enemy_POSINICIAL_Y, enemy[i].enemy_DIM_X, enemy[i].enemy_DIM_Y};
        


        if (enemy[i].hitTimer > 0.0f && enemy[i].isAlive) {
            enemy[i].hitTimer -= GetFrameTime(); // Decrease the timer by the frame time

            if(!enemy[i].attackPosition)
                if (*direct == 1) DrawSpriteAnimationPro(inimAnim_walkingLeft, enemy[i].rec, (Vector2){0, 0}, 0, RED);
                else DrawSpriteAnimationPro(inimAnim_walkingRight, enemy[i].rec, (Vector2){0, 0}, 0, RED);
            else
                if (*direct == 1) DrawSpriteAnimationPro(inimAnim_attackingLeft, enemy[i].rec, (Vector2){0, 0}, 0, RED);
                else DrawSpriteAnimationPro(inimAnim_attackingRight, enemy[i].rec, (Vector2){0, 0}, 0, RED);

        } 
        else if (enemy[i].health >= 0 &&  enemy[i].isAlive) {

            if (enemy[i].attackPosition)
                if (*direct == 1) DrawSpriteAnimationPro(inimAnim_attackingLeft, enemy[i].rec, (Vector2){0, 0}, 0, WHITE);
                else DrawSpriteAnimationPro(inimAnim_attackingRight, enemy[i].rec, (Vector2){0, 0}, 0, WHITE);
            else 
                if (*direct == 1) DrawSpriteAnimationPro(inimAnim_walkingLeft, enemy[i].rec, (Vector2){0, 0}, 0, WHITE);
                else DrawSpriteAnimationPro(inimAnim_walkingRight, enemy[i].rec, (Vector2){0, 0}, 0, WHITE);


          
        }

        if (enemy[i].health < 0 && enemy[i].isAlive) {
            enemy[i].isAlive = false;
            enemy[i].deathTimer = 1.2f; // Set the timer to the length of the death animation
            player->pontuacao += enemy[i].pontuacao;
            if (player->pontuacao >= 100) *(MAX_ENEMIES) += (player->pontuacao  % 3);

            printf("Teste: %d MAX_ENEMIES %d\n" , (player->pontuacao  % 10), *MAX_ENEMIES);

        }

        // If the deathTimer is greater than 0, draw the death animation
        if (enemy[i].deathTimer > 0.0f) {
            enemy[i].deathTimer -= GetFrameTime(); // Decrease the timer by the frame time

            if (*direct == 1) DrawSpriteAnimationPro(inimAnim_dyingLeft, enemy[i].rec, (Vector2){0, 0}, 0, WHITE);
            else DrawSpriteAnimationPro(inimAnim_dyingRight, enemy[i].rec, (Vector2){0, 0}, 0, WHITE);

        }

        if(enemy[i].deathTimer <= 0.0f && !enemy[i].isAlive) {
            removeEnemy(&enemy, cont, i);
            i--;
            (*numEnemies)--;

        }

        
        // printf("enemy health %f playey damage %f\n", enemy[i].health, player->damage);

        if(IsKeyDown(KEY_E)){// Verifique se a tecla "E" está pressionada e adicione balas conforme necessário
            *GunRU = addGun(enemy[i].enemy_POSINICIAL_X, enemy[i].enemy_POSINICIAL_Y, *GunRU, contRU, bala, direct);
        }


        // printf("enemy position: %f\n", enemy[i].enemy_POSINICIAL_X);
        // printf("player position: %f\n", player->rec.x);

       float distance = enemy[i].enemy_POSINICIAL_X > player->rec.x ? (enemy[i].enemy_POSINICIAL_X - player->rec.x) : (player->rec.x - enemy[i].enemy_POSINICIAL_X);

        // printf("distance: %f\n", distance);

        if(distance <= enemy[i].attackThreshold && (enemy[i].timeSinceLastHit >= enemy[i].hitDelay) && enemy[i].attackPosition == false && CheckCollisionRecs(enemy[i].rec, player->rec) && enemy[i].isAlive){
            enemy[i].attackPosition = true;
            enemy[i].attackAnimationTimer = enemy[i].attackAnimationLength; // Start the attack animation
        }
        // else {
            // enemy[i].attackPosition = false;
        // }

        // If the attack animation is playing
        if(enemy[i].attackAnimationTimer > 0){
            enemy[i].attackAnimationTimer -= GetFrameTime(); // Decrease the timer by the frame time
            // Draw the attack animation here
        }


        // If the attack animation has finished, apply the damage
        if(enemy[i].attackAnimationTimer <= 0 && CheckCollisionRecs(enemy[i].rec, player->rec) && enemy[i].attackPosition){
            player->health -= enemy[i].damage;
            player->hitTimer = 0.3f;
            enemy[i].timeSinceLastHit = 0; // Reset the hit delay timer
            enemy[i].attackPosition = false;
        }



        // printf("player health: %f\n", player->health);


        // printf("pontuacao %.2f\n", player->pontuacao);
    }
    updateGun(*GunRU, *contRU, bala);
}

