#ifndef BLOCK_H
#define BLOCK_H

#include <SFML/Graphics.hpp>
#include "Constants.h"
#include <iostream>
#include <cstdlib>

class Block
{
    public:
        Block(float xPos, float yPos, float width);

        void update(float dt);
        void reset(int dir);
        void fall(float dt);

        sf::RectangleShape getShape();
        sf::Vector2f getVel();

        void setColor(const sf::Color& color);
        static sf::Color getNextColor();
        static void resetColors();
        void setPerfect();

    protected:

    private:
        sf::RectangleShape blockShape;
        sf::Vector2f vel;
        sf::Vector2f blockSize;

        static const float gravity;

        static std::vector<sf::Color> getColorGradient(sf::Color c1, sf::Color c2);
        static std::vector<sf::Color> blockColors;
        static int colorIndex;
        static const int numColors;

};

#endif // BLOCK_H
