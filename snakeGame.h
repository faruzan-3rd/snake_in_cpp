#ifndef _SNAKEGAME_H
#define _SNAKEGAME_H


#include "util.h"
#include "snake.h"
#include <SFML/Graphics.hpp>
#include <random>


class SnakeGameManager{
    public:
        static const char EMPTY {'e'};
        static const char APPLE {'a'};

        SnakeGameManager(const int grid_width, const int grid_height, const Coords default_pos, const int default_size,
                         const float upd_interval, const float apple_probability);
        ~SnakeGameManager();

        int get_width() const;
        int get_height() const;
        void draw_grid(sf::RenderWindow& window) const;
        bool tick(const sf::Time& time);
        void drop_apple();
        void change_direction_to(const char new_direction);
        bool apple_eaten();
        void setup();
        bool is_gameover();

    private:
        int _width;
        int _height;
        Coords default_pos;
        int default_size;
        char** grid;
        Snake* snake{};
        float last_update;
        float upd_interval;
        float apple_probability;
        std::default_random_engine engine;
        bool gameover;
};


#endif