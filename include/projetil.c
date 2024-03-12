#include "raylib.h"
#include <stdio.h>

#include <stdlib.h>
#include "projetil.h"
#include "inimigos.h"

Projectil* projectilList = NULL; // Start with an empty list

// Function to add a bullet to the list
void addProjectil(Rectangle playerRect, float speed, int playerDirec) {

    Projectil* newProject = (Projectil*)malloc(sizeof(Projectil));

    newProject->position = playerDirec > 0 ? (Vector2) {playerRect.x + 80, playerRect.y + 35} : (Vector2) {playerRect.x - 0, playerRect.y + 35};

    newProject->speed = playerDirec > 0 ? speed : -speed;
    newProject->next = projectilList;
    projectilList = newProject;

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

bool updateProjectils(Texture2D projectilTexture, Rectangle sourceRecProject, int SCREEN_WIDTH, RU* Ru, int* cont){
    Projectil* current = projectilList;
    Projectil* prev = NULL;

    while (current != NULL) {
        // Update bullet position
        current->position.x += current->speed;
        // Draw the bullet
        Rectangle destRecProject = { current->position.x, current->position.y, projectilTexture.width, projectilTexture.height };
        // DrawTextureRec(projectilTexture, sourceRecProject, (Vector2){ destRecProject.x, destRecProject.y }, WHITE);

        Vector2 origin = { destRecProject.width/2 , destRecProject.height/2};
        DrawTexturePro(projectilTexture, sourceRecProject, destRecProject, origin, 0, WHITE);

        for(int i = 0; i < *cont; i++) {
            // Check for collision
            if (CheckCollisionRecs(destRecProject, Ru[i].rec) && Ru[i].isAlive)  {
                Ru[i].hit = true;
                printf("Bullet hit the enemy!\n");
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
        // Check if bullet is off-screen
        if (current->position.x < 0 || current->position.x > SCREEN_WIDTH) {
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
