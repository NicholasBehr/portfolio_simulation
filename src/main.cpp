#include <iostream>
#include <queue>
#include "../include/stocks.h"
#include "../include/dataIngest.h"

int main(int argc, char* argv[]) {
    float   cash = 200000;
    int     count[3] = {0,0, 0};
    float   value[3] = {30.837,26.379, 196.88};
    float allocation[3] = {0.3, 0.5, 0.2};

    std::cout << "Starting..." << std::endl;

    DataIngest data = DataIngest("../historyIndex.csv",";");

    int     runs = 50000;
    int     percentile = 5; //5% of results smaller, 95% of results larger
    int     heap_size = std::round(runs * percentile / 100.0);
    std::priority_queue<int> max_heap;

    for (int i = 0; i < runs; ++i) {
        //initialize fresh portfolio
        Stocks test = Stocks(cash, 3, count, value, allocation);

        //simulate 444 months
        for (int j = 0; j < 444; ++j) {
            test.simulate_month(data.getRandomGrowth());
        }

        //keep track of the smallest results
        float value = test.getValue();
        if(max_heap.size() < heap_size || max_heap.top() > value){
            max_heap.push(value);
        }
        if(max_heap.size() > heap_size){
            max_heap.pop();
        }
    }

    std::cout << std::endl << "percentile..." << max_heap.top() << std::endl << std::endl;



    return 0;
}

