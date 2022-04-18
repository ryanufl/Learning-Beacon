#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Screen.h"
#include <cstdlib>
#include <string>

using namespace std;
int a, b = 0;
int add(int &a, int &b) {
    //int a = rand() % 10; // up to 10
    //int b = rand() % 10; // up to 10
    //add();
    return a + b;
}
int divide(int &a, int &b){
    //int a = rand() % 10;
    //int b = rand() % 10;
    int c = a * b;
    int d = c / b;
    return d;

}
int multiply(int &a, int &b){
    //int a = rand() % 10;
    //int b = rand() % 10;
    return a * b;
}
int subtract(int &a, int &b){
    //int a = rand() % 20;
    //int b = rand() % 20;
    if (a > b) {
        return a - b;
    }
    return b - a;
}
string randomFunct(int &count) {
    string display = "";
    if (count == 0) {//add 
        a = rand() % 10;
        b = rand() % 10;
        add(a, b);
        display = to_string(a) + " + " + to_string(b);
    }
    else if (count == 1) {//subtract
        a = rand() % 20;
        b = rand() % 20;
        subtract(a, b);
        if (a > b) {
            display = to_string(a) + " - " + to_string(b);
        }
        else {
            display = to_string(b) + " - " + to_string(a);
        }
       
    }
    else if (count == 2) {//multiply
        a = rand() % 10;
        b = rand() % 10;
        multiply(a, b);
        display = to_string(a) + " X " + to_string(b);
    }
    else if (count == 3) {//divide
        a = rand() % 10;
        b = rand() % 10 + 1;
        int c = a * b;
        divide(a, b);
        display = to_string(c) + " / " + to_string(b);
    }
    return display;
}
int getA() {
    return a;
}
int getB() {
    return b;
}

