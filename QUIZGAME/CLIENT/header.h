#include <SFML/Graphics.hpp>
struct button{
    float width;
    float heigth;
    float x;
    float y;
};
struct point{
    float x;
    float y;
};
bool checkButton(float x, float y,button but){
    if(x>but.x&&x<but.x+but.width&&y>but.y&&y<but.y+but.heigth){
        return 1;
    }
    return 0;
}

#define textSize 24
#define WI 800
#define HE 800
