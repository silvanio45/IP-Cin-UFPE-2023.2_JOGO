#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "entity.h"
#include "animacao.h"


float RonaldoUmidadef2(float RUPosx, float speed, int direct) {
    if(RUPosx >= -100 && direct == 1){
        RUPosx += speed;
    }else if(RUPosx >= -100 && direct == -1){
        RUPosx -= speed;
    }
    return RUPosx;
}

float CarangueijoArmandoCarlosf2(float CACPosx, float speed, int direct) {
    if(CACPosx >= -100 && direct == 1){
        CACPosx += speed;
    }else if(CACPosx >= -100 && direct == -1){
        CACPosx -= speed;
    }
    return CACPosx;
}

float CalabresoTarcioGeometriaf2(float CTGPosx, float speed, int direct) {
    if(CTGPosx >= -100 && direct == 1){
        CTGPosx += speed;
    }else if(CTGPosx >= -100 && direct == -1){
        CTGPosx -= speed;
    }
    return CTGPosx;
}

void updateGunRU(GUNRU* GunRU, int contGun, Texture2D bulletTexture) {
    for(int i = 0; i < contGun; i++) {
        if(GunRU[i].direct == 1) {
            GunRU[i].posx -= GunRU[i].speed;
        } else if(GunRU[i].direct == -1) {
            GunRU[i].posx += GunRU[i].speed;
        }

        GunRU[i].rec.x = GunRU[i].posx;
        GunRU[i].rec.y = GunRU[i].posy;

        DrawTextureRec(bulletTexture, (Rectangle){0, 0, bulletTexture.width, bulletTexture.height}, (Vector2){GunRU[i].rec.x, GunRU[i].rec.y}, WHITE);
    }
}

void updateGunCAC(GUNCAC* GunCAC, int contGun, Texture2D bulletTexture) {
    for(int i = 0; i < contGun; i++) {
        if(GunCAC[i].direct == 1) {
            GunCAC[i].posx -= GunCAC[i].speed;
        } else if(GunCAC[i].direct == -1) {
            GunCAC[i].posx += GunCAC[i].speed;
        }

        GunCAC[i].rec.x = GunCAC[i].posx;
        GunCAC[i].rec.y = GunCAC[i].posy;

        DrawTextureRec(bulletTexture, (Rectangle){0, 0, bulletTexture.width, bulletTexture.height}, (Vector2){GunCAC[i].rec.x, GunCAC[i].rec.y}, WHITE);
    }
}

