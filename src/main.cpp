#include <iostream>
#include "../include/portfolio.h"

int main() {
    Date test = Date(2022, 7, 31);
    std::cout << "Hello, World!" << std::endl;

    std::cout << test.getMonth() << std::endl;
    return 0;
}
