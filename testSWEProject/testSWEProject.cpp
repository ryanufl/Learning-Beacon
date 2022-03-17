#include <SFML/Graphics.hpp>
#include <iostream>


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
                    if (playButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        playButton.setFillColor(sf::Color::Yellow);
                    }else if(exitButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        window.close();
                    }
                }
            }
        }

        window.clear();
        window.draw(background);
        window.draw(playButton);
        window.draw(exitButton);
        window.display();
    }


    return 0;
}
