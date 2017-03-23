#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>

class Constants
{
    public:
        static const int width;
        static const int height;
        static const int defaultBlockWidth;
        static const int defaultBlockHeight;
        static const int numColors;

        static const float gravity;

        static std::vector<sf::Color> blockColors;

        static int colorIndex;

        static sf::Color getNextColor();

    protected:

    private:
        static std::vector<sf::Color> getColorGradient(sf::Color c1, sf::Color c2);
};

#endif // CONSTANTS_H
