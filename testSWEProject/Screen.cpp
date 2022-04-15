#include "Screen.h"
#include <iostream>

Screen::Screen() {
    this->needToDraw = false;
}
Screen::Screen(bool showScreenOnCreation) {
    needToDraw = showScreenOnCreation;
    _font->loadFromFile("../testSWEProject/src/Font/OpenSans-Regular.ttf");
}

Screen::~Screen() { //not sure if I need this.
    for(int i = 0; i < text.size(); ++i) delete text[i];
    delete _font;
}

void Screen::showScreen(sf::RenderWindow &w) {
    if (thingsToDraw.find("background") != thingsToDraw.end()) {
        w.draw(thingsToDraw.find("background")->second);
    }
    for (auto i = thingsToDraw.begin(); i != thingsToDraw.end(); i++) {
        if (i->first != "background") {
            w.draw(i->second);
        }
    }
    for (int i = 0; i < text.size(); ++i) {
        w.draw(*text[i]);
    }
}

void Screen::setText(string text_to_output, string where_to_display) {
    sf::Text* _text = new sf::Text();
    _text->setFont(*_font);
    _text->setString(text_to_output);
    _text->setCharacterSize(35);
    _text->setFillColor(sf::Color::Black);
    sf::FloatRect textRect = _text->getLocalBounds();
    sf::FloatRect RectangleShapeRect = thingsToDraw[where_to_display].getLocalBounds();
    _text->setPosition(thingsToDraw[where_to_display].getPosition().x + (RectangleShapeRect.width / 2 - textRect.width / 2),
                       thingsToDraw[where_to_display].getPosition().y + (RectangleShapeRect.height / 2 - 25));
    text.emplace_back(_text);
}


