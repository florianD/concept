#include "../include/Player.h"

namespace rpg
{
    SDL_Rect Player::d_spriteClips[128];
    Image Player::d_spriteSheetTexture;

    enum
    {
        DFRONT=64, FRONT=72, DLEFT=80, LEFT=88, DBACK=96, BACK=104, DRIGHT=112, RIGHT=120
    };

    Player::Player(int x, int y, int vel, int vx, int vy, std::string name, int orientation, SDL_Renderer *renderer):Character(x, y, vel, vx, vy, name, orientation)
    {
        d_box.w = 32;
        d_box.h = 32;
        d_frame = frameFromOri(-64);
    }

    double Player::frameFromOri(double offset)
    {
        switch(d_orientation)
        {
            case EAST:
                return RIGHT + (int)offset;
            case WEST:
                return LEFT + (int)offset;
            case SOUTH:
                return FRONT + (int)offset;
            case NORTH:
                return BACK + (int)offset;
            case DEAST:
                return DRIGHT + (int)offset;
            case DWEST:
                return DLEFT + (int)offset;
            case DSOUTH:
                return DFRONT + (int)offset;
            case DNORTH:
                return DBACK + (int)offset;
        }
    }

    void Player::resetAnimation()
    {
        d_frame = frameFromOri(-64);
        d_clip = 0;
        d_offset = 0.0;
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
            int frames_w = 8;
            int frames_h = 8;
            int groups_w = 1;
            int groups_h = 2;

            int size_w = d_spriteSheetTexture.getWidth() / (groups_w * frames_w);
            int size_h = (d_spriteSheetTexture.getHeight() - (frames_h * groups_h - 1)) / (groups_h * frames_h);

            int offset_h = 0;

            int k = 0;
            for(int i = 0; i < groups_h * frames_h; ++i)
            {
                for(int j = 0; j < groups_w * frames_w; ++j)
                {
                    d_spriteClips[k].x = j * size_w;
                    d_spriteClips[k].y = i * size_h + offset_h;
                    d_spriteClips[k].w = size_w;
                    d_spriteClips[k++].h = size_h;
                }
                offset_h++;
            }
        }
        return success;
    }

    void Player::render(SDL_Renderer *renderer, SDL_Rect &cam)
    {
        /*SDL_Rect r;
        r.x = (d_box.x - d_box.y) * (config::SIDE_X / 2) / d_box.w - cam.x + config::OFFSET_X * 2;
        r.y = (d_box.x + d_box.y) * (config::SIDE_Y / 2) / d_box.h - cam.y + config::OFFSET_Y + config::SIDE_Y;
        r.w = d_box.w;
        r.h = d_box.h;
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderFillRect(renderer, &r);*/

        SDL_Rect *currentClip = &d_spriteClips[(int)d_frame];
        d_spriteSheetTexture.render(renderer,
        (d_box.x - d_box.y) * (config::SIDE_X / 2) / d_box.w - cam.x + config::OFFSET_X,
        (d_box.x + d_box.y) * (config::SIDE_Y / 2) / d_box.h - cam.y + config::OFFSET_Y,
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
