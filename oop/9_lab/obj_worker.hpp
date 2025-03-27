#pragma once

#include <vector>
#include <unordered_map>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_set>
#include <cmath>
#include <algorithm>
#include <cstdint>

class Point {
private:
    float x, y, z;

public:
    Point(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}

    bool operator==(const Point& other) const;

    Point& operator=(const Point&) = default;

    inline float getX() const;
    inline float getY() const;
    inline float getZ() const;

    struct Hash {
        size_t operator()(const Point& p) const {
            return std::hash<float>()(p.x) ^
                   (std::hash<float>()(p.y) << 1) ^
                   (std::hash<float>()(p.z) << 2);
        }
    };
};

class Triangle {
private:
    uint32_t v1;
    uint32_t v2;
    uint32_t v3;
    uint32_t color;

public:
    Triangle(uint32_t v1 = 0, uint32_t v2 = 0, uint32_t v3 = 0, uint32_t color = 0)
        : v1(v1), v2(v2), v3(v3), color(color) {}

    inline uint32_t getV1() const;
    inline uint32_t getV2() const;
    inline uint32_t getV3() const;
    inline uint32_t getColor() const;

    inline void setV1(uint32_t v);
    inline void setV2(uint32_t v);
    inline void setV3(uint32_t v);
    inline void setColor(uint32_t c);

    inline bool operator<(const Triangle& other) const;

};

class OBJModel {
private:
    std::vector<Point> points;
    std::vector<Triangle> triangles;
    std::unordered_map<Point, size_t, Point::Hash> vertexMap;

    size_t findOrAddVertex(const Point& v);

public:
    bool loadFromFile(const std::string& filename);

    void removeUnusedVertices();

    void merge(const OBJModel& other);

    void setColorOBJ(uint32_t color);

    void sortPoints();

    void sortTriangles();

    const std::vector<Point>& getPoints() const;

    const std::vector<Triangle>& getTriangles() const;

    void saveToFile(const std::string& filename) const;
};