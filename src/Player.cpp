#include "../include/Player.h"

namespace rpg
{
    int Player::d_size_w = 0;
    int Player::d_size_h = 0;
    SDL_Rect Player::d_spriteClips[128];
    Image Player::d_spriteSheetTexture;

    Player::Player(int x, int y, int vel, int vx, int vy, std::string name, int orientation, SDL_Renderer *renderer):Character(x, y, vel, vx, vy, name, orientation)
    {
        d_box.w = 32;
        d_box.h = 32;
    }

    bool Player::loadSpriteSheet(SDL_Renderer *renderer)
    {
        bool success = true;

        if(!d_spriteSheetTexture.load("img/object/char/player.png", renderer))
        {
            printf("Failed to load player texture\n");
            success = false;
        }
        else
        {
            d_size_w = (d_spriteSheetTexture.getWidth() / 8);
            d_size_h = (d_spriteSheetTexture.getHeight() / 16);

            int k = 0;
            for(int i = 0; i < 16; ++i)
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

    void Player::render(SDL_Renderer *renderer, SDL_Rect &cam)
    {
        /*SDL_Rect r;
        r.x = (d_box.x - d_box.y) * (config::SIDE_X / 2) / d_box.w - cam.x + 32;
        r.y = (d_box.x + d_box.y) * (config::SIDE_Y / 2) / d_box.h - cam.y;
        r.w = d_box.w;
        r.h = d_box.h;
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderFillRect(renderer, &r);*/

        SDL_Rect *currentClip = &d_spriteClips[(int)d_frame];
        d_spriteSheetTexture.render(renderer,
        (d_box.x - d_box.y) * (config::SIDE_X / 2) / d_box.w - cam.x,
        (d_box.x + d_box.y) * (config::SIDE_Y / 2) / d_box.h - cam.y - 64,
        currentClip);
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
