#include "timer.h"

void Timer::start()
{
    start_ = std::chrono::high_resolution_clock::now();
}

void Timer::stop()
{
    stop_ = std::chrono::high_resolution_clock::now();
}

void Timer::print(const std::string &label)
{
    auto t = std::chrono::duration_cast<std::chrono::milliseconds> (stop_ - start_);
    std::cout << label << ": " << t.count() << " ms" << std::endl;
}