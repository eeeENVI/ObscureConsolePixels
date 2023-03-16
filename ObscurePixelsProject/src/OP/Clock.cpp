#include "../../include/OP/Clock.h"

namespace op
{
    Clock::Clock()
    {
        restart();
    }

    double Clock::restart()
    {   
        double elapsed = getElapsedTime();
        _start = std::chrono::steady_clock::now();

        return elapsed;
    }

    double Clock::getElapsedTime()
    {
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsedTime = end - _start;

        return elapsedTime.count();
    }

} // namespace op
