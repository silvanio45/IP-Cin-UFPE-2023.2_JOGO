

void handleEnemyShot(Enemy *enemy, SpriteAnimation SpriteAnimation){
/*
Will take care of enemys shot and death animation
*/

            if ((*enemy).hitTimer > 0.0f && enemy->isAlive) {
                enemy->hitTimer -= GetFrameTime(); // Decrease the timer by the frame time
                DrawSpriteAnimationPro(inim1Anim_walkingLeft, enemy->rec, (Vector2){0,0}, 0, RED);
            } else if (enemy->health >= 0){
                printf("%f\n", enemy->rec.x);
                DrawSpriteAnimationPro(inim1Anim_walkingLeft, enemy->rec, (Vector2){0,0}, 0, WHITE);
            }
            // printf("Heath: %f\n", enemy->health);



                    // If the enemy's health drops below 0, start the death animation
            if (enemy->health < 0 && enemy->isAlive) {
                enemy->isAlive = false;
                enemy->deathTimer = 1.3f; // Set the timer to the length of the death animation
            }

            // If the deathTimer is greater than 0, draw the death animation
            if (enemy->deathTimer > 0.0f) {
                enemy->deathTimer -= GetFrameTime(); // Decrease the timer by the frame time
                DrawSpriteAnimationPro(inim1Anim_dyingLeft, enemy->rec, (Vector2){0,0}, 0, WHITE);
            }

            // printf("%f\n", enemy->deathTimer);

}
