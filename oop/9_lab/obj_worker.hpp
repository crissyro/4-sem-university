#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <list>
#include <unordered_map>
#include <functional> 
#include <string>
#include <cstdint>  
#include <sstream>

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

    bool operator==(const Point& other) const noexcept;

    bool operator<(const Point& other) const noexcept ;

    _Float32 distance(const Point& other) const;

    _Float32 dot(const Point& other) const;

    inline _Float32 getX() const;
    inline _Float32 getY() const;
    inline _Float32 getZ() const;

    inline void setX(_Float32 x);
    inline void setY(_Float32 y);
    inline void setZ(_Float32 z);
};

class Triangle {
private:
    uint32_t v1;
    uint32_t v2;
    uint32_t v3;
    uint32_t color;

public: 
    Triangle(uint32_t v1 = 0, uint32_t v2 = 0, uint32_t v3 = 0, uint32_t color = 0) :
        v1(v1), v2(v2), v3(v3), color(color) {}

    ~Triangle() = default;

    bool operator==(const Triangle& other) const;
    bool operator<(const Triangle& other) const;

    inline uint32_t getV1() const; 
    inline uint32_t getV2() const; 
    inline uint32_t getV3() const; 
    inline uint32_t getColor() const; 

    inline void setV1(uint32_t v1); 
    inline void setV2(uint32_t v2);
    inline void setV3(uint32_t v3);
    inline void setColor(uint32_t color);
};

template<> struct std::hash<Point> {
    size_t operator()(const Point& p) const noexcept {
        return hash<float>()(p.getX()) ^ 
              (hash<float>()(p.getY()) << 1) ^ 
              (hash<float>()(p.getZ()) << 2);
    }
};

class OBJModel {
private:
    std::list<Point> points;
    std::list<Triangle> triangles;

    int findOrAddVertex(const Point& v);

public:
    OBJModel() = default;
    ~OBJModel() = default;

    bool loadFromFile(const std::string& filename);
    void setColorOBJ(const u_int32_t color);
    void merge(OBJModel& other);
    void sortPoints();
    void sortTriangles();
    void print() const;

    const std::list<Triangle>& getTriangles() const;
    const std::list<Point>& getPoints() const;
};