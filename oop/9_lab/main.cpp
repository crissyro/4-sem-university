#include "obj_worker.hpp"
#include <iostream>

int main() {
    OBJModel model;

    if (!model.loadFromFile("triangle.obj")) {
        std::cerr << "Failed to load model!" << std::endl;
        return 1;
    }

    model.setColorOBJ(0xFFA500); 
    model.removeUnusedVertices();
    model.sortPoints();
    model.sortTriangles();

    OBJModel additional;
    if (additional.loadFromFile("additional.obj")) {
        additional.setColorOBJ(0x00FF00);
        model.merge(additional);
    }

    model.saveToFile("processed_model.obj");

    std::cout << "Processing complete!\n";
    std::cout << "Final vertex count: " << model.getPoints().size() << "\n";
    std::cout << "Final triangle count: " << model.getTriangles().size() << "\n";

    return 0;
}