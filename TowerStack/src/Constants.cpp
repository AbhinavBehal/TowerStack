#include "Constants.h"

const int Constants::width = 600;
const int Constants::height = 800;
const int Constants::defaultBlockWidth = 400;
const int Constants::defaultBlockHeight = 20;
const int Constants::numColors = 15;


int Constants::colorIndex = 0;

const float Constants::gravity = 20.f;

std::vector<sf::Color> Constants::getColorGradient(sf::Color c1, sf::Color c2) {

    int n = Constants::numColors;
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

        out.push_back(sf::Color(r, g, b));
    }
    return out;
}

std::vector<sf::Color> Constants::blockColors = Constants::getColorGradient(sf::Color(rand()%256, rand()%256, rand()%256), sf::Color(rand()%256, rand()%256, rand()%256));

sf::Color Constants::getNextColor() {

    if(Constants::colorIndex >= Constants::numColors) {
        Constants::colorIndex = 0;
        Constants::blockColors = Constants::getColorGradient(Constants::blockColors.back(), sf::Color(rand()%256, rand()%256, rand()%256));
    }
    return Constants::blockColors.at(Constants::colorIndex++ % (Constants::numColors));
}

