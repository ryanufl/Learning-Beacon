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

