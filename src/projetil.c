#include "raylib.h"
#include <stdio.h>

#include <stdlib.h>
#include "../include/projetil.h"

Bullet* bulletList = NULL; // Start with an empty list

// Function to add a bullet to the list
void addBullet(Rectangle playerRect, float speed, int playerDirec) {
    // printf("add bullet\n %f %f\n", position.x, position.y);
    printf("DIRET: %d\n", playerDirec);

    

    Bullet* newBullet = (Bullet*)malloc(sizeof(Bullet));

    newBullet->position = playerDirec > 0 ? (Vector2) {playerRect.x + 60, playerRect.y + 15} : (Vector2) {playerRect.x - 30, playerRect.y + 15};

    newBullet->speed = playerDirec > 0 ? speed : -speed;
    newBullet->next = bulletList;
    bulletList = newBullet;
}

// Function to remove a bullet from the list
void removeBullet(Bullet* bullet) {
    if (bulletList == bullet) {
        bulletList = bullet->next;
    } else {
        Bullet* current = bulletList;
        while (current != NULL && current->next != bullet) {
            current = current->next;
        }
        if (current != NULL) {
            current->next = bullet->next;
        }
    }
    free(bullet);
}

void updateBullets(Texture2D bulletTexture, Rectangle sourceRecBullet, int SCREEN_WIDTH){
    Bullet* current = bulletList;
    Bullet* prev = NULL;

    while (current != NULL) {
        // Update bullet position
        current->position.x += current->speed;
        // printf("UpdateBullet\n %f %f\n", current->position.x , current->position.y);
        // Draw the bullet
        Rectangle destRecBullet = { current->position.x, current->position.y, bulletTexture.width, bulletTexture.height };
        DrawTextureRec(bulletTexture, sourceRecBullet, (Vector2){ destRecBullet.x, destRecBullet.y }, WHITE);

        // Check if bullet is off-screen
        if (current->position.x < 0 || current->position.x > SCREEN_WIDTH) {
            Bullet* next = current->next;
            if (prev != NULL) {
                prev->next = next;
            } else {
                bulletList = next;
            }
            removeBullet(current);
            current = next;
        } else {
            prev = current;
            current = current->next;
        }
    }
}
