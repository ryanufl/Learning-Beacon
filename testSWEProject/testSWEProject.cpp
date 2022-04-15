//#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Screen.h"


using namespace std;

void setKey(vector<sf::RectangleShape>& keys, int priorKey, int currentKey, int offset);
void setCurrentLine(string input, vector<sf::RectangleShape>& output, vector<sf::RectangleShape>& references);

int main(int argc, char** argv)
{
    sf::RenderWindow window(sf::VideoMode(1600, 1000), "Learning Beacon", sf::Style::Close); //creates intial window


    sf::RectangleShape background(sf::Vector2f(1600, 1000)); //adds background
    sf::Texture fishtankBackground;                          //

    fishtankBackground.loadFromFile("../testSWEProject/fishtank.jpg");         //sets up background
    background.setTexture(&fishtankBackground);              //


    sf::RectangleShape playButton(sf::Vector2f(400, 150));   //
    sf::RectangleShape exitButton(sf::Vector2f(400, 150));   //
    //
    playButton.setPosition(600,300);                         //
    exitButton.setPosition(600,500);                         //creates two main menu buttons
    //moves them
    playButton.setOutlineColor(sf::Color::Black);            //
    playButton.setOutlineThickness(5);                       //
    //
    exitButton.setOutlineColor(sf::Color::Black);            //
    exitButton.setOutlineThickness(5);                       //


    vector<Screen*> screens;                                               //used to correctly print one screen at a time


    Screen startMenu(false);                                               //
    screens.push_back(&startMenu);                                        //
    startMenu.thingsToDraw.emplace("background", background);             //adds all buttons/images used for startMenu ========WILL NEED TO CHANGE WHEN USING SPRITES========
    startMenu.thingsToDraw.emplace("playButton", playButton);                   //
    startMenu.setText("Play", "playButton");
    startMenu.thingsToDraw.emplace("exitButton", exitButton);                   //
    startMenu.setText("Exit", "exitButton");

    /*
     * play menu
     * display when play button clicked.
     */
    Screen playMenu(false);
    screens.push_back(&playMenu);
    playMenu.thingsToDraw.emplace("background", background); //set background as background.jpg.
    playMenu.thingsToDraw.find("background")->second.setFillColor(sf::Color(40,40,40)); //change color to darker.
    playMenu.thingsToDraw.emplace("MathGame_Button", sf::RectangleShape(sf::Vector2f(400, 150))); //button MathGame_Button.
    playMenu.thingsToDraw.emplace("GrammarGame_Button", sf::RectangleShape(sf::Vector2f(400, 150))); //button GrammarGame_Button.
    playMenu.thingsToDraw.emplace("TypingGame_Button", sf::RectangleShape(sf::Vector2f(400, 150))); //button TypingGame_Button.
    playMenu.thingsToDraw.find("MathGame_Button")->second.setPosition(100, 400); //set MathGame_Button position.
    playMenu.thingsToDraw.find("GrammarGame_Button")->second.setPosition(600, 400); //set GrammarGame_Button position.
    playMenu.thingsToDraw.find("TypingGame_Button")->second.setPosition(1100, 400); //set TypingGame_Button position.
    playMenu.setText("Math Game", "MathGame_Button");       //
    playMenu.setText("Grammar Game", "GrammarGame_Button"); //display text
    playMenu.setText("Typing Game", "TypingGame_Button");   //



    Screen mathGame(false);                             
    screens.push_back(&mathGame);                       
    sf::Texture mathBackground;                         
    mathBackground.loadFromFile("../testSWEProject/mathbackground.jpg");
    background.setTexture(&mathBackground);
    mathGame.thingsToDraw.emplace("background", background);                                    //math background
    mathGame.thingsToDraw.emplace("backButton", sf::RectangleShape(sf::Vector2f(400, 100)));    // 
    mathGame.thingsToDraw.emplace("mathDisplay", sf::RectangleShape(sf::Vector2f(400, 200)));
    mathGame.thingsToDraw.emplace("choiceOneMath", sf::RectangleShape(sf::Vector2f(400, 75)));
    mathGame.thingsToDraw.emplace("choiceTwoMath", sf::RectangleShape(sf::Vector2f(400, 75)));
    mathGame.thingsToDraw.emplace("nextMath", sf::RectangleShape(sf::Vector2f(400, 75)));
    mathGame.thingsToDraw.find("backButton")->second.setPosition(50, 75);                     //back buttom on top left corner
    mathGame.thingsToDraw.find("mathDisplay")->second.setPosition(900, 300);  // where the equation will be
    mathGame.thingsToDraw.find("choiceOneMath")->second.setPosition(900, 550); // first option 
    mathGame.thingsToDraw.find("choiceTwoMath")->second.setPosition(900, 675); // second option
    mathGame.thingsToDraw.find("nextMath")->second.setPosition(900, 800); // to go to next question

    Screen typingGame(true);
    screens.push_back(&typingGame);
    sf::RectangleShape testLetter(sf::Vector2f(100, 100));
    sf::Texture font;
    font.loadFromFile("../testSWEProject/src/image/font.png");
    testLetter.setTexture(&font);
    testLetter.setOutlineThickness(5);
    testLetter.setOutlineColor(sf::Color::Black);
    
    vector<sf::RectangleShape> keys;
    for (int i = 0; i < 26; i++) {
        keys.push_back(testLetter);
        if (i < 13) {
            keys.at(i).setTextureRect(sf::IntRect(17 + 73 * i, 20, 40 + i, 40));
        }
        else {
            keys.at(i).setTextureRect(sf::IntRect(17 + 73 * (i-13), 100, 40 + (i-13), 40));
        }
        keys.at(i).setPosition(i * 105 + 20, 60);
    } 
    //adding a space key
    keys.push_back(sf::RectangleShape(sf::Vector2f(100,100)));
    keys.at(26).setTexture(&font);

    keys.at(26).setTextureRect(sf::IntRect(120, 100, 1, 1));

    //first letter of each row used as a reference, q is used as reference for a and z, so move 'q' and move entire keyboard
    keys.at(16).setPosition(300,450);//q //first row, offset each by 65, second row starts 1/4 a key after first, third row starts 1/2 a key after second

    setKey(keys, 16, 22, 105); //row 1
    setKey(keys, 22, 4, 105);
    setKey(keys, 4, 17, 105);
    setKey(keys, 17, 19, 105);
    setKey(keys, 19, 24, 105);
    setKey(keys, 24, 20, 105);
    setKey(keys, 20, 8, 105);
    setKey(keys, 8, 14, 105);
    setKey(keys, 14, 15, 105);

    //row 2
    keys.at(0).setPosition(keys.at(16).getPosition().x + 25, keys.at(16).getPosition().y + 105);
    setKey(keys, 0, 18, 105);
    setKey(keys, 18, 3, 105);
    setKey(keys, 3, 5, 105);
    setKey(keys, 5, 6, 105);
    setKey(keys, 6, 7, 105);
    setKey(keys, 7, 9, 105);
    setKey(keys, 9, 10, 105);
    setKey(keys, 10, 11, 105);

    //row 3
    keys.at(25).setPosition(keys.at(0).getPosition().x + 50, keys.at(0).getPosition().y + 105);
    setKey(keys, 25, 23, 105);
    setKey(keys, 23, 2, 105);
    setKey(keys, 2, 21, 105);
    setKey(keys, 21, 1, 105);
    setKey(keys, 1, 13, 105);
    setKey(keys, 13, 12, 105);
    
    //manually fix J and Q bc they are a little too big
    keys.at(9).setTextureRect(sf::IntRect(17 + 73 * 9, 20, 45 + 9, 52));
    keys.at(16).setTextureRect(sf::IntRect(17 + 73 * (16 - 13), 100, 40 + (16 - 13), 52));

    sf::RectangleShape greenOrRedTint(testLetter.getSize());
    vector<sf::RectangleShape> keyTint;

    for (int i = 0; i < keys.size(); i++) {
        keyTint.push_back(greenOrRedTint);
        keyTint.at(i).setPosition(keys.at(i).getPosition());
    }

    for (int i = 0; i < keys.size(); i++) {
        typingGame.thingsToDraw.emplace("testLetter" + to_string(i), keys.at(i));
        typingGame.thingsToDraw.emplace("keyTint" + to_string(i), keyTint.at(i));
    }

    vector<sf::RectangleShape> currentLine;
    setCurrentLine("this is a test", currentLine, keys);
    for (int i = 0; i < currentLine.size(); i++) {
        typingGame.thingsToDraw.emplace("currentChar" + to_string(i), currentLine.at(i));
    }
    sf::RectangleShape greyOrWhiteTint(currentLine.at(0).getSize());
    vector<sf::RectangleShape> currentLineTint;
    for (int i = 0; i < currentLine.size(); i++) {
        currentLineTint.push_back(greyOrWhiteTint);
        currentLineTint.at(i).setPosition(currentLine.at(i).getPosition());
    }
    for (int i = 0; i < currentLineTint.size(); i++) {
        typingGame.thingsToDraw.emplace("acurrentCharTint" + to_string(i), currentLineTint.at(i));
    }


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (startMenu.needToDraw) {
                        if (startMenu.thingsToDraw.find("playButton")->second.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {//tests bounds of button and if the screen is currently visable
                            startMenu.thingsToDraw.find("playButton")->second.setFillColor(sf::Color::Yellow);
                            playMenu.needToDraw = true;
                            startMenu.needToDraw = false;
                        }
                        else if (startMenu.thingsToDraw.find("exitButton")->second.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {//tests bounds of button and if the screen is currently visable
                            window.close();
                        }
                        else if (startMenu.thingsToDraw.find("exitButton")->second.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {//tests bounds of button and if the screen is currently visable
                            startMenu.needToDraw = false;
                            mathGame.needToDraw = true;
                        }
                    }
                    else if(playMenu.needToDraw){
                        //only if on play menu screen, change colors to yellow for button clicking.
                        if (playMenu.thingsToDraw.find("MathGame_Button")->second.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                            playMenu.needToDraw = false;
                            mathGame.needToDraw = true;
                        }
                        else if(playMenu.thingsToDraw.find("GrammarGame_Button")->second.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                            playMenu.thingsToDraw.find("GrammarGame_Button")->second.setFillColor(sf::Color::Yellow);
                        else if(playMenu.thingsToDraw.find("TypingGame_Button")->second.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                            playMenu.thingsToDraw.find("TypingGame_Button")->second.setFillColor(sf::Color::Yellow);
                    }
                    else if (mathGame.needToDraw) {
                        if (mathGame.thingsToDraw.find("choiceOneMath")->second.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) { // click on first choice
                            mathGame.thingsToDraw.find("choiceOneMath")->second.setFillColor(sf::Color::Blue);
                        }
                        else if (mathGame.thingsToDraw.find("choiceTwoMath")->second.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) { //click on second choice
                            mathGame.thingsToDraw.find("choiceTwoMath")->second.setFillColor(sf::Color::Magenta);
                        }
                        else if (mathGame.thingsToDraw.find("nextMath")->second.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) { // click to next game
                            mathGame.thingsToDraw.find("nextMath")->second.setFillColor(sf::Color::Green);
                        }
                        else if (mathGame.thingsToDraw.find("backButton")->second.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {//tests bounds of button and if the screen is currently visable
                            startMenu.needToDraw = true;
                            mathGame.needToDraw = false;
                        }
                    }
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                typingGame.thingsToDraw.find("keyTint0")->second.setFillColor(sf::Color(sf::Color(255, 0, 0, 255)));
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
            {
                typingGame.thingsToDraw.find("acurrentCharTint0")->second.setFillColor(sf::Color(0, 0, 0, 255));
               // typingGame.thingsToDraw.find("currentChar0")->second.setOutlineColor(sf::Color::Black);
               // typingGame.thingsToDraw.find("currentChar0")->second.setOutlineThickness(5);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
            {
                typingGame.thingsToDraw.find("acurrentCharTint0")->second.setPosition(500, 400);
            }
        }

        window.clear(sf::Color::White);
        for (int i = 0; i < screens.size(); i++) {
            if (screens.at(i)->needToDraw) {
                screens.at(i)->showScreen(window);
            }
        }
        window.display();
    }


    doctest::Context context;
    int res = context.run(); // run tests
    return res;
}              




void setKey(vector<sf::RectangleShape>& keys, int referenceKey, int currentKey, int offset) {
    keys.at(currentKey).setPosition(keys.at(referenceKey).getPosition().x + offset, keys.at(referenceKey).getPosition().y);
}

void setCurrentLine(string input, vector<sf::RectangleShape>& output, vector<sf::RectangleShape>& references) {
    string acceptableChars = "abcdefghijklmnopqrstuvwxyz ";
    for (int i = 0; i < input.length(); i++) {
        char currentLetter = input.at(i);
        if (acceptableChars.find(currentLetter) != string::npos) {
            //cout << acceptableChars.find(currentLetter) << endl;
            output.push_back(references.at(acceptableChars.find(currentLetter)));
            output.at(output.size() - 1).setOutlineThickness(0);
            output.at(output.size() - 1).setSize(sf::Vector2f(40, 40));
            //output.at(output.size() - 1).setOutlineThickness(1);
        }
    }
    if (output.size() >= 1) {
        output.at(0).setPosition(100, 100);
    }
    for (int i = 1; i < output.size(); i++) {
        setKey(output, i - 1, i, 40);
    }
    for (int i = output.size() - 1; i >= 0; i--) {
        output.push_back(sf::RectangleShape(output.at(0).getSize()));
        //output.at(output.size()-1).setPosition(output.at(0).getPosition());
        output.at(output.size() - 1).setFillColor(sf::Color::Blue);
    }
    //for (int i = 0; i < output.size() / 2; i++) {
    //    output.at(i + (output.size()-1)/2).setPosition(output.at(i).getPosition());
    //}
}


TEST_CASE("Testing Screen Creation and Setting Position") {
    Screen createScreen;
    Screen* screen = &createScreen;
    CHECK(screen != nullptr);

    Screen s;
    s.thingsToDraw.emplace("testButton", sf::RectangleShape(sf::Vector2f(400, 150)));
    s.thingsToDraw.find("testButton")->second.setFillColor(sf::Color::Yellow);
    CHECK(s.thingsToDraw.find("testButton")->second.getFillColor() == sf::Color::Yellow);


   sf::RectangleShape exitButton(sf::Vector2f(400, 150));                 
   exitButton.setPosition(600, 500);                     
   CHECK(exitButton.getPosition().x == 600);
   CHECK(exitButton.getPosition().y == 500);
}