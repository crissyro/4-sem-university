#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <list>
#include <string>

#define EPSILON 1e-6

class Point {
private:
    _Float32 x;
    _Float32 y;
    _Float32 z;

public:
    Point(_Float32 x = 0, _Float32 y = 0, _Float32 z = 0) :
        x(x), y(y), z(z) {}

    ~Point() = default;

    bool operator==(const Point& other) const;

    bool operator<(const Point& other) const;

    _Float32 distance(const Point& other) const;

    _Float32 dot(const Point& other) const;

    inline _Float32 getX() const { return x ;}
    inline _Float32 getY() const { return y ;}
    inline _Float32 getZ() const { return z ;}

    inline void setX(_Float32 x) { this->x = x; }
    inline void setY(_Float32 y) { this->y = y; }
    inline void setZ(_Float32 z) { this->z = z; }
};

class Triangle {
private:
    u_int32_t v1;
    u_int32_t v2;
    u_int32_t v3;
    u_int32_t color;

public: 
    Triangle(u_int32_t v1 = 0, u_int32_t v2 = 0, u_int16_t v3 = 0) :
        v1(v1), v2(v2), v3(v3), color(0) {}

    ~Triangle() = default;

    bool operator==(const Triangle& other) const;
    bool operator<(const Triangle& other) const;

    inline u_int32_t getV1() const { return v1; }
    inline u_int32_t getV2() const { return v2; }
    inline u_int32_t getV3() const { return v3; }
    inline u_int32_t getColor() const { return color; }

    inline void setV1(u_int32_t v1) { this->v1 = v1; }
    inline void setV2(u_int32_t v2) { this->v2 = v2; }
    inline void setV3(u_int32_t v3) { this->v3 = v3; }
    inline void setColor(u_int32_t color) { this->color = color; }
};

class OBJModel {
private:
    std::list<Point> vertices;
    std::list<Triangle> triangles;

    size_t findOrAddVertex(const Point& v);

public:
    OBJModel() = default;
    ~OBJModel() = default;

    bool loadFromFile(const std::string& filename);
    void saveToFile(const std::string& filename) const;
    inline void setColor(const u_int32_t color);
    void merge(OBJModel& other);
    void sortVertices();
    void sortTriangles();
    void print() const;
};