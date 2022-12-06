#include "include/OP/ConsoleHandler.h"
#include "include/OP/Clock.h"
#include <time.h>

using namespace op;

int main()
{
    srand(time(NULL));
    
    Color c(255,0,0);
    
    ConsoleHandler console(100,50,0,1);

    Clock clock;

    double dt = 0.0;

    std::vector<VertexArray> rectangles;

    VertexArray rect;
    rect.resize(8);

     for(int i = 0; i < 4;i++)
                for(int j = 0; j < 2;j++)
                {
                    rect[j + i * 2].bgColor = Color(rand()%128 + 128,rand()%128 + 128,rand()%128 + 128);
                    rect[j + i * 2].fgColor = Color(rand()%128 + 128,rand()%128 + 128,rand()%128 + 128);
                    rect[j + i * 2].setPosition(Vector2f(float(i+10),float(j+5)));
                    rect[j + i * 2].setChar('#');   
                }

    for(int i =0;i<20;i++)  rectangles.push_back(rect);

                
    while(console.isOpen())
    {
        dt += clock.getElapsedTime();

        if(dt > 5.0 / 360.0) 
        {
            // update
            for(int x = 0 ; x < 10; x ++)
            {
                int randx = x*4;
                int randy = x+x;
                for(int i = 0; i < 4;i++)
                {
                    for(int j = 0; j < 2;j++)
                    {
                        rectangles[x][j + i * 2].bgColor = Color(rand()%128 + 128,rand()%128 + 128,rand()%128 + 128);
                        rectangles[x][j + i * 2].fgColor = Color(rand()%128 + 128,rand()%128 + 128,rand()%128 + 128);
                        rectangles[x][j + i * 2].setPosition(float(randx+i),float(randy+j));
                        rectangles[x][j + i * 2].setChar('#');   
                    }
                }
            }

            console.clear();
            for(int i = 0 ; i < 10; i ++)
            {
                console.draw(rectangles[i]);
            }
            console.display(); 
            console.moveView(Vector2i(rand()%3 -1,rand()%3 - 1));
         
            dt = 0;
        }
        clock.restart();
    }

    return 0;
}
