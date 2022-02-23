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

Stocks::Stocks(float _cash, int _number_of_stocks, int *_stock_count, float *_stock_value, float *_stock_allocation) : Stocks(_number_of_stocks)
{
    cash = _cash;
    std::memcpy(stock_count, _stock_count, sizeof(int) * number_of_stocks);
    std::memcpy(stock_value, _stock_value, sizeof(float) * number_of_stocks);
    std::memcpy(stock_allocation, _stock_allocation, sizeof(float) * number_of_stocks);
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

void Stocks::printStockCountDesired()
{
    std::cout << "The desired stock count is: ( ";
    for (int dimension = 0; dimension < number_of_stocks; ++dimension) {
        std::cout << stock_count_desired[dimension] <<" ";
    }
    std::cout << ")" << std::endl;
}

void Stocks::printStockCount()
{
    std::cout << "The actual stock count is: ( ";
    for (int dimension = 0; dimension < number_of_stocks; ++dimension) {
        std::cout << stock_count[dimension] <<" ";
    }
    std::cout << ")" << std::endl;
}

void Stocks::rebalance(){ //upto 15 different stocks
    float available_funds = this->getValue(); //cache of getValue()
    float remaining_budget = available_funds; //left in wallet to buy additional stocks

    //stock_allocation[dimension] * available_funds / stock_value[dimension] is the theoretical optimum
    //since we don't allow fractional shares, this value gets floored
    int stock_count_floor[number_of_stocks];
    for (int dimension = 0; dimension < number_of_stocks; ++dimension) {
        stock_count_floor[dimension] = floor(stock_allocation[dimension] * available_funds / stock_value[dimension]);
        remaining_budget -= stock_count_floor[dimension] * stock_value[dimension];
    }

    //the remaining funds can now be uses on further purchases to closer approach the optimum
    //square_distance is the distance from this optimum and the current stock_count_desired ^2
    unsigned short best_bit_flag = 0;
    float best_square_distance = INFINITY;

    //a hypercube is built around the optimum and the distance to all corners is checked,
    //the minimum distance, which also fits into the remaining_budget is chosen
    for (unsigned int bit_flag = 0; bit_flag < 0b1 << number_of_stocks; ++bit_flag) {
        float square_distance = 0;
        float required_additional_budget = 0;
        for (int dimension = 0; dimension < number_of_stocks; ++dimension) {
            if(bit_flag >> dimension & 0b1){
                square_distance += powf( (stock_allocation[dimension] * available_funds / stock_value[dimension])
                        - (stock_count_floor[dimension] + 1), 2);
                required_additional_budget += stock_value[dimension];
            }
            else{
                square_distance += powf( (stock_allocation[dimension] * available_funds / stock_value[dimension])
                        - (stock_count_floor[dimension] + 0), 2);
            }
        }
        if(required_additional_budget <= remaining_budget && square_distance <= best_square_distance){
            best_bit_flag = bit_flag;
            best_square_distance = square_distance;
        }
    }

    //write the result of the computation to stock_count_desired
    for (int dimension = 0; dimension < number_of_stocks; ++dimension) {
        stock_count_desired[dimension] = (best_bit_flag >> dimension & 0b1) ? stock_count_floor[dimension] + 1 : stock_count_floor[dimension];
    }
}

void Stocks::simulate_month(float *growth_factor){
    //Let stock value develop
    for(int i = 0; i < number_of_stocks; i++) {
        stock_value[i] *= growth_factor[i];
    }

    //calculate the cumulative deviation from the stock allocation
    float value = this->getValue();
    float total_deviation = 0;
    for(int i = 0; i < number_of_stocks; i++) {
        total_deviation += std::abs(stock_allocation[i] - (stock_value[i] * stock_count[i])/value);
    }

    //if this deviation exceeds 5% then rebalance
    if(total_deviation >= 5/100)
    {
        this->rebalance(); //Update desired stock count, optimally aligned with stock_allocation

        for(int i = 0; i < number_of_stocks; i++) {
            int purchase_cnt = stock_count_desired[i] - stock_count[i]; //pos if purchasing, neg if selling
            cash -= stock_value[i] * purchase_cnt;
            stock_count[i] += purchase_cnt;
        }
    }
}