//
// Created by Nicholas on 09.02.2022.
//

#ifndef PORTFOLIO_SIMULATION_DATAINGEST_H
#define PORTFOLIO_SIMULATION_DATAINGEST_H
#include <string>
#include <random>


class DataIngest
{
public:
    //Constructor
    DataIngest(std::string path, std::string delimiter);

    //Destructor
    ~DataIngest();

    float* getRandomGrowth();

private:
    int number_of_stocks;
    int number_of_months;
    float **monthly_growth;
    std::mt19937_64 eng;
};

#endif //PORTFOLIO_SIMULATION_DATAINGEST_H
