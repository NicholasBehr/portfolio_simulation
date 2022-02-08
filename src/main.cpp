#include <iostream>
#include "../include/stocks.h"

int main(int argc, char* argv[]) {
    float   cash = 20000;
    int     count[3] = {0,0, 0};
    float   value[3] = {81,4, 6};

    std::cout << "Starting..." << std::endl;

    Stocks test = Stocks(cash, 3, count, value);

    float allocation[3] = {0.6, 0.2, 0.2};
    test.setAllocation(allocation);


    test.rebalance();

    return 0;
}

