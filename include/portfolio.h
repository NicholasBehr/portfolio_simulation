//
// Created by Nicholas on 07.02.2022.
//

#ifndef PORTFOLIO_SIMULATION_PORTFOLIO_H
#define PORTFOLIO_SIMULATION_PORTFOLIO_H

class Date
{
    private:
        int m_year;
        int m_month;
        int m_day;

    public:
        Date(int year, int month, int day);

        void SetDate(int year, int month, int day);

        int getYear() { return m_year; }
        int getMonth() { return m_month; }
        int getDay()  { return m_day; }
};

#endif //PORTFOLIO_SIMULATION_PORTFOLIO_H
