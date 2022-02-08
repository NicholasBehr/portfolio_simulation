//
// Created by Nicholas on 08.02.2022.
//

#include "../include/stocks.h"
#include <stdlib.h>
#include <assert.h>
#include <cstring>
#include <cmath>
#include <iostream>

Stocks::Stocks(int _number_of_stocks)
{
    cash = 0;
    number_of_stocks = _number_of_stocks;

    //Allocate stock_count array
    stock_count = (int*) calloc(number_of_stocks, sizeof(int));
    assert(stock_count);

    //Allocate stock_value array
    stock_value = (float*) calloc(number_of_stocks, sizeof(float));
    assert(stock_value);

    //Allocate stock_allocation array
    stock_allocation = (float*) calloc(number_of_stocks, sizeof(float));
    assert(stock_allocation);

    //Allocate stock_count_desired array
    stock_count_desired = (int*) calloc(number_of_stocks, sizeof(int));
    assert(stock_count_desired);
}

Stocks::Stocks(float _cash, int _number_of_stocks, int *_stock_count, float *_stock_value) : Stocks(_number_of_stocks)
{
    cash = _cash;
    std::memcpy(stock_count, _stock_count, sizeof(int) * number_of_stocks);
    std::memcpy(stock_value, _stock_value, sizeof(float) * number_of_stocks);
}

Stocks::~Stocks()
{
    //Free stock_count array
    free(stock_count);
    stock_count = NULL;

    //Free stock_value array
    free(stock_value);
    stock_value = NULL;

    //Free stock_allocation array
    free(stock_allocation);
    stock_allocation = NULL;

    //Free stock_allocation array
    free(stock_count_desired);
    stock_count_desired = NULL;
}

float Stocks::getValue()
{
    float value = cash;
    for(int i = 0; i < number_of_stocks; i++) {
        value += stock_count[i] * stock_value[i];
    }
    return value;
}

void Stocks::setAllocation(float *_stock_allocation) {
    std::memcpy(stock_allocation, _stock_allocation, sizeof(float) * number_of_stocks);
}

void Stocks::rebalance() {
    minimum_cost = INFINITY;
    float value = this->getValue();
    this->rebalance_recursive(0, value, value, 0);

    std::cout << "result: " << std::endl;
    for (int i = 0; i < number_of_stocks; ++i) {
        std::cout << stock_count[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "cost: " << minimum_cost << std::endl;
}

void Stocks::rebalance_recursive(int dimension, float total_value , float remaining_value, float previous_cost)
{
    for(int amount = 0; amount <= remaining_value / stock_value[dimension]; ++amount) {
        stock_count_desired[dimension] = amount;
        float cost = previous_cost + pow(stock_allocation[dimension]*total_value/stock_value[dimension] - amount,2);
        if(dimension + 1 < number_of_stocks ) {
            this -> rebalance_recursive(dimension + 1, total_value, remaining_value - amount * stock_value[dimension], cost);
        }
        else {
            if(cost < minimum_cost) {
                std::memcpy(stock_count, stock_count_desired, sizeof(int) * number_of_stocks);
                minimum_cost = cost;
            }
        }
    }
}