#include "../include/Character.h"

namespace rpg
{
    int Character::d_id = 0;

    enum
    {
        SOUTH=0, NORTH=1, WEST=2, EAST=3, DSOUTH=4, DNORTH=5, DWEST=6, DEAST=7
    };

    enum
    {
        FRONT=64, BACK=72, LEFT=80, RIGHT=88, DFRONT=96, DBACK=104, DLEFT=112, DRIGHT=120
    };

    void Character::oriFromDir()
    {
        if(d_velX > 0)
        {
            d_orientation = EAST;
            if(d_velY > 0)
            {
                d_orientation = DSOUTH;
            }
            else if(d_velY < 0)
            {
                d_orientation = DEAST;
            }
        }
        else if(d_velX < 0)
        {
            d_orientation = WEST;
            if(d_velY < 0)
            {
                d_orientation = DNORTH;
            }
            else if(d_velY > 0)
            {
                d_orientation = DWEST;
            }
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

    Character::Character():d_box({0,0,0,0}), d_vel(0), d_velX(0), d_velY(0), d_name(""), d_orientation(SOUTH), d_offset(0.0), d_clip(0)
    {
        d_id++;
        d_frame = frameFromOri(-64);
    }

    Character::Character(int x, int y, int vel, int vx, int vy, std::string name, int orientation):d_box({x,y,0,0}), d_vel(vel), d_velX(vx), d_velY(vy), d_name(name), d_orientation(orientation), d_offset(0.0), d_clip(0)
    {
        d_id++;
        d_frame = frameFromOri(-64);
    }

    Character::~Character(){}

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
        d_frame = frameFromOri(-64);
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
            d_frame = frameFromOri(d_clip % 8 - 64) + d_offset;
            if(d_offset >= 0.4)
            {
                d_offset = 0.0;
                d_clip++;
                if((int)d_frame >= frameFromOri(7))
                {
                    d_clip = frameFromOri(-64);
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
