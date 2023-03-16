#include "../include/OP/ConsoleHandler.h"
#include "../include/OP/Clock.h"
#include <math.h>

using namespace op;

// standard console resolution with font 11 on fullscreen (f11) is 193 x 53

const int size_x = 600;
const int size_y = 300;

int main()
{
    // raw method
    Vertex* shape = new Vertex[size_x * size_y];

     for(int y = 0 ; y < size_y; ++y) {
        for(int x = 0; x < size_x;++x) {
            shape[x + y * size_x].setPosition(Vector2i(x,y)); 
        }
    }
    

    // 60 fps
    ConsoleHandler console(size_x, size_y,60);
    Clock clock;

    double dt = 0.0;
    double iTime = 0.0;

    while(console.isOpen()) {   

        dt = clock.restart();

        for(int i = 0; i < size_x*size_y; ++i)
        {
            // normalizing vector ( 0 ; 1 )
            Vector2f u = Vector2f(shape[i].getPosition().x/size_x,shape[i].getPosition().y/size_y);

            double r = 0.5 + 0.5 * cos(iTime + u.x + 4);
            double g = 0.5 + 0.5 * cos(iTime + u.y + 2);
            double b = 0.5 + 0.5 * cos(iTime + u.x + 0);

            // Alpha channel
            //double a = 0.5 + 0.5 * cos(iTime+u.x+u.y+0);

            shape[i].setBg(Color(r*255,g*255,b*255));
        }   

        iTime += dt * 0.5;

        console.clear();

        console.draw(shape,size_x*size_y);  
        
        console.display(); 
    }

    return 0;
}
