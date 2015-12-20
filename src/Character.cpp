#include "../include/Character.h"

namespace rpg
{
    int Character::d_num = 0;

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

    Character::Character():d_box({0,0,0,0}), d_vel(0), d_velX(0), d_velY(0), d_name(""), d_orientation(SOUTH), d_offset(0.0), d_clip(0), d_id(d_num++)
    {
    }

    Character::Character(int x, int y, int vel, int vx, int vy, std::string name, int orientation):d_box({x,y,0,0}), d_vel(vel), d_velX(vx), d_velY(vy), d_name(name), d_orientation(orientation), d_offset(0.0), d_clip(0), d_id(d_num++)
    {
    }

    Character::~Character()
    {
        d_num--;
    }

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

    void Character::moveTo(int x, int y)
    {
        d_box.x = x;
        d_box.y = y;
        d_orientation = SOUTH;
    }

    int Character::getId() const
    {
        return d_id;
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
