void updateEnemy(Texture2D inimigo1SpriteSheet, Enemy* enemy, int* cont, int SCREEN_WIDTH, int* direct, float Pposx, Texture2D bala, GUNCTG** GunRU, int* contRU){
    for(int i = 0; i < *cont; i++){
        if(Pposx <= enemy[i].enemy_POSINICIAL_X){
            *direct = 1;
        }else{
            *direct = -1;
        }
        
        enemy[i].enemy_POSINICIAL_X = f2(enemy[i].enemy_POSINICIAL_X, enemy[i].speed, *direct);
        enemy[i].rec = (Rectangle){enemy[i].enemy_POSINICIAL_X, enemy[i].enemy_POSINICIAL_Y, enemy[i].enemy_DIM_X, enemy[i].enemy_DIM_Y};
        
        if (*direct == 1) { 
            DrawSpriteAnimationPro(inim1Anim_walkingLeft, enemy[i].rec, (Vector2){0, 0}, 0, WHITE);
        }else if(*direct == -1 ){ 
            DrawSpriteAnimationPro(inim1Anim_walkingRight, enemy[i].rec, (Vector2){0, 0}, 0, WHITE);
        }
        
        if(IsKeyDown(KEY_E)){// Verifique se a tecla "E" está pressionada e adicione balas conforme necessário
            *GunRU = addGunRU(enemy[i].enemy_POSINICIAL_X, enemy[i].enemy_POSINICIAL_Y, *GunRU, contRU, bala, direct);
        }
    }
    updateGunRU(*GunRU, *contRU, bala);
}
