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
    void showScreen(sf::RenderWindow &w);

};



#endif //SWEPROJECT_SCREEN_H
