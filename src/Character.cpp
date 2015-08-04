#include "../include/Character.h"

namespace rpg
{
    enum
    {
        SOUTH=0, NORTH=2, WEST=4, EAST=6
    };

    enum
    {
        FRONT=0, BACK=6, LEFT=12, RIGHT=18
    };

    // range dans d_orientation l'entier correspondant au mouvement
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

    // range dans d_frame l'entier correspondant à l'orientation
    void Character::frameFromOri(int offset)
    {
        switch(d_orientation)
        {
            case EAST:
                d_frame = RIGHT + offset;
                break;
            case WEST:
                d_frame = LEFT + offset;
                break;
            case SOUTH:
                d_frame = FRONT + offset;
                break;
            case NORTH:
                d_frame = BACK + offset;
                break;
        }
    }

    Character::Character():d_x(0), d_y(0), d_id(0), d_vel(2), d_velX(0), d_velY(0), d_name(""), d_orientation(SOUTH), d_frame(0), d_foot(0)
    {
        frameFromOri(0);
    }

    Character::Character(int x, int y, int vel, int vx, int vy, int id, string name, int orientation):d_x(x), d_y(y), d_vel(vel), d_velX(vx), d_velY(vy), d_id(id), d_name(name), d_orientation(orientation), d_frame(0), d_foot(0)
    {
        frameFromOri(0);
    }

    Character::~Character(){}

    int Character::getOrientation() const
    {
        return d_orientation;
    }

    int Character::getX() const
    {
        return d_x;
    }

    int Character::getY() const
    {
        return d_y;
    }

    string Character::getName() const
    {
        return d_name;
    }

    void Character::rotate(int r)
    {
        d_orientation = r;
    }

    void Character::walk()
    {

    }

    void Character::moveTo(int x, int y)
    {
        d_x = x;
        d_y = y;
        d_orientation = SOUTH;
    }

    void Character::render(SDL_Renderer *renderer, int camx, int camy)
    {
        SDL_Rect *currentClip = &d_spriteClips[d_frame];
        d_spriteSheetTexture.render(renderer, d_x - camx, d_y - camy, currentClip);
    }

    void Character::renderT(SDL_Renderer *renderer, int camx, int camy)
    {
        SDL_Rect *currentClip = &d_spriteClips[d_frame+1];
        d_spriteSheetTexture.render(renderer, d_x - camx, d_y - camy - config::d_side, currentClip);
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
