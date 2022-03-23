#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Screen.h"


using namespace std;

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
    startMenu.thingsToDraw.emplace("exitButton", exitButton);                   //

    Screen mathGame(false);                                                                     //
    screens.push_back(&mathGame);                                                               //
    mathGame.thingsToDraw.emplace("background", background);                                    //
    mathGame.thingsToDraw.find("background")->second.setFillColor(sf::Color(40, 40, 40));       // where math game UI will be
    mathGame.thingsToDraw.emplace("backButton", sf::RectangleShape(sf::Vector2f(500, 500)));    //
    mathGame.thingsToDraw.find("backButton")->second.setPosition(400, 400);                     //


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (startMenu.thingsToDraw.find("playButton") != startMenu.thingsToDraw.end() && startMenu.thingsToDraw.find("playButton")->second.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y) && startMenu.needToDraw) {//tests bounds of button and if the screen is currently visable
                        startMenu.thingsToDraw.find("playButton")->second.setFillColor(sf::Color::Yellow);
                    }else if(startMenu.thingsToDraw.find("exitButton") != startMenu.thingsToDraw.end() && startMenu.thingsToDraw.find("exitButton")->second.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y) && startMenu.needToDraw) {//tests bounds of button and if the screen is currently visable
                        startMenu.needToDraw = false;
                        mathGame.needToDraw = true;
                    }
                    else if (mathGame.thingsToDraw.find("backButton") != mathGame.thingsToDraw.end() && mathGame.thingsToDraw.find("backButton")->second.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y) && mathGame.needToDraw) {//tests bounds of button and if the screen is currently visable
                        startMenu.needToDraw = true;
                        mathGame.needToDraw = false;
                        
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
