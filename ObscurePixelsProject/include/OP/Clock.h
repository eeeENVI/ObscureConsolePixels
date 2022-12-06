#pragma once

#include <chrono>

namespace op
{
    // Class to handle <chrono> more easily
    class Clock
    {   
        typedef std::chrono::time_point<std::chrono::steady_clock> chrono_time_t;

        private:
        chrono_time_t _start;

        public:
        // Init Clock Run    
        Clock();

        // Restarts Clock
        void restart();

        // Return ElapsedTime in seconds cause Clock has seconds ratio
        double getElapsedTime();
    };

} // namespace op