#include "raylib.h"
#include <stdio.h>

#include <stdlib.h>
#include "entity.h"
#include "animacao.h"

Enemy* enemyList = NULL; // Start with an empty list 

// Function to add a Enemy to the list
void addEnemy(Enemy enemy) {

    Enemy* newEnemy = (Enemy*)malloc(sizeof(Enemy));
    

    newEnemy->rec.x = enemy.rec.x;
    newEnemy->rec.y = enemy.rec.y;

    newEnemy->rec.height = enemy.rec.height;
    newEnemy->rec.width = enemy.rec.width;
    
    // newEnemy->rec.width = enemy.rec.width;
    
    newEnemy->speed = -enemy.speed;
    newEnemy->next = enemyList;
    enemyList = newEnemy;//aa

}

// Function to remove a Enemy from the lis
void removeEnemy(Enemy* enemy) {
    if (enemyList == enemy) {
        enemyList = enemy->next;
    } else {
        Enemy* current = enemyList;
        while (current != NULL && current->next != enemy) {
            current = current->next;
        }
        if (current != NULL) {
            current->next = enemy->next;
        }
    }
    free(enemy);
}

void updateEnemys(SpriteAnimation EnemyAnimation, Enemy enemy, int SCREEN_WIDTH){
    Enemy* current = enemyList;
    Enemy* prev = NULL;

    while (current != NULL) {
        // Update Enemy position
        current->rec.x += current->speed;
        printf("%f %f\n", current->rec.x, current->rec.y);
        // Draw the Enemy
        // Rectangle destRecEnemy = { current->rec.x, current->position.y, EnemyTexture.width, EnemyTexture.height };
        // DrawTextureRec(EnemyTexture, sourceRecEnemy, (Vector2){ destRecEnemy.x, destRecEnemy.y }, WHITE);
        DrawSpriteAnimationPro(EnemyAnimation, current->rec, (Vector2){0,0}, 0, RED);

        // Check if Enemy is off-screen
        if (current->rec.x < 0 || current->rec.x > SCREEN_WIDTH) {
            Enemy* next = current->next;
            //if Enemy is off-screen remove it and set the previos Enemy struct as current
            if (prev != NULL) {
                prev->next = next;
            } else {
                enemyList = next;
            }
            removeEnemy(current);
            current = next;
        } else {
            prev = current;
            current = current->next;
        }
    }
}
