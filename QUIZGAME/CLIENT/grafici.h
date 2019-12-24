#include <SFML/Graphics.hpp>
sf::RectangleShape pressButtons[4];//5-th is the question rectangle
sf::RectangleShape deleteButons[4];
sf::Text texts[5];
sf::Text texts_default[5];
sf::Font font;
sf::RectangleShape eraser;
sf::Text clocker;
struct p{
    float width;
    float height;
    float x;
    float y;
};
p points[5];
void questionInterface(sf::RenderWindow & window){
      //set positions
    points[4]={50,50,30,100};    
    points[0]={50,50,10,360};
    //eraser
    eraser = sf::RectangleShape(sf::Vector2f(800,800));
    eraser.setFillColor(sf::Color::Black);
    eraser.setPosition(points[0].x+points[0].width + 5,0);
    for(int i =1;i<4;i++){
        points[i]=points[0];
        points[i].y=points[i].y+(i)*30+(i)*points[i].height;
    }

    //delete buttons
    for(int i =0 ;i<4;i++){
        deleteButons[i]=sf::RectangleShape(sf::Vector2f(points[i].width,points[i].height));
        deleteButons[i].setPosition(points[i].x,points[i].y);
        deleteButons[i].setFillColor(sf::Color::Black);
    }
    //settings buttons
    for(int i =0;i<4;i++){
        pressButtons[i]=sf::RectangleShape(sf::Vector2f(points[i].width,points[i].height));
        pressButtons[i].setPosition(points[i].x,points[i].y);
    }
    for(int i =0 ;i<4;i++){
        pressButtons[i].setFillColor(sf::Color::Black);
        pressButtons[i].setOutlineThickness(3);
        if(i==0){
            pressButtons[i].setOutlineColor(sf::Color::Green);
        }
        else{
        pressButtons[i].setOutlineColor(sf::Color(118, 215, 196));
        }
    
        window.draw(pressButtons[i]);
    }
    window.display();

    for(int i=0;i<5;i++){
        texts[i].setFillColor(sf::Color::Green);
        texts[i].setStyle(sf::Text::Bold);
        texts[i].setCharacterSize(24);
        texts[i].setFont(font);
        texts_default[i]=texts[i];
    }
    clocker.setFont(font);
    clocker.setFillColor(sf::Color::Green);
    clocker.setCharacterSize(40);
    clocker.setPosition(500,500);
    clocker.setString("10");

    texts_default[4].setString("Q:");
    texts_default[0].setString("A");
    texts_default[1].setString("B");
    texts_default[2].setString("C");
    texts_default[3].setString("D");
    texts_default[4].setCharacterSize(30);
    texts[4].setCharacterSize(20);
    
    for(int i =0;i<5;i++){
        texts_default[i].setPosition(points[i].x,points[i].y);
        texts_default[i].setFont(font);
        window.draw(texts_default[i]);
    }
    texts[0].setPosition(points[4].x+50,points[4].y);//Q
    texts[1].setPosition(points[0].x+70,points[0].y-10);//A
    texts[2].setPosition(points[1].x+70,points[1].y-10);//B
    texts[3].setPosition(points[2].x+70,points[2].y-10);//C
    texts[4].setPosition(points[3].x+70,points[3].y-10);//D
    for(int i =0 ;i<5;i++){
        window.draw(texts[i]);
    }
    
    window.display();
}
//if need to be implemented
sf::String edit(char container[],int i){
    if(strlen(container)*16<800-points[i].x-60){
        sf::String edit = container ;
        return edit;
    }
    sf::String edit=container;
    int k =800-points[i].x-60;//800-60-30 = 710/ 
    sf::String holder;
    sf::String tmp;
    int j =1;
    int p =0;
    int chars = 60;
    while(16*(edit.getSize()-1)>k){
        tmp=edit.substring(0,chars);
        j=0;
        std::cout<<tmp.getSize()<<std::endl;
        while(tmp[tmp.getSize()-1]!=' '){
            tmp.erase(tmp.getSize()-1,1);
        }
        std::cout<<tmp.toAnsiString()<<std::endl;
        edit.erase(0,tmp.getSize());
        tmp+='\n';
        holder+=tmp;
    }
    if(edit.getSize()!=0){
        holder+=edit;
    }
    return holder;
}
