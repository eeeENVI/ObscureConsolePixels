#include "../../include/OP/ConsoleHandler.h"
#include "../../include/OP/Drawable.h"
#include "../../include/OP/Core.h"

#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>

namespace op
{
    ConsoleHandler::ConsoleHandler(unsigned width,unsigned height,double fpsLimit, bool alt_buffer)
    {
        this->_width = width;
        this->_height = height;
        
        this->fps = fpsLimit * fps_const;
        this->fpsLock = 1.0;

        this->_altBuffer = alt_buffer;

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

        if(_altBuffer) printf(CSI "?1049l"); // leave alternative buffer
    }

    //inits
    void ConsoleHandler::initScreenStatus()
    {
        // Prepare terminal
        if(_altBuffer) printf(CSI "?1049h"); // enter alternative buffer

        printf(HIDE_CURSOR);
        printf(CLEAR);

        // settings of console handler
        _open = true;
        DefaultPrintingMode = "\033[1;H\033[0m\0";
    }

    void ConsoleHandler::initScreen()
    {
        view = Vector2i(0,0); 

        Screen = new Vertex[_width * _height];

        // high memory cost higher buffer output efficiency
        //lf_out = new char[((_width * _height) * 40) + (_width * 10) + 10]; // new place for it ( IN DEV) for new LARGE FAST copying

        // low memory cost
        ff_out = new char[(_height * 40) + 20]; // per row

        for(size_t y = 0; y < _height;++y)    
        {
            for(size_t x = 0; x < _width;++x)
            {
                Screen[x + y * _width] =  Vertex();
            }
        }
    }

    // accessors
    bool ConsoleHandler::isOpen()
    {
        dt = clock.restart();

        if(fps != 0)
        {
            fpsLock -= fps * dt; 
            //fpser += fps * fps * dt; 

            if(fpsLock > 0.0)
            {
                return isOpen();
            }

            fpsLock = 1.0;
            //fpser = 0.0 ;
        }
        
        return _open;
    }

    // Setters
    void ConsoleHandler::setFramerateLimit(size_t num)
    {
        fps = num * fps_const;
    }

    void ConsoleHandler::setView(const Vector2i v)
    {
        view = v;
    }

    void ConsoleHandler::moveView(const Vector2i v)
    {
        view += v;
    }

    void ConsoleHandler::setDefaultPrintingMode()
    {
        //printf(CSI "1;H" SGR_RES);
        fwrite(DefaultPrintingMode,sizeof(char),10,stdout);
    }

    // Getters

    Vector2i ConsoleHandler::getView()
    {
        return view;
    }
    
    // Functions
    void ConsoleHandler::close()
    {
    this->_open = false;
    }    

