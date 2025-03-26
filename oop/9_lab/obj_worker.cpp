#include "obj_worker.hpp"

_Float32 Point::distance(const Point& other) const {
    _Float32 dx = x - other.x;
    _Float32 dy = y - other.y;
    _Float32 dz = z - other.z;

    return std::sqrt(dx * dx + dy * dy + dz * dz);
}

inline _Float32 Point::getX() const {
    return x;
}

inline _Float32 Point::getY() const {
    return y;
}

inline _Float32 Point::getZ() const {
    return z;
}

inline void Point::setX(_Float32 x) {
    this->x = x;
}

inline void Point::setY(_Float32 y) {
    this->y = y;
}

inline void Point::setZ(_Float32 z) {
    this->z = z;
}

bool Point::operator==(const Point& other) const noexcept {
    return x == other.x && y == other.y && z == other.z;
}

bool Point::operator<(const Point& other) const noexcept {
    if (x != other.x) {
        return x < other.x;
    }

    if (y != other.y) {
        return y < other.y;
    }

    return z < other.z;
}

_Float32 Point::dot(const Point& other) const {
    return x * other.x + y * other.y + z * other.z;
}

bool Triangle::operator==(const Triangle& other) const {
    return (v1 == other.v1 && v2 == other.v2 && v3 == other.v3);
}

inline uint32_t Triangle::getV1() const {
    return v1;
}

inline uint32_t Triangle::getV2() const {
    return v2;
} 

inline uint32_t Triangle::getV3() const {
    return v3;
} 

inline uint32_t Triangle::getColor() const {
    return color;
}

inline void Triangle::setV1(uint32_t v1) {
    this->v1 = v1;
}

inline void Triangle::setV2(uint32_t v2) {
    this->v2 = v2;
}

inline void Triangle::setV3(uint32_t v3) {
    this->color = v3;
}

inline void Triangle::setColor(uint32_t color) {
    this->color = color;
}

bool Triangle::operator<(const Triangle& other) const {
    return (v1 < other.v1) || 
          (v1 == other.v1 && (v2 < other.v2 || 
          (v2 == other.v2 && v3 < other.v3)));
}

bool OBJModel::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    points.clear();
    triangles.clear();

    std::string line;
    while (std::getline(file, line)) {
        if (line.substr(0, 2) == "v ") {
            std::istringstream iss(line.substr(2));
            float x, y, z;
            if (iss >> x >> y >> z) {
                points.emplace_back(x, y, z);
            }
        } else if (line.substr(0, 2) == "f ") {
            std::istringstream iss(line.substr(2));
            int v1, v2, v3;
            
            if (iss >> v1 >> v2 >> v3) {
                triangles.emplace_back(v1-1, v2-1, v3-1, 0);
            }
        }
    }
    return true;
}

int OBJModel::findOrAddVertex(const Point& v) {
    static std::unordered_map<Point, int> vertexMap;
    auto it = vertexMap.find(v);

    if (it != vertexMap.end()) {
        return it->second;
    }

    points.push_back(v);

    int index = points.size() - 1;
    vertexMap[v] = index;

    return index;
}

void OBJModel::setColorOBJ(uint32_t color) {
    for (auto& t : triangles) {
        t.setColor(color);
    }
}


void OBJModel::merge(OBJModel& other) {
    std::vector<int> indexMap;
    for (const auto& v : other.points) {
        indexMap.push_back(findOrAddVertex(v));
    }

    for (auto& t : other.triangles) {
        triangles.emplace_back(
            indexMap[t.getV1()],
            indexMap[t.getV2()],
            indexMap[t.getV3()],
            t.getColor()
        );
    }
}

void OBJModel::print() const {
    std::cout << "Vertices (" << points.size() << "):\n";

    for (const auto& p : points) {
        std::cout << "v " << p.getX() << " " << p.getY() << " " << p.getZ() << "\n";
    }

    std::cout << "\nTriangles (" << triangles.size() << "):\n";

    for (const auto& t : triangles) {
        std::cout << "f " << t.getV1() + 1 << " " << t.getV2() + 1 << " " << t.getV3() + 1
                  << " Color: 0x" << std::hex << t.getColor() << std::dec << "\n";
    }
}

const std::list<Point>& OBJModel::getPoints() const {
    return points;
}

const std::list<Triangle>& OBJModel::getTriangles() const {
    return triangles;
}

void OBJModel::sortPoints() {
    points.sort();
}

void OBJModel::sortTriangles() {
    triangles.sort();
}