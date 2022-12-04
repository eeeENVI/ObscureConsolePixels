#pragma once

#include "Vector2.h"
#include "Color.h"

namespace op
{
    class Vertex
    {
        private:
        char char_value; // something like a.. texture? but it's character

        Vector2f position; // position that might be casted to int

        public:
        Color fgColor; // texture color : foreground
        Color bgColor; // "Vertex" color : background

        //Setters
        void setPosition(const Vector2f v);
       
        void setChar(const char ch);

        //Getters
        char getChar() const;
       
        Vector2f getPosition() const;
    
        // Constructors
        // Default
        Vertex();

        // Full constructor
        Vertex(char ch, Color fg, Color bg, Vector2f v);
        
        // Char constructor
        Vertex(char ch);
           
        // Colors constructor
        Vertex(Color fg, Color bg);
       
        // Position Constructor
        Vertex(Vector2f v);
       
        // Copy Constructor
        Vertex(const Vertex& p);
    };
} // namespace op
