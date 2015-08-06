#include "../include/Player.h"

namespace rpg
{
    enum
    {
        SOUTH=0, NORTH=2, WEST=4, EAST=6
    };

    Player::Player(int x, int y, int vel, int vx, int vy, string name, int orientation, SDL_Renderer *renderer):Character(x, y, vel, vx, vy, name, orientation)
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
            d_box.w = d_spriteSheetTexture.getWidth() / 12;
            d_box.h = d_spriteSheetTexture.getHeight() / 4;
            int k = 0;
            for(int i = 0; i <= 2; i+=2)
            {
                for(int j = 0; j < 12; ++j)
                {
                    d_spriteClips[k].x = j * d_box.w;
                    d_spriteClips[k].y = (i+1) * d_box.h;
                    d_spriteClips[k].w = d_box.w;
                    d_spriteClips[k++].h = d_box.h;

                    d_spriteClips[k].x = j * d_box.w;
                    d_spriteClips[k].y = i * d_box.h;
                    d_spriteClips[k].w = d_box.w;
                    d_spriteClips[k++].h = d_box.h;
                }
            }
        }
        return success;
    }

    Player::~Player()
    {
        d_spriteSheetTexture.free();
    }

    void Player::renderT(SDL_Renderer *renderer, SDL_Rect &cam)
    {
        SDL_Rect *currentClip = &d_spriteClips[d_frame+1];
        d_spriteSheetTexture.render(renderer, d_x - cam.x, d_y - cam.y - d_box.h, currentClip);
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
