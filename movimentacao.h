float movx(float posx) {
    float speed = 6.0f; // Increase this value to make the player move faster horizontally
    if (IsKeyDown(KEY_D)) {
        posx += speed;
    }
    if (IsKeyDown(KEY_A)) {
        posx -= speed;
    }
    if (posx < 0) {
        posx = 0;
    }
    if (posx > 1200) {
        posx = 1200;
    }
    return posx;
}

float movy(float posy, float gravidade) {
    float speed = 40.0f; // Increase this value to make the player move faster vertically
    if (IsKeyDown(KEY_S)) {
        posy += speed;
    }
    if (IsKeyDown(KEY_W)) {
        posy -= speed;
    }
    if (posy < 0) {
        posy = 0;
    }
    if (posy > 600) {
        posy = 600;
    }
    posy = posy + gravidade;
    return posy;
}

float pulo(float posy, float *velY, float gravidade, float bonecoHeight, float delta, bool *isJumping, bool *jump){
    

    float initPosY = 600;

    // Apply gravity and update position (fix logic here)
    *velY -= gravidade * delta;
    posy -= *velY * delta;

    printf("AAAA");

    if (posy <= (600 - bonecoHeight)) {
        *isJumping = false;
        *velY = 0;  // Reset vertical velocity
    }

    return posy;
}
