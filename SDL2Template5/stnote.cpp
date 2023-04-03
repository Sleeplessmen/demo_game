/*
    // clear the window
    SDL_RenderClear(rend);

    // draw the image to the window
    SDL_RenderCopy(rend, tex, NULL, NULL);
    SDL_RenderPresent(rend);

    // wait a few seconds
    SDL_Delay(5000);

    // clean up resources before exiting
    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
*/



/*
    // struct to hold the position and size of the sprite
    SDL_Rect dest;

    // get the dimensions of texture
    SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);

    // position the sprite at the bottom center of the window
    // origin is the top left corner, position y is down
    dest.x = (WIDTH - dest.w) / 2;

    // require float resolution for y position
    float y_pos = HEIGHT;

    // animation loop
    while(dest.y >= -dest.h) {
        // clear the window
        SDL_RenderClear(rend);

        // set the y position in the struct
        dest.y = (int) y_pos;

        // draw the image to the window
        SDL_RenderCopy(rend, tex, NULL, &dest);
        SDL_RenderPresent(rend);

        // update sprite position
        y_pos -= (float) SPEED / 60;

        // wait 1/60th of a second
        SDL_Delay(1000/60);
    }
*/



/*
    // struct to hold the position and size of the sprite
    SDL_Rect dest;

    // get the dimensions of texture
    SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);
    dest.w /= 4;
    dest.h /= 4;
    
    // start sprite in center of screen
    float x_pos = (WIDTH - dest.w) / 2;
    float y_pos = (HEIGHT - dest.h) / 2;
    
    // give sprite initial velocity
    float x_vel = SPEED;
    float y_vel = SPEED;

    // set to 1 when window close button is pressed
    int close = 0;

    // animation loop
    while(!close) 
    {
        // process event
        SDL_Event e;
        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT) 
            {
                close = 1;
            }
        }
        
        // collision detection with bounds
        if(x_pos <= 0) 
        {
            x_pos = 0;
            x_vel = -x_vel;
        }
        if(y_pos <= 0) 
        {
            y_pos = 0;
            y_vel = -y_vel;
        }
        if(x_pos >= WIDTH - dest.w) 
        {
            x_pos = WIDTH - dest.w;
            x_vel = -x_vel;
        }
        if(y_pos >= HEIGHT - dest.h) 
        {
            y_pos = HEIGHT - dest.h;
            y_vel = -y_vel;
        }

        // update positions
        x_pos += x_vel / 60;
        y_pos += y_vel / 60;

        // set the positions in the struct 
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
*/