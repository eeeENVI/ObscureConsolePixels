#include "include/OP/ConsoleHandler.h"
#include "include/OP/Clock.h"
#include <time.h>
#include <iostream>

using namespace op;

int main()
{
    srand(time(NULL));
    
    Color c(255,0,0);
    
    int size_x = 30;
    int size_y = 130;

    char def = ' ';

    ConsoleHandler console(size_x, size_y,0);

    Clock clock;

    double dt = 0.0;

    VertexArray rect;
    rect.resize(size_x*size_y);

    for(int i = 0 ; i < size_x; ++i)
        for(int j = 0; j < size_y;++j)
        {
            rect[j + i * size_y].setPosition(Vector2f(float(i),float(j)));  

            if(j + i * size_y <= (size_x*size_y)/3) rect[j + i * size_y].setBg(Color(rand()%224 + 32,32,32));
            if(j + i * size_y >= (size_x*size_y)/3)  rect[j + i * size_y].setBg(Color(32,rand()%224 + 32,32));   
            if(j + i * size_y >= (size_x*size_y)*2/3)  rect[j + i * size_y].setBg(Color(32,32,rand()%224 + 32));  
        }
             
    double maxFps = 0.0;
    double elapsedTime = 0.0;
    while(console.isOpen())
    {
        dt += clock.getElapsedTime();

        // 0.25 ~ 1fps
        if(dt > 0.25 / 60) 
        {
            console.moveView(Vector2i(rand()%3 - 1,rand()%3 - 1));

            console.clear();    
            console.draw(rect);    
            console.display(); 

            /*elapsedTime = clock.getElapsedTime();
            std::cout << "Time need to process buffer (" << size_x << " x " << size_y << ") in seconds: " << elapsedTime << "\nFPS: " << 1.0 / elapsedTime;
            if(maxFps < 1.0 / elapsedTime) maxFps = 1.0 / elapsedTime;
            std::cout << "\nMaxFps: " << maxFps << std::endl;*/
   
            dt = 0;
        }
        clock.restart();
    }

    return 0;
}
