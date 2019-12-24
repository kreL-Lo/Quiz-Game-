struct button{
    float width;
    float heigth;
    float x;
    float y;
};
bool checkButton(float x, float y,button but){
    if(x>but.x&&x<but.x+but.width&&y>but.y&&y<but.y+but.heigth){
        return 1;
    }
    return 0;
}