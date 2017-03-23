#include "Block.h"

Block::Block(float xPos, float yPos, float width)
{
    blockSize.x = width;
    blockSize.y = Constants::defaultBlockHeight;
    blockShape.setSize(blockSize);
    blockShape.setPosition(xPos, yPos - blockSize.y);

    blockShape.setOutlineColor(sf::Color(51, 51, 51));
    blockShape.setOutlineThickness(-1.f);

    vel.x = 300.f;
    vel.y = 500.f;
}

void Block::update(float dt)
{
    blockShape.move(vel.x * dt, 0);

    if(blockShape.getPosition().x + blockSize.x > Constants::width)
    {
        vel.x *= -1;
        vel.y *= -1;
        blockShape.setPosition(Constants::width - blockSize.x, blockShape.getPosition().y);
    }
    else if(blockShape.getPosition().x < 0)
    {
        vel.x *= -1;
        vel.y *= -1;
        blockShape.setPosition(0, blockShape.getPosition().y);
    }
}

void Block::fall(float dt)
{
    vel.y += Constants::gravity * dt;
    blockShape.move(0, vel.y * dt);
}

void Block::setColor(const sf::Color& color) { blockShape.setFillColor(color); }

void Block::reset(int dir)
{
    if(dir > 0) {
        blockShape.setPosition(Constants::width - blockSize.x, blockShape.getPosition().y);
        vel.x *= -1;
    } else {
        blockShape.setPosition(0, blockShape.getPosition().y);
    }
}

sf::RectangleShape Block::getShape() { return blockShape; }

sf::Vector2f Block::getVel() { return vel; }
