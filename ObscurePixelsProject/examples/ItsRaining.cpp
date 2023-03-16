#include "../include/OP/ConsoleHandler.h"
#include "../include/OP/Clock.h"
#include <time.h>
#include <math.h>

using namespace op;

    // standard is 193 x 53

const int size_x = 193;
const int size_y = 53;

int main()
{
    srand(time(NULL));
  
    Vertex* shape = new Vertex[size_x * size_y];

     for(int y = 0 ; y < size_y; ++y)
     {
        for(int x = 0; x < size_x;++x)
        {
            shape[x + y * size_x].setPosition(Vector2i(x,y));  
        }
     }
    
    // 60 fps
    ConsoleHandler console(size_x, size_y,60);
    Clock clock;

    double dt = 0.0;

    while(console.isOpen())
    {   
        for(int i = 0;i < size_x*size_y; ++i)
        {
            int r = rand()%192 + 16;
            int g = rand()%32;
            int b = rand()%64;

            if(r < g)
            {
                shape[i].setBg(Color(0,g,b,rand()%128 + 128));
            }
            else
            {   
                shape[i].setBg(Color(0,0,0));  
            }  
            
        }   
        
        console.clear();

        console.draw(shape,size_x*size_y);  
        
        console.display(); 
    }

    return 0;
}
