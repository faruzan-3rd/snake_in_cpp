#ifndef _SNAKE_H
#define _SNAKE_H

#include "util.h"
#include <queue>
#include <map>


class Snake{
    public:
        Snake();
        Snake(const Coords default_pos, const int default_length, const int max_width, const int max_height);
        Snake(const Snake& source);

        std::deque<Coords> get_body() const;
        void grow();
        void move();
        void set_direction_to(const char new_direction);
        bool crashed();

    private:
        Coords to_safe_coords(Coords old) const;

    private:
        std::deque<Coords> body;
        char cur_dir;
        std::map<char, Coords> direction;
        bool next_pop;
        int mx_width;
        int mx_height;

};



#endif