void updateGunCTG(GUNCTG* GunCTG, int contGun, Texture2D bulletTexture) {
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

GUNRU* addGunRU(float posX, float posY, GUNRU* Bala, int* cont, Texture2D bala, int* direct) {
    if (Bala == NULL) {
        Bala = (GUNRU*)malloc(sizeof(GUNRU));
    } else {
        Bala = (GUNRU*)realloc(Bala, (*cont + 1) * sizeof(GUNRU));
    }

    if (Bala == NULL) {
        
        printf("Erro ao alocar memória para a lista de balas do RU.\n");
        exit(EXIT_FAILURE);
    }

    Bala[*cont].posx = posX;
    Bala[*cont].posy = posY;
    Bala[*cont].direct = *direct;
    Bala[*cont].speed = 6;
    Bala[*cont].rec = (Rectangle){Bala[*cont].posx, Bala[*cont].posy, bala.width, bala.height};
    (*cont)++;
    return Bala;
}

GUNCAC* addGunCAC(float posX, float posY, GUNCAC* Bala, int* cont, Texture2D bala, int* direct) {
    if (Bala == NULL) {
        Bala = (GUNCAC*)malloc(sizeof(GUNCAC));
    } else {
        Bala = (GUNCAC*)realloc(Bala, (*cont + 1) * sizeof(GUNCAC));
    }

    if (Bala == NULL) {

        printf("Erro ao alocar memória para a lista de balas do CAC.\n");
        exit(EXIT_FAILURE); 
    }

    Bala[*cont].posx = posX;
    Bala[*cont].posy = posY;
    Bala[*cont].direct = *direct;
    Bala[*cont].speed = 6;
    Bala[*cont].rec = (Rectangle){Bala[*cont].posx, Bala[*cont].posy, bala.width, bala.height};
    (*cont)++;
    return Bala;
}

GUNCTG* addGunCTG(float posX, float posY, GUNCTG* Bala, int* cont, Texture2D bala, int* direct) {
    if (Bala == NULL) {
        Bala = (GUNCTG*)malloc(sizeof(GUNCTG));
    } else {
        Bala = (GUNCTG*)realloc(Bala, (*cont + 1) * sizeof(GUNCTG));
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

RU* addRu(RU* Ru, int* cont, Texture2D inimigo1SpriteSheet){
    Ru = (RU*) realloc(Ru, (*cont+1)*(sizeof(RU)));
    
    Ru[*cont].Ru_POSINICIAL_X = 1280;
    Ru[*cont].Ru_POSINICIAL_Y = 400;
    Ru[*cont].Ru_DIM_X = 105;
    Ru[*cont].Ru_DIM_Y = 105;
    Ru[*cont].speed = -1;
    
    Ru[*cont].rec =(Rectangle){Ru[*cont].Ru_POSINICIAL_X, Ru[*cont].Ru_POSINICIAL_Y, Ru[*cont].Ru_DIM_X, Ru[*cont].Ru_DIM_Y}; 

    printf("BBBB\n");

    (*cont)++;

    return Ru;
}

CarangueijoArmandoCarlos* addCAC(CarangueijoArmandoCarlos* CAC, int* contCAC, Texture2D inimigo1SpriteSheet){
    CAC = (CarangueijoArmandoCarlos*) realloc(CAC, (*contCAC+1)*(sizeof(CarangueijoArmandoCarlos)));
    
    CAC[*contCAC].CAC_POSINICIAL_X = 1280;
    CAC[*contCAC].CAC_POSINICIAL_Y = 400;
    CAC[*contCAC].CAC_DIM_X = 105;
    CAC[*contCAC].CAC_DIM_Y = 105;
    CAC[*contCAC].speed = -1;

    printf("AAA\n");


    CAC[*contCAC].rec =(Rectangle){CAC[*contCAC].CAC_POSINICIAL_X, CAC[*contCAC].CAC_POSINICIAL_Y, CAC[*contCAC].CAC_DIM_X, CAC[*contCAC].CAC_DIM_Y}; 
    
    (*contCAC)++;

    return CAC;
}

CalabresoTarcioGeometria* addCTG(CalabresoTarcioGeometria* CTG, int* contCTG, Texture2D inimigo2SpriteSheet){
    CTG = (CalabresoTarcioGeometria*) realloc(CTG, (*contCTG+1)*(sizeof(CalabresoTarcioGeometria)));
    
    CTG[*contCTG].CTG_POSINICIAL_X = 1280;
    CTG[*contCTG].CTG_POSINICIAL_Y = 400;
    CTG[*contCTG].CTG_DIM_X = 105;
    CTG[*contCTG].CTG_DIM_Y = 105;
    CTG[*contCTG].speed = -1;
    
    CTG[*contCTG].rec =(Rectangle){CTG[*contCTG].CTG_POSINICIAL_X, CTG[*contCTG].CTG_POSINICIAL_Y, CTG[*contCTG].CTG_DIM_X, CTG[*contCTG].CTG_DIM_Y}; 
    
    (*contCTG)++;

    return CTG;
}

void updateRu(Texture2D inimigo1SpriteSheet, RU* Ru, int* cont, int SCREEN_WIDTH, int* direct, float Pposx, Texture2D bala, GUNCTG** GunRU, int* contRU){
    for(int i = 0; i < *cont; i++){
        if(Pposx <= Ru[i].Ru_POSINICIAL_X){
            *direct = 1;
        }else{
            *direct = -1;
        }
        
        Ru[i].Ru_POSINICIAL_X = RonaldoUmidadef2(Ru[i].Ru_POSINICIAL_X, Ru[i].speed, *direct);
        Ru[i].rec = (Rectangle){Ru[i].Ru_POSINICIAL_X, Ru[i].Ru_POSINICIAL_Y, Ru[i].Ru_DIM_X, Ru[i].Ru_DIM_Y};
        
        if (*direct == 1) { 
            DrawSpriteAnimationPro(inim1Anim_walkingLeft, Ru[i].rec, (Vector2){0, 0}, 0, WHITE);
        }else if(*direct == -1 ){ 
            DrawSpriteAnimationPro(inim1Anim_walkingRight, Ru[i].rec, (Vector2){0, 0}, 0, WHITE);
        }
        
        if(IsKeyDown(KEY_E)){// Verifique se a tecla "E" está pressionada e adicione balas conforme necessário
            *GunRU = addGunRU(Ru[i].Ru_POSINICIAL_X, Ru[i].Ru_POSINICIAL_Y, *GunRU, contRU, bala, direct);
        }
    }
    updateGunRU(*GunRU, *contRU, bala);
}
void updateCAC(Texture2D inimigo1SpriteSheet, CarangueijoArmandoCarlos* CAC, int* contCAC, int SCREEN_WIDTH, int* direct, float Pposx, Texture2D bala, GUNCAC** GunCAC, int* contGun){
    for(int i = 0; i < *contCAC; i++){
        if(Pposx <= CAC[i].CAC_POSINICIAL_X){
            *direct = 1;
        }else{
            *direct = -1;
        }
        
        CAC[i].CAC_POSINICIAL_X = CarangueijoArmandoCarlosf2(CAC[i].CAC_POSINICIAL_X, CAC[i].speed, *direct);
        CAC[i].rec = (Rectangle){CAC[i].CAC_POSINICIAL_X, CAC[i].CAC_POSINICIAL_Y, CAC[i].CAC_DIM_X, CAC[i].CAC_DIM_Y};
        
        if (*direct == 1) { 
            DrawSpriteAnimationPro(inim1Anim_walkingLeft, CAC[i].rec, (Vector2){0, 0}, 0, WHITE);
        }else if(*direct == -1 ){ 
            DrawSpriteAnimationPro(inim1Anim_walkingRight, CAC[i].rec, (Vector2){0, 0}, 0, WHITE);
        }
        
        if(IsKeyDown(KEY_E)){// Verifique se a tecla "E" está pressionada e adicione balas conforme necessário
            *GunCAC = addGunCAC(CAC[i].CAC_POSINICIAL_X, CAC[i].CAC_POSINICIAL_Y, *GunCAC, contGun, bala, direct);
        }
    }
    updateGunCAC(*GunCAC, *contGun, bala);
}


void updateCTG(Texture2D inimigo2SpriteSheet, CalabresoTarcioGeometria* CTG, int* contCTG, int SCREEN_WIDTH, int* direct, float Pposx, Texture2D bala, GUNCTG** GunCTG, int* contGun) {
    for(int i = 0; i < *contCTG; i++) {
        if(Pposx <= CTG[i].CTG_POSINICIAL_X) {
            *direct = 1;
        } else {
            *direct = -1;
        }
        
        CTG[i].CTG_POSINICIAL_X = CarangueijoArmandoCarlosf2(CTG[i].CTG_POSINICIAL_X, CTG[i].speed, *direct);
        CTG[i].rec = (Rectangle){CTG[i].CTG_POSINICIAL_X, CTG[i].CTG_POSINICIAL_Y, CTG[i].CTG_DIM_X, CTG[i].CTG_DIM_Y};
        
        if (*direct == 1) { 
            DrawSpriteAnimationPro(inim2Anim_walkingLeft, CTG[i].rec, (Vector2){0, 0}, 0, WHITE);
        } else if(*direct == -1) { 
            DrawSpriteAnimationPro(inim2Anim_walkingRight, CTG[i].rec, (Vector2){0, 0}, 0, WHITE);
        }
        
        if(IsKeyDown(KEY_E)){// Verifique se a tecla "K" está pressionada e adicione balas conforme necessário
        *GunCTG = addGunCTG(CTG[i].CTG_POSINICIAL_X, CTG[i].CTG_POSINICIAL_Y, *GunCTG, contGun, bala, direct);
        }
    }

    updateGunCTG(*GunCTG, *contGun, bala);
}