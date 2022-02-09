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

        //Getter
        float getValue();
        void getStockCountDesired();

        //Setter
        void setAllocation(float *_stock_allocation);

        //Update desired stock count, optimally aligned with stock_allocation
        void rebalance();

        void simulate_month(float *growth_factor);

    private:
        float cash;                 //How much cash is at the brokerage account?
        int number_of_stocks;       //How many unique stock types exist?
        int *stock_count;           //How many stocks are held of each type?
        int *stock_count_desired;   //How many would we like to hold -> (output of rebalance)
        float *stock_value;         //What is the value of each different stock type?
        float *stock_allocation;    //What is the target weight of each stock type?
};

#endif //PORTFOLIO_SIMULATION_STOCKS_H
