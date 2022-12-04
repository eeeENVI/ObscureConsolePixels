#pragma once

#include <chrono>

namespace op
{
    // Klasa upraszczajaca korzystanie z chrono
    class Clock
    {   
        typedef std::chrono::time_point<std::chrono::steady_clock> chrono_time_t;

        private:
        chrono_time_t _start;

        public:
        // Init Close Run    
        Clock();

        // Restarts Clock
        void restart();

        // Return ElapsedTime in seconds cause Clock has seconds ratio
        double getElapsedTime();
        
    };

} // namespace op