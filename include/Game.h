#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <sstream>

#include <SFML/Graphics.hpp>

#include "Stack.h"
#include "Constants.h"


class Game
{
    public:
        Game();
        void start();
    protected:

    private:

        sf::RenderWindow window;
        sf::Text scoreText;
        sf::Font mainFont;
        sf::Clock clock;

        sf::RectangleShape menuRect;
        sf::Text menuText;

        sf::RectangleShape scoreRect;
        sf::Text finalScoreText;
        sf::Text scoreInstructionText;

        void updateScore();
        void resetScore();
        void setupScore();

        std::ostringstream scoreStream;

        int score;
        int scoreIncr;

        Stack s;

        bool mainMenu;
        bool scoreMenu;
};

#endif // GAME_H
