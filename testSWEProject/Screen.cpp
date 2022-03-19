#include "Screen.h"

Screen::Screen() {
    this->needToDraw = false;
}
Screen::Screen(bool showScreenOnCreation) {
    needToDraw = showScreenOnCreation;
}
void Screen::showScreen(sf::RenderWindow &w) {
    w.draw(thingsToDraw.find("background")->second);
    for (auto i = thingsToDraw.begin(); i != thingsToDraw.end(); i++) {
        if (i->first != "background") {
            w.draw(i->second);
        }
    }
}