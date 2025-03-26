#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <list>
#include <string>

#define EPSILON 1e-6

class Vertex {
private:
    _Float32 x;
    _Float32 y;
    _Float32 z;

public:
    Vertex(_Float32 x = 0, _Float32 y = 0, _Float32 z = 0) :
        x(x), y(y), z(z) {}

    bool operator==(const Vertex& other) const;

    bool operator<(const Vertex& other) const;

    _Float32 distance(const Vertex& other) const;

    _Float32 dot(const Vertex& other) const;

    inline _Float32 getX() const { return x ;}
    inline _Float32 getY() const { return y ;}
    inline _Float32 getZ() const { return z ;}

    inline void setX(_Float32 x) { this->x = x; }
    inline void setY(_Float32 y) { this->y = y; }
    inline void setZ(_Float32 z) { this->z = z; }
};

class TRiangle {

};