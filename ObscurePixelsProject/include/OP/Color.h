#pragma once

#include <stdint.h>

namespace op
{
    class Color
    {

        private:
         // returns unique value to rgb color
        size_t getUniqueValue() const;
        
        protected:
        // Technically its 255 cause uint8_t but just use it this way < MAX_VALUE (easier with maths)
        static const unsigned MAX_VALUE = 256;

        public: 
        // R G B, value is unique number 
        uint8_t r; 
        uint8_t g;
        uint8_t b;
    
        // Default
        Color();

        // Full
        Color(uint8_t red,uint8_t green,uint8_t blue);

        // Copy Constructor Color new(Other Color)
        Color(const Color& c1);        

        const Color& operator =(const Color&);

        bool operator==(const Color&) const;
       
        bool operator!=(const Color&) const;
       
    };

    // Alias to Color cause it uses RGB scheme
    typedef Color RGB;

} // namespace op
