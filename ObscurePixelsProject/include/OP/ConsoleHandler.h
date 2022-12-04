#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "Color.h"
#include "Vertex.h"
#include "VertexArray.h"

namespace op
{   
    class Drawable;

    // these are fine 
    #define ESC "\033"
    #define CSI ESC"["
    #define CLEAR CSI "1;1H" CSI "2J" CSI "3J" CSI "0m"
    #define HOME CSI "1000D" CSI "1000A"
    #define RESET CSI "c"

    //printf(CSI "?1049h"); // enter alternative buffer
    //printf(CSI "?1049l"); // leave alternative buffer
    #define HIDE_CURSOR CSI "?25l"	

    // Colors
    #define SGR_RES CSI"0m"
    #define FG CSI "38;2;"
    #define BG CSI "48;2;"
    // too much ..?

    // Klasa obsługująca konsole przy pomocy Console Sequence Introducer ( CSI ) kodow
    class ConsoleHandler
    {
        private:
        // Definition of our console printing region starting from left top corner
        friend class VertexArray;

        unsigned _width,_height; //  y(columns), x(rows)
        unsigned _framePerSecondRateLimit;

        // view vector
        Vector2i view; // Used as form of camera-vector 
        
        // Array of characters that can be displayed whenever we wants with whatever properties
        Vertex* Screen = nullptr;
        char _defaultChar = ' ';
        Color _defaultBgClear;

        // External windows buffer
        bool fast_buffer;

        //accessors 
        bool _alt_buffer;
        bool _open;

        // Constructors / Destructors
        public:
        ConsoleHandler(unsigned width,unsigned height,bool alt_buffer = false, bool fast_buffer = false);
        
        ~ConsoleHandler();
    
        // accessors
        bool isOpen() const;
       
        //setters
        void setFramePerSecondRate(unsigned rate = 0);

        void setView(Vector2i);
        void moveView(Vector2i);
        
        // Functions
        // Clear screen with aditional parameter that fills up it with color
        void clear(const Color bg = Color(0,0,0));

        void draw(); // Alternative 0

        void draw(const Drawable& drawable); // Main option

        void draw(const Vertex* vertices, unsigned count_vertices); // Alternative 2

        void display();

        private:
        // Inits
        void initScreen();
        
        void initScreenStatus();


        // Setters
        void setDefaultPrintingMode();
       
        // Most important drawer
        void printCh(const char c,const Color fg = Color(255,255,255),const Color bg = Color(0,0,0));
        
    }; 
} // namespace op
