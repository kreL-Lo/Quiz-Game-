

sf::RectangleShape test[16];
sf::Text text[16];
sf::ConvexShape arrows[2];
#define k HE/height-1
sf::RectangleShape tails[2];
//messy stuff
using namespace std;
void drawPlayerScore(vector<string> data, int index){
    sf::String str;
    str="abc";
    text[index].setString(str);
}
void drawAll(sf::RenderWindow & window){
    for(int i=0;i<k;i++){
        window.draw(test[i]);
        window.draw(text[i]);
    }
    for(int i =0 ;i<2;i++)
    {  
        window.draw(arrows[i]);
        window.draw(tails[i]);
    }
        window.display();
}

sf::Font font;

void grafici_init(sf::RenderWindow & window){
    float x, y;
    x=20;
    font.loadFromFile("Arial.ttf");
    y=40;
    for(int i =0;i<2;i++)
        arrows[i].setFillColor(sf::Color::Green);
    
    arrows[0].setPointCount(3);
    arrows[0].setPoint(0, sf::Vector2f(x, y));
    arrows[0].setPoint(1, sf::Vector2f(x+30, y+30));
    arrows[0].setPoint(2, sf::Vector2f(x+30,y-30));
    
    for(int i =0 ;i<2;i++)
        {
            tails[i]=sf::RectangleShape(sf::Vector2f(50,20));
            tails[i].setFillColor(sf::Color::Green);
        }
        tails[0].setPosition(x+20,y-10);

    x=680;
    y=40;
    arrows[1].setPointCount(3);
    arrows[1].setPoint(0, sf::Vector2f(x, y));
    arrows[1].setPoint(1, sf::Vector2f(x-30, y-30));
    arrows[1].setPoint(2, sf::Vector2f(x-30,y+30));
    tails[1].setPosition(x+20-90,y-10);
    window.draw(tails[0]);
    window.draw(tails[1]);
    window.draw(arrows[1]);
    window.draw(arrows[0]);
    for(int i =0 ; i<16;i++)   {
        test[i]=sf::RectangleShape(sf::Vector2f(width,height));
        test[i].setFillColor(sf::Color::Black);
        test[i].setOutlineColor(sf::Color::Green);
        test[i].setOutlineThickness(1);        
        text[i].setFont(font);
        text[i].setCharacterSize(30);
        text[i].setFillColor(sf::Color::Green);
        text[i].setStyle(sf::Text::Bold);
        }
        int d=  k;
        printf("%d",d);
    for(int i =0;i<k;i++){
        test[i].setPosition(100,10+height*i);
        text[i].setPosition(100+20,10+height*i+20);
        window.draw(test[i]);
    }
    window.display();
    
}