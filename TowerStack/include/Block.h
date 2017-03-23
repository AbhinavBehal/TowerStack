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
        void setColor(const sf::Color& color);

        sf::RectangleShape getShape();

        sf::Vector2f getVel();

    protected:

    private:
        sf::RectangleShape blockShape;
        sf::Vector2f vel;
        sf::Vector2f blockSize;
};

#endif // BLOCK_H
