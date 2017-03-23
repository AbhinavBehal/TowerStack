#include <iostream>
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Block.h"
#include "Stack.h"
#include <ctime>
#include <cstdlib>

int main()
{
    srand(time(0));

    sf::RenderWindow window(sf::VideoMode(Constants::width, Constants::height), "TowerStack", sf::Style::Close);
    window.setFramerateLimit(240);

    Stack s;

    sf::Clock clock;

    while(window.isOpen())
    {
        float dt = clock.restart().asSeconds();
        std::cout << 1.0 / dt << std::endl;
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
            if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::Space)
                {
                    if(!s.add()){
                        window.setView(window.getDefaultView());
                    }

                }
            }
        }
        window.clear(sf::Color::White);

        s.update(dt);
        s.draw(window, dt);

        window.display();
    }
}
