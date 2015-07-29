#include "../include/Image.h"

namespace rpg
{
    Image::Image() : d_texture(NULL), d_width(0), d_height(0)
    {
    }

    bool Image::load(string path, SDL_Renderer *gRenderer)
    {
        free();

        SDL_Texture* newTexture = NULL;

        SDL_Surface* loadedSurface = IMG_Load(path.c_str());
        if(loadedSurface == NULL)
        {
            printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
        }
        else
        {
            SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0x00));

            newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
            if(newTexture == NULL)
            {
                printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
            }
            else
            {
                //SDL_QueryTexture(newTexture, NULL, NULL, &d_width, &d_height);
                d_width = loadedSurface->w;
                d_height = loadedSurface->h;
            }
            SDL_FreeSurface(loadedSurface);
        }

        d_texture = newTexture;
        return d_texture != NULL;
    }

    void Image::free()
    {
        if(d_texture != NULL)
        {
            SDL_DestroyTexture(d_texture);
            d_texture = NULL;
        }
    }

    void Image::render(SDL_Renderer *gRenderer, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
    {
        SDL_Rect renderQuad = {x, y, d_width, d_height};

        if(clip != NULL)
        {
            renderQuad.w = clip->w;
            renderQuad.h = clip->h;
        }

        SDL_RenderCopyEx(gRenderer, d_texture, clip, &renderQuad, angle, center, flip);
    }

    int Image::getWidth() const
    {
        return d_width;
    }

    int Image::getHeight() const
    {
        return d_height;
    }

    Image::~Image()
    {
        free();
    }
}
