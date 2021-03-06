#include "../include/Image.h"

namespace rpg
{
    Image::Image() : d_texture(NULL), d_width(0), d_height(0)
    {
    }

    bool Image::load(std::string path, SDL_Renderer *gRenderer)
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
            SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0xFF, 0xFF, 0xFF));

            newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
            if(newTexture == NULL)
            {
                printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
            }
            else
            {
                d_width = loadedSurface->w;
                d_height = loadedSurface->h;
            }
            SDL_FreeSurface(loadedSurface);
        }
        d_texture = newTexture;
        return d_texture != NULL;
    }

    bool Image::loadText(std::string text, SDL_Color color, SDL_Renderer *gRenderer, TTF_Font *gFont)
    {
        free();

        SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, text.c_str(), color);
        if(textSurface != NULL)
        {
            d_texture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
            if(d_texture == NULL)
            {
                printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
            }
            else
            {
                d_width = textSurface->w;
                d_height = textSurface->h;
            }
            SDL_FreeSurface(textSurface);
        }
        else
        {
            printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
        }
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
