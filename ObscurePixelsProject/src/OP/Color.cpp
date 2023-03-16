#include "../../include/OP/Color.h"

namespace op
{    

    // RGB scheme
    Color::Color(){}

    Color::Color(uint8_t red,uint8_t green,uint8_t blue,uint8_t alpha)
    {
        r = red; g = green; b = blue; a = alpha;
    }
    
    Color::Color(const Color& c)
    {
        r = c.r;
        g = c.g;
        b = c.b;
        a = c.a;
    }

    size_t Color::getUniqueValue() const
    {
        return (r * 256 * 256) + ( g * 256) + (b);
    }

    const Color& Color::operator =(const Color& c)
    {
        r = c.r;
        g = c.g;
        b = c.b;
        a = c.a;

        return *this;
    }

    // Linear interpolation - lerp but from 0..255
    uint8_t Color::mix_Component(uint16_t c1,uint16_t c2,uint16_t a)
    {
        return c1 + (c2 - c1)*a/255;
    }

    Color Color::blendColors(Color c1,Color c2)
    {
        return Color(mix_Component(c1.r,c2.r,c2.a),mix_Component(c1.g,c2.g,c2.a),mix_Component(c1.b,c2.b,c2.a));
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
