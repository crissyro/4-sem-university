#include "list.hpp"
#include <iostream>

using namespace mylist;

int main() {
    List<int> intList;

    intList.push_back(1);
    intList.push_back(2);
    intList.push_back(3);

    for(const auto& item : intList) {
        std::cout << item << ' ';
    }
    std::cout << std::endl;

    return 0;
}