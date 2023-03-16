#pragma once

#include "Vector2.h"
#include "Color.h"

namespace op
{
    class Vertex
    {
        private:
        
        char char_value;  // something like a.. texture? but it's character
        
        Color fgColor;    // Texture color : foreground
        Color bgColor;    // Pixel color : background

        Vector2i position; // position that might be casted to int when Screen Checks it

        public:   

        //Setters
        void setPosition(const Vector2i v);
        void movePosition(const Vector2i v);

        void setChar(const char ch);
        void setFg(const Color c);
        void setBg(const Color c);

        //Getters
        char getChar() const;
        Color getFg() const;
        Color getBg() const;
       
        Vector2i getPosition() const;
    
        // Constructors
        // Default
        Vertex();

        // Full constructor
        Vertex(char ch, Color fg, Color bg, Vector2i v);
    
        // Copy Constructor
        Vertex(const Vertex& p);

        // Operators
        Vertex& operator=(const Vertex&);

        bool operator==(const Vertex&) const;
       
        bool operator!=(const Vertex&) const;
    };
} // namespace op
