CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pthread
LDFLAGS = -pthread -lstdc++ -lgtest -lgtest_main
INCLUDE = -I.

SRC = obj_worker.cpp
TEST_SRC = tests.cpp
OBJ = $(SRC:.cpp=.o)
TEST_OBJ = $(TEST_SRC:.cpp=.o)
MAIN_TARGET = main_app
TEST_TARGET = obj_test

.PHONY: all test clean

all: $(MAIN_TARGET)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(MAIN_TARGET): $(OBJ) main.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

$(TEST_TARGET): $(TEST_OBJ) $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -f $(OBJ) $(TEST_OBJ) $(MAIN_TARGET) $(TEST_TARGET) *.o