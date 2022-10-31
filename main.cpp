#include <SFML/Graphics.hpp>
#include "snakeGame.h"
#include "util.h"


int main(int argc, char const *argv[])
{
    int width{800};
    int height{800};
    sf::RenderWindow window(sf::VideoMode(width, height), "Snake in C++!");

    sf::Font arial;
    arial.loadFromFile("Arial 2.ttf");

    sf::Text gameoverTxt("Game Over!", arial);
    gameoverTxt.setCharacterSize(30);
    gameoverTxt.setStyle(sf::Text::Bold);
    gameoverTxt.setFillColor(sf::Color::Red);
    gameoverTxt.setPosition(width / 2, height / 2);

    int y_offset = 55;
    sf::Text playagainTxt("Press space to play again", arial);
    playagainTxt.setCharacterSize(15);
    playagainTxt.setFillColor(sf::Color::Magenta);
    playagainTxt.setPosition(width / 2, height / 2 + y_offset);

    SnakeGameManager manager(25, 25, Coords{12, 12}, 3, 0.35f, 0.07f);
    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }
        window.clear();

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            manager.change_direction_to(W);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
            manager.change_direction_to(N);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            manager.change_direction_to(E);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
            manager.change_direction_to(S);
        }
        manager.tick(clock.getElapsedTime());
        manager.draw_grid(window);

        if(manager.is_gameover()){
            window.draw(gameoverTxt);
            window.draw(playagainTxt);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
                manager.setup();
            }
        }
        window.display();
        
    }

    return 0;
}