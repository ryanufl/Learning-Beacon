#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Screen.h"


using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1600, 1000), "Learning Beacon", sf::Style::Close);


    sf::RectangleShape background(sf::Vector2f(1600, 1000));
    sf::Texture fishtankBackground;
    fishtankBackground.loadFromFile("fishtank.jpg");
    background.setTexture(&fishtankBackground); 


    sf::RectangleShape playButton(sf::Vector2f(400, 150));
    sf::RectangleShape exitButton(sf::Vector2f(400, 150));
    
    playButton.setPosition(600,300);
    exitButton.setPosition(600,500);
    
    playButton.setOutlineColor(sf::Color::Black);
    playButton.setOutlineThickness(5);

    exitButton.setOutlineColor(sf::Color::Black);
    exitButton.setOutlineThickness(5);

    vector<Screen*> screens;

    Screen startMenu(true);
    screens.push_back(&startMenu);
    startMenu.thingsToDraw.emplace("background", background);
    startMenu.thingsToDraw.emplace("play", playButton);
    startMenu.thingsToDraw.emplace("exit", exitButton);

    Screen mathGame(false);
    screens.push_back(&mathGame);
    mathGame.thingsToDraw.emplace("background", background);
    mathGame.thingsToDraw.find("background")->second.setFillColor(sf::Color(40, 40, 40));
    mathGame.thingsToDraw.emplace("backButton", sf::RectangleShape(sf::Vector2f(500, 500)));
    mathGame.thingsToDraw.find("backButton")->second.setPosition(400, 400);


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    //cout << event.mouseButton.x << "   :X\n\ny: " << event.mouseButton.y << "\n";
                    if (startMenu.thingsToDraw.find("play")->second.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y) && startMenu.needToDraw) {
                        playButton.setFillColor(sf::Color::Yellow);
                        //background.setFillColor(sf::Color(40, 40, 40));
                        startMenu.thingsToDraw.find("play")->second.setFillColor(sf::Color::Yellow);
                    }else if(startMenu.thingsToDraw.find("exit")->second.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y) && startMenu.needToDraw) {
                        //window.close();
                        startMenu.needToDraw = false;
                        mathGame.needToDraw = true;
                    }
                    else if (mathGame.thingsToDraw.find("backButton")->second.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y) && mathGame.needToDraw) {
                        //window.close();
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
