<<<<<<< HEAD
#include "Stack.h"

Stack::Stack()
{
    reset();
    std::cout << (int)blocks.back().getShape().getFillColor().r << std::endl;
    viewVel = 200.f;
    xTol = 5;
}

void Stack::draw(sf::RenderWindow& window, float dt)
{
    for(Block& b : blocks)
    {
        window.draw(b.getShape());
    }

    if(blocks.back().getShape().getPosition().y < window.getSize().y / 2)
    {
        sf::View view = window.getView();

        if(view.getCenter().y > blocks.back().getShape().getPosition().y)
            view.move(0,  -viewVel * dt);
        if(view.getCenter().y < blocks.back().getShape().getPosition().y)
            view.setCenter(view.getCenter().x, blocks.back().getShape().getPosition().y);

        window.setView(view);
    }

    for(std::vector<sf::Color>::size_type i = 0; i < brokenBlocks.size(); ++i)///Using range for loop caused crashes when holding down space
    {
        brokenBlocks.at(i).fall(dt);
        if(brokenBlocks.at(i).getShape().getPosition().y > window.getView().getCenter().y + window.getView().getSize().y * 0.5)
        {
            std::swap(brokenBlocks.at(i), brokenBlocks.back());
            brokenBlocks.pop_back();
        }
    }

    for(Block& b : brokenBlocks)
    {
        window.draw(b.getShape());
    }
}

void Stack::update(float dt)
{
    blocks.back().update(dt);
}

bool Stack::add()
{
    sf::Vector2f newPos = blocks.back().getShape().getPosition();
    sf::Vector2f topPos = blocks.at(blocks.size() - 2).getShape().getPosition();
    int dx = abs(topPos.x - newPos.x);

    int newWidth = 0;
    int brokenWidth = 0;
    int newX = 0;
    int brokenX = 0;
    bool perfect = false;

    int dir = blocks.back().getVel().x > 0 ? 1 : -1;

    if(dx <= xTol) {
        newWidth = blocks.back().getShape().getSize().x;
        newX = topPos.x;
        perfect = true;
    } else {
        newWidth = blocks.back().getShape().getSize().x - dx;
        brokenWidth = newWidth - blocks.back().getShape().getSize().x;

        newX = 0;
        brokenX = 0;

        if(newPos.x < topPos.x) {
            newX = topPos.x;
            brokenX = newX;
        }
        else if(newPos.x >= topPos.x) {
            newX = newPos.x;
            brokenX = newX + newWidth - brokenWidth;
        }

        if(newWidth <= 0)
        {
            std::cout << "Game Over" << std::endl;
            //reset();
            return false;
        }
    }

    sf::Color old = blocks.back().getShape().getFillColor();

    blocks.back() = Block(newX, newPos.y + Constants::defaultBlockHeight, newWidth);
    blocks.back().setColor(old);
    if(perfect) {
        blocks.back().setPerfect();
    }

    blocks.push_back(Block(newX, newPos.y, newWidth));
    blocks.back().reset(dir);
    blocks.back().setColor(Block::getNextColor());

    if(!perfect) {
        brokenBlocks.push_back(Block(brokenX, newPos.y + Constants::defaultBlockHeight, brokenWidth));
        brokenBlocks.back().setColor(old);
    }

    return true;
}

void Stack::reset()
{
    blocks.clear();
    blocks.shrink_to_fit();

    Block::resetColors();

    blocks.push_back(Block(Constants::width/2 - Constants::defaultBlockWidth / 2, Constants::height, Constants::defaultBlockWidth));
    blocks.back().setColor(Block::getNextColor());
    blocks.push_back(Block(Constants::width/2 - Constants::defaultBlockWidth / 2, Constants::height - Constants::defaultBlockHeight, Constants::defaultBlockWidth));
    blocks.back().setColor(Block::getNextColor());
}

sf::Color Stack::getTopColor() { return blocks.back().getShape().getFillColor(); }
=======
#include "Stack.h"

Stack::Stack()
{
    reset();
    viewVel = 200.f;
    xTol = 5;
}

void Stack::draw(sf::RenderWindow& window, float dt)
{
    for(Block& b : blocks)
    {
        window.draw(b.getShape());
    }

    if(blocks.back().getShape().getPosition().y < window.getSize().y / 2)
    {
        sf::View view = window.getView();

        if(view.getCenter().y > blocks.back().getShape().getPosition().y)
            view.move(0,  -viewVel * dt);
        if(view.getCenter().y < blocks.back().getShape().getPosition().y)
            view.setCenter(view.getCenter().x, blocks.back().getShape().getPosition().y);

        window.setView(view);
    }

    for(std::vector<sf::Color>::size_type i = 0; i < brokenBlocks.size(); ++i)///Using range for loop caused crashes when holding down space
    {
        brokenBlocks.at(i).fall(dt);
        if(brokenBlocks.at(i).getShape().getPosition().y > window.getView().getCenter().y + window.getView().getSize().y * 0.5)
        {
            std::swap(brokenBlocks.at(i), brokenBlocks.back());
            brokenBlocks.pop_back();
        }
    }

    for(Block& b : brokenBlocks)
    {
        window.draw(b.getShape());
    }
}

void Stack::update(float dt)
{
    blocks.back().update(dt);
}

bool Stack::add()
{
    sf::Vector2f newPos = blocks.back().getShape().getPosition();
    sf::Vector2f topPos = blocks.at(blocks.size() - 2).getShape().getPosition();
    int dx = abs(topPos.x - newPos.x);

    int newWidth = 0;
    int brokenWidth = 0;
    int newX = 0;
    int brokenX = 0;
    bool perfect = false;

    int dir = blocks.back().getVel().x > 0 ? 1 : -1;

    if(dx <= xTol) {
        newWidth = blocks.back().getShape().getSize().x;
        newX = topPos.x;
        perfect = true;
    } else {
        newWidth = blocks.back().getShape().getSize().x - dx;
        brokenWidth = newWidth - blocks.back().getShape().getSize().x;

        newX = 0;
        brokenX = 0;

        if(newPos.x < topPos.x) {
            newX = topPos.x;
            brokenX = newX;
        }
        else if(newPos.x >= topPos.x) {
            newX = newPos.x;
            brokenX = newX + newWidth - brokenWidth;
        }

        if(newWidth <= 0)
        {
            return false;
        }
    }

    sf::Color old = blocks.back().getShape().getFillColor();

    blocks.back() = Block(newX, newPos.y + Constants::defaultBlockHeight, newWidth);
    blocks.back().setColor(old);
    if(perfect) {
        blocks.back().setPerfect();
    }

    blocks.push_back(Block(newX, newPos.y, newWidth));
    blocks.back().reset(dir);
    blocks.back().setColor(Block::getNextColor());

    if(!perfect) {
        brokenBlocks.push_back(Block(brokenX, newPos.y + Constants::defaultBlockHeight, brokenWidth));
        brokenBlocks.back().setColor(old);
    }

    return true;
}

void Stack::reset()
{
    blocks.clear();
    blocks.shrink_to_fit();

    Block::resetColors();

    blocks.push_back(Block(Constants::width/2 - Constants::defaultBlockWidth / 2, Constants::height, Constants::defaultBlockWidth));
    blocks.back().setColor(Block::getNextColor());
    blocks.push_back(Block(Constants::width/2 - Constants::defaultBlockWidth / 2, Constants::height - Constants::defaultBlockHeight, Constants::defaultBlockWidth));
    blocks.back().setColor(Block::getNextColor());
}

sf::Color Stack::getTopColor() { return blocks.back().getShape().getFillColor(); }
>>>>>>> Readme updates and bug fixes
