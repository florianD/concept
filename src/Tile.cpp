#include "../include/Tile.h"

namespace rpg
{
    Tile::Tile(int x, int y, int type) : d_type(type)
    {
        d_box.x = x;
        d_box.y = y;
        d_box.w = config::SIDE;
        d_box.h = config::SIDE;
    }

    void Tile::render(Image &im, SDL_Renderer *renderer, SDL_Rect &camera, std::vector<SDL_Rect> &tileClips)
    {
        im.render(renderer, d_box.x - camera.x, d_box.y - camera.y, &tileClips[d_type]);
    }

    int Tile::getType() const
    {
        return d_type;
    }

    SDL_Rect Tile::getBox() const
    {
        return d_box;
    }

    Tile::~Tile()
    {
    }
}
