#include "../../include/OP/ConsoleHandler.h"
#include "../../include/OP/Drawable.h"

#include <iostream>
#include <cstring>


namespace op
{
    ConsoleHandler::ConsoleHandler(unsigned width,unsigned height,bool alt_buffer)
    {
        this->_width = width;
        this->_height = height;
        this->_alt_buffer = alt_buffer;

        initScreenStatus();
        initScreen();
    }

    ConsoleHandler::~ConsoleHandler()
    {
        _open = false;

        delete[] ff_out;
        ff_out = nullptr;

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

        //lastFrame = new Vertex[_width * _height]; // IN DEV for new checking
        //lf_out = new char[((_width * _height) * 40) + (_width * 10)]; // new place for it ( IN DEV) for new copying

        ff_out = new char[(_height * 40) + 10]; // per row

        for(unsigned x = 0; x < _width;++x) 
        {
            for(unsigned y = 0; y < _height;++y)
            {
                Screen[y + x * _height] =  Vertex(_defaultChar, _defaultFgClear, _defaultBgClear,Vector2f(float(x),float(y)));
                //lastFrame[y + x * _height] = Screen[y + x * _height];
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

    // Setters

    void ConsoleHandler::setView(const Vector2i v)
    {
        view = v;
    }

    void ConsoleHandler::moveView(const Vector2i v)
    {
        view += v;
    }

    // Getters

    Vector2i ConsoleHandler::getView()
    {
        return view;
    }

    void ConsoleHandler::setDefaultPrintingMode()
    {
        printf(CSI "1;1H" SGR_RES);
    }
    
    // Functions

    // Clear screen with aditional parameter that fills it up with color
    // assigns CLEARED vertex to screen
    void ConsoleHandler::clear(const Color bg )
    {        
        for(size_t i = 0; i < _width * _height;++i)
        {
            Screen[i].setChar(_defaultChar);
            Screen[i].setBg(bg);
        }
    }

    // Just keeping it empty
    void ConsoleHandler::draw(){};

    // Self Explenatory, it draws custom drawable object duh
    void ConsoleHandler::draw(const Drawable& drawable)
    {
        drawable.draw(*this);
    }

    // Draws designed VertexArray class object
    void ConsoleHandler::draw(const VertexArray& array)
    {
        if (!array.isEmpty())
        {
            for(int i = 0; i < array.getVertexCount();++i)
            {
                Vector2f pos = array[i].getPosition();

                // Casts Float position of vertex to Integer cause of console screen limits
                // and substracts from it with view offset
                int x = static_cast<int>(pos.x) - view.x;
                int y = static_cast<int>(pos.y) - view.y;

                // Checks if it fits screen position;
                if( x >= 0 && x < _width && y >= 0 && y < _height)
                {
                    size_t index = y + x * _height;
                    // Saves Vertex to the ScreenBuffer
                    Screen[index].setChar(array[i].getChar());
                    Screen[index].setBg(array[i].getBg());
                    Screen[index].setFg(array[i].getFg());
                }
            }
        }
    }
   
    // Draws raw vertices from pointer to Vertex but function is pretty much the same as with VertexArray
    void ConsoleHandler::draw(const Vertex* vertices, unsigned count_vertices)
    {
        if (count_vertices > 0)
        {
            for(int i = 0; i < count_vertices;++i)
            {
                Vector2f pos = vertices[i].getPosition();

                // Casts Float position of vertex to Integer cause of console screen limits
                // and substracts from it with view offset
                int x = static_cast<int>(pos.x) - view.x;
                int y = static_cast<int>(pos.y) - view.y;

                // Checks if it fits screen position;
                if( x >= 0 && x < _width && y >= 0 && y < _height)
                {
                    size_t index = y + x * _height;
                    // Saves Vertex to the ScreenBuffer
                    Screen[index].setChar(vertices[i].getChar());
                    Screen[index].setBg(vertices[i].getBg());
                    Screen[index].setFg(vertices[i].getFg());
                }
            }
        }
    }

    void ConsoleHandler::display()
    {
        // size_x * size_y + number_of_endlines
        f_buffer_size_newlines_debug = 0;
        f_buffer_size_debug = 0;

        for(size_t x = 0; x < _width;++x)
        {
            f_buffer_size = 0;

            for(size_t y = 0; y < _height;++y)
            {
                size_t index = y + x * _height;

                char ch = Screen[index].getChar();
                Color fg = Screen[index].getFg();
                Color bg = Screen[index].getBg();
                short code = 0;

                    // Memory optimalization
                    if((Screen[(index)-1].getBg() == bg && ch == ' ') ||
                       (Screen[(index)-1].getFg() == fg && Screen[(index)-1].getBg() == bg))
                    {
                        code = 1; // in case of same color parameters or same bg argument and lack of char with fg (space)
                    }
                    else if(bg == _defaultBgClear && ch == _defaultChar) 
                    {
                        code = 2; // in case of cleared pixel that didn't change after clear
                    }
                    else if(ch == ' ' || Screen[(index)-1].getFg() == fg)
                    {
                        code = 3; // in case of same fg, we just need to print background
                    }
                    else if(Screen[(index)-1].getBg() == bg)
                    {
                        code = 4; // in case of same bg, we just need to print foreground
                    }    

                // add current pixel
                FormatFastBuffer(ch,fg,bg,code);
            }
            // add endline
            FormatFastBufferNextLine(x);
            f_buffer_size_debug += f_buffer_size;
            // Drawing per row
            WriteFastBuffer();
        }
        // Debuging / Controling
        setDefaultPrintingMode();

        //debugFastBuffer(); 
    }    

    // Fast Buffer Formater
    void ConsoleHandler::FormatFastBuffer(const char c,const Color fg ,const Color bg,short code )
    {
        // code : 0,1,2,3,4: no opt, cleared pixel opt, full opt, bg opt, fg opt
        // tmp buffer for single character ( to optimize )
        char t_out[40];

        // CSI formating color;
        if(code == 1)
        {
            // Same parameters, optimization #1 tier
            //snprintf(t_out,2,"%c",c);  
            t_out[0] = c;
            t_out[1] = '\0';
        }
        else if(code == 2)
        {
            t_out[0] = '\033';
            t_out[1] = '[';
            t_out[2] = '0';
            t_out[3] = 'm';
            t_out[4] = c;
            t_out[5] = '\0';
        } 
        else if(code == 3) // Pixel mode, no char to print so no foregorund or same fg as before, optimization #2 tier 
        {
            snprintf(t_out,21,"\033[48;2;%d;%d;%dm%c",bg.r,bg.g,bg.b,c);
        }
        else if(code == 4) // same bg as before so just print fg parameter, optimization #3 tier (although it's effect is same as #2)
        {
            snprintf(t_out,21,"\033[38;2;%d;%d;%dm%c",fg.r,fg.g,fg.b,c);
        }
        else snprintf(t_out,40,"\033[38;2;%d;%d;%dm\033[48;2;%d;%d;%dm%c",fg.r,fg.g,fg.b,bg.r,bg.g,bg.b,c);  // full buffer used, no opt
    
        // increases buffer with every character_format
        size_t size = strlen(t_out);
        f_buffer_size  += size;

        memcpy(ff_out+f_buffer_size-size,t_out,size+1);
    }

    void ConsoleHandler::FormatFastBufferNextLine(size_t x)
    {
        char t_out[10]; // do 4 cyfr, max: 9999; 5 format + 4 cyfry + 1 null

        sprintf(t_out,"\033[%lu;1H",x+2);

        size_t size = strlen(t_out);
        f_buffer_size += size;
        f_buffer_size_newlines_debug += size;

        memcpy(ff_out+f_buffer_size-size,t_out,size+1);
    }

    // Fast Buffer Writer and cleaner
    void ConsoleHandler::WriteFastBuffer()
    {
        fwrite(ff_out,sizeof(char),f_buffer_size,stdout);
    }
    
    void ConsoleHandler::debugFastBuffer()
    {
        double avg = f_buffer_size_debug / (_height*_width);

        std::cout << "avarage size usage per 'pixel' in Bytes: " << avg << " \n" << "ff_out_buffer size: " << f_buffer_size_debug  << " B " << f_buffer_size_debug / 1024 << " KB " << (f_buffer_size_debug / (1024*1024)) << " MB " << std::endl;
    }

} // namespace op