int main()
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
   // sf::RectangleShape mbackground(sf::Vector2f(1600, 1000));
    screens.push_back(&mathGame);                       
    sf::Texture mathBackground;                         
    mathBackground.loadFromFile("mathbackground.jpg");
    background.setTexture(&mathBackground);
    mathGame.thingsToDraw.emplace("background", background);                                    //math background
    mathGame.thingsToDraw.emplace("backButton", sf::RectangleShape(sf::Vector2f(400, 100)));    //
    mathGame.thingsToDraw.emplace("mathDisplay", sf::RectangleShape(sf::Vector2f(400, 200)));
    mathGame.thingsToDraw.emplace("choiceOneMath", sf::RectangleShape(sf::Vector2f(400, 75)));
    mathGame.thingsToDraw.emplace("choiceTwoMath", sf::RectangleShape(sf::Vector2f(400, 75)));
    mathGame.thingsToDraw.emplace("nextMath", sf::RectangleShape(sf::Vector2f(200, 75)));
    mathGame.thingsToDraw.find("backButton")->second.setPosition(50, 75);                     //back buttom on top left corner
    mathGame.thingsToDraw.find("mathDisplay")->second.setPosition(900, 300);  // where the equation will be
    mathGame.thingsToDraw.find("choiceOneMath")->second.setPosition(900, 550); // first option 
    mathGame.thingsToDraw.find("choiceTwoMath")->second.setPosition(900, 675); // second option
    //mathGame.thingsToDraw.find("choiceThreeMath")->second.setPosition(900, 800); //thrid option
    mathGame.thingsToDraw.find("nextMath")->second.setPosition(1300, 900); // to go to next question
    mathGame.setText("Back", "backButton");
    int count = 0;
    int count1 = 0;
    string display = "";
    mathGame.setText("Click Start to start", "mathDisplay");
    mathGame.setText("Start", "nextMath");
    
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
                            if (count1 == 1) {
                                mathGame.thingsToDraw.find("choiceOneMath")->second.setFillColor(sf::Color::Green);
                                mathGame.setText("CORRECT", "mathDisplay");
                            }
                            else {
                                mathGame.thingsToDraw.find("choiceOneMath")->second.setFillColor(sf::Color::Red);
                                mathGame.setText("INCORRECT", "mathDisplay");
                            }

                        }
                        else if (mathGame.thingsToDraw.find("choiceTwoMath")->second.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) { //click on second choice
                            if (count1 == 2) {
                                mathGame.thingsToDraw.find("choiceTwoMath")->second.setFillColor(sf::Color::Green);
                                mathGame.setText("CORRECT", "mathDisplay");
                            }
                            else {
                                mathGame.thingsToDraw.find("choiceTwoMath")->second.setFillColor(sf::Color::Red);
                                mathGame.setText("INCORRECT", "mathDisplay");
                            }
                        }
                        else if (mathGame.thingsToDraw.find("nextMath")->second.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) { // click to next game
                            mathGame.setText("Next", "nextMath");
                            count = rand() % 3;
                            count1 = rand() % 2 + 1;
                            display = randomFunct(count);
                            mathGame.setText(display, "mathDisplay");
                            mathGame.thingsToDraw.find("choiceTwoMath")->second.setFillColor(sf::Color::White);
                            mathGame.thingsToDraw.find("choiceOneMath")->second.setFillColor(sf::Color::White);
                            int c = 0;
                            int d = rand() % 20;
                            int thisA = getA();
                            int thisB = getB();

                            if (count >= 4) {
                                count = 0;
                            }

                            if (count1 > 2) {
                                count1 = 0;
                            }
                            if (count == 0 && count1 == 1) {//add and correct choice 1
                                c = add(thisA, thisB);
                                while (d == c) {
                                    d = rand() % 20;
                                }
                                mathGame.setText(to_string(c), "choiceOneMath");
                                mathGame.setText(to_string(d), "choiceTwoMath");

                            }
                            else if (count == 1 && count1 == 1) {//subtract and correct choice 1
                                c = subtract(thisA, thisB);
                                while (d == c) {
                                    d = rand() % 20;
                                }
                                mathGame.setText(to_string(c), "choiceOneMath");
                                mathGame.setText(to_string(d), "choiceTwoMath");
                            }
                            else if (count == 2 && count1 == 1) {//multiply and correct choice 1
                                c = multiply(thisA, thisB);
                                while (d == c) {
                                    d = rand() % 20;
                                }
                                mathGame.setText(to_string(c), "choiceOneMath");
                                mathGame.setText(to_string(d), "choiceTwoMath");
                            }
                            else if (count == 3 && count1 == 1) {//divide and correct choice 1
                                c = divide(thisA, thisB);
                                while (d == c) {
                                    d = rand() % 20;
                                }
                                mathGame.setText(to_string(c), "choiceOneMath");
                                mathGame.setText(to_string(d), "choiceTwoMath");

                            }
                            else if (count == 0 && count1 == 2) {//add and correct choice 2
                                c = add(thisA, thisB);
                                while (d == c) {
                                    d = rand() % 20;
                                }
                                mathGame.setText(to_string(c), "choiceTwoMath");
                                mathGame.setText(to_string(d), "choiceOneMath");
                            }
                            else if (count == 1 && count1 == 2) {//subtract and correct choice 2
                                c = subtract(thisA, thisB);
                                while (d == c) {
                                    d = rand() % 20;
                                }
                                mathGame.setText(to_string(c), "choiceTwoMath");
                                mathGame.setText(to_string(d), "choiceOneMath");
                            }
                            else if (count == 2 && count1 == 2) {//multiply and correct choice 2
                                c = multiply(thisA, thisB);
                                while (d == c) {
                                    d = rand() % 20;
                                }
                                mathGame.setText(to_string(c), "choiceTwoMath");
                                mathGame.setText(to_string(d), "choiceOneMath");
                            }
                            else if (count == 3 && count1 == 2) {//divide and correct choice 2
                                c = divide(thisA, thisB);
                                while (d == c) {
                                    d = rand() % 20;
                                }
                                mathGame.setText(to_string(c), "choiceTwoMath");
                                mathGame.setText(to_string(d), "choiceOneMath");
                            }
                            
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


    return 0;
}