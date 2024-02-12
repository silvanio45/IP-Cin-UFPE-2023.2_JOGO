float movx(float posx) {
    if (IsKeyDown(KEY_D)) {
        posx += 0.6f;
    }
    if (IsKeyDown(KEY_A)) {
        posx -= 0.6f;
    }
    if (posx < 0) {
        posx = 0;
    }
    if (posx > 1100) {
        posx = 1100;
    }
    return posx;
}

float movy(float posy, float gravidade) {
    if (IsKeyDown(KEY_S)) {
        posy += 0.6f;
    }
    if (IsKeyDown(KEY_W)) {
        posy -= 0.6f;
    }
    if (posy < 0) {
        posy = 0;
    }
    if (posy > 500) {
        posy = 500;
    }
    if(IsKeyDown(KEY_SPACE)){
       posy = posy - 2.2; 
    }
    posy = posy + gravidade;
    return posy;
}