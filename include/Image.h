#ifndef IMAGE_H
#define IMAGE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <iostream>
#include "config.h"
using std::string;
using std::ostream;
using std::istream;
using std::endl;

namespace rpg
{
    class Image
    {
        public:
            Image();
            ~Image();
            bool load(string path, SDL_Renderer *gRenderer);
            //bool loadFromFile(string path);
            void free();
            void render(SDL_Renderer *gRenderer, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
            //void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
            int getWidth() const;
            int getHeight() const;
        private:
            int d_width, d_height;
            SDL_Texture* d_texture;
    };
}

#endif // IMAGE_H
