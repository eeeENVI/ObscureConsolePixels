#include "../../include/OP/ConsoleHandler.h"
#include "../../include/OP/Drawable.h"

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

        delete[] Screen;

        if(_alt_buffer) printf(CSI "?1049l"); // leave alternative buffer
    }

    //inits
    void ConsoleHandler::initScreen()
    {
        _defaultBgClear = Color(0,0,0);

        view = Vector2i(0,0); 

        Screen = new Vertex[_width * _height];

        for(unsigned x = 0; x < _width;x++) 
        {
            for(unsigned y = 0; y < _height;y++)
            {
                Screen[x + y * _width] = Vertex(Vector2f(float(x),float(y)));
            }
        }
    }

    void ConsoleHandler::initScreenStatus()
    {
        if(fast_buffer == true)
        {
            // .. code
        }

        //settings of terminal
        if(_alt_buffer) printf(CSI "?1049h"); // enter alternative buffer

        printf(HIDE_CURSOR);
        printf(CLEAR);

        //settings of console handler
        setFramePerSecondRate(0);
        _open = true;
    }

    // accessors
    bool ConsoleHandler::isOpen() const
    {
        return _open;
    }

    //setters
    void ConsoleHandler::setFramePerSecondRate(unsigned rate)
    {
        _framePerSecondRateLimit = rate;
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
    // Clear screen with aditional parameter that fills up it with color
    void ConsoleHandler::clear(const Color bg )
    {
        _defaultBgClear = bg;
        //printf(CSI BG "%d;%d;%dm",+bg.r,+bg.g,bg.b); 
        if(fast_buffer == false) printf(CLEAR);

        for(unsigned x = 0; x < _width;x++)
        {
            for(unsigned y = 0; y < _height;y++)
            {
                Screen[x + y * _width].bgColor = _defaultBgClear;
                Screen[x + y * _width].setChar(' ');
                //printCh(' ',bg,bg);
            }
            //printf(CSI "%d;1H",x+2);
        }
        setDefaultPrintingMode();
    }

    void ConsoleHandler::draw(const Drawable& drawable)
    {
        drawable.draw(*this);
    }

    void ConsoleHandler::draw()
    {
        
    };

    //void ConsoleHandler::draw(const Vertex* vertices, unsigned count_vertices);

    void ConsoleHandler::display()
    {
        for(short x = 0; x < _width;x++)
        {
            for(short y = 0; y < _height;y++)
            {
                // we don't want to destroy background! For this is clear() so ..
                // if there's something diffrent on the screen buffer worth something...
                {
                    // ...Draw it! [psst.. remember about colors ;)]
                    char ch = Screen[x + y * _width].getChar();
                    Color c1 = Screen[x + y * _width].fgColor;
                    Color c2 = Screen[x + y * _width].bgColor;

                    if(fast_buffer == true)
                    {
                        // fast char buffer pointer  
                        char* fcbp = &ch;
;
                        // colors
                        printf(CSI FG "%d;%d;%dm" CSI BG "%d;%d;%dm" ,+c1.r,+c1.g,+c1.b,+c2.r,+c2.g,c2.b);

                        // stdout
                        fwrite(fcbp,sizeof(char),1,stdout);

                        printf(SGR_RES); 
                    }
                    else
                    {
                        printCh(ch,c1,c2);
                    }
                }
            }
            printf(CSI "%d;1H",x+2);   
        }
        setDefaultPrintingMode();
    }    

    //Most important drawer
    void ConsoleHandler::printCh(const char c,const Color fg ,const Color bg )
    {
        printf(CSI FG "%d;%d;%dm" CSI BG "%d;%d;%dm%c" ,+fg.r,+fg.g,+fg.b,+bg.r,+bg.g,bg.b,c);
        printf(SGR_RES);
    }
    
} // namespace op
