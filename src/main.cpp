#include <iostream>
#include "../include/stocks.h"

int main(int argc, char* argv[]) {
    float   cash = 14811;
    int     count[3] = {0,0, 0};
    float   value[3] = {31.177,200.35, 27.098};

    std::cout << "Starting..." << std::endl;

    Stocks test = Stocks(cash, 3, count, value);

    float allocation[3] = {0.3, 0.2, 0.5};
    test.setAllocation(allocation);

    test.rebalance();
    test.getStockCountDesired();

    return 0;
}

