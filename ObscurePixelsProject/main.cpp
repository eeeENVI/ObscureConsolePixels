#include "include/OP/ConsoleHandler.h"
#include "include/OP/Clock.h"
#include <time.h>
#include <iostream>
#include <vector>
#include <math.h>

using namespace op;

int size_x = 600;
int size_y = 200;

void drawCircle(ConsoleHandler* handler,Vector2f position,int radius, Color color)
{
    Vertex* circle = new Vertex[4*(radius*radius)];

    for(int y = 0; y < radius+1;++y)
    {
        for(int x = 0; x < radius+radius+1;++x)
        {
            circle[x + y * (radius+radius+1)].setPosition(Vector2i(position.x + x,position.y + y));

            int dx = (x)-radius;
            int dy = (y*2)-radius;

            if(dx*dx + dy*dy <= radius*radius)
            {
                circle[x + y * (radius+radius+1)].setBg(color);
            }
            else
            {
                circle[x + y * (radius+radius+1)].setBg(Color(255,0,255,0));
            }

        }
    }

    handler->draw(circle,4*(radius*radius));
    delete circle;
}

// default position (0,0)
void drawRectangle(ConsoleHandler* handler,Color color, Vector2i size, Vector2f position = Vector2f(0,0))
{
    Vertex* rect = new Vertex[size.x * size.y];

    for(int y = 0; y < size.y;++y)
    {
        for(int x = 0; x < size.x;++x)
        {
            rect[x + y * size.x].setPosition(Vector2i(position.x + x,position.y + y));
            rect[x + y * size.x].setBg(color);
        }
    }

    handler->draw(rect,size.x*size.y);
    delete rect;
}

struct particle
{
    Vector2f pos;
    Vector2f vel;
    Color color;

    int r;

    particle(Vector2f p,int radius,Color c)
    {
        pos = p;
        r = radius;
        color = c;
        vel = Vector2f(0,0);
    }

    void draw(ConsoleHandler* hndlr)
    {
        drawRectangle(hndlr,color,Vector2i(1,1),pos);
        //drawCircle(hndlr,pos,r,color);
    }
};


//imagine 3 types; 10,20,30
void updateParticles(std::vector<particle>& particles1,std::vector<particle>& particles2,double g)
{
    for(auto &a : particles1) {

    double fx = 0;
    double fy = 0;

    for(auto const &b : particles2) {

        double dx = a.pos.x - b.pos.x;
        double dy = 2*(a.pos.y - b.pos.y);
        double d = sqrt(dx*dx + dy*dy);

        if(d > 0 && d < 80)
        {
            double f = g * 1 / d;
            fx += f * dx;
            fy += f * dy;
        }

    }
    a.vel.x = (a.vel.x + fx)*0.5;
    a.vel.y = (a.vel.y + fy)*0.5;

    a.pos.x += a.vel.x;
    a.pos.y += a.vel.y;

    if(a.pos.x <= 0 || a.pos.x >= size_x) a.vel.x *= -1;
    if(a.pos.y <= 0 || a.pos.y >= size_y) a.vel.y *= -1;
    
    }
}

