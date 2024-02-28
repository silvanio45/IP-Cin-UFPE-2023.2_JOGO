#include "raylib.h"
#include <stdio.h>
#include "projetil.h"
#include <stdlib.h>



Bullet* bulletList = NULL; // Start with an empty list

// Function to add a bullet to the list
void addBullet(Vector2 position, float speed) {
    Bullet* newBullet = (Bullet*)malloc(sizeof(Bullet));
    newBullet->position = position;
    newBullet->speed = speed;
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

void updateBullets(Texture2D bulletTexture, Rectangle sourceRecBullet, int SCREE_WIDTH, Bullet* current){
    while (current != NULL) {
                // Update bullet position
                current->position.x += current->speed;

                // Draw the bullet
                Rectangle destRecBullet = { current->position.x, current->position.y, bulletTexture.width, bulletTexture.height };
                DrawTextureRec(bulletTexture, sourceRecBullet, (Vector2){ destRecBullet.x, destRecBullet.y }, WHITE);

                // Check if bullet is off-screen
                if (current->position.x < 0 || current->position.x > SCREE_WIDTH) {
                    Bullet* next = current->next;
                    removeBullet(current);
                    current = next;
                } else {
                    current = current->next;
                }
            }
}