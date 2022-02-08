//
// Created by Nicholas on 08.02.2022.
//

#ifndef PORTFOLIO_SIMULATION_STOCKS_H
#define PORTFOLIO_SIMULATION_STOCKS_H


class Stocks
{
    public:
        //Constructor
        Stocks(int _number_of_stocks);
        Stocks(float _cash, int _number_of_stocks, int *_initial_stock_count, float *_initial_stock_value);

        //Destructor
        ~Stocks();

        //Getter & Setter
        float getValue();
        void setAllocation(float *_stock_allocation);

        void rebalance();


    private:
        float cash;                 //How much cash is at brokerage account?
        int number_of_stocks;       //How many stock types exist?
        int *stock_count;           //How many stocks are held of each type?
        float *stock_value;         //What is the value of each different stock type?
        float *stock_allocation;    //What is the target weight of each stock type?
        int *stock_count_desired;   //How many stocks should be held of each type to align with allocation?

        float getDistance(float cash_available);
};

#endif //PORTFOLIO_SIMULATION_STOCKS_H
