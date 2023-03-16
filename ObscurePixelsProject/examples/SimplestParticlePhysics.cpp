#include "../include/OP/ConsoleHandler.h"
#include "../include/OP/Clock.h"
#include <time.h>
#include <vector>
#include <math.h>

using namespace op;

// ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! 
// IF YOU"RE INTERESTED IN JUST PARTICLES SKIP TO LINE : 62 

// SUGGESTED resolution 193 x 53 and full screen but change particles parameters
const int size_x = 600;
const int size_y = 300;

// its buggy, needs some refactoring but for tests its enough
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
        // Decide wheter you want rectangles or Circles
        drawRectangle(hndlr,color,Vector2i(1,1),pos);
        //drawCircle(hndlr,pos,r,color);
    }
};


// Simple Physics system ( only 3 newton laws with some constraints and normalized weight = 1)
void updateParticles(std::vector<particle>& particles1,std::vector<particle>& particles2,double g)
{
    for(auto &a : particles1) {

    // Initialize for each particle1, Vector's Force with 0 
    double fx = 0;
    double fy = 0;

    // Iterate through every particle2 
    for(auto const &b : particles2) {

        // Calculate distance 
        double dx = a.pos.x - b.pos.x;
        double dy = 2*(a.pos.y - b.pos.y); // Y dimension for character is 2 times big as X dimension so we need to double the distance to make it look natural
        double d = sqrt(dx*dx + dy*dy);

        // simple constraint ( if distance is less than 0 (LOL) or greater than certain D don't calculate it)
        if(d > 0 && d < 60)
        {

            // G is acceleration that we pass to function, 1 is constant mass for every particle 
            // F = a * m 

            double f = g * 1 / d; 
            
            // We stack up Forces for every particle interaction
            fx += f * dx;
            fy += f * dy;
        }

    }

    // here we add up velocity and acceleration
    a.vel.x = (a.vel.x + fx)*0.5;
    a.vel.y = (a.vel.y + fy)*0.5;

    // we update new position 
    a.pos.x += a.vel.x;
    a.pos.y += a.vel.y;

    // if hits boundaries just turn back
    if(a.pos.x <= 0 || a.pos.x >= size_x) a.vel.x *= -1;
    if(a.pos.y <= 0 || a.pos.y >= size_y) a.vel.y *= -1;
    
    }
}

int main()
{
    srand(time(NULL));
    
    ConsoleHandler console(size_x, size_y,30);

    // generateParticles

    std::vector<particle> reds;
    std::vector<particle> yellows;
    std::vector<particle> greens;

    size_t p_num1 = 200;
    size_t p_num2 = 200;
    size_t p_num3 = 400;

    for(int p = 1; p < p_num1+1 ; ++p)
    {
        particle pt(Vector2f(rand()%size_x,rand()%size_y),3,Color(255,0,0,255));
        reds.push_back(pt);
    }

    for(int p = 1; p < p_num2+1 ; ++p)
    {
        particle pt(Vector2f(rand()%size_x,rand()%size_y),3,Color(255,255,0,255));
        yellows.push_back(pt);
    }

    for(int p = 1; p < p_num3+1 ; ++p)
    {
        particle pt(Vector2f(rand()%size_x,rand()%size_y),3,Color(0,255,0,255));
        greens.push_back(pt);
    }

    while(console.isOpen()) {   

        // How Object 1 react to Object 2 with what force ( - attraction + repulsion )
        updateParticles(greens,greens,-0.32);
        updateParticles(greens,reds,-0.17);
        updateParticles(greens,yellows,0.34);

        updateParticles(reds,reds,-0.1);
        updateParticles(reds,greens,-0.34);

        updateParticles(yellows,yellows,0.15);
        updateParticles(yellows,greens,-0.2);

        console.clear(Color(32,32,32));

        for(int i = 0; i <reds.size(); ++i) reds[i].draw(&console);
        for(int i = 0; i < yellows.size(); ++i) yellows[i].draw(&console);
        for(int i = 0; i < greens.size(); ++i) greens[i].draw(&console);

        console.display(); 

    }

    return 0;
}
