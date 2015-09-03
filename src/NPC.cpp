#include "../include/NPC.h"

namespace rpg
{
    SDL_Rect NPC::d_spriteClips[144];
    Image NPC::d_spriteSheetTexture;

    enum
    {
        DFRONT=80, FRONT=88, DLEFT=96, LEFT=104, DBACK=112, BACK=120, DRIGHT=128, RIGHT=136
    };

    NPC::NPC(int x, int y, int vel, int vx, int vy, std::string name, int orientation, SDL_Renderer *renderer):Character(x, y, vel, vx, vy, name, orientation)
    {
        d_box.w = 32;
        d_box.h = 32;
        d_frame = frameFromOri(-64);
    }

    double NPC::frameFromOri(double offset)
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

    bool NPC::loadSpriteSheet(SDL_Renderer *renderer)
    {
        bool success = true;

        if(!d_spriteSheetTexture.load("img/object/char/npc.png", renderer))
        {
            printf("Failed to load npc texture\n");
            success = false;
        }
        else
        {
            int frames_w = 10;
            int frames_h = 8;
            int groups_w = 1;
            int groups_h = 2;

            int size_w = d_spriteSheetTexture.getWidth() / (groups_w * frames_w);
            int size_h = (d_spriteSheetTexture.getHeight() - (frames_h * groups_h - 1)) / (groups_h * frames_h);

            int offset_h = 0;

            int k = 0;
            for(int i = 0; i < 8; ++i)
            {
                for(int j = 0; j < frames_w; ++j)
                {
                    d_spriteClips[k].x = j * size_w;
                    d_spriteClips[k].y = i * size_h + offset_h;
                    d_spriteClips[k].w = size_w;
                    d_spriteClips[k++].h = size_h;
                }
                offset_h++;
            }

            for(int i = 8; i < 16; ++i)
            {
                for(int j = 0; j < 8; ++j)
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

    void NPC::render(SDL_Renderer *renderer, SDL_Rect &cam)
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

    void NPC::resetAnimation()
    {
        int offset = d_orientation * 2;
        d_frame = frameFromOri(-80 + offset);
        d_clip = 0;
        d_offset = 0.0;
    }

    void NPC::walk()
    {
        oriFromDir();
        d_offset += 0.1;
        if(!isMotionless())
        {
            d_frame = frameFromOri(d_clip % 8) + d_offset;
            if(d_offset >= 0.2)
            {
                d_offset = 0.0;
                d_clip++;
                /*if((int)d_frame > frameFromOri(8))
                {
                    d_clip = frameFromOri(0);
                }*/
            }
            d_box.x += d_velX;
            d_box.y += d_velY;
            if((d_box.x < 0) || (d_box.x + d_box.w > (config::LEVEL_W / (config::SIDE_X / d_box.w) + (config::SIDE_Y - d_box.w) / 2)))
            {
                d_box.x -= d_velX;
                resetAnimation();
            }
            if((d_box.y < 0) || (d_box.y + d_box.h > (config::LEVEL_H / (config::SIDE_Y / d_box.h) + (config::SIDE_Y - d_box.w) / 2)))
            {
                d_box.y -= d_velY;
                resetAnimation();
            }
        }
        else
        {
            int offset = d_orientation * 2;
            d_frame = frameFromOri(d_clip % 10 - 80 + offset) + d_offset;
            if(d_offset >= 0.4)
            {
                d_offset = 0.0;
                d_clip++;
                /*if((int)d_frame > frameFromOri(10))
                {
                    d_clip = frameFromOri(-80 + offset);
                }*/
            }
        }
    }

    NPC::~NPC()
    {
        d_spriteSheetTexture.free();
    }
}
