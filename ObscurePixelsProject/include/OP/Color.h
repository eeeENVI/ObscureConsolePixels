#pragma once

#include <stdint.h>

namespace op
{
    class Color
    {
        protected:
        static const unsigned MAX_VALUE = 256;

        public: 
        // R G B, value is unique number 
        uint8_t r; 
        uint8_t g;
        uint8_t b;
    
        // Default
        Color() = default;

        // Full
        Color(uint8_t red,uint8_t green,uint8_t blue);

        // Copy Constructor Color new(Other Color)
        Color(const Color& c1);        

        // Idk what to do with this but it might come in handy
        int getUniqueValue();

        const Color& operator =(const Color&);
    };

    
} // namespace op
