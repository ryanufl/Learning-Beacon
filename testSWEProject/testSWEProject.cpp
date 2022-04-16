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

    Screen grammarGame(false);
    screens.push_back(&grammarGame);

    sf::Texture gramBackground;
    gramBackground.loadFromFile("../testSWEProject/grammarBackground.jpg");
    background.setTexture(&gramBackground);

    int gramQNo = 0;
    vector<int> gramRightAns = {1, 0, 2, 1, 2};

    sf::RectangleShape gramBack(sf::Vector2f(400, 100));
    sf::RectangleShape gramDispBack(sf::Vector2f(800, 200));
    sf::RectangleShape gramA0(sf::Vector2f(400, 75));
    sf::RectangleShape gramA1(sf::Vector2f(400, 75));
    sf::RectangleShape gramA2(sf::Vector2f(400, 75));
    sf::RectangleShape gramNext(sf::Vector2f (200, 75));

    gramBack.setOutlineColor(sf::Color::Black);
    gramBack.setOutlineThickness(5);
    gramDispBack.setOutlineColor(sf::Color::Black);
    gramDispBack.setOutlineThickness(5);
    gramA0.setOutlineColor(sf::Color::Black);
    gramA0.setOutlineThickness(5);
    gramA1.setOutlineColor(sf::Color::Black);
    gramA1.setOutlineThickness(5);
    gramA2.setOutlineColor(sf::Color::Black);
    gramA2.setOutlineThickness(5);
    gramNext.setOutlineColor(sf::Color::Black);
    gramNext.setOutlineThickness(5);

    grammarGame.thingsToDraw.emplace("background", background);
    grammarGame.thingsToDraw.emplace("gramBack", gramBack);
    grammarGame.thingsToDraw.emplace("gramDispBack", gramDispBack);
    grammarGame.thingsToDraw.emplace("gramA0", gramA0);
    grammarGame.thingsToDraw.emplace("gramA1", gramA1);
    grammarGame.thingsToDraw.emplace("gramA2", gramA2);
    grammarGame.thingsToDraw.emplace("gramNext", gramNext);

    grammarGame.thingsToDraw.find("gramBack")->second.setPosition(50, 75);
    grammarGame.thingsToDraw.find("gramDispBack")->second.setPosition(600, 75);
    grammarGame.thingsToDraw.find("gramA0")->second.setPosition(800, 375);
    grammarGame.thingsToDraw.find("gramA1")->second.setPosition(800, 475);
    grammarGame.thingsToDraw.find("gramA2")->second.setPosition(800, 575);
    grammarGame.thingsToDraw.find("gramNext")->second.setPosition(800, 675);

    grammarGame.setText("Back", "gramBack");
    grammarGame.setText("What is '!' called?", "gramDispBack");
    grammarGame.setText("Period", "gramA0");
    grammarGame.setText("Exclamation mark", "gramA1");
    grammarGame.setText("Question mark", "gramA2");
    grammarGame.setText("Next", "gramNext");

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
                        else if(playMenu.thingsToDraw.find("GrammarGame_Button")->second.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                            playMenu.needToDraw = false;
                            grammarGame.needToDraw = true;
                        }
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
                    else if (grammarGame.needToDraw) {
                        if (grammarGame.thingsToDraw.find("gramBack")->second.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                            startMenu.needToDraw = true;
                            grammarGame.needToDraw = false;
                        }
                        else if (grammarGame.thingsToDraw.find("gramNext")->second.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                            gramQNo++;
                            grammarGame.thingsToDraw.find("gramA0")->second.setFillColor(sf::Color::White);
                            grammarGame.thingsToDraw.find("gramA1")->second.setFillColor(sf::Color::White);
                            grammarGame.thingsToDraw.find("gramA2")->second.setFillColor(sf::Color::White);

                            if(gramQNo == 1) {
                                grammarGame.setText(
                                        "Which one of these ends a sentence?",
                                        "gramDispBack");
                                grammarGame.setText(".", "gramA0");
                                grammarGame.setText("\'", "gramA1");
                                grammarGame.setText(",", "gramA2");
                            } else if(gramQNo == 2) {
                                grammarGame.setText("What is the word green in the\nsentence\"This apple is green.\"?", "gramDispBack");
                                grammarGame.setText("A noun", "gramA0");
                                grammarGame.setText("A verb", "gramA1");
                                grammarGame.setText("An adjective", "gramA2");
                            } else if(gramQNo == 3) {
                                grammarGame.setText("Who is the subject in the sentence\n\"Kevin is giving Sam and Sara his pencil.\"?", "gramDispBack");
                                grammarGame.setText("Sam", "gramA0");
                                grammarGame.setText("Kevin", "gramA1");
                                grammarGame.setText("Sara", "gramA2");
                            } else if (gramQNo == 4) {
                                grammarGame.setText("What is the possessive in the sentence\n\"Daniel's eraser is in the desk.\"?", "gramDispBack");
                                grammarGame.setText("Desk", "gramA0");
                                grammarGame.setText("Eraser", "gramA1");
                                grammarGame.setText("Daniel's", "gramA2");
                            } else {
                                grammarGame.setText("End Display", "gramDispBack");
                                grammarGame.setText("End Answer 0", "gramA0");
                                grammarGame.setText("End Answer 1", "gramA1");
                                grammarGame.setText("End Answer 2", "gramA2");
                            }
                        }
                        else if (grammarGame.thingsToDraw.find("gramA0")->second.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                            if(gramQNo == 1) {
                                grammarGame.thingsToDraw.find("gramA0")->second.setFillColor(sf::Color::Green);
                            } else {
                                grammarGame.thingsToDraw.find("gramA0")->second.setFillColor(sf::Color::Red);
                            }
                        }
                        else if (grammarGame.thingsToDraw.find("gramA1")->second.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                            if(gramQNo == 0 || gramQNo == 3) {
                                grammarGame.thingsToDraw.find("gramA1")->second.setFillColor(sf::Color::Green);
                            } else {
                                grammarGame.thingsToDraw.find("gramA1")->second.setFillColor(sf::Color::Red);
                            }
                        }
                        else if (grammarGame.thingsToDraw.find("gramA2")->second.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                            if(gramQNo == 2 || gramQNo == 4) {
                                grammarGame.thingsToDraw.find("gramA2")->second.setFillColor(sf::Color::Green);
                            } else {
                                grammarGame.thingsToDraw.find("gramA2")->second.setFillColor(sf::Color::Red);
                            }
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