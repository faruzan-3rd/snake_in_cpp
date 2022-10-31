#include "snakeGame.h"
#include "snake.h"
#include "util.h"
#include <queue>
#include <random>
#include <iostream>
#include <SFML/Graphics.hpp>


SnakeGameManager::SnakeGameManager(const int grid_width, const int grid_height, const Coords default_pos, const int default_size,
                                     const float upd_interval, const float apple_probability){
    _width = grid_width;
    _height = grid_height;
    last_update = 0;
    this->apple_probability = apple_probability;
    this->upd_interval = upd_interval;
    this->default_pos = default_pos;
    this->default_size = default_size;

    grid = new char*[_height];

    setup();
}


void SnakeGameManager::setup(){
    for(int i = 0; i < _height; i++) grid[i] = new char[_width]{SnakeGameManager::EMPTY};

    if(snake != nullptr) delete snake;
    snake = new Snake(default_pos, default_size, _width, _height);

    std::random_device seed;
    std::default_random_engine engine(seed());

    gameover = false;
}


SnakeGameManager::~SnakeGameManager(){
    for(int i = 0; i < _height; i++) delete[] grid[i];
    delete[] grid;
}


int SnakeGameManager::get_width() const{
    return this->_width;
}


int SnakeGameManager::get_height() const{
    return this->_height;
}


void SnakeGameManager::draw_grid(sf::RenderWindow& window) const{
    sf::Vector2u size = window.getSize();

    int rend_width {(int)size.x / _width};
    int rend_height {(int)size.y / _height};
    sf::ConvexShape square(4);
    square.setFillColor(sf::Color::Red);

    for(int y = 0; y < _height; y++) for(int x = 0; x < _width; x++){
        if(*(*(grid + y) + x) == SnakeGameManager::APPLE){
            square.setPoint(0, sf::Vector2f(rend_width * x, rend_height * y));
            square.setPoint(1, sf::Vector2f(rend_width * x + rend_width, rend_height * y));
            square.setPoint(2, sf::Vector2f(rend_width * x + rend_width, rend_height * y + rend_height));
            square.setPoint(3, sf::Vector2f(rend_width * x, rend_height * y + rend_height));
            window.draw(square);
        }
    }

    std::deque<Coords> snake_body = snake->get_body();
    square.setFillColor(sf::Color::Green);
    bool first = true;
    for(auto bd = snake_body.begin(); bd != snake_body.end(); bd++){
        int x = bd->x, y = bd->y;
        square.setPoint(0, sf::Vector2f(rend_width * x, rend_height * y));
        square.setPoint(1, sf::Vector2f(rend_width * x + rend_width, rend_height * y));
        square.setPoint(2, sf::Vector2f(rend_width * x + rend_width, rend_height * y + rend_height));
        square.setPoint(3, sf::Vector2f(rend_width * x, rend_height * y + rend_height));
        window.draw(square);
        if(first){
            first = false;
            square.setFillColor(sf::Color::Blue);
        }
    }
}


bool SnakeGameManager::tick(const sf::Time& time){
    if(time.asSeconds() - last_update >= upd_interval && !gameover){
        last_update = time.asSeconds();
        snake->move();
        if(snake->crashed()){
            // GameOver
            std::cout << "Game over! " << std::endl;
            gameover = true;
            return true;
        }
        if(apple_eaten()){
            snake->grow();
        }
        drop_apple();
    }

    return false;
}


void SnakeGameManager::drop_apple(){
    std::uniform_real_distribution<> prob(0, 1.0);

    if(prob(engine) <= apple_probability){
        int j = prob(engine) * _width, i = prob(engine) * _height;
        grid[i][j] = SnakeGameManager::APPLE;
    }
}


void SnakeGameManager::change_direction_to(const char new_direction){
    snake->set_direction_to(new_direction);
}


bool SnakeGameManager::apple_eaten(){
    Coords head = snake->get_body().front();
    if(grid[head.y][head.x] == SnakeGameManager::APPLE){
        grid[head.y][head.x] = SnakeGameManager::EMPTY;
        return true;
    }
    return false;
}


bool SnakeGameManager::is_gameover(){
    return gameover;
}
