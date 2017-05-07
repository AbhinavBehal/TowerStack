#include "Block.h"

const int Block::numColors = 12;

int Block::colorIndex = 0;

const float Block::gravity = 1000.f;

std::vector<sf::Color> Block::getColorGradient(sf::Color c1, sf::Color c2) {
    int n = Block::numColors;
    if(n <= 1)
        return std::vector<sf::Color>{c1};
    else if(n == 2)
        return std::vector<sf::Color>{c1, c2};

    std::vector<sf::Color> out;
    for(int i = 1; i <= n; ++i)
    {
        float w = (1-(float)(i-1)/(n-1));

        int r = (w)*c1.r + (1-w)*c2.r;
        int g = (w)*c1.g + (1-w)*c2.g;
        int b = (w)*c1.b + (1-w)*c2.b;

        out.push_back(sf::Color(r, g, b, 140));
    }
    return out;
}

void Block::resetColors() {
    Block::colorIndex = 0;
    Block::blockColors = Block::getColorGradient(sf::Color(rand()%256, rand()%256, rand()%256), sf::Color(rand()%256, rand()%256, rand()%256));
}

std::vector<sf::Color> Block::blockColors = Block::getColorGradient(sf::Color(rand() % 256, rand() % 256, rand() % 256), sf::Color(rand() % 256, rand() % 256, rand() % 256));

sf::Color Block::getNextColor() {

    if(Block::colorIndex >= Block::numColors) {
        Block::colorIndex = 0;
        Block::blockColors = Block::getColorGradient(Block::blockColors.back(), sf::Color(rand()%256, rand()%256, rand()%256));
    }
    return Block::blockColors.at(Block::colorIndex++ % (Block::numColors));
}

Block::Block(float xPos, float yPos, float width)
{
    blockSize.x = width;
    blockSize.y = Constants::defaultBlockHeight;
    blockShape.setSize(blockSize);
    blockShape.setPosition(xPos, yPos - blockSize.y);

    blockShape.setOutlineColor(sf::Color(255,255,255));
    blockShape.setOutlineThickness(-1.0f);

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
    vel.y += Block::gravity * dt;
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

void Block::setPerfect()
{
    sf::Color current = blockShape.getFillColor();
    blockShape.setFillColor(sf::Color(current.r, current.g, current.b));
}
