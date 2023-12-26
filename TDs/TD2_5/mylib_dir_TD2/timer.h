#include <iostream>
#include <chrono>

class Timer
{
private:
    std::chrono::high_resolution_clock::time_point start_;
    std::chrono::high_resolution_clock::time_point stop_;

public:
    void start();
    void stop();
    void print(const std::string &label);
};