int main()
{
    srand(time(NULL));
        
    // full HD our goal : 2 073 600
    // 1920 x 1080
    // standard is 193 x 53
  
    Vertex* shape = new Vertex[size_x * size_y];

     for(int y = 0 ; y < size_y; ++y)
     {
        for(int x = 0; x < size_x;++x)
        {
            shape[x + y * size_x].setPosition(Vector2i(x,y));  
            //if(x + y * size_x <= (size_x*size_y)/3) shape[x + y * size_x].setBg(Color(224,rand()%32 + 192,224));
           // if(x + y * size_x>= (size_x*size_y)/3)  shape[x + y * size_x].setBg(Color(224,rand()%32 + 192,224));   
            //if(x + y * size_x>= (size_x*size_y)*2/3)  shape[x + y * size_x].setBg(Color(224,rand()%32 + 192,224));
            //rect[j + i * size_y].setBg(Color(rand()%64,rand()%64,rand()%64));
            //rect[j + i * size_y].setBg(Color(0,10+i%50,0));
        }
     }
    
    // 60 fps
    ConsoleHandler console(size_x, size_y);
    Clock clock;

    int mod = 3;
    long double iTime = 1;
    double maxFps = 0.0; double maxElapsed = 0.0;
    double minFps = 0.0; double minElapsed = 0.0;
    double elapsedTime = 0.0;
    double dt = 0.0;

    std::vector<particle> reds;
    std::vector<particle> yellows;
    std::vector<particle> greens;
    std::vector<particle> blacks;
    int p_num1 = 200;
    int p_num2 = 200;
    int p_num3 = 200;
    int p_num4 = 1;

    for(int p = 1; p < p_num1+1;++p)
    {
        particle pt(Vector2f(rand()%size_x,rand()%size_y),3,Color(255,0,0,255));
        reds.push_back(pt);
    }

    for(int p = 1; p < p_num2+1;++p)
    {
        particle pt(Vector2f(rand()%size_x,rand()%size_y),3,Color(255,255,0,255));
        yellows.push_back(pt);
    }

    for(int p = 1; p < p_num3+1;++p)
    {
        particle pt(Vector2f(rand()%size_x,rand()%size_y),3,Color(0,255,0,255));
        greens.push_back(pt);
    }

    for(int p = 1; p < p_num4+1;++p)
    {
        particle pt(Vector2f(size_x/2,size_y/2),6,Color(0,0,0,248));
        blacks.push_back(pt);
    }


    while(console.isOpen())
    {   
        // fps test
            /*int i = 0;
            double time = clock.restart();
            while(i < (1.0 / time ))
            {
                ++i;
            }*/
            dt += clock.restart();

            /*for(int i = 0;i < size_x*size_y;++i)
            {
               /*Vector2f vec2 = Vector2f(shape[i].getPosition().x/size_x,shape[i].getPosition().y/size_y);

                double r = 0.5 + 0.5 * cos(iTime+vec2.x+vec2.y+2);
                double g = 0.5 + 0.5 * cos(iTime+vec2.x+vec2.y+0);
                double b = 0.5 + 0.5 * cos(iTime+vec2.x+vec2.y+4);
                double a = 0.5 + 0.5 * cos(iTime+vec2.x+vec2.y+0);

                shape[i].setBg(Color(r*255,g*255,b*255,a*255));
                iTime += dt;*/
                
                //iTime += (vec2.x)/(0.005+vec2.y);
                //iTime += vec2.y/(0.005+vec2.x);

                /*int r = rand()%192 + 16;
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
                
            }   */  
            //console.moveView(Vector2i(rand()%3 -1,rand()%3 - 1));
            updateParticles(greens,greens,-0.32);
            updateParticles(greens,reds,-0.17);
            updateParticles(greens,yellows,0.34);

            updateParticles(reds,reds,-0.1);
            updateParticles(reds,greens,-0.34);

            updateParticles(yellows,yellows,0.15);
            updateParticles(yellows,greens,-0.2);

            /*updateParticles(yellows,blacks,-1);
            updateParticles(reds,blacks,-1);
            updateParticles(greens,blacks,-1);*/

            console.clear(Color(32,32,32));

            //console.draw(shape,size_x*size_y);  
            for(int i = 0;i<reds.size();++i) reds[i].draw(&console);
            for(int i = 0;i<yellows.size();++i) yellows[i].draw(&console);
            for(int i = 0;i<greens.size();++i) greens[i].draw(&console);
            //for(int i = 0;i<blacks.size();++i) blacks[i].draw(&console);
            console.display(); 

            elapsedTime = clock.getElapsedTime();
            std::cout << "Time need to process buffer (" << size_x << " x " << size_y << ") in seconds: " << elapsedTime << " | FPS: " << 1.0 / elapsedTime;
            if(maxFps < 1.0 / elapsedTime)
            { 
                maxFps = 1.0 / elapsedTime;
                maxElapsed = elapsedTime;
                minFps = maxFps;
                minElapsed = maxElapsed;
            }
            if(minFps > 1.0 / elapsedTime)
            {
                minFps = 1.0 / elapsedTime;
                minElapsed = elapsedTime;
            }
            std::cout << "\nMaxFps: " << maxFps << " | " << maxElapsed << "\nMinFps: " << minFps << " | " << minElapsed << std::endl;
       // std::cout << "(i) Loops: " << i << "\n";
        dt = 0;
    }

    return 0;
}
