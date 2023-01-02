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

        // Definition of our console printing region starting from left top corner
        size_t _width,_height; //  x,y

        // View vector
        Vector2i view; // Used as form of camera-vector control
        
        // Just a pointer to Vertices array
        Vertex* Screen = nullptr;

        //default "screen" vertex
        char _defaultChar;
        Color _defaultBgClear;
        Color _defaultFgClear;

        char* ff_out = nullptr;
        size_t f_buffer_size;

        // for debugging :) 
        size_t f_buffer_size_debug;
        size_t f_buffer_size_newlines_debug;


        // IN DEV
        char* lf_out = nullptr;
        Vertex* lastFrame = nullptr;

        // Accessors 
        bool _alt_buffer; 
        bool _open;

        // Constructors and Destructors
        public:
        ConsoleHandler(unsigned width,unsigned height,bool alt_buffer = false);
        
        ~ConsoleHandler();
    
        // Accessors
        bool isOpen() const;
       
        // Setters

        // manipulate ViewPort
        void setView(Vector2i);
        void moveView(Vector2i);

        // Getters

        // Returns Vector2i to view
        Vector2i getView();
        
        // Main Functionality Loop (Clear the screen, write (draw) vertices to buffer, Display them (write to console))

        // Clear screen with aditional parameter that fills it up with color
        void clear(const Color bg = Color(0,0,0));

        void draw(); // draws nothing

        void draw(const Drawable& drawable); // Main option used to draw custom Drawable objects

        void draw(const VertexArray& array); // used to draw designed, encapsulated VertexArray class
        
        void draw(const Vertex* vertices, unsigned count_vertices); // Alternative use to directy draw array of vertices

        void display(); // Displays Characters to screen

        private:
        // Inits
        void initScreen();
        void initScreenStatus();

        // Setters
        void setDefaultPrintingMode();

        // Accessors / Getters

        // Buffer operations
        // prepare FastBuffer (ff_out)
        void FormatFastBuffer(const char c,const Color fg = Color(255,255,255),const Color bg = Color(0,0,0),short optimize_code = 0);

        // adds nextline to FastBuffer when hits new row
        void FormatFastBufferNextLine(size_t row_counter);

        // Write whole buffer to stdin instantaneously and then clears it
        void WriteFastBuffer();

        void debugFastBuffer();
    }; 
} // namespace op
