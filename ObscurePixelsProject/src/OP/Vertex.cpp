#include "../../include/OP/Vertex.h"

namespace op
{
    // Constructors
    Vertex::Vertex()
    {
        // default Vertex
        char_value = ' ';
        fgColor = Color(255,255,255);
        bgColor = Color(0,0,0);
        position = Vector2i(0.0f,0.0f);
    }

    Vertex::Vertex(char ch, Color fg, Color bg, Vector2i v)
    {
        char_value = ch;
        fgColor = fg;
        bgColor = bg;
        position = v;
    }

    Vertex::Vertex(const Vertex& p)
    {
        char_value = p.char_value;
        fgColor = p.fgColor;
        bgColor = p.bgColor;
        position = p.position;
    }

    // Setters
    void Vertex::setPosition(const Vector2i v)
    {
        this->position = v;
    }

    void Vertex::movePosition(const Vector2i v)
    {
        this->position += v;
    }

    void Vertex::setChar(const char ch)
    {
        this->char_value = ch;
    }

    void Vertex::setFg(const Color c)
    {
        this->fgColor = c;
    }

    void Vertex::setBg(const Color c)
    {
        this->bgColor = c;
    }

    // Getters
    char Vertex::getChar() const
    {
        return char_value;
    }

    Color Vertex::getFg() const
    {
        return fgColor;
    }

    Color Vertex::getBg() const
    {
        return bgColor;
    }

    Vector2i Vertex::getPosition() const
    {
        return position; 
    }
    
    // Operators
    Vertex& Vertex::operator=(const Vertex& obj)
    {
        this->char_value = obj.char_value;
        this->fgColor = obj.fgColor;
        this->bgColor = obj.bgColor;
        this->position = obj.position;

        return *this;
    }

    // Check for Vertices characteristics (ignore position)
    bool Vertex::operator==(const Vertex& obj) const
    {
        return (bgColor == obj.bgColor && fgColor == obj.fgColor && char_value == obj.char_value);
    }

    bool Vertex::operator!=(const Vertex& obj) const
    {
        return (bgColor != obj.bgColor || fgColor != obj.fgColor || char_value != obj.char_value);
    }

} // namespace op

