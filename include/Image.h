#ifndef IMAGE_H
#define IMAGE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>

namespace rpg
{
    class Image
    {
        public:
            Image();
            ~Image();
            bool load(std::string path, SDL_Renderer *gRenderer);
            void free();
            void render(SDL_Renderer *gRenderer, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
            int getWidth() const;
            int getHeight() const;
        private:
            int d_width, d_height;
            SDL_Texture* d_texture;
    };
}

#endif // IMAGE_H