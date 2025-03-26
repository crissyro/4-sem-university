CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pthread
GTEST = -lgtest -lgtest_main
INCLUDE = -I.

SRC = obj_worker.cpp
TEST_SRC = tests.cpp
OBJ = $(SRC:.cpp=.o)
TEST_OBJ = $(TEST_SRC:.cpp=.o)
TARGET = obj_test

all: $(TARGET)

$(TARGET): $(OBJ) $(TEST_OBJ)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $^ -o $@ $(GTEST)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

test: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJ) $(TEST_OBJ) $(TARGET)

.PHONY: all test clean