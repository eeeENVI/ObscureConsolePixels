#pragma once

#include <stdint.h>

namespace op
{
    class Color
    {
        private:
         // returns unique value to rgb color
        size_t getUniqueValue() const;

        static uint8_t mix_Component(uint16_t c1,uint16_t c2,uint16_t a);

        public: 
        // R G B, value is unique number 
        uint8_t r; 
        uint8_t g;
        uint8_t b;
        uint8_t a;
    
        // Default
        Color();

        // Full
        Color(uint8_t red,uint8_t green,uint8_t blue, uint8_t alpha = 255);

        // Copy Constructor Color new(Other Color)
        Color(const Color& c1);        

        const Color& operator =(const Color&);

        static Color blendColors(Color,Color);

        bool operator==(const Color&) const;
       
        bool operator!=(const Color&) const;

        // Static const colors
        /*static const Color Black;       
        static const Color White;       
        static const Color Red;        
        static const Color Green;       
        static const Color Blue;        
        static const Color Yellow;      
        static const Color Magenta;     
        static const Color Cyan;        
        static const Color Transparent; */

        static constexpr int MAX_VALUE = 255;
       
    };


    // Alias to Color cause it uses RGBA scheme
    typedef Color RGBA;

} // namespace op
