#include <gtest/gtest.h>
#include <fstream>
#include "obj_worker.hpp"

class OBJModelTest : public ::testing::Test {
protected:
    void SetUp() override {
        createTestFiles();
    }

    void TearDown() override {
        removeTestFiles();
    }

    void createTestFiles() {
        std::ofstream("valid.obj") << "v 0 0 0\nv 1 0 0\nv 0 1 0\nf 1 2 3\nf 2 3 1\n";
        std::ofstream("empty.obj");
    }

    void removeTestFiles() {
        remove("valid.obj");
        remove("empty.obj");
        remove("output.obj");
    }
};

TEST(PointTest, Equality) {
    Point p1(1.0f, 2.0f, 3.0f);
    Point p2(1.0f, 2.0f, 3.0f);
    Point p3(1.1f, 2.0f, 3.0f);
    ASSERT_TRUE(p1 == p2);
    ASSERT_FALSE(p1 == p3);
}

TEST(PointTest, DistanceCalculation) {
    Point p1(0, 0, 0);
    Point p2(3, 4, 0);
    EXPECT_FLOAT_EQ(p1.distance(p2), 5.0f);
}

TEST(TriangleTest, ColorOperations) {
    Triangle t(1, 2, 3);
    t.setColor(0xFF00FF);
    EXPECT_EQ(t.getColor(), 0xFF00FF);
}

TEST_F(OBJModelTest, LoadInvalidFile) {
    OBJModel model;
    EXPECT_FALSE(model.loadFromFile("nonexistent.obj"));
}

TEST_F(OBJModelTest, ColorAssignment) {
    OBJModel model;
    model.loadFromFile("valid.obj");
    model.setColorOBJ(0x00FF00);
    
    for (const auto& t : model.getTriangles()) {
        EXPECT_EQ(t.getColor(), 0x00FF00);
    }
}

TEST_F(OBJModelTest, Sorting) {
    OBJModel model;
    model.loadFromFile("valid.obj");
    model.merge(model);
    
    model.sortPoints();
    const auto& verts = model.getPoints();
    EXPECT_TRUE(std::is_sorted(verts.begin(), verts.end()));
    
    model.sortTriangles();
    const auto& tris = model.getTriangles();
    EXPECT_TRUE(std::is_sorted(tris.begin(), tris.end()));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}