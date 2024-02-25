#include "raylib.h"
#include <stdlib.h>

typedef struct SpriteAnimation
{
    Texture2D spriteSheet;
    int framesPerSecond;
    float timeStarted;

    Rectangle* rectanges;
    int rectanglesLength;
}SpriteAnimation;

SpriteAnimation CreateSpriteAnimation(Texture2D spriteSheet, int framesPerSecond, Rectangle rectangles[], int length)
{
    SpriteAnimation spriteAnimation = 
    {
        .spriteSheet = spriteSheet,
        .framesPerSecond = framesPerSecond,
        .timeStarted = GetTime(),
        .rectanges = NULL,
        .rectanglesLength = length,
    };

    //aloca/verifica a alocacao do espaco para a quantidade de retangulo
    //caso seja possivel, designa espaco da memoria para a quantidade 
    //de retangulos e salva o endereco do inicio em um ponteiro
    Rectangle* mem = (Rectangle*)malloc(sizeof(Rectangle) * length); 
    if (mem == NULL)
    {
        //não possui memoria
        spriteAnimation.rectanglesLength = 0;
        exit(1);
        return spriteAnimation;
    }
    //atribui o endereço que foi guardado para a lista de retangulos
    spriteAnimation.rectanges = mem;

    //preenche o array com os retangulos
    for (int i = 0; i < length; i++) spriteAnimation.rectanges[i] = rectangles[i];

    return spriteAnimation;
}

void DisposeSpriteAnimation(SpriteAnimation animation)
{
    free(animation.rectanges);
}

void DrawSpriteAnimationPro(SpriteAnimation animation, Rectangle dest, Vector2 origin, float rotation, Color tint)//animacao de sprite, posicao que ira ficar na tela, onde eh o meio do retangulo, rotacao, matiz   
{
    int index = (int)((GetTime()- animation.timeStarted) *animation.framesPerSecond) % animation.rectanglesLength;

    Rectangle source = animation.rectanges[index];
    DrawTexturePro(animation.spriteSheet, source, dest, origin, rotation, tint);
}
