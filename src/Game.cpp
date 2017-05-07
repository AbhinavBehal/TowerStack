#include "Game.h"

Game::Game() :
    window(sf::VideoMode(Constants::width, Constants::height), "TowerStack", sf::Style::Close),
    menuRect({(float)Constants::width, (float)Constants::height}),
    scoreRect({Constants::width * 0.75f, Constants::height * 0.25f}),
    score(0),
    scoreIncr(33),
    mainMenu(true),
    scoreMenu(false)
{
    mainFont.loadFromFile("GOTHIC.ttf");
    scoreText.setFont(mainFont);
    scoreText.setCharacterSize(40);

    score = -scoreIncr;
    updateScore();

    menuRect.setFillColor(sf::Color(s.getTopColor().r, s.getTopColor().g, s.getTopColor().b, 100));
    menuRect.setPosition(Constants::width * 0.5 - menuRect.getSize().x * 0.5, Constants::height * 0.5 - menuRect.getSize().y * 0.5);

    menuText.setFont(mainFont);
    menuText.setString("TowerStack");
    menuText.setFillColor(s.getTopColor());
    menuText.setPosition(menuRect.getPosition().x + 40.f, menuRect.getPosition().y + 30.f);
    menuText.setCharacterSize(50);

    finalScoreText.setFont(mainFont);
    finalScoreText.setCharacterSize(50);

    scoreInstructionText.setFont(mainFont);
    scoreInstructionText.setCharacterSize(50);

    window.setFramerateLimit(240);
    window.setKeyRepeatEnabled(false);
}

void Game::start()
{
    clock.restart();
    while(window.isOpen())
    {
        float dt = clock.restart().asSeconds();

        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();

            if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::Space && !mainMenu && !scoreMenu)
                {
                    if(!s.add()){
                        setupScore();
                        resetScore();
                        scoreMenu = true;
                    } else {
                        updateScore();

                    }
                }
                else if(event.key.code == sf::Keyboard::Space && mainMenu)
                {
                    mainMenu = false;
                }
                else if(event.key.code == sf::Keyboard::Space && scoreMenu)
                {
                    s.reset();
                    resetScore();
                    scoreMenu = false;
                    window.setView(window.getDefaultView());
                }
            }
        }

        window.clear(sf::Color::White);

        s.draw(window, dt);
        if(!mainMenu && !scoreMenu) {
            s.update(dt);
            scoreText.setPosition(window.getView().getCenter().x - scoreText.getGlobalBounds().width * 0.5f, window.getView().getCenter().y - window.getView().getSize().y * 0.5f);
            window.draw(scoreText);
        }
        if(mainMenu) {
            window.draw(menuRect);
            window.draw(menuText);
        }
        if(scoreMenu) {
            window.draw(scoreRect);
            window.draw(finalScoreText);
            window.draw(scoreInstructionText);
        }

        window.display();
    }
}

void Game::updateScore()
{
    score += scoreIncr;
    scoreStream << score;

    scoreText.setString(scoreStream.str());
    scoreText.setFillColor(s.getTopColor());

    scoreStream.str("");
    scoreStream.clear();
}

void Game::resetScore()
{
    score = 0;
    scoreStream << score;

    scoreText.setString(scoreStream.str());
    scoreText.setFillColor(s.getTopColor());

    scoreStream.str("");
    scoreStream.clear();
}

void Game::setupScore()
{
    scoreRect.setPosition(window.getView().getCenter().x - scoreRect.getSize().x * 0.5, window.getView().getCenter().y - scoreRect.getSize().x * 0.5 - 100);
    scoreRect.setFillColor(sf::Color(s.getTopColor().r, s.getTopColor().g, s.getTopColor().b, 100));

    finalScoreText.setString(scoreText.getString());
    finalScoreText.setFillColor(sf::Color::White);
    finalScoreText.setPosition(scoreRect.getPosition().x + scoreRect.getSize().x * 0.5 - finalScoreText.getGlobalBounds().width * 0.5,
                               scoreRect.getPosition().y + 10.f);

    scoreInstructionText.setString("Space to restart");
    scoreInstructionText.setFillColor(s.getTopColor());
    scoreInstructionText.setPosition(scoreRect.getPosition().x + scoreRect.getSize().x * 0.5 - scoreInstructionText.getGlobalBounds().width * 0.5,
                                     scoreRect.getPosition().y + scoreRect.getSize().y - scoreInstructionText.getGlobalBounds().height - 30.f);
}
