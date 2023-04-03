#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL_timer.h>
#include<SDL2/SDL_image.h>

#define WIDTH (640)
#define HEIGHT (480)

// speed in pixels/second
#define SPEED (300)

using namespace std;

int main(int argc, char* argv[]) 
{

    // attempt to initialize graphics and timer system
    if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0) 
    {
        cout << "error initializing SDL" << SDL_GetError() << endl;
    }

    SDL_Window* win = SDL_CreateWindow("Hello, C550!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
    if(!win) 
    {
         cout << "error creating window" << SDL_GetError() << endl;
         SDL_Quit();
         return 1;
    }

    
    // creater a renderer, which sets up the graphics hardware
    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);
    if(!rend) 
    {
    // clean up resources before exiting
    cout << "error creating renderer" << SDL_GetError() << endl; 
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 1;
    }


    // load the image into memory using SDL_image library function
    // bmp, png, gif ... all good
    SDL_Surface* surface = IMG_Load("res/pic1.bmp");
    if(!surface) 
    {
        cout << "error creating surface" << SDL_GetError() << endl;
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }


    // load the image data into the graphics hardware's memory
    SDL_Texture *tex = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);
    if(!tex) 
    {
        cout << "error creating texture" << SDL_GetError() << endl;
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    // struct to hold the position and size of the sprite
    SDL_Rect dest;

    // get the dimensions of texture
    SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);
    dest.w /= 4;
    dest.h /= 4;
    
    // start sprite in center of screen
    float x_pos = (WIDTH - dest.w) / 2;
    float y_pos = (HEIGHT - dest.h) / 2;
    float x_vel = 0;
    float y_vel = 0;
    
    // keep track of which inputs are given
    int up = 0; 
    int down = 0;
    int left = 0;
    int right = 0;

    // set to 1 when window close button is pressed
    int close = 0;

    // animation loop
    while(!close) 
    {
        // process event
        SDL_Event e;
        while(SDL_PollEvent(&e))
        {
            switch (e.type)
            { 
            case SDL_QUIT:

                close = 1;
                break;
                
            case SDL_KEYDOWN:

                switch (e.key.keysym.scancode)
                {
                case SDL_SCANCODE_A:
                case SDL_SCANCODE_LEFT:
                    left = 1;
                    break;
                case SDL_SCANCODE_D:
                case SDL_SCANCODE_RIGHT:
                    right = 1;
                    break;
                case  SDL_SCANCODE_W:
                case SDL_SCANCODE_UP:
                    up = 1;
                    break;
                case SDL_SCANCODE_S:
                case SDL_SCANCODE_DOWN:
                    down = 1;
                    break;
                } 

                break;
            case SDL_KEYUP:

                switch (e.key.keysym.scancode)
                {
                case SDL_SCANCODE_A:
                case SDL_SCANCODE_LEFT:
                    left = 0;
                    break;
                case SDL_SCANCODE_D:
                case SDL_SCANCODE_RIGHT:
                    right = 0;
                    break;
                case SDL_SCANCODE_W:
                case SDL_SCANCODE_UP:
                    up = 0;
                    break;
                case SDL_SCANCODE_S:
                case SDL_SCANCODE_DOWN:
                    down = 0;
                    break;
                }

                break;
            }
        }
        // determine velocity
        x_vel = y_vel = 0;
        if(up && !down) y_vel = -SPEED;
        if(down && !up) y_vel = SPEED;
        if(left && !right) x_vel = -SPEED;
        if(right && !left) x_vel = SPEED;

        // update positions
        x_pos += x_vel / 60;
        y_pos += y_vel / 60;

        // collision detection with bounds
        if(x_pos <= 0) x_pos = 0;
        if(y_pos <= 0) y_pos = 0;
        if(x_pos >= WIDTH - dest.w) x_pos = WIDTH - dest.w;
        if(y_pos >= HEIGHT - dest.h) y_pos = HEIGHT - dest.h;

        // set the position in the struct 
        dest.y = (int) y_pos;
        dest.x = (int) x_pos;

        // clear the window
        SDL_RenderClear(rend);

        // draw the image to the window
        SDL_RenderCopy(rend, tex, NULL, &dest);
        SDL_RenderPresent(rend);

        // wait 1/60th of a second
        SDL_Delay(1000/60);
    }

    // clean up resources before exiting
    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}