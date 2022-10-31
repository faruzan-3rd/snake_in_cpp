#ifndef _UTIL_H
#define _UTIL_H


const char N{'n'};
const char S{'s'};
const char E{'e'};
const char W{'w'};


struct Coords{
    const Coords operator+(const Coords& right);
    Coords& operator+=(const Coords& right);
    bool operator==(Coords& right);

    int x;
    int y;
};



#endif