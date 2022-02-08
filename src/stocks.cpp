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
    for(int i = 0; i < number_of_stocks; i++)
    {
        value += stock_count[i] * stock_value[i];
    }
    return value;
}

void Stocks::setAllocation(float *_stock_allocation)
{
    std::memcpy(stock_allocation, _stock_allocation, sizeof(float) * number_of_stocks);
}

void Stocks::rebalance()
{
    float already_allocated = 0;
    float total_cash_available = this -> getValue();
    float remaining_cash_available = total_cash_available;

    bool locked[number_of_stocks];
    for ( int i = 0; i < number_of_stocks; ++i) locked[i] = false;

    for (int k = 0; k < number_of_stocks; ++ k){
        float min_dist  = INFINITY;
        int min_index = 0;

        for(int j = 0; j < number_of_stocks; j++) //decide which one to floor
        {
            if(locked[j]) continue;

            float distance = 0;
            float free_cash = fmodf((stock_allocation[j]/(1-already_allocated)) * remaining_cash_available, stock_value[j]);

            for (int i = 0; i < number_of_stocks; i++)
            {
                if(locked[i]) continue;
                float free_cash_portion = (i==j) ? -free_cash : free_cash * (stock_allocation[i]/(1-already_allocated-stock_allocation[j]));
                distance += pow(stock_allocation[i] * total_cash_available - ((stock_allocation[i]/(1-already_allocated)) * remaining_cash_available + free_cash_portion),2); //budget - tatsaechlich
            }

            if (distance < min_dist)
            {
                min_dist = distance;
                min_index = j;
            }
        }

        stock_count_desired[min_index] = floor(remaining_cash_available * (stock_allocation[min_index]/(1-already_allocated)) / stock_value[min_index]);
        remaining_cash_available -= stock_count_desired[min_index] * stock_value[min_index];
        already_allocated += stock_allocation[min_index];
        locked[min_index] = true;
    }

    for (int i = 0; i < number_of_stocks; i++)
    {
        std::cout << stock_count_desired[i] << std::endl;
    }
}

float Stocks::getDistance(float cash_available)
{
    float distance = 0;
    for(int i = 0; i < number_of_stocks; i++)
    {
        distance += pow(stock_allocation[i]*cash_available - stock_count_desired[i]*stock_value[i],2); //budget - planned expense
    }
    return distance;
}