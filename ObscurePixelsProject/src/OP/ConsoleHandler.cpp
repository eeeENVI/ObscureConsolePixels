#include "../../include/OP/ConsoleHandler.h"
#include "../../include/OP/Drawable.h"

#include <iostream>
#include <cstring>


namespace op
{
    ConsoleHandler::ConsoleHandler(unsigned width,unsigned height,bool alt_buffer,bool fast_buffer)
    {
        this->_width = height;
        this->_height = width;
        this->_alt_buffer = alt_buffer;
        this->fast_buffer = fast_buffer;

        initScreenStatus();
        initScreen();
    }

    ConsoleHandler::~ConsoleHandler()
    {
        _open = false;

        if(fast_buffer)
        {
            delete[] ff_out;
            ff_out = nullptr;
        }

        delete[] Screen;
        Screen = nullptr;

        if(_alt_buffer) printf(CSI "?1049l"); // leave alternative buffer
    }

    //inits
    void ConsoleHandler::initScreen()
    {
        _defaultChar = ' ';
        _defaultBgClear = Color(0,0,0);
        _defaultFgClear = Color(255,255,255);

        view = Vector2i(0,0); 

        Screen = new Vertex[_width * _height];

        for(unsigned x = 0; x < _width;x++) 
        {
            for(unsigned y = 0; y < _height;y++)
            {
                Screen[x + y * _width] = Vertex(Vector2f(float(x),float(y)));
                Screen[x + y * _width].setChar(_defaultChar);
                Screen[x + y * _width].bgColor = _defaultBgClear;
                Screen[x + y * _width].fgColor = _defaultFgClear;
            }
        }
    }

    void ConsoleHandler::initScreenStatus()
    {
        // Prepare terminal
        if(_alt_buffer) printf(CSI "?1049h"); // enter alternative buffer

        printf(HIDE_CURSOR);
        printf(CLEAR);

        // settings of console handler
        _open = true;
    }

    // accessors
    bool ConsoleHandler::isOpen() const
    {
        return _open;
    }

    void ConsoleHandler::setView(const Vector2i v)
    {
        view = v;
    }

    void ConsoleHandler::moveView(const Vector2i v)
    {
        view = view + v;
    }

    void ConsoleHandler::setDefaultPrintingMode()
    {
        printf(CSI "1;1H");
        printf(SGR_RES);
    }
    
    // Functions

    // Clear screen with aditional parameter that fills it up with color
    // assigns CLEARED vertex to screen
    void ConsoleHandler::clear(const Color bg )
    {
        _defaultBgClear = bg;
        _defaultChar = ' ';

        // with Fast Buffer there's no need to do it
        if(fast_buffer == false) printf(CLEAR);

        for(unsigned x = 0; x < _width;x++)
        {
            for(unsigned y = 0; y < _height;y++)
            {
                Screen[x + y * _width].bgColor = _defaultBgClear;
                Screen[x + y * _width].setChar(_defaultChar);
            }
        }
        setDefaultPrintingMode();
    }

    // Self Explenatory, it draws custom drawable object duuh
    void ConsoleHandler::draw(const Drawable& drawable)
    {
        drawable.draw(*this);
    }

    // Just keeping it empty
    void ConsoleHandler::draw(){};

    // IN DEV
    //void ConsoleHandler::draw(const Vertex* vertices, unsigned count_vertices);

    void ConsoleHandler::display()
    {
        bool dev = 1;

        if(dev == true)
        {
            ff_out = new char[(_width * _height + (_width+1)) * 50];
            f_buffer_size = 0;
        }
       
        for(size_t x = 0; x < _width;x++)
        {
            for(size_t y = 0; y < _height;y++)
            {
                    // ...Draw it! [psst.. remember about colors ;)]
                    char ch = Screen[x + y * _width].getChar();
                    Color fg = Screen[x + y * _width].fgColor;
                    Color bg = Screen[x + y * _width].bgColor;                    

                    if(fast_buffer)
                    {       
                        if(dev == true)
                        {
                           FormatFastBuffer(ch,fg,bg);
                        }
                        else 
                        {
                            // temporary solution
                            char t_out[50];
                            sprintf(t_out,"\033[38;2;%d;%d;%dm\033[48;2;%d;%d;%dm%c",+fg.r,+fg.g,+fg.b,+bg.r,+bg.g,+bg.b,ch);       

                            size_t size = strlen(t_out);

                            fwrite(t_out,sizeof(char),size,stdout);
                        }                         
                    }
                    else
                    {
                        // Default option (set fast_buffer = false)
                        printCh(ch,fg,bg);
                    }
            }
            if(fast_buffer)
            {
                if(dev == true) FormatFastBufferNextLine(x);
                else printf(CSI "%d;1H",x+2); 
            }
            else printf(CSI "%d;1H",x+2);   
        }

        if(dev == true) WriteFastBuffer();

        setDefaultPrintingMode();
    }    

    // Fast Buffer Formater
    void ConsoleHandler::FormatFastBuffer(const char c,const Color fg ,const Color bg )
    {
        // tmp buffer for single character ( to optimize )
        char t_out[50];

        // CSI formating color;
        sprintf(t_out,"\033[38;2;%d;%d;%dm\033[48;2;%d;%d;%dm%c",+fg.r,+fg.g,+fg.b,+bg.r,+bg.g,+bg.b,c);       

        // increases buffer with every character_format
        size_t size = strlen(t_out);
        f_buffer_size  += size;

        // first character needs to be copied others are concat'ed
        if(f_buffer_size == size) std::strcpy(ff_out,t_out);
        else std::strcat(ff_out,t_out);
    }

    void ConsoleHandler::FormatFastBufferNextLine(size_t x)
    {
        char t_out[50];

        sprintf(t_out,"\033[%d;1H",x+2);

        size_t size = strlen(t_out);

        f_buffer_size  += size;

        std::strcat(ff_out,t_out);
    }

    // Fast Buffer Writer and cleaner
    void ConsoleHandler::WriteFastBuffer()
    {
        fwrite(ff_out,sizeof(char),f_buffer_size,stdout);

        delete[] ff_out;
    }

    // Basic drawer
    void ConsoleHandler::printCh(const char c,const Color fg ,const Color bg )
    {
        printf(CSI FG "%d;%d;%dm" CSI BG "%d;%d;%dm%c", +fg.r,+fg.g,+fg.b,+bg.r,+bg.g,+bg.b,c);
        printf(SGR_RES);
    }
    
} // namespace op
