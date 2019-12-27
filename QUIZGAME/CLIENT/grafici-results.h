
sf::RectangleShape status;
sf::RectangleShape test[50];
sf::Text topTen;
sf::Text Winner[2];
sf::Text curStatus;
sf::RectangleShape exitButton;
sf::Text exitText;
sf::Text text[50];
sf::Text curPosition[2];
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
    window.draw(topTen);
    window.draw(curPosition[0]);
    window.draw(curPosition[1]);
    window.draw(Winner[0]);
    window.draw(Winner[1]);
    window.draw(status);
    window.draw(exitButton);
    window.draw(exitText);
    window.draw(curStatus);
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
        text[i].setFillColor(sf::Color( 20, 90, 50 ));
        text[i].setStyle(sf::Text::Bold);
        }
        int d = ker;
    for(int i =0;i<d;i++){
        test[i].setPosition(10,50+height*i);
        text[i].setPosition(10+5,50+height*i+10);
        window.draw(test[i]);
    }
    topTen = text[0];
    topTen.setString("Top10 Players\n");
    topTen.setPosition(200,10);
    topTen.setCharacterSize(25);
    Winner[0]= topTen;
    Winner[0].setString("Winner : ");
    Winner[0].setCharacterSize(30);
    Winner[0].setPosition(20,500);
    Winner[0].setFillColor(sf::Color::Red);
    for(int i =0 ;i<2;i++){
        curPosition[i]=Winner[0];
    }
    ///status
    status = test[0];
    status.setPosition(20,650);
    status.setOutlineColor(sf::Color( 241, 196, 15 ));
    status.setSize(sf::Vector2f(300,100));
    curStatus= text[0];
    curStatus.setCharacterSize(30);
    curStatus.setFillColor(sf::Color( 220, 118, 51 ));
    curStatus.setPosition(30,660);
    curStatus.setString("Running");

    ///exit 
    exitButton= status ;
    exitButton.setOutlineColor(sf::Color( 192, 57, 43 ));
    exitButton.setPosition(500,650);
    exitButton.setSize(sf::Vector2f(200,100));
    exitButton.setOutlineThickness(3);
    exitText = text[0];
    exitText.setPosition(510,660);
    exitText.setFillColor(sf::Color( 123, 36, 28 ));
    exitText.setString("Exit");
    exitText.setCharacterSize(25);
    //
    Winner[1]=Winner[0];
    Winner[1].setPosition(200,500);
    Winner[1].setString("test");
    Winner[1].setFillColor(sf::Color::Yellow);
    curPosition[0].setFillColor(sf::Color::Blue);
    curPosition[0].setPosition(20,600);
    curPosition[1].setPosition(200,600);
    curPosition[1].setFillColor(sf::Color( 115, 198, 182));
    curPosition[0].setString("Placement: ");curPosition[0].setString("Placement: ");
    curPosition[1].setString("GHEORGHE :: Score 10 :: Loc ::5 ");
    window.draw(curPosition[0]);
    window.draw(curPosition[1]);
    window.draw(Winner[0]);
    window.draw(Winner[1]);
    window.draw(topTen);
    window.draw(status);
    window.draw(exitButton);
    window.draw(exitText);
    window.draw(curStatus);
    window.display();
    
}