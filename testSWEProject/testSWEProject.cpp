//#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Screen.h"
#include <fstream>


using namespace std;

void setKey(vector<sf::RectangleShape>& keys, int priorKey, int currentKey, int offset);
void setCurrentLine(string input, vector<sf::RectangleShape>& output, vector<sf::RectangleShape>& references);
void turnLowerAndFix(string& toLower);

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





    //typing game start
    Screen typingGame(false);
    screens.push_back(&typingGame);
    sf::RectangleShape tBackground(sf::Vector2f(1600, 1000)); //adds background
    sf::Texture typingBackground;
    typingBackground.loadFromFile("typingBackground.jpg");
    tBackground.setTexture(&typingBackground);
    typingGame.thingsToDraw.emplace("background", tBackground);
    sf::RectangleShape testLetter(sf::Vector2f(100, 100)); //key shape
    sf::Texture font;
    font.loadFromFile("../testSWEProject/src/image/font.png");
    testLetter.setTexture(&font);
    testLetter.setOutlineThickness(5);
    testLetter.setOutlineColor(sf::Color::Black);
    int placeInCurrentLine = 0; //used for correct key tinting
    string currentLineStringInput; //place holder if file is empty
    vector<int> wrongKeys; //used for turning red tints off
    ifstream inputFile("typingLines.txt");
    vector<string> differentLines;

    string readInLine;
    while (getline(inputFile, readInLine)) {
        differentLines.push_back(readInLine);
    }
    if (differentLines.size() == 0) {
        currentLineStringInput = "Please update typingLines.txt";
    }
    else {
        srand(time(NULL));
        int secret = rand() % (differentLines.size());

        currentLineStringInput = differentLines.at(secret);
    }
    turnLowerAndFix(currentLineStringInput);
    
    vector<sf::RectangleShape> keys; //used for keyboard/line of text
    for (int i = 0; i < 26; i++) {
        keys.push_back(testLetter);
        if (i < 13) {
            keys.at(i).setTextureRect(sf::IntRect(17 + 73 * i, 20, 40 + i, 40)); //sets the key shape to be a single letter
        }
        else {
            keys.at(i).setTextureRect(sf::IntRect(17 + 73 * (i-13), 100, 40 + (i-13), 40)); //used for second row bc original .png is split into two rows
        }
        keys.at(i).setPosition(i * 105 + 20, 60);
    } 
    //adding a space key
    keys.push_back(sf::RectangleShape(sf::Vector2f(100,100)));
    keys.at(26).setTexture(&font);

    keys.at(26).setTextureRect(sf::IntRect(120, 100, 1, 1)); //sets it to random area that is blank, used as a space
   
    //first letter of each row used as a reference, q is used as reference for a and z, so move 'q' and move entire keyboard
    keys.at(16).setPosition(300,400);//q //first row, offset each by 65, second row starts 1/4 a key after first, third row starts 1/2 a key after second

    setKey(keys, 16, 22, 105); //row 1
    setKey(keys, 22, 4, 105);
    setKey(keys, 4, 17, 105);
    setKey(keys, 17, 19, 105);
    setKey(keys, 19, 24, 105);
    setKey(keys, 24, 20, 105);
    setKey(keys, 20, 8, 105);
    setKey(keys, 8, 14, 105);
    setKey(keys, 14, 15, 105);

    //row 2
    keys.at(0).setPosition(keys.at(16).getPosition().x + 25, keys.at(16).getPosition().y + 105);
    setKey(keys, 0, 18, 105);
    setKey(keys, 18, 3, 105);
    setKey(keys, 3, 5, 105);
    setKey(keys, 5, 6, 105);
    setKey(keys, 6, 7, 105);
    setKey(keys, 7, 9, 105);
    setKey(keys, 9, 10, 105);
    setKey(keys, 10, 11, 105);

    //row 3
    keys.at(25).setPosition(keys.at(0).getPosition().x + 50, keys.at(0).getPosition().y + 105);
    setKey(keys, 25, 23, 105);
    setKey(keys, 23, 2, 105);
    setKey(keys, 2, 21, 105);
    setKey(keys, 21, 1, 105);
    setKey(keys, 1, 13, 105);
    setKey(keys, 13, 12, 105);
    
    //manually fix J and Q bc they are a little too big
    keys.at(9).setTextureRect(sf::IntRect(17 + 73 * 9, 20, 45 + 9, 52));
    keys.at(16).setTextureRect(sf::IntRect(17 + 73 * (16 - 13), 100, 40 + (16 - 13), 52));
    //manually doing stuff with space/spacebar
    keys.at(26).setOutlineColor(sf::Color::Black);
    keys.at(26).setOutlineThickness(5); //below line sets spacebar relative to the X key, using general keyboard as a reference
    keys.at(26).setPosition(keys.at(23).getPosition().x + keys.at(23).getSize().x + keys.at(23).getOutlineThickness() - 25, keys.at(23).getPosition().y + keys.at(23).getSize().y + keys.at(23).getOutlineThickness()); 
    keys.at(26).setSize(sf::Vector2f(500, keys.at(26).getSize().y));

    sf::RectangleShape greenOrRedTint(testLetter.getSize()); //used to tint a key on the keyboard if it is the correct/incorrect input
    vector<sf::RectangleShape> keyTint;

    for (int i = 0; i < keys.size(); i++) {
        keyTint.push_back(greenOrRedTint);
        keyTint.at(i).setPosition(keys.at(i).getPosition()); //copies position of keyboard key for the tint to be directly over.
    }
    keyTint.at(26).setSize(keys.at(26).getSize()); //used only for space key

    for (int i = 0; i < keys.size(); i++) {
        typingGame.thingsToDraw.emplace("testLetter" + to_string(i), keys.at(i)); //testLetter is the keyboard keys, just discovered that the order in the map can control the layers, so this works
        typingGame.thingsToDraw.emplace("keyTint" + to_string(i), keyTint.at(i));
    }

    vector<sf::RectangleShape> currentLine; //line of text that user will type
    setCurrentLine(currentLineStringInput, currentLine, keys); //sets line of text
    for (int i = 0; i < currentLine.size(); i++) {
        typingGame.thingsToDraw.emplace("currentChar" + to_string(i), currentLine.at(i)); 
    }
    sf::RectangleShape greyOrYellowOrWhiteTint(currentLine.at(0).getSize()); 
    vector<sf::RectangleShape> currentLineTint;
    for (int i = 0; i < currentLine.size(); i++) {
        currentLineTint.push_back(greyOrYellowOrWhiteTint); 
        currentLineTint.at(i).setPosition(currentLine.at(i).getPosition()); //pretty much same as above 
    }
    for (int i = 0; i < currentLineTint.size(); i++) {
        typingGame.thingsToDraw.emplace("acurrentCharTint" + to_string(i), currentLineTint.at(i)); //a added for alphabetical order oops
    }
    //typing game end




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
                        else if (playMenu.thingsToDraw.find("TypingGame_Button")->second.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)){
                            playMenu.needToDraw = false;
                            typingGame.needToDraw = true;
                        }

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
                }
            }

            if (typingGame.needToDraw) {
                //actual code for the typing game logic


                if (event.type == sf::Event::KeyPressed) {
                    char nextInput = '~'; //place holder character that wont be used
                    if (event.key.code == sf::Keyboard::A) {
                        nextInput = 'a';
                    }
                    else if (event.key.code == sf::Keyboard::B) {
                        nextInput = 'b';
                    }
                    else if (event.key.code == sf::Keyboard::C) {
                        nextInput = 'c';
                    }
                    else if (event.key.code == sf::Keyboard::D) {
                        nextInput = 'd';
                    }
                    else if (event.key.code == sf::Keyboard::E) {
                        nextInput = 'e';
                    }
                    else if (event.key.code == sf::Keyboard::F) {
                        nextInput = 'f';
                    }
                    else if (event.key.code == sf::Keyboard::G) {
                        nextInput = 'g';
                    }
                    else if (event.key.code == sf::Keyboard::H) {
                        nextInput = 'h';
                    }
                    else if (event.key.code == sf::Keyboard::I) {
                        nextInput = 'i';
                    }
                    else if (event.key.code == sf::Keyboard::J) {
                        nextInput = 'j';
                    }
                    else if (event.key.code == sf::Keyboard::K) {
                        nextInput = 'k';
                    }
                    else if (event.key.code == sf::Keyboard::L) {
                        nextInput = 'l';
                    }
                    else if (event.key.code == sf::Keyboard::M) {
                        nextInput = 'm';
                    }
                    else if (event.key.code == sf::Keyboard::N) {
                        nextInput = 'n';
                    }
                    else if (event.key.code == sf::Keyboard::O) {
                        nextInput = 'o';
                    }
                    else if (event.key.code == sf::Keyboard::P) {
                        nextInput = 'p';
                    }
                    else if (event.key.code == sf::Keyboard::Q) {
                        nextInput = 'q';
                    }
                    else if (event.key.code == sf::Keyboard::R) {
                        nextInput = 'r';
                    }
                    else if (event.key.code == sf::Keyboard::S) {
                        nextInput = 's';
                    }
                    else if (event.key.code == sf::Keyboard::T) {
                        nextInput = 't';
                    }
                    else if (event.key.code == sf::Keyboard::U) {
                        nextInput = 'u';
                    }
                    else if (event.key.code == sf::Keyboard::V) {
                        nextInput = 'v';
                    }
                    else if (event.key.code == sf::Keyboard::W) {
                        nextInput = 'w';
                    }
                    else if (event.key.code == sf::Keyboard::X) {
                        nextInput = 'x';
                    }
                    else if (event.key.code == sf::Keyboard::Y) {
                        nextInput = 'y';
                    }
                    else if (event.key.code == sf::Keyboard::Z) {
                        nextInput = 'z';
                    }
                    else if (event.key.code == sf::Keyboard::Space) {
                        nextInput = ' ';
                    }
                    if (placeInCurrentLine < currentLineTint.size() && nextInput == currentLineStringInput.at(placeInCurrentLine)) { //if correct letter
                        string acceptableChars = "abcdefghijklmnopqrstuvwxyz ";
                        
                        placeInCurrentLine++;
                        for (int i = 0; i < wrongKeys.size(); i++) {
                            typingGame.thingsToDraw.find("keyTint" + to_string(wrongKeys.at(i)))->second.setFillColor(sf::Color(255, 255, 255, 255)); //sets wrong letters from red to white
                        }
                        wrongKeys.clear();
                        if (acceptableChars.find(nextInput) != string::npos) {
                            typingGame.thingsToDraw.find("keyTint" + to_string(acceptableChars.find(nextInput)))->second.setFillColor(sf::Color(0, 255, 0, 155)); //sets right key to green
                            wrongKeys.push_back(acceptableChars.find(nextInput)); //uses same thing to reset, oh well
                        }

                    }
                    else { //wrong input
                        string acceptableChars = "abcdefghijklmnopqrstuvwxyz ";
                        if (acceptableChars.find(nextInput) != string::npos) {
                            typingGame.thingsToDraw.find("keyTint" + to_string(acceptableChars.find(nextInput)))->second.setFillColor(sf::Color(255, 0, 0, 155)); //sets wrong key to red
                            wrongKeys.push_back(acceptableChars.find(nextInput));
                        }
                    }
                }
                if (placeInCurrentLine < currentLineTint.size() && typingGame.thingsToDraw.find("acurrentCharTint" + to_string(placeInCurrentLine)) != typingGame.thingsToDraw.end()) {
                    if (placeInCurrentLine >= 1) {
                        typingGame.thingsToDraw.find("acurrentCharTint" + to_string(placeInCurrentLine - 1))->second.setFillColor(sf::Color(40, 40, 40, 155)); //sets old letters to type to grey
                    }
                    typingGame.thingsToDraw.find("acurrentCharTint" + to_string(placeInCurrentLine))->second.setFillColor(sf::Color(255, 255, 0, 255)); //sets current letter to type to yellow
                }
                if (placeInCurrentLine == currentLine.size()) {
                    for (int i = 0; i < currentLine.size(); i++) {
                        typingGame.thingsToDraw.erase("acurrentCharTint" + to_string(i));
                        typingGame.thingsToDraw.erase("currentChar" + to_string(i));
                    }
                    currentLine.clear();
                    currentLineTint.clear();

                    if (differentLines.size() > 1) {
                        srand(time(NULL));
                        int secret = rand() % (differentLines.size());

                        currentLineStringInput = differentLines.at(secret);
                    }
                    turnLowerAndFix(currentLineStringInput);
                   
                    setCurrentLine(currentLineStringInput, currentLine, keys); //sets line of text
                    for (int i = 0; i < currentLine.size(); i++) {
                        typingGame.thingsToDraw.emplace("currentChar" + to_string(i), currentLine.at(i));
                    }
                    for (int i = 0; i < currentLine.size(); i++) {
                        currentLineTint.push_back(greyOrYellowOrWhiteTint);
                        currentLineTint.at(i).setPosition(currentLine.at(i).getPosition()); //pretty much same as above 
                    }
                    for (int i = 0; i < currentLineTint.size(); i++) {
                        typingGame.thingsToDraw.emplace("acurrentCharTint" + to_string(i), currentLineTint.at(i)); //a added for alphabetical order oops
                    }
                    placeInCurrentLine = 0;
                }

            }
           
        }

        window.clear(sf::Color::White);
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




