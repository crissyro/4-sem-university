#include "obj_worker.hpp"


bool Point::operator==(const Point& other) const {
    return std::abs(x - other.x) < 1e-6 &&
           std::abs(y - other.y) < 1e-6 &&
           std::abs(z - other.z) < 1e-6;
}

inline float Point::getX() const { 
    return x; 
}

inline float Point::getY() const { 
    return y; 
}

inline float Point::getZ() const { 
    return z; 
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

inline void Triangle::setV1(uint32_t v) { 
    v1 = v; 
}

inline void Triangle::setV2(uint32_t v) { 
    v2 = v; 
}

inline void Triangle::setV3(uint32_t v) { 
    v3 = v; 
}

inline void Triangle::setColor(uint32_t c) { 
    color = c; 
}

inline bool Triangle::operator<(const Triangle& other) const {
    return std::tie(v1, v2, v3) < std::tie(other.v1, other.v2, other.v3);
}

size_t OBJModel::findOrAddVertex(const Point& v) {
    auto it = vertexMap.find(v);
    if (it != vertexMap.end()) return it->second;
    
    points.push_back(v);
    vertexMap[v] = points.size() - 1;
    return points.size() - 1;
}


bool OBJModel::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) return false;

    points.clear();
    triangles.clear();
    vertexMap.clear();

    std::string line;
    while (std::getline(file, line)) {
        if (line.substr(0, 2) == "v ") {
            std::istringstream iss(line.substr(2));
            float x, y, z;
            if (iss >> x >> y >> z) {
                points.emplace_back(x, y, z);
            }
        }
        else if (line.substr(0, 2) == "f ") {
            std::istringstream iss(line.substr(2));
            std::vector<uint32_t> face;
            std::string token;

            while (iss >> token) {
                size_t pos = token.find('/');
                if (pos != std::string::npos) token = token.substr(0, pos);
                
                try {
                    int idx = std::stoi(token);
                    if (idx < 0) idx = points.size() + idx + 1;
                    if (idx > 0) face.push_back(static_cast<uint32_t>(idx - 1));
                }
                catch (...) {}
            }

            if (face.size() >= 3) {
                for (size_t i = 2; i < face.size(); ++i) {
                    triangles.emplace_back(face[0], face[i-1], face[i]);
                }
            }
        }
    }
    return true;
}

void OBJModel::removeUnusedVertices() {
    std::unordered_set<size_t> used;
    for(const auto& t : triangles) {
        if(t.getV1() < points.size()) {
            used.insert(t.getV1());
        }

        if(t.getV2() < points.size()) {
            used.insert(t.getV2());
        }
        
        if(t.getV3() < points.size()) {
            used.insert(t.getV3());
        }
    }

    std::vector<Point> newPoints;
    std::vector<size_t> indexMap(points.size());
    size_t newIndex = 0;

    for (size_t i = 0; i < points.size(); ++i) {
        if (used.count(i)) {
            indexMap[i] = newIndex++;
            newPoints.push_back(points[i]);
        }
    }

    for (auto& t : triangles) {
        t.setV1(indexMap[t.getV1()]);
        t.setV2(indexMap[t.getV2()]);
        t.setV3(indexMap[t.getV3()]);
    }

    points = std::move(newPoints);
    vertexMap.clear();
    for (size_t i = 0; i < points.size(); ++i) {
        vertexMap[points[i]] = i;
    }
}

void OBJModel::setColorOBJ(uint32_t color) {
    for (auto& t : triangles) t.setColor(color);
}

void OBJModel::merge(const OBJModel& other) {
    std::vector<size_t> indexMap(other.points.size());
    
    for(size_t i = 0; i < other.points.size(); ++i) {
        indexMap[i] = findOrAddVertex(other.points[i]);
    }

    for(const auto& t : other.triangles) {
        triangles.emplace_back(
            indexMap[t.getV1()],
            indexMap[t.getV2()],
            indexMap[t.getV3()],
            t.getColor()
        );
    }
}

void OBJModel::sortPoints() {
    std::sort(points.begin(), points.end(), 
        [](const Point& a, const Point& b) {
            float ax = a.getX(), ay = a.getY(), az = a.getZ();
            float bx = b.getX(), by = b.getY(), bz = b.getZ();
            return std::tie(ax, ay, az) < std::tie(bx, by, bz);
        });
}

void OBJModel::sortTriangles() {
    std::sort(triangles.begin(), triangles.end());
}

const std::vector<Point>& OBJModel::getPoints() const { 
    return points; 
}

const std::vector<Triangle>& OBJModel::getTriangles() const { 
    return triangles; 
}

void OBJModel::saveToFile(const std::string& filename) const {
    std::ofstream out(filename);
    for (const auto& p : points) {
        out << "v " << p.getX() << " " << p.getY() << " " << p.getZ() << "\n";
    }
    for (const auto& t : triangles) {
        out << "f " << t.getV1()+1 << " " << t.getV2()+1 << " " << t.getV3()+1 << "\n";
    }
}