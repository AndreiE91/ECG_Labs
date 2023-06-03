//
//  main.cpp
//  SDL_Lab1
//
//  Created by CGIS on 16/02/16.
//  Copyright © 2016 CGIS. All rights reserved.
//

#include <iostream>
#include "include\SDL.h"
#include "transform.h"
#include <cmath>
#include <vector>
#include <stdbool.h>

using namespace egc;

SDL_Renderer *windowRenderer;
// define rectangle vertices
std::vector<vec3> myPoints;

//define window dimensions
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

SDL_Window *window = NULL;
SDL_Event currentEvent;

mat3 matrix;
vec3 pivotPoint;

SDL_Rect rectangleCoordinates = {100, 100, 200, 200};

bool quit = false;

int mouseX, mouseY;

vec3 initial;
bool firstTime = true;

void updateLines() {
    float previousX = initial.x;
    float previousY = initial.y;
    for (vec3 point : myPoints) {
        SDL_RenderDrawLine(windowRenderer, previousX, previousY, point.x, point.y);
        previousX = point.x;
        previousY = point.y;
    }
    SDL_RenderDrawLine(windowRenderer, previousX, previousY, initial.x, initial.y);
}

vec3 centerPoint() {
    float sumX = initial.x;
    float sumY = initial.y;
    for (const auto& point : myPoints) {
        sumX += point.x;
        sumY += point.y;
    }
    float x = sumX / float(myPoints.size() + 1);
    float y = sumY / float(myPoints.size() + 1);
    return vec3(x, y, 1.0f);
}

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
			// Create a renderer for the current window
			windowRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

			if(windowRenderer == NULL)
            {
                std::cout << "Failed to create the renderer: " << SDL_GetError() << std::endl;
                success = false;
            }
            else
            {
                //Set background color
				SDL_SetRenderDrawColor(windowRenderer, 255, 255, 255, 255);
			
                //Apply background color
                SDL_RenderClear(windowRenderer);
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
                    if (firstTime) {
                        initial.x = mouseX;
                        initial.y = mouseY;
                        initial.z = 1;
                        firstTime = false;
                        std::cout << initial << std::endl;
                    }
                    else {
                        myPoints.push_back(vec3(mouseX, mouseY, 1));
                        pivotPoint = centerPoint();
                    }
                }

                if (currentEvent.button.button == SDL_BUTTON_RIGHT)
                {
                    SDL_GetMouseState(&mouseX, &mouseY);
                    std::cout << "Mouse click => " << "x: " << mouseX << ", y: " << mouseY << std::endl;
                    pivotPoint = vec3(mouseX, mouseY, 1);
                }
            }
            
            //Mouse event -> mouse movement
            if(currentEvent.type == SDL_MOUSEMOTION)
            {
                if(currentEvent.button.button == SDL_BUTTON_LEFT)
                {
                    SDL_GetMouseState(&mouseX, &mouseY);
                    std::cout << "Mouse move => " << "x: " << mouseX << ", y: " << mouseY << std::endl;
                }
            }
            
            //Keyboard event
            if(currentEvent.type == SDL_KEYDOWN)
            {
                switch(currentEvent.key.keysym.sym)
                {
                    case SDLK_UP: 
                    {
                        matrix = egc::translate(pivotPoint.x, pivotPoint.y) * egc::scale(1.1f, 1.1f) * egc::translate(-pivotPoint.x, -pivotPoint.y);
                        break;
                    }
                    case SDLK_DOWN:
                    {
                        matrix = egc::translate(pivotPoint.x, pivotPoint.y) * egc::scale(1/1.1f, 1/1.1f) * egc::translate(-pivotPoint.x, -pivotPoint.y);
                        break;
                    }
                    case SDLK_r: {
                        myPoints.clear();
                        firstTime = true;
                        break;
                    }
                    case SDLK_LEFT: // rotate counterclockwise
                    {
                        matrix = egc::translate(pivotPoint.x, pivotPoint.y) * egc::rotate(-10.0f) * egc::translate(-pivotPoint.x, -pivotPoint.y);
                    }
                    break;

                    case SDLK_RIGHT: // rotate clockwise
                    {
                        matrix = egc::translate(pivotPoint.x, pivotPoint.y) * egc::rotate(10.0f) * egc::translate(-pivotPoint.x, -pivotPoint.y);
                    }
                    break;

                    default:                        
                        break;
                }
                initial = matrix * initial;
                std::cout << initial << std::endl;
                for (vec3 &point : myPoints) {
                    point = matrix * point;
                }
            }
            
			
            // Clear the window
            SDL_SetRenderDrawColor(windowRenderer, 255, 255, 255, 255);
            SDL_RenderClear(windowRenderer);

            // Draw the rectangle
            SDL_SetRenderDrawColor(windowRenderer, 0, 0, 255, 255);

            updateLines();

            // Update the window
            SDL_RenderPresent(windowRenderer);
        }
    }
    
    destroyWindow();
    return 0;
}
