#pragma once

#include "Color.h"
#include "VertexArray.h"
#include "Clock.h"

namespace op
{   
    class Drawable;
    // Core shortcuts
    #define ESC "\033" 
    #define CSI ESC"[" 
    #define RESET CSI "c"

    // Cursor / Screen Manipulations
    #define CLEAR CSI "1;H" CSI "2J" CSI "3J" CSI "0m"
    #define HOME CSI "1000D" CSI "1000A"
    #define HIDE_CURSOR CSI "?25l"	
    
    // Color Manipulations
    #define SGR_RES CSI"0m"
    #define FG CSI "38;2;"
    #define BG CSI "48;2;"

    // Class to handle ESC and CSI sequences to control consol output
    class ConsoleHandler 
    {
        private:
        friend class Drawable;
        // Definition of our console printing region starting from left top corner
        size_t _width,_height; //  x,y

        // View vector
        Vector2i view; // Used as form of camera-vector control
        
        // Main Screen
        Vertex* Screen = nullptr;

        // IN DEV
        char* lf_out = nullptr;
        char* lf_beg; // to save buffer beg position
        char* lf_end; // to save buffer end position

        char* ff_out = nullptr;
        char* ff_beg; // to save buffer beg position
        char* ff_end; // to save buffer end position

        // Internal Clock
        Clock clock;
        double dt;

        // FpsLimiter
        const double fps_const = 2.0;
        double fps;
        double fpsLock;

        // for debugging :) 
        size_t f_buffer_size_debug;

        // Handler Registers
        bool _altBuffer; 
        bool _open;
        const char* DefaultPrintingMode;

        // Constructors and Destructors

        // creates console screen handler width,height,alternative_buffer
        public:
        ConsoleHandler(unsigned width,unsigned height,double fpsLimit = 0,bool alt_buffer = false);
        
        ~ConsoleHandler();
    
        // Accessors

        bool isOpen();
       
        // Setters

        void setFramerateLimit(size_t num);

        // manipulate ViewPort
        void setView(Vector2i);
        void moveView(Vector2i);

        // Getters

        // Returns Vector2i to view
        Vector2i getView();
        
        // Main Functionality Loop (Clear the screen, write (draw) vertices to buffer, Display them (write to console))
        // Clear screen with aditional parameter that fills it up with color
        void clear(const Color& bg = Color(0,0,0));

        void draw(); // draws nothing

        void draw(const Drawable& drawable); // Main option used to draw custom Drawable objects

        void draw(const VertexArray& array); // used to draw designed, encapsulated VertexArray class
        
        void draw(const Vertex* vertices, unsigned count_vertices); // Alternative use to directy draw array of vertices

        void display(); // Displays Characters to screen
        // ~ Render Target Class end 

        void close(); // to forcefully close console handler

        private:
        // Inits
        void initScreen();
        void initScreenStatus();

        // Setters
        void setDefaultPrintingMode();

        // Buffer operations
        // prepare FastBuffer (ff_out)
        void fastFormatter(size_t row);
 
        // Format & Write whole buffer with nextline to stdin instantaneously
        void WriteFastBuffer();

        // just debugging tool
        void debugFastBuffer();
    }; 
} // namespace op
