

sf::RectangleShape test[50];
sf::Text text[50];
#define ker (HE/height)/2
sf::RectangleShape tails[2];
//messy stuff
using namespace std;
void drawPlayerScore(vector<string> data, int index){
    sf::String str;
    str="abc";
    text[index].setString(str);
}
void drawAll(sf::RenderWindow & window){
    for(int i=0;i<ker;i++){
        window.draw(test[i]);
        window.draw(text[i]);
    }
        window.display();
}


void grafici_init(sf::RenderWindow & window){
    font.loadFromFile("Arial.ttf");
    for(int i =0 ; i<50;i++)   {
        test[i]=sf::RectangleShape(sf::Vector2f(width,height));
        test[i].setFillColor(sf::Color::Black);
        test[i].setOutlineColor(sf::Color::Green);
        test[i].setOutlineThickness(1);        
        text[i].setFont(font);
        text[i].setCharacterSize(20);
        text[i].setFillColor(sf::Color::Green);
        text[i].setStyle(sf::Text::Bold);
        }
        int d = ker;
    for(int i =0;i<d;i++){
        test[i].setPosition(10,10+height*i);
        text[i].setPosition(10+5,10+height*i+10);
        window.draw(test[i]);
    }
    window.display();
    
}