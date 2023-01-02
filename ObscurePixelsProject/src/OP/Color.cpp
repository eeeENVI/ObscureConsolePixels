#include "../../include/OP/Color.h"

namespace op
{    

    // RGB scheme
    Color::Color()
    {
        r = 255; g = 255; b = 255;
    }

    Color::Color(uint8_t red,uint8_t green,uint8_t blue)
    {
        r = red; g = green; b = blue;
    }
    
    Color::Color(const Color& c)
    {
        r = c.r;
        g = c.g;
        b = c.b;
    }

    size_t Color::getUniqueValue() const
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

    bool Color::operator==(const Color& obj) const
    {
        return getUniqueValue() == obj.getUniqueValue();
    }

    bool Color::operator!=(const Color& obj) const
    {
        return getUniqueValue() != obj.getUniqueValue();
    }
    
} // namespace op
