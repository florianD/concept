#include "../include/Character.h"

namespace rpg
{
    int Character::d_id = 0;

    enum
    {
        SOUTH=0, NORTH=2, WEST=4, EAST=6
    };

    enum
    {
        FRONT=32, BACK=40, LEFT=48, RIGHT=56
    };

    void Character::oriFromDir()
    {
        if(d_velX > 0)
        {
            d_orientation = EAST;
        }
        else if(d_velX < 0)
        {
            d_orientation = WEST;
        }
        else if(d_velY > 0)
        {
            d_orientation = SOUTH;
        }
        else if(d_velY < 0)
        {
            d_orientation = NORTH;
        }
    }

    double Character::frameFromOri(double offset)
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
        }
    }

    Character::Character():d_box({0,0,0,0}), d_vel(0), d_velX(0), d_velY(0), d_name(""), d_orientation(SOUTH), d_offset(0.0), d_clip(0)
    {
        d_id++;
        d_frame = frameFromOri(-32);
    }

    Character::Character(int x, int y, int vel, int vx, int vy, std::string name, int orientation):d_box({x,y,0,0}), d_vel(vel), d_velX(vx), d_velY(vy), d_name(name), d_orientation(orientation), d_offset(0.0), d_clip(0)
    {
        d_id++;
        d_frame = frameFromOri(-32);
    }

    Character::~Character(){}

    /*void Character::render(SDL_Renderer *renderer, SDL_Rect &cam)
    {*/
        /*SDL_Rect r;
        r.x = (d_box.x - d_box.y) * (config::SIDE_X / 2) / d_box.w - cam.x + 32;
        r.y = (d_box.x + d_box.y) * (config::SIDE_Y / 2) / d_box.h - cam.y;
        r.w = d_box.w;
        r.h = d_box.h;
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderFillRect(renderer, &r);*/

        /*SDL_Rect *currentClip = &d_spriteClips[(int)d_frame];
        d_spriteSheetTexture.render(renderer,
        (d_box.x - d_box.y) * (config::SIDE_X / 2) / d_box.w - cam.x,
        (d_box.x + d_box.y) * (config::SIDE_Y / 2) / d_box.h - cam.y - 64,
        currentClip);
    }*/

    int Character::getOrientation() const
    {
        return d_orientation;
    }

    int Character::getX() const
    {
        return d_box.x;
    }

    int Character::getY() const
    {
        return d_box.y;
    }

    std::string Character::getName() const
    {
        return d_name;
    }

    void Character::rotate(int r)
    {
        d_orientation = r;
    }

    SDL_Rect Character::getRect() const
    {
        return d_box;
    }

    void Character::resetAnimation()
    {
        d_frame = frameFromOri(-32);
        d_clip = 0;
        d_offset = 0.0;
    }

    void Character::walk()
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
                if((int)d_frame >= frameFromOri(7))
                {
                    d_clip = frameFromOri(0);
                }
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
            d_frame = frameFromOri(d_clip % 8 - 32) + d_offset;
            if(d_offset >= 0.4)
            {
                d_offset = 0.0;
                d_clip++;
                if((int)d_frame >= frameFromOri(7))
                {
                    d_clip = frameFromOri(-32);
                }
            }
        }
    }

    void Character::moveTo(int x, int y)
    {
        d_box.x = x;
        d_box.y = y;
        d_orientation = SOUTH;
    }

    int Character::getVel() const
    {
        return d_vel;
    }

    int Character::getVelX() const
    {
        return d_velX;
    }

    int Character::getVelY() const
    {
        return d_velY;
    }

    void Character::setVel(int vel)
    {
        d_vel = vel;
    }

    void Character::setVelX(int vel)
    {
        d_velX = vel;
    }

    void Character::setVelY(int vel)
    {
        d_velY = vel;
    }

    bool Character::isMotionless() const
    {
        return (getVelX() == 0 && getVelY() == 0);
    }
}
