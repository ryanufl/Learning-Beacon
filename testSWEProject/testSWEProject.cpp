//#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Screen.h"


using namespace std;

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


    Screen startMenu(true);                                               //
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
        }

        window.clear();
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