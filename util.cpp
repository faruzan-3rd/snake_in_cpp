#include "util.h"


const Coords Coords::operator+(const Coords& right){
    Coords cd;
    cd.x = this->x + right.x;
    cd.y = this->y + right.y;

    return cd;
}

Coords& Coords::operator+=(const Coords& right){
    (*this) = (*this) + right;
    return *this;
}


const Coords operator*(const Coords& left, const int& right){
    Coords cd {left};
    cd.x *= right;
    cd.y *= right;
    return cd;
}

const Coords operator*(const int& left, Coords& right){
    return right * left;
}


bool Coords::operator==(Coords& right){
    return x == right.x && y == right.y;
}


