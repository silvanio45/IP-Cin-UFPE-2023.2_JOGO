#ifndef ANIMACAO_H
#define ANIMACAO_H

#include "raylib.h"
#include <stdlib.h>
#include "entity.h"

#define BOTAOINICIAL_POS_X (1280 - botaoStart.width) / 2
#define BOTAOINICIAL_POS_Y (720 - botaoStart.height) / 2
#define PLAYER_POSINICIAL_X 105
#define PLAYER_POSINICIAL_Y 1205
#define PLAYER_DIM_X 105
#define PLAYER_DIM_Y 105

typedef struct SpriteAnimation
{
    Texture2D spriteSheet;
    int framesPerSecond;
    float timeStarted;

    Rectangle* rectanges;
    int rectanglesLength;
}SpriteAnimation;

SpriteAnimation CreateSpriteAnimation(Texture2D spriteSheet, int framesPerSecond, Rectangle rectangles[], int length);
    
void DisposeSpriteAnimation(SpriteAnimation animation);

void DrawSpriteAnimationPro(SpriteAnimation animation, Rectangle dest, Vector2 origin, float rotation, Color tint);

void initAnimations(Texture2D playerSpriteSheet, Texture2D inimigo1SpriteSheet, Texture2D inimigo2SpriteSheet, Texture2D inimigo3SpriteSheet);

void playerAnimation(int playerDirec, Rectangle playerRect, Player player);

//----------------------------------------------------------------------------------
//  Animacoes
// Player
extern SpriteAnimation playerAnim_walkingRight;
extern SpriteAnimation playerAnim_walkingLeft;
extern SpriteAnimation playerAnim_idleRight;
extern SpriteAnimation playerAnim_idleLeft;
extern SpriteAnimation playerAnim_idleShotingRight;
extern SpriteAnimation playerAnim_idleShotingLeft;
extern SpriteAnimation playerAnim_runningShotingRight;
extern SpriteAnimation playerAnim_runningShotingLeft;
extern SpriteAnimation playerAnim_jumppingMovRight;
extern SpriteAnimation playerAnim_jumppingMovLeft;
extern SpriteAnimation playerAnim_jumppingRight;
extern SpriteAnimation playerAnim_jumppingLeft;
extern SpriteAnimation playerAnim_idleShotingUpRight;
extern SpriteAnimation playerAnim_idleShotingUpLeft;
extern SpriteAnimation playerAnim_runningShotingUpRight;
extern SpriteAnimation playerAnim_runningShotingUpLeft;
extern SpriteAnimation playerAnim_dyingRight;
extern SpriteAnimation playerAnim_dyingLeft;
// Inimigo 1
extern SpriteAnimation inim1Anim_walkingRight;
extern SpriteAnimation inim1Anim_walkingLeft;
extern SpriteAnimation inim1Anim_attackingRight;
extern SpriteAnimation inim1Anim_attackingLeft;
extern SpriteAnimation inim1Anim_dyingRight;
extern SpriteAnimation inim1Anim_dyingLeft;
// Inimigo 2
extern SpriteAnimation inim2Anim_walkingRight;
extern SpriteAnimation inim2Anim_walkingLeft;
extern SpriteAnimation inim2Anim_attackingRight;
extern SpriteAnimation inim2Anim_attackingLeft;
extern SpriteAnimation inim2Anim_dyingRight;
extern SpriteAnimation inim2Anim_dyingLeft;
// Inimigo 3
extern SpriteAnimation inim3Anim_walkingRight;
extern SpriteAnimation inim3Anim_walkingLeft;
extern SpriteAnimation inim3Anim_attackingRight;
extern SpriteAnimation inim3Anim_attackingLeft;
extern SpriteAnimation inim3Anim_dyingRight;
extern SpriteAnimation inim3Anim_dyingLeft;
//----------------------------------------------------------------------------------
#endif // ANIMACAO_H