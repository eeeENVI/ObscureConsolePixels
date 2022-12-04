#include "../../include/OP/Color.h"

namespace op
{    
    Color::Color(uint8_t red,uint8_t green,uint8_t blue)
    {
        r = 255; g = 255; b = 255;
        r = red; g = green; b = blue;
    }
    
    Color::Color(const Color& c)
    {
        r = c.r;
        g = c.g;
        b = c.b;
    }

    int Color::getUniqueValue()
    {
        return (r * MAX_VALUE * MAX_VALUE) + ( g * MAX_VALUE) + (b);
    }

    const Color& Color::operator =(const Color& c)
    {
        r = c.r;
        g = c.g;
        b = c.b;
        return *this;
    }

} // namespace op
