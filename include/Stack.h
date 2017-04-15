#ifndef STACK_H
#define STACK_H

#include "Block.h"
#include "Constants.h"
#include <iostream>
#include <cmath>

class Stack
{
    public:
        Stack();

        void draw(sf::RenderWindow& window, float dt);
        bool add();
        void update(float dt);
        void reset();
        sf::Color getTopColor();

    protected:

    private:
        std::vector<Block> blocks;
        std::vector<Block> brokenBlocks;
        int viewVel;

        int xTol;
};

#endif // STACK_H