    // assigns CLEARED vertex to screen
    void ConsoleHandler::clear(const Color& bg )
    {        
        for(size_t i = 0; i < _width * _height; ++i)
        {
            Screen[i].setChar(' ');
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

    // THIS WILL BE REDESIGNED CAUSE ITS SHITTY AND UGLY AF
    // Draws designed VertexArray class object vertex by vertex
    void ConsoleHandler::draw(const VertexArray& array)
    {
        if (!array.isEmpty())
        {
            for(int i = 0; i < array.getVertexCount();++i)
            {
                Vector2i pos = array[i].getPosition();

                // Casts Float position of vertex to Integer cause of console screen limits
                // and substracts from it with view offset
                int x = pos.x - view.x;
                int y = pos.y - view.y;

                // Checks if it fits screen position;
                //  || (array[i].getBg() == _defaultBgClear && array[i].getChar() == _defaultChar)
                if((x >= 0 && x < _width && y >= 0 && y < _height) )
                {
                    size_t index = x + y * _width;
                    // Copy ArrayVertex properties to ScreenVertices      
                    Screen[index] = array[i];
                }
            }
        }
    }
   
    // Draws from raw pointer to Vertex, looks for within vertices and draws it
    void ConsoleHandler::draw(const Vertex* vertices, unsigned count_vertices)
    {
        if (count_vertices > 0)
        {
            for(int i = 0; i < count_vertices;++i)
            {
                Vector2i pos = vertices[i].getPosition();

                // Casts Float position of vertex to Integer cause of console screen limits
                // and substracts from it with view offset
                int x = pos.x - view.x;
                int y = pos.y - view.y;

                // Checks if it fits screen position;
                if(y >= 0 && y < _height && x >= 0 && x < _width)
                {
                    size_t index = x + y * _width;
                   
                    // Alpha blending
                    Screen[index].setBg(Color::blendColors(Screen[index].getBg(),vertices[i].getBg()));
                }
            }
        }
    }

    void ConsoleHandler::display()
    {
        // size_x * size_y + number_of_endlines
        f_buffer_size_debug = 0;

        // Drawing per row
        for(size_t y = 0; y < _height;++y)
        {
            fastFormatter(y); // TESTER 
        }

        //WriteFastBuffer(); // TESTER

        // Debuging / Controling
        setDefaultPrintingMode();
        //debugFastBuffer(); 

    }    

    void ConsoleHandler::fastFormatter(size_t y)
    {
        int i = y * _width;
        int cap = i + _width;

        // to save buffer position
        ff_beg = ff_out;

        for(i; i < cap; ++i)
        {
            char c = Screen[i].getChar();
            Color fg = Screen[i].getFg();
            Color bg = Screen[i].getBg();

            if((Screen[(i)-1].getBg() == bg && c == ' ') ||
                (Screen[(i)-1].getFg() == fg && Screen[(i)-1].getBg() == bg))
            {
                // in case of same color parameters or same bg argument and lack of char with fg (space)
                *ff_out++ = c;
                *ff_out = '\0';
            }
            else if(bg == Color(0,0,0) && c == ' ') 
            {
                // in case of cleared pixel that didn't change after clear
                *ff_out++ = '\033';
                *ff_out++ = '[';
                *ff_out++ = '0';
                *ff_out++ = 'm';
                *ff_out++ = c;
                *ff_out = '\0';
            }
            else if(c == ' ' || Screen[(i)-1].getFg() == fg)
            {
                // in case of same fg, we just need to print background
                ff_out += op::Core::formatBgOut(ff_out,bg,c);
            }
            else if(Screen[(i)-1].getBg() == bg)
            {
                // in case of same bg, we just need to print foreground
                ff_out += op::Core::formatFgOut(ff_out,fg,c);
            }
            else 
            {
                // no optimalization
                ff_out += op::Core::formatColorsOut(ff_out,fg,bg,c);
            }  
        }

        ff_out += op::Core::formatLineOut(ff_out,y+2);
        
        // used to determine size of buffer by substracting its value with ff_beg
        size_t ff_length = ff_out - ff_beg;

        // to restore buffer position
        ff_out = ff_beg;

        // print row - end of process
        fwrite(ff_out,sizeof(char),ff_length,stdout);

        // debug
        f_buffer_size_debug += ff_length;
    }

    // Fast Buffer Writer and cleaner
    void ConsoleHandler::WriteFastBuffer()
    {
        // to save buffer position
        lf_beg = lf_out;

        int i;
        int cap;

        for(int y; y < _height;++y)
        {      
            i = y * _width;
            cap = i + _width;

            for(i; i < cap; ++i)
            {
                char c = Screen[i].getChar();
                Color fg = Screen[i].getFg();
                Color bg = Screen[i].getBg();

                if((Screen[(i)-1].getBg() == bg && c == ' ') ||
                    (Screen[(i)-1].getFg() == fg && Screen[(i)-1].getBg() == bg))
                {
                    // in case of same color parameters or same bg argument and lack of char with fg (space)
                    *lf_out++ = c;
                    *lf_out = '\0';
                }
                else if(bg == Color(0,0,0) && c == ' ') 
                {
                    // in case of cleared pixel that didn't change after clear
                    *lf_out++ = '\033';
                    *lf_out++ = '[';
                    *lf_out++ = '0';
                    *lf_out++ = 'm';
                    *lf_out++ = c;
                    *lf_out = '\0';
                }
                else if(c == ' ' || Screen[(i)-1].getFg() == fg)
                {
                    // in case of same fg, we just need to print background
                    lf_out += op::Core::formatBgOut(lf_out,bg,c);
                }
                else if(Screen[(i)-1].getBg() == bg)
                {
                    // in case of same bg, we just need to print foreground
                    lf_out += op::Core::formatFgOut(lf_out,fg,c);
                }
                else 
                {
                    // no optimalization
                    lf_out += op::Core::formatColorsOut(lf_out,fg,bg,c);
                }          
            }

            lf_out += op::Core::formatLineOut(lf_out,y+2);

        }
    
        lf_out += op::Core::formatLineOut(lf_out,1);

        // used to determine size of buffer by substracting its value with ff_beg
        size_t lf_length = lf_out - lf_beg;

        // to restore buffer position
        lf_out = lf_beg;

        // print row - end of process
        fwrite(lf_out,sizeof(char),lf_length,stdout);

        // debug
        f_buffer_size_debug += lf_length;
    }
    
    void ConsoleHandler::debugFastBuffer()
    {
        double avg = f_buffer_size_debug / (_height*_width);

        std::cout << "avarage size usage per 'pixel' in Bytes: " << avg << " | " << "ff_out_buffer size: " << f_buffer_size_debug  << " B " << f_buffer_size_debug / 1024 << " KB " << (f_buffer_size_debug / (1024*1024)) << " MB " << std::endl;
    }

} // namespace op
