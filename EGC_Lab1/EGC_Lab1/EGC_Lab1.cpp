//
//  main.cpp
//  SDL_Lab1
//
//  Created by CGIS on 16/02/16.
//  Copyright © 2016 CGIS. All rights reserved.
//

#include <iostream>
#include "include\SDL.h"

//define window dimensions
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

SDL_Window *window = NULL;
SDL_Surface *windowSurface = NULL;
SDL_Event currentEvent;

SDL_Rect rectangleCoordinates = {100, 100, 200, 200};
Uint32 rectagleColor;

int selected_color = 0;
int red = 0;
int green = 0;
int blue = 0;
int firstClickX, firstClickY;

bool quit = false;

int mouseX, mouseY;

bool initWindow()
{
    bool success = true;
    
    //Try to initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL initialization failed" << std::endl;
        success = false;
    }
    else{
        //Try to create the window
        window = SDL_CreateWindow("SDL Hello World Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);
        
        if(window == NULL)
        {
            std::cout << "Failed to create window: " << SDL_GetError() << std::endl;
            success = false;
        }
        else
        {
            //Try to get the window surface
            windowSurface = SDL_GetWindowSurface(window);
            
            if(windowSurface == NULL)
            {
                std::cout << "Failed to get the window surface: " << SDL_GetError() << std::endl;
                success = false;
            }
            else
            {
                //Initialize surface color
                SDL_FillRect(windowSurface, NULL, SDL_MapRGB(windowSurface->format, 255, 255, 255));
                
                //Update the surface
                SDL_UpdateWindowSurface(window);
            }

        }
    }
    
    return success;
}

void destroyWindow()
{
    //Destroy window
    SDL_DestroyWindow(window);
    window = NULL;
    
    //Quit SDL
    SDL_Quit();
}

int main(int argc, char * argv[]) {
    if(!initWindow())
    {
        std::cout << "Failed to initialize" << std::endl;
        return -1;
    }
    
    rectagleColor = SDL_MapRGB(windowSurface->format, red, green, blue);
    
    while (!quit) {
        //Handle events on queue
        if(SDL_WaitEvent(&currentEvent) != 0)
        {
            //User requests quit
            if(currentEvent.type == SDL_QUIT)
            {
                quit = true;
            }
            
            //Mouse event -> pressed button
            if(currentEvent.type == SDL_MOUSEBUTTONDOWN)
            {
                if(currentEvent.button.button == SDL_BUTTON_LEFT)
                {
                    SDL_GetMouseState(&mouseX, &mouseY);
                    std::cout << "Mouse click => " << "x: " << mouseX << ", y: " << mouseY << std::endl;

                    SDL_FillRect(windowSurface, NULL, SDL_MapRGB(windowSurface->format, 255, 255, 255));
                    rectangleCoordinates.x = mouseX;
                    rectangleCoordinates.y = mouseY;
                    firstClickX = mouseX;
                    firstClickY = mouseY;
                }
                
            }
            
            //Mouse event -> mouse movement
            if(currentEvent.type == SDL_MOUSEMOTION)
            {
                if(currentEvent.button.button == SDL_BUTTON_LEFT)
                {
                    SDL_GetMouseState(&mouseX, &mouseY);
                    std::cout << "Mouse move => " << "x: " << mouseX << ", y: " << mouseY << std::endl;

                    if (mouseX >= firstClickX) {
                        rectangleCoordinates.w = abs(rectangleCoordinates.x - mouseX);
                    }
                    if (mouseY >= firstClickY) {
                        rectangleCoordinates.h = abs(rectangleCoordinates.y - mouseY);
                    }
                    if (mouseX < firstClickX) {
                        rectangleCoordinates.x = mouseX;
                        rectangleCoordinates.w = abs(firstClickX - mouseX);
                    }
                    if (mouseY < firstClickY) {
                        rectangleCoordinates.y = mouseY;
                        rectangleCoordinates.h = abs(firstClickY - mouseY);
                    }
                }
                SDL_FillRect(windowSurface, NULL, SDL_MapRGB(windowSurface->format, 255, 255, 255));
                SDL_FillRect(windowSurface, &rectangleCoordinates, rectagleColor);

                SDL_UpdateWindowSurface(window);
            }
            
            //Keyboard event
            if(currentEvent.type == SDL_KEYDOWN)
            {
                switch(currentEvent.key.keysym.sym)
                {
                    case SDLK_UP:
                    {
                        switch (selected_color) {
                            case 0: 
                            {
                                if (red < 255) {
                                    red += 5;
                                }
                                break;
                            }
                            case 1:
                            {
                                if (green < 255) {
                                    green += 5;
                                }
                                break;
                            }
                            case 2:
                            {
                                if (blue < 255) {
                                    blue += 5;
                                }
                                break;
                            }
                            default:
                            {
                                if (red < 255) {
                                    red += 5;
                                }
                                break;
                            }
                        }
                        rectagleColor = SDL_MapRGB(windowSurface->format, red, green, blue);
                        break;
                    }
                    case SDLK_DOWN:
                    {
                        switch (selected_color) {
                        case 0:
                        {
                            if (red > 0) {
                                red -= 5;
                            }
                            break;
                        }
                        case 1:
                        {
                            if (green > 0) {
                                green -= 5;
                            }
                            break;
                        }
                        case 2:
                        {
                            if (blue > 0) {
                                blue -= 5;
                            }
                            break;
                        }
                        default:
                        {
                            if (red > 0) {
                                red -= 5;
                            }
                            break;
                        }
                        }
                        rectagleColor = SDL_MapRGB(windowSurface->format, red, green, blue);
                        break;
                    }
                        
                    case SDLK_r:
                    {
                        selected_color = 0;
                        break;
                    }
                    case SDLK_g:
                    {
                        selected_color = 1;
                        break;
                    }
                    case SDLK_b:
                    {
                        selected_color = 2;
                        break;
                    }
                        
                    default:
                    {
                        rectagleColor = SDL_MapRGB(windowSurface->format, 255, 255, 0);
                        break;
                    }
                }
            }
            
            SDL_FillRect(windowSurface, &rectangleCoordinates, rectagleColor);
            
            SDL_UpdateWindowSurface(window);
        }
    }
    
    destroyWindow();
    return 0;
}
