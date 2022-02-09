//
// Created by Nicholas on 09.02.2022.
//

#include "../include/dataIngest.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cassert>


DataIngest::DataIngest(std::string path, std::string delimiter)
{
    //reads csv in format "CSV (Trennzeichen-getrennt)(*.csv)"
    //EM IMI;WORLD;EUROPE
    //100.000;100.000;100.000
    //98.181;105.648;102.733

    std::ifstream csv;
    csv.open (path, std::ios::in);

    std::string line;
    if(std::getline(csv, line)){
        number_of_stocks = std::count(line.begin(), line.end(), ';') + 1;
        std::cout << number_of_stocks << " columns where detected!\n";

        size_t pos = 0;
        std::string token;
        for (int i = 0; i < number_of_stocks; ++i) {
            std::cout << "collumn " << i << " = ";
            pos = line.find(delimiter);
            token = line.substr(0, pos);
            std::cout << token << std::endl;
            line.erase(0, pos + delimiter.length());
        }
    }

    std::vector<float> data;
    while (std::getline(csv, line))
    {
        size_t pos = 0;
        std::string token;
        for (int i = 0; i < number_of_stocks; ++i) {
            pos = line.find(delimiter);
            token = line.substr(0, pos);

            try
            {
                float lineFloat = std::stof(token);
                data.push_back(lineFloat);
            }
            catch (const std::invalid_argument& ia)
            {
                std::cerr << "Invalid argument: " << ia.what() << '\n';
            }

            line.erase(0, pos + delimiter.length());
        }
    }

    assert( data.size() % number_of_stocks == 0);

    number_of_months = data.size() / number_of_stocks;
    std::cout << number_of_months << " rows where detected!\n\n";

    csv.close();

    number_of_months--;

    //Allocate 2D monthly_growth array
    int data_index = 0;
    monthly_growth = (float**) malloc(number_of_months * sizeof(float *));
    assert(monthly_growth);
    for(int row = 0; row < number_of_months; row++)
    {
        monthly_growth[row] = (float*) malloc(number_of_stocks * sizeof(float));
        assert(monthly_growth[row]);

        for (int col = 0; col < number_of_stocks; ++col) {
            //save the month-to-month change
            // next_month / this_month
            monthly_growth[row][col] = data[data_index + number_of_stocks] / data[data_index];
            data_index++;
        }
    }

    //Preview data head
    std::cout << "monthly growth:" << std::endl;
    for (int row = 0; row < 5; row++) {
        for (int col = 0; col < number_of_stocks; ++col) {
            std::cout << monthly_growth[row][col] << ", ";
        }
        std::cout << std::endl;
    }
    std::cout << "...\n\n";

    //Seed rng
    std::random_device device;
    std::seed_seq seq{device(), device(), device(), device()};
    eng.seed(seq);
}

DataIngest::~DataIngest()
{
    //Free 2D monthly_growth array
    for (int row = 0; row < number_of_months; row++) {
        free(monthly_growth[row]);
    }
    free(monthly_growth);
}

float* DataIngest::getRandomGrowth()
{
    std::uniform_int_distribution<int> distr(0, number_of_months - 1);
    return monthly_growth[distr(eng)];
}