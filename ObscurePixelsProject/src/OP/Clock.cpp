#include "../../include/OP/Clock.h"

namespace op
{
    Clock::Clock()
    {
        restart();
    }

    void Clock::restart()
    {
        _start = std::chrono::steady_clock::now();
    }

    double Clock::getElapsedTime()
    {
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsedTime = end - _start;

        return elapsedTime.count();
    }

} // namespace op
