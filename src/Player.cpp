#include "../include/Player.h"

namespace rpg
{
    enum
    {
        SOUTH=0, NORTH=2, WEST=4, EAST=6
    };

    Player::Player(int x, int y, int vel, int vx, int vy, std::string name, int orientation, SDL_Renderer *renderer):Character(x, y, vel, vx, vy, name, orientation)
    {
        loadSpriteSheet(renderer);
    }

    bool Player::loadSpriteSheet(SDL_Renderer *renderer)
    {
        bool success = true;

        if(!d_spriteSheetTexture.load("img/object/char/player.png", renderer))
        {
            printf("Failed to load walking animation texture\n");
            success = false;
        }
        else
        {
            d_size_w = (d_spriteSheetTexture.getWidth() / 8);
            d_size_h = (d_spriteSheetTexture.getHeight() / 8);

            d_box.w = 32;
            d_box.h = 32;

            int k = 0;
            for(int i = 0; i < 8; ++i)
            {
                for(int j = 0; j < 8; ++j)
                {
                    d_spriteClips[k].x = j * d_size_w;
                    d_spriteClips[k].y = i * d_size_h;
                    d_spriteClips[k].w = d_size_w;
                    d_spriteClips[k++].h = d_size_h;
                }
            }
        }
        return success;
    }

    Player::~Player()
    {
        d_spriteSheetTexture.free();
    }

    void Player::handleEvent(SDL_Event &e)
    {
        if(e.type == SDL_KEYDOWN && e.key.repeat == 0)
        {
            switch(e.key.keysym.sym)
            {
                case SDLK_UP:
                    d_velY -= d_vel;
                    break;
                case SDLK_DOWN:
                    d_velY += d_vel;
                    break;
                case SDLK_LEFT:
                    d_velX -= d_vel;
                    break;
                case SDLK_RIGHT:
                    d_velX += d_vel;
                    break;
            }
        }
        else if(e.type == SDL_KEYUP && e.key.repeat == 0)
        {
            switch(e.key.keysym.sym)
            {
                case SDLK_UP:
                    d_velY += d_vel;
                    break;
                case SDLK_DOWN:
                    d_velY -= d_vel;
                    break;
                case SDLK_LEFT:
                    d_velX += d_vel;
                    break;
                case SDLK_RIGHT:
                    d_velX -= d_vel;
                    break;
            }
        }
    }
}
