#ifndef SWEPROJECT_SCREEN_H
#define SWEPROJECT_SCREEN_H


#pragma once
#include <SFML/Graphics.hpp>
#include <map>

using namespace std;
struct Screen
{
    bool needToDraw;
    map<string, sf::RectangleShape> thingsToDraw;
    Screen();
    Screen(bool a);
    ~Screen();
    void showScreen(sf::RenderWindow &w);
    void setText(string text_to_output, string where_to_display);

private:
    // use for setText function
    vector<sf::Text*> text;
    sf::Font* _font = new sf::Font;

    //
};



#endif //SWEPROJECT_SCREEN_H
