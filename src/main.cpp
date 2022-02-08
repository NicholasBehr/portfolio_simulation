#include <iostream>
#include "../include/stocks.h"

int main(int argc, char* argv[]) {
    float   cash = 94;
    int     count[3] = {0,0, 0};
    float   value[3] = {5,10, 7};

    std::cout << "Starting..." << std::endl;

    Stocks test = Stocks(cash, 3, count, value);

    float allocation[3] = {0.4, 0.1, 0.5};
    test.setAllocation(allocation);


    test.rebalance();

    return 0;
}

