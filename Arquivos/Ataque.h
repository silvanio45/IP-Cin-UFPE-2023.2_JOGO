int AtaquePersonagem(float posx, float posy){
    int cont = 0;
    float py;
    float px;
    
    if(cont == 0){
        py = posy;
        px = posx;
    }
    
    if(px == 1280 || py == 720){
        cont = 0;
    } 
    if(IsKeyDown(KEY_F)){
        cont = 1; 
    }
    if(cont == 1){
        px += 0.6f;
    }
    return px;
}
            