void setKey(vector<sf::RectangleShape>& keys, int referenceKey, int currentKey, int offset) {//used to set a key horizontally, with an offset for the x-axis, y axis not considered and handled manually
    keys.at(currentKey).setPosition(keys.at(referenceKey).getPosition().x + offset, keys.at(referenceKey).getPosition().y);
}

void setCurrentLine(string input, vector<sf::RectangleShape>& output, vector<sf::RectangleShape>& references) {
    string acceptableChars = "abcdefghijklmnopqrstuvwxyz "; //doesnt use uppercase as input
    for (int i = 0; i < input.length(); i++) {
        char currentLetter = input.at(i);
        if (acceptableChars.find(currentLetter) != string::npos) {
            //cout << acceptableChars.find(currentLetter) << endl;
            output.push_back(references.at(acceptableChars.find(currentLetter))); //adds the appropriate letter to the display
            output.at(output.size() - 1).setOutlineThickness(0);
            output.at(output.size() - 1).setSize(sf::Vector2f(40, 40));
            //output.at(output.size() - 1).setOutlineThickness(1);
        }
    }
    if (output.size() >= 1) {
        output.at(0).setPosition(400, 200); //sets first character in sentence
    }
    for (int i = 1; i < output.size(); i++) {
        setKey(output, i - 1, i, 40); //sets rest of sentence, all on one line, big sentences will be bad.
    }   
}
void turnLowerAndFix(string& input) { //turns string to lower case and gets rid of characters that arent yet implemented, eg not lower case or space
    string acceptableChars = "abcdefghijklmnopqrstuvwxyz "; 
    for (int i = 0; i < input.size(); i++) {
        input.at(i) = tolower(input.at(i));
        if (acceptableChars.find(input.at(i)) == string::npos) {
            input.erase(i, 1);
            i--;
        }
    }
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