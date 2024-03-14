#include "raylib.h"
#include <stdio.h>

#include <stdlib.h>
#include "projetil.h"
#include "inimigos.h"
#include <math.h>

Projectil* projectilList = NULL; // Start with an empty list

// Function to add a bullet to the list
void addProjectil(Rectangle playerRect, float speed, int playerDirec, bool isPlayerLookingUp) {

    Projectil* newProjectil = (Projectil*)malloc(sizeof(Projectil));

    Vector2 position;
    if(isPlayerLookingUp){
        position = (Vector2) {playerRect.x + 55, playerRect.y - 60};
    }
    else if (playerDirec > 0 ) {
        position = (Vector2) {playerRect.x + 80, playerRect.y + 35};
    } else {
        position = (Vector2) {playerRect.x - 0, playerRect.y + 35};
    }

    newProjectil->position = position;



    newProjectil->isFacingUp = isPlayerLookingUp;

    newProjectil->speed = (Vector2) {playerDirec > 0 ? speed : -speed, isPlayerLookingUp ? -speed : 0};
    newProjectil->next = projectilList;
    projectilList = newProjectil;

}

// Function to remove a bullet from the list
void removeProjectil(Projectil* projectil) {
    if (projectilList == projectil) {
        projectilList = projectil->next;
    } else {
        Projectil* current = projectilList;
        while (current != NULL && current->next != projectil) {
            current = current->next;
        }
        if (current != NULL) {
            current->next = projectil->next;
        }
    }
    free(projectil);
}

bool updateProjectils(Texture2D projectilTexture, Rectangle sourceRecProject, int SCREEN_WIDTH, Enemy* Ru, int* cont, bool isPlayerLookingUp, Platforms *platforms, Player player){
    Projectil* current = projectilList;
    Projectil* prev = NULL;
    float rotation;



    while (current != NULL) {
        // Update bullet position
        
        if(current->isFacingUp) {

            current->position.y += current->speed.y;
            // current->isFacingUp = true;
            rotation = 90;
        }
        
        else {
            rotation = 0;
            current->position.x += current->speed.x;
            // current->isFacingUp = false;

        }
        // Draw the bullet
        Rectangle destRecProject = { current->position.x, current->position.y, projectilTexture.width, projectilTexture.height };

        Vector2 origin = { destRecProject.width/2 , destRecProject.height/2};

        DrawTexturePro(projectilTexture, sourceRecProject, destRecProject, origin, rotation, WHITE);

        for(int i = 0; i < *cont; i++) {
            // Check for collision with enemy
            if (CheckCollisionRecs(destRecProject, Ru[i].rec) && Ru[i].isAlive)  {
                // Ru[i].hit = true;
                Ru[i].hitTimer = 0.2f;
                Ru[i].health -= player.damage;
                
                
                Projectil* next = current->next;
                if (prev != NULL) {
                    prev->next = next;
                } else {
                    projectilList = next;
                }
                removeProjectil(current);
                current = next;
                return true; // A bullet hit the enemy
            }
        }
        for(int i = 0; i < 2; i++) {
            if (CheckCollisionRecs(destRecProject, platforms[i].rec)) {
                Projectil* next = current->next;
                if (prev != NULL) {
                    prev->next = next;
                } else {
                    projectilList = next;
                }
                removeProjectil(current);
                current = next;
                return false; // A bullet hit the platform
            }
        }

        // Check if bullet is off-screen
        if ((current->position.x < 0 || current->position.x > SCREEN_WIDTH) || 
            (current->position.y < 0 || current->position.y > GetScreenHeight())) {
            Projectil* next = current->next;
            //if bullet is off-screen remove it and set the previos bullet struct as current
            if (prev != NULL) {
                prev->next = next;
            } else {
                projectilList = next;
            }
            removeProjectil(current);
            current = next;
        } else { //if is not then change to next bullet 
            prev = current;
            current = current->next;
        }
    }
    return false; // No bullets hit the enemy
}
