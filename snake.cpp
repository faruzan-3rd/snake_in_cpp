#include "snake.h"
#include "util.h"
#include <queue>
#include <iostream>


Snake::Snake(const Coords default_pos, const int default_length, const int max_width, const int max_height){
    mx_width = max_width;
    mx_height = max_height;
    direction = {{N, Coords{0, -1}}, {S, Coords{0, 1}}, {E, Coords{1, 0}}, {W, Coords{-1, 0}}};
    Coords cur_body = to_safe_coords(default_pos);
    const Coords nxt {direction[W]};
    cur_dir = E;
    next_pop = true;
    
    for(int i = 0; i < default_length; i++){
        body.push_back(cur_body);
        cur_body = to_safe_coords(cur_body + nxt);
    }
}


std::deque<Coords> Snake::get_body() const{
    return body;
}


void Snake::grow(){
    next_pop = false;
}


void Snake::move(){
    Coords head {body.front()};
    head = to_safe_coords(head + direction[cur_dir]);
    body.push_front(head);

    if(next_pop){
        body.pop_back();
    }else{
        next_pop = true;
    }
}


void Snake::set_direction_to(const char new_direction){
    cur_dir = new_direction;
}


Coords Snake::to_safe_coords(Coords old) const{
    old.x = ((old.x % mx_width) + mx_width) % mx_width;
    old.y = ((old.y % mx_height) + mx_height) % mx_height;
    return old;
}


bool Snake::crashed(){
    Coords head {body.front()};

    for(auto bd {body.begin() + 1}; bd != body.end(); bd++){
        if(*bd == head){
            return true;
        }
    }

    return false;
}
