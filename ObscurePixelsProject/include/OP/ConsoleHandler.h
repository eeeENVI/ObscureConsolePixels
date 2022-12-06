#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "Color.h"
#include "Vertex.h"
#include "VertexArray.h"

namespace op
{   
    class Drawable;

    // Core shortcuts
    #define ESC "\033" 
    #define CSI ESC"[" 
    #define RESET CSI "c"

    // Cursor / Screen Manipulations
    #define CLEAR CSI "1;1H" CSI "2J" CSI "3J" CSI "0m"
    #define HOME CSI "1000D" CSI "1000A"
    #define HIDE_CURSOR CSI "?25l"	

    // Color Manipulations
    #define SGR_RES CSI"0m"
    #define FG CSI "38;2;"
    #define BG CSI "48;2;"

    // Class to handle ESC and CSI sequences
    class ConsoleHandler
    {
        private:
        friend class VertexArray;

        // Definition of our console printing region starting from left top corner
        unsigned _width,_height; //  x,y

        // View vector
        Vector2i view; // Used as form of camera-vector control
        
        // Just a pointer to Vertices array
        Vertex* Screen = nullptr;
        char _defaultChar;
        Color _defaultBgClear;
        Color _defaultFgClear;

        // Faster console buffer (in DEV)
        char* ff_out = nullptr;
        size_t f_buffer_size;
        bool fast_buffer;

        // Accessors 
        bool _alt_buffer; 
        bool _open;

        // Constructors and Destructors
        public:
        ConsoleHandler(unsigned width,unsigned height,bool alt_buffer = false, bool fast_buffer = false);
        
        ~ConsoleHandler();
    
        // Accessors
        bool isOpen() const;
       
        // Setters

        // manipulate ViewPort
        void setView(Vector2i);
        void moveView(Vector2i);
        
        // Main Functionality Loop (Clear the screen, write (draw) vertices to buffer, Display them (write to console))

        // Clear screen with aditional parameter that fills it up with color
        void clear(const Color bg = Color(0,0,0));

        void draw(); // draws nothing

        void draw(const Drawable& drawable); // Main option used to draw custom Drawable objects

        //void draw(const Vertex* vertices, unsigned count_vertices); // Alternative used to directy draw array of vertices

        void display(); // Displays Characters to screen

        private:
        // Inits
        void initScreen();
        void initScreenStatus();

        // Setters
        void setDefaultPrintingMode();
       
        // prepare FastBuffer (ff_out)
        void FormatFastBuffer(const char c,const Color fg = Color(255,255,255),const Color bg = Color(0,0,0));

        // adds nextline to FastBuffer when hits new row
        void FormatFastBufferNextLine(size_t row_counter);

        // Write whole buffer to stdin instantaneously and then clears it
        void WriteFastBuffer();

        // Basic drawer ( old version )
        void printCh(const char c,const Color fg = Color(255,255,255),const Color bg = Color(0,0,0));
    }; 
} // namespace op
