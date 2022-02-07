cmake_minimum_required(VERSION 3.21)
project(portfolio_simulation)

set(CMAKE_CXX_STANDARD 14)

add_executable(portfolio_simulation src/main.cpp src/portfolio.cpp include/portfolio.h)
include_directories( ./src/include )