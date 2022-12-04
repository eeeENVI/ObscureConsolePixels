#include "include/OP/ConsoleHandler.h"
#include "include/OP/Clock.h"
#include <time.h>

using namespace op;

int main()
{
    srand(time(NULL));
    
    Color c(255,0,0);
    
    ConsoleHandler console(20,10,false,true);

    Clock clock;

    double dt = 0.0;

    VertexArray line;
    line.resize(10);
   

    for(int i = 0; i < 10;i++)
                for(int j = 0; j < 1;j++)
                {
                    line[j + i * 1].bgColor = Color(rand()%128 + 128,rand()%128 + 128,rand()%128 + 128);
                    line[j + i * 1].setPosition(Vector2f(float(0),float(i)));
                    line[j + i * 1].setChar(' ');          
                }

    VertexArray rect;
    rect.resize(8);

     for(int i = 0; i < 4;i++)
                for(int j = 0; j < 2;j++)
                {
                    rect[j + i * 2].bgColor = Color(rand()%128 + 128,rand()%128 + 128,rand()%128 + 128);
                    rect[j + i * 2].setPosition(Vector2f(float(i+5),float(j+2)));
                    rect[j + i * 2].setChar('@');   
                }


    while(console.isOpen())
    {
        dt += clock.getElapsedTime();

        if(dt >= 5.0 / 60.0) 
        {
            // update

            console.clear();
            console.draw(line);
            console.draw(rect);
            console.display(); 

            console.moveView(Vector2i(-1,0));
         
            dt = 0;
        }
        clock.restart();
    }

    return 0;
}
