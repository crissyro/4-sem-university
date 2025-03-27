#include <gtest/gtest.h>
#include <fstream>
#include "obj_worker.hpp"

class OBJModelTest : public ::testing::Test {
protected:
    void SetUp() override {
        createComplexTestFile();
    }

    void TearDown() override {
        remove("complex_input.obj");
        remove("processed.obj");
    }

    void createComplexTestFile() {
        std::ofstream f("complex_input.obj");
        f << "# Complex model with normals\n";
        for(int i = 0; i < 1000; ++i) {
            f << "v " << i << " " << i+1 << " " << i+2 << "\n";
            f << "vn " << 0 << " " << 0 << " " << 1 << "\n";
        }
        for(int i = 1; i <= 997; ++i) {
            f << "f " << i << "//" << i << " " 
              << i+1 << "//" << i+1 << " " 
              << i+2 << "//" << i+2 << "\n";
        }
    }
};

TEST_F(OBJModelTest, CleanProcessing) {
    OBJModel model;
    
    ASSERT_TRUE(model.loadFromFile("complex_input.obj"));
    
    ASSERT_EQ(model.getPoints().size(), 1000);
    ASSERT_EQ(model.getTriangles().size(), 997 * 1); 

    model.removeUnusedVertices();
    model.sortPoints();
    model.sortTriangles();
    
    model.saveToFile("processed.obj");

    std::ifstream out("processed.obj");
    std::string line;
    int vertex_count = 0;
    int normal_count = 0;
    int face_count = 0;

    while(std::getline(out, line)) {
        if(line.substr(0, 2) == "v ") vertex_count++;
        if(line.substr(0, 3) == "vn ") normal_count++;
        if(line.substr(0, 2) == "f ") face_count++;
    }

    EXPECT_EQ(normal_count, 0) << "All normals should be removed";
    EXPECT_EQ(vertex_count, model.getPoints().size());
    EXPECT_EQ(face_count, model.getTriangles().size());
    
    auto& verts = model.getPoints();
    for(size_t i = 1; i < verts.size(); ++i) {
        ASSERT_FALSE(verts[i-1] == verts[i]) 
            << "Duplicate vertices at positions " 
            << i-1 << " and " << i;
    }
}

TEST_F(OBJModelTest, ColorPersistence) {
    OBJModel model;
    model.loadFromFile("complex_input.obj");
    
    model.setColorOBJ(0xFFA500);

    for(const auto& t : model.getTriangles()) {
        ASSERT_EQ(t.getColor(), 0xFFA500);
    }
    
    model.merge(model);
    model.removeUnusedVertices();
    
    for(const auto& t : model.getTriangles()) {
        EXPECT_EQ(t.getColor(), 0xFFA500);
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}