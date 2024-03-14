
void updateEnemy(int type, Enemy* enemy, int* cont, int SCREEN_WIDTH, int* direct, float Pposx, Texture2D bala, gun** GunRU, int* contRU, bool collision, Player *player){
    
    
    SpriteAnimation inimAnim_walkingRight;
    SpriteAnimation inimAnim_walkingLeft;
    SpriteAnimation inimAnim_dyingLeft;
    SpriteAnimation inimAnim_dyingRight;
    SpriteAnimation inimAnim_attackingLeft;
    SpriteAnimation inimAnim_attackingRight;
    
    if (type == 1) {
        inimAnim_walkingRight = inim1Anim_walkingRight;
        inimAnim_walkingLeft = inim1Anim_walkingLeft;
        inimAnim_dyingLeft = inim1Anim_dyingLeft;
        inimAnim_dyingRight = inim1Anim_dyingRight;
        inimAnim_attackingLeft = inim1Anim_attackingLeft;
        inimAnim_attackingRight = inim1Anim_attackingRight;


    }
    else if (type == 2) {
        inimAnim_walkingRight = inim2Anim_walkingRight;
        inimAnim_walkingLeft = inim2Anim_walkingLeft;
        inimAnim_dyingLeft = inim2Anim_dyingLeft;
        inimAnim_dyingRight = inim2Anim_dyingRight;
        inimAnim_attackingLeft = inim2Anim_attackingLeft;
        inimAnim_attackingRight = inim2Anim_attackingRight;

    }
    else if (type == 3) {
        inimAnim_walkingRight = inim3Anim_walkingRight;
        inimAnim_walkingLeft = inim3Anim_walkingLeft;
        inimAnim_dyingLeft = inim3Anim_dyingLeft;
        inimAnim_dyingRight = inim3Anim_dyingRight;
        inimAnim_attackingLeft = inim3Anim_attackingLeft;
        inimAnim_attackingRight = inim3Anim_attackingRight;

    }

    for(int i = 0; i < *cont; i++){
        if(Pposx <= enemy[i].enemy_POSINICIAL_X){
            *direct = 1;
        }else{
            *direct = -1;
        }
        
        
        if (enemy[i].isAlive && !enemy[i].attackPosition) enemy[i].enemy_POSINICIAL_X = f2(enemy[i].enemy_POSINICIAL_X, enemy[i].speed, *direct);
        enemy[i].rec = (Rectangle){enemy[i].enemy_POSINICIAL_X, enemy[i].enemy_POSINICIAL_Y, enemy[i].enemy_DIM_X, enemy[i].enemy_DIM_Y};
        


        if (enemy[i].hitTimer > 0.0f && enemy[i].isAlive) {
            enemy[i].hitTimer -= GetFrameTime(); // Decrease the timer by the frame time
            printf("AAA\n");

            if(!enemy[i].attackPosition)
                if (*direct) DrawSpriteAnimationPro(inimAnim_walkingLeft, enemy[i].rec, (Vector2){0, 0}, 0, RED);
                else DrawSpriteAnimationPro(inimAnim_walkingRight, enemy[i].rec, (Vector2){0, 0}, 0, RED);
            else
                if (*direct) DrawSpriteAnimationPro(inim1Anim_attackingLeft, enemy[i].rec, (Vector2){0, 0}, 0, RED);
                else DrawSpriteAnimationPro(inim1Anim_attackingRight, enemy[i].rec, (Vector2){0, 0}, 0, RED);

        } 
        else if (enemy[i].health >= 0 &&  enemy[i].isAlive) {

            if (enemy[i].attackPosition)
                if (*direct) DrawSpriteAnimationPro(inim1Anim_attackingLeft, enemy[i].rec, (Vector2){0, 0}, 0, WHITE);
                else DrawSpriteAnimationPro(inim1Anim_attackingRight, enemy[i].rec, (Vector2){0, 0}, 0, WHITE);
            else 
                if (*direct) DrawSpriteAnimationPro(inimAnim_walkingLeft, enemy[i].rec, (Vector2){0, 0}, 0, WHITE);
                else DrawSpriteAnimationPro(inimAnim_walkingRight, enemy[i].rec, (Vector2){0, 0}, 0, WHITE);


          
        }

        if (enemy[i].health < 0 && enemy[i].isAlive) {
            enemy[i].isAlive = false;
            enemy[i].deathTimer = 1.2f; // Set the timer to the length of the death animation
        }

        // If the deathTimer is greater than 0, draw the death animation
        if (enemy[i].deathTimer > 0.0f) {
            enemy[i].deathTimer -= GetFrameTime(); // Decrease the timer by the frame time

            if (*direct) DrawSpriteAnimationPro(inimAnim_dyingLeft, enemy[i].rec, (Vector2){0, 0}, 0, WHITE);
            else DrawSpriteAnimationPro(inimAnim_dyingRight, enemy[i].rec, (Vector2){0, 0}, 0, WHITE);

        }
        
        // printf("enemy health %f playey damage %f\n", enemy[i].health, player->damage);

        if(IsKeyDown(KEY_E)){// Verifique se a tecla "E" está pressionada e adicione balas conforme necessário
            *GunRU = addGun(enemy[i].enemy_POSINICIAL_X, enemy[i].enemy_POSINICIAL_Y, *GunRU, contRU, bala, direct);
        }


        // printf("enemy position: %f\n", enemy[i].enemy_POSINICIAL_X);
        // printf("player position: %f\n", player->rec.x);

        float distance = enemy[i].enemy_POSINICIAL_X > player->rec.x ? (enemy[i].enemy_POSINICIAL_X - player->rec.x) : (player->rec.x - enemy[i].enemy_POSINICIAL_X);

        // printf("distance: %f\n", distance);

        if(distance <= 100){
            enemy[i].attackPosition = true;
            // DrawSpriteAnimationPro(inimAnim_attackingLeft, enemy[i].rec, (Vector2){0, 0}, 0, WHITE);
        }
        else {
            enemy[i].attackPosition = false;
        }


        if(CheckCollisionRecs(enemy[i].rec, player->rec) && enemy[i].attackPosition){
            player->health -= enemy[i].damage;
            player->hit = true;
        }


    }
    updateGun(*GunRU, *contRU, bala);